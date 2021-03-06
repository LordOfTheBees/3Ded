#pragma once
#include "CoordinateSystem.h"
#include "Point.h"
#include "Camera.h"
#include "Polygon.h"
#include "Model.h"
#include "BinaryTree.h"
#include "Light.h"

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

		bool m_thread_set_coord_done;//true(����� ���� ���������) or false(������ ���� ���������� ��������)
		bool m_thread_set_coord_is_work;//true(����� ��������) or false(����� �� ��������)
		std::mutex m_mutex_deque_models;

		ThreadHelper();
		~ThreadHelper();
	};

	class TDRenderWindow : public sf::RenderWindow {
	private:
		std::vector<Model> m_models;
		Camera m_camera;
		Light m_light;
		CoordinateSystem m_world_coord_system;
		BinaryTree* m_bsp_tree;
		bool m_camera_exist, m_world_exist;
		bool m_frame_exist, m_color_exist; // true - ��������
		bool m_gradient_color_is_on;//true - ��������
		bool m_wrong_side_is_on;//true - ������� == �������� ������������ �� ������ ����� ��������������
		bool m_draw_models_system_coord_is_on;//true - �������
		bool m_allocation_of_points_is_on;//true - �������
		bool m_draw_unusable_points_is_on;//true - �������
		__int64 m_start, m_end, m_tps;

		ThreadHelper m_thread_helper;
		std::thread * m_thread_set_coord;
		friend static void threadSetCoord(ThreadHelper * thread_helper, Camera * camera);

		void drawModelsSystemCoord(const Model& model);
		void drawUnusablePoints(Model& model);
	protected:
		void draw_polygon(BinTree* tmp);
	public:
		TDRenderWindow();
		TDRenderWindow(sf::VideoMode video_mode, std::string title);

		void setCamera(const Camera& camera);
		void setLight(const Light& light);
		void setWorldCoordSystem(const CoordinateSystem& world_coord_system);

		void activeFrame(bool frame);
		void activeColor(bool color);
		void activeGradient(bool gradient);
		void activeWrongSide(bool switcher);
		void activeDrawModelsCS(bool switcher);//CS - Coord System
		void activeAllocationPoint(bool swithcer);
		void activeDrawUnusablePoints(bool switcher);

		virtual void draw(Model model);
		virtual void clear(sf::Color color);
		virtual void display();

		Camera getCamera();
		CoordinateSystem getWorldCoordSystem();

		Point * getPointToControl(sf::Vector2f coord_on_screen);
		Polygon * getPolygonToControl(sf::Vector2f coord_on_screen);

		~TDRenderWindow();
	};
}
