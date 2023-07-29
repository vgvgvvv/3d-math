//
// Created by 董宸 on 2021/6/19.
//

#pragma once

#include "MathLibAPI.h"

class MATHLIB_API Color {
public:
    // Red component of the color.
    float r;

    // Green component of the color.
    float g;

    // Blue component of the color.
    float b;

    // Alpha component of the color.
    float a;

    // Solid red. RGBA is (1, 0, 0, 1).
    static const Color red;
    // Solid green. RGBA is (0, 1, 0, 1).
    static const Color green;
    // Solid blue. RGBA is (0, 0, 1, 1).
    static const Color blue;
    // Solid white. RGBA is (1, 1, 1, 1).
    static const Color white;
    // Solid black. RGBA is (0, 0, 0, 1).
    static const Color black;
    // Yellow. RGBA is (1, 0.92, 0.016, 1), but the color is nice to look at!
    static const Color yellow;
    // Cyan. RGBA is (0, 1, 1, 1).
    static const Color cyan;
    // Magenta. RGBA is (1, 0, 1, 1).
    static const Color magenta;
    // Gray. RGBA is (0.5, 0.5, 0.5, 1).
    static const Color gray;
    // English spelling for ::ref::gray. RGBA is the same (0.5, 0.5, 0.5, 1).
    static const Color grey;
    // Completely transparent. RGBA is (0, 0, 0, 0).
    static const Color clear;

    // The grayscale value of the color (RO)
    float grayscale() const;

    Color() : r(1), g(1), b(1), a(1)
    {
	    
    }
	
    // Constructs a new Color with given r,g,b,a components.
    Color(float r, float g, float b, float a)
    {
        this->r = r; this->g = g; this->b = b; this->a = a;
    }

    // Constructs a new Color with given r,g,b components and sets /a/ to 1.
    Color(float r, float g, float b)
    {
        this->r = r; this->g = g; this->b = b; this->a = 1.0F;
    }

    /// *listonly*
    // override string ToString()
    // {
    //     return String.Format("RGBA({0:F3}, {1:F3}, {2:F3}, {3:F3})", r, g, b, a);
    // }
    //
    // // Returns a nicely formatted string of this color.
    // string ToString(string format)
    // {
    //     return String.Format("RGBA({0}, {1}, {2}, {3})", r.ToString(format), g.ToString(format), b.ToString(format), a.ToString(format));
    // }
    //
    // // used to allow Colors to be used as keys in hash tables
    // override int GetHashCode()
    // {
    //     return ((Vector4)this).GetHashCode();
    // }
    //
    // // also required for being able to use Colors as keys in hash tables
    // override bool Equals(object other)
    // {
    //     if (!(other is Color)) return false;
    //
    //     return Equals((Color)other);
    // }
    //
    // bool Equals(Color other)
    // {
    //     return r.Equals(other.r) && g.Equals(other.g) && b.Equals(other.b) && a.Equals(other.a);
    // }

    // Adds two colors together. Each component is added separately.
    Color operator+(Color other) const;

    // Subtracts color /b/ from color /a/. Each component is subtracted separately.
    Color operator-(Color other) const;

    // Multiplies two colors together. Each component is multiplied separately.
    Color operator*(Color other) const;

    // Multiplies color /a/ by the float /b/. Each color component is scaled separately.
    Color operator*(float other) const;

    // Divides color /a/ by the float /b/. Each color component is scaled separately.
    Color operator/(float b) const;

    //*undoc*
    bool operator==(Color rhs) const;

    //*undoc*
    bool operator!=(Color rhs) const;

    // Interpolates between colors /a/ and /b/ by /t/.
    static Color Lerp(Color a, Color b, float t);

    // Interpolates between colors /a/ and /b/ by /t/ without clamping the interpolant
    static Color LerpUnclamped(Color a, Color b, float t);


        // A version of the color that has had the inverse gamma curve applied
    Color linear() const;

    // A version of the color that has had the gamma curve applied
    Color gamma() const;

    float maxColorComponent() const;

    float& operator[](int index);

    // Convert a color from RGB to HSV color space.
    static void RGBToHSV(Color rgbColor, float& H, float& S, float& V);

    static void RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, float& H, float& S, float& V);

    static Color HSVToRGB(float H, float S, float V);

    // Convert a set of HSV values to an RGB Color.
    static Color HSVToRGB(float H, float S, float V, bool hdr);

private:
    // Returns new color that has RGB components multiplied, but leaving alpha untouched.
    Color RGBMultiplied(float multiplier) const;
    // Returns new color that has RGB components multiplied, but leaving alpha untouched.
    Color AlphaMultiplied(float multiplier) const;
    // Returns new color that has RGB components multiplied, but leaving alpha untouched.
    Color RGBMultiplied(Color multiplier) const;
};



