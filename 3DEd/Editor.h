#include "TDRenderWindow.h"
#include "Model.h"
#include "Point.h"
#include "CoordinateSystem.h"
#include "Camera.h"
#include "Polygon.h"

#include <iostream>
#pragma once

class Editor {
private:
	tdrw::TDRenderWindow * m_window;
	tdrw::Light m_light;
	tdrw::Camera m_camera;
	tdrw::Model m_object;
	tdrw::Point * m_selected_point;
	tdrw::Polygon * m_selected_polygon;
protected:
public:
	Editor();

	void drawAllElement();

	void start();

	bool moveObject();
	bool moveCamera();

	bool controlPolygons();
	bool changeSelectedPolygon();

	bool controlPoints();
	bool moveSelectedPoint();

	~Editor();
};