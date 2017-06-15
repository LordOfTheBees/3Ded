#include "Camera.h"
#include <iostream>

namespace tdrw {
	Camera::Camera() {
	}

	Camera::Camera(const Camera & right){
		m_screen_size = right.m_screen_size;
		m_coord_system_of_camera = right.m_coord_system_of_camera;
		m_world_coord_system = right.m_world_coord_system;
		m_viewing_angle = right.m_viewing_angle;
		m_convert_number_x = right.m_convert_number_x;
		m_convert_number_y = right.m_convert_number_y;
		m_radius = right.m_radius;
	}

	void Camera::setDataOfCamera(const CoordinateSystem & world_system, const CoordinateSystem & camera_system, const double & m_viewing_angle, const sf::Vector2u m_screen_size) {
		m_world_coord_system = world_system;
		m_coord_system_of_camera = camera_system;
		this->m_viewing_angle = m_viewing_angle;
		this->m_screen_size = m_screen_size;

		generateConvertNumber();
	}

	void Camera::setWorldCoordSystem(const CoordinateSystem & world_system) {
		m_world_coord_system = world_system;
	}

	void Camera::setCameraCoordSystem(const CoordinateSystem & camera_system) {
		m_coord_system_of_camera = camera_system;
	}

	void Camera::setViewingAngle(const double & m_viewing_angle) {
		this->m_viewing_angle = m_viewing_angle;
	}

	void Camera::setScreenSize(const sf::Vector2u m_screen_size) {
		this->m_screen_size = m_screen_size;
		this->m_screen_size.x *= 1;
		this->m_screen_size.y *= 1;
	}

	void Camera::generateConvertNumber() {
		double pi = 3.14159265;
		m_coord_system_of_camera.setBasisCoordSystem(m_world_coord_system);
		m_world_coord_system.setBasisCoordSystem(m_coord_system_of_camera);
		m_radius = (m_screen_size.x) / (std::pow(std::tan(m_viewing_angle * pi / (2 * 180)), 1.0 / 3.0));
	}

	void Camera::rotationAngleOnX(double alpha){
		m_coord_system_of_camera.rotationAngleOnX(alpha);
	}

	void Camera::rotationAngleOnY(double alpha){
		m_coord_system_of_camera.rotationAngleOnY(alpha);
	}

	void Camera::rotationAngleOnZ(double alpha){
		m_coord_system_of_camera.rotationAngleOnZ(alpha);
	}

	void Camera::setZeroPointOfCoord(const Point & zero_point){
		m_coord_system_of_camera.setZeroPointOfCoord(zero_point);
		m_coord_system_of_camera.setBasisCoordSystem(m_world_coord_system);
	}

	std::vector<double> Camera::getDirectionOfGaze() const{
		return m_coord_system_of_camera.getZAxis();
	}

	std::vector<Point> Camera::getConvertedPoints(const Polygon & polygon)
	{
		std::vector<Point*> t_points = polygon.getPoints();
		std::vector<Point> t_converted_points;
		for (int i = 0; i < t_points.size(); ++i) {
			t_converted_points.push_back(m_world_coord_system.convertToBasis(*t_points[i]));
		}
		return t_converted_points;
	}

	sf::Vector2f Camera::getCoordOnScreen(const Point& point_in_world_cs) {
		Point converted_point = m_world_coord_system.convertToBasis(point_in_world_cs);
		//Вся эта дичь работает на основе подобных треуголников 
		//Находим коэф. подобных треугольников с помощью гипотенуз(m_radius/...) а потом умножаем на координату x(or y), чтобы найти ,какая она будет на экране
		return sf::Vector2f(m_screen_size.x / 2 - 2 * ((m_radius) / (std::sqrt(converted_point.z * converted_point.z + converted_point.x * converted_point.x)))*converted_point.x,
			m_screen_size.y / 2 - 2 * ((m_radius) / (std::sqrt(converted_point.z * converted_point.z + converted_point.y * converted_point.y)))*converted_point.y);
		/*return sf::Vector2f(m_screen_size.x / 2 + 100 * converted_point.x / converted_point.z,
							m_screen_size.y / 2 + 100 * converted_point.y / converted_point.z)*/;
	}

	Point Camera::convertToWoorldSystem(const Point & point_in_camera_system){
		return m_coord_system_of_camera.convertToBasis(point_in_camera_system);
	}

	Point Camera::getZeroPointOfCamera() {
		Point point_zero = m_coord_system_of_camera.getZeroPoint();
		return point_zero;
	}

	CoordinateSystem Camera::getCoordSystemOfCamera()
	{
		return m_world_coord_system;
	}

	Camera::~Camera()
	{
	}
}
//Привязка к Up(к потолку) или Down(к полу). То есть будет автоматическая генерация координатной системы. Параллельность и соноправленность(угол меньше 90)
//УГол обзора (горизонтальные), который позволяет высчитать точку через которую проводить проекцию
//Позже релизовать вертикальный угол обзора. То есть разобрать работу объектива у камеры
//Вектор который указывает куда направлена камера(z-ось) 