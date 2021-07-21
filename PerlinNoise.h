//
// Created by 董宸 on 2021/6/19.
//

#pragma once

#include "3d-math_API.h"

class _3d_math_API PerlinNoise {
public:
	static float Noise(float x, float y);

    static float NoiseNormalized(float x, float y)
    {
        //-0.697 - 0.795 + 0.697
        float value = Noise(x, y);
        value = (value + 0.69F) / (0.793F + 0.69F);
        return value;
    }

private:
    static int p[];

	static float fade(float t);
	
	static float lerp(float t, float a, float b);

	static float grad(int hash, float x, float y, float z);

	static float grad2(int hash, float x, float y);
};



