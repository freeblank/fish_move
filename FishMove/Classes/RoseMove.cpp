//
//  RoseMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/5.
//
//

#include "RoseMove.h"
const float rose_size = 350;

float RoseMove::getRadius(float theta) {
    return rose_size*sinf(theta*2);
}
