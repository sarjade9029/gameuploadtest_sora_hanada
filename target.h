#pragma once
#include "DxLib.h"
#include "Scr.h"
class Tg
{
public:
	int Thp;			//ターゲットの細かい状態
	int Ppt;			//プレイヤーのポイント
	int Ept;			//敵のポイント
	int X;				//横座標
	int Y;				//縦座標
	int H;
	int W;
	int ux;
	int uy;
	int redGraph;
	int	redGraph2;			//3段階
	int	redGraph3;			//2段階
	int	redGraph1;			//1段階
	int blueGraph;
	int	blueGraph2;			//3段階
	int	blueGraph3;			//2段階
	int	blueGraph1;			//1段階
	int grayGraph;
	bool Visibleflag;
	bool HitFlag;
	bool PptFlag;			//ポイント獲得のフラグ
	bool EptFlag;			//敵のポイント獲得のフラグ
	
	void Init();			//初期化
	void Update();			//更新
	void Draw(Scr&scr);		//描画
};