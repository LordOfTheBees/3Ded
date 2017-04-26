#include "CoordinateSystem.h"
#include <iostream>
#include <vector>

CoordinateSystem & CoordinateSystem::operator=(const CoordinateSystem & right)
{
	if (this == &right)
		return *this;
	this->size = right.size;

	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j) {
			this->coord_system[i][j] = right.coord_system[i][j];
		}
	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j) {
			this->basis_coord_system[i][j] = right.basis_coord_system[i][j];
		}

	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j) {
			this->transition_matrix[i][j] = right.transition_matrix[i][j];
		}

	this->zero_point_of_basis = right.zero_point_of_basis;
	this->zero_point = right.zero_point;
	return *this;
}

CoordinateSystem::CoordinateSystem() {
	size = 3;
	this->coord_system = new double*[size];
	for (int i = 0; i < size; ++i)
		this->coord_system[i] = new double[size];


	this->basis_coord_system = new double*[size];
	for (int i = 0; i < size; ++i)
		this->basis_coord_system[i] = new double[size];


	this->transition_matrix = new double*[size];
	for (int i = 0; i < size; ++i)
		this->transition_matrix[i] = new double[size];
}

CoordinateSystem::CoordinateSystem(int size) {
	this->size = size;

	coord_system = new double*[size];
	for (int i = 0; i < size; ++i)
		coord_system[i] = new double[size];

	this->basis_coord_system = new double*[size];
	for (int i = 0; i < size; ++i)
		this->basis_coord_system[i] = new double[size];

	transition_matrix = new double*[size];
	for (int i = 0; i < size; ++i)
		transition_matrix[i] = new double[size];
}

CoordinateSystem::CoordinateSystem(const CoordinateSystem & right){
	this->size = right.size;

	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j) {
			this->coord_system[i][j] = right.coord_system[i][j];
		}
	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j) {
			this->basis_coord_system[i][j] = right.basis_coord_system[i][j];
		}

	for (int i = 0; i < this->size; ++i)
		for (int j = 0; j < this->size; ++j) {
			this->transition_matrix[i][j] = right.transition_matrix[i][j];
		}

	this->zero_point_of_basis = right.zero_point_of_basis;
	this->zero_point = right.zero_point;
}

void CoordinateSystem::setBasisCoordSystem(double ** c_p, const Point & zer) {
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j) {
			this->basis_coord_system[i][j] = c_p[i][j];
		}

	zero_point_of_basis = zer;
}

void CoordinateSystem::setBasisCoordSystem(const CoordinateSystem & coord) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			this->basis_coord_system[i][j] = coord.coord_system[i][j];
		}
	}

	zero_point_of_basis = coord.zero_point;
}

void CoordinateSystem::setCoordSystem(double ** c_p, Point& zer) {
	this->zero_point = zer;

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j) {
			coord_system[i][j] = c_p[i][j];
		}
}

void CoordinateSystem::setCoordSystem(const CoordinateSystem & r_value) {
	this->zero_point = r_value.zero_point;
	this->size = r_value.size;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j)
			coord_system[i][j] = r_value.coord_system[i][j];
	}
}


void CoordinateSystem::generateTransitionMatrix() {
	//Ќайти матрицу перехода от —(е->е') от базиса
	//	e1 = (-2, 1, -1), e2 = (1, -1, 3), e3 = (1, 2, -1) к базису
	//	е'1 = ( -1, 2, 3) , е'2 = (2, 1, 2), e'3 = ( 0, 2, 1 )

	//	(-2  1  1 | -1  2  0)
	//	( 1 -1  2 |  2  1  2)
	//	(-1  3 -1 |  3  2  1)
	//	и после элементарных преобразований получаем :
	//  (1 0 0 | 2 0 1)
	//	(0 1 0 | 2 1 0)
	//	(0 0 1 | 1 1 1)

	double ** tmp_coord_system;
	tmp_coord_system = new double*[size];
	for (int i = 0; i < size; ++i)
		tmp_coord_system[i] = new double[size];

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j) {
			tmp_coord_system[i][j] = coord_system[i][j];
			transition_matrix[i][j] = basis_coord_system[i][j];
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

			transition_matrix[d1[i]][j] += k1 * transition_matrix[i][j];
			transition_matrix[d2[i]][j] += k2 * transition_matrix[i][j];
			transition_matrix[i][j] /= tmp;
		}

	}

	for (int i = 0; i < size; ++i)
		delete[] tmp_coord_system[i];
	delete[] tmp_coord_system;
	//верно, проверено
}

Point CoordinateSystem::convertToBasis(const Point& point) {
	std::vector<double> point_coord = point.getCoord();
	double * new_coord = new double[size];

	for (int i = 0; i < size; ++i) {
		new_coord[i] = 0;
		for (int j = 0; j < size; ++j)
			new_coord[i] += point_coord[j] * transition_matrix[i][j];
	}
	//std::cout << new_coord[0] << " " << new_coord[1] << " " << new_coord[2] << std::endl;
	Point converted_point(new_coord[0], new_coord[1], new_coord[2]);
	return converted_point + zero_point - zero_point_of_basis;
	//верно, проверено
}

double ** CoordinateSystem::getMatrixOfCoord() const {
	double ** tmp = new double*[size];
	for (int i = 0; i < size; ++i)
		tmp[i] = new double[size];

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			tmp[i][j] = coord_system[i][j];
	return tmp;
}

Point CoordinateSystem::getZeroPoint() const {
	return zero_point;
}


CoordinateSystem::~CoordinateSystem() {
	if (coord_system != nullptr) {
		for (int i = 0; i < size; ++i)
			delete[] coord_system[i];
		delete[] coord_system;
	}

	if (transition_matrix != nullptr) {
		for (int i = 0; i < size; ++i)
			delete[] transition_matrix[i];
		delete[] transition_matrix;
	}
}
