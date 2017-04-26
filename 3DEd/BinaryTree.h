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
		double coefficient[4];//a*x, b*y, c*z, d
		bool side_of_camera;//находится путём подставления координаты точки начала камеры в уравнения и деления на модуль полученного 

		~BinTree();
	};



	class BinaryTree {
	private:
		BinTree* tmp;
		BinTree* root;
		BinTree* active_node;
		Point zero_point_of_camera;
		CoordinateSystem converted_coord_system_from_model;
		CoordinateSystem converted_coord_system_from_camera;
	protected:
		void recursiveAddElement();
	public:
		BinaryTree();

		//Не забыть про различные системы координат при отослании координаты камеры
		void setConvertedCoordSystemFromModel(const CoordinateSystem & converted_coord_system_from_model);
		void setConvertedCoordSystemFromCamera(const CoordinateSystem & converted_coord_system_from_camera);
		void setZeroPointOfCamera(Point zero_point_of_camera);
		void setRoot(Polygon polygon, Point zero_point_of_camera);
		void addElement(Polygon polygon);
		void clear();

		std::vector<Polygon> addPolygons();
		BinTree* getBinaryTree() const;
		~BinaryTree();
	};
}
