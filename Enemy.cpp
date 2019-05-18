#include "Enemy.h"
//敵の初期化
void Enemy::Init()
{
	//敵画像
	graph = LoadGraph("data/texture/redbox.png");
	//敵体力
	hitPoint = 3;
	//適当座標
	positionX = 540;
	positionY = 540;
	GetGraphSize(graph, &width, &height);
	enemyShotintarvalcount = 30;
	hitFlag = true;
	scorePoint = 200;
	sector = 0;
	sectorVectol = 0;
	sectorFlag = false;
	outsideScreen = true;
	aliveFlag = false;
}
//敵の更新
void Enemy::Update(Player&player,Scroll&scroll)
{
	if (aliveFlag == true)
	{
		hitFlag = true;
	}

	if (enemyShotintarvalcount != 0)//機能確認済み
	{
		enemyShotintarvalcount--;
	}
	//
	if (enemyShotintarvalcount == 0)
	{
		sectorVectol = 0;

		if (sector - 2 == -2)
		{
			sectorVectol -= DX_PI_F / 3;
		}
		if (sector - 2 == -1)
		{
			sectorVectol -= DX_PI_F / 6;
		}
		if (sector - 2 == 0)
		{
			sectorVectol = 0;
		}
		if (sector - 2 == 1)
		{
			sectorVectol += DX_PI_F / 6;
		}
		if (sector - 2 == 2)
		{
			sectorVectol += DX_PI_F / 3;
		}

		if (sector >= 4)
		{
			sectorFlag = true;
		}
		if (sector <= 0)
		{
			sectorFlag = false;
		}

		if (sectorFlag == false)
		{
			sector ++;
		}
		if (sectorFlag == true)
		{
			sector --;
		}
	}

	if (positionX >= SCREEN_W + scroll.positionX)//スクリーンの右端外
	{
		outsideScreen = true;
	}
	if (positionX + width <= scroll.positionX)
	{
		outsideScreen = true;
	}
	if (positionY + height <= scroll.positionY)
	{
		outsideScreen = true;
	}
	if (positionY >= SCREEN_H + scroll.positionY)
	{
		outsideScreen = true;
	}
	
	//
	if(positionX < 64)
	{
		positionX = 64;
	}
	if(positionX + 64 > SCREEN_W + 1920)
	{
		positionX = SCREEN_W + 1920 - 256;
	}
	if (positionY < 64)
	{
		positionY = 64;
	}
	if (positionY + 64 > SCREEN_H + 1080)
	{
		positionY = SCREEN_H + 1080 - 256;
	}

	//画面内
	if ((positionX + width < SCREEN_W + scroll.positionX && positionX > 64 + scroll.positionX) && (positionY > 64 + scroll.positionY && positionY + height < SCREEN_H + scroll.positionY))
	{
		outsideScreen = false;
	}

	//体力０なら消えようね
	if (hitPoint <= 0)
	{
		aliveFlag = false;
	}
	if (aliveFlag == false)
	{
		player.score += scorePoint;
		player.scoreFlag = true;
		hitFlag = false;
		outsideScreen =false;
		hitPoint = 3;
		
	}
}
//敵の描画
void Enemy::Draw(Scroll&scroll)
{
    if (aliveFlag == true)//ここは働いている
    {
            DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY,0.0,0.0,1.5,0.0, graph, TRUE);
    }
}