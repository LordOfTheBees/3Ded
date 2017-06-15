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
		return std::sqrt(std::pow(first.m_coord_on_screen.x - second.m_coord_on_screen.x, 2) + std::pow(first.m_coord_on_screen.y - second.m_coord_on_screen.y, 2));
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
		this->m_number_of_uses = right.m_number_of_uses;
		this->m_coord_on_screen = right.m_coord_on_screen;
		this->m_is_active = right.m_is_active;
		return *this;
	}

	Point::Point() {
		m_coord_on_screen.x = -300;
		m_coord_on_screen.y = -300;
		m_number_of_uses = 0;
		m_normal_exist = false;
		m_is_active = false;
	}

	Point::Point(const Point & _point) {
		x = _point.x;
		y = _point.y;
		z = _point.z;
		m_number_of_uses = _point.m_number_of_uses;
		m_normal_exist = false;
		this->m_coord_on_screen = _point.m_coord_on_screen;
		m_is_active = _point.m_is_active;
	}

	Point::Point(std::vector<double> coord) {
		m_coord_on_screen.x = -300;
		m_coord_on_screen.y = -300;
		x = coord[0];
		y = coord[1];
		z = coord[2];
		m_number_of_uses = 0;
		m_normal_exist = false;
		m_is_active = false;
	}

	Point::Point(float x, float y, float z) {
		m_coord_on_screen.x = -300;
		m_coord_on_screen.y = -300;
		this->x = x;
		this->y = y;
		this->z = z;
		m_number_of_uses = 0;
		m_normal_exist = false;
		m_is_active = false;
	}

	void Point::setCoord(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Point::setCoord(const Point & _point) {
		x = _point.x;
		y = _point.y;
		z = _point.z;
		this->m_coord_on_screen = _point.m_coord_on_screen;
	}

	void Point::setCoord(std::vector<double> coord) {
		x = coord[0];
		y = coord[1];
		z = coord[2];
	}

	void Point::setCoordOnScreen(const sf::Vector2f & m_coord_on_screen) {
		this->m_coord_on_screen = m_coord_on_screen;
	}

	void Point::setActive(bool switcher){
		m_is_active = switcher;
	}

	void Point::upUseNumber(unsigned int num){
		m_number_of_uses = +num;
	}

	void Point::downUseNumber(unsigned int num){
		m_number_of_uses -= num;
	}

	bool Point::isActive() const{
		return m_is_active;
	}

	bool Point::isUsed() const{
		if (m_number_of_uses > 0)
			return true;
		return false;
	}

	bool Point::checkPointByCoordOnScreen(const sf::Vector2f & mouse_position) const {
		if ((std::pow(mouse_position.x - m_coord_on_screen.x, 2) + std::pow(mouse_position.y - m_coord_on_screen.y, 2)) <= 25)
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
		return m_coord_on_screen;
	}


	Point::~Point() {
	}

}