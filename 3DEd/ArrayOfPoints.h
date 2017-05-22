#include "Point.h"
#include <vector>

#define ull unsigned long long

#pragma once
namespace tdrw {
	class ArrayOfPoints
	{
	private:
		std::vector<Point*> m_all_points;
	protected:
	public:
		void operator=(const ArrayOfPoints& right);
		Point* operator[](int number);

		ArrayOfPoints();
		ArrayOfPoints(const ArrayOfPoints& right);

		//добавляет точку в контейнер без проверки на вхождение
		Point * addPoint(const Point point);

		void erasePoint(int number);
		void erasePoint(Point * point);

		Point* getPtrPoint(int number);
		int size();
		std::vector<Point*> getPoint(const sf::Vector2f coord_of_point);
		~ArrayOfPoints();
	};

}