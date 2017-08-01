//
//  LagrangeCurveMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

#ifndef LagrangeCurveMove_h
#define LagrangeCurveMove_h

#include <stdio.h>
#include "BaseMove.h"

class LagrangeCurveMove : public BaseMove {
public:
    virtual void setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);
    virtual bool isEnd();
    
    virtual void setPoints(const std::vector<Point> &points);
    
private:
    float getCombination(int i);
    
private:
    std::vector<Point> _points;
    float step;
    float _curTime;
};

#endif /* LagrangeCurveMove_h */
