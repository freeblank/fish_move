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
#include "LagrangeCurveMove.h"
#include "HeartMove.h"
#include "LemniscateMove.h"

FishCreator::FishCreator(MoveType type, int totalNum) {
    _type = type;
    _totalNum = totalNum;
    _curFish = nullptr;
    
    if (_type == MoveType_StraightLine || _type == MoveType_Bezier || _type == MoveType_Lagrange
        || _type == MoveType_Heart || _type == MoveType_Lemniscate) {
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
        case MoveType_Lagrange:
            i_move = new LagrangeCurveMove();
            dynamic_cast<LagrangeCurveMove*>(i_move)->setPoints(_points);
            break;
        case MoveType_Heart:
            i_move = new HeartMove();
            dynamic_cast<HeartMove*>(i_move)->setOrigin(_points[0]);
            break;
        case MoveType_Lemniscate:
            i_move = new LemniscateMove();
            dynamic_cast<LemniscateMove*>(i_move)->setOrigin(_points[0]);
        default:
            break;
    }
    
    if (!i_move) return;
    
    FishSprite *i_fish = FishManager::getInstance()->addFish();
    i_fish->bindMove(i_move);
    i_move->next(1/60.0);
    _initPos = i_move->getCurPos();
    _curFish = i_fish;
    
    _curNum++;
}

void FishCreator::update() {
    if (_totalNum>0 && _curNum>=_totalNum) return;
    if (!_curFish) return;
    
    float create_distance = 80.0f;
    Point i_pos = _curFish->getPosition();
    if (i_pos.getDistance(_initPos) >= create_distance) {
        createFish();
    }
}



