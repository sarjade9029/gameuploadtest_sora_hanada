#include "Player.h"
//プレイヤーの初期化
void Player::Init()
{
	shotDirection = 0;
	shotDirection2 = 0;
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
void Player::Update(Scroll&scroll)
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
	if (positionX > SCREEN_W - (width + 15 + 64) + scroll.positionX)//外に出ようとすると戻される
	{
		positionX= SCREEN_W - (width + 15 + 64) + scroll.positionX;//
	}
	if (positionX < 64)
	{
		positionX = 64;
	}
	if (positionY < 64)
	{
		positionY = 64;
	}
	if (positionY > SCREEN_H - (height + 15 + 64) + scroll.positionY)
	{
		positionY = SCREEN_H - (height + 15 + 64) + scroll.positionY;
	}

	//弾の発射制御と方向及び   動作確認済み

	shotDirection = 0;
	shotDirection2 = 0;

	if (CheckHitKey(KEY_INPUT_UP))
	{
		shotDirection = 8;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		shotDirection = 2;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		shotDirection = 6;
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		shotDirection = 4;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP))
	{
		shotDirection = 4;
		shotDirection2 = 8;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN))
	{
		shotDirection = 4;
		shotDirection2 = 2;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP))
	{
		shotDirection = 6;
		shotDirection2 = 8;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN))
	{
		shotDirection = 6;
		shotDirection2 = 2;
	}
	//シフトを押しながらなら必ず弾が斜めにでる
	if (CheckHitKey(KEY_INPUT_LSHIFT) || CheckHitKey(KEY_INPUT_RSHIFT))
	{
		if (CheckHitKey(KEY_INPUT_UP))
		{
			shotDirection = 0;
		}
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			shotDirection = 0;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT))
		{
			shotDirection = 0;
		}
		if (CheckHitKey(KEY_INPUT_LEFT))
		{
			shotDirection = 0;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_UP))
		{
			shotDirection = 4;
			shotDirection2 = 8;
		}
		if (CheckHitKey(KEY_INPUT_LEFT) && CheckHitKey(KEY_INPUT_DOWN))
		{
			shotDirection = 4;
			shotDirection2 = 2;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_UP))
		{
			shotDirection = 6;
			shotDirection2 = 8;
		}
		if (CheckHitKey(KEY_INPUT_RIGHT) && CheckHitKey(KEY_INPUT_DOWN))
		{
			shotDirection = 6;
			shotDirection2 = 2;
		}
	}

	if (hitPoint <= 0)
	{
		hitFlag = false;
	}

}

//プレイヤーの描画
void Player::Draw(Scroll&scroll)
{
	if (hitFlag == true)
	{
		DrawRotaGraph2F(positionX - scroll.positionX,positionY - scroll.positionY,0,0,1.5,0.0,image,TRUE);
	}
}