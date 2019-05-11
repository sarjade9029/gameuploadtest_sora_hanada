#pragma once
#include "DxLib.h"
#include "Scr.h"
#include "Common.h"
#include "Enemy.h"
#include "player.h"

class Player;
//現状使うものしか置いてない
class Shot
{
public:
	//shot_state
    double		X;
    double		Y;
    int		Xs;
    int		Ys;
	int		Dmg;
	int		wite;					//次の弾撃つまで待てよ
    bool	VisibleFlag;			//描画用
    bool	Shotflag;               // いきているたまか？

	//shot_graph
    int		Graph;					//仮しかない
    float		W;						//横幅
    float		H;						//縦幅

	//shot_vector
	bool	East;					//弾は東に進む
	bool	West;					//弾は西に進む
	bool	South;					//弾は南に進む
	bool	North;					//弾は北に進む
	bool	directionflag;			//方角指定


    void	Init();						//初期化
	void    Setshot( Player* player );
    void	Update(Scr&scr);
    void	Draw(Scr&scr);

};
