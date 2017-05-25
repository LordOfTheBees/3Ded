#include "Point.h"
#include <vector>
#pragma once
//������� �� �������� ������� ��������� � basis
//setCoordsystem(T) - ����� �����, ������� ������������ � ������ �����������
//setBasisCoordsystem(P) - ����� �����, ��� ��� ����� �����. �� ���� � ��� ������� ��������� � ����� ���������� 
//convertToBasis - ���������� �����, �������� � ������� ��������� T � �����, ������� ������ � P. ��������� ��� ����������.
namespace tdrw {
	class CoordinateSystem
	{
	private:
		int size;
		std::vector<std::vector<double>> * m_coord_system;
		std::vector<std::vector<double>> * m_basis_coord_system;
		std::vector<std::vector<double>> * m_transition_matrix;
		Point zero_point;
		Point zero_point_of_basis;
	protected:
	public:
		CoordinateSystem& operator=(const CoordinateSystem& right);

		CoordinateSystem();
		CoordinateSystem(const CoordinateSystem& right);

		void setBasisCoordSystem(std::vector<std::vector<double>> c_p, const Point& zer);
		void setBasisCoordSystem(const CoordinateSystem& coord);
		void setCoordSystem(std::vector<std::vector<double>> c_p, Point& zer);
		void setCoordSystem(const CoordinateSystem& r_value);
		void setZeroPointOfCoord(const Point& zero_point);

		void rotationAngleOnX(double alpha);
		void rotationAngleOnY(double alpha);
		void rotationAngleOnZ(double alpha);
		void generateTransitionMatrix();
		Point convertToBasis(const Point& point) const;

		std::vector<std::vector<double>> CoordinateSystem::getMatrixOfCoord() const;
		Point CoordinateSystem::getZeroPoint() const;
		std::vector<double> getXAxis() const;
		std::vector<double> getYAxis() const;
		std::vector<double> getZAxis() const;

		~CoordinateSystem();
	};
}
