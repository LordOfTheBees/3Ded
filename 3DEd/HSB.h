#pragma once
#include <SFML/Graphics/Color.hpp>
namespace tdrw {
	class HSB
	{
	private:
	protected:
	public:
		int hue;//�������� ��� (0-360)
		double saturation;//������������ (0-100)
		double brightness;//������� (0-100)

		HSB();
		HSB(sf::Color rgb);

		void transferToHSB(sf::Color rgb);
		sf::Color getRGB();

		~HSB();
	};
}

