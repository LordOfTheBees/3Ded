#include "BinaryTree.h"
#include <iostream>

namespace tdrw {
	void BinaryTree::recursiveAddElement() {
		double n;
		bool side;
		for (int i = 0; i < m_points.size(); ++i) {
			n = m_points[i].x * active_node->coefficient[0] + m_points[i].y * active_node->coefficient[1] + m_points[i].z * active_node->coefficient[2] + active_node->coefficient[3];
			if (n == 0)
				continue;
			side = std::signbit(n);

			if (side == active_node->side_of_camera) {
				if (active_node->closer == nullptr) {
					active_node->closer = tmp;
					tmp = nullptr;
					return;
				}
				else {
					active_node = active_node->closer;
					recursiveAddElement();
					return;
				}
			}
			else {
				if (active_node->further == nullptr) {
					active_node->further = tmp;
					tmp = nullptr;
					return;
				}
				else {
					active_node = active_node->further;
					recursiveAddElement();
					return;
				}
			}

		}

		//если для данной итерации все точки проверяемого полигона лежат на плоскости выбранного(active_node->polygon) то заходим сюда
		if (active_node->closer == nullptr) {
			active_node->closer = tmp;
			tmp = nullptr;
			return;
		}
		else {
			active_node = active_node->closer;
			recursiveAddElement();
			return;
		}

		return;
	}

	BinaryTree::BinaryTree() {
		tmp = nullptr;
		root = nullptr;
		active_node = nullptr;
	}

	void BinaryTree::setConvertedCoordSystemFromModel(const CoordinateSystem & converted_coord_system_from_model) {
		this->converted_coord_system_from_model = converted_coord_system_from_model;
	}

	void BinaryTree::setConvertedCoordSystemFromCamera(const CoordinateSystem & converted_coord_system_from_camera) {
		this->converted_coord_system_from_camera = converted_coord_system_from_camera;
	}

	void BinaryTree::setZeroPointOfCamera(Point zero_point_of_camera)
	{
		this->zero_point_of_camera = zero_point_of_camera;
	}

	void BinaryTree::addElement(Polygon polygon) {
		tmp = new BinTree;
		tmp->polygon = polygon;
		std::vector<Point> points = polygon.getConvertedPoints();

		Point M0 = points[0];
		Point M1 = points[1];
		Point M2 = points[2];

		tmp->coefficient[0] = -M0.y*(M2.z - M1.z) + M1.y*(M2.z - M0.z) - M2.y*(M1.z - M0.z);
		tmp->coefficient[1] = M0.z*(M1.x - M2.x) - M1.z*(M0.x - M2.x) + M2.z*(M0.x - M1.x);
		tmp->coefficient[2] = M0.x*(M1.y - M2.y) - M1.x*(M0.y - M2.y) + M2.x*(M0.y - M1.y);
		tmp->coefficient[3] = -M0.x*tmp->coefficient[0] - M0.y*tmp->coefficient[1] - M0.z*tmp->coefficient[2];

		double n = zero_point_of_camera.x * tmp->coefficient[0] + zero_point_of_camera.y * tmp->coefficient[1] + zero_point_of_camera.z * tmp->coefficient[2] + tmp->coefficient[3];
		tmp->side_of_camera = std::signbit(n);

		if (root == nullptr) {
			root = tmp;
			tmp = nullptr;
			return;
		}
		active_node = root;

		m_points = tmp->polygon.getConvertedPoints();
		recursiveAddElement();
	}

	void BinaryTree::clear() {
		delete root;
		root = nullptr;
		active_node = nullptr;
	}

	std::vector<Polygon> BinaryTree::addPolygons() {

		return std::vector<Polygon>();
	}

	BinTree * BinaryTree::getBinaryTree() const {
		return root;
	}


	BinaryTree::~BinaryTree() {
		active_node = nullptr;
		delete root;
	}

	BinTree::BinTree() {
		closer = nullptr;
		further = nullptr;
		side_of_camera = 0;
		for (int i = 0; i < 4; ++i)
			coefficient[i] = 0;
	}

	BinTree::~BinTree() {
		delete closer;
		delete further;
	}
}