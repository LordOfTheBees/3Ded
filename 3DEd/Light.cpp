#include "Light.h"

#include <cmath>
namespace tdrw {
	Light::Light()
	{
	}


	void Light::setDirection(const CoordinateSystem & coord_system){
		m_direction = coord_system;
		m_direction_z = coord_system.getZAxis();
	}

	void Light::setZeroPoint(const Point & point){
		m_direction.setZeroPointOfCoord(point);
	}

	sf::Color Light::getTransformColor(const Polygon & polygon){
		std::vector<double> coefficient = polygon.getNormal();

		double alpha = (m_direction_z[0] * coefficient[0] + m_direction_z[1] * coefficient[1] + m_direction_z[2] * coefficient[2]) /
			(std::sqrt(std::pow(m_direction_z[0], 2) + std::pow(m_direction_z[1], 2) + std::pow(m_direction_z[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

		alpha *= -1;
		alpha += 1;
		alpha = alpha * 50 / 100;
		alpha = alpha * alpha;

		m_hsb.transferToHSB(polygon.getColor());
		m_hsb.brightness *= alpha;

		return m_hsb.getRGB();
	}

	sf::Color Light::getTransformColor(const Point & point, sf::Color color)
	{
		std::vector<double> coefficient = point.getNormal();

		double alpha = (m_direction_z[0] * coefficient[0] + m_direction_z[1] * coefficient[1] + m_direction_z[2] * coefficient[2]) /
			(std::sqrt(std::pow(m_direction_z[0], 2) + std::pow(m_direction_z[1], 2) + std::pow(m_direction_z[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

		alpha *= -1;
		alpha += 1;
		alpha = alpha * 50 / 100;
		alpha = std::pow(alpha, 3);

		m_hsb.transferToHSB(color);
		m_hsb.brightness *= alpha;

		return m_hsb.getRGB();
	}


	Light::~Light()
	{
	}
}
