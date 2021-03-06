#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Point.h"

#pragma once
namespace tdrw {
	class Model;
	class Polygon
	{
	private:
		Model* m_him_model;
		std::vector<Point*> m_points;
		sf::Color m_color;

		double square(std::vector<Point> points);
	protected:
	public:
		//not ready!!!!!!!!!!!!!!!
		friend bool operator==(const Polygon& left, const Polygon& right);

		Polygon& operator=(const Polygon& right);

		Polygon(Model * model = nullptr);
		Polygon(const Polygon& polygon);
		Polygon(Model * model, std::vector<Point*> points, sf::Color color);
		Polygon(Model * model, Point* point1, Point* point2, Point* point3, sf::Color color);

		void setPoints(std::vector<Point*> points);
		void setPoints(Point* point1, Point* point2, Point* point3);
		void setColor(sf::Color color);

		std::string getStringWithData() const;
		//���� �� ������ ����� ����� � ��������
		bool checkExistencePoint(const Point * point);
		bool hitTesting(sf::Vector2f coord_on_screen);

		std::vector<Point*> getPoints() const;
		std::vector<double> getNormal() const;
		sf::Color getColor() const;
		Model* getModel() const;
		std::vector<Point> getConvertedPoints() const;
		~Polygon();
	};
}
