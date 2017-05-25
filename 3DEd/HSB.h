#pragma once
#include <SFML/Graphics/Color.hpp>
namespace tdrw {
	class HSB
	{
	private:
	protected:
	public:
		int hue;//цветовой тон (0-360)
		double saturation;//насыщенность (0-100)
		double brightness;//€ркость (0-100)

		HSB();
		HSB(sf::Color rgb);

		void transferToHSB(sf::Color rgb);
		sf::Color getRGB();

		~HSB();
	};
}

