#pragma once
#include "CoordinateSystem.h"
#include "Point.h"
#include "Camera.h"
#include "Polygon.h"
#include "Model.h"
#include "BinaryTree.h"

#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace tdrw {

	class TDRenderWindow : public sf::RenderWindow {
	private:
		int counter;
		std::vector<Model> models;
		Camera camera;
		CoordinateSystem world_coord_system;
		BinaryTree* bsp_tree;
		bool camera_exist, world_exist;

		__int64 m_start, m_end, m_tps;
	protected:
		void draw_polygon(BinTree* tmp);
	public:
		TDRenderWindow();
		TDRenderWindow(sf::VideoMode video_mode, std::string title);

		void setCamera(const Camera& camera);
		void setWorldCoordSystem(const CoordinateSystem& world_coord_system);

		virtual void draw(Model model);
		virtual void clear(sf::Color color);
		virtual void display();

		~TDRenderWindow();
	};
}
