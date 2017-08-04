//
//  SpiralMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/5.
//
//

#include "SpiralMove.h"

const float spiral_size = 12;

bool SpiralMove::isEnd() {
    return _theta >= 10*M_PI;
}

float SpiralMove::getRadius(float theta) {
    return spiral_size*_theta;
}
