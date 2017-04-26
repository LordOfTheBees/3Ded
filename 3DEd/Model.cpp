#include "Model.h"
#include <iostream>
namespace tdrw {
	void Model::operator=(const Model & right) {
		if (this != &right) {
			this->points.clear();
			this->polygons.clear();
			this->own_coord_system = right.own_coord_system;
			for (int i = 0; i < right.points.size(); ++i)
				this->points.push_back(right.points[i]);

			for (int i = 0; i < right.polygons.size(); ++i)
				this->polygons.push_back(right.polygons[i]);
		}
	}

	Model::Model() {
	}

	Model::Model(const Model & right) {
		this->points.clear();
		this->polygons.clear();
		this->own_coord_system = right.own_coord_system;
		for (int i = 0; i < right.points.size(); ++i)
			this->points.push_back(right.points[i]);

		for (int i = 0; i < right.polygons.size(); ++i)
			this->polygons.push_back(right.polygons[i]);
	}

	void Model::setModelCoordSystem(const CoordinateSystem& model_coord_system) {
		this->own_coord_system = model_coord_system;
	}

	void Model::setWorldCoordSystem(const CoordinateSystem& world_coord_system) {
		this->own_coord_system.setBasisCoordSystem(world_coord_system);
		this->own_coord_system.generateTransitionMatrix();
	}

	void Model::addPolygon(Polygon polygon) {
		polygon.setModel(this);
		polygons.push_back(polygon);
		std::vector<Point> got_points = polygon.getPoints();
		this->points.insert(points.end(), got_points.begin(), got_points.end());
	}

	void Model::rotationAngleOnX(double alpha) {
		own_coord_system.rotationAngleOnX(alpha);
	}

	void Model::rotationAngleOnY(double alpha) {
		own_coord_system.rotationAngleOnY(alpha);
	}

	void Model::rotationAngleOnZ(double alpha) {
		own_coord_system.rotationAngleOnZ(alpha);
	}

	void Model::setZeroPointOfCoord(const Point & zero_point) {
		own_coord_system.setZeroPointOfCoord(zero_point);
	}

	CoordinateSystem Model::getCoordSystem() {
		return own_coord_system;
	}

	Point Model::getPoint(const sf::Vector2i mouse_coord) const {
		for (int i = 0; i < this->points.size(); ++i) {
			if (points[i].mousePositionEqualWithCoordPoint(mouse_coord)) {
				return points[i];
			}
		}
		return Point();
	}

	std::vector<Point> Model::getAllPoints() const {
		return points;
	}

	std::vector<Polygon> Model::getAllPolygon() const {
		return polygons;
	}

	Point Model::convertToWorldCoordSystem(const Point& point) const {
		return own_coord_system.convertToBasis(point);
	}


	bool Model::deletePoint(Point * point) {
		/*for (auto it = polygons.begin(); it != polygons.end(); ++it) {
			if (it->checkExistencePoint(*point)) {
				it = polygons.erase(it);
				it--;
			}
		}*/
		return false;
	}

	Model::~Model() {
	}
}