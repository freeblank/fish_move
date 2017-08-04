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
#include "PolarMove.h"

class HeartMove : public PolarMove {
protected:
    virtual float getRadius(float theta);
};

#endif /* HeartMove_h */
