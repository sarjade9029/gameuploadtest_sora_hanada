#pragma once
#include "DxLib.h"
#include "Scroll.h"
#include "Common.h"
class Enemy 
{
public:
	int		shotIntervalCount;						//エネミーが弾を出すためのクールタイム
	int		shotSector;								//エネミーの弾の発射方向をプレイヤーからずらす
	
	//場所を変える
	int		scorePoint;								//プレイヤーのスコアに加算する値
    
	int		graph;									//エネミー画像
    int		width;									//エネミー画像の縦
    int		height;									//エネミー画像の横
    int		hitPoint;								//エネミーの体力

	float	positionX;								//エネミーの横の位置
	float	positionY;								//エネミーの縦の位置

	//命名
	float	shotSectorVector;						//プレイヤーに向かって打つ弾の角度
	
	bool	sectorFlag;								//エネミーの弾を
    bool	hitFlag;								//エネミーの当たり判定
	bool	outsideScreen;							//エネミーが画面内に存在するかどうかの判定
	bool	aliveFlag;								//エネミーが生きているか死んでいるかの判定
	
	void    Init();									//エネミー初期化
    void    Update(Player&player,Scroll&scroll);	//エネミー更新
    void    Draw(Scroll&scroll);					//エネミー描画

};