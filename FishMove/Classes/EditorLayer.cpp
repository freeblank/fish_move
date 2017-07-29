//
//  EditorLayer.cpp
//  FishMove
//
//  Created by pClass on 17/7/29.
//
//

#include "EditorLayer.h"


bool EditorLayer::init() {
    if (!LayerColor::initWithColor(Color4B::BLACK)) return false;
    
    initUI();
    return true;
}

void EditorLayer::initUI() {
    float i_x = 1020;
    float i_y = 40;
    float i_step = 100;
    Button *i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_StraightLine);
    i_button->setTitleText("StraightLine");
    this->addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Lagrange);
    i_button->setTitleText("Lagrange");
    this->addChild(i_button);
    i_y += i_step;
    
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Bezier);
    i_button->setTitleText("Bezier");
    this->addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Paramtric);
    i_button->setTitleText("Paramtric");
    this->addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Polar);
    i_button->setTitleText("Polar");
    this->addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Yellow);
    i_button->setPosition(Vec2(800, 40));
    i_button->setTitleText("Finish");
    i_button->addClickEventListener([=](Ref*){
        this->setVisible(false);
    });
    this->addChild(i_button);
    
    this->onClickButton(Button_StraightLine);
}

Button* EditorLayer::createButton(ButtonType type) {
    std::stringstream ss;
    ss << "button" << type << ".png";
    log("%s, %d\n", ss.str().c_str(), type);
    
    Button *i_button = Button::create(ss.str().c_str());
    i_button->setTitleColor(Color3B::BLACK);
    i_button->setTitleFontSize(30);
    
    i_button->setScale9Enabled(true);
    i_button->setCapInsets(Rect(10, 10, 230, 38));
    i_button->setContentSize(Size(200, 50));
    
    if (type == Button_Blue)
    {
        i_button->addClickEventListener([=](Ref *ref){
            Button* button = dynamic_cast<Button *>(ref);
            this->onClickButton((ButtonTag)button->getTag());
        });
    }
    return i_button;
}

void EditorLayer::onClickButton(ButtonTag tag) {
    this->_selectTag = tag;
    
    //hide all button
    showPolar(false);
    showParamtric(false);
    
    switch (tag) {
        case Button_StraightLine:
            break;
        case Button_Lagrange:
            break;
        case Button_Bezier:
            break;
        case Button_Paramtric:
            showParamtric(true);
            break;
        case Button_Polar:
            showPolar(true);
            break;
        default:
            break;
    }
}

void EditorLayer::showPolar(bool show) {
    
}

void EditorLayer::showParamtric(bool show) {
    
}






