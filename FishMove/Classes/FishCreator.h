//
//  FishCreator.h
//  FishMove
//
//  Created by FreeBlank on 17/7/30.
//
//

#ifndef FishCreator_h
#define FishCreator_h

#include <stdio.h>
#include "FishSprite.h"
#include "FishManager.h"

using namespace cocos2d;

class FishCreator {
public:
    FishCreator(MoveType type, int totalNum=-1);
    
    void createFish();
    void update();
    
private:
    Point _initPos;
    FishSprite *_curFish;
    MoveType _type;
    
    int _totalNum;
    int _curNum;
    
    std::vector<Point> _points;
};

#endif /* FishCreator_h */
