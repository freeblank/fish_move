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

typedef enum _move_type
{
    MoveType_Null = 0,
    MoveType_StraightLine,
    MoveType_Lagrange,
    MoveType_Bezier,
    MoveType_Polar,
    MoveType_Heart,
    MoveType_Lemniscate,
    MoveType_Spiral,
    MoveType_Rose
} MoveType;

class FishManager {
public:
    static FishManager* getInstance();
    
    FishManager();
    ~FishManager();
    
    void setLayer(Layer *layer);
    
    FishSprite* addFish(FishType type=FishType_Small);
    void removeFish(FishSprite *fish);
    void removeAllFish();
    
    void lockAllFishesForEditor();
    void unlockAllFishes();
    
    void updateMove(float delta);
    const std::string getMoveTypeKey(MoveType type);
    void loadPoints(MoveType type, std::vector<Point> &points);
    void savePoints(MoveType type, const std::vector<Point> &points);
    
private:
    std::vector<FishSprite *> _fishes;
    Layer *_layerFish;
};

#endif /* FishManager_h */
