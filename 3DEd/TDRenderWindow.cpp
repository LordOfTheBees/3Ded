#include "TDRenderWindow.h"
#include <iostream>

namespace tdrw {
	void TDRenderWindow::draw_polygon(BinTree* tmp) {
		std::vector<Point> points = tmp->polygon.getPoints();
		sf::VertexArray* polygon_to_draw = new sf::VertexArray(sf::Triangles, 3);
		sf::VertexArray* line = new sf::VertexArray(sf::Lines, 6);
		sf::Color pol_color = tmp->polygon.getColor();

		int j = 0;

		//вначале идём к самым дальним полигонам
		if (tmp->further != nullptr) {
			draw_polygon(tmp->further);
		}
		counter++;
		/*std::cout << "=================\n";
		std::cout << "(" << points[0].x << "," << points[0].y << "," << points[0].z << ")" << std::endl;
		std::cout << "(" << points[1].x << "," << points[1].y << "," << points[1].z << ")" << std::endl;
		std::cout << "(" << points[2].x << "," << points[2].y << "," << points[2].z << ")" << std::endl;*/
		//как только рекурсивно дошли до самого дальнего, начинаем отрисовывать активный(послученный в виде аргумента) полигон
		for (int i = 0; i < points.size(); ++i) {
			(*polygon_to_draw)[i].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(points[i]));
		}
		for (int i = 0; i < points.size(); ++i) {
			(*polygon_to_draw)[i].color = pol_color;
		}
		sf::RenderWindow::draw(*polygon_to_draw);

		for (int i = 0; i < 6; i += 2) {
			(*line)[i].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(points[j % points.size()]));
			(*line)[i + 1].position = camera.getCoordOnScreen(models[0].convertToWorldCoordSystem(points[(j + 1) % points.size()]));
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
		std::vector<Polygon> polygons;
		std::vector<Polygon> tmp_data;
		models.push_back(model);

		for (int i = 0; i < models.size(); ++i) {
			//tmp_data.clear();
			tmp_data = models[i].getAllPolygon();
			polygons.insert(polygons.end(), tmp_data.begin(), tmp_data.end());
		}

		bsp_tree->setZeroPointOfCamera(this->camera.getZeroPointOfCamera());
		for (int i = 0; i < polygons.size(); ++i) {
			bsp_tree->addElement(polygons[i]);
		}

		//draw in sf::RenderWIndow

	}

	void TDRenderWindow::clear(sf::Color color) {
		sf::RenderWindow::clear(color);
	}

	void TDRenderWindow::display() {
		counter = 0;
		draw_polygon(bsp_tree->getBinaryTree());
		delete bsp_tree;
		bsp_tree = new BinaryTree;
		models.clear();
		sf::RenderWindow::display();
		std::cout << counter << std::endl;
	}


	TDRenderWindow::~TDRenderWindow()
	{
	}
}