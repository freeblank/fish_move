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

class BaseMove {
public:
    BaseMove() { _totalTime = 10; _curPos = Vec2::ZERO; }
    virtual ~BaseMove() {}
    
    // the total time fish move along with the path from began to end will cost
    virtual void setTotalTime(float time) = 0;
    
    // the fish will move to the point at next step
    virtual Point next(float delta) = 0;
    
    // get the fish current position
    virtual Point getCurPos() { return _curPos; }
    
    // get angle of director the fish current move
    virtual float getAngle() = 0;
    
    // check if the fish move at the end of path
    virtual bool isEnd() = 0;
    
protected:
    float _totalTime;
    Point _curPos;
};

#endif /* BaseMove_h */
