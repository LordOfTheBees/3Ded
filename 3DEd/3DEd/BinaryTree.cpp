#include "BinaryTree.h"
#include <iostream>


void BinaryTree::toFurther(Polygon polygon) {
	std::cout << "Further\n";
	active_node->further = new BinTree;
	active_node = active_node->further;
	active_node->polygon = polygon;

	std::vector<Point> points = polygon.getPoints();

	Point M0 = points[0];
	Point M1 = points[1];
	Point M2 = points[2];

	active_node->coefficient[0] = -M0.y*(M2.z - M1.z) + M1.y*(M2.z - M0.z) - M2.y*(M1.z - M0.z);
	active_node->coefficient[1] = M0.z*(M1.x - M2.x) - M1.z*(M0.x - M2.x) + M2.z*(M0.x - M1.x);
	active_node->coefficient[2] = M0.x*(M1.y - M2.y) - M1.x*(M0.y - M2.y) + M2.x*(M0.y - M1.y);
	active_node->coefficient[3] = -M0.x*active_node->coefficient[0] - M0.y*active_node->coefficient[1] - M0.z*active_node->coefficient[2];

	/*active_node->coefficient[0] = (M1.y - M0.y)*(M2.z - M0.z) - (M2.y - M0.y)*(M1.z - M0.z);
	active_node->coefficient[1] = -(M1.x - M0.x)*(M2.z - M0.z) + (M2.x - M0.x)*(M1.z - M0.z);
	active_node->coefficient[2] = (M1.x - M0.x)*(M2.y - M0.y) - (M2.x - M0.x)*(M1.y - M0.y);
	active_node->coefficient[3] = -active_node->coefficient[0] * M0.x + active_node->coefficient[1] * M0.y - active_node->coefficient[2] * M0.z;*/

	double n = zero_point_of_camera.x * active_node->coefficient[0] + zero_point_of_camera.y * active_node->coefficient[1] + zero_point_of_camera.z * active_node->coefficient[2] + active_node->coefficient[3];
	active_node->side_of_camera = std::signbit(n);
}

void BinaryTree::toCloser(Polygon polygon) {
	std::cout << "Closser\n";
	active_node->closer = new BinTree;
	active_node = active_node->closer;
	active_node->polygon = polygon;

	std::vector<Point> points = polygon.getPoints();

	Point M0 = points[0];
	Point M1 = points[1];
	Point M2 = points[2];

	active_node->coefficient[0] = -M0.y*(M2.z - M1.z) + M1.y*(M2.z - M0.z) - M2.y*(M1.z - M0.z);
	active_node->coefficient[1] = M0.z*(M1.x - M2.x) - M1.z*(M0.x - M2.x) + M2.z*(M0.x - M1.x);
	active_node->coefficient[2] = M0.x*(M1.y - M2.y) - M1.x*(M0.y - M2.y) + M2.x*(M0.y - M1.y);
	active_node->coefficient[3] = -M0.x*active_node->coefficient[0] - M0.y*active_node->coefficient[1] - M0.z*active_node->coefficient[2];

	/*active_node->coefficient[0] = (M1.y - M0.y)*(M2.z - M0.z) - (M2.y - M0.y)*(M1.z - M0.z);
	active_node->coefficient[1] = -(M1.x - M0.x)*(M2.z - M0.z) + (M2.x - M0.x)*(M1.z - M0.z);
	active_node->coefficient[2] = (M1.x - M0.x)*(M2.y - M0.y) - (M2.x - M0.x)*(M1.y - M0.y);
	active_node->coefficient[3] = -active_node->coefficient[0] * M0.x + active_node->coefficient[1] * M0.y - active_node->coefficient[2] * M0.z;*/

	double n = zero_point_of_camera.x * active_node->coefficient[0] + zero_point_of_camera.y * active_node->coefficient[1] + zero_point_of_camera.z * active_node->coefficient[2] + active_node->coefficient[3];
	active_node->side_of_camera = std::signbit(n);
}

BinaryTree::BinaryTree() {
	root = nullptr;
	active_node = nullptr;
}

void BinaryTree::setRoot(Polygon polygon, Point zero_point_of_camera) {
	root = new BinTree;
	root->polygon = polygon;
	this->active_node = root;

	this->zero_point_of_camera = zero_point_of_camera;
	std::vector<Point> points = polygon.getPoints();

	Point M0 = points[0];
	Point M1 = points[1];
	Point M2 = points[2];

	active_node->coefficient[0] = -M0.y*(M2.z - M1.z) + M1.y*(M2.z - M0.z) - M2.y*(M1.z - M0.z);
	active_node->coefficient[1] = M0.z*(M1.x - M2.x) - M1.z*(M0.x - M2.x) + M2.z*(M0.x - M1.x);
	active_node->coefficient[2] = M0.x*(M1.y - M2.y) - M1.x*(M0.y - M2.y) + M2.x*(M0.y - M1.y);
	active_node->coefficient[3] = -M0.x*active_node->coefficient[0] - M0.y*active_node->coefficient[1] - M0.z*active_node->coefficient[2];

	/*active_node->coefficient[0] = (M1.y - M0.y)*(M2.z - M0.z) - (M2.y - M0.y)*(M1.z - M0.z);
	active_node->coefficient[1] = -(M1.x - M0.x)*(M2.z - M0.z) + (M2.x - M0.x)*(M1.z - M0.z);
	active_node->coefficient[2] = (M1.x - M0.x)*(M2.y - M0.y) - (M2.x - M0.x)*(M1.y - M0.y);
	active_node->coefficient[3] = -active_node->coefficient[0] * M0.x + active_node->coefficient[1] * M0.y - active_node->coefficient[2] * M0.z;*/

	double n = zero_point_of_camera.x * active_node->coefficient[0] + zero_point_of_camera.y * active_node->coefficient[1] + zero_point_of_camera.z * active_node->coefficient[2] + active_node->coefficient[3];
	active_node->side_of_camera = std::signbit(n);
}

void BinaryTree::addElement(Polygon polygon) {
	active_node = root;
	std::vector<Point> points = polygon.getPoints();

	bool found = false;
	double n;

	while (!found) {
		for (int i = 0; i < points.size(); ++i) {
			n = points[i].x * active_node->coefficient[0] + points[i].y * active_node->coefficient[1] + points[i].z * active_node->coefficient[2] + active_node->coefficient[3];
			if (n == 0)
				continue;
			n = std::signbit(n);

			if (n == active_node->side_of_camera) {
				if (active_node->closer == nullptr) {
					BinaryTree::toCloser(polygon);
					found = true;
					break;
				}
				else {
					active_node = active_node->closer;
				}
			}
			else {
				if (active_node->further == nullptr) {
					BinaryTree::toFurther(polygon);
					found = true;
					break;
				}
				else {
					active_node = active_node->further;
				}
			}

		}
		if (!found) {
			if (active_node->closer != nullptr)
				active_node = active_node->closer;
			else {
				BinaryTree::toCloser(polygon);
				found = true;
			}
		}
	}
}

void BinaryTree::clear() {
	delete root;
	root = nullptr;
	active_node = nullptr;
}

std::vector<Polygon> BinaryTree::addPolygons() {

	return std::vector<Polygon>();
}

BinTree * BinaryTree::getBinaryTree() const {
	return root;
}


BinaryTree::~BinaryTree() {
	active_node = nullptr;
	delete root;
}

BinTree::BinTree() {
	closer = nullptr;
	further = nullptr;
	side_of_camera = 0;
	for (int i = 0; i < 4; ++i)
		coefficient[i] = 0;
}

BinTree::~BinTree() {
	delete closer;
	delete further;
}
