#include "Model.h"
#include <iostream>
namespace tdrw {
	void Model::operator=(const Model & right) {
		if (this != &right) {
			this->m_polygons.clear();
			this->m_own_coord_system = right.m_own_coord_system;

			for (int i = 0; i < right.m_polygons.size(); ++i)
				this->m_polygons.push_back(right.m_polygons[i]);
		}
	}

	Model::Model() {
	}

	Model::Model(const Model & right) {
		this->m_polygons.clear();
		this->m_own_coord_system = right.m_own_coord_system;

		for (int i = 0; i < right.m_polygons.size(); ++i)
			this->m_polygons.push_back(right.m_polygons[i]);
	}

	void Model::setModelCoordSystem(const CoordinateSystem& model_coord_system) {
		this->m_own_coord_system = model_coord_system;
	}

	void Model::setWorldCoordSystem(const CoordinateSystem& world_coord_system) {
		this->m_own_coord_system.setBasisCoordSystem(world_coord_system);
		this->m_own_coord_system.generateTransitionMatrix();
	}

	//==============

	void Model::addPolygon(Polygon polygon){
		m_polygons.push_back(polygon);
	}

	void Model::addPolygon(std::vector<Point*> points, sf::Color color){
		Polygon t_polygon(this, points, color);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(Point * point1, Point * point2, Point * point3, sf::Color color){
		Polygon t_polygon(this, point1, point2, point3, color);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(Point point1, Point point2, Point point3, sf::Color color) {
		std::vector<Point*> t_tmp_points;
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point1));
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point2));
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point3));

		Polygon t_polygon(this, t_tmp_points, color);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(std::vector<Point> points, sf::Color color) {
		std::vector<Point*> t_tmp_points;
		
		for (auto& x : points) {
			t_tmp_points.push_back(ArrayOfPoints::addPoint(x));
		}

		Polygon t_polygon(this, t_tmp_points, color);
		m_polygons.push_back(t_polygon);
	}

	//==============

	void Model::rotationAngleOnX(double alpha) {
		m_own_coord_system.rotationAngleOnX(alpha);
	}

	void Model::rotationAngleOnY(double alpha) {
		m_own_coord_system.rotationAngleOnY(alpha);
	}

	void Model::rotationAngleOnZ(double alpha) {
		m_own_coord_system.rotationAngleOnZ(alpha);
	}

	//==============

	void Model::setZeroPointOfCoord(const Point & zero_point) {
		m_own_coord_system.setZeroPointOfCoord(zero_point);
	}

	CoordinateSystem Model::getCoordSystem() {
		return m_own_coord_system;
	}

	Point* Model::getPoint(const sf::Vector2f mouse_coord){
		std::vector<Point*> t_points = ArrayOfPoints::getPoint(mouse_coord);
		//TODO
		//здесь нужно написать отбор ближайшей точки к центру экрана
		return t_points[0];
	}

	std::vector<Polygon> Model::getAllPolygon() const {
		return m_polygons;
	}

	Point Model::convertToWorldCoordSystem(const Point& point) const {
		return m_own_coord_system.convertToBasis(point);
	}


	Model::~Model() {
	}
}