#include "Editor.h"

#include <vector>
#include <algorithm>
Editor::Editor()
{
}

void Editor::drawAllElement(){
	m_window->clear(sf::Color::Black);
	m_window->draw(m_object);
	m_window->display();
}

void Editor::start() {
	m_window = new tdrw::TDRenderWindow(sf::VideoMode(1800, 900), "Kek");
	tdrw::Point zero;
	tdrw::CoordinateSystem t_coord_system;
	tdrw::CoordinateSystem m_camera_coord;

	t_coord_system.setCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(0, 0, 0));
	t_coord_system.setBasisCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(0, 0, 0));
	t_coord_system.generateTransitionMatrix();


	m_camera_coord.setCoordSystem({ { 0, 0, 1 },{ 0, 1, 0 },{ 1, 0, 0 } }, tdrw::Point(0, 0, 0));
	m_camera_coord.setBasisCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(0, 0, 0));
	m_camera_coord.generateTransitionMatrix();

	m_camera.setDataOfCamera(t_coord_system, m_camera_coord, 120, sf::Vector2u(1800, 900));
	m_camera.generateConvertNumber();

	m_camera_coord.setBasisCoordSystem(t_coord_system);
	m_camera_coord.generateTransitionMatrix();
	m_light.setDirection(m_camera_coord);
	

	m_window->setLight(m_light);
	m_window->setCamera(m_camera);
	m_window->setWorldCoordSystem(t_coord_system);

	double x = 30, y = -3, z = 0;

	m_object.load("head.obj");
	std::cout << "Load finished\n";
	t_coord_system.setCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(x, y, z));
	m_object.setModelCoordSystem(t_coord_system);

	m_window->draw(m_object);
	m_window->display();

	bool a_frame = true, a_color = true, a_gradient = false, a_wrong_side = true;
	
	sf::Vector2i t_mouse_position;
	sf::Event event;
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					//Move object
				case sf::Keyboard::F1: {
					moveObject();
					break;
				}

					//Move camera
				case sf::Keyboard::F2: {
					moveCamera();
					break;
				}

					//Control Poins
				case sf::Keyboard::F3: {
					controlPoints();
					break;
				}

					//Control Polygons
				case sf::Keyboard::F4: {
					controlPolygons();
					break;
				}

					//Turn on/off wrong side in polygons
				case sf::Keyboard::W: {
					if (a_wrong_side) {
						a_wrong_side = false;
						m_window->activeWrongSide(a_wrong_side);
					}
					else {
						a_wrong_side = true;
						m_window->activeWrongSide(a_wrong_side);
					}
					drawAllElement();
					break;
				}

					//Turn on/off gradient
				case sf::Keyboard::G: {
					if (a_gradient) {
						a_gradient = false;
						m_window->activeGradient(a_gradient);
					}
					else {
						a_gradient = true;
						m_window->activeGradient(a_gradient);
					}
					drawAllElement();
					break;
				}

					//Turn on/off frame
				case sf::Keyboard::F: {
					if (a_frame) {
						a_frame = false;
						m_window->activeFrame(a_frame);
					}
					else {
						a_frame = true;
						m_window->activeFrame(a_frame);
					}
					drawAllElement();
					break;
				}

					//Turn on/off polygon's color
				case sf::Keyboard::C: {
					if (a_color) {
						a_color = false;
						m_window->activeColor(a_color);
					}
					else {
						a_color = true;
						m_window->activeColor(a_color);
					}
					drawAllElement();
					break;
				}

					//Exit
				case sf::Keyboard::Escape: {
					m_window->close();
					break;
				}
				default:
					break;
				}
			}
		}
	}
}


bool Editor::moveObject()
{
	std::cout << "\t Pls, move Object...\n";
	static double x = 30, y = -3, z = 0;
	sf::Event event;
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Left:
					z -= 1;
					m_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
					drawAllElement();
					break;
				case sf::Keyboard::Right:
					z += 1;
					m_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
					drawAllElement();
					break;
				case sf::Keyboard::Up:
					y += 1;
					m_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
					drawAllElement();
					break;
				case sf::Keyboard::Down:
					y -= 1;
					m_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
					drawAllElement();
					break;
				case sf::Keyboard::Numpad8:
					x += 1;
					m_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
					drawAllElement();
					break;
				case sf::Keyboard::Numpad2:
					x -= 1;
					m_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
					drawAllElement();
					break;
				case sf::Keyboard::Numpad7:
					m_object.rotationAngleOnX(-10);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad9:
					m_object.rotationAngleOnX(10);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad4:
					m_object.rotationAngleOnY(-10);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad6:
					m_object.rotationAngleOnY(10);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad1:
					m_object.rotationAngleOnZ(-10);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad3:
					m_object.rotationAngleOnZ(10);
					drawAllElement();
					break;
				case sf::Keyboard::P:
					std::cout << "\t End move Object\n";
					return true;
				default:
					break;
				}
				std::cout << "\t(" << x << ", " << y << ", " << z << ")\n";
				//m_window->setCamera(m_camera);
			}
		}
	}
	std::cout << "\t End move Object\n";
	return true;
}

bool Editor::moveCamera(){
	std::cout << "\t Pls, move Camera...\n";
	tdrw::Point t_zero_point_of_camera = m_camera.getZeroPointOfCamera();
	tdrw::Point t_point_to_move(0, 0, 0);
	sf::Event event;
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Left:
					t_point_to_move.z -= 1;
					m_camera.setZeroPointOfCoord(m_camera.convertToWoorldSystem(t_point_to_move));
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Right:
					t_point_to_move.z += 1;
					m_camera.setZeroPointOfCoord(m_camera.convertToWoorldSystem(t_point_to_move));
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Up:
					t_point_to_move.y += 1;
					m_camera.setZeroPointOfCoord(m_camera.convertToWoorldSystem(t_point_to_move));
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Down:
					t_point_to_move.y -= 1;
					m_camera.setZeroPointOfCoord(m_camera.convertToWoorldSystem(t_point_to_move));
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad8:
					t_point_to_move.x += 1;
					m_camera.setZeroPointOfCoord(m_camera.convertToWoorldSystem(t_point_to_move));
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad2:
					t_point_to_move.x -= 1;
					m_camera.setZeroPointOfCoord(m_camera.convertToWoorldSystem(t_point_to_move));
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad7:
					m_camera.rotationAngleOnX(-10);
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad9:
					m_camera.rotationAngleOnX(10);
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad4:
					m_camera.rotationAngleOnY(-10);
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad6:
					m_camera.rotationAngleOnY(10);
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad1:
					m_camera.rotationAngleOnZ(-10);
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::Numpad3:
					m_camera.rotationAngleOnZ(10);
					m_window->setCamera(m_camera);
					drawAllElement();
					break;
				case sf::Keyboard::P:
					std::cout << "\t End move Camera\n";
					return true;
				default:
					break;
				}
				t_point_to_move.setCoord(0, 0, 0);
			}
		}
	}
	std::cout << "\t End move Camera\n";
	return true;
}

bool Editor::controlPolygons(){
	std::cout << "\t Pls, select Polygon...\n";
	sf::Vector2i t_mouse_position;
	sf::Event event;
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				switch (event.key.code) {
				case sf::Mouse::Left:
					t_mouse_position = sf::Mouse::getPosition(*m_window);
					std::cout << "\t(" << t_mouse_position.x << ", " << t_mouse_position.y << ")\n";
					m_selected_polygon = m_window->getPolygonToControl(sf::Vector2f(t_mouse_position.x, t_mouse_position.y));
					if (m_selected_polygon != nullptr) {
						changeSelectedPolygon();
					}
					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::P: {
					std::cout << "\t End select Polygon\n";
					return true;
				}
				default:
					break;
				}
			}
		}
	}
	std::cout << "\t End select Polygon\n";
	return false;
}

bool Editor::changeSelectedPolygon(){
	std::cout << "\t\tPls, change selected polygon...\n";
	sf::Event event;
	sf::Color t_save_color = m_selected_polygon->getColor();
	std::vector<tdrw::Point*> t_tmp_points;

	m_selected_polygon->setColor(sf::Color::Blue);
	m_window->clear(sf::Color::Black);
	m_window->draw(m_object);
	m_window->display();
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					//Change normal
				case sf::Keyboard::N: {
					t_tmp_points = m_selected_polygon->getPoints();
					std::reverse(t_tmp_points.begin(), t_tmp_points.end());
					m_selected_polygon->setPoints(t_tmp_points);
					t_tmp_points.clear();
					drawAllElement();
					break;
				}
				case sf::Keyboard::P:
					m_selected_polygon->setColor(t_save_color);
					drawAllElement();
					std::cout << "\t\tEnd change Polygon\n";
					return true;
					break;
				default:
					break;
				}
			}
		}
	}
	m_selected_polygon->setColor(t_save_color);
	std::cout << "\t\tEnd change Polygon\n";
	return false;
}

bool Editor::controlPoints()
{
	std::cout << "\t Pls, select Point...\n";
	sf::Vector2i t_mouse_position;
	sf::Event event;
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				switch (event.key.code) {
				case sf::Mouse::Left:
					t_mouse_position = sf::Mouse::getPosition(*m_window);
					std::cout << "\t(" << t_mouse_position.x << ", " << t_mouse_position.y << ")\n";
					m_selected_point = m_window->getPointToControl(sf::Vector2f(t_mouse_position.x, t_mouse_position.y));
					if (m_selected_point != nullptr) {
						moveSelectedPoint();
					}
					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code){
				case sf::Keyboard::P: {
					std::cout << "\t End select Point\n";
					return true;
				}
				default:
					break;
				}
			}
		}
	}
	std::cout << "\t End select Point\n";
	return false;
}

bool Editor::moveSelectedPoint()
{
	std::cout << "\t\t Pls, move selected Point...\n";
	sf::Event event;
	while (m_window->isOpen()) {
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Left:
					m_selected_point->z -= 0.1;
					break;
				case sf::Keyboard::Right:
					m_selected_point->z += 0.1;
					break;
				case sf::Keyboard::Up:
					m_selected_point->y += 0.1;
					break;
				case sf::Keyboard::Down:
					m_selected_point->y -= 0.1;
					break;
				case sf::Keyboard::Numpad8:
					m_selected_point->x += 0.1;
					break;
				case sf::Keyboard::Numpad2:
					m_selected_point->x -= 0.1;
					break;
				case sf::Keyboard::P:
					std::cout << "\t\t End move selected Point\n";
					return true;
					break;
				default:
					break;
				}
				m_window->clear(sf::Color::Black);
				m_window->draw(m_object);
				m_window->display();
			}
		}
	}
	std::cout << "\t\t End move selected Point\n";
	return true;
}

Editor::~Editor()
{
}

