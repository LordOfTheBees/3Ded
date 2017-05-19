#include "Polygon.h"
#include "Model.h"
#include <iostream>
namespace tdrw {
	bool operator==(const Polygon & left, const Polygon & right) {
		if (left.m_points.size() == right.m_points.size()) {
			for (int i = 0; i < right.m_points.size(); ++i)
				if (left.m_points[i] != right.m_points[i])
					return false;
			return true;
		}
		return false;
	}

	Polygon & Polygon::operator=(const Polygon & right) {
		if (this == &right)
			return *this;
		this->m_him_model = right.m_him_model;
		this->m_points = right.m_points;
		this->m_color = right.m_color;
		return *this;
	}

	Polygon::Polygon(Model * model) {
		m_him_model = model;
		m_color = sf::Color::White;
	}

	Polygon::Polygon(const Polygon & polygon) {
		this->m_him_model = polygon.m_him_model;
		this->m_points = polygon.m_points;
		this->m_color = polygon.m_color;
	}

	Polygon::Polygon(Model * model, std::vector<Point*> points, sf::Color color) {
		this->m_him_model = model;
		this->m_points = points;
		this->m_color = color;
	}

	Polygon::Polygon(Model * model, Point * point1, Point * point2, Point * point3, sf::Color color) {
		this->m_him_model = model;
		this->m_points.push_back(point1);
		this->m_points.push_back(point2);
		this->m_points.push_back(point3);

		this->m_color = color;
	}

	void Polygon::setPoints(std::vector<Point*> points) {
		this->m_points = points;
	}

	void Polygon::setPoints(Point * point1, Point * point2, Point * point3) {
		this->m_points.push_back(point1);
		this->m_points.push_back(point2);
		this->m_points.push_back(point3);
	}

	void Polygon::setColor(sf::Color color) {
		this->m_color = color;
	}

	//Есть ли вообще такая точка в полигоне
	bool Polygon::checkExistencePoint(const Point * point) {
		for (auto it = m_points.begin(); it != m_points.end(); it++)
			if (*it == point)
				return true;
		return false;
	}

	std::vector<Point*> Polygon::getPoints() const { return m_points; }

	sf::Color Polygon::getColor() const{
		return m_color;
	}

	Model * Polygon::getModel() const{
		return m_him_model;
	}

	std::vector<Point> Polygon::getConvertedPoints(){
		CoordinateSystem t_cs = m_him_model->getCoordSystem();
		std::vector<Point> t_tmp;
		for (int i = 0; i < m_points.size(); ++i) {
			t_tmp.push_back(t_cs.convertToBasis(*m_points[i]));
		}
		return t_tmp;
	}


	Polygon::~Polygon() {
	}
}