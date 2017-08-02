//
//  LemniscateMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/3.
//
//

#include "LemniscateMove.h"

const float lemniscate_size = 500;


bool LemniscateMove::setTotalTime(float time) {
    if (!BaseMove::setTotalTime(time)) return false;
    
    _step = M_PI/_totalTime;
    return true;
}

Point LemniscateMove::getPosByTheta(float theta) {
    Point pos = Point::ZERO;
    float r = lemniscate_size*sqrtf(cosf(theta*2));
    pos.x = _origin.x + r*cosf(_theta);
    pos.y = _origin.y + r*sinf(_theta);
    return pos;
}

Point LemniscateMove::next(float delta, bool fix) {
    _theta += _step*delta;
    
    if (_theta >= 2*M_PI) {
        _prePos = _curPos;
        _curPos = _origin;
        
        return _curPos;
    }
    
    
    if (_theta>=M_PI/4 && _theta<=M_PI*3/4) {
        _calcPos = _origin;
    } else {
        _calcPos = getPosByTheta(_theta);
    }
    
    _curPos = BaseMove::next(delta, fix);
    
    
    if (_theta>=M_PI/4 && _theta<=M_PI*3/4) {
        if (_step > 0) {
            _theta = M_PI*5/4;
        } else {
            _theta = M_PI*7/4;
        }
        _step = _step*-1;
    }

    return _curPos;
}
