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
		m_wrong_side_is_active = true;
		tmp = nullptr;
		root = nullptr;
		active_node = nullptr;
	}

	void BinaryTree::setCamera(const Camera & camera){
		m_camera = camera;
	}

	void BinaryTree::setZeroPointOfCamera(Point zero_point_of_camera)
	{
		this->zero_point_of_camera = zero_point_of_camera;
	}

	void BinaryTree::addElement(const Polygon& polygon) {
		tmp = new BinTree;		
		tmp->coefficient = polygon.getNormal();

		if (!m_wrong_side_is_active) {
			std::vector<double> t_direction_gaze = m_camera.getDirectionOfGaze();
			double alpha = (t_direction_gaze[0] * tmp->coefficient[0] + t_direction_gaze[1] * tmp->coefficient[1] + t_direction_gaze[2] * tmp->coefficient[2]) /
				(std::sqrt(std::pow(t_direction_gaze[0], 2) + std::pow(t_direction_gaze[1], 2) + std::pow(t_direction_gaze[2], 2))*std::sqrt(std::pow(tmp->coefficient[0], 2) + std::pow(tmp->coefficient[1], 2) + std::pow(tmp->coefficient[2], 2)));

			if (alpha >= 1 / 2) {
				delete tmp;
				return;
			}
		}

		tmp->polygon = polygon;

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

	void BinaryTree::activeWrongSide(bool switcher){
		m_wrong_side_is_active = switcher;
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
	}

	BinTree::~BinTree() {
		delete closer;
		delete further;
	}
}