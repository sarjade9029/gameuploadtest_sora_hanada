#include "Shot.h"
#include "HitCheck.h"

//弾の初期化
void Shot::Init()
{
    // ショットのグラフィックをメモリにロード.
    Graph = LoadGraph("data/texture/blueshot.png");


    // 弾が画面上に存在しているか保持する変数に『存在していない』を意味するfalseを代入しておく
    VisibleFlag = false;
	directionflag = false;
	
	wite = 15;
	Dmg = 1;
    // 弾のグラフィックのサイズ
    GetGraphSizeF(Graph, &W, &H);
	Ys = 10;
	Xs = 10;

	Shotflag = false;
}

void Shot::Setshot(Player* player)
{
	//プレイヤーの画像の中央を取る
	//プレイヤーの横幅の中心
	X = (player->X) + (player->W*0.75);
	//プレイヤーの縦の中心
	Y = (player->Y) + (player->H*0.75);
	if (Shotflag == false && player->direction != 0)
	{
		VisibleFlag = true;
		directionflag = true;
		Shotflag = true;
	}
	//生きているならもしくは生き返らせたなら方向を決める
	if (Shotflag == true)
	{
		if (player->direction == 2 || player->direction2 == 2)
		{
			//画像回転
			South = true;
		}
		if (player->direction == 4 || player->direction2 == 4)
		{
			//画像回転
			West = true;
		}
		if (player->direction == 6 || player->direction2 == 6)
		{
			//画像回転
			East = true;
		}
		if (player->direction == 8 || player->direction2 == 8)
		{
			//画像回転
			North = true;
		}
		player->shotIntervalCount = wite;
	}

}

//弾の更新(弾の移動と当たり判定
void Shot::Update(Scr&scr)
{
	if(directionflag == true)//動いている
	{ 
		if (South == true)
		{
			Y += Ys;
		}
		if (North == true)
		{
			Y -= Ys;
		}
		if (West == true)
		{
			X -= Xs;
		}
		if (East == true)
		{
			X += Xs;
		}
	}
	if (X > SCREEN_W - W + scr.scrX|| X < 64 || Y < 64 || Y > SCREEN_H - H + scr.scrY || X > SCREEN_W * 2 - (W + 64) || Y > SCREEN_H * 2 - (H + 48) || X < scr.scrX || Y < scr.scrY)//動いていなかったら弾の挙動がおかしくなる、消えないし
	{
		VisibleFlag = false;
	}
	if (VisibleFlag == false)
	{
		directionflag = false;
		Shotflag = false;
		South = false;
		North = false;
		East = false;
		West = false;
	}
	
}

//弾の描画
void Shot::Draw(Scr&scr)
{
	//最初の一発は画像がおかしくなることがある（斜めを二つ描画している）
    if (VisibleFlag == true)
    {
        // 画面に弾iを描画する
		if (South || North)
		{
			if (!East && !West)
			{
				DrawRotaGraph2F(X - scr.scrX,Y - scr.scrY,0.0,0.0,1.0, 0.0,Graph, TRUE);//上下
			}
		}
		if (East || West)
		{
			if (!South && !North)
			{
				DrawRotaGraph2F(X - scr.scrX,Y - scr.scrY,0.0,0.0,1.0, DX_PI_F/2,Graph, TRUE);//左右
			}
		}
		if ((North && East) || (South && West))
		{
			DrawRotaGraph2F(X - scr.scrX,Y - scr.scrY,0.0,0.0,1.0, DX_PI_F/4,Graph, TRUE);//斜め右上or左下
		}
		if ((North && West) || (South && East))
		{
			DrawRotaGraph2F(X - scr.scrX,Y - scr.scrY,0.0,0.0,1.0, DX_PI_F*1.75,Graph, TRUE);//斜め左上or右下
		}
    }
}