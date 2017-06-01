#include "TDRenderWindow.h"
#include <iostream>
#include <windows.h>
#define KEK std::cout<<"KEK\n"
namespace tdrw {
	void threadSetCoord(ThreadHelper * h_thread_helper, Camera * camera){
		std::unique_lock<std::mutex> t_unique_lock(h_thread_helper->m_mutex);

		while (!h_thread_helper->m_thread_set_coord_done) {
			h_thread_helper->m_thread_set_coord_is_work = false;
			h_thread_helper->m_cv_for_coord.wait(t_unique_lock);
			h_thread_helper->m_thread_set_coord_is_work = true;
			if (h_thread_helper->m_thread_set_coord_done) {
				h_thread_helper->m_thread_set_coord_is_work = false;
				break;
			}
			//Блокируем доступ к очереди моделей и вытаскиваем первые элемент. Доступ после открывается
			//=========
			while (h_thread_helper->m_models.size() != 0) {
				while (!h_thread_helper->m_mutex_deque_models.try_lock()) {}
				if (h_thread_helper->m_models.size() == 0) {
					h_thread_helper->m_mutex_deque_models.unlock();
					h_thread_helper->m_thread_set_coord_is_work = false;
					continue;
				}

				Model t_model = h_thread_helper->m_models.front();
				h_thread_helper->m_models.pop_front();

				h_thread_helper->m_mutex_deque_models.unlock();
				//==========
				std::vector<Point*> t_all_points = t_model.getAllPoints();
				sf::Vector2f check_vect;
				for (auto x : t_all_points) {
					x->setCoordOnScreen(camera->getCoordOnScreen(t_model.convertToWorldCoordSystem(*x)));
				}
			}
		}
	}

	void TDRenderWindow::drawModelsSystemCoord(const Model& model){
		CoordinateSystem t_coord_system = model.getCoordSystem();
		Point t_zero = t_coord_system.getZeroPoint();

		sf::VertexArray * t_line;

		//x axis == red
		t_line = new sf::VertexArray(sf::Lines, 2);
		(*t_line)[0].position = camera.getCoordOnScreen(t_zero);
		(*t_line)[1].position = camera.getCoordOnScreen(model.convertToWorldCoordSystem(Point(5, 0, 0)));
		(*t_line)[0].color = sf::Color::Red;
		(*t_line)[1].color = sf::Color::Red;
		sf::RenderWindow::draw(*t_line);
		delete t_line;

		//y axis == blue
		t_line = new sf::VertexArray(sf::Lines, 2);
		(*t_line)[0].position = camera.getCoordOnScreen(t_zero);
		(*t_line)[1].position = camera.getCoordOnScreen(model.convertToWorldCoordSystem(Point(0, 5, 0)));
		(*t_line)[0].color = sf::Color::Blue;
		(*t_line)[1].color = sf::Color::Blue;
		sf::RenderWindow::draw(*t_line);
		delete t_line;

		//z axis == yellow
		t_line = new sf::VertexArray(sf::Lines, 2);
		(*t_line)[0].position = camera.getCoordOnScreen(t_zero);
		(*t_line)[1].position = camera.getCoordOnScreen(model.convertToWorldCoordSystem(Point(0, 0, 5)));
		(*t_line)[0].color = sf::Color::Yellow;
		(*t_line)[1].color = sf::Color::Yellow;
		sf::RenderWindow::draw(*t_line);
		delete t_line;
	}

	void TDRenderWindow::draw_polygon(BinTree* tmp) {
		std::vector<Point*> t_points = tmp->polygon.getPoints();
		sf::VertexArray* polygon_to_draw = new sf::VertexArray(sf::TrianglesFan, t_points.size());
		sf::VertexArray* line = new sf::VertexArray(sf::LinesStrip, t_points.size()*2);
		sf::Color t_color_to_gradient = tmp->polygon.getColor();
		sf::Color pol_color = m_light.getTransformColor(tmp->polygon);

		int j = 0;

		//вначале идём к самым дальним полигонам
		if (tmp->further != nullptr) {
			draw_polygon(tmp->further);
		}

		/*std::cout << "=================\n";
		std::cout << "(" << points[0].x << "," << points[0].y << "," << points[0].z << ")" << std::endl;
		std::cout << "(" << points[1].x << "," << points[1].y << "," << points[1].z << ")" << std::endl;
		std::cout << "(" << points[2].x << "," << points[2].y << "," << points[2].z << ")" << std::endl;*/
		//как только рекурсивно дошли до самого дальнего, начинаем отрисовывать активный(послученный в виде аргумента) полигон
		if (m_color_exist) {
			sf::Vector2f check_vect;
			for (int i = 0; i < t_points.size(); ++i) {
				check_vect = t_points[i]->getCoordOnScreen();
				//std::cout << "(" << check_vect.x << ", " << check_vect.y << ")\n";
				(*polygon_to_draw)[i].position = check_vect;
			}
			if (m_gradient_color_is_on) {
				for (int i = 0; i < t_points.size(); ++i) {
					(*polygon_to_draw)[i].color = m_light.getTransformColor(*t_points[i], t_color_to_gradient);
				}
			}
			else {
				for (int i = 0; i < t_points.size(); ++i) {
					(*polygon_to_draw)[i].color = pol_color;
				}
			}
			sf::RenderWindow::draw(*polygon_to_draw);
		}


		j = 0;
		if (m_frame_exist) {
			for (int i = 0; i < t_points.size() * 2; i += 2) {
				(*line)[i].position = t_points[j % t_points.size()]->getCoordOnScreen();
				(*line)[i + 1].position = t_points[(j + 1) % t_points.size()]->getCoordOnScreen();
				j++;
			}
			for (int i = 0; i < t_points.size() * 2; ++i)
				(*line)[i].color = sf::Color::Red;
			sf::RenderWindow::draw(*line);
		}
		//потом к ближайшем
		if (tmp->closer != nullptr) {
			draw_polygon(tmp->closer);
		}

		delete line;
		delete polygon_to_draw;
		return;
	}

	TDRenderWindow::TDRenderWindow() {
		bsp_tree = nullptr;
		m_frame_exist = true;
		m_color_exist = true;
		m_gradient_color_is_on = false;
		m_wrong_side_is_on = true;
		m_draw_models_system_coord_is_on = true;
		m_thread_helper.m_thread_set_coord_done = false;
		m_thread_helper.m_thread_set_coord_is_work = true;
		m_thread_set_coord = new std::thread(threadSetCoord, &m_thread_helper, &camera);
	}

	TDRenderWindow::TDRenderWindow(sf::VideoMode video_mode, std::string title) {

		m_thread_helper.m_thread_set_coord_done = false;
		m_thread_helper.m_thread_set_coord_is_work = true;
		m_thread_set_coord = new std::thread(threadSetCoord, &m_thread_helper, &camera);

		m_frame_exist = true;
		m_color_exist = true;
		m_gradient_color_is_on = false;
		m_wrong_side_is_on = true;
		m_draw_models_system_coord_is_on = true;

		bsp_tree = nullptr;
		sf::RenderWindow::create(video_mode, title);
	}


	void TDRenderWindow::setCamera(const Camera& camera) {
		camera_exist = true;
		this->camera = camera;
		this->camera.setScreenSize(sf::RenderWindow::getSize());
		if (world_exist) {
			this->camera.setWorldCoordSystem(this->world_coord_system);
			this->camera.setScreenSize(sf::RenderWindow::getSize());
			this->camera.generateConvertNumber();
		}
	}

	void TDRenderWindow::setLight(const Light & light){
		m_light = light;
	}

	void TDRenderWindow::setWorldCoordSystem(const CoordinateSystem& world_coord_system) {
		this->world_exist = true;
		this->world_coord_system = world_coord_system;
		if (camera_exist) {
			this->camera.setWorldCoordSystem(this->world_coord_system);
			this->camera.setScreenSize(sf::RenderWindow::getSize());
			this->camera.generateConvertNumber();
		}
	}

	void TDRenderWindow::activeFrame(bool frame){
		m_frame_exist = frame;
	}

	void TDRenderWindow::activeColor(bool color){
		m_color_exist = color;
	}

	void TDRenderWindow::activeGradient(bool gradient){
		m_gradient_color_is_on = gradient;
	}

	void TDRenderWindow::activeWrongSide(bool switcher){
		m_wrong_side_is_on = switcher;
	}

	void TDRenderWindow::activeDrawModelsCS(bool switcher){
		m_draw_models_system_coord_is_on = switcher;
	}

	void TDRenderWindow::draw(Model model) {
		if (m_gradient_color_is_on) {
			std::vector<Point*> t_points = model.getAllPoints();
			for (auto x : t_points) {
				x->clearNormal();
			}
			model.generateNormalInPoints();
		}

		std::thread *t_bsp_thread, *t_coord_thread;
		model.setWorldCoordSystem(world_coord_system);
		models.push_back(model);

		while(!m_thread_helper.m_mutex_deque_models.try_lock()){}
		m_thread_helper.m_models.push_back(model);
		m_thread_helper.m_mutex_deque_models.unlock();
		m_thread_helper.m_cv_for_coord.notify_all();

		//TODO
		//Посылать модель в отдельный поток для выставления координат точек на экране
	}

	void TDRenderWindow::clear(sf::Color color) {
		models.clear();
		delete bsp_tree;
		bsp_tree = nullptr;

		sf::RenderWindow::clear(color);
	}

	void TDRenderWindow::display() {
		//ЗАПОЛНЯЕМ BSP TREE
		std::vector<Polygon> polygons;
		std::vector<Polygon> tmp_data;

		for (int i = 0; i < models.size(); ++i) {
			//tmp_data.clear();
			tmp_data = models[i].getAllPolygon();
			polygons.insert(polygons.end(), tmp_data.begin(), tmp_data.end());
		}

		//std::cout << "Create bsp tree... ";
		//QueryPerformanceFrequency((LARGE_INTEGER *)&m_tps);
		//QueryPerformanceCounter((LARGE_INTEGER *)&m_start);

		bsp_tree = new BinaryTree;
		bsp_tree->setCamera(camera);
		bsp_tree->activeWrongSide(m_wrong_side_is_on);
		bsp_tree->setZeroPointOfCamera(this->camera.getZeroPointOfCamera());
		for (int i = 0; i < polygons.size(); ++i) {
			bsp_tree->addElement(polygons[i]);
		}

		//QueryPerformanceCounter((LARGE_INTEGER *)&m_end);
		//std::cout << ((double)(m_end - m_start) / m_tps) * 1000. << " miliseconds\n";


		//std::cout << "Wait find coord... ";
		//ОТРИСОВЫВАЕМ
		while (m_thread_helper.m_thread_set_coord_is_work) {}//ожидаем окончания работы потока

		//std::cout << "Draw all polygons... ";

		BinTree * t_tmp_tree = bsp_tree->getBinaryTree();
		if(t_tmp_tree != nullptr)
			draw_polygon(t_tmp_tree);

		if (m_draw_models_system_coord_is_on) {
			for (auto x : models)
				drawModelsSystemCoord(x);
		}
		sf::RenderWindow::display();

		//QueryPerformanceCounter((LARGE_INTEGER *)&m_end);
		//std::cout << ((double)(m_end - m_start) / m_tps) * 1000. << " miliseconds\n";
	}

	Camera TDRenderWindow::getCamera(){
		return camera;
	}

	CoordinateSystem TDRenderWindow::getWorldCoordSystem(){
		return world_coord_system;
	}

	Point * TDRenderWindow::getPointToControl(sf::Vector2f coord_on_screen){
		bool t_fisrt_scan_done = false;
		double t_min_distance;
		double t_tmp_distance;
		Point* t_suitable_point = nullptr;
		std::vector<Point*> t_tmp_points;

		Point t_zero_point_of_camera = camera.getZeroPointOfCamera();
		for (auto x : models) {
			t_tmp_points = x.getPoint(coord_on_screen);
			for (auto y : t_tmp_points) {
				t_tmp_distance = Point::calcDistance(t_zero_point_of_camera, x.convertToWorldCoordSystem(*y));
				if (!t_fisrt_scan_done) {
					t_fisrt_scan_done = true;
					t_min_distance = t_tmp_distance;
					t_suitable_point = y;
				}

				if (t_min_distance > t_tmp_distance) {
					t_min_distance = t_tmp_distance;
					t_suitable_point = y;
				}
			}
			t_tmp_points.clear();
		}

		return t_suitable_point;
	}

	Polygon * TDRenderWindow::getPolygonToControl(sf::Vector2f coord_on_screen){
		bool t_fisrt_scan_done = false;
		double t_min_distance;
		double t_tmp_distance;
		Polygon * t_suitable_polygon = nullptr;
		std::vector<Polygon*> t_tmp_polygons;
		std::vector<Point*> t_tmp_points;

		Point t_zero_point_of_camera = camera.getZeroPointOfCamera();
		for (auto x : models) {
			t_tmp_polygons = x.getSuitablePolygons(coord_on_screen);
			for (auto y : t_tmp_polygons) {
				//высчитываем среднее растояние до полигона
				t_tmp_points = y->getPoints();
				t_tmp_distance = 0;
				for (auto z : t_tmp_points) {
					t_tmp_distance += Point::calcDistance(t_zero_point_of_camera, x.convertToWorldCoordSystem(*z));
				}
				t_tmp_distance = t_tmp_distance / t_tmp_points.size();
				t_tmp_points.clear();

				//проверяем на минимум
				if (!t_fisrt_scan_done) {
					t_fisrt_scan_done = true;
					t_min_distance = t_tmp_distance;
					t_suitable_polygon = y;
				}

				if (t_min_distance > t_tmp_distance) {
					t_min_distance = t_tmp_distance;
					t_suitable_polygon = y;
				}
			}
			t_tmp_polygons.clear();
		}

		return t_suitable_polygon;
	}


	TDRenderWindow::~TDRenderWindow(){
		m_thread_helper.m_thread_set_coord_done = true;
		m_thread_helper.m_cv_for_coord.notify_all();
		m_thread_set_coord->join();
	}

	ThreadHelper::ThreadHelper(){
		m_thread_set_coord_done = true;
		m_thread_set_coord_is_work = false;
	}

	ThreadHelper::~ThreadHelper()
	{
	}
} 