#pragma once
#include "Shot.h"
#include "Scroll.h"
#include "DxLib.h"
#include "Common.h"

class Player
{
public:
	int		shotDirection;				//弾の方向
	int		shotDirection2;				//弾の方向斜め
	int		shotIntervalCount;			//プレイヤーの弾の発射待機時間
    int		hitPoint;					//体力
	int		width;						//幅
	int		height;						//高さ
    int		xSpeed;						//横速度
    int		ySpeed;						//縦速度
    int		image;						//画像
	//場所を変える
	int		witeTime;					//敵出現までの時間
	int		score;						//実際のスコア
	int		playerScore;				//表示されるスコア

    float	positionX;					//プレイヤーの横の位置
    float	positionY;					//プレイヤーの縦の位置
	bool	scoreFlag;					//スコアインクリメント計算用フラグ
	bool	hitFlag;					//敵の弾に当たるようにするフラグ

    void	Init();						//プレイヤーの初期化
    void	Update(Scroll&scroll);			//プレイヤーのアップデート
    void	Draw(Scroll&scroll);				//プレイヤーの描画
};