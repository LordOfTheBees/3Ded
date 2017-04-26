#include "Camera.h"
#include <iostream>


Camera::Camera(){
}

void Camera::setDataOfCamera(const CoordinateSystem & world_system, const CoordinateSystem & camera_system, const double & viewing_angle, const sf::Vector2u screen_size){
	world_coord_system = world_system;
	coord_system_of_camera = camera_system;
	this->viewing_angle = viewing_angle;
	this->screen_size = screen_size;

	double pi = 3.14159265;
	coord_system_of_camera.setBasisCoordSystem(world_coord_system);
	coord_system_of_camera.generateTransitionMatrix();
	convert_number_x = 1 / (tan(viewing_angle * pi / (2 * 180)) * (screen_size.x / 2));
	convert_number_x = 1 / (tan(viewing_angle * pi / (2 * 180)) * (screen_size.y / 2));
}

void Camera::setWorldCoordSystem(const CoordinateSystem & world_system){
	world_coord_system = world_system;
}

void Camera::setCameraCoordSystem(const CoordinateSystem & camera_system){
	coord_system_of_camera = camera_system;
}

void Camera::setViewingAngle(const double & viewing_angle){
	this->viewing_angle = viewing_angle;
}

void Camera::setScreenSize(const sf::Vector2u screen_size){
	this->screen_size = screen_size;
}

void Camera::generateConvertNumber(){
	double pi = 3.14159265;
	world_coord_system.setBasisCoordSystem(coord_system_of_camera);
	world_coord_system.generateTransitionMatrix();
	convert_number_x = 200000 / (tan(viewing_angle * pi / (2 * 180)) * (screen_size.x / 2));
	convert_number_y = convert_number_x;
	radius = (screen_size.x / 2) / (std::tan(viewing_angle * pi / (2 * 180)));
	//convert_number_y = 1 / (tan(viewing_angle * pi / (2 * 180)) * (screen_size.y / 2));
	/*convert_number_x = 2;
	convert_number_y = 2;*/
}

std::vector<Point> Camera::getConvertedPoints(const Polygon & polygon)
{
	std::vector<Point> points = polygon.getPoints();
	std::vector<Point> converted_points;
	for (int i = 0; i < points.size(); ++i) {
		converted_points.push_back(world_coord_system.convertToBasis(points[i]));
	}
	return converted_points;
}

sf::Vector2f Camera::getCoordOnScreen(Point& point_in_world_cs){
	Point converted_point = world_coord_system.convertToBasis(point_in_world_cs);
	//����� �������� ���������� ������ ������� � ��������� ������ ��������� �� ������
	//� ����������� �������� �� z<0, ���� ��� ������
	//return sf::Vector2f(screen_size.x / 2 + 5*converted_point.x, screen_size.y / 2 + 5*converted_point.y);
	return sf::Vector2f( screen_size.x/2 + 2*((radius) / (std::sqrt(converted_point.z * converted_point.z + converted_point.x * converted_point.x)))*converted_point.x,
						 screen_size.y/2 + 2*((radius) / (std::sqrt(converted_point.z * converted_point.z + converted_point.y * converted_point.y)))*converted_point.y);

	//!!!!!return sf::Vector2f(screen_size.x / 2 + convert_number_x * converted_point.x / converted_point.z, screen_size.y / 2 + convert_number_y * converted_point.y / converted_point.z);
	//return sf::Vector2f(convert_number_x * converted_point.x / converted_point.z, convert_number_y * converted_point.y / converted_point.z);
}

Point Camera::getZeroPointOfCamera(){
	Point point_zero = coord_system_of_camera.getZeroPoint();
	return point_zero;
}



Camera::~Camera()
{
}
//�������� � Up(� �������) ��� Down(� ����). �� ���� ����� �������������� ��������� ������������ �������. �������������� � ����������������(���� ������ 90)
//���� ������ (��������������), ������� ��������� ��������� ����� ����� ������� ��������� ��������
//����� ���������� ������������ ���� ������. �� ���� ��������� ������ ��������� � ������
//������ ������� ��������� ���� ���������� ������(z-���) 