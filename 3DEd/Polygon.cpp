#include "Polygon.h"
#include "Model.h"
#include <iostream>
namespace tdrw {
	bool operator==(const Polygon & left, const Polygon & right) {
		if (left.points.size() == right.points.size()) {
			for (int i = 0; i < right.points.size(); ++i)
				if (left.points[i] != right.points[i])
					return false;
			return true;
		}
		return false;
	}

	Polygon & Polygon::operator=(const Polygon & right) {
		if (this == &right)
			return *this;
		this->m_him_model = right.m_him_model;
		this->points = right.points;
		this->color = right.color;
		return *this;
	}

	Polygon::Polygon() {
		m_him_model = nullptr;
		color = sf::Color::White;
	}

	Polygon::Polygon(const Polygon & polygon) {
		this->m_him_model = polygon.m_him_model;
		this->points = polygon.points;
		this->color = polygon.color;
	}

	Polygon::Polygon(std::vector<Point> points, sf::Color color) {
		this->points = points;
		this->color = color;
	}

	Polygon::Polygon(Point point1, Point point2, Point point3, sf::Color color) {
		this->points.push_back(point1);
		this->points.push_back(point2);
		this->points.push_back(point3);

		this->color = color;
	}

	void Polygon::setPoints(std::vector<Point> points) {
		this->points = points;
	}

	void Polygon::setPoints(Point point1, Point point2, Point point3) {
		this->points.push_back(point1);
		this->points.push_back(point2);
		this->points.push_back(point3);
	}

	void Polygon::setColor(sf::Color color) {
		this->color = color;
	}

	void Polygon::setModel(Model * model){
		m_him_model = model;
		m_him_model->getAllPolygon();
	}

	//Есть ли вообще такая точка в полигоне
	bool Polygon::checkExistencePoint(const Point & point) {
		for (auto it = points.begin(); it != points.end(); it++)
			if (*it == point)
				return true;
		return false;
	}

	std::vector<Point> Polygon::getPoints() const { return points; }

	sf::Color Polygon::getColor() const{
		return color;
	}

	Model * Polygon::getModel() const{
		return m_him_model;
	}

	std::vector<Point> Polygon::getConvertedPoints(){
		CoordinateSystem i_cs = m_him_model->getCoordSystem();
		std::vector<Point> tmp;
		for (int i = 0; i < points.size(); ++i) {
			tmp.push_back(i_cs.convertToBasis(points[i]));
		}
		return tmp;
	}


	Polygon::~Polygon() {
	}
}