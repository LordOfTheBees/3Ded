#include <vector>
#include <string>

#pragma once
namespace tdrw {
	class Data {
	public:
		std::string m_type;
		std::vector<float> m_coordinates;//�������� ������ ��� ����� v, vt, vn, vp
		std::vector<int> m_vertices;//���������� ������ ��� ���� f
		std::vector<int> m_texture_coordinates;// ���������� ���������� ��� ���� f
		std::vector<int> m_normal;//������� ��� ���� f
	};

	class ObjLoSa
	{
	private:
		Data m_data;
	public:
		Data separator(std::string str);

		bool load(std::string file_path);
		bool save(std::string file_path);

		ObjLoSa();
		~ObjLoSa();
	};
}

