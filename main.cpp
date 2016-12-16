#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<ctype.h>
#include<stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#include "Letter_Colour.h"
#include "Level.h"
#include "UnitData.h"
#include "UnitType.h"
#include "ConsoleMenu.h"

unsigned char LevelData[Rows_Count][Columns_Count];

int fps;
clock_t ClockLastFrame;
int FramesCounter;
float FramesTimeCounter;

const int MaxUnitsCount = 35;
Unit_Data UnitsData[MaxUnitsCount];
int UnitsCount;
int Hero_Index;
int Points;

const float CellBegin = 0.001f;
const float CellEnd = 0.999f;
const float g = 40.0;

void SetupSystem();
void Initialise(int current_level);
void Render();
void Update();
void UpdateUnit(Unit_Data *pointer_to_UnitData, float DeltaTime);
void UpdateAI();
bool MoveUnitTo(Unit_Data *pointer_to_UnitData, float newX, float newY);
Unit_Data* GetUnitAt(int row, int col);
void KillUnit(Unit_Data* pointer_to_UnitData);
void Shutdown();

void main(){
	SetupSystem();
	
	do{
	InitMenu();
	ShowMenu();
	MenuPoint(Pointer_Position);
	}while(!Exit);

	Shutdown();
}

void Play(int current_level, bool begin)
{
	OpenMenu = false;
	
	do{
	Render_System_Clear();
	if(begin) Initialise(current_level);//начать уровень с начала
	Hero_Wins = false;
	IsGameActive = true;
	
	do{
	Render();
	Update();
	}while(IsGameActive && !OpenMenu);
	if(Hero_Wins) current_level ++;
	begin = true;
	}while(current_level != Number_Of_Levels && !OpenMenu);
}

void SetupSystem(){
	srand(time(NULL));
	Render_System_Initialize();
}

void Initialise(int current_level){
	fps = 0;
	FramesCounter = 0;
	FramesTimeCounter = 0;
	UnitsCount = 0;
	Hero_Index = 0;
	Points = 0;
	
	ClockLastFrame = clock();

	for(int row = 0; row < Rows_Count; row ++)
		for(int col = 0; col < Columns_Count; col ++)
		{
			unsigned char CellSymbol = LevelData0[current_level][row][col];
			LevelData[row][col] = CellSymbol;

			switch(CellSymbol)
			{
				case CellSymbol_Hero: Hero_Index = UnitsCount;
				case CellSymbol_Goomba:
					
					Unit_Type UnitType = Get_Unit_Type_From_Cell(CellSymbol);
					UnitsData[UnitsCount].type = UnitType;
					UnitsData[UnitsCount].y = float(row);
					UnitsData[UnitsCount].x = float(col);
					UnitsData[UnitsCount].health = 1;
					UnitsData[UnitsCount].xSpeed = 0.0;
					UnitsData[UnitsCount].ySpeed = 0.0;
					UnitsData[UnitsCount].xOrder = UnitOrder_None;
					UnitsData[UnitsCount].yOrder = UnitOrder_None;
					UnitsCount ++;

					break;
			}
		}

}

void Render(){
	Render_System_Clear();

	for(int row = 0; row < Rows_Count; row ++)
		for(int col = 0; col < Columns_Count; col ++)
		{
			unsigned char CellSymbol = LevelData[row][col];
			unsigned char RenderSymbol = GetRenderCellSymbol(CellSymbol);
			Letter_Colour SymbolColour = GetRenderCellSymbolColour(CellSymbol);
			Letter_Colour BackgroundColour = GetRenderCellSymbolBackgroundColour(CellSymbol);

			if(CellSymbol == CellSymbol_Hero)
				SymbolColour = GetRenderHeroColour(UnitsData[Hero_Index].health);

			Render_System_Char(row, col, RenderSymbol, SymbolColour, BackgroundColour);
		}

	char buf[32];
	sprintf(buf, "FPS: %d", fps);
	Render_System_Text(0, 0, buf, Letter_Colour_Grey, Letter_Colour_Black);
	sprintf(buf, "Points: %d", Points);
	Render_System_Text(0, Columns_Count - 10*(Points >= 10) - 9*(Points < 10), buf, Letter_Colour_Grey, Letter_Colour_Black);

	Render_System_Flush();
}

void Update(){
	clock_t ClockNow = clock();
	clock_t DeltaClock = ClockNow - ClockLastFrame;
	float dT = float(DeltaClock)/CLOCKS_PER_SEC;
	ClockLastFrame = ClockNow;

	FramesCounter ++;
	FramesTimeCounter += dT;
	if(FramesTimeCounter >= 1.0)
		{
			FramesTimeCounter -= 1.0;
			fps = FramesCounter;
			FramesCounter = 0;
		}

	if(IsKeyDown(VK_UP))
		UnitsData[Hero_Index].yOrder = UnitOrder_Backward;
	else UnitsData[Hero_Index].yOrder = UnitOrder_None;

	if(IsKeyDown(VK_LEFT)) 
		UnitsData[Hero_Index].xOrder = UnitOrder_Backward;
	else
	{
	if(IsKeyDown(VK_RIGHT)) 
		UnitsData[Hero_Index].xOrder = UnitOrder_Forward;
	else UnitsData[Hero_Index].xOrder = UnitOrder_None;
	}

	for(int u = 0; u< UnitsCount; u++)
		UpdateUnit(&UnitsData[u], dT);

	UpdateAI();
	
	if(IsKeyDown(27))
		OpenMenu = true;

if(UnitsData[Hero_Index].health <= 0)
	{
	int HIDrow = (Rows_Count - HIDr)/2;
	int HIDcol = (Columns_Count - HIDc)/2;
	for(int i = 0; i < HIDr; i++)
		Render_System_Text(HIDrow + i, HIDcol, Hero_Is_Dead[i], Letter_Colour_Red, Letter_Colour_Black);
	Render_System_Flush();
	while(!IsKeyDown(32)){}
	IsGameActive = false;
	}

if(Hero_Wins)
	{
	int HIVrow = (Rows_Count - HIVr)/2;
	int HIVcol = (Columns_Count - HIVc)/2;
	for(int i = 0; i < HIVr; i++)
		Render_System_Text(HIVrow + i, HIVcol, Victory[i], Letter_Colour_Green, Letter_Colour_Black);
	Render_System_Flush();
  	while(!IsKeyDown(32)){}
	IsGameActive = false;
	}
}

void UpdateUnit(Unit_Data *pointer_to_UnitData, float dT){
	int row = int(pointer_to_UnitData->y);
	int col = int(pointer_to_UnitData->x);

	if(LevelData[row + 1][col] == CellSymbol_Jumper)
		pointer_to_UnitData->ySpeed = -GetSpeedFromCell(LevelData[row + 1][col]);

	if(pointer_to_UnitData->yOrder == UnitOrder_Backward)
		if((pointer_to_UnitData->y >= row + CellEnd)
			&&(LevelData[row + 1][col] != CellSymbol_Empty)
			&&(LevelData[row + 1][col] != CellSymbol_Abyss))
				pointer_to_UnitData->ySpeed = -Get_Unit_Jump_Speed(pointer_to_UnitData->type);

	if(pointer_to_UnitData->xOrder == UnitOrder_Backward)
		pointer_to_UnitData->xSpeed = -Get_Unit_Speed_X(pointer_to_UnitData->type);
	else if(pointer_to_UnitData->xOrder == UnitOrder_Forward)
		pointer_to_UnitData->xSpeed = Get_Unit_Speed_X(pointer_to_UnitData->type);
	else pointer_to_UnitData->xSpeed = 0;

	float dY = pointer_to_UnitData->ySpeed * dT;
	float dX = pointer_to_UnitData->xSpeed * dT;
	float newX = pointer_to_UnitData->x + dX;
	float newY = pointer_to_UnitData->y + dY;
	int newRow = int(newY);
	int newCol = int(newX);

	//движение по вертикали
	if(newRow != row){
		if(MoveUnitTo(pointer_to_UnitData, pointer_to_UnitData->x, newY))
			row = int(pointer_to_UnitData->y);
		else 
		{
			if(newRow > row)
			{
				pointer_to_UnitData->y = row + CellEnd;
				if(pointer_to_UnitData->ySpeed > 0.0) pointer_to_UnitData->ySpeed = 0.0;
			}
			else 
			{
				pointer_to_UnitData->y = row + CellBegin;
				if(pointer_to_UnitData->ySpeed < 0.0) pointer_to_UnitData->ySpeed = 0.0;
			}
		}
	}
	else pointer_to_UnitData->y = newY;

	//движение по горизонтали
	if(newCol != col){
		if(MoveUnitTo(pointer_to_UnitData, newX, pointer_to_UnitData->y))
			col = int(pointer_to_UnitData->x);
		else 
		{
			if(newCol > col)
			{
				pointer_to_UnitData->x = col + CellEnd;
				if(pointer_to_UnitData->xSpeed > 0.0) pointer_to_UnitData->xSpeed = 0.0;
			}
			else 
			{
				pointer_to_UnitData->x = col + CellBegin;
				if(pointer_to_UnitData->xSpeed < 0.0) pointer_to_UnitData->xSpeed = 0.0;
			}
		}
	}
	else pointer_to_UnitData->x = newX;

	//gravity
	pointer_to_UnitData->ySpeed += g*dT;
	if(pointer_to_UnitData->ySpeed > g)pointer_to_UnitData->ySpeed = g;
}

void UpdateAI(){
	for(int u = 0; u < UnitsCount; u++)
	{
		if((u == Hero_Index)||(UnitsData[u].health <= 0)) continue;

		int row = int(UnitsData[u].y);
		int col = int(UnitsData[u].x);

		if(UnitsData[u].xOrder == UnitOrder_None)
		{
			int ran = rand()%2;
			if((ran) && (LevelData[row][col - 1] == CellSymbol_Empty))
				UnitsData[u].xOrder = UnitOrder_Backward;
			else if((!ran) && (LevelData[row][col + 1] == CellSymbol_Empty))
				UnitsData[u].xOrder = UnitOrder_Forward;
			else if (LevelData[row][col + 1] == CellSymbol_Empty) UnitsData[u].xOrder = UnitOrder_Forward;
			else if (LevelData[row][col - 1] == CellSymbol_Empty) UnitsData[u].xOrder = UnitOrder_Backward;
		}
		else if(UnitsData[u].xOrder == UnitOrder_Backward)
		{
			unsigned char LeftCell = LevelData[row][col - 1];
			Unit_Type unit_type = Get_Unit_Type_From_Cell(LeftCell);
			if((UnitsData[u].x <= (col + CellBegin)) && (unit_type == Unit_Type_None) && (LeftCell != CellSymbol_Empty))
				UnitsData[u].xOrder = UnitOrder_Forward;
		}
		else
		{
			unsigned char RightCell = LevelData[row][col + 1];
			Unit_Type unit_type = Get_Unit_Type_From_Cell(RightCell);
			if((UnitsData[u].x >= (col + CellEnd)) && (unit_type == Unit_Type_None) && (RightCell != CellSymbol_Empty))
				UnitsData[u].xOrder = UnitOrder_Backward;
		}
	}
}

bool MoveUnitTo(Unit_Data *pointer_to_UnitData, float newX, float newY){
	if(pointer_to_UnitData->health <= 0) return false;
	bool CanMoveToCell = false;
	
	int newRow = int(newY);
	int newCol = int(newX);
	int Row = int(pointer_to_UnitData->y);
	int Col = int(pointer_to_UnitData->x);

	unsigned char UnitSymbol = LevelData[Row][Col];
	unsigned char DestinationCell = LevelData[newRow][newCol];

	int DirectionRow = newRow - Row;
	int DestinationCol = newCol - Col;
	
	switch(DestinationCell){
		case CellSymbol_Empty: {CanMoveToCell = true; break;}
		case CellSymbol_Abyss: {KillUnit(pointer_to_UnitData);break;}
		case CellSymbol_Box:
			{
				if(DirectionRow < 0)
				{
					LevelData[newRow][newCol] = CellSymbol_Opened_Box;
					LevelData[newRow -1][newCol] = CellSymbol_Crystal;
				}
				break;
			}
		case CellSymbol_Mushroom_Box:
			{
				if(DirectionRow < 0)
				{
					LevelData[newRow][newCol] = CellSymbol_Opened_Box;
					LevelData[newRow - 1][newCol] = CellSymbol_Mushroom;
					Unit_Type UnitType = Get_Unit_Type_From_Cell(LevelData[newRow - 1][newCol]);
					UnitsData[UnitsCount].type = UnitType;
					UnitsData[UnitsCount].y = float(newRow - 1);
					UnitsData[UnitsCount].x = float(newCol);
					UnitsData[UnitsCount].health = 1;
					UnitsData[UnitsCount].xSpeed = 0.0;
					UnitsData[UnitsCount].ySpeed = 0.0;
					UnitsData[UnitsCount].xOrder = UnitOrder_None;
					UnitsData[UnitsCount].yOrder = UnitOrder_None;
					UnitsCount ++;
				}
				break;
			}
	}

	//hero actions
	if(pointer_to_UnitData->type == Unit_Type_Hero)
	{
		switch(DestinationCell){
			case CellSymbol_Crystal:{CanMoveToCell = true; Points ++; break;}
			case CellSymbol_Exit: {Hero_Wins = true; break;}
			case CellSymbol_Mushroom:
				{
					CanMoveToCell = true;
					Unit_Data* ptr_mushroom;
					int u;
					for(u = 0; u < UnitsCount; u++)
						if(int(UnitsData[u].x) == newCol && int(UnitsData[u].y) == newRow) break;
					if(pointer_to_UnitData->health < 2)
						pointer_to_UnitData->health = 2;
					KillUnit(&UnitsData[u]);
					break;
				}
			case CellSymbol_Brick_Wall:
				{
					if((pointer_to_UnitData->health > 1) && (DirectionRow < 0))
						LevelData[newRow][newCol] = CellSymbol_Empty;
					break;
				}
			case CellSymbol_Goomba:
				{
					if(DirectionRow > 0)//если мы сверху
					{
						Unit_Data* unit_data = GetUnitAt(newRow, newCol);
						if(unit_data != 0)
						{
							KillUnit(unit_data);
							pointer_to_UnitData->ySpeed = - Get_Unit_Jump_Speed(pointer_to_UnitData->type);
						}
					}
						break;
				}
		}
	}

	else if(pointer_to_UnitData->type == Unit_Type_Mushroom)
	{
		switch(DestinationCell){
		case CellSymbol_Hero:
			{
				UnitsData[Hero_Index].health ++;
				KillUnit(pointer_to_UnitData);
				break;
			}
		default:
			{
				Unit_Type unit_type = Get_Unit_Type_From_Cell(DestinationCell);
				if(unit_type != Unit_Type_None)
				{
					if(pointer_to_UnitData->xOrder == UnitOrder_Backward)
						pointer_to_UnitData->xOrder = UnitOrder_Forward;
					else pointer_to_UnitData->xOrder = UnitOrder_Backward;
					break;
				}
				break;
			}
		}
	}

	//monsters' actions
	else
	{
		switch(DestinationCell){
		case CellSymbol_Hero:
			{
				UnitsData[Hero_Index].health --;
				if(pointer_to_UnitData->xOrder == UnitOrder_Backward)
					pointer_to_UnitData->xOrder = UnitOrder_Forward;
				else pointer_to_UnitData->xOrder = UnitOrder_Backward;
				break;
			}
		default:
			{
				Unit_Type unit_type = Get_Unit_Type_From_Cell(DestinationCell);
				if(unit_type != Unit_Type_None)
				{
					if(pointer_to_UnitData->xOrder == UnitOrder_Backward)
						pointer_to_UnitData->xOrder = UnitOrder_Forward;
					else pointer_to_UnitData->xOrder = UnitOrder_Backward;
					break;
				}
				break;
			}
		}
	}

	if(CanMoveToCell)
	{
		LevelData[Row][Col] = CellSymbol_Empty;
		pointer_to_UnitData->x = newX;
		pointer_to_UnitData->y = newY;
		LevelData[newRow][newCol] = UnitSymbol;
	}

	return CanMoveToCell;
}

Unit_Data* GetUnitAt (int row, int col){

for(int u = 0; u < UnitsCount; u++)
	{
		if(UnitsData[u].health <= 0) continue;
		if((int(UnitsData[u].y) == row) && (int(UnitsData[u].x) == col))
			return &UnitsData[u];
	}
return 0;
}

void KillUnit(Unit_Data* pointer_to_UnitData){
	pointer_to_UnitData->health = 0;
	LevelData[int(pointer_to_UnitData->y)][int(pointer_to_UnitData->x)] = CellSymbol_Empty;
}

void Shutdown(){

}