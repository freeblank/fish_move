//
//  FishSprite.h
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//  fish create and update logic
//

#ifndef FishSprite_h
#define FishSprite_h

#include <stdio.h>

using namespace cocos2d;

//int arrType[] = {10, 20, 40, 41, 100, 200, 300, 301, 302, 500, 600, 1000, 1001};
typedef enum _fish_type {
    FishType_Small = 10,
    FishType_Normal = 20,
    FishType_Big = 40,
} FishType;

class FishSprite : public Sprite {
public:
    CREATE_FUNC(FishSprite);
    
    virtual bool init();
    void setType(FishType type);
    FishType getFishType() { return _type; }
    
private:
    FishType _type;
};

#endif /* FishSprite_h */
