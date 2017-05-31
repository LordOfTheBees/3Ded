#include "Polygon.h"
#include "Model.h"
#include <iostream>
namespace tdrw {
	bool operator==(const Polygon & left, const Polygon & right) {
		if (left.m_points.size() == right.m_points.size()) {
			for (int i = 0; i < right.m_points.size(); ++i)
				if (left.m_points[i] != right.m_points[i])
					return false;
			return true;
		}
		return false;
	}

	double Polygon::square(std::vector<Point> points) {
		double a = Point::calcDistanceInWindow(points[0], points[1]);
		double b = Point::calcDistanceInWindow(points[1], points[2]);
		double c = Point::calcDistanceInWindow(points[2], points[0]);
		double p = (a + b + c) / 2;
		return std::sqrt(p*(p - a)*(p - b)*(p - c));
	}

	Polygon & Polygon::operator=(const Polygon & right) {
		if (this == &right)
			return *this;
		m_him_model = right.m_him_model;
		m_points = right.m_points;
		m_points_after_splitted = right.m_points_after_splitted;
		m_color = right.m_color;
		return *this;
	}

	Polygon::Polygon(Model * model) {
		m_points_after_splitted.clear();
		m_him_model = model;
		m_color = sf::Color::White;
	}

	Polygon::Polygon(const Polygon & right) {
		m_him_model = right.m_him_model;
		m_points = right.m_points;
		m_points_after_splitted = right.m_points_after_splitted;
		m_color = right.m_color;
	}

	Polygon::Polygon(Model * model, std::vector<Point*> points, sf::Color color) {
		this->m_him_model = model;
		this->m_points = points;
		this->m_color = color;

		m_points_after_splitted.clear();
	}

	Polygon::Polygon(Model * model, Point * point1, Point * point2, Point * point3, sf::Color color) {
		this->m_him_model = model;
		this->m_points.push_back(point1);
		this->m_points.push_back(point2);
		this->m_points.push_back(point3);

		this->m_color = color;
		m_points_after_splitted.clear();
	}

	void Polygon::setPoints(std::vector<Point*> points) {
		this->m_points = points;
	}

	void Polygon::setPoints(Point * point1, Point * point2, Point * point3) {
		this->m_points.push_back(point1);
		this->m_points.push_back(point2);
		this->m_points.push_back(point3);
	}

	void Polygon::setColor(sf::Color color) {
		this->m_color = color;
	}


	bool Polygon::wasSplitted() const{
		if (m_points_after_splitted.size() != 0)
			return true;
		return false;
	}

	//≈сть ли вообще така€ точка в полигоне
	bool Polygon::checkExistencePoint(const Point * point) {
		for (auto it = m_points.begin(); it != m_points.end(); it++)
			if (*it == point)
				return true;
		return false;
	}

	bool Polygon::hitTesting(sf::Vector2f coord_on_screen) {
		Point t_point_with_coord(0, 0, 0);
		t_point_with_coord.setCoordOnScreen(coord_on_screen);

		double t_square = 0;
		double t_sum_of_square = 0;

		std::vector<Point> t_points;
		for (auto x : m_points)
			t_points.push_back(*x);

		t_square = square(t_points);

		std::vector<Point> t_points_for_square;
		//теперь считаем суммы площадей тругольников с вершиной в нашей точке

		for (int i = 0; i < t_points.size(); ++i) {
			t_points_for_square.push_back(t_points[i]);
			t_points_for_square.push_back(t_points[(i+1)%t_points.size()]);
			t_points_for_square.push_back(t_point_with_coord);

			t_sum_of_square += square(t_points_for_square);

			t_points_for_square.clear();
		}

		if (std::abs(t_sum_of_square - t_square) < 0.01)
			return true;
		return false;
	}

	std::vector<Polygon> Polygon::dividePolygon(const Polygon & splitter) const{
		//ЅЋяяяяяяяяяяяяяяяяяя
		//ќЎ»Ѕ ј «ƒ≈—№
		//Ё“ќ ѕ»«ƒ≈÷
		//TODO
		//»справить ошибку

		std::vector<double> t_n_s = splitter.getNormal();//t_normal_splitter

		double t_side, t_side_active, t_side_previos;//this arg will keep the location of the point(front of or behind the splitter or on the splitter)
		Polygon t_first(m_him_model);//signbit() == true
		Polygon t_second(m_him_model);//signbit() == false

		Point t_previous_point(0,0,0);
		
		double t_delta_x;
		double t_delta_y;
		double t_delta_z;
		double t_labda;
		Point t_splitted_point;
		std::vector<Point> t_zero_points;

		bool t_this_first_iteration = true;
		bool t_previous_side = false;//true - t_first // false - t_second

		//перезапписываем точки в другой вектор. “.к. в m_points может не быть точек, как и наоборот
		std::vector<Point> t_points;
		if (m_points_after_splitted.size() != 0) {
			for (auto x : m_points_after_splitted)
				t_points.push_back(x);
		}
		else {
			for (auto x : m_points)
				t_points.push_back(*x);
		}


		for (auto x : t_points) {
			t_side = x.x * t_n_s[0] + x.y * t_n_s[1] + x.z * t_n_s[2] + t_n_s[3];

			if (t_side == 0) {
				t_zero_points.push_back(x);
				t_previous_point = x;
				continue;
			}

			switch (std::signbit(t_side)){
			//==========================================
			case true: {
				//¬Ќачале проверка на первую итерацию, чтобы с чего-то начать
				if (t_this_first_iteration) {
					for (auto y : t_zero_points) {
						t_first.m_points_after_splitted.push_back(y);
					}
					t_zero_points.clear();

					t_this_first_iteration = false;
					t_previous_side = true;
					t_first.m_points_after_splitted.push_back(x);
					break;
				}

				//првоерка на zero points
				else if (t_zero_points.size() != 0) {
					if (t_previous_side) {
						for (auto y : t_zero_points) {
							t_first.m_points_after_splitted.push_back(y);
						}
						t_zero_points.clear();

						t_previous_side = true;
						t_first.m_points_after_splitted.push_back(x);
					}
					else {
						for (auto y : t_zero_points) {
							t_first.m_points_after_splitted.push_back(y);
							t_second.m_points_after_splitted.push_back(y);
						}
						t_zero_points.clear();

						t_previous_side = true;
						t_first.m_points_after_splitted.push_back(x);
					}
				}
				//проверка на переход точки на другу сторону
				//осталась на той же стороне
				else if (t_previous_side) { 
					t_previous_side = true;
					t_first.m_points_after_splitted.push_back(x);
				}
				//перешла на другую сторону
				else {
					t_previous_side = true;//т.к. последн€€ запись будет на другой стороне

					//находим точку, котора€ находитс€ на пр€мой и плоскости, котора€ эту пр€мую раздел€ет
					t_delta_x = t_previous_point.x - x.x;
					t_delta_y = t_previous_point.y - x.y;
					t_delta_z = t_previous_point.z - x.z;
					t_labda = (-x.x - x.y - x.z - t_n_s[3]) /
							  (t_delta_x * t_n_s[0] + t_delta_y * t_n_s[1] + t_delta_z * t_n_s[2]);

					t_splitted_point.setCoord(x.x + t_delta_x*t_labda,
											  x.y + t_delta_y*t_labda,
											  x.z + t_delta_z*t_labda);

					t_first.m_points_after_splitted.push_back(t_splitted_point);
					t_second.m_points_after_splitted.push_back(t_splitted_point);
					t_first.m_points_after_splitted.push_back(x);
				}

				break;
			}

			//==========================================
			case false: {
				if (t_this_first_iteration) {
					for (auto y : t_zero_points) {
						t_second.m_points_after_splitted.push_back(y);
					}
					t_zero_points.clear();

					t_this_first_iteration = false;
					t_previous_side = false;
					t_second.m_points_after_splitted.push_back(x);
					break;
				}

				//првоерка на zero points
				else if (t_zero_points.size() != 0) {
					if (!t_previous_side) {
						for (auto y : t_zero_points) {
							t_second.m_points_after_splitted.push_back(y);
						}
						t_zero_points.clear();

						t_previous_side = false;
						t_second.m_points_after_splitted.push_back(x);
					}
					else {
						for (auto y : t_zero_points) {
							t_first.m_points_after_splitted.push_back(y);
							t_second.m_points_after_splitted.push_back(y);
						}
						t_zero_points.clear();

						t_previous_side = false;
						t_second.m_points_after_splitted.push_back(x);
					}
				}
				//проверка на переход точки на другу сторону
				//осталась на той же стороне
				else if (!t_previous_side) {
					t_previous_side = false;
					t_second.m_points_after_splitted.push_back(x);
				}
				//перешла на другую сторону
				else {
					t_previous_side = false;//т.к. последн€€ запись будет на другой стороне

											//находим точку, котора€ находитс€ на пр€мой и плоскости, котора€ эту пр€мую раздел€ет
					t_delta_x = t_previous_point.x - x.x;
					t_delta_y = t_previous_point.y - x.y;
					t_delta_z = t_previous_point.z - x.z;
					t_labda = (-x.x - x.y - x.z - t_n_s[3]) /
						(t_delta_x * t_n_s[0] + t_delta_y * t_n_s[1] + t_delta_z * t_n_s[2]);

					t_splitted_point.setCoord(x.x + t_delta_x*t_labda,
						x.y + t_delta_y*t_labda,
						x.z + t_delta_z*t_labda);

					t_first.m_points_after_splitted.push_back(t_splitted_point);
					t_second.m_points_after_splitted.push_back(t_splitted_point);
					t_second.m_points_after_splitted.push_back(x);
				}

				break;
			}

			default:
				break;
			}
			t_previous_point = x;
		}

		//ƒобавл€ем последнюю точку в последний работающий вектор t_previous_side
		auto x = t_points[0];
		t_side = x.x * t_n_s[0] + x.y * t_n_s[1] + x.z * t_n_s[2] + t_n_s[3];

		if (t_side == 0) {
			if (t_previous_side) {
				t_first.m_points_after_splitted.push_back(x);
			}
			else {
				t_second.m_points_after_splitted.push_back(x);
			}
		}
		else if(std::signbit(t_side) != t_previous_side){
			//находим точку, котора€ находитс€ на пр€мой и плоскости, котора€ эту пр€мую раздел€ет
			t_delta_x = t_previous_point.x - x.x;
			t_delta_y = t_previous_point.y - x.y;
			t_delta_z = t_previous_point.z - x.z;
			t_labda = (-x.x - x.y - x.z - t_n_s[3]) /
					  (t_delta_x * t_n_s[0] + t_delta_y * t_n_s[1] + t_delta_z * t_n_s[2]);

			t_splitted_point.setCoord(x.x + t_delta_x*t_labda,
									  x.y + t_delta_y*t_labda,
									  x.z + t_delta_z*t_labda);

			t_first.m_points_after_splitted.push_back(t_splitted_point);
			t_second.m_points_after_splitted.push_back(t_splitted_point);
		}

		std::vector<Polygon> t_ready_polygon;
		if (t_first.m_points_after_splitted.size() >= 3) {
			t_first.setColor(m_color);
			t_ready_polygon.push_back(t_first);
		}
		if (t_second.m_points_after_splitted.size() >= 3) {
			t_second.setColor(m_color);
			t_ready_polygon.push_back(t_second);
		}

		return t_ready_polygon;
	}

	std::vector<Point*> Polygon::getPoints() const { return m_points; }

	std::vector<Point> Polygon::getPointsAfterSplitted(){
		std::vector<Point> t_tmp_points = m_points_after_splitted;
		m_points_after_splitted.clear();
		return t_tmp_points;
	}

	std::vector<double> Polygon::getNormal() const{
		std::vector<Point> t_converted_points = getConvertedPoints();

		std::vector<double> t_normal(4);
		t_normal[0] = -t_converted_points[0].y*(t_converted_points[2].z - t_converted_points[1].z) + t_converted_points[1].y*(t_converted_points[2].z - t_converted_points[0].z) - t_converted_points[2].y*(t_converted_points[1].z - t_converted_points[0].z);
		t_normal[1] = t_converted_points[0].z*(t_converted_points[1].x - t_converted_points[2].x) - t_converted_points[1].z*(t_converted_points[0].x - t_converted_points[2].x) + t_converted_points[2].z*(t_converted_points[0].x - t_converted_points[1].x);
		t_normal[2] = t_converted_points[0].x*(t_converted_points[1].y - t_converted_points[2].y) - t_converted_points[1].x*(t_converted_points[0].y - t_converted_points[2].y) + t_converted_points[2].x*(t_converted_points[0].y - t_converted_points[1].y);
		t_normal[3] = -t_converted_points[0].x*t_normal[0] - t_converted_points[0].y*t_normal[1] - t_converted_points[0].z*t_normal[2];
		return t_normal;
	}

	sf::Color Polygon::getColor() const{
		return m_color;
	}

	Model * Polygon::getModel() const{
		return m_him_model;
	}

	std::vector<Point> Polygon::getConvertedPoints() const{
		CoordinateSystem t_cs = m_him_model->getCoordSystem();
		std::vector<Point> t_tmp;
		if (m_points_after_splitted.size() != 0) {
			for (auto x : m_points_after_splitted) {
				t_tmp.push_back(t_cs.convertToBasis(x));
			}
		}
		else {
			for (auto x : m_points) {
				t_tmp.push_back(t_cs.convertToBasis(*x));
			}
		}
		return t_tmp;
	}


	Polygon::~Polygon() {
	}
}