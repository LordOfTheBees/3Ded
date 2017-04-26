#include "CoordinateSystem.h"
#include <cmath>
#include <vector>
#include "Point.h"
#include "Polygon.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#pragma once
namespace tdrw {
	class Camera {
	private:
		sf::Vector2u screen_size;
		CoordinateSystem coord_system_of_camera;
		CoordinateSystem world_coord_system;
		double viewing_angle;//угол обзора
		double convert_number_x;//постоянная для нахождения x на экране монитора
		double convert_number_y;//постоянная для нахождения y на экране монитора
		double radius;
	protected:
	public:
		Camera();
		void setDataOfCamera(const CoordinateSystem& world_system, const CoordinateSystem& camera_system, const double& viewing_angle, const sf::Vector2u screen_size);
		void setWorldCoordSystem(const CoordinateSystem& world_system);
		void setCameraCoordSystem(const CoordinateSystem& camera_system);
		void setViewingAngle(const double& viewing_angle);
		void setScreenSize(const sf::Vector2u screen_size);
		void generateConvertNumber();

		std::vector<Point> getConvertedPoints(const Polygon& polygon);
		sf::Vector2f getCoordOnScreen(Point& point_in_world_cs);
		Point getZeroPointOfCamera();
		CoordinateSystem getCoordSystemOfCamera();
		~Camera();
	};
}
