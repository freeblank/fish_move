//
//  HeartMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

#include "HeartMove.h"
const float heart_size = 200;

float HeartMove::getRadius(float theta) {
    return heart_size*(1-sinf(_theta));
}
