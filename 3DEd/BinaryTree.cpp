#include "BinaryTree.h"
#include <iostream>

namespace tdrw {
	void BinaryTree::recursiveAddElement() {
		double n;
		bool side;
		for (int i = 0; i < m_points.size(); ++i) {
			n = m_points[i].x * m_active_node->coefficient[0] + m_points[i].y * m_active_node->coefficient[1] + m_points[i].z * m_active_node->coefficient[2] + m_active_node->coefficient[3];
			if (n == 0)
				continue;
			side = std::signbit(n);

			if (side == m_active_node->side_of_camera) {
				if (m_active_node->closer == nullptr) {
					m_active_node->closer = m_tmp;
					m_tmp = nullptr;
					return;
				}
				else {
					m_active_node = m_active_node->closer;
					recursiveAddElement();
					return;
				}
			}
			else {
				if (m_active_node->further == nullptr) {
					m_active_node->further = m_tmp;
					m_tmp = nullptr;
					return;
				}
				else {
					m_active_node = m_active_node->further;
					recursiveAddElement();
					return;
				}
			}

		}

		//если для данной итерации все точки проверяемого полигона лежат на плоскости выбранного(m_active_node->polygon) то заходим сюда
		if (m_active_node->closer == nullptr) {
			m_active_node->closer = m_tmp;
			m_tmp = nullptr;
			return;
		}
		else {
			m_active_node = m_active_node->closer;
			recursiveAddElement();
			return;
		}

		return;
	}

	BinaryTree::BinaryTree() {
		m_wrong_side_is_active = true;
		m_tmp = nullptr;
		m_root = nullptr;
		m_active_node = nullptr;
	}

	void BinaryTree::setCamera(const Camera & camera) {
		m_camera = camera;
	}

	void BinaryTree::setZeroPointOfCamera(Point zero_point_of_camera) {
		this->m_zero_point_of_camera = zero_point_of_camera;
	}

	void BinaryTree::addElement(const Polygon& polygon) {
		m_tmp = new BinTree;
		m_tmp->coefficient = polygon.getNormal();

		if (!m_wrong_side_is_active) {
			std::vector<double> t_direction_gaze = m_camera.getDirectionOfGaze();
			double alpha = (t_direction_gaze[0] * m_tmp->coefficient[0] + t_direction_gaze[1] * m_tmp->coefficient[1] + t_direction_gaze[2] * m_tmp->coefficient[2]) /
				(std::sqrt(std::pow(t_direction_gaze[0], 2) + std::pow(t_direction_gaze[1], 2) + std::pow(t_direction_gaze[2], 2))*std::sqrt(std::pow(m_tmp->coefficient[0], 2) + std::pow(m_tmp->coefficient[1], 2) + std::pow(m_tmp->coefficient[2], 2)));

			if (alpha >= 1 / 2) {
				delete m_tmp;
				return;
			}
		}

		m_tmp->polygon = polygon;

		double n = m_zero_point_of_camera.x * m_tmp->coefficient[0] + m_zero_point_of_camera.y * m_tmp->coefficient[1] + m_zero_point_of_camera.z * m_tmp->coefficient[2] + m_tmp->coefficient[3];
		m_tmp->side_of_camera = std::signbit(n);

		if (m_root == nullptr) {
			m_root = m_tmp;
			m_tmp = nullptr;
			return;
		}
		m_active_node = m_root;

		m_points = m_tmp->polygon.getConvertedPoints();
		recursiveAddElement();
	}

	void BinaryTree::clear() {
		//delete m_tmp;
		delete m_root;
		m_root = nullptr;
		m_active_node = nullptr;
	}

	void BinaryTree::activeWrongSide(bool switcher) {
		m_wrong_side_is_active = switcher;
	}

	std::vector<Polygon> BinaryTree::addPolygons() {
		return std::vector<Polygon>();
	}

	BinTree * BinaryTree::getBinaryTree() const {
		return m_root;
	}


	BinaryTree::~BinaryTree() {
		m_active_node = nullptr;
		delete m_root;
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