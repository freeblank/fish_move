//
//  StraightLineMove.h
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#ifndef StraightLineMove_h
#define StraightLineMove_h

#include <stdio.h>
#include "BaseMove.h"

class StraightLineMove : public BaseMove {
public:
    virtual void setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);
    virtual bool isEnd();
    
    virtual void setPoints(const std::vector<Point> &points);
private:
    Point _pos[2];
    Point _step;
};

#endif /* StraightLineMove_h */
