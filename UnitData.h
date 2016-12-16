#pragma once

#include"UnitType.h"
#include "UnitOrder.h"

struct Unit_Data
{
	Unit_Type type;
	int health;
	float x;
	float y;
	float xSpeed;
	float ySpeed;
	UnitOrder xOrder;
	UnitOrder yOrder;
};