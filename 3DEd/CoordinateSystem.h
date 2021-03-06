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
		int m_size;
		std::vector<std::vector<double>> * m_coord_system;
		std::vector<std::vector<double>> * m_basis_coord_system;
		std::vector<std::vector<double>> * m_transition_matrix;
		Point m_zero_point;
		Point m_zero_point_of_basis;
		bool m_basic_is_exist;
		bool m_own_is_exist;

		void generateTransitionMatrix();
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
		Point convertToBasis(const Point& point) const;

		std::vector<std::vector<double>> CoordinateSystem::getMatrixOfCoord() const;
		Point CoordinateSystem::getZeroPoint() const;
		std::vector<double> getXAxis() const;
		std::vector<double> getYAxis() const;
		std::vector<double> getZAxis() const;

		~CoordinateSystem();
	};
}
