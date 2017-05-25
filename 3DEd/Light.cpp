#include "Light.h"

#include <cmath>
namespace tdrw {
	Light::Light()
	{
	}


	void Light::setDirection(const CoordinateSystem & coord_system){
		m_direction = coord_system;
	}

	void Light::setZeroPoint(const Point & point){
		m_direction.setZeroPointOfCoord(point);
	}

	sf::Color Light::getTransformColor(const Polygon & polygon){
		std::vector<Point> points = polygon.getConvertedPoints();

		Point M0 = points[0];
		Point M1 = points[1];
		Point M2 = points[2];

		std::vector<double> t_dir = m_direction.getZAxis();
		double coefficient[3];
		coefficient[0] = -M0.y*(M2.z - M1.z) + M1.y*(M2.z - M0.z) - M2.y*(M1.z - M0.z);
		coefficient[1] = M0.z*(M1.x - M2.x) - M1.z*(M0.x - M2.x) + M2.z*(M0.x - M1.x);
		coefficient[2] = M0.x*(M1.y - M2.y) - M1.x*(M0.y - M2.y) + M2.x*(M0.y - M1.y);

		double alpha = (t_dir[0] * coefficient[0] + t_dir[1] * coefficient[1] + t_dir[2] * coefficient[2]) /
			(std::sqrt(std::pow(t_dir[0], 2) + std::pow(t_dir[1], 2) + std::pow(t_dir[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

		alpha *= -1;
		alpha += 1;
		alpha = alpha * 50 / 100;
		alpha = alpha * alpha;

		m_hsb.transferToHSB(polygon.getColor());
		m_hsb.brightness *= alpha;

		return m_hsb.getRGB();
	}


	Light::~Light()
	{
	}
}
