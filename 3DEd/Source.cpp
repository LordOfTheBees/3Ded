#include "Point.h"
#include "CoordinateSystem.h"
#include "Camera.h"
#include "Polygon.h"
#include "Model.h"
#include "TDRenderWindow.h"
#include "Editor.h"

#include <functional>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define KEK std::cout<<"KEK\n"

int main() {

	Editor editor;
	editor.start();
	
	system("pause");

	return 0;
}