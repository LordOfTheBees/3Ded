#include "Point.h"
#include "CoordinateSystem.h"
#include "Polygon.h"

#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#pragma once
class Model
{
private:
	CoordinateSystem own_coord_system;
	std::vector<Polygon> polygons;
	std::vector<Point> points;
protected:
public:
	void operator=(const Model& right);

	Model();
	Model(const Model& right);

	void setModelCoordSystem(const CoordinateSystem& model_coord_system);
	void setWorldCoordSystem(const CoordinateSystem& world_coord_system);
	void addPolygon(Polygon polygon);

	Point getPoint(const sf::Vector2i mouse_coord) const;
	std::vector<Point> getAllPoints() const;
	std::vector<Polygon> getAllPolygon() const;

	Point convertToWorldCoordSystem(const Point& point);

	bool deletePoint(Point* point);
	~Model();
};

