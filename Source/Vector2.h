//
// Created by 董宸 on 2021/6/19.
//

#ifndef SOURCE_VECTOR2_H
#define SOURCE_VECTOR2_H

class Vector2 {
public:
    float x;
    float y;

    float operator[] (int index);

    Vector2(float x, float y){
        this->x = x;
        this->y = y;
    }

};

#endif //SOURCE_VECTOR2_H
