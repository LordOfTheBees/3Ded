#pragma once
#include <vector>
#include <cmath>

#include "Camera.h"
#include "Point.h"
#include "Polygon.h"
#include "CoordinateSystem.h"
#include "Model.h"



namespace tdrw {
	class BinTree {
	public:
		BinTree();

		BinTree* closer;
		BinTree* further;
		Polygon polygon;
		std::vector<double> coefficient;//a*x, b*y, c*z, d
		bool side_of_camera;//находится путём подставления координаты точки начала камеры в уравнения и деления на модуль полученного 

		~BinTree();
	};



	class BinaryTree {
	private:
		BinTree* m_tmp;
		BinTree* m_root;
		BinTree* m_active_node;
		Camera m_camera;
		Point m_zero_point_of_camera;
		std::vector<Point> m_points;

		bool m_wrong_side_is_active;
	protected:
		void recursiveAddElement();
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
