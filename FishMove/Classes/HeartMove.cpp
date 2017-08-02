//
//  HeartMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

#include "HeartMove.h"
const float heart_size = 200;

Point HeartMove::getPosByTheta(float theta) {
    Point pos = Point::ZERO;
    pos.x = _origin.x + heart_size*(1-sinf(_theta))*cosf(_theta);
    pos.y = _origin.y + heart_size*(1-sinf(_theta))*sinf(_theta);
    return pos;
}
