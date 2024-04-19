#pragma once
#include "../struct/position.h"
class BaseObj {
public:
	Position pos;
	void setPosition(const Position& pos);
	virtual void drawSelf() = 0;
	BaseObj(const Position& startPos);
	virtual ~BaseObj() {};
};