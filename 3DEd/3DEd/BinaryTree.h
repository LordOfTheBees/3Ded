#pragma once
#include <vector>
#include <cmath>

#include "Point.h"
#include "Polygon.h"

class BinTree {
public:
	BinTree();

	BinTree* closer;
	BinTree* further;
	Polygon polygon;
	double coefficient[4];//a*x, b*y, c*z, d
	int side_of_camera;//��������� ���� ������������ ���������� ����� ������ ������ � ��������� � ������� �� ������ ����������� 

	~BinTree();
};

class BinaryTree{
private:
	BinTree* root;
	BinTree* active_node;
	Point zero_point_of_camera;
protected:
	void toFurther(Polygon polygon);
	void toCloser(Polygon polygon);
public:
	BinaryTree();

	//�� ������ ��� ��������� ������� ��������� ��� ��������� ���������� ������
	void setRoot(Polygon polygon, Point zero_point_of_camera);
	void addElement(Polygon polygon);
	void clear();

	std::vector<Polygon> addPolygons();
	BinTree* getBinaryTree() const;
	~BinaryTree();
};

