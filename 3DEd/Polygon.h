#include <vector>
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
		std::vector<Point> points;
		sf::Color color;
	protected:
	public:
		//not ready!!!!!!!!!!!!!!!
		friend bool operator==(const Polygon& left, const Polygon& right);

		Polygon& operator=(const Polygon& right);

		Polygon();
		Polygon(const Polygon& polygon);
		Polygon(std::vector<Point> points, sf::Color color);
		Polygon(Point point1, Point point2, Point point3, sf::Color color);

		void setPoints(std::vector<Point> points);
		void setPoints(Point point1, Point point2, Point point3);
		void setColor(sf::Color color);
		void setModel(Model* model);

		//Есть ли вообще такая точка в полигоне
		bool checkExistencePoint(const Point& point);

		std::vector<Point> getPoints() const;
		sf::Color getColor() const;
		Model* getModel() const;
		std::vector<Point> getConvertedPoints();
		~Polygon();
	};
}
