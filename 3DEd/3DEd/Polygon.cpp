#include "Polygon.h"
#include <iostream>
bool operator==(const Polygon & left, const Polygon & right){
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
	this->points = right.points;
	this->color = right.color;
	return *this;
}

Polygon::Polygon(){
	color = sf::Color::White;
}

Polygon::Polygon(const Polygon & polygon){
	this->points = polygon.points;
	this->color = polygon.color;
}

Polygon::Polygon(std::vector<Point> points, sf::Color color){
	this->points = points;
	this->color = color;
}

Polygon::Polygon(Point point1, Point point2, Point point3, sf::Color color){
	this->points.push_back(point1);
	this->points.push_back(point2);
	this->points.push_back(point3);

	this->color = color;
}

void Polygon::setPoints(std::vector<Point> points){
	this->points = points;
}

void Polygon::setPoints(Point point1, Point point2, Point point3){
	this->points.push_back(point1);
	this->points.push_back(point2);
	this->points.push_back(point3);
}

void Polygon::setColor(sf::Color color){
	this->color = color;
}

//Есть ли вообще такая точка в полигоне
bool Polygon::checkExistencePoint(const Point & point){
	for (auto it = points.begin(); it != points.end(); it++)
		if (*it == point)
			return true;

	return false;
}

std::vector<Point> Polygon::getPoints() const { return points; }


Polygon::~Polygon(){
}
