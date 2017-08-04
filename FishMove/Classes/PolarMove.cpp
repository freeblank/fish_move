//
//  PolarMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/3.
//
//

#include "PolarMove.h"

//
//  PolarMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

PolarMove::PolarMove() {
    _theta = 0;
    
    setTotalTime(_totalTime);
}

bool PolarMove::setTotalTime(float time) {
    if (!BaseMove::setTotalTime(time)) return false;
    
    _step = 2*M_PI/_totalTime;
    return true;
}

Point PolarMove::getPosByTheta(float theta) {
    float r = getRadius(theta);
    return Point(_origin.x+r*cosf(theta), _origin.y+r*sinf(theta));
}

Point PolarMove::next(float delta, bool fix) {
    _theta += _step*delta;
    
    _calcPos = getPosByTheta(_theta);
    
    return BaseMove::next(delta, fix);
}


bool PolarMove::isEnd() {
    return _theta >= 2*M_PI;
}

void PolarMove::setOrigin(cocos2d::Vec2 origin) {
    _origin = origin;
    
    _curPos = getPosByTheta(_theta);
    _prePos = _curPos;
}

