//
//  BezierCurveMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/30.
//
//

#include "BezierCurveMove.h"

void BezierCurveMove::setTotalTime(float time) {
    if (time <= 0) return;
    
    _totalTime = time;
    step = 1.0/_totalTime;
}

Point BezierCurveMove::next(float delta, bool fix) {
    _curTime += step*delta;
    
    int n = (int)_points.size()-1;
    if (_curTime >= 1) {
        _prePos = _curPos;
        _curPos = _points[n];
        return _curPos;
    }
    
    float k1 = powf(1-_curTime, n);    //(1-t)^(n-i)
    float k2 = 1;                            //t^i
    
    _calcPos = Point::ZERO;
    _calcPos.x = 0;
    _calcPos.y = 0;
    for (int i=0; i<=n; ++i) {
        float k = getCombination(i)*k1*k2;
        _calcPos.x += k*_points[i].x;
        _calcPos.y += k*_points[i].y;
        
        k1 /= (1-_curTime);
        k2 *= _curTime;
    }
    
    return BaseMove::next(delta);
}

bool BezierCurveMove::isEnd() {
    return _curTime>1;
}

void BezierCurveMove::setPoints(const std::vector<Point> &points) {
    _points = points;
    
    _prePos = _points[0];
    _curPos = _points[0];
    _curTime = 0;
    
    setTotalTime(_totalTime);
    next(1.0/60);
}

float BezierCurveMove::getCombination(int i) {
    if (_points.size()<2 || i>=_points.size() || i<0) return -1;
    
    if (_combinations.size() <= 0) {
        int n = (int)_points.size()-1;
        float i_combination = 1;
        _combinations.push_back(i_combination);
        for (int k=0; k<=n; ++k)
        {
            i_combination *= 1.0f*(n-k)/(k+1);
            _combinations.push_back(i_combination);
        }
    }
    
    return _combinations[i];
}
