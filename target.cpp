#include "target.h"
void Tg::Init()
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
	Thp = -5;
	Ppt = 0;
	Ept = 0;
	X = 0;//固定位置四か所強制
	Y = 0;
	ux = 0;
	uy = 0;
	GetGraphSize(redGraph,&W,&H);
	PptFlag = false;
	EptFlag = false;
}

void Tg::Update()
{
	if (Thp >= 1)
	{
		//クリスタルの色変更（青）
		if (Thp > 4)
		{
			Thp = 4;//青色
		}
		PptFlag = true;	
	}
	if (Thp >= 1 && Thp <= 3)
	{
		PptFlag = false;
	}
	if (Thp == 0)
	{
		//クリスタルの色（リセット）
		PptFlag = false;
		EptFlag = false;
	}
	if(Thp <= -1 && Thp >= 3)
	{
		EptFlag = false;
	}
	if (Thp <= -1)
	{
		//クリスタルの色変更（赤）
		if (Thp < -4)
		{
			Thp = -4;//赤色
		}
		EptFlag = true;
	}
}

void Tg::Draw(Scr&scr)
{
	//クリスタルの描画
	if (Thp != 0)
	{
		//青表示

		if (PptFlag == true)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, blueGraph, TRUE);
		}
		if (Thp == 3)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, blueGraph3, TRUE);
		}
		if (Thp == 2)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, blueGraph2, TRUE);
		}
		if (Thp == 1)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, blueGraph1, TRUE);
		}

		//赤表示
		if (EptFlag == true)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, redGraph, TRUE);
		}
		if (Thp == -3)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, redGraph3, TRUE);
		}
		if (Thp == -2)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, redGraph2, TRUE);
		}
		if (Thp == -1)
		{
			DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, redGraph1, TRUE);
		}
	}
	else
	{
		DrawRotaGraph2F(X - scr.scrX, Y - scr.scrY, 0.0, 0.0, 1.55, 0.0, grayGraph, TRUE);
	}

	//32*i+1=感覚を踏まえた値
	//間隔開けのための数字
	//1920-128=描画位置
	//同期は個々のhpと合わせればいい
	//再度小さいものを描画
	//描画の問題
	

	if (Thp != 0)
	{
		//青表示
		if (PptFlag == true)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph, TRUE);
		}
		if (Thp == 3)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph3, TRUE);
		}
		if (Thp == 2)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph2, TRUE);
		}
		if (Thp == 1)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, blueGraph1, TRUE);
		}

		//赤表示
		if (EptFlag == true)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph, TRUE);
		}
		if (Thp == -3)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph3, TRUE);
		}
		if (Thp == -2)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph2, TRUE);
		}
		if (Thp == -1)
		{
			DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, redGraph1, TRUE);
		}
	}
	else
	{
		DrawRotaGraph2F(ux, uy, 0.0, 0.0, 1.55, 0.0, grayGraph, TRUE);
	}

}