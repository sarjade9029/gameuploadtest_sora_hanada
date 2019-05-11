#pragma once
#include "DxLib.h"
#include "Scr.h"
#include "player.h"
#include "Enemy.h"
#include <math.h>
#include "Common.h"
class EnemyShot
{
public:

	float	enemyShotX;
	float	enemyShotY;
	int		enemyShotGraph;
	int		enemyShotH;
	int		enemyShotW;
	int		enemyShotDmg;
	float	sectorvec;
	float	NumericAngle;
	float	angle;
	float	speed;
	bool    enemyShotflag;
	bool	enemyShotVisibleFlag;
	void    Init();
	void	enemyShotSet(Player&player,Enemy&enemy);
	void    Update(Scr&scr);
	void    Draw(Scr&scr);
};
