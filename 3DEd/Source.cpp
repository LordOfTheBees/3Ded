#include "Point.h"
#include "CoordinateSystem.h"
#include "Camera.h"
#include "Polygon.h"
#include "Model.h"
#include "TDRenderWindow.h"

#include <functional>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define KEK std::cout<<"KEK\n"

int main() {
	tdrw::Point zero;
	tdrw::CoordinateSystem coord_system(3);
	tdrw::CoordinateSystem camera_coord(3);
	int x, y, z;
	x = 0;
	y = 0;
	z = 0;
	double tmp1[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	double ** coord = new double*[3];
	for (int i = 0; i < 3; ++i)
		coord[i] = new double[3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			coord[i][j] = tmp1[i][j];
	coord_system.setCoordSystem(coord, tdrw::Point(0, 0, 0));
	coord_system.setBasisCoordSystem(coord, tdrw::Point(0, 0, 0));
	coord_system.generateTransitionMatrix();

	double ** coord_camera_kek = new double*[3];
	for (int i = 0; i < 3; ++i)
		coord_camera_kek[i] = new double[3];

	double tmp2[3][3] = { { 0, 0, 1 },
						  { 0, 1, 0 },
						  { 1, 0, 0 } };
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			coord_camera_kek[i][j] = tmp2[i][j];


	camera_coord.setCoordSystem(coord_camera_kek, tdrw::Point(x, y, z));
	camera_coord.setBasisCoordSystem(coord, tdrw::Point(0, 0, 0));
	camera_coord.generateTransitionMatrix();

	tdrw::Camera camera;
	camera.setDataOfCamera(coord_system, camera_coord, 120, sf::Vector2u(1800, 900));
	camera.generateConvertNumber();
	
	tdrw::Model coub;
	coub.setModelCoordSystem(coord_system);

	/*tdrw::Point A(0, 0, 0);
	tdrw::Point B(0, 0, 10);
	tdrw::Point C(0, 10, 10);
	tdrw::Point D(10, 10, 10);
	tdrw::Point E(0, 10, 0);
	tdrw::Point F(10, 10, 0);
	tdrw::Point G(10, 0, 0);
	tdrw::Point H(10, 0, 10);
	coub.addPolygon(A, B, H, sf::Color::White);
	coub.addPolygon(A, G, H, sf::Color::White);

	coub.addPolygon(A, B, C, sf::Color::Red);
	coub.addPolygon(A, E, C, sf::Color::Red);

	coub.addPolygon(E, C, D, sf::Color::Blue);
	coub.addPolygon(E, F, D, sf::Color::Blue);

	coub.addPolygon(F, D, H, sf::Color::Cyan);
	coub.addPolygon(F, G, H, sf::Color::Cyan);

	coub.addPolygon(B, C, D, sf::Color::Green);
	coub.addPolygon(B, H, D, sf::Color::Green);

	coub.addPolygon(A, E, F, sf::Color::Magenta);
	coub.addPolygon(A, G, F, sf::Color::Magenta);*/
	coub.load("head.obj");
	tdrw::TDRenderWindow window(sf::VideoMode(1800, 900), "Kek");
	window.setCamera(camera);
	window.setWorldCoordSystem(coord_system);

	x = -100;
	y = -50;
	z = 0;
	x = 30;
	y = -3;
	z = 0;
	coord_system.setCoordSystem(coord, tdrw::Point(x, y, z));
	coub.setModelCoordSystem(coord_system);
	window.draw(coub);
	window.display();

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Left:
					z -= 2;
					break;
				case sf::Keyboard::Right:
					z += 2;
					break;
				case sf::Keyboard::Up:
					y += 2;
					break;
				case sf::Keyboard::Down:
					y -= 2;
					break;
				case sf::Keyboard::Numpad8:
					x += 2;
					break;
				case sf::Keyboard::Numpad2:
					x -= 2;
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				case sf::Keyboard::Numpad7:
					coub.rotationAngleOnX(-4);
					break;
				case sf::Keyboard::Numpad9:
					coub.rotationAngleOnX(4);
					break;
				case sf::Keyboard::Numpad4:
					coub.rotationAngleOnY(-4);
					break;
				case sf::Keyboard::Numpad6:
					coub.rotationAngleOnY(4);
					break;
				case sf::Keyboard::Numpad1:
					coub.rotationAngleOnZ(-4);
					break;
				case sf::Keyboard::Numpad3:
					coub.rotationAngleOnZ(4);
					break;
				default:
					break;
				}
				std::cout << "(" << x << ", " << y << ", " << z << ")\n";
				coub.setZeroPointOfCoord(tdrw::Point(x, y, z));
				window.clear(sf::Color::Black);
				window.draw(coub);
				window.display();
			}
		}
	}

	system("pause");

	return 0;
}