#pragma once

#include"Letter_Colour.h"
#include "Render_System.h"

const int Rows_Count = Screen_Rows;
const int Columns_Count = Screen_Columns;
const int Number_Of_Levels = 2;

const unsigned char CellSymbol_Empty			= ' ';
const unsigned char CellSymbol_Brick_Wall		= '#';
const unsigned char CellSymbol_Steel_Wall		= '@';
const unsigned char CellSymbol_Abyss			= 'a';
const unsigned char CellSymbol_Pipe				= 'p';
const unsigned char CellSymbol_Crystal			= '0';
const unsigned char CellSymbol_Box				= '?';
const unsigned char CellSymbol_Opened_Box		= '&';
const unsigned char CellSymbol_Mushroom			= '^';
const unsigned char CellSymbol_Mushroom_Box		= '!';
const unsigned char CellSymbol_Hero				= 'h';
const unsigned char CellSymbol_Goomba			= 'g';
const unsigned char CellSymbol_Exit				= '|';
const unsigned char CellSymbol_Flag				= '>';
const unsigned char CellSymbol_Jumper			= '$';

const unsigned char LevelData0[Number_Of_Levels][Rows_Count][Columns_Count+1] =
{
	//level 1
	{
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"#         0                                                          g         #",
	"#      @                                                             @     |>  #",
	"#     @@     @                  ##?#        0 0 0                   @@     |   #",
	"#    @@@     @@      pppp                            pppp          @@@     |   #",
	"#   @@@@ g   @@@      pp   g            g g           pp          @@@@     |   #",
	"#  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
	"#                                                                              #",
	"#                   0                                      0 0                 #",
	"# @       #??#     ###            !               ?####   ######               #",
	"# @@                                                                           #",
	"# @@@                                                                          #",
	"# @@@@     ##      ######     ?   ?   ?     ?#    #               ##           #",
	"# @@@@@                                                                        #",
	"# @@@@@@               # g g g g            g             g g            #     #",
	"# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##@    #",
	"#                                                                              #",
	"#               ?                                                            ###",
	"#                                                                              #",
	"#                                              pppp                     #!#    #",
	"#          ?  #!#?#                 pppp        pp        pppp          # #    #",
	"#                        pppp        pp         pp         pp                  #",
	"#  h           g          pp         pp g       pp     g g pp        #   g     #",
	"# #################################################################  ###########",
	"#a#################################################################aa###########",
	},
	//level 2 here
	{
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"#                                                                              #",
	"#   |>                                                                   @@@@  #",
	"#   |                                                                   @@@   ?#",
	"#   |                                                                  @@      #",
	"#   |     g                              g g                          @        #",
	"#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@@@@#",
	"#                                                                              #",
	"#                                                                     ###      #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                           ###!#?#            #",
	"#                                                           ###!#?#            #",
	"#                                                                              #",
	"#                        g                  g                                  #",
	"# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
	"#                                                                              #",
	"#?                                                                             #",
	"#                         !#?                         #                        #",
	"#                                                     ##                       #",
	"# pppp                                     ?##!       ## #                     #",
	"#  pp                    pppp                         ## ##                    #",
	"#  pp                     pp                          ## ###                h  #",
	"# #####$################################################ ############## ########",
	"#a######################################################a##############a########",
	}
	//level template

	/*
	{
	"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
	"#                                                                              #",
	"#   |>                                                                         #",
	"#   |                                                                          #",
	"#   |                                                                          #",
	"#   |     g                              g g                                   #",
	"#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"# @                      g g g g            g             g g                  #",
	"# @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##@@@@@#",
	"#                                                                              #",
	"#?                                                                             #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"#                                                                              #",
	"#              g                       g              g g               g  h   #",
	"# #####$############################################################### ########",
	"#a#####################################################################a########",
	}
	*/
};

const int HIDr = 12, HIDc = 21;
const char Hero_Is_Dead [HIDr][HIDc] =
	{
		"                    ",
		" ###################",
		" #                 #",
		" # HERO IS DEAD!!! #",
		" #                 #",
		" ###################",
		" ###################",
		" #   Press space   #",
		" #to restart level #",
		" #       ...       #",
		" ###################",
		"                    ",
	};

const int HIVr = 12, HIVc = 21;
const char Victory [HIDr][HIDc] =
	{
		"                    ",
		" ###################",
		" #                 #",
		" #  HERO WINS!!!   #",
		" #                 #",
		" ###################",
		" ###################",
		" #   Press space   #",
		" #to enter the next#",
		" #     level...    #",
		" ###################",
		"                    ",
	};

unsigned char GetRenderCellSymbol(unsigned char CellSymbol);
Letter_Colour GetRenderCellSymbolColour (unsigned char CellSymbol);
Letter_Colour GetRenderCellSymbolBackgroundColour (unsigned char CellSymbol);
Letter_Colour GetRenderHeroColour (int HeroHealth);

unsigned char GetRenderCellSymbol(unsigned char CellSymbol){
	switch(CellSymbol){
	case CellSymbol_Empty:				return ' ';
	case CellSymbol_Brick_Wall:			return 177;
	case CellSymbol_Steel_Wall:			return 178;
	case CellSymbol_Abyss:				return ' ';
	case CellSymbol_Pipe:				return 178;
	case CellSymbol_Crystal:			return 4;
	case CellSymbol_Box:				return '?';
	case CellSymbol_Opened_Box:			return 254;
	case CellSymbol_Mushroom:			return 6;
	case CellSymbol_Mushroom_Box:		return '?';
	case CellSymbol_Hero:				return 2;
	case CellSymbol_Goomba:				return 2;
	case CellSymbol_Exit:				return 222;
	case CellSymbol_Flag:				return 16;
	case CellSymbol_Jumper:				return 15;
	}

	return '?';
}

Letter_Colour GetRenderCellSymbolColour (unsigned char CellSymbol){
	switch(CellSymbol){
	case CellSymbol_Brick_Wall:			return Letter_Colour_Dark_Yellow;
	case CellSymbol_Steel_Wall:			return Letter_Colour_White;
	case CellSymbol_Pipe:				return Letter_Colour_Green;
	case CellSymbol_Crystal:			return Letter_Colour_Cyan;
	case CellSymbol_Box:				return Letter_Colour_Dark_Red;
	case CellSymbol_Opened_Box:			return Letter_Colour_Grey;
	case CellSymbol_Mushroom:			return Letter_Colour_Red;
	case CellSymbol_Mushroom_Box:		return Letter_Colour_Dark_Red;
	case CellSymbol_Hero:				return Letter_Colour_Yellow;
	case CellSymbol_Goomba:				return Letter_Colour_Dark_Red;
	case CellSymbol_Exit:				return Letter_Colour_Green;
	case CellSymbol_Flag:				return Letter_Colour_White;
	case CellSymbol_Jumper:				return Letter_Colour_Cyan;
	}

	return Letter_Colour_Grey;
}

Letter_Colour GetRenderCellSymbolBackgroundColour (unsigned char CellSymbol){
	switch(CellSymbol){
	case CellSymbol_Brick_Wall:			return Letter_Colour_Red;
	case CellSymbol_Steel_Wall:			return Letter_Colour_Dark_Grey;
	case CellSymbol_Pipe:				return Letter_Colour_Dark_Green;
	case CellSymbol_Box:				return Letter_Colour_Yellow;
	case CellSymbol_Opened_Box:			return Letter_Colour_Dark_Grey;
	case CellSymbol_Mushroom_Box:		return Letter_Colour_Yellow;
	case CellSymbol_Jumper:				return Letter_Colour_Dark_Cyan;
	}

	return Letter_Colour_Black;
}

Letter_Colour GetRenderHeroColour (int HeroHealth){
	switch(HeroHealth){
		case 2: return Letter_Colour_Red;
	}

	return Letter_Colour_Yellow;
}

float GetSpeedFromCell(char CellSymbol){
	switch(CellSymbol){
		case CellSymbol_Jumper:			return 10;
	}
}