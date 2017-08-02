//
//  BezierCurveMove.h
//  FishMove
//
//  Created by FreeBlank on 17/7/30.
//
//

#ifndef BezierCurveMove_h
#define BezierCurveMove_h

#include <stdio.h>
#include "BaseMove.h"

class BezierCurveMove : public BaseMove {
public:
    BezierCurveMove();
    virtual bool setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);
    virtual bool isEnd();
    
    virtual void setPoints(const std::vector<Point> &points);
    
private:
    float getCombination(int i);

private:
    std::vector<Point> _points;
    float _step;
    float _curTime;
    std::vector<float> _combinations;
};

#endif /* BezierCurveMove_h */
