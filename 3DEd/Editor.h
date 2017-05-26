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
protected:
public:
	Editor();
	void start();

	bool moveObject();
	bool moveSelectedPoint();
	~Editor();
};