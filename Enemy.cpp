#include "Enemy.h"
//敵の初期化
void Enemy::Init()
{
	graph = LoadGraph("data/texture/redbox.png");
	hitPoint = 3;
	positionX = 540;
	positionY = 540;
	GetGraphSize(graph, &width, &height);
	shotIntervalCount = 30;
	scorePoint = 200;
	shotSector = 0;
	shotSectorVector = 0;
	hitFlag = true;
	outsideScreen = true;
	sectorFlag = false;
	aliveFlag = false;
}

//敵の更新
void Enemy::Update(Player&player,Scroll&scroll)
{
	if (aliveFlag == true)
	{
		hitFlag = true;
	}

	if (shotIntervalCount != 0)
	{
		shotIntervalCount--;
	}

	if (shotIntervalCount == 0)
	{
		shotSectorVector = 0;

		if (shotSector - 2 == -2)
		{
			shotSectorVector -= DX_PI_F / 3;
		}
		if (shotSector - 2 == -1)
		{
			shotSectorVector -= DX_PI_F / 6;
		}
		if (shotSector - 2 == 0)
		{
			shotSectorVector = 0;
		}
		if (shotSector - 2 == 1)
		{
			shotSectorVector += DX_PI_F / 6;
		}
		if (shotSector - 2 == 2)
		{
			shotSectorVector += DX_PI_F / 3;
		}

		if (shotSector >= 4)
		{
			sectorFlag = true;
		}
		if (shotSector <= 0)
		{
			sectorFlag = false;
		}

		if (sectorFlag == false)
		{
			shotSector ++;
		}
		if (sectorFlag == true)
		{
			shotSector --;
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

	if ((positionX + width < SCREEN_W + scroll.positionX && positionX > 64 + scroll.positionX) && (positionY > 64 + scroll.positionY && positionY + height < SCREEN_H + scroll.positionY))
	{
		outsideScreen = false;
	}

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
    if (aliveFlag == true)
    {
            DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY,0.0,0.0,1.5,0.0, graph, TRUE);
    }
}