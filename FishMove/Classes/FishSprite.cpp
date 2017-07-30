//
//  FishSprite.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "FishSprite.h"

bool FishSprite::init() {
    if (!Sprite::init()) return false;
    
    lockForEditor = false;
    _move = nullptr;
    return true;
}

void FishSprite::setType(FishType type) {
    _type = type;
    
    char str[100] = {0};
    sprintf(str, "fish_%04d_%d_%02d.png",type/10, type%10, 0);
    
    setSpriteFrame(str);
    
    Vector<SpriteFrame*> spriteFrames;
    for (int i=0; i<100; i++) {
        sprintf(str, "fish_%04d_%d_%02d.png",type/10, type%10, i);
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        if (frame == nullptr) {
            break;
        }
        spriteFrames.pushBack(frame);
    }
    
    if (spriteFrames.size() <= 0) return;
    
    Animation *animation = Animation::createWithSpriteFrames(spriteFrames, 0.2f, true);
    runAction(RepeatForever::create(Animate::create(animation)));
}

void FishSprite::bindMove(BaseMove *move) {
    _move = move;
    setPosition(_move->getCurPos());
}

void FishSprite::updateMove(float delta) {
    if (!_move) return;
    
    _move->next(delta);
    setPosition(_move->getCurPos());
    setRotation(180-_move->getAngle());
}

bool FishSprite::isEnd() {
    if (!_move) return false;
    
    return _move->isEnd();
}
