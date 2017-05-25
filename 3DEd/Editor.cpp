#include "Editor.h"

#include "TDRenderWindow.h"
#include "Model.h"
#include "Point.h"
#include "CoordinateSystem.h"
#include "Camera.h"
#include "Polygon.h"

#include <iostream>
Editor::Editor()
{
}

void Editor::start() {
	tdrw::TDRenderWindow t_td_window(sf::VideoMode(1800, 900), "Kek");
	tdrw::Point zero;
	tdrw::CoordinateSystem t_coord_system;
	tdrw::CoordinateSystem camera_coord;

	t_coord_system.setCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(0, 0, 0));
	t_coord_system.setBasisCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(0, 0, 0));
	t_coord_system.generateTransitionMatrix();


	camera_coord.setCoordSystem({ { 0, 0, 1 },{ 0, 1, 0 },{ 1, 0, 0 } }, tdrw::Point(0, 0, 0));
	camera_coord.setBasisCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(0, 0, 0));
	camera_coord.generateTransitionMatrix();

	tdrw::Camera camera;
	camera.setDataOfCamera(t_coord_system, camera_coord, 120, sf::Vector2u(1800, 900));
	camera.generateConvertNumber();

	camera_coord.setBasisCoordSystem(t_coord_system);
	camera_coord.generateTransitionMatrix();
	tdrw::Light light;
	light.setDirection(camera_coord);
	

	t_td_window.setLight(light);
	t_td_window.setCamera(camera);
	t_td_window.setWorldCoordSystem(t_coord_system);


	tdrw::Model t_object;
	double x = 30, y = -3, z = 0;

	t_object.load("gourd.obj");
	t_coord_system.setCoordSystem({ { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } }, tdrw::Point(x, y, z));
	t_object.setModelCoordSystem(t_coord_system);

	t_td_window.draw(t_object);
	t_td_window.display();

	sf::Event event;
	while (t_td_window.isOpen()) {
		while (t_td_window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Left:
					z -= 1;
					break;
				case sf::Keyboard::Right:
					z += 1;
					break;
				case sf::Keyboard::Up:
					y += 1;
					break;
				case sf::Keyboard::Down:
					y -= 1;
					break;
				case sf::Keyboard::Numpad8:
					x += 1;
					break;
				case sf::Keyboard::Numpad2:
					x -= 1;
					break;
				case sf::Keyboard::Escape:
					t_td_window.close();
					break;
				case sf::Keyboard::Numpad7:
					t_object.rotationAngleOnX(-4);
					break;
				case sf::Keyboard::Numpad9:
					t_object.rotationAngleOnX(4);
					break;
				case sf::Keyboard::Numpad4:
					t_object.rotationAngleOnY(-4);
					break;
				case sf::Keyboard::Numpad6:
					t_object.rotationAngleOnY(4);
					break;
				case sf::Keyboard::Numpad1:
					t_object.rotationAngleOnZ(-4);
					break;
				case sf::Keyboard::Numpad3:
					t_object.rotationAngleOnZ(4);
					break;
				default:
					break;
				}
				std::cout << "(" << x << ", " << y << ", " << z << ")\n";
				t_object.setZeroPointOfCoord(tdrw::Point(x, y, z));
				t_td_window.clear(sf::Color::Black);
				t_td_window.draw(t_object);
				t_td_window.display();
			}
		}
	}
}


Editor::~Editor()
{
}

