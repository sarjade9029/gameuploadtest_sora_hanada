#include "Shot.h"
#include "HitCheck.h"

//弾の初期化
void Shot::Init()
{
    Graph = LoadGraph("data/texture/blueshot.png");
    VisibleFlag = false;
	directionflag = false;
	wite = 15;
	Dmg = 1;
    GetGraphSizeF(Graph, &W, &H);
	Ys = 10;
	Xs = 10;
	Shotflag = false;
}

void Shot::Setshot(Player* player)
{
	//プレイヤーの画像の中央を取る
	//プレイヤーの横幅の中心
	positionX = (player->positionX) + (player->width*0.75);
	//プレイヤーの縦の中心
	positionY = (player->positionY) + (player->height*0.75);
	if (Shotflag == false && player->shotDirection != 0)
	{
		VisibleFlag = true;
		directionflag = true;
		Shotflag = true;
	}
	//生きているならもしくは生き返らせたなら方向を決める
	if (Shotflag == true)
	{
		if (player->shotDirection == 2 || player->shotDirection2 == 2)
		{
			//画像回転
			South = true;
		}
		if (player->shotDirection == 4 || player->shotDirection2 == 4)
		{
			//画像回転
			West = true;
		}
		if (player->shotDirection == 6 || player->shotDirection2 == 6)
		{
			//画像回転
			East = true;
		}
		if (player->shotDirection == 8 || player->shotDirection2 == 8)
		{
			//画像回転
			North = true;
		}
		player->shotIntervalCount = wite;
	}

}

//弾の更新(弾の移動と当たり判定
void Shot::Update(Scroll&scroll)
{
	if(directionflag == true)//動いている
	{ 
		if (South == true)
		{
			positionY += Ys;
		}
		if (North == true)
		{
			positionY -= Ys;
		}
		if (West == true)
		{
			positionX -= Xs;
		}
		if (East == true)
		{
			positionX += Xs;
		}
	}
	if (positionX > SCREEN_W - W + scroll.positionX|| positionX < 64 || positionY < 64 || positionY > SCREEN_H - H + scroll.positionY || positionX > SCREEN_W * 2 - (W + 64) || positionY > SCREEN_H * 2 - (H + 48) || positionX < scroll.positionX || positionY < scroll.positionY)//動いていなかったら弾の挙動がおかしくなる、消えないし
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
void Shot::Draw(Scroll&scroll)
{
	//最初の一発は画像がおかしくなることがある（斜めを二つ描画している）
    if (VisibleFlag == true)
    {
        // 画面に弾iを描画する
		if (South || North)
		{
			if (!East && !West)
			{
				DrawRotaGraph2F(positionX - scroll.positionX,positionY - scroll.positionY,0.0,0.0,1.0, 0.0,Graph, TRUE);//上下
			}
		}
		if (East || West)
		{
			if (!South && !North)
			{
				DrawRotaGraph2F(positionX - scroll.positionX,positionY - scroll.positionY,0.0,0.0,1.0, DX_PI_F/2,Graph, TRUE);//左右
			}
		}
		if ((North && East) || (South && West))
		{
			DrawRotaGraph2F(positionX - scroll.positionX,positionY - scroll.positionY,0.0,0.0,1.0, DX_PI_F/4,Graph, TRUE);//斜め右上or左下
		}
		if ((North && West) || (South && East))
		{
			DrawRotaGraph2F(positionX - scroll.positionX,positionY - scroll.positionY,0.0,0.0,1.0, DX_PI_F*1.75,Graph, TRUE);//斜め左上or右下
		}
    }
}