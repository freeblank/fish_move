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
    virtual bool setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);
    virtual bool isEnd();
    
    virtual void setPoints(const std::vector<Point> &points);
    
private:
    std::vector<Point> _points;
    float _step;
    float _curTime;
};

#endif /* LagrangeCurveMove_h */
