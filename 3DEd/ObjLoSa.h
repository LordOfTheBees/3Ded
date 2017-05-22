#include <vector>
#include <string>

#pragma once
namespace tdrw {
	class Data {
	public:
		std::string m_type;
		std::vector<float> m_coordinates;//хранение данных при типах v, vt, vn, vp
		std::vector<int> m_vertices;//координаты вершин при типе f
		std::vector<int> m_texture_coordinates;// текстурные координаты при типе f
		std::vector<int> m_normal;//нормали при типе f
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

