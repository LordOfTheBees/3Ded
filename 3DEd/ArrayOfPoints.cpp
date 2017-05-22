#include "ArrayOfPoints.h"


namespace tdrw {
	void ArrayOfPoints::operator=(const ArrayOfPoints & right){
		m_all_points = right.m_all_points;
	}

	Point* ArrayOfPoints::operator[](int number){
		return m_all_points[number];
	}

	ArrayOfPoints::ArrayOfPoints(){
	}

	ArrayOfPoints::ArrayOfPoints(const ArrayOfPoints & right){
		m_all_points = right.m_all_points;
	}

	Point * ArrayOfPoints::addPoint(const Point point){
		Point* t_ptr_point = new Point;
		*t_ptr_point = point;
		m_all_points.push_back(t_ptr_point);
		return m_all_points.back();
	}

	void ArrayOfPoints::erasePoint(int number){
		if (number >= m_all_points.size())
			return;
		std::vector<Point*>::iterator t_it = m_all_points.begin() + number;
		m_all_points.erase(t_it);
	}

	void ArrayOfPoints::erasePoint(Point * point){
		for (auto it = m_all_points.begin(); it != m_all_points.end(); ++it) {
			if (*it == point) {
				m_all_points.erase(it);
				return;
			}
		}
	}

	Point * ArrayOfPoints::getPtrPoint(int number){
		return m_all_points[number];
	}

	int ArrayOfPoints::size(){
		return m_all_points.size();
	}

	std::vector<Point*> ArrayOfPoints::getPoint(const sf::Vector2f coord_of_point){
		std::vector<Point*> t_points;

		for (auto& x : m_all_points) {
			if (x->checkPointByCoordOnScreen(coord_of_point)) {
				t_points.push_back(x);
			}
		}

		return t_points;
	}


	ArrayOfPoints::~ArrayOfPoints(){
	}

}