//
//  RoseMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/5.
//
//

#ifndef RoseMove_h
#define RoseMove_h

#include <stdio.h>
#include "PolarMove.h"

class RoseMove : public PolarMove {
protected:
    virtual float getRadius(float theta);
};
#endif /* RoseMove_h */
