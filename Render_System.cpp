#include "Render_System.h"

#include<Windows.h>
#include<stdio.h>
#include<string>

HANDLE ConsoleHandle = 0;

ConsoleSymbolData BackBuffer[Screen_Rows][Screen_Columns];
ConsoleSymbolData ScreenBuffer[Screen_Rows][Screen_Columns];

void Set_Console_Colour(Letter_Colour SymbolColour, Letter_Colour BackgroundColour);
void Set_Console_Cursor(int row, int col);

void Render_System_Initialize()
{
	ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//hide cursor
	CONSOLE_CURSOR_INFO CursorInfo;
	CursorInfo.dwSize = 1;
	CursorInfo.bVisible = 0;
	SetConsoleCursorInfo( ConsoleHandle, &CursorInfo);

	//initialize buffers
	for(int row = 0; row < Screen_Rows; row++)
		for(int col = 0; col < Screen_Columns; col++)
		{
			BackBuffer[row][col].symbol = 0;
			BackBuffer[row][col].Symbol_Colour = Letter_Colour_Grey;
			BackBuffer[row][col].Background_Colour = Letter_Colour_Black;

			ScreenBuffer[row][col] = BackBuffer[row][col];
		}

}

void Render_System_Clear()
{
	for(int row = 0; row < Screen_Rows; row++)
		for(int col = 0; col < Screen_Columns; col++)
		{
			BackBuffer[row][col].symbol = 0;
			BackBuffer[row][col].Background_Colour = Letter_Colour_Black;
		}
}

void Render_System_Char(int row, int col, char symbol, Letter_Colour SymbolColour, Letter_Colour BackgroundColour)
{
	BackBuffer[row][col].symbol = symbol;
	BackBuffer[row][col].Symbol_Colour = SymbolColour;
	BackBuffer[row][col].Background_Colour = BackgroundColour;
}

void Render_System_Text(int row, int col, const char* text, Letter_Colour SymbolColour, Letter_Colour BackgroundColour)
{
	int column = col;
	char symbol = *text;

	while(symbol!=0)
	{
	Render_System_Char(row, col, symbol, SymbolColour, BackgroundColour);
	text++;
	col++;
	symbol = *text;
	}
}

void Render_System_String(int row, int col, std::string text, Letter_Colour SymbolColour, Letter_Colour BackgroundColour)
{
	int column = col;
	Letter_Colour CellColour = SymbolColour, BackColour = BackgroundColour;
	char symbol;
	int i = 1;
	if(text.size() != 0)
	{
		while(i < text.size() - 1)
		{
		symbol = text.at(i);
		switch(symbol){
			case '_': {
				i++;
				char control[4] = {text.at(i), text.at(i+1),text.at(i+2),text.at(i+3)};
					if((control[0] == 'c')&&(control[1] == 'o')&&(control[2] == 'l')&&(control[3] == 'r'))
					{
						i += 5; 
						symbol = 0; 
						switch(text.at(i)){
							case 'Y': {CellColour = Letter_Colour_Yellow; break;}
							case 'W': {CellColour = Letter_Colour_White; break;}
							case 'G': {CellColour = Letter_Colour_Grey; break;}
							case 'D':
								{
									i++;
									switch(text.at(i)){
										case 'R': {CellColour = Letter_Colour_Dark_Red; break;}
									}
								break;
								}
						}
					}
					else if((control[0] == 'c')&&(control[1] == 'h')&&(control[2] == 'a')&&(control[3] == 'r'))
						{
							i += 5;
							int num[3] = {0,0,0}, buf[3];
							num[0] = text.at(i) - 48;
							if(text.at(i+1) != ' ') {i++; num[1]=text.at(i) - 48;}
							if(text.at(i+1) != ' ') {i++; num[2]=text.at(i) - 48;}
							buf[0] = num[2];
							buf[1] = num[1];
							buf[2] = num[0];
							 
							symbol = num[2] + 10*num[1] + 100*num[0];//получили символ, который уже можно выводить
						}
				break;
				}
			default: break;
		}
		if(symbol != 0){Render_System_Char(row, col, symbol, CellColour, BackColour);
		col++;}
		i++;
		
		}
	}
}

void Render_System_Flush()
{
	bool ScreenBufferModified = false;

	for(int row = 0; row < Screen_Rows; row ++)
		for(int col = 0; col < Screen_Columns; col ++)
		{
			if( (BackBuffer[row][col].symbol != ScreenBuffer[row][col].symbol)
				||(BackBuffer[row][col].Symbol_Colour != ScreenBuffer[row][col].Symbol_Colour)
				||(BackBuffer[row][col].Background_Colour != ScreenBuffer[row][col].Background_Colour))
			{
				ScreenBuffer[row][col] = BackBuffer[row][col];

				Set_Console_Cursor(row, col);
				Set_Console_Colour(ScreenBuffer[row][col].Symbol_Colour, ScreenBuffer[row][col].Background_Colour);
				printf("%c", ScreenBuffer[row][col].symbol);

				ScreenBufferModified = true;
			}
		}

	if(ScreenBufferModified)
		Set_Console_Cursor(0, 0);
}

void Set_Console_Colour(Letter_Colour SymbolColour, Letter_Colour BackgroundColour)
{
	SetConsoleTextAttribute(ConsoleHandle, SymbolColour | (BackgroundColour << 4));
}

void Set_Console_Cursor(int row, int col)
{
	COORD CursorCoord;
	CursorCoord.X = col;
	CursorCoord.Y = row;
	SetConsoleCursorPosition( ConsoleHandle, CursorCoord);
}