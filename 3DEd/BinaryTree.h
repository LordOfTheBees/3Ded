#pragma once
#include <vector>
#include <cmath>

#include "Point.h"
#include "Polygon.h"
#include "CoordinateSystem.h"
#include "Camera.h"
#include "Model.h"

namespace tdrw {
	class BinTree {
	public:
		BinTree();

		BinTree* closer;
		BinTree* further;
		Polygon polygon;
		std::vector<Point> points;
		std::vector<double> coefficient;//a*x, b*y, c*z, d
		bool side_of_camera;//находится путём подставления координаты точки начала камеры в уравнения и деления на модуль полученного 

		~BinTree();
	};



	class BinaryTree {
	private:
		BinTree* tmp;
		BinTree* root;
		BinTree* active_node;
		Point zero_point_of_camera;
		Camera m_camera;
		std::vector<Point> m_points;

		int m_counter_splitted_polygon;
		std::vector<BinTree*> m_node_for_recalculated;

		bool m_wrong_side_is_active;
	protected:
		void recursiveAddElement();
		void recursiveAddElementWithoutSplitted();
	public:
		BinaryTree();

		//Не забыть про различные системы координат при отослании координаты камеры
		void setCamera(const Camera& camera);
		void setZeroPointOfCamera(Point zero_point_of_camera);
		void addElement(const Polygon& polygon);
		void clear();

		void activeWrongSide(bool switcher);

		std::vector<Polygon> addPolygons();
		BinTree* getBinaryTree() const;
		~BinaryTree();
	};
}
