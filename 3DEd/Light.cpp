#include "Light.h"

#include <cmath>
namespace tdrw {
	Light::Light(){
		m_light_type = point;
	}

	void Light::activeSurfaceType(const CoordinateSystem & coord_system){
		m_light_type = surface;
		m_direction_z = coord_system.getZAxis();
	}

	void Light::activePointType(const Point& zero_point){
		m_light_type = point;
		m_zero_point = zero_point;
	}

	sf::Color Light::getTransformColor(const Polygon & polygon){
		std::vector<double> coefficient = polygon.getNormal();

		std::vector<double> t_result_vector(3, 0);
		std::vector<double> t_tmp_vector(3, 0);
		std::vector<Point> t_points = polygon.getConvertedPoints();
		double alpha;

		switch (m_light_type)
		{
		case surface: {
			alpha = (m_direction_z[0] * coefficient[0] + m_direction_z[1] * coefficient[1] + m_direction_z[2] * coefficient[2]) /
				(std::sqrt(std::pow(m_direction_z[0], 2) + std::pow(m_direction_z[1], 2) + std::pow(m_direction_z[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

			alpha *= -1;
			alpha += 1;
			alpha = alpha * 50 / 100;
			alpha = alpha * alpha;

			m_hsb.transferToHSB(polygon.getColor());
			m_hsb.brightness *= alpha;

			return m_hsb.getRGB();
		}

		case point: {
			for (auto x : t_points) {
				t_tmp_vector = { x.x - m_zero_point.x, x.y - m_zero_point.y, x.z - m_zero_point.z };
				for (int i = 0; i < 3; ++i) {
					t_result_vector[i] += t_tmp_vector[i];
				}
				t_tmp_vector.clear();
			}

			alpha = (t_result_vector[0] * coefficient[0] + t_result_vector[1] * coefficient[1] + t_result_vector[2] * coefficient[2]) /
				(std::sqrt(std::pow(t_result_vector[0], 2) + std::pow(t_result_vector[1], 2) + std::pow(t_result_vector[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

			alpha *= -1;
			alpha += 1;
			alpha = alpha * 50 / 100;
			alpha = alpha * alpha;

			m_hsb.transferToHSB(polygon.getColor());
			m_hsb.brightness *= alpha;

			return m_hsb.getRGB();

		}
		default:
			break;
		}
	}

	sf::Color Light::getTransformColor(const Point & main_point, sf::Color color)
	{
		std::vector<double> coefficient = main_point.getNormal();

		std::vector<double> t_result_vector(3, 0);
		double alpha;

		switch (m_light_type)
		{
		case surface: {
			alpha = (m_direction_z[0] * coefficient[0] + m_direction_z[1] * coefficient[1] + m_direction_z[2] * coefficient[2]) /
				(std::sqrt(std::pow(m_direction_z[0], 2) + std::pow(m_direction_z[1], 2) + std::pow(m_direction_z[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

			alpha *= -1;
			alpha += 1;
			alpha = alpha * 50 / 100;
			alpha = alpha * alpha;

			m_hsb.transferToHSB(color);
			m_hsb.brightness *= alpha;

			return m_hsb.getRGB();
		}

		case point: {
			t_result_vector = { main_point.x - m_zero_point.x, main_point.y - m_zero_point.y, main_point.z - m_zero_point.z };

			alpha = (t_result_vector[0] * coefficient[0] + t_result_vector[1] * coefficient[1] + t_result_vector[2] * coefficient[2]) /
				(std::sqrt(std::pow(t_result_vector[0], 2) + std::pow(t_result_vector[1], 2) + std::pow(t_result_vector[2], 2))*std::sqrt(std::pow(coefficient[0], 2) + std::pow(coefficient[1], 2) + std::pow(coefficient[2], 2)));

			alpha *= -1;
			alpha += 1;
			alpha = alpha * 50 / 100;
			alpha = alpha * alpha;

			m_hsb.transferToHSB(color);
			m_hsb.brightness *= alpha;

			return m_hsb.getRGB();

		}
		default:
			break;
		}
	}


	Light::~Light()
	{
	}
}
