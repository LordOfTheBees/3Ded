#include "CoordinateSystem.h"
#include <iostream>
#include <cmath>

namespace tdrw {
	CoordinateSystem & CoordinateSystem::operator=(const CoordinateSystem & right)
	{
		if (this == &right)
			return *this;
		this->size = right.size;

		m_coord_system = new std::vector<std::vector<double>>(size, std::vector<double>(size));
		m_basis_coord_system = new std::vector<std::vector<double>>(size, std::vector<double>(size));
		m_transition_matrix = new std::vector<std::vector<double>>(size, std::vector<double>(size));

		m_own_is_exist = right.m_own_is_exist;
		m_basic_is_exist = right.m_basic_is_exist;

		if (right.m_basic_is_exist)
			*m_basis_coord_system = *right.m_basis_coord_system;

		if (right.m_own_is_exist)
			*m_coord_system = *right.m_coord_system;

		if ((right.m_basic_is_exist) && (right.m_own_is_exist))
			*m_transition_matrix = *right.m_transition_matrix;

		this->zero_point_of_basis = right.zero_point_of_basis;
		this->zero_point = right.zero_point;
		return *this;
	}

	CoordinateSystem::CoordinateSystem() {
		m_own_is_exist = false;
		m_basic_is_exist = false;
		size = 3;

		m_coord_system = new std::vector<std::vector<double>>(size, std::vector<double>(size));
		m_basis_coord_system = new std::vector<std::vector<double>>(size, std::vector<double>(size));
		m_transition_matrix = new std::vector<std::vector<double>>(size, std::vector<double>(size));
	}

	CoordinateSystem::CoordinateSystem(const CoordinateSystem & right) {
		this->size = right.size;

		m_coord_system = new std::vector<std::vector<double>>(size, std::vector<double>(size));
		m_basis_coord_system = new std::vector<std::vector<double>>(size, std::vector<double>(size));
		m_transition_matrix = new std::vector<std::vector<double>>(size, std::vector<double>(size));

		m_own_is_exist = right.m_own_is_exist;
		m_basic_is_exist = right.m_basic_is_exist;

		if(right.m_basic_is_exist)
			*m_basis_coord_system = *right.m_basis_coord_system;

		if(right.m_own_is_exist)
			*m_coord_system = *right.m_coord_system;

		if((right.m_basic_is_exist) && (right.m_own_is_exist))
			*m_transition_matrix = *right.m_transition_matrix;

		this->zero_point_of_basis = right.zero_point_of_basis;
		this->zero_point = right.zero_point;
	}

	void CoordinateSystem::setBasisCoordSystem(std::vector<std::vector<double>> b_c_s, const Point & zer) {
		m_basic_is_exist = true;
		*m_basis_coord_system = b_c_s;
		zero_point_of_basis = zer;

		if (m_own_is_exist)
			generateTransitionMatrix();
	}

	void CoordinateSystem::setBasisCoordSystem(const CoordinateSystem & coord) {
		m_basic_is_exist = true;
		*m_basis_coord_system = *coord.m_coord_system;
		zero_point_of_basis = coord.zero_point;

		if (m_own_is_exist)
			generateTransitionMatrix();
	}

	void CoordinateSystem::setCoordSystem(std::vector<std::vector<double>> c_s, Point& zer) {
		m_own_is_exist = true;
		this->zero_point = zer;
		*m_coord_system = c_s;

		if (m_basic_is_exist)
			generateTransitionMatrix();
	}

	void CoordinateSystem::setCoordSystem(const CoordinateSystem & r_value) {
		m_own_is_exist = true;
		this->zero_point = r_value.zero_point;
		this->size = r_value.size;
		*m_coord_system = *r_value.m_coord_system;
		
		if (m_basic_is_exist)
			generateTransitionMatrix();
	}

	void CoordinateSystem::setZeroPointOfCoord(const Point & zero_point) {
		this->zero_point = zero_point;
	}

	void CoordinateSystem::rotationAngleOnX(double alpha) {
		if (!m_own_is_exist)
			new std::exception("own coord system dousn't exist");
		double i_pi = 3.14159265;
		double i_alpha = alpha * i_pi / (2 * 180);

		std::vector<std::vector<double>> i_rotation_matrix(3, std::vector<double>(3));
		i_rotation_matrix = { {1, 0, 0},
							  {0, std::cos(i_alpha), -std::sin(i_alpha)},
							  {0, std::sin(i_alpha), std::cos(i_alpha) } };

		std::vector<std::vector<double>> i_result(3, std::vector<double>(3));
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				i_result[i][j] = 0;
				for (int k = 0; k < 3; ++k)
					i_result[i][j] += i_rotation_matrix[i][k] * (*m_coord_system)[k][j];
			}
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				(*m_coord_system)[i][j] = i_result[i][j];
			}
		}

		generateTransitionMatrix();
	}

	void CoordinateSystem::rotationAngleOnY(double alpha) {
		if (!m_own_is_exist)
			new std::exception("own coord system dousn't exist");
		double i_pi = 3.14159265;
		double i_alpha = alpha * i_pi / (2 * 180);

		std::vector<std::vector<double>> i_rotation_matrix(3, std::vector<double>(3));
		i_rotation_matrix = { { std::cos(i_alpha), 0, std::sin(i_alpha) },
							  { 0, 1, 0 },
							  { -std::sin(i_alpha), 0, std::cos(i_alpha) } };

		std::vector<std::vector<double>> i_result(3, std::vector<double>(3));
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				i_result[i][j] = 0;
				for (int k = 0; k < 3; ++k)
					i_result[i][j] += i_rotation_matrix[i][k] * (*m_coord_system)[k][j];
			}
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				(*m_coord_system)[i][j] = i_result[i][j];
			}
		}

		generateTransitionMatrix();
	}

	void CoordinateSystem::rotationAngleOnZ(double alpha) {
		if (!m_own_is_exist)
			new std::exception("own coord system dousn't exist");
		double i_pi = 3.14159265;
		double i_alpha = alpha * i_pi / (2 * 180);


		std::vector<std::vector<double>> i_rotation_matrix(3, std::vector<double>(3));
		i_rotation_matrix = { { std::cos(i_alpha), -std::sin(i_alpha), 0 },
							  { std::sin(i_alpha), std::cos(i_alpha), 0 },
							  { 0, 0, 1 } };

		std::vector<std::vector<double>> i_result(3, std::vector<double>(3));
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				i_result[i][j] = 0;
				for (int k = 0; k < 3; ++k)
					i_result[i][j] += i_rotation_matrix[i][k] * (*m_coord_system)[k][j];
			}
		}

		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				(*m_coord_system)[i][j] = i_result[i][j];
			}
		}

		generateTransitionMatrix();
	}

	void CoordinateSystem::generateTransitionMatrix() {
		//����� ������� �������� �� �(�->�') �� ������
		//	e1 = (-2, 1, -1), e2 = (1, -1, 3), e3 = (1, 2, -1) � ������
		//	�'1 = ( -1, 2, 3) , �'2 = (2, 1, 2), e'3 = ( 0, 2, 1 )

		//	(-2  1  1 | -1  2  0)
		//	( 1 -1  2 |  2  1  2)
		//	(-1  3 -1 |  3  2  1)
		//	� ����� ������������ �������������� �������� :
		//  (1 0 0 | 2 0 1)
		//	(0 1 0 | 2 1 0)
		//	(0 0 1 | 1 1 1)

		std::vector<std::vector<double>> tmp_coord_system(size, std::vector<double>(size));

		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j) {
				tmp_coord_system[i][j] = (*m_coord_system)[i][j];
				(*m_transition_matrix)[i][j] = (*m_basis_coord_system)[i][j];
			}

		for (int i = 0; i < size; ++i) {
			if (tmp_coord_system[i][i] == 0) {
				for (int j = 0; j < size; ++j) {
					if (tmp_coord_system[j][i] != 0) {
						for (int t = 0; t < size; ++t) {
							tmp_coord_system[i][t] += tmp_coord_system[j][t];
						}
						break;
					}
				}
			}
		}

		int d1[3] = { 1, 0, 0 };
		int d2[3] = { 2, 2, 1 };
		double k1, k2, tmp;
		for (int i = 0; i < size; ++i) {
			k1 = -tmp_coord_system[d1[i]][i] / tmp_coord_system[i][i];
			k2 = -tmp_coord_system[d2[i]][i] / tmp_coord_system[i][i];
			tmp = tmp_coord_system[i][i];
			for (int j = 0; j < size; ++j) {
				tmp_coord_system[d1[i]][j] += k1 * tmp_coord_system[i][j];
				tmp_coord_system[d2[i]][j] += k2 * tmp_coord_system[i][j];
				tmp_coord_system[i][j] /= tmp;

				(*m_transition_matrix)[d1[i]][j] += k1 * (*m_transition_matrix)[i][j];
				(*m_transition_matrix)[d2[i]][j] += k2 * (*m_transition_matrix)[i][j];
				(*m_transition_matrix)[i][j] /= tmp;
			}

		}

		//�����, ���������
	}

	Point CoordinateSystem::convertToBasis(const Point& point) const{
		std::vector<double> point_coord = point.getCoord();
		double * new_coord = new double[size];

		for (int i = 0; i < size; ++i) {
			new_coord[i] = 0;
			for (int j = 0; j < size; ++j)
				new_coord[i] += point_coord[j] * (*m_transition_matrix)[i][j];
		}
		//std::cout << new_coord[0] << " " << new_coord[1] << " " << new_coord[2] << std::endl;
		Point converted_point(new_coord[0], new_coord[1], new_coord[2]);
		return converted_point + zero_point - zero_point_of_basis;
		//�����, ���������
	}

	std::vector<std::vector<double>> CoordinateSystem::getMatrixOfCoord() const {
		std::vector<std::vector<double>> tmp(size, std::vector<double>(size));

		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				tmp[i][j] = (*m_coord_system)[i][j];
		return tmp;
	}

	Point CoordinateSystem::getZeroPoint() const {
		return zero_point;
	}

	std::vector<double> CoordinateSystem::getXAxis() const{
		return (*m_coord_system)[0];
	}

	std::vector<double> CoordinateSystem::getYAxis() const{
		return (*m_coord_system)[1];
	}

	std::vector<double> CoordinateSystem::getZAxis() const{
		return (*m_coord_system)[2];
	}


	CoordinateSystem::~CoordinateSystem() {
		delete m_basis_coord_system;
		delete m_coord_system;
		delete m_transition_matrix;
	}
}