//
//  HeartMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/2.
//
//

#ifndef HeartMove_h
#define HeartMove_h

#include <stdio.h>
#include "ParamtricMove.h"

class HeartMove : public ParamtricMove {
protected:
    virtual Point getPosByTheta(float theta);
};

#endif /* HeartMove_h */
