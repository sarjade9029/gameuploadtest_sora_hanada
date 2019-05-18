#pragma once
#include "DxLib.h"
#include "Common.h"
#include "Player.h"

class Scroll
{
public:
	int positionX;				//画面スクロールの横の位置
	int positionY;				//画面スクロールの縦の位置

	void Init();						//
	void Update(Player & player);		//
};