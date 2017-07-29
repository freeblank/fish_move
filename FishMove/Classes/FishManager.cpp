//
//  FishManager.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "FishManager.h"

static FishManager* s_shareFileManager = nullptr;

FishManager* FishManager::getInstance() {
    if (!s_shareFileManager) {
        s_shareFileManager = new FishManager();
    }
    
    return s_shareFileManager;
}

FishManager::FishManager() {
    _fishes.clear();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish.plist", "fish.png");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("fish2.plist", "fish2.png");
}

FishManager::~FishManager() {
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        (*it)->removeFromParent();
        (*it)->release();
    }
    
    _fishes.clear();
}

FishSprite* FishManager::addFish(FishType type) {
    FishSprite *i_fish = nullptr;
    
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        if ((*it)->getFishType() == type and !(*it)->isVisible()) {
            i_fish = *it;
            break;
        }
    }
    if (!i_fish) {
        i_fish = FishSprite::create();
        i_fish->retain();
        i_fish->setType(type);
    }
    
    return i_fish;
}

void FishManager::removeFish(FishSprite *fish) {
    if (!fish) return;
    
    fish->removeFromParent();
    fish->setVisible(false);
}

void FishManager::removeAllFish() {
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        (*it)->removeFromParent();
        (*it)->setVisible(false);
    }
}
