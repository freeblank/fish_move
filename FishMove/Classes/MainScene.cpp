//
//  MainScene.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/28.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"


bool MainScene::init() {
    if (!Scene::init())
    {
        return false;
    }
    
    initUI();
    
    
    return true;
}

void MainScene::initUI() {
    Sprite *i_bg = Sprite::create("bg.jpg");
    i_bg->setAnchorPoint(Vec2(0, 0));
    i_bg->setPosition(Vec2(0, 0));
    addChild(i_bg, 0);
    
    ui::Button *i_button = Button::create("button1.png");
    i_button->setScale9Enabled(true);
    i_button->setCapInsets(Rect(10, 10, 230, 38));
    i_button->setContentSize(Size(100, 50));
    i_button->setTitleFontSize(30);
    i_button->addClickEventListener([=](Ref*){
        if (fishLayer) {
            fishLayer->setEditable(true);
        }
        if (editorLayer) {
            editorLayer->show(true);
        }
    });
    i_button->setTitleText("Editor");
    
    i_button->setPosition(Vec2(1070, 600));
    i_button->setTitleColor(Color3B::BLACK);
    addChild(i_button, 0);
    
    i_button = Button::create("button1.png");
    i_button->setScale9Enabled(true);
    i_button->setCapInsets(Rect(10, 10, 230, 38));
    i_button->setContentSize(Size(100, 50));
    i_button->setTitleFontSize(30);
    i_button->addClickEventListener([=](Ref*){
        if (fishLayer) {
            fishLayer->clear();
        }
    });
    i_button->setTitleText("Clear");
    
    i_button->setPosition(Vec2(950, 600));
    i_button->setTitleColor(Color3B::BLACK);
    addChild(i_button, 0);
    
    fishLayer = FishLayer::create();
    addChild(fishLayer, 2);
    
    editorLayer = EditorLayer::create();
    addChild(editorLayer, 1);
    editorLayer->setVisible(false);
    
}
