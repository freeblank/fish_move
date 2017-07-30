//
//  FishLayer.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "FishLayer.h"


bool FishLayer::init()
{
    if (!Layer::init()) return false;
    
    FishManager::getInstance()->setLayer(this);
    
    addEventListener();
    scheduleUpdate();
    
    _editable = false;
    return true;
}

void FishLayer::addEventListener() {
    _eventDispatcher->addCustomEventListener("Editor_Finish", [=](EventCustom* event){
        MoveType i_type = (MoveType)(*((int*)event->getUserData()));
        onEditorFinish(i_type);
        
        _editable = false;
    });
    
    _eventDispatcher->addCustomEventListener("Editor_Finish_No_Change", [=](EventCustom* event){
        if (_fishCreators.size() <= 0) {
            MoveType i_type = (MoveType)(*((int*)event->getUserData()));
            onEditorFinish(i_type);
        }
        
        _editable = false;
    });
    
}

void FishLayer::update(float delta) {
    Layer::update(delta);
    
    if (_editable) return;
    
    FishManager::getInstance()->updateMove(delta);
    for (std::vector<FishCreator *>::iterator it=_fishCreators.begin(); it!=_fishCreators.end(); ++it) {
        (*it)->update();
    }
}

void FishLayer::onEditorFinish(MoveType type) {
    FishCreator *fishCreator = new FishCreator(type, -1);
    _fishCreators.push_back(fishCreator);
}

void FishLayer::clear() {
    FishManager::getInstance()->removeAllFish();
    
    for (std::vector<FishCreator *>::iterator it=_fishCreators.begin(); it!=_fishCreators.end();) {
        delete (*it);
        
        it = _fishCreators.erase(it);
    }
    _fishCreators.clear();
}


