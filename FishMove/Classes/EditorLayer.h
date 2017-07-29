//
//  EditorLayer.h
//  FishMove
//
//  Created by pClass on 17/7/29.
//
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
    
private:
    void initUI();
    void onClickButton(ButtonTag tag);
    
    Button* createButton(ButtonType type);
    void showParamtric(bool show);
    void showPolar(bool show);
private:
    ButtonTag _selectTag;
    Layer *layerParamtric;
    Layer *layerPolar;
};

#endif /* EditorLayer_h */
