#pragma once
#include "DxLib.h"
#include "Common.h"
#include "Player.h"

class Scr
{
public:
	int scrX;
	int scrY;
	void Init();
	void Update(Player & player);
};