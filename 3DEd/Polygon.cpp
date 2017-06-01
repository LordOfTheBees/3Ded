#include "Polygon.h"
#include "Model.h"

#include <iostream>
#include <sstream>
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

	double Polygon::square(std::vector<Point> points) {
		double a = Point::calcDistanceInWindow(points[0], points[1]);
		double b = Point::calcDistanceInWindow(points[1], points[2]);
		double c = Point::calcDistanceInWindow(points[2], points[0]);
		double p = (a + b + c) / 2;
		return std::sqrt(p*(p - a)*(p - b)*(p - c));
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

	std::string Polygon::getStringWithData() const{
		std::ostringstream t_ostr;

		int t_found_num;

		for (auto x : m_points) {
			t_found_num = m_him_model->getNumOfElement(x);
			if (t_found_num == -1)
				throw new std::exception("polygon with a non-existent point");
			t_ostr << t_found_num + 1;
			t_ostr << ' ';
		}

		return t_ostr.str();
	}


	//Есть ли вообще такая точка в полигоне
	bool Polygon::checkExistencePoint(const Point * point) {
		for (auto it = m_points.begin(); it != m_points.end(); it++)
			if (*it == point)
				return true;
		return false;
	}

	bool Polygon::hitTesting(sf::Vector2f coord_on_screen) {
		Point t_point_with_coord(0, 0, 0);
		t_point_with_coord.setCoordOnScreen(coord_on_screen);

		double t_square = 0;
		double t_sum_of_square = 0;

		std::vector<Point> t_points;
		for (auto x : m_points)
			t_points.push_back(*x);

		t_square = square(t_points);

		std::vector<Point> t_points_for_square;
		//теперь считаем суммы площадей тругольников с вершиной в нашей точке

		for (int i = 0; i < t_points.size(); ++i) {
			t_points_for_square.push_back(t_points[i]);
			t_points_for_square.push_back(t_points[(i+1)%t_points.size()]);
			t_points_for_square.push_back(t_point_with_coord);

			t_sum_of_square += square(t_points_for_square);

			t_points_for_square.clear();
		}

		if (std::abs(t_sum_of_square - t_square) < 0.01)
			return true;
		return false;
	}

	std::vector<Point*> Polygon::getPoints() const { return m_points; }

	std::vector<double> Polygon::getNormal() const{
		std::vector<Point> t_converted_points = getConvertedPoints();

		std::vector<double> t_normal(4);
		t_normal[0] = -t_converted_points[0].y*(t_converted_points[2].z - t_converted_points[1].z) + t_converted_points[1].y*(t_converted_points[2].z - t_converted_points[0].z) - t_converted_points[2].y*(t_converted_points[1].z - t_converted_points[0].z);
		t_normal[1] = t_converted_points[0].z*(t_converted_points[1].x - t_converted_points[2].x) - t_converted_points[1].z*(t_converted_points[0].x - t_converted_points[2].x) + t_converted_points[2].z*(t_converted_points[0].x - t_converted_points[1].x);
		t_normal[2] = t_converted_points[0].x*(t_converted_points[1].y - t_converted_points[2].y) - t_converted_points[1].x*(t_converted_points[0].y - t_converted_points[2].y) + t_converted_points[2].x*(t_converted_points[0].y - t_converted_points[1].y);
		t_normal[3] = -t_converted_points[0].x*t_normal[0] - t_converted_points[0].y*t_normal[1] - t_converted_points[0].z*t_normal[2];
		return t_normal;
	}

	sf::Color Polygon::getColor() const{
		return m_color;
	}

	Model * Polygon::getModel() const{
		return m_him_model;
	}

	std::vector<Point> Polygon::getConvertedPoints() const{
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