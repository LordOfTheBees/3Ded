#pragma once
#include "CoordinateSystem.h"
#include "Point.h"
#include "Camera.h"
#include "Polygon.h"
#include "Model.h"
#include "BinaryTree.h"

#include <deque>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <vector>
#include <string>
#include <fstream>
#include <functional>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace tdrw {
	class ThreadHelper {
	public:
		std::condition_variable m_cv_for_coord;
		std::mutex m_mutex;

		std::deque<Model> m_models;

		bool m_thread_set_coord_done;//true(поток надо завершить) or false(потоку надо продолжать работать)
		bool m_thread_set_coord_is_work;//true(поток работает) or false(поток не работает)
		std::mutex m_mutex_deque_models;

		ThreadHelper();
		~ThreadHelper();
	};

	class TDRenderWindow : public sf::RenderWindow {
	private:
		int counter;
		std::vector<Model> models;
		Camera camera;
		CoordinateSystem world_coord_system;
		BinaryTree* bsp_tree;
		bool camera_exist, world_exist;

		__int64 m_start, m_end, m_tps;

		ThreadHelper m_thread_helper;
		std::thread * m_thread_set_coord;
		friend void threadSetCoord(ThreadHelper * thread_helper, Camera * camera);
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
