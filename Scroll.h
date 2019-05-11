#pragma once
#include "DxLib.h"
#include "Common.h"
#include "Player.h"

class Scroll
{
public:
	int scrollPositionX;
	int scrollPositionY;
	void Init();
	void Update(Player & player);
};