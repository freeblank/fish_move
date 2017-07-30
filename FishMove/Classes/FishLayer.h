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
#include "FishManager.h"
#include "FishCreator.h"

using namespace cocos2d;

class FishLayer : public Layer {
public:
    CREATE_FUNC(FishLayer);
    virtual bool init();
    
    virtual void update(float delta);
    void addEventListener();
    
    void setEditable(bool editable) { _editable = editable; }
    void clear();
    
private:
    void onEditorFinish(MoveType type);
    
private:
    bool _editable;
    std::vector<FishCreator*> _fishCreators;
};
#endif /* FishLayer_h */
