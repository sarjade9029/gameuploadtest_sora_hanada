#include "Enemy.h"
//敵の初期化
void Enemy::Init()
{
	//敵画像
	Graph = LoadGraph("data/texture/redbox.png");
	//敵体力
	Life = 3;
	//適当座標
	X = 540;//最初の一体が0.0に出ることの修正、出現位置は画面内？
	Y = 540;
	GetGraphSize(Graph, &W, &H);
	enemyShotintarvalcount = 30;
	HitFlag = true;
	point = 200;
	sector = 0;
	sectorvec = 0;
	sectorflag = false;
	outside_screen = true;
	aliveFlag = false;
}
//敵の更新
void Enemy::Update(Player&player,Scr&scr)
{
	if (aliveFlag == true)
	{
		HitFlag = true;
	}

	if (enemyShotintarvalcount != 0)//機能確認済み
	{
		enemyShotintarvalcount--;
	}
	//
	if (enemyShotintarvalcount == 0)
	{
		sectorvec = 0;

		if (sector - 2 == -2)
		{
			sectorvec -= DX_PI_F / 3;
		}
		if (sector - 2 == -1)
		{
			sectorvec -= DX_PI_F / 6;
		}
		if (sector - 2 == 0)
		{
			sectorvec = 0;
		}
		if (sector - 2 == 1)
		{
			sectorvec += DX_PI_F / 6;
		}
		if (sector - 2 == 2)
		{
			sectorvec += DX_PI_F / 3;
		}

		if (sector >= 4)
		{
			sectorflag = true;
		}
		if (sector <= 0)
		{
			sectorflag = false;
		}

		if (sectorflag == false)
		{
			sector ++;
		}
		if (sectorflag == true)
		{
			sector --;
		}
	}

	if (X >= SCREEN_W + scr.scrX)//スクリーンの右端外
	{
		outside_screen = true;
	}
	if (X + W <= scr.scrX)
	{
		outside_screen = true;
	}
	if (Y + H <= scr.scrY)
	{
		outside_screen = true;
	}
	if (Y >= SCREEN_H + scr.scrY)
	{
		outside_screen = true;
	}
	
	//
	if(X < 64)
	{
		X = 64;
	}
	if(X + 64 > SCREEN_W + 1920)
	{
		X = SCREEN_W + 1920 - 256;
	}
	if (Y < 64)
	{
		Y = 64;
	}
	if (Y + 64 > SCREEN_H + 1080)
	{
		Y = SCREEN_H + 1080 - 256;
	}

	//画面内
	if ((X + W < SCREEN_W + scr.scrX && X > 64 + scr.scrX) && (Y > 64 + scr.scrY && Y + H < SCREEN_H + scr.scrY))
	{
		outside_screen = false;
	}

	//体力０なら消えようね
	if (Life <= 0)
	{
		aliveFlag = false;
	}
	if (aliveFlag == false)
	{
		player.score += point;
		player.scoreflag = true;
		HitFlag = false;
		outside_screen =false;
		Life = 3;
		
	}
}
//敵の描画
void Enemy::Draw(Scr&scr)
{
    if (aliveFlag == true)//ここは働いている
    {
            DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY,0.0,0.0,1.5,0.0, Graph, TRUE);
    }
}