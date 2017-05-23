#include "Model.h"
#include <iostream>
#include <fstream>

#define KEK std::cout<<"KEK\n"

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
		m_polygons.push_back(Polygon(this, points, color));
	}

	void Model::addPolygon(Point * point1, Point * point2, Point * point3, sf::Color color){
		m_polygons.push_back(Polygon(this, point1, point2, point3, color));
	}

	void Model::addPolygon(Point point1, Point point2, Point point3, sf::Color color) {
		std::vector<Point*> t_tmp_points;
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point1));
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point2));
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point3));

		m_polygons.push_back(Polygon(this, t_tmp_points, color));
	}

	void Model::addPolygon(std::vector<Point> points, sf::Color color) {
		std::vector<Point*> t_tmp_points;
		
		for (auto& x : points) {
			t_tmp_points.push_back(ArrayOfPoints::addPoint(x));
		}

		m_polygons.push_back(Polygon(this, t_tmp_points, color));
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

	Data Model::separator(std::string str) {
		Data t_data;
		if ((str[0] == '#') || (str.size() == 0) || (str[0] == ' ')) {
			t_data.m_type.push_back('#');
			return t_data;
		}

		//считывает тип (первые символы до пробела)
		int i = 0;
		while (true) {
			if (str[i] == ' ')
				break;
			t_data.m_type.push_back(str[i]);
			++i;
		}
		//проходим на след символ после пробела
		++i;

		int t = 0;
		std::string t_tmp, t_tmp_str;
		//дальше идёт считывание данных в зависимоти от типа
		if (t_data.m_type == "v") {
			t_tmp.clear();

			for (i; i < str.size(); ++i) {
				if (str[i] == ' ') {
					t_data.m_coordinates.push_back(std::stof(t_tmp));
					t_tmp.clear();
				}
				else
					t_tmp.push_back(str[i]);
			}
			t_data.m_coordinates.push_back(std::stof(t_tmp));
			t_tmp.clear();
		}

		if (t_data.m_type == "f") {
			t = 0;
			t_tmp.clear();

			for (i; i < str.size(); ++i) {
				t_tmp_str.clear();
				while ((str[i] != ' ') && (i != str.size())) {
					t_tmp_str.push_back(str[i]);
					++i;
				}

				int j = 0;
				//После записи строки в t_tmp_str, вдираем оттуда числа
				//Считываем первое число. Вершины
				t_tmp.clear();
				while ((t_tmp_str[j] != '/') && (j < t_tmp_str.size())) {
					t_tmp.push_back(t_tmp_str[j]);
					j++;
				}
				if (t_tmp.size() != 0)
					t_data.m_vertices.push_back(std::stoi(t_tmp));
				if (j == t_tmp_str.size())
					continue;

				//Считываем второе число. Текстурные координаты
				t_tmp.clear();
				while ((t_tmp_str[j] != '/') && (j < t_tmp_str.size())) {
					t_tmp.push_back(t_tmp_str[j]);
					j++;
				}
				if(t_tmp.size() != 0)
					t_data.m_texture_coordinates.push_back(std::stoi(t_tmp));
				if (j == t_tmp_str.size())
					continue;

				//Считываем третье число. Нормаль
				t_tmp.clear();
				while ((t_tmp_str[j] != '/') && (j < t_tmp_str.size())) {
					t_tmp.push_back(t_tmp_str[j]);
					j++;
				}
				if (t_tmp.size() != 0)
					t_data.m_normal.push_back(std::stoi(t_tmp));
				if (j == t_tmp_str.size())
					continue;

			}
		}

		return t_data;
	}

	bool Model::load(const std::string file_path) {
		std::string t_str;
		std::ifstream file(file_path);
		Data t_data;

		while (std::getline(file, t_str)) {
			t_data = separator(t_str);
			if (t_data.m_type == "v") {
				addPoint(Point(t_data.m_coordinates));
			}

			if (t_data.m_type == "f") {
				std::vector<Point*> t_point;
				for (auto x : t_data.m_vertices) {
					t_point.push_back(getPtrPoint(x-1));
				}
				addPolygon(t_point, sf::Color::White);
			}
		}

		return true;
	}

	bool Model::save(const std::string file_path)
	{
		return true;
	}

	Model::~Model() {
	}
}