#include "Player.h"
//プレイヤーの初期化
void Player::Init()
{
	direction = 0;
	direction2 = 0;
	shotIntervalCount = 15;
	Img = LoadGraph("data/texture/bluebox.png");
	Hp = 100;
    X = 912;
    Y = 492;
    Xs = 7;
    Ys = 7;
	addcounter = 1;
	witetime = 60;
	HitFlag = true;
	scoreflag = false;
	GetGraphSize(Img, &W, &H);
}

//プレイヤーの更新
void Player::Update(Scr&scr)
{
	if (shotIntervalCount != 0)//機能確認済み
	{
		shotIntervalCount--;
	}
	if (witetime != 0)
	{
		witetime--;
	}
	if (scoreflag == true)
	{
		if (plscore <= score)
		{
			plscore++;
			plscore++;
			if (plscore == score)
			{
				scoreflag = false;
			}
		}
	}

	//左移動
    if (CheckHitKey(KEY_INPUT_A) == 1)
    {
		X -= Xs;
    }
	//右移動
    if (CheckHitKey(KEY_INPUT_D) == 1)
    {
		X += Xs;
    }
	//上移動
	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		Y -= Ys;
	}
	//下移動
	if (CheckHitKey(KEY_INPUT_S) == 1)
	{
		Y += Ys;
	}

	//強制壁判定
	if (X > SCREEN_W - (W + 15 + 64) + scr.scrX)//外に出ようとすると戻される
	{
		X = SCREEN_W - (W + 15 + 64) + scr.scrX;//
	}
	if (X < 64)
	{
		X = 64;
	}
	if (Y < 64)
	{
		Y = 64;
	}
	if (Y > SCREEN_H - (H + 15 + 64) + scr.scrY)
	{
		Y = SCREEN_H - (H + 15 + 64) + scr.scrY;
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

	if (Hp <= 0)
	{
		HitFlag = false;
	}

}

//プレイヤーの描画
void Player::Draw(Scr&scr)
{
	if (HitFlag == true)
	{
		DrawRotaGraph2F(X - scr.scrX,Y - scr.scrY,0,0,1.5,0.0,Img,TRUE);
	}
}