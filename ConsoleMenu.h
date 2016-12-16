//попытка сделать универсальный модуль меню

#pragma once

#include<stdio.h>
#include<conio.h>
#include<Windows.h>
#include<ctype.h>
#include<stdlib.h>
#include<string>
#include <iostream>
#include<fstream>
using namespace std;

#include "Letter_Colour.h"
#include "Render_System.h"
#include "Input.h"

bool IsGameActive = true;//для прерывания игры
bool Exit = false;//для выхода из программы
bool Hero_Wins = false;
bool OpenMenu;//для вызова меню из игры
int a = 1; //метка для отслеживания первого запуска уровня
int Pointer_Position = 1;
const char Pointer = 16;
int current_level = 0;

const int Number_of_menus = 2;
const int Number_of_variants = 5;
const int Menu_String_Length = 37;
const int MainMenu_RowsCount = Number_of_variants + 3;
const char MainMenu[Number_of_menus][MainMenu_RowsCount][Menu_String_Length + 1] = 
{
	//main menu
	{
	"MENU",
	"Use W,S to navigate, space to choose",
	"",
	"Continue game",
	"Restart level",
	"Choose level",
	"Help",
	"Exit",
	},
	//help menu
	{
	"HELP",
	"",
	}
};

void InitMenu();
void ShowMenu();
void MenuPoint(int Pointer_Position); //делает то, что выбрали в меню
void LevelMenu();//меню выбора уровня
void HelpMenu();//помощь - инструкция
void Play(int level, bool begin);//запускает уровень level, если begin=true, то запускает его заново, если нет - игра продолжается

void InitMenu(){
	Render_System_Clear();

	for(int row = 0; row < MainMenu_RowsCount; row ++)
		Render_System_Text(row, 10, MainMenu[0][row] , Letter_Colour_Grey, Letter_Colour_Black);

	Render_System_Flush();
}

void ShowMenu()
{
char buf;
Pointer_Position = 1;

do{
	Render_System_Char(3, 8, ' '*(Pointer_Position != 1) + Pointer*(Pointer_Position == 1), Letter_Colour_Grey, Letter_Colour_Black);
	Render_System_Char(4, 8, ' '*(Pointer_Position != 2) + Pointer*(Pointer_Position == 2), Letter_Colour_Grey, Letter_Colour_Black);
	Render_System_Char(5, 8, ' '*(Pointer_Position != 3) + Pointer*(Pointer_Position == 3), Letter_Colour_Grey, Letter_Colour_Black);
	Render_System_Char(6, 8, ' '*(Pointer_Position != 4) + Pointer*(Pointer_Position == 4), Letter_Colour_Grey, Letter_Colour_Black);
	Render_System_Char(7, 8, ' '*(Pointer_Position != 5) + Pointer*(Pointer_Position == 5), Letter_Colour_Grey, Letter_Colour_Black);

	Render_System_Flush();

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
	}while(buf!=' ');
}

void HelpMenu()
{
Render_System_Clear();

Render_System_Text(1,8,"HELP",Letter_Colour_Dark_Green, Letter_Colour_Black);

int last_string_row = 7;
ifstream fin ("help.txt",ios_base::in);
if(fin == NULL)
	{
	Render_System_Text(3, 8, "ERROR OPENING HELP FILE!", Letter_Colour_Grey, Letter_Colour_Black);
	Render_System_Text(4, 8, "CHECK IF THE FILE EXISTS IN CORRESPONDING DIRECTORY!", Letter_Colour_Grey, Letter_Colour_Black);
	Render_System_Text(5, 8, "project_name\\project_name\\Help.txt", Letter_Colour_Grey, Letter_Colour_Black);
	}
else{
	int i = 3;
	std::string str;
	while (!(fin.eof()))
		{
			getline(fin,str);
			Render_System_String(i, 8, str, Letter_Colour_Grey, Letter_Colour_Black);
			i++;
			last_string_row ++;
		}
}
Render_System_Text(last_string_row,8,"Press any key to return to menu...",Letter_Colour_Grey, Letter_Colour_Black);
Render_System_Flush();

_getch();
}

void MenuPoint(int Pointer_Position)
{
	switch(Pointer_Position){
		case 1: {
			if(a) {Play(current_level, 1); a=0;}
			else Play(current_level, 0);
			break;}
		case 2: {Play(current_level, 1);break;}
		case 3: {system("cls"); LevelMenu(); break;}
		case 4: {system("cls"); HelpMenu(); break;}
		case 5: {Exit = true; break;}
	}
}

void LevelMenu()
{
	Render_System_Clear();
	int Level_Pointer_Position = 1;
	char Pointer = 16;
	char buf;
	
	Render_System_Text(1, 8, "CHOOSE LEVEL", Letter_Colour_White, Letter_Colour_Black);
	Render_System_Text(2, 8, "Use W,S to navigate", Letter_Colour_White, Letter_Colour_Black);
	for(int i = 0; i < Number_Of_Levels; i++)
		{
			char buffer[32];
			sprintf(buffer, " Level %d", i+1);
			Render_System_Text(i+4, 10, buffer, Letter_Colour_Grey, Letter_Colour_Black);
		}

	do{
		for(int i = 0; i < Number_Of_Levels; i++)
		{
			char buffer[32];
			if(Level_Pointer_Position == i+1) sprintf(buffer, "%c", Pointer);
			else sprintf(buffer, " ");
			Render_System_Text(i+4, 8, buffer, Letter_Colour_Grey, Letter_Colour_Black);
		}
		Render_System_Flush();
		buf = _getch();
		switch(buf){
			case 'w':
				{
				if(Level_Pointer_Position !=1)Level_Pointer_Position --;
				break;
				}
			case 's':
				{
				if(Level_Pointer_Position !=Number_Of_Levels)Level_Pointer_Position ++;
				break;
				}
			default:
				break;
			}
	}while(buf!=' ');

	current_level = Level_Pointer_Position - 1;
	Play(current_level, 1);
}