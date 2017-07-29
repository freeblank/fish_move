//
//  EditorLayer.h
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
//  a editor to load and change the path which fishes move along
//

#ifndef EditorLayer_h
#define EditorLayer_h

#include <stdio.h>
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

typedef enum _button_tag
{
    Button_Null = 0,
    Button_StraightLine,
    Button_Lagrange,
    Button_Bezier,
    Button_Paramtric,
    Button_Polar
} ButtonTag;

typedef enum _button_type {
    Button_Blue = 1,
    Button_Yellow
} ButtonType;

class EditorLayer : public LayerColor {
public:
    virtual bool init();
    CREATE_FUNC(EditorLayer);
    
    virtual void onEnter();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    void initUI();
    void onClickButton(ButtonTag tag);
    
    Button* createButton(ButtonType type);
    void showParamtric(bool show);
    void showPolar(bool show);
    
    void cleanEditor();
    
    void addPoint(Vec2 pos, int tag=-1);
    void movePoint(Button *button, Vec2 pos);
    
    void loadPoints();
    void savePoints();
private:
    ButtonTag _selectTag;
    Layer *_layerParamtric;
    Layer *_layerPolar;
    Layer *_layerPoint;
    
    std::vector<Point> _points;
    DrawNode *_drawNode;
};

#endif /* EditorLayer_h */
