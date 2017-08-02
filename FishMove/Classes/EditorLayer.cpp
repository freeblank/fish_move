//
//  EditorLayer.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//

#include "EditorLayer.h"
#include "StraightLineMove.h"
#include "BezierCurveMove.h"
#include "LagrangeCurveMove.h"
#include "HeartMove.h"
#include "LemniscateMove.h"

bool EditorLayer::init() {
    if (!LayerColor::initWithColor(Color4B::BLACK)) return false;
    
    _selectMoveType = MoveType_Null;
    _move = nullptr;
    
    initUI();
    return true;
}

EditorLayer::~EditorLayer()
{
    if (_move) {
        delete _move;
        _move = nullptr;
    }
}

void EditorLayer::initUI() {
    float i_x = 150;
    float i_y = 600;
    float i_step = 210;
    Button *i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(MoveType_StraightLine);
    i_button->setTitleText("StraightLine");
    addChild(i_button);
    i_x += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(MoveType_Lagrange);
    i_button->setTitleText("Lagrange");
    addChild(i_button);
    i_x += i_step;
    
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(MoveType_Bezier);
    i_button->setTitleText("Bezier");
    addChild(i_button);
    i_x += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(i_x, i_y));
    i_button->setTag(MoveType_Paramtric);
    i_button->setTitleText("Paramtric");
    addChild(i_button);
    i_x += i_step;
    
//    i_button = createButton(Button_Blue);
//    i_button->setPosition(Vec2(i_x, i_y));
//    i_button->setTag(MoveType_Polar);
//    i_button->setTitleText("Polar");
//    addChild(i_button);
//    i_x += i_step;
    
    _layerParamtric = Layer::create();
    addChild(_layerParamtric);
    
    i_y = 0;
    i_step = 100;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(0, i_y));
    i_button->setTag(MoveType_Heart);
    i_button->setTitleText("Heart");
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(0, i_y));
    i_button->setTag(MoveType_Lemniscate);
    i_button->setTitleText("Lemniscate");
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(0, i_y));
    i_button->setTag(MoveType_Heart);
    i_button->setTitleText("Test3");
    addChild(i_button);
    i_y += i_step;
    
    i_button = createButton(Button_Blue);
    i_button->setPosition(Vec2(0, i_y));
    i_button->setTag(MoveType_Heart);
    i_button->setTitleText("Test4");
    addChild(i_button);
    i_y += i_step;
    
    
    i_button = createButton(Button_Yellow);
    i_button->setPosition(Vec2(800, 40));
    i_button->setTitleText("Reset");
    i_button->addClickEventListener([=](Ref*){
        _points.clear();
        FishManager::getInstance()->savePoints(_selectMoveType, _points);
        onClickButton(_selectMoveType);
    });
    addChild(i_button);
    
    i_button = createButton(Button_Yellow);
    i_button->setPosition(Vec2(1020, 40));
    i_button->setTitleText("Finish");
    i_button->addClickEventListener([=](Ref*){
        show(false);
        
        if (_haveChange) {
            _eventDispatcher->dispatchCustomEvent("Editor_Finish", &_selectMoveType);
        } else {
            _eventDispatcher->dispatchCustomEvent("Editor_Finish_No_Change", &_selectMoveType);
        }
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
            onClickButton((MoveType)button->getTag());
        });
    }
    return i_button;
}

void EditorLayer::show(bool i_show) {
    if (i_show) {
        _haveChange = false;
        FishManager::getInstance()->lockAllFishesForEditor();
        onClickButton(MoveType_StraightLine);
        setVisible(true);
    } else {
        FishManager::getInstance()->removeAllFish();
        FishManager::getInstance()->unlockAllFishes();
        setVisible(false);
    }
}

void EditorLayer::cleanEditor() {
    //hide all button
    showPolar(false);
    showParamtric(false);
    
    _layerPoint->removeAllChildren();
    _drawNode->clear();
}

void EditorLayer::onClickButton(MoveType tag) {
    _selectMoveType = tag;
    
    cleanEditor();
    
    switch (tag) {
        case MoveType_StraightLine:
            break;
        case MoveType_Lagrange:
            break;
        case MoveType_Bezier:
            break;
        case MoveType_Paramtric:
            showParamtric(true);
            break;
            break;
        default:
            break;
    }
    
    FishManager::getInstance()->loadPoints(_selectMoveType, _points);
    for (int i=0; i<_points.size(); ++i) {
        addPoint(_points[i], i);
    }
    refreshFishes();
}

void EditorLayer::showPolar(bool show) {
    
}

void EditorLayer::showParamtric(bool show) {
    if (_layerParamtric) {
        _layerParamtric->setVisible(show);
    }
}

void EditorLayer::refreshFishes() {
    FishManager::getInstance()->removeAllFish();
    
    if (_move) {
        delete _move;
        _move = nullptr;
    }
    
    switch (_selectMoveType) {
        case MoveType_StraightLine:
            _move = new StraightLineMove();
            dynamic_cast<StraightLineMove*>(_move)->setPoints(_points);
            break;
        case MoveType_Bezier:
            _move = new BezierCurveMove();
            dynamic_cast<BezierCurveMove*>(_move)->setPoints(_points);
            break;
        case MoveType_Lagrange:
            _move = new LagrangeCurveMove();
            dynamic_cast<LagrangeCurveMove*>(_move)->setPoints(_points);
            break;
        case MoveType_Heart:
            _move = new HeartMove();
            dynamic_cast<HeartMove*>(_move)->setOrigin(_points[0]);
            break;
        case MoveType_Lemniscate:
            _move = new LemniscateMove();
            dynamic_cast<LemniscateMove*>(_move)->setOrigin(_points[0]);
            break;
        default:
            break;
    }
    
    if (!_move) return;
    
    float i_total_time = 10;
    _move->setTotalTime(i_total_time);
    Point prePos = Point::ZERO;
    Point curPos = Point::ZERO;
    float i_dis = 0;
    while(!_move->isEnd())
    {
        FishSprite* i_fish = FishManager::getInstance()->addFish();
        i_fish->setPosition(_move->getCurPos());
        i_fish->setRotation(180-_move->getAngle());
        
        prePos = _move->getCurPos();
        do {
            _move->next(1/60.0);
            curPos = _move->getCurPos();
            i_dis = (curPos.x-prePos.x)*(curPos.x-prePos.x) + (curPos.y-prePos.y)*(curPos.y-prePos.y);
        } while (!_move->isEnd() && i_dis<5000);
    }
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
    if (tag < 0) {
        tag = (int)_points.size();
        _points.push_back(pos);
    }
    _drawNode->drawPoint(pos, 5, Color4F::RED);
    
    float button_size = 80;
    
    Button *i_button = Button::create("point.png");
    i_button->setAnchorPoint(Vec2(0.5, 0.5));
    i_button->setPosition(pos);
    i_button->setScale(button_size);
    i_button->setTag(tag);
    i_button->setColor(Color3B::BLUE);
//    i_button->setOpacity(50);
    i_button->addTouchEventListener([=](Ref* ref,Widget::TouchEventType type) {
        Button *button = dynamic_cast<Button *>(ref);
        if (type == Widget::TouchEventType::MOVED) {
            this->movePoint(button, button->getTouchMovePosition());
        } else if (type == Widget::TouchEventType::ENDED) {
            this->movePoint(button, button->getTouchEndPosition());
            FishManager::getInstance()->savePoints(_selectMoveType, _points);
            this->refreshFishes();
            
            _haveChange = true;
        }
    });
    _layerPoint->addChild(i_button);
    
    Text *i_text = Text::create();
    std::stringstream ss;
    ss<<(tag+1);
    i_text->setString(ss.str());
    i_text->setScale(1/button_size);
    i_button->addChild(i_text);
}



void EditorLayer::onEnter() {
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
    
    if (_selectMoveType == MoveType_Bezier || _selectMoveType == MoveType_Lagrange) {
        addPoint(touch->getLocation());
        
        FishManager::getInstance()->savePoints(_selectMoveType, _points);
        this->refreshFishes();
        
        _haveChange = true;
    }
    
    return true;
}

void EditorLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cocos2d::log("onTouchMoved");
}

void EditorLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    cocos2d::log("onTouchEnded");
}




