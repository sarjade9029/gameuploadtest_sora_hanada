#include "Player.h"
//プレイヤーの初期化
void Player::Init()
{
	direction = 0;
	direction2 = 0;
	shotIntervalCount = 15;
	image = LoadGraph("data/texture/bluebox.png");
	hitPoint = 100;
    positionX = 912;
    positionY = 492;
    xSpeed = 7;
    ySpeed = 7;
	witeTime = 60;
	hitFlag = true;
	scoreFlag = false;
	GetGraphSize(image, &width, &height);
}

//プレイヤーの更新
void Player::Update(Scr&scr)
{
	if (shotIntervalCount != 0)//機能確認済み
	{
		shotIntervalCount--;
	}
	if (witeTime != 0)
	{
		witeTime--;
	}
	if (scoreFlag == true)
	{
		if (playerScore <= score)
		{
			playerScore++;
			playerScore++;
			if (playerScore == score)
			{
				scoreFlag = false;
			}
		}
	}

	//左移動
    if (CheckHitKey(KEY_INPUT_A) == 1)
    {
		positionX -= xSpeed;
    }
	//右移動
    if (CheckHitKey(KEY_INPUT_D) == 1)
    {
		positionX += xSpeed;
    }
	//上移動
	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		positionY -= ySpeed;
	}
	//下移動
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		positionY += ySpeed;
	}

	//強制壁判定
	if (positionX > SCREEN_W - (width + 15 + 64) + scr.scrX)//外に出ようとすると戻される
	{
		positionX= SCREEN_W - (width + 15 + 64) + scr.scrX;//
	}
	if (positionX < 64)
	{
		positionX = 64;
	}
	if (positionY < 64)
	{
		positionY = 64;
	}
	if (positionY > SCREEN_H - (height + 15 + 64) + scr.scrY)
	{
		positionY = SCREEN_H - (height + 15 + 64) + scr.scrY;
	}

	//弾の発射制御と方向及び   動作確認済み

	direction = 0;
	direction2 = 0;

	if (CheckHitKey(KEY_INPUT_UP))
	{
		direction = 8;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		direction = 2;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		direction = 6;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		direction = 4;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP))
	{
		direction = 4;
		direction2 = 8;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN))
	{
		direction = 4;
		direction2 = 2;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP))
	{
		direction = 6;
		direction2 = 8;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN))
	{
		direction = 6;
		direction2 = 2;
	}
	//シフトを押しながらなら必ず弾が斜めにでる
	if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
	{
		if (CheckHitKey(KEY_INPUT_UP))
		{
			direction = 0;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			direction = 0;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			direction = 0;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			direction = 0;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP))
		{
			direction = 4;
			direction2 = 8;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN))
		{
			direction = 4;
			direction2 = 2;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP))
		{
			direction = 6;
			direction2 = 8;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN))
		{
			direction = 6;
			direction2 = 2;
		}
	}

	if (hitPoint <= 0)
	{
		hitFlag = false;
	}

}

//プレイヤーの描画
void Player::Draw(Scr&scr)
{
	if (hitFlag == true)
	{
		DrawRotaGraph2F(positionX - scr.scrX,positionY - scr.scrY,0,0,1.5,0.0,image,TRUE);
	}
}