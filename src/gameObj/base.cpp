#include "base.h"

void BaseObj::setPosition(const Position& pos)
{
	this->pos.x = pos.x;
	this->pos.y = pos.y;
}

BaseObj::BaseObj(const Position& startPos) :pos(startPos) {}
