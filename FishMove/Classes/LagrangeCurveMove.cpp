//
//  LagrangeCurveMove.cpp
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

#include "LagrangeCurveMove.h"

bool LagrangeCurveMove::setTotalTime(float time) {
    if (!BaseMove::setTotalTime(time)) return false;
    
    if (_points.size()<2) return false;
    
    _step = (_points[_points.size()-1].x-_points[0].x)/_totalTime;
    return true;
}

Point LagrangeCurveMove::next(float delta, bool fix) {
    if (not fix) {
        _calcPos.x = _curPos.x;
    }
    _calcPos.x += _step*delta;
    
    if ((_points[0].x-_points[_points.size()-1].x)*(_calcPos.x-_points[_points.size()-1].x)<=0) {
        _prePos = _curPos;
        _curPos = _points[_points.size()-1];
        
        return _curPos;
    }
    
    _calcPos.y = 0;
    float i_total_numerator = 1;
    float k = _points.size();
    for (int j=0; j<k; ++j) {
        i_total_numerator *= (_calcPos.x-_points[j].x);
    }
    
    float i_total_denominator = 1;
    for (int j=0; j<_points.size(); ++j) {
        i_total_denominator = 1;
        for (int i=0; i<_points.size(); ++i) {
            if (i == j) continue;
            i_total_denominator *= (_points[j].x-_points[i].x);
        }
        _calcPos.y += _points[j].y*i_total_numerator/(_calcPos.x-_points[j].x)/i_total_denominator;
    }
    
    return BaseMove::next(delta, fix);
}

bool LagrangeCurveMove::isEnd() {
    return (_points[0].x-_points[_points.size()-1].x)*(_curPos.x-_points[_points.size()-1].x)<=0;
}

void LagrangeCurveMove::setPoints(const std::vector<Point> &points) {
    if (points.size() <= 1) return;

    _points.clear();
    _points.push_back(points[0]);
    float i_delta_x = (points[points.size()-1].x-points[0].x);
    for (std::vector<Point>::const_iterator it=points.begin()+1; it!=points.end(); ++it) {
        std::vector<Point>::reverse_iterator it_new = _points.rbegin();
        for (; it_new!=_points.rend(); ++it_new) {
            if (((*it_new).x-(*it).x)*i_delta_x <= 0)
            {
                _points.insert(it_new.base(), *it);
                break;
            }
        }
        if (it_new == _points.rend()) {
            _points.insert(it_new.base(), *it);
        }
    }
    
    _prePos = _points[0];
    _curPos = _points[0];
    
    setTotalTime(_totalTime);
}

