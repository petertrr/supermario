#pragma once

#include "level.h"
 
 enum Unit_Type
{
    Unit_Type_None,
    Unit_Type_Hero,
    Unit_Type_Goomba,
	Unit_Type_Mushroom
};
  
Unit_Type Get_Unit_Type_From_Cell( unsigned char CellSymbol )
{
    switch( CellSymbol )
    {
        case CellSymbol_Hero:				return Unit_Type_Hero;
        case CellSymbol_Goomba:				return Unit_Type_Goomba;
		case CellSymbol_Mushroom:			return Unit_Type_Mushroom;
    }
	return Unit_Type_None;
}

int Get_Unit_Speed_X(Unit_Type UnitType)
{
	switch(UnitType){
		case Unit_Type_Hero:	return 10;
		case Unit_Type_Goomba:	return 2;
		case Unit_Type_Mushroom:return 2;
	}
	return 0;
}

int Get_Unit_Jump_Speed(Unit_Type UnitType)
{
	switch(UnitType){
		case Unit_Type_Hero:	return 17;
	}
	return 0;
}