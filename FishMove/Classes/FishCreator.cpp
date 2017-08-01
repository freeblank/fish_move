//
//  FishCreator.cpp
//  FishMove
//
//  Created by FreeBlank on 17/7/30.
//
//

#include "FishCreator.h"
#include "StraightLineMove.h"
#include "BezierCurveMove.h"

FishCreator::FishCreator(MoveType type, int totalNum) {
    _type = type;
    _totalNum = totalNum;
    _curFish = nullptr;
    
    if (_type == MoveType_StraightLine || _type == MoveType_Bezier) {
        FishManager::getInstance()->loadPoints(_type, _points);
    }
    
    createFish();
}

void FishCreator::createFish() {
    BaseMove *i_move = nullptr;
    switch (_type) {
        case MoveType_StraightLine:
            i_move = new StraightLineMove();
            dynamic_cast<StraightLineMove*>(i_move)->setPoints(_points);
            break;
        case MoveType_Bezier:
            i_move = new BezierCurveMove();
            dynamic_cast<BezierCurveMove*>(i_move)->setPoints(_points);
            break;
        default:
            break;
    }
    
    if (!i_move) return;
    
    FishSprite *i_fish = FishManager::getInstance()->addFish();
    i_fish->bindMove(i_move);
    _initPos = i_move->getCurPos();
    _curFish = i_fish;
    
    _curNum++;
}

void FishCreator::update() {
    if (_totalNum>0 && _curNum>=_totalNum) return;
    if (!_curFish) return;
    
    float create_distance = 80.0f;
    if (_type == MoveType_Bezier) {
        create_distance = 80.0f;
    }
    Point i_pos = _curFish->getPosition();
    if (i_pos.getDistance(_initPos) >= create_distance) {
        createFish();
    }
}



