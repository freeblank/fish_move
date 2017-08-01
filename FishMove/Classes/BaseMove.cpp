//
//  BaseMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

#include "BaseMove.h"

Point BaseMove::next(float delta, bool fix) {
    float dis = (_calcPos.x-_curPos.x)*(_calcPos.x-_curPos.x) + (_calcPos.y-_curPos.y)*(_calcPos.y-_curPos.y);
    if (fabsf(delta) > 0.001) {
        if (dis < move_dis_min) {
            return next(0.5f * fabsf(delta), true);
        } else if (dis > move_dis_max) {
            return next(-0.5f * fabsf(delta), true);
        }
    }
    
    _prePos = _curPos;
    _curPos = _calcPos;
    return _curPos;
}

float BaseMove::getAngle() {
    Point dir = Vec2(_curPos.x-_prePos.x, _curPos.y-_prePos.y);
    
    if (fabs(dir.x) < 0.0001) {
        return dir.y>0 ? 90 : 270;
    } else if (fabs(dir.y) < 0.0001) {
        return dir.x>0 ? 0 : 180;
    } else {
        return (float)(atan2f(dir.y, dir.x)*180.0f/M_PI);
    }
}
