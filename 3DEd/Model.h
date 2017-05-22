#include "Point.h"
#include "CoordinateSystem.h"
#include "Polygon.h"
#include "ArrayOfPoints.h"

#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#pragma once
namespace tdrw {
	class Data {
	public:
		std::string m_type;
		std::vector<double> m_coordinates;//�������� ������ ��� ����� v, vt, vn, vp
		std::vector<int> m_vertices;//���������� ������ ��� ���� f
		std::vector<int> m_texture_coordinates;// ���������� ���������� ��� ���� f
		std::vector<int> m_normal;//������� ��� ���� f
	};

	class Model: public ArrayOfPoints
	{
	private:
		CoordinateSystem m_own_coord_system;
		std::vector<Polygon> m_polygons;
	protected:
	public:
		void operator=(const Model& right);

		Model();
		Model(const Model& right);

		void setModelCoordSystem(const CoordinateSystem& model_coord_system);
		void setWorldCoordSystem(const CoordinateSystem& world_coord_system);

		//�������� ������� ��� ���������� ����� � ����� ���
		void addPolygon(Polygon polygon);
		//�������� ������� ��� ���������� ����� � ����� ���
		void addPolygon(std::vector<Point*> points, sf::Color color);
		//�������� ������� ��� ���������� ����� � ����� ���
		void addPolygon(Point* point1, Point* point2, Point* point3, sf::Color color);
		//�������� ������� � ���������� ����� � ����� ���
		void addPolygon(std::vector<Point> points, sf::Color color);
		//�������� ������� � ���������� ����� � ����� ���
		void addPolygon(Point point1, Point point2, Point point3, sf::Color color);

		void rotationAngleOnX(double alpha);
		void rotationAngleOnY(double alpha);
		void rotationAngleOnZ(double alpha);
		void setZeroPointOfCoord(const Point& zero_point);

		CoordinateSystem getCoordSystem();
		Point* getPoint(const sf::Vector2f mouse_coord);
		std::vector<Polygon> getAllPolygon() const;

		Point convertToWorldCoordSystem(const Point& point) const;

		Data separator(std::string str);
		bool load(const std::string file_path);
		bool save(const std::string file_path);

		bool deletePoint(Point* point);
		~Model();
	};
}
