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
				KEK;
				std::vector<Point*> t_all_points = t_model.getAllPoints();
				std::cout << t_all_points.size() << std::endl;
				//std::cout << "(" << t_all_points[0]->x << ", " << t_all_points[0]->y << ", " << t_all_points[0]->z << ")\n";
				/*sf::Vector2f t_tmp_coord = camera->getCoordOnScreen(t_model.convertToWorldCoordSystem(Point(0, 0, 0)));
				std::cout << "Calculeted in draw (" << t_tmp_coord.x << ", " << t_tmp_coord.y << ")\n";*/
				for (auto x : t_all_points) {
					x->setCoordOnScreen(camera->getCoordOnScreen(t_model.convertToWorldCoordSystem(*x)));
				}
			}
		}
	}

	void TDRenderWindow::draw_polygon(BinTree* tmp) {
		while (m_thread_helper.m_thread_set_coord_is_work) {}//ожидаем окончания работы потока

		std::vector<Point*> t_points = tmp->polygon.getPoints();
		sf::VertexArray* polygon_to_draw = new sf::VertexArray(sf::Triangles, 3);
		sf::VertexArray* line = new sf::VertexArray(sf::Lines, 6);
		sf::Color pol_color = tmp->polygon.getColor();

		int j = 0;

		//вначале идём к самым дальним полигонам
		if (tmp->further != nullptr) {
			draw_polygon(tmp->further);
		}
		
		/*sf::Vector2f t_tmp_coord = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[0]));
		std::cout << "Calculeted in draw (" << t_tmp_coord.x << ", " << t_tmp_coord.y << ")\n";
		t_tmp_coord = t_points[0]->getCoordOnScreen();
		std::cout << "Calculeted in thread (" << t_tmp_coord.x << ", " << t_tmp_coord.y << ")\n\n";*/

		/*std::cout << "=================\n";
		std::cout << "(" << points[0].x << "," << points[0].y << "," << points[0].z << ")" << std::endl;
		std::cout << "(" << points[1].x << "," << points[1].y << "," << points[1].z << ")" << std::endl;
		std::cout << "(" << points[2].x << "," << points[2].y << "," << points[2].z << ")" << std::endl;*/
		//как только рекурсивно дошли до самого дальнего, начинаем отрисовывать активный(послученный в виде аргумента) полигон
		for (int i = 0; i < t_points.size(); ++i) {
			(*polygon_to_draw)[i].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[i]));
			//(*polygon_to_draw)[i].position = t_points[i]->getCoordOnScreen();
		}
		for (int i = 0; i < t_points.size(); ++i) {
			(*polygon_to_draw)[i].color = pol_color;
		}
		//sf::RenderWindow::draw(*polygon_to_draw);

		for (int i = 0; i < 6; i += 2) {
			(*line)[i].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[j % t_points.size()]));
			(*line)[i + 1].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[(j + 1) % t_points.size()]));
			//(*line)[i].position = t_points[j % t_points.size()]->getCoordOnScreen();
			//(*line)[i + 1].position = t_points[(j + 1) % t_points.size()]->getCoordOnScreen();
			j++;
		}
		for (int i = 0; i < 6; ++i)
			(*line)[i].color = sf::Color::Red;
		sf::RenderWindow::draw(*line);

		//потом к ближайшем
		if (tmp->closer != nullptr) {
			draw_polygon(tmp->closer);
		}

		return;
	}

	TDRenderWindow::TDRenderWindow() {
		bsp_tree = nullptr;

		m_thread_helper.m_thread_set_coord_done = false;
		m_thread_helper.m_thread_set_coord_is_work = true;
		m_thread_set_coord = new std::thread(threadSetCoord, &m_thread_helper, &camera);
	}

	TDRenderWindow::TDRenderWindow(sf::VideoMode video_mode, std::string title) {

		m_thread_helper.m_thread_set_coord_done = false;
		m_thread_helper.m_thread_set_coord_is_work = true;
		m_thread_set_coord = new std::thread(threadSetCoord, &m_thread_helper, &camera);

		bsp_tree = nullptr;
		sf::RenderWindow::create(video_mode, title);
	}

	void TDRenderWindow::setCamera(const Camera& camera) {
		models.clear();
		delete bsp_tree;
		bsp_tree = nullptr;

		camera_exist = true;
		this->camera = camera;
		this->camera.setScreenSize(sf::RenderWindow::getSize());
		if (world_exist) {
			this->camera.setWorldCoordSystem(this->world_coord_system);
			this->camera.setScreenSize(sf::RenderWindow::getSize());
			this->camera.generateConvertNumber();
		}
	}

	void TDRenderWindow::setWorldCoordSystem(const CoordinateSystem& world_coord_system) {
		models.clear();
		delete bsp_tree;
		bsp_tree = nullptr;

		this->world_exist = true;
		this->world_coord_system = world_coord_system;
		if (camera_exist) {
			this->camera.setWorldCoordSystem(this->world_coord_system);
			this->camera.setScreenSize(sf::RenderWindow::getSize());
			this->camera.generateConvertNumber();
		}
	}

	void TDRenderWindow::draw(Model model) {
		std::thread *t_bsp_thread, *t_coord_thread;
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

		QueryPerformanceFrequency((LARGE_INTEGER *)&m_tps);
		QueryPerformanceCounter((LARGE_INTEGER *)&m_start);

		bsp_tree = new BinaryTree;
		bsp_tree->setZeroPointOfCamera(this->camera.getZeroPointOfCamera());
		for (int i = 0; i < polygons.size(); ++i) {
			bsp_tree->addElement(polygons[i]);
		}

		QueryPerformanceCounter((LARGE_INTEGER *)&m_end);
		std::cout << ((double)(m_end - m_start) / m_tps) * 1000. << " miliseconds\n";


		//ОТРИСОВЫВАЕМ
		QueryPerformanceFrequency((LARGE_INTEGER *)&m_tps);
		QueryPerformanceCounter((LARGE_INTEGER *)&m_start);

		draw_polygon(bsp_tree->getBinaryTree());
		sf::RenderWindow::display();

		models.clear();
		delete bsp_tree;
		bsp_tree = nullptr;

		QueryPerformanceCounter((LARGE_INTEGER *)&m_end);
		std::cout << ((double)(m_end - m_start) / m_tps) * 1000. << " miliseconds\n";
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