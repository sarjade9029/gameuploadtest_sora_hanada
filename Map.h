#pragma once
#include "DxLib.h"
#include "Scr.h"
#define TUTMAP_WIDTH       30
#define TUTMAP_HEIGHT      17
#define ALLMAP_CHIP_SIZE	64
#define MAINMAP_WIDTH		60 //58 1237 19
#define MAINMAP_HEIGHT		34 //32 682 10
class Map
{
public:
	int MapChip;
	void Inittut();
	void InitMain();
	void Drawtut();
	void DrawMain(Scr&scr);

	unsigned char datatut[TUTMAP_HEIGHT][TUTMAP_WIDTH];
	unsigned char datamain[MAINMAP_HEIGHT][MAINMAP_WIDTH];
};