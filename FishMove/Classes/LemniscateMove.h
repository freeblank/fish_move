//
//  LemniscateMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/3.
//
//

#ifndef LemniscateMove_h
#define LemniscateMove_h

#include <stdio.h>
#include "ParamtricMove.h"

class LemniscateMove : public ParamtricMove {
public:
    virtual bool setTotalTime(float time);
    virtual Point next(float delta, bool fix=false);

protected:
    virtual Point getPosByTheta(float theta);
};

#endif /* LemniscateMove_h */
