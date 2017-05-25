#include "HSB.h"

#include <cmath>
namespace tdrw {
	HSB::HSB(){
		hue = 0;
		saturation = 0;
		brightness = 100;
		//белый
	}

	HSB::HSB(sf::Color rgb){
		double t_r = ((double)rgb.r)/255;
		double t_g = ((double)rgb.g)/255;
		double t_b = ((double)rgb.b)/255;
		double t_max = 0;
		double t_min = 1;
		double t_delta;

		t_max = std::fmax(t_r, t_g);
		t_max = std::fmax(t_max, t_b);

		t_min = std::fmin(t_r, t_g);
		t_min = std::fmin(t_min, t_b);

		t_delta = t_max - t_min;

		//hue
			 if (t_delta == 0) hue = 0;
		else if (t_max == t_r) hue = std::floor(60 * (((t_g - t_b) / t_delta) + 6) + .5);
		else if (t_max == t_g) hue = std::floor(60 * (((t_b - t_r) / t_delta) + 2) + .5);
		else				   hue = std::floor(60 * (((t_r - t_g) / t_delta) + 4) + .5);

		if (hue >= 360) hue -= 360;
		//saturation
		if (t_max == 0) saturation = 0;
		else			saturation = t_delta / t_max;
		saturation *= 100;

		//brightness
		brightness = t_max * 100;
	}

	void HSB::transferToHSB(sf::Color rgb){
		double t_r = ((double)rgb.r) / 255;
		double t_g = ((double)rgb.g) / 255;
		double t_b = ((double)rgb.b) / 255;
		double t_max = 0;
		double t_min = 1;
		double t_delta;

		t_max = std::fmax(t_r, t_g);
		t_max = std::fmax(t_max, t_b);

		t_min = std::fmin(t_r, t_g);
		t_min = std::fmin(t_min, t_b);

		t_delta = t_max - t_min;

		//hue
		if (t_delta == 0) hue = 0;
		else if (t_max == t_r) hue = std::floor(60 * (((t_g - t_b) / t_delta) + 6) + .5);
		else if (t_max == t_g) hue = std::floor(60 * (((t_b - t_r) / t_delta) + 2) + .5);
		else				   hue = std::floor(60 * (((t_r - t_g) / t_delta) + 4) + .5);

		if (hue >= 360) hue -= 360;
		//saturation
		if (t_max == 0) saturation = 0;
		else			saturation = t_delta / t_max;
		saturation *= 100;

		//brightness
		brightness = t_max * 100;
	}

	sf::Color HSB::getRGB(){
		double t_min = ((100 - saturation)*brightness) / 100;
		double t_a = (brightness - t_min) * (hue % 60) / 60;
		double t_inc = t_min + t_a;
		double t_dec = brightness - t_a;

		int t_swithcer = hue / 60;
		double t_r, t_g, t_b;
		switch (t_swithcer)
		{
		case 0:
			return sf::Color(brightness * 255 / 100, t_inc * 255 / 100, t_min * 255 / 100);
		case 1:
			return sf::Color(t_dec * 255 / 100, brightness * 255 / 100, t_min * 255 / 100);
		case 2:
			return sf::Color(t_min * 255 / 100, brightness * 255 / 100, t_inc * 255 / 100);
		case 3:
			return sf::Color(t_min * 255 / 100, t_dec * 255 / 100, brightness * 255 / 100);
		case 4:
			return sf::Color(t_inc * 255 / 100, t_min * 255 / 100, brightness * 255 / 100);
		case 5:
			return sf::Color(brightness * 255 / 100, t_min * 255 / 100, t_dec * 255 / 100);
		default:
			break;
		}
		return sf::Color(255, 255, 255);
	}


	HSB::~HSB()
	{
	}
}
