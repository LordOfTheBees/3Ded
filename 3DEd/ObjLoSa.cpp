#include "ObjLoSa.h"


namespace tdrw {
	Data ObjLoSa::separator(std::string str){
		Data t_data;
		if (str[0] == '#') {
			t_data.m_type.push_back('#');
			return t_data;
		}

		//считывает тип (первые символы до пробела)
		int i = 0;
		while (true) {
			if (str[i] == ' ')
				break;
			t_data.m_type.push_back(str[i]);
			++i;
		}
		++i;

		int t = 0;
		std::string t_tmp, t_tmp_str;
		//дальше идёт считывание данных в зависимоти от типа
		if (t_data.m_type == "v") {
			t_tmp.clear();

			for (i; i < str.size(); ++i) {
				if (str[i] == ' ') {
					t_data.m_coordinates.push_back(std::stof(t_tmp));
					t_tmp.clear();
				}
				else
					t_tmp.push_back(str[i]);
			}
			t_data.m_coordinates.push_back(std::stof(t_tmp));
			t_tmp.clear();
		}

		if (t_data.m_type == "f") {
			t = 0;
			t_tmp.clear();

			for (i; i < str.size(); ++i) {
				t_tmp_str.clear();
				while ((str[i] != ' ') && (i != str.size())) {
					t_tmp_str.push_back(str[i]);
					++i;
				}

				int j = 0;
				//После записи строки в t_tmp_str, вдираем оттуда числа
				//Считываем первое число. Вершины
				while ((t_tmp_str[j] != '/') && (j < t_tmp_str.size())) {
					t_tmp.push_back(t_tmp_str[j]);
					j++;
				}
				t_data.m_vertices.push_back(std::stoi(t_tmp));
				t_tmp.clear();
				if (j == t_tmp_str.size())
					continue;

				//Считываем второе число. Текстурные координаты
				while ((t_tmp_str[j] != '/') && (j < t_tmp_str.size())) {
					t_tmp.push_back(t_tmp_str[j]);
					j++;
				}
				t_data.m_texture_coordinates.push_back(std::stoi(t_tmp));
				t_tmp.clear();
				if (j == t_tmp_str.size())
					continue;

				//Считываем третье число. Нормаль
				while ((t_tmp_str[j] != '/') && (j < t_tmp_str.size())) {
					t_tmp.push_back(t_tmp_str[j]);
					j++;
				}
				t_data.m_normal.push_back(std::stoi(t_tmp));
				t_tmp.clear();
				if (j == t_tmp_str.size())
					continue;

			}
		}

		return t_data;
	}

	bool ObjLoSa::load(std::string file_path){

		return true;
	}
	bool ObjLoSa::save(std::string file_path)
	{
		return false;
	}
	ObjLoSa::ObjLoSa()
	{
	}


	ObjLoSa::~ObjLoSa()
	{
	}
}
