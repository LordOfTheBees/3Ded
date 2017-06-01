#include "Point.h"
#include <sstream>

namespace tdrw {
	bool operator!=(const Point & left, const Point & right) {
		return ((right.x != left.x) || (left.y != right.y) || (left.z != right.z));
	}

	bool operator==(const Point & left, const Point & right) {
		return ((right.x == left.x) && (left.y == right.y) && (left.z == right.z));
	}

	const Point operator+(const Point& left, const Point& right) {
		return Point(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	const Point operator-(const Point& left, const Point& right) {
		return Point(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	double Point::calcDistanceInWindow(const Point & first, const Point & second){
		return std::sqrt(std::pow(first.coord_on_screen.x - second.coord_on_screen.x, 2) + std::pow(first.coord_on_screen.y - second.coord_on_screen.y, 2));
	}

	double Point::calcDistance(const Point & first, const Point & second) {
		return std::sqrt(std::pow(first.x - second.x, 2) + std::pow(first.y - second.y, 2) + std::pow(first.z - second.z, 2));
	}

	Point & Point::operator=(const Point & right) {
		if (this == &right)
			return *this;
		this->x = right.x;
		this->y = right.y;
		this->z = right.z;
		this->existance = true;
		this->coord_on_screen = right.coord_on_screen;
		return *this;
	}

	Point::Point() {
		coord_on_screen.x = -300;
		coord_on_screen.y = -300;
		existance = false;
		m_normal_exist = false;
	}

	Point::Point(const Point & _point) {
		x = _point.x;
		y = _point.y;
		z = _point.z;
		existance = true;
		m_normal_exist = false;
		this->coord_on_screen = _point.coord_on_screen;
	}

	Point::Point(std::vector<double> coord) {
		x = coord[0];
		y = coord[1];
		z = coord[2];
		m_normal_exist = false;
	}

	Point::Point(float x, float y, float z) {
		coord_on_screen.x = -300;
		coord_on_screen.y = -300;
		this->x = x;
		this->y = y;
		this->z = z;
		this->existance = true;
		m_normal_exist = false;
	}

	void Point::setCoord(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		existance = true;
	}

	void Point::setCoord(const Point & _point) {
		x = _point.x;
		y = _point.y;
		z = _point.z;
		existance = true;
		this->coord_on_screen = _point.coord_on_screen;
	}

	void Point::setCoord(std::vector<double> coord) {
		x = coord[0];
		y = coord[1];
		z = coord[2];
	}

	void Point::setCoordOnScreen(const sf::Vector2f & coord_on_screen) {
		this->coord_on_screen = coord_on_screen;
	}

	bool Point::isExist() const {
		return existance;
	}

	bool Point::checkPointByCoordOnScreen(const sf::Vector2f & mouse_position) const {
		/*if ((mouse_position.x - 2 < this->coord_on_screen.x) && (this->coord_on_screen.x < mouse_position.x + 2) &&
			(mouse_position.y - 2 < this->coord_on_screen.y) && (this->coord_on_screen.y < mouse_position.y + 2))
			return true;*/

		if ((std::pow(mouse_position.x - coord_on_screen.x, 2) + std::pow(mouse_position.y - coord_on_screen.y, 2)) <= 16)
			return true;
		return false;
	}

	std::string Point::convertCoordToString() const{
		std::ostringstream t_ostr;

		t_ostr << x;
		t_ostr << ' ';
		t_ostr << y;
		t_ostr << ' ';
		t_ostr << z;
		
		return t_ostr.str();
	}

	//(x, y, z)
	std::vector<double> Point::getCoord() const {
		std::vector<double> coord;
		coord.push_back(x);
		coord.push_back(y);
		coord.push_back(z);
		return coord;
	}

	void Point::addNormal(std::vector<double> normal) {
		double t_length = std::sqrt(std::pow(normal[0], 2) + std::pow(normal[1], 2) + std::pow(normal[2], 2));
		for (int i = 0; i < normal.size(); ++i) {
			normal[i] = normal[i] / t_length;
		}

		if (!m_normal_exist) {
			m_normal = normal;
			m_normal_exist = true;
		}
		else {
			for (int i = 0; i < m_normal.size(); ++i) {
				m_normal[i] = m_normal[i] + normal[i];
			}
		}
	}

	std::vector<double> Point::getNormal() const{
		if (m_normal_exist)
			return m_normal;
		return std::vector<double>(3,0);
	}

	void Point::clearNormal(){
		m_normal_exist = false;
		m_normal.clear();
	}

	sf::Vector2f Point::getCoordOnScreen() const{
		return coord_on_screen;
	}


	Point::~Point() {
	}

}