#pragma once
#include "DxLib.h"
#include "Common.h"
#include "Player.h"

class Scroll
{
public:
	int scrollPositionX;				//画面スクロールの横の位置
	int scrollPositionY;				//画面スクロールの縦の位置

	void Init();						//
	void Update(Player & player);		//
};