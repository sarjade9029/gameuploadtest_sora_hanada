#pragma once
#include "Shot.h"
#include "Scr.h"
#include "DxLib.h"
#include "Common.h"

class Player
{
public:
	int		Direction;					//弾の方向性
	int		Direction2;					//弾の方向性斜め用
	int		shotIntervalCount;			//前回打った弾をもとに今撃っていいか
    int		hitPoint;					//体力
	int		width;						//幅
	int		height;						//高さ
    int		xSpeed;						//横速度
    int		ySpeed;						//縦速度
    int		image;						//画像
	int		witeTime;					//待ち時間
	int		score;						//スコア
	int		playreScore;				//表示されるスコア
    float	X;							//
    float	Y;							//
	bool	ScoreFlag;					//スコアインクリメント計算用
	bool	HitFlag;					//当たりかどうか
    void	Init();						//
    void	Update(Scr&scr);			//
    void	Draw(Scr&scr);				//
};