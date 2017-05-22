#include "TDRenderWindow.h"
#include <iostream>
#include <windows.h>
#include <thread>

namespace tdrw {
	void TDRenderWindow::draw_polygon(BinTree* tmp) {
		std::vector<Point*> t_points = tmp->polygon.getPoints();
		sf::VertexArray* polygon_to_draw = new sf::VertexArray(sf::Triangles, 3);
		sf::VertexArray* line = new sf::VertexArray(sf::Lines, 6);
		sf::Color pol_color = tmp->polygon.getColor();

		int j = 0;

		//������� ��� � ����� ������� ���������
		if (tmp->further != nullptr) {
			draw_polygon(tmp->further);
		}
		counter++;
		/*std::cout << "=================\n";
		std::cout << "(" << points[0].x << "," << points[0].y << "," << points[0].z << ")" << std::endl;
		std::cout << "(" << points[1].x << "," << points[1].y << "," << points[1].z << ")" << std::endl;
		std::cout << "(" << points[2].x << "," << points[2].y << "," << points[2].z << ")" << std::endl;*/
		//��� ������ ���������� ����� �� ������ ��������, �������� ������������ ��������(����������� � ���� ���������) �������
		for (int i = 0; i < t_points.size(); ++i) {
			(*polygon_to_draw)[i].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[i]));
		}
		for (int i = 0; i < t_points.size(); ++i) {
			(*polygon_to_draw)[i].color = pol_color;
		}
		//sf::RenderWindow::draw(*polygon_to_draw);

		for (int i = 0; i < 6; i += 2) {
			(*line)[i].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[j % t_points.size()]));
			(*line)[i + 1].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(*t_points[(j + 1) % t_points.size()]));
			j++;
		}
		for (int i = 0; i < 6; ++i)
			(*line)[i].color = sf::Color::Red;
		sf::RenderWindow::draw(*line);

		//����� � ���������
		if (tmp->closer != nullptr) {
			draw_polygon(tmp->closer);
		}

		return;
	}

	TDRenderWindow::TDRenderWindow() {
		bsp_tree = new BinaryTree;
	}

	TDRenderWindow::TDRenderWindow(sf::VideoMode video_mode, std::string title) {
		bsp_tree = new BinaryTree;
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

	void TDRenderWindow::setWorldCoordSystem(const CoordinateSystem& world_coord_system) {
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

		//TODO
		//���������� ��� ���, ����� ������ models.push_back(model) 
		//� ������ �������� � ���������� �������, �.�. ������ ������� bsp_tree ����� ������� � �����

		//draw in sf::RenderWIndow

	}

	void TDRenderWindow::clear(sf::Color color) {
		sf::RenderWindow::clear(color);
	}

	void TDRenderWindow::display() {
		//��������� BSP TREE
		std::vector<Polygon> polygons;
		std::vector<Polygon> tmp_data;

		for (int i = 0; i < models.size(); ++i) {
			//tmp_data.clear();
			tmp_data = models[i].getAllPolygon();
			polygons.insert(polygons.end(), tmp_data.begin(), tmp_data.end());
		}

		QueryPerformanceFrequency((LARGE_INTEGER *)&m_tps);
		QueryPerformanceCounter((LARGE_INTEGER *)&m_start);
		// ����������� ���

		bsp_tree->setZeroPointOfCamera(this->camera.getZeroPointOfCamera());
		for (int i = 0; i < polygons.size(); ++i) {
			bsp_tree->addElement(polygons[i]);
		}

		QueryPerformanceCounter((LARGE_INTEGER *)&m_end);
		std::cout << ((double)(m_end - m_start) / m_tps) * 1000. << " miliseconds\n";


		//������������
		QueryPerformanceFrequency((LARGE_INTEGER *)&m_tps);
		QueryPerformanceCounter((LARGE_INTEGER *)&m_start);
		// ����������� ���

		draw_polygon(bsp_tree->getBinaryTree());
		delete bsp_tree;
		bsp_tree = new BinaryTree;
		models.clear();
		sf::RenderWindow::display();

		QueryPerformanceCounter((LARGE_INTEGER *)&m_end);
		std::cout << ((double)(m_end - m_start) / m_tps) * 1000. << " miliseconds\n";
	}


	TDRenderWindow::~TDRenderWindow()
	{
	}
}