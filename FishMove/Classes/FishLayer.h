//
//  FishLayer.h
//  FishMove
//
//  Created by FreeBlank on 17/7/29.
//
// all fish will add into the layer, change it with listener event from editor
//

#ifndef FishLayer_h
#define FishLayer_h

#include <stdio.h>
#include "BaseMove.h"

using namespace cocos2d;

class FishLayer : public Layer {
public:
    CREATE_FUNC(FishLayer);
    virtual bool init();
    
    virtual void update(float delta);
    void addEventListener();
    
private:
    void onUpdateMove(BaseMove *move);
    void onEditorFinish();
    
private:
    BaseMove *_move;
    bool _editable;
};
#endif /* FishLayer_h */
