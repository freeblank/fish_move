//
//  EditorLayer.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "EditorLayer.h"


bool EditorLayer::init() {
    if (!LayerColor::initWithColor(Color4B::BLACK)) return false;
    
    _selectTag = Button_Null;
    
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
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Lagrange);
    i_button->setTitleText("Lagrange");
    addChild(i_button);
    i_y += i_step;
    
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Bezier);
    i_button->setTitleText("Bezier");
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Paramtric);
    i_button->setTitleText("Paramtric");
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(Button_Polar);
    i_button->setTitleText("Polar");
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Yellow);
    i_button->setPosition(Vec2(800, 40));
    i_button->setTitleText("Finish");
    i_button->addClickEventListener([=](Ref*){
        setVisible(false);
    });
    addChild(i_button);
    
    _layerParamtric = Layer::create();
    _layerParamtric->setAnchorPoint(Vec2::ZERO);
    _layerParamtric->setPosition(Vec2::ZERO);
    addChild(_layerParamtric, 1);
    
    _layerPolar = Layer::create();
    _layerPolar->setAnchorPoint(Vec2::ZERO);
    _layerPolar->setPosition(Vec2::ZERO);
    addChild(_layerPolar, 1);
    
    _layerPoint = Layer::create();
    _layerPoint->setAnchorPoint(Vec2::ZERO);
    _layerPoint->setPosition(Vec2::ZERO);
    addChild(_layerPoint, 2);
    
    _drawNode = DrawNode::create();
    addChild(_drawNode, 10);
    
    
    onClickButton(Button_StraightLine);
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
            onClickButton((ButtonTag)button->getTag());
        });
    }
    return i_button;
}

void EditorLayer::cleanEditor() {
    //hide all button
    showPolar(false);
    showParamtric(false);
    
    _layerPoint->removeAllChildren();
    _drawNode->clear();
}

void EditorLayer::onClickButton(ButtonTag tag) {
    _selectTag = tag;
    
    cleanEditor();
    
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
    
    loadPoints();
    for (int i=0; i<_points.size(); ++i) {
        addPoint(_points[i], i);
    }
}

void EditorLayer::showPolar(bool show) {
    
}

void EditorLayer::showParamtric(bool show) {
    
}

void EditorLayer::movePoint(Button *button, Vec2 pos) {
    button->setPosition(pos);
    _points[button->getTag()] = pos;
    
    _drawNode->clear();
    for (int i=0; i<_points.size(); ++i)
    {
        _drawNode->drawPoint(_points[i], 5, Color4F::RED);
    }
}

void EditorLayer::addPoint(Vec2 pos, int tag) {
    if (tag < 0)
    {
        tag = (int)_points.size();
        _points.push_back(pos);
    }
    _drawNode->drawPoint(pos, 5, Color4F::RED);
    
    Button *i_button = Button::create("point.png");
    i_button->setAnchorPoint(Vec2(0.5, 0.5));
    i_button->setPosition(pos);
    i_button->setScale(80);
    i_button->setTag(tag);
    i_button->setColor(Color3B::BLUE);
    i_button->setOpacity(50);
    i_button->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type) {
        Button *button = dynamic_cast<Button *>(ref);
        if (type == Widget::TouchEventType::MOVED) {
            movePoint(button, button->getTouchMovePosition());
        } else if (type == Widget::TouchEventType::ENDED) {
            movePoint(button, button->getTouchEndPosition());
            savePoints();
        }
    });
    
    _layerPoint->addChild(i_button);
}

void EditorLayer::loadPoints() {
    if (_selectTag==Button_Null) return;
    
    _points.clear();
    
    std::stringstream ss_key;
    ss_key<<"Point_"<<_selectTag;
    std::string str_value = UserDefault::getInstance()->getStringForKey(ss_key.str().c_str());
    
    std::stringstream ss_value(str_value);
    std::string i_temp;
    std::string pos_x = "";
    std::string pos_y = "";
    while (ss_value>>pos_x>>pos_y) {
        Point pos;
        pos.x = atof(pos_x.c_str());
        pos.y = atof(pos_y.c_str());
        
        _points.push_back(pos);
        pos_x = "";
        pos_y = "";
    }

    if (_points.size() <= 0)
    {
        _points.push_back(Vec2(200, 320));
        _points.push_back(Vec2(700, 320));
    }
}

void EditorLayer::savePoints() {
    if (_selectTag==Button_Null || _points.size()<=0) return;
    
    std::stringstream ss_value;
    for (std::vector<Point>::iterator it=_points.begin(); it!=_points.end(); ++it) {
        ss_value<<(*it).x<<" "<<(*it).y<<" ";
    }
    
    std::stringstream ss_key;
    ss_key<<"Point_"<<_selectTag;
    UserDefault::getInstance()->setStringForKey(ss_key.str().c_str(), ss_value.str().c_str());
}

void EditorLayer::onEnter()
{
    Layer::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(false);
    
    listener->onTouchBegan = CC_CALLBACK_2(EditorLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(EditorLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(EditorLayer::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool EditorLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cocos2d::log("onTouchBegan");
    
    if (!isVisible()) return false;
    return true;
}

void EditorLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cocos2d::log("onTouchMoved");
}

void EditorLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cocos2d::log("onTouchEnded");
}




