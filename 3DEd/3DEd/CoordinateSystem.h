#include "Point.h"
#pragma once
//������� �� �������� ������� ��������� � basis
//setCoordsystem(T) - ����� �����, ������� ������������ � ������ �����������
//setBasisCoordsystem(P) - ����� �����, ��� ��� ����� �����. �� ���� � ��� ������� ��������� � ����� ���������� 
//convertToBasis - ���������� �����, �������� � ������� ��������� T � �����, ������� ������ � P. ��������� ��� ����������.
class CoordinateSystem
{
private:
	int size;
	double ** coord_system;
	double ** basis_coord_system;
	double ** transition_matrix;
	Point zero_point;
	Point zero_point_of_basis;
protected:
public:
	CoordinateSystem& operator=(const CoordinateSystem& right);

	CoordinateSystem();
	CoordinateSystem(int n);
	CoordinateSystem(const CoordinateSystem& right);

	void setBasisCoordSystem(double ** c_p, const Point& zer);
	void setBasisCoordSystem(const CoordinateSystem& coord);
	void setCoordSystem(double ** c_p, Point& zer);
	void setCoordSystem(const CoordinateSystem& r_value);

	void generateTransitionMatrix();
	Point convertToBasis(const Point& point);

	double ** CoordinateSystem::getMatrixOfCoord() const;
	Point CoordinateSystem::getZeroPoint() const;
	~CoordinateSystem();
};

