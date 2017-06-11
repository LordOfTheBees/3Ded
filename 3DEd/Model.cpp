#include "Model.h"
#include <iostream>
#include <fstream>

#define KEK std::cout<<"KEK\n"

namespace tdrw {
	void Model::operator=(const Model & right){
		if (this != &right) {
			this->m_polygons.clear();
			this->m_own_coord_system = right.m_own_coord_system;
			setAllPoints(right.getAllPoints());
			for (int i = 0; i < right.m_polygons.size(); ++i)
				this->m_polygons.push_back(right.m_polygons[i]);
		}
	}

	Model::Model() {
	}

	Model::Model(const Model & right) : ArrayOfPoints(right){
		this->m_polygons.clear();
		this->m_own_coord_system = right.m_own_coord_system;
		setAllPoints(right.getAllPoints());
		for (int i = 0; i < right.m_polygons.size(); ++i)
			this->m_polygons.push_back(right.m_polygons[i]);
	}

	void Model::setModelCoordSystem(const CoordinateSystem& model_coord_system) {
		this->m_own_coord_system = model_coord_system;
	}

	void Model::setWorldCoordSystem(const CoordinateSystem& world_coord_system) {
		this->m_own_coord_system.setBasisCoordSystem(world_coord_system);
	}

	//==============

	void Model::addPolygon(Polygon polygon){
		Polygon * t_polygon = new Polygon(polygon);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(std::vector<Point*> points, sf::Color color){
		Polygon * t_polygon = new Polygon(this, points, color);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(Point * point1, Point * point2, Point * point3, sf::Color color){
		Polygon * t_polygon = new Polygon(this, point1, point2, point3, color);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(Point point1, Point point2, Point point3, sf::Color color) {
		std::vector<Point*> t_tmp_points;
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point1));
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point2));
		t_tmp_points.push_back(ArrayOfPoints::addPoint(point3));

		Polygon * t_polygon = new Polygon(this, t_tmp_points, color);
		m_polygons.push_back(t_polygon);
	}

	void Model::addPolygon(std::vector<Point> points, sf::Color color) {
		std::vector<Point*> t_tmp_points;
		
		for (auto& x : points) {
			t_tmp_points.push_back(ArrayOfPoints::addPoint(x));
		}

		Polygon * t_polygon = new Polygon(this, t_tmp_points, color);
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

	CoordinateSystem Model::getCoordSystem() const {
		return m_own_coord_system;
	}

	std::vector<Polygon> Model::getAllPolygon() const {
		std::vector<Polygon> t_tmp_polygon;
		for (auto x : m_polygons) {
			t_tmp_polygon.push_back(*x);
		}
		return t_tmp_polygon;
	}

	std::vector<Polygon*> Model::getAllPtrPolygon(){
		return m_polygons;
	}

	std::vector<Polygon*> Model::getSuitablePolygons(sf::Vector2f coord_on_screen){
		std::vector<Polygon*> t_tmp_polygons;
		t_tmp_polygons.clear();

		for (auto x : m_polygons) {
			if (x->hitTesting(coord_on_screen)) {
				t_tmp_polygons.push_back(x);
			}
		}

		return t_tmp_polygons;
	}

	Point Model::convertToWorldCoordSystem(const Point& point) const {
		return m_own_coord_system.convertToBasis(point);
	}

	void Model::generateNormalInPoints(){
		std::vector<double> t_tmp_normal;
		std::vector<Point*> t_tmp_points;
		for (auto x : m_polygons) {
			t_tmp_normal = x->getNormal();
			t_tmp_points = x->getPoints();
			for (auto y : t_tmp_points) {
				y->addNormal(t_tmp_normal);
			}
		}
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
		if (!file.is_open()) {
			return false;
		}
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
		file.close();
		return true;
	}

	bool Model::save(const std::string file_path){
		std::ofstream file(file_path, std::ofstream::trunc);
		if (!file.is_open()) {
			throw new std::exception("Failed to save to file");
		}

		std::string t_str;

		std::vector<Point*> t_points = getAllPoints();
		for (auto x : t_points) {
			t_str.clear();
			t_str += "v ";
			t_str += x->convertCoordToString();
			t_str += "\n";
			file << t_str;
		}

		for (auto x : m_polygons) {
			t_str.clear();
			t_str += "f ";
			t_str += x->getStringWithData();
			t_str += "\n";
			file << t_str;
		}
		file.close();
		return true;
	}

	void Model::optimization(){
		ArrayOfPoints::deleteUnusablePoints();
	}

	Model::~Model() {
	}
}