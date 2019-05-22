#pragma once
#include "DxLib.h"
#include "Scroll.h"
#include "Common.h"
class Map
{
public:
	int MapChip;
	void Inittut();
	void InitMain();
	void Drawtut();
	void DrawMain(Scroll&scroll);

	unsigned char datatut[TUTORIAL_MAP_HEIGHT][TUTORIAL_MAP_WIDTH];
	unsigned char datamain[MAIN_MAP_HEIGHT][MAIN_MAP_WIDTH];
};