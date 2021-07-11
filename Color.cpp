//1F
// Created by 董宸 on 2021/6/19.
//

#include "Color.h"

#include "Utility.h"


// Solid red. RGBA is (1, 0, 0, 1).
const Color Color::red(1.F, 0.F, 0.F, 1.F);
// Solid green. RGBA is (0, 1, 0, 1).
const Color Color::green(0.F, 1.F, 0.F, 1.F);
// Solid blue. RGBA is (0, 0, 1, 1).
const Color Color::blue(0.F, 0.F, 1.F, 1.F);
// Solid white. RGBA is (1, 1, 1, 1).
const Color Color::white(1.F, 1.F, 1.F, 1.F);
// Solid black. RGBA is (0, 0, 0, 1).
const Color Color::black(0.F, 0.F, 0.F, 1.F);
// Yellow. RGBA is (1, 0.92, 0.016, 1), but the color is nice to look at!
const Color Color::yellow(1.F, 235.F / 255.F, 4.F / 255.F, 1.F);
// Cyan. RGBA is (0, 1, 1, 1).
const Color Color::cyan(0.F, 1.F, 1.F, 1.F);
// Magenta. RGBA is (1, 0, 1, 1).
const Color Color::magenta(1.F, 0.F, 1.F, 1.F);
// Gray. RGBA is (0.5, 0.5, 0.5, 1).
const Color Color::gray(.5F, .5F, .5F, 1.F);
// English spelling for ::ref::gray. RGBA is the same (0.5, 0.5, 0.5, 1).
const Color Color::grey(.5F, .5F, .5F, 1.F);
// Completely transparent. RGBA is (0, 0, 0, 0).
const Color Color::clear(0.F, 0.F, 0.F, 0.F);

float Color::grayscale() const
{
	return 0.299F * r + 0.587F * g + 0.114F * b;
}

Color Color::operator+(Color other) const
{
	return {r + other.r, g + other.g, b + other.b, a + other.a};
}

Color Color::operator-(Color other) const
{
	return {r - other.r, g - other.g, b - other.b, a - other.a};
}

Color Color::operator*(Color other) const
{
	return {r * other.r, g * other.g, b * other.b, a * other.a};
}

Color Color::operator*(float other) const
{
	return {r * other, g * other, b * other, a * other};
}

Color Color::operator/(float b) const
{
	return {r / b, g / b, b / b, a / b};
}

bool Color::operator==(Color rhs) const
{
	// Returns false in the presence of NaN values.
	return r == rhs.r &&
		g == rhs.g &&
		b == rhs.b &&
		a == rhs.a;
}

bool Color::operator!=(Color rhs) const
{
	// Returns true in the presence of NaN values.
	return !(*this == rhs);
}

Color Color::Lerp(Color a, Color b, float t)
{
	t = Math::Clamp01(t);
	return Color(
		a.r + (b.r - a.r) * t,
		a.g + (b.g - a.g) * t,
		a.b + (b.b - a.b) * t,
		a.a + (b.a - a.a) * t
	);
}

Color Color::LerpUnclamped(Color a, Color b, float t)
{
	return {
		a.r + (b.r - a.r) * t,
		a.g + (b.g - a.g) * t,
		a.b + (b.b - a.b) * t,
		a.a + (b.a - a.a) * t
	};
}

Color Color::linear() const
{
	return Color(Math::GammaToLinearSpace(r), Math::GammaToLinearSpace(g), Math::GammaToLinearSpace(b), a);
}

Color Color::gamma() const
{
	return Color(Math::LinearToGammaSpace(r), Math::LinearToGammaSpace(g), Math::LinearToGammaSpace(b), a);
}

float Color::maxColorComponent() const
{
	return Math::Max(Math::Max(r, g), b);
}

float& Color::operator[](int index)
{
	ASSERT(index == 0 || index == 1 || index == 2 || index == 3, "Color index is error !!");
	switch (index)
	{
	case 0: return r;
	case 1: return g;
	case 2: return b;
	case 3: return a;
	default:
		break;
	}
	return r;
}

void Color::RGBToHSV(Color rgbColor, float& H, float& S, float& V)
{
	// when blue is highest valued
	if ((rgbColor.b > rgbColor.g) && (rgbColor.b > rgbColor.r))
		RGBToHSVHelper((float)4, rgbColor.b, rgbColor.r, rgbColor.g, H, S, V);
		//when green is highest valued
	else if (rgbColor.g > rgbColor.r)
		RGBToHSVHelper((float)2, rgbColor.g, rgbColor.b, rgbColor.r, H, S, V);
		//when red is highest valued
	else
		RGBToHSVHelper((float)0, rgbColor.r, rgbColor.g, rgbColor.b, H, S, V);
}

void Color::RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, float& H, float& S, float& V)
{
	V = dominantcolor;
	//we need to find out which is the minimum color
	if (V != 0)
	{
		//we check which color is smallest
		float small = 0;
		if (colorone > colortwo) small = colortwo;
		else small = colorone;

		float diff = V - small;

		//if the two values are not the same, we compute the like this
		if (diff != 0)
		{
			//S = max-min/max
			S = diff / V;
			//H = hue is offset by X, and is the difference between the two smallest colors
			H = offset + ((colorone - colortwo) / diff);
		}
		else
		{
			//S = 0 when the difference is zero
			S = 0;
			//H = 4 + (R-G) hue is offset by 4 when blue, and is the difference between the two smallest colors
			H = offset + (colorone - colortwo);
		}

		H /= 6;

		//conversion values
		if (H < 0)
		{
			H += 1.0f;
		}
	}
	else
	{
		S = 0;
		H = 0;
	}
}

Color Color::HSVToRGB(float H, float S, float V)
{
	return HSVToRGB(H, S, V, true);
}

Color Color::HSVToRGB(float H, float S, float V, bool hdr)
{
	Color retval = white;
	if (S == 0)
	{
		retval.r = V;
		retval.g = V;
		retval.b = V;
	}
	else if (V == 0)
	{
		retval.r = 0;
		retval.g = 0;
		retval.b = 0;
	}
	else
	{
		retval.r = 0;
		retval.g = 0;
		retval.b = 0;

		//crazy hsv conversion
		float t_S, t_V, h_to_floor;

		t_S = S;
		t_V = V;
		h_to_floor = H * 6.0f;

		int temp = (int)Math::Floor(h_to_floor);
		float t = h_to_floor - ((float)temp);
		float var_1 = (t_V) * (1 - t_S);
		float var_2 = t_V * (1 - t_S * t);
		float var_3 = t_V * (1 - t_S * (1 - t));

		switch (temp)
		{
		case 0:
			retval.r = t_V;
			retval.g = var_3;
			retval.b = var_1;
			break;

		case 1:
			retval.r = var_2;
			retval.g = t_V;
			retval.b = var_1;
			break;

		case 2:
			retval.r = var_1;
			retval.g = t_V;
			retval.b = var_3;
			break;

		case 3:
			retval.r = var_1;
			retval.g = var_2;
			retval.b = t_V;
			break;

		case 4:
			retval.r = var_3;
			retval.g = var_1;
			retval.b = t_V;
			break;

		case 5:
			retval.r = t_V;
			retval.g = var_1;
			retval.b = var_2;
			break;

		case 6:
			retval.r = t_V;
			retval.g = var_3;
			retval.b = var_1;
			break;

		case -1:
			retval.r = t_V;
			retval.g = var_1;
			retval.b = var_2;
			break;
		}

		if (!hdr)
		{
			retval.r = Math::Clamp(retval.r, 0.0f, 1.0f);
			retval.g = Math::Clamp(retval.g, 0.0f, 1.0f);
			retval.b = Math::Clamp(retval.b, 0.0f, 1.0f);
		}
	}
	return retval;
}

Color Color::RGBMultiplied(float multiplier) const
{
	return Color(r * multiplier, g * multiplier, b * multiplier, a);
}

Color Color::AlphaMultiplied(float multiplier) const
{
	return Color(r, g, b, a * multiplier);
}

Color Color::RGBMultiplied(Color multiplier) const
{
	return Color(r * multiplier.r, g * multiplier.g, b * multiplier.b, a);
}
