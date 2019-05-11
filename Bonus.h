#pragma once
#include "Dxlib.h"
#include "target.h"

class Bonus
{
public:

	int point;						//スコア加算

	bool aliveflag;					//条件がそろったら

	bool blueflag;
	bool blueflag2;
	bool blueflag3;
	bool blueflag4;

	void Init();					//初期化
	void Update(Player&player);		//アップデート
};