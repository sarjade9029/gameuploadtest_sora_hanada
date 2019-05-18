#include "EnemyShot.h"
void EnemyShot::Init()
{
	enemyShotGraph = LoadGraph("data/texture/test.png");//画像の読込
	GetGraphSize(enemyShotGraph, &enemyShotW, &enemyShotH);//画像の縦横読みとり
	speed = 5;
	enemyShotX = 0;//座標の初期化
	enemyShotY = 0;
	enemyShotDmg = 1;
	angle = 0;
	NumericAngle = 0;
	enemyShotflag = false;//撃てる状態にしておく
	enemyShotVisibleFlag = false;
	sectorVectol = 0;
}

void EnemyShot::enemyShotSet(Player&player,Enemy&enemy)
{
	enemyShotX = enemy.positionX + (enemy.width * 0.75);//敵の中央
	enemyShotY = enemy.positionY + (enemy.height * 0.75);//敵の中央
	enemyShotX = enemyShotX - (enemyShotW * 0.5);
	enemyShotY = enemyShotY - (enemyShotH * 0.5);
	NumericAngle = atan2f((float)(player.positionY + (player.height * 0.75) - enemyShotY), (float)(player.positionX + (player.width * 0.75) - enemyShotX));
	angle = - NumericAngle * 180 / DX_PI_F ;//
	sectorVectol = enemy.shotSectorVectol;
	if (enemyShotflag == false && enemy.hitFlag == true)
	{
		enemyShotflag = true;//撃った後に進むようにする
		enemyShotVisibleFlag = true;//見えるようにする
	}
	enemy.shotIntarvalCount = 30;//待ち時間これは働いている
}

void EnemyShot::Update(Scroll&scroll)
{
	if (enemyShotflag == true)
	{
		enemyShotX += cosf(NumericAngle + sectorVectol) * speed;//反復
		enemyShotY += sinf(NumericAngle + sectorVectol) * speed;
	}
	if (/*enemyShotX > SCREEN_W + enemyShotW + scroll.positionX ||*/ enemyShotX < 63 || enemyShotY < 63 /*|| enemyShotY > SCREEN_H + enemyShotH + scroll.positionY*/ || enemyShotX > SCREEN_W * 2 - (enemyShotW + 64) || enemyShotY > SCREEN_H * 2 - (enemyShotH + 48) || enemyShotX < scroll.positionX || enemyShotY <scroll.positionY)//動いていなかったら弾の挙動がおかしくなる、消えないし
	{
		enemyShotVisibleFlag = false;//外に出たら見えなくして
	}
	if (enemyShotVisibleFlag == false)
	{
		enemyShotflag = false;//撃てる状態に戻す
	}
}

void EnemyShot::Draw(Scroll&scroll)
{
	if (enemyShotVisibleFlag == true)
	{
		DrawRotaGraph2F(enemyShotX - scroll.positionX + (enemyShotW * 0.5),enemyShotY - scroll.positionY + (enemyShotH * 0.5),(enemyShotW * 0.5), (enemyShotH * 0.5),1.0,(double)NumericAngle + sectorVectol,enemyShotGraph,TRUE);//表示
	}
}