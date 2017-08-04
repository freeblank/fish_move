//
//  PolarMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/3.
//
//

#ifndef PolarMove_h
#define PolarMove_h

#include <stdio.h>
#include "BaseMove.h"

class PolarMove : public BaseMove {
public:
    PolarMove();
    virtual bool setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);
    virtual bool isEnd();
    
    virtual void setOrigin(Vec2 origin);
    
protected:
    virtual float getRadius(float theta) = 0;
    Point getPosByTheta(float theta);
    
protected:
    Vec2 _origin;
    float _step;
    float _theta;
};

#endif /* PolarMove_h */
