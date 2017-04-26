#include "Point.h"


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
	}

	Point::Point(const Point & _point) {
		x = _point.x;
		y = _point.y;
		z = _point.z;
		existance = true;
		this->coord_on_screen = _point.coord_on_screen;
	}

	Point::Point(float x, float y, float z) {
		coord_on_screen.x = -300;
		coord_on_screen.y = -300;
		this->x = x;
		this->y = y;
		this->z = z;
		this->existance = true;
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

	void Point::setCoordOnScreen(const sf::Vector2f & coord_on_screen) {
		this->coord_on_screen = coord_on_screen;
	}

	bool Point::isExist() const {
		return existance;
	}

	bool Point::mousePositionEqualWithCoordPoint(const sf::Vector2i & mouse_position) const {
		if ((mouse_position.x - 2 < this->coord_on_screen.x) && (this->coord_on_screen.x < mouse_position.x + 2) &&
			(mouse_position.y - 2 < this->coord_on_screen.y) && (this->coord_on_screen.y < mouse_position.y + 2))
			return true;
		return false;
	}

	//(x, y, z)
	std::vector<double> Point::getCoord() const {
		std::vector<double> coord;
		coord.push_back(x);
		coord.push_back(y);
		coord.push_back(z);
		return coord;
	}


	Point::~Point() {
	}

}