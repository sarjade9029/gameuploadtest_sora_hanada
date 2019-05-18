#include "target.h"
void Target::Init()
{
	//初期化
	redGraph = LoadGraph("data/texture/redtarget.png");
	redGraph2 = LoadGraph("data/texture/redtarget2.png");
	redGraph3 = LoadGraph("data/texture/redtarget3.png");
	redGraph1 = LoadGraph("data/texture/redtarget1.png");
	blueGraph = LoadGraph("data/texture/bluetarget.png");
	blueGraph2 = LoadGraph("data/texture/bluetarget2.png");
	blueGraph3 = LoadGraph("data/texture/bluetarget3.png");
	blueGraph1 = LoadGraph("data/texture/bluetarget1.png");
	grayGraph= LoadGraph("data/texture/graytarget.png");
	state = -5;
	positionX = 0;//固定位置四か所強制
	positionY = 0;
	ux = 0;
	uy = 0;
	GetGraphSize(redGraph,&W,&H);
	playerPointFlag = false;
	enemyPointFlag = false;
}

void Target::Update()
{
	if (state >= 1)
	{
		//クリスタルの色変更（青）
		if (state > 4)
		{
			state = 4;//青色
		}
		PptFlag = true;	
	}
	if (state >= 1 && state <= 3)
	{
		PptFlag = false;
	}
	if (state == 0)
	{
		//クリスタルの色（リセット）
		PptFlag = false;
		EptFlag = false;
	}
	if(state <= -1 && state >= 3)
	{
		EptFlag = false;
	}
	if (state <= -1)
	{
		//クリスタルの色変更（赤）
		if (state < -4)
		{
			state = -4;//赤色
		}
		EptFlag = true;
	}
}

void Target::Draw(Scroll&scroll)
{
	//クリスタルの描画
	if (state != 0)
	{
		//青表示

		if (PptFlag == true)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, blueGraph, TRUE);
		}
		if (state == 3)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, blueGraph3, TRUE);
		}
		if (state == 2)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, blueGraph2, TRUE);
		}
		if (state == 1)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, blueGraph1, TRUE);
		}

		//赤表示
		if (EptFlag == true)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, redGraph, TRUE);
		}
		if (state == -3)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, redGraph3, TRUE);
		}
		if (state == -2)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, redGraph2, TRUE);
		}
		if (state == -1)
		{
			DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, redGraph1, TRUE);
		}
	}
	else
	{
		DrawRotaGraph2F(positionX - scroll.positionX, positionY - scroll.positionY, 0.0, 0.0, 1.55, 0.0, grayGraph, TRUE);
	}

	//32*i+1=感覚を踏まえた値
	//間隔開けのための数字
	//1920-128=描画位置
	//同期は個々のhpと合わせればいい
	//再度小さいものを描画
	//描画の問題
	

	if (state != 0)
	{
		//青表示
		if (PptFlag == true)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph, TRUE);
		}
		if (state == 3)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph3, TRUE);
		}
		if (state == 2)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph2, TRUE);
		}
		if (state == 1)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph1, TRUE);
		}

		//赤表示
		if (EptFlag == true)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph, TRUE);
		}
		if (state == -3)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph3, TRUE);
		}
		if (state == -2)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph2, TRUE);
		}
		if (state == -1)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph1, TRUE);
		}
	}
	else
	{
		DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, grayGraph, TRUE);
	}

}