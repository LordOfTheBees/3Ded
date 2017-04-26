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

int main() {
	Point zero;
	CoordinateSystem coord_system(3);
	CoordinateSystem camera_coord(3);
	int x, y, z;
	x = 15;
	y = 15;
	z = 15;
	double tmp1[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	double ** coord = new double*[3];
	for (int i = 0; i < 3; ++i)
		coord[i] = new double[3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			coord[i][j] = tmp1[i][j];
	coord_system.setCoordSystem(coord, Point(0, 0, 0));
	coord_system.setBasisCoordSystem(coord, Point(0, 0, 0));
	coord_system.generateTransitionMatrix();

	double ** coord_camera_kek = new double*[3];
	for (int i = 0; i < 3; ++i)
		coord_camera_kek[i] = new double[3];

	double tmp2[3][3] = { { 0, 0, -1 },
						  { 0, 1, 0 },
						  { 1, 0, 0 } };
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			coord_camera_kek[i][j] = tmp2[i][j];


	camera_coord.setCoordSystem(coord_camera_kek, Point(x, y, z));
	camera_coord.setBasisCoordSystem(coord, Point(0, 0, 0));
	camera_coord.generateTransitionMatrix();

	Camera camera;
	camera.setDataOfCamera(coord_system, camera_coord, 160, sf::Vector2u(1280, 1280));
	camera.generateConvertNumber();
	
	Model coub;
	coub.setModelCoordSystem(coord_system);

	Point A(0, 0, 0);
	Point B(0, 0, 10);
	Point C(0, 10, 10);
	Point D(10, 10, 10);
	Point E(0, 10, 0);
	Point F(10, 10, 0);
	Point G(10, 0, 0);
	Point H(10, 0, 10);

	coub.addPolygon(Polygon(A, B, H, sf::Color::White));
	coub.addPolygon(Polygon(A, G, H, sf::Color::White));

	coub.addPolygon(Polygon(A, B, C, sf::Color::White));
	coub.addPolygon(Polygon(A, E, C, sf::Color::White));

	coub.addPolygon(Polygon(E, C, D, sf::Color::White));
	coub.addPolygon(Polygon(E, F, D, sf::Color::White));

	coub.addPolygon(Polygon(F, D, H, sf::Color::White));
	coub.addPolygon(Polygon(F, G, H, sf::Color::White));

	coub.addPolygon(Polygon(B, C, D, sf::Color::White));
	coub.addPolygon(Polygon(B, H, D, sf::Color::White));

	coub.addPolygon(Polygon(A, E, F, sf::Color::White));
	coub.addPolygon(Polygon(A, G, F, sf::Color::White));

	TDRenderWindow window(sf::VideoMode(1920, 1080), "Kek");
	window.setCamera(camera);
	window.setWorldCoordSystem(coord_system);

	window.draw(coub);
	window.display();
	x = -100;
	y = -50;
	z = 0;
	for (x; x < -20; ++x) {
		y++;
		coord_system.setCoordSystem(coord, Point(x, y, z));
		coub.setModelCoordSystem(coord_system);
		window.clear(sf::Color::Black);
		window.draw(coub);
		window.display();
	}
	/*CoordinateSystem coord11;
	CoordinateSystem coord22;

	double tmp1[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	double ** coord1 = new double*[3];
	for (int i = 0; i < 3; ++i)
		coord1[i] = new double[3];

	double tmp2[3][3] = { { 1, 0, 0 },{ 0, 1, 0 },{ 0, 0, 1 } };
	double ** coord2 = new double*[3];
	for (int i = 0; i < 3; ++i)
		coord2[i] = new double[3];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			coord1[i][j] = tmp1[i][j];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			coord2[i][j] = tmp1[i][j];
	
	coord11.setCoordSystem(coord1, Point(0, 0, 0));
	coord22.setCoordSystem(coord2, Point(3, 0, 0));
	coord11.setBasisCoordSystem(coord22);
	coord11.generateTransitionMatrix();
	Point result_point = coord11.convertToBasis(Point(5, 2, 3));
	std::cout << "(" << result_point.x << "," << result_point.y << "," << result_point.z << ")" << std::endl;
	Camera camera;
	camera.setWorldCoordSystem(coord11);
	camera.setCameraCoordSystem(coord22);
	camera.setViewingAngle(120);
	camera.setScreenSize(sf::Vector2u(1920, 1080));
	camera.generateConvertNumber();
	sf::Vector2f result_point_on_screen = camera.getCoordOnScreen(Point(1, 1, 2));
	std::cout << "(" << result_point_on_screen.x << "," << result_point_on_screen.y << ")\n";*/
	double ch = 7 / 12;
	std::cout << ch / ch << std::endl;
	ch = ch / ch;
	std::cout << ch << std::endl;
	system("pause");

	return 0;
}