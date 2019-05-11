#pragma once
#include "DxLib.h"
#include "Scr.h"
#include "Common.h"
class Enemy 
{
public:
	int		enemyShotintarvalcount;
	float	X;
	float	Y;
	int		sector;
	float	sectorvec;
	int		point;
    int		Graph;
    int		W;
    int		H;
    int		Life;
	bool	sectorflag;
    bool	HitFlag;
	bool	outside_screen;
	bool	aliveFlag;
	void    Init();
    void    Update(Player&player,Scr&scr);
    void    Draw(Scr&scr);

};