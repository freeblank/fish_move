//
//  ParamtricMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/3.
//
//

#ifndef ParamtricMove_h
#define ParamtricMove_h

#include <stdio.h>
#include "BaseMove.h"

class ParamtricMove : public BaseMove {
public:
    ParamtricMove();
    virtual bool setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);
    virtual bool isEnd();
    
    virtual void setOrigin(Vec2 origin);
    
protected:
    virtual Point getPosByTheta(float theta) = 0;
    
protected:
    Vec2 _origin;
    float _step;
    float _theta;
};

#endif /* ParamtricMove_h */
