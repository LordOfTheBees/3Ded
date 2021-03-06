#include "ArrayOfPoints.h"

#include <iostream>
#include <algorithm>
namespace tdrw {
	void ArrayOfPoints::operator=(const ArrayOfPoints & right) {
		m_all_points = right.m_all_points;
	}

	Point* ArrayOfPoints::operator[](int number) {
		return m_all_points[number];
	}

	ArrayOfPoints::ArrayOfPoints() {
	}

	ArrayOfPoints::ArrayOfPoints(const ArrayOfPoints & right) {
		m_all_points = right.m_all_points;
	}

	Point * ArrayOfPoints::addPoint(const Point point) {
		m_all_points.push_back(new Point(point));
		return m_all_points.back();
	}

	void ArrayOfPoints::setAllPoints(const std::vector<Point*> points){
		m_all_points = points;
	}

	void ArrayOfPoints::erasePoint(int number) {
		if ((number >= m_all_points.size()) || (number < 0))
			throw new std::exception("ArrayOfPoints::erasePoint: wrong number(the selected number exceeds the number of points or it is negative)");
		std::vector<Point*>::iterator t_it = m_all_points.begin() + number;
		m_all_points.erase(t_it);
	}

	void ArrayOfPoints::erasePoint(Point * point) {
		for (auto it = m_all_points.begin(); it != m_all_points.end(); ++it) {
			if (*it == point) {
				m_all_points.erase(it);
				return;
			}
		}

		throw new std::exception("ArrayOfPoints::erasePoint: This ptr point does not exist.");
	}

	int ArrayOfPoints::getNumOfElement(Point * point) {
		for (int i = 0; i < m_all_points.size(); ++i) {
			if (m_all_points[i] == point)
				return i;
		}
		return -1;
	}

	Point * ArrayOfPoints::getPtrPoint(int number) {
		if ((number >= m_all_points.size()) || (number < 0))
			throw new std::exception("ArrayOfPoints::erasePoint: wrong number(the selected number exceeds the number of points or it is negative)");
		return m_all_points[number];
	}

	int ArrayOfPoints::size() {
		return m_all_points.size();
	}

	std::vector<Point*> ArrayOfPoints::getPoint(const sf::Vector2f coord_of_point) {
		std::vector<Point*> t_points;
		t_points.clear();

		for (auto& x : m_all_points) {
			if (x->checkPointByCoordOnScreen(coord_of_point)) {
				t_points.push_back(x);
			}
		}

		return t_points;
	}

	std::vector<Point*> ArrayOfPoints::getAllPoints() const {
		return m_all_points;
	}

	std::vector<Point*> ArrayOfPoints::getUnusablePoints() const{
		return m_unusable_points;
	}

	bool ArrayOfPoints::fillVectorWithUnusablePoints() {
		m_unusable_points.clear();
		bool check = false;
		for (auto x : m_all_points) {
			if (!x->isUsed()) {
				m_unusable_points.push_back(x);
				check = true;
			}
		}
		return check;
	}


	void ArrayOfPoints::deleteUnusablePoints() {
		Point * t_point = nullptr;
		for (auto it = m_all_points.begin(); it != m_all_points.end(); ++it) {
			while (!(*it)->isUsed()) {
				t_point = *it;
				it = m_all_points.erase(it);

				delete t_point;
				if (it == m_all_points.end())
					break;
			}
		}

		m_unusable_points.clear();
	}

	ArrayOfPoints::~ArrayOfPoints(){
	}

}