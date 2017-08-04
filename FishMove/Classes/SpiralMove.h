//
//  SpiralMove.h
//  FishMove
//
//  Created by FreeBlank on 17/8/5.
//
//

#ifndef SpiralMove_h
#define SpiralMove_h

#include <stdio.h>
#include "PolarMove.h"

class SpiralMove : public PolarMove {
public:
    virtual bool isEnd();
    
protected:
    virtual float getRadius(float theta);
};

#endif /* SpiralMove_h */
