//
//  FishLayer.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "FishLayer.h"
#include "FishManager.h"

bool FishLayer::init()
{
    if (!Layer::init()) return false;
    
    FishSprite* i_fish = FishManager::getInstance()->addFish();
    i_fish->setPosition(Vec2(200, 200));
    addChild(i_fish);
    return true;
}

void FishLayer::addEventListener() {
    _eventDispatcher->addCustomEventListener("Editor_Update_Move", [=](EventCustom * custom){
        onUpdateMove((BaseMove *)custom->getUserData());
    });
    
    _eventDispatcher->addCustomEventListener("Editor_Finish", [=](EventCustom*){
        onEditorFinish();
    });
}

void FishLayer::update(float delta) {
    Layer::update(delta);
    
    if (!_editable) return;
}

void FishLayer::onUpdateMove(BaseMove *move) {
    _move = move;
    
    //TODO update move
}

void FishLayer::onEditorFinish() {
    
}
