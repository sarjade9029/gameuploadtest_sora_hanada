#pragma once
#include "DxLib.h"
#include "Scroll.h"
class Target
{
public:
	int state;			//ターゲットの細かい状態
	int positionX;				//横座標
	int positionY;				//縦座標
	int Height;
	int Width;
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
	bool playerPointFlag;			//ポイント獲得のフラグ
	bool enemyPointFlag;			//敵のポイント獲得のフラグ
	
	void Init();			//初期化
	void Update();			//更新
	void Draw(Scroll&scroll);		//描画
};