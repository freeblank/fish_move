//
//  MainScene.hpp
//  FishMove
//
//  Created by pClass on 17/7/28.
//
//

#ifndef MainScene_h
#define MainScene_h

#include <stdio.h>
#include "EditorLayer.h"
#include "FishLayer.h"

using namespace cocos2d;

class MainScene : public Scene {
public:
    virtual bool init();
    void initUI();
    
    CREATE_FUNC(MainScene);
    
private:
    EditorLayer *editorLayer;
    FishLayer *fishLayer;
};

#endif /* MainScene_h */
