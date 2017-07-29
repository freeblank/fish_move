//
//  FishManager.h
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//  All fish will create or remove by FishManager. the fish will not remove when it was deleted, just invisible, and reuse when need a fish.
//

#ifndef FishManager_h
#define FishManager_h

#include <stdio.h>
#include "FishSprite.h"

using namespace cocos2d;

class FishManager {
public:
    static FishManager* getInstance();
    
    FishManager();
    ~FishManager();
    
    FishSprite* addFish(FishType type=FishType_Small);
    void removeFish(FishSprite *fish);
    void removeAllFish();
    
private:
    std::vector<FishSprite *> _fishes;
};

#endif /* FishManager_h */
