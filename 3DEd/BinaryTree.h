#pragma once
#include <vector>
#include <cmath>

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
		BinTree* tmp;
		BinTree* root;
		BinTree* active_node;
		Point zero_point_of_camera;
		std::vector<Point> m_points;
	protected:
		void recursiveAddElement();
	public:
		BinaryTree();

		//Не забыть про различные системы координат при отослании координаты камеры
		void setZeroPointOfCamera(Point zero_point_of_camera);
		void addElement(const Polygon& polygon);
		void clear();

		std::vector<Polygon> addPolygons();
		BinTree* getBinaryTree() const;
		~BinaryTree();
	};
}
