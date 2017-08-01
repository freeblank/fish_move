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
    _layerFish = nullptr;
    
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

void FishManager::setLayer(cocos2d::Layer *layer) {
    _layerFish = layer;
}

FishSprite* FishManager::addFish(FishType type) {
    FishSprite *i_fish = nullptr;
    
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        if (!(*it)->lockForEditor && (*it)->getFishType() == type && !(*it)->isVisible()) {
            i_fish = *it;
            break;
        }
    }
    if (!i_fish) {
        i_fish = FishSprite::create();
        i_fish->retain();
        _fishes.push_back(i_fish);
        
        i_fish->setType(type);
        if (_layerFish) {
            _layerFish->addChild(i_fish);
        }
    }
    
    i_fish->setVisible(true);
    
    return i_fish;
}

void FishManager::removeFish(FishSprite *fish) {
    if (!fish) return;
    
    fish->setVisible(false);
}

void FishManager::removeAllFish() {
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        if (!(*it)->lockForEditor) {
            (*it)->setVisible(false);
        }
    }
}

void FishManager::lockAllFishesForEditor() {
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        if ((*it)->isVisible()) {
            (*it)->lockForEditor = true;
            (*it)->setVisible(false);
        }
    }
}

void FishManager::unlockAllFishes() {
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        if ((*it)->lockForEditor) {
            (*it)->lockForEditor = false;
            (*it)->setVisible(true);
        }
    }
}


void FishManager::updateMove(float delta) {
    for (std::vector<FishSprite *>::iterator it=_fishes.begin(); it!=_fishes.end(); ++it) {
        FishSprite *fish = *it;
        if (!fish->isVisible()) continue;
        
        fish->updateMove(delta);
        if (fish->isEnd()) {
            removeFish(fish);
        }
    }
}

const std::string FishManager::getMoveTypeKey(MoveType type) {
    std::stringstream ss_key;
    ss_key<<"Point_"<<type;
    
    return ss_key.str();
}

void FishManager::loadPoints(MoveType type, std::vector<Point> &points) {
    if (type==MoveType_Null) return;
    
    points.clear();
    
    const std::string i_key = FishManager::getInstance()->getMoveTypeKey(type);
    std::string str_value = UserDefault::getInstance()->getStringForKey(i_key.c_str());
    
    std::stringstream ss_value(str_value);
    std::string i_temp;
    std::string pos_x = "";
    std::string pos_y = "";
    while (ss_value>>pos_x>>pos_y) {
        Point pos;
        pos.x = atof(pos_x.c_str());
        pos.y = atof(pos_y.c_str());
        
        points.push_back(pos);
        pos_x = "";
        pos_y = "";
    }
    
    if (points.size() <= 0)
    {
        points.push_back(Vec2(200, 320));
        points.push_back(Vec2(700, 320));
    }
}

void FishManager::savePoints(MoveType type, const std::vector<Point> &points) {
    if (type==MoveType_Null) return;
    
    std::string i_key = FishManager::getInstance()->getMoveTypeKey(type);
    if (points.size()<=0) {
        UserDefault::getInstance()->setStringForKey(i_key.c_str(), "");
        return;
    }
    
    std::stringstream ss_value;
    for (std::vector<Point>::const_iterator it=points.begin(); it!=points.end(); ++it) {
        ss_value<<(*it).x<<" "<<(*it).y<<" ";
    }
    
    UserDefault::getInstance()->setStringForKey(i_key.c_str(), ss_value.str().c_str());
}
