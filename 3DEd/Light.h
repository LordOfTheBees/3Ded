#include "CoordinateSystem.h"
#include "Point.h"
#include "Polygon.h"
#include "HSB.h"

#include <SFML\Graphics\Color.hpp>
#pragma once
namespace tdrw {
	class Light
	{
	private:
		HSB m_hsb;
		std::vector<double> m_direction_z;
		Point m_zero_point;

		enum{surface, point} m_light_type;
	public:
		Light();

		void activeSurfaceType(const CoordinateSystem & coord_system);//requires only z axis and ZeroPoint
		void activePointType(const Point& point);

		sf::Color getTransformColor(const Polygon& polygon);
		sf::Color getTransformColor(const Point& point, sf::Color color);

		~Light();
	};
}

