//
//  ParamtricMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/3.
//
//

#include "ParamtricMove.h"

//
//  ParamtricMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

ParamtricMove::ParamtricMove() {
    _theta = 0;
    
    setTotalTime(_totalTime);
}

bool ParamtricMove::setTotalTime(float time) {
    if (!BaseMove::setTotalTime(time)) return false;
    
    _step = 2*M_PI/_totalTime;
    return true;
}

Point ParamtricMove::next(float delta, bool fix) {
    _theta += _step*delta;
    
    if (_theta >= 2*M_PI) {
        _prePos = _curPos;
        _curPos = _origin;
        
        return _curPos;
    }
    
    _calcPos = getPosByTheta(_theta);
    
    return BaseMove::next(delta, fix);
}


bool ParamtricMove::isEnd() {
    return _theta >= 2*M_PI;
}

void ParamtricMove::setOrigin(cocos2d::Vec2 origin) {
    _origin = origin;
    
    _curPos = getPosByTheta(_theta);
    _prePos = _curPos;
}

