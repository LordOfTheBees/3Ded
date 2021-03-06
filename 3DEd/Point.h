#include <vector>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#pragma once
namespace tdrw {
	class Point
	{
	private:
		sf::Vector2f m_coord_on_screen;
		std::vector<double> m_normal;
		bool m_normal_exist;
		bool m_is_active;

		unsigned int m_number_of_uses;
	protected:
	public:
		double x, y, z;

		static double calcDistanceInWindow(const Point& first, const Point& second);
		static double calcDistance(const Point& first, const Point& second);

		friend bool operator!=(const Point& left, const Point& right);
		friend bool operator==(const Point& left, const Point& right);
		friend const Point operator+(const Point& left, const Point& right);
		friend const Point operator-(const Point& left, const Point& right);

		Point& operator=(const Point& right);

		Point();
		Point(const Point& _point);
		Point(std::vector<double> coord);
		Point(float x, float y, float z);

		void setCoord(float x, float y, float z);
		void setCoord(const Point& _point);
		void setCoord(std::vector<double> coord);
		void setCoordOnScreen(const sf::Vector2f& coord_on_screen);
		void setActive(bool switcher);

		void upUseNumber(unsigned int num = 1);
		void downUseNumber(unsigned int num = 1);

		bool isActive() const;
		bool isUsed() const;
		bool checkPointByCoordOnScreen(const sf::Vector2f& mouse_position) const;

		//(x, y, z)
		std::string convertCoordToString() const;
		std::vector<double> getCoord() const;

		void addNormal(std::vector<double> normal);

		std::vector<double> getNormal() const;
		void clearNormal();
		sf::Vector2f getCoordOnScreen() const;

		~Point();
	};
}
