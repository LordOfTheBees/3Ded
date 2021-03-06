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

	tdrw::Point m_light_point;
	tdrw::CoordinateSystem m_light_coord_system;
protected:
public:
	Editor();

	void drawAllElement();

	void start();

	bool moveObject();
	bool moveCamera();

	bool controlPolygons();
	bool changeSelectedPolygon();
	bool createNewPolygon();

	bool controlPoints();
	bool moveSelectedPoint();
	bool createNewPoint();

	~Editor();
};