#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<Windows.h>
#include<ctype.h>
#include<stdlib.h>

#include<iostream>
using namespace std;

#include "Letter_Colour.h"
#include "ConsoleMenu.h"
#include "Level.h"

int Pointer_Position = 1;
HANDLE consoleHandle = 0;
int current_level = 0;

void ShowMenu(bool IsGameActive, bool Exit){
const int Number_of_variants = 5;
const char Pointer = 16;
char buf;
Pointer_Position = 1;

do{
	COORD CursorCoord;
	CursorCoord.X = 0;
	CursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, CursorCoord);

	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
cout<<"\tMENU\n\tUse W,S to navigate, space to choose\n\n";
	if(Pointer_Position == 1)cout<<"\t"<<Pointer;
	else cout<<"\t"<<" ";
	cout<<" "<<"Continue game\n";
	if(Pointer_Position == 2)cout<<"\t"<<Pointer;
	else cout<<"\t"<<" ";
	cout<<" "<<"Restart level\n";
	if(Pointer_Position == 3)cout<<"\t"<<Pointer;
	else cout<<"\t"<<" ";
	cout<<" "<<"Choose level\n";
	if(Pointer_Position == 4)cout<<"\t"<<Pointer;
	else cout<<"\t"<<" ";
	cout<<" "<<"Help\n";
	if(Pointer_Position == 5)cout<<"\t"<<Pointer;
	else cout<<"\t"<<" ";
	cout<<" "<<"Exit\n"<<
	endl;

buf = _getch();
switch(buf){
		case 'w':
			{
			if(Pointer_Position !=1)Pointer_Position --;
			break;
			}
		case 's':
			{
			if(Pointer_Position !=Number_of_variants)Pointer_Position ++;
			break;
			}
		default:
			break;
		}
}
while(buf!=' ');
system("cls");
}

void LevelMenu(bool IsGameActive){
	int Level_Position = 1;
	char Pointer = 16;
	char buf;
	do{
	COORD CursorCoord;
	CursorCoord.X = 0;
	CursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, CursorCoord);

	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
cout<<"\tCHOOSE LEVEL\n\tUse W,S to navigate\n\n";
for(int i = 0; i < Number_Of_Levels; i++)
	{if(Level_Position == i+1)cout<<"\t"<<Pointer;
	else cout<<"\t"<<" ";
	cout<<" "<<"Level "<<i+1<<"\n";
	}
	buf = _getch();
switch(buf){
		case 'w':
			{
			if(Level_Position !=1)Level_Position --;
			break;
			}
		case 's':
			{
			if(Level_Position !=Number_Of_Levels)Level_Position ++;
			break;
			}
		default:
			break;
		}
	}
while(buf=='w'||buf=='s');
	current_level = Level_Position - 1;
	IsGameActive = true;
	Pointer_Position = 2;
system("cls");
}

void ShowHelp(){
	COORD CursorCoord;
	CursorCoord.X = 0;
	CursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, CursorCoord);

//Here you write help, needed in your game
/*
cout<<"\tYour aim is to reach the exit. Move boxes to clear you path.\n"<<
	"\tYou are not allowed to go through walls.\n"<<
	"\tUse WASD to move. R quickly restarts current level.\n"<<
	"\n\tSymbols used:\n";
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Green);
	cout<<"\t"<<symbolHero;
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
	cout<<" is Hero. Move him using WASD.\n";
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Red);
	cout<<"\t"<<symbolExit;
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
	cout<<" is exit. Reach it to win.\n";
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Yellow);
	cout<<"\t"<<symbolBox;
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
	cout<<" is box\n";
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_White);
	cout<<"\t"<<symbolWall;
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
	cout<<" is wall\n";
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Dark_Red);
	cout<<"\t"<<symbolMine;
	SetConsoleTextAttribute(consoleHandle, Letter_Colour_Grey);
	cout<<" is a mine. Standing on the mine will kill the Hero.\n"
		<<"\t  Placing a box on a mine will destroy both.\n";
	cout<<endl;
*/

cout<<"\n\tPress any key to return to menu..."<<endl;
_getch();
system("cls");
}
