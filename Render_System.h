#pragma once

#include<iostream>
#include<string>
#include "Letter_Colour.h"

const int Screen_Rows = 25;
const int Screen_Columns = 80;

struct ConsoleSymbolData
{
	char symbol;
	Letter_Colour Symbol_Colour;
	Letter_Colour Background_Colour;
};

void Render_System_Initialize();
void Render_System_Clear();
void Render_System_Char(int row, int col, char symbol, Letter_Colour SymbolColour, Letter_Colour BackgroundColour);
void Render_System_Text(int row, int col, const char* text, Letter_Colour SymbolColour, Letter_Colour BackgroundColour);
void Render_System_String(int row, int col, std::string text, Letter_Colour SymbolColour, Letter_Colour BackgroundColour);
void Render_System_Flush();