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
		CoordinateSystem m_direction;
	public:
		Light();


		void setDirection(const CoordinateSystem& coord_system);//requires only z axis and ZeroPoint
		void setZeroPoint(const Point &point);

		sf::Color getTransformColor(const Polygon& polygon);


		~Light();
	};
}

