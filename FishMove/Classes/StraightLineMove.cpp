//
//  StraightLineMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "StraightLineMove.h"

void StraightLineMove::setTotalTime(float time) {
    if (time <= 0) return;
    
    _totalTime = time;
    if (_pos[1].x==_pos[0].x && _pos[1].y==_pos[1].y) return;
    
    _step.x = 1.0/_totalTime*(_pos[1].x-_pos[0].x);
    _step.y = 1.0/_totalTime*(_pos[1].y-_pos[0].y);
}

Point StraightLineMove::next(float delta) {
    _curPos.x += _step.x*delta;
    _curPos.y += _step.y*delta;
    
    return _curPos;
}

float StraightLineMove::getAngle() {
    Point dir = Point(_pos[1].x-_pos[0].x, _pos[1].y-_pos[0].y);
    if (fabs(dir.x) < 0.0001) {
        return dir.y>0 ? 90 : 270;
    } else if (fabs(dir.y) < 0.0001) {
        return dir.x>0 ? 0 : 180;
    } else {
        return (float)(atan2f(dir.y, dir.x)*180.0f/M_PI);
    }
}

bool StraightLineMove::isEnd() {
    return (_pos[0].x-_pos[1].x)*(_curPos.x-_pos[1].x)<0 || (_pos[0].y-_pos[1].y)*(_curPos.y-_pos[1].y)<0;
}

void StraightLineMove::setPoints(const std::vector<Point> &points) {
    if (points.size() < 2) return;
    
    _pos[0] = points[0];
    _pos[1] = points[1];
    
    _curPos = _pos[0];
    
    setTotalTime(_totalTime);
}
