#pragma once
#include "DxLib.h"
#include "Common.h"
#include "target.h"
#include "bitmapText.h"
class UI
{
public:

	int		mainmusic;							//メイン局
	int		shothit;							//ショットの音
	int		titleGraph;							//タイトル画像
	int		endGraph;							//終わりの画像
	int		framenum;							//ゲーム開始（タイトルからではなくプレイ）からの時間
	int		starttime;							//ゲーム開始（タイトル辺りから）
	int		zerotime;							//一定のタイミングでとる
	int		drawtime;							//描画用の時間
	int		waittime;
	int     tutgraph;
	int     tutgraph2;
	int		shiftGraph;
	int		textGraph;
	int		textGraph2;
	int		textGraph3;
	int		textGraph4;
	int		enemycount;
	int		enemycount2;
	int		enemycount3;
	int		enemycount4;
	int		cs[TARGET];							//ui用画像
	void	Init(BitmapText & text);			//
	void	Draw(Tg&target);					//

};