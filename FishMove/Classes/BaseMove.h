//
//  BaseMove.h
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//  control the fish to move, update position, change director and so on. it's abstract class, you need inheritance and implement the functions to order the fish how to update.
//

#ifndef BaseMove_h
#define BaseMove_h

#include <stdio.h>
using namespace cocos2d;

const float move_dis_min = 2;
const float move_dis_max = 5;

class BaseMove {
public:
    BaseMove() { _totalTime = 10; _curPos = Vec2::ZERO; _prePos = Vec2::ZERO; _firstDis = 0; }
    virtual ~BaseMove() {}
    
    // the total time fish move along with the path from began to end will cost
    virtual void setTotalTime(float time) = 0;
    
    // the fish will move to the point at next step
    virtual Point next(float delta, bool fix=false);
    
    // get the fish current position
    virtual Point getCurPos() { return _curPos; }
    
    // get angle of director the fish current move
    virtual float getAngle();
    
    // check if the fish move at the end of path
    virtual bool isEnd() = 0;
    
protected:
    float _totalTime;
    Point _curPos;
    Point _calcPos;
    Point _prePos;
    float _firstDis;
};

#endif /* BaseMove_h */
