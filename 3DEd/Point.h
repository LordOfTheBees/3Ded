#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#pragma once
namespace tdrw {
	class Point
	{
	private:
		sf::Vector2f coord_on_screen;
		bool existance;
	protected:
	public:
		double x, y, z;

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

		bool isExist() const;
		bool isUsed() const;
		bool checkPointByCoordOnScreen(const sf::Vector2f& mouse_position) const;

		//(x, y, z)
		std::vector<double> getCoord() const;

		sf::Vector2f getCoordOnScreen() const;

		~Point();
	};
}
