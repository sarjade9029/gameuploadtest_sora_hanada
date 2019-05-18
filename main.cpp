// block.cpp : アプリケーションのエントリ ポイントを定義します。
#include "DxLib.h"
#include <windows.h>
#include "Common.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyShot.h"
#include "Shot.h"
#include "target.h"
#include "Map.h"
#include "Scroll.h"
#include "HitCheck.h"
#include "bitmapText.h"
#include "UI.h"
#include "Bonus.h"
#include <math.h>
#pragma warning (disable:4996)

Player player;					//プレイヤー
Enemy *enemy;					//エネミー
Shot *shot;						//ショット
Target *target;						//ターゲット　
Map map;						//マップ
HitCheck hitcheck;				//敵、自機の弾の判定　	
EnemyShot **enemyshot;			//敵の弾
Scroll scroll;						//スクロール
UI ui;							//UI
BitmapText text;				//テキスト　
Bonus bouns;

bool ProgramLooping = true;
int status;

enum { TITLE, MENU, TUTORIAL, PLAY, OVER, CLEAR };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// 解像度をSCREEN_W*SCREEN_H、colorを16bitに設定.
	SetGraphMode(SCREEN_W, SCREEN_H, 16);
	// ウインドウモードに.
	ChangeWindowMode(TRUE);
	// DXライブラリ初期化処理
	DxLib_Init();

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	while (1)
	{
		SetTextureAddressMode(DX_TEXADDRESS_WRAP);
		SetDrawScreen(DX_SCREEN_BACK);

		//初期化
		{
			int seed;
			seed = GetNowCount();
			srand(seed);
		}

		//SHOTやenemyの詳細な数はCommonへ
		target = new Target[TARGET];
		enemy = new Enemy[ENEMY];
		shot = new Shot[SHOT];
		enemyshot = new EnemyShot*[SHOT];
		for (int i = 0; i < SHOT; i++)
		{
			enemyshot[i] = new EnemyShot[SHOT];
		}

		//プレイヤーの初期化
		player.Init();
		//敵弾の初期化
		for (int i = 0; i < SHOT; i++)
		{
			shot[i].Init();
			for (int j = 0; j < ENEMY; j++)
			{
				enemyshot[i][j].Init();
			}
		}

		//敵初期化
		for (int i = 0; i < ENEMY; i++)
		{
			enemy[i].Init();
		}

		//的初期化
		for (int i = 0; i < TARGET; i++)
		{
			target[i].Init();
		}

		ui.Init(text);

		//ここの改善は分からん,ターゲットの位置取り
		//左上
		target[0].positionX = 640;
		target[0].positionY = 424;
		target[0].ux = 1680;
		target[0].uy = 1020;
		//右上
		target[1].positionX = SCREEN_W * 2 - 640;
		target[1].positionY = 424;
		target[1].ux = 1740;
		target[1].uy = 1020;
		//左下
		target[2].positionX = 640;
		target[2].positionY = SCREEN_H * 2 - 424;
		target[2].ux = 1800;
		target[2].uy = 1020;
		//右下
		target[3].positionX = SCREEN_W * 2 - 640;
		target[3].positionY = SCREEN_H * 2 - 424;
		target[3].ux = 1860;
		target[3].uy = 1020;

		//マップ初期化
		map.Inittut();

		//画面を綺麗に消す
		ClearDrawScreen();

		status = TITLE;//タイトルの表示

		ui.zerotime = GetNowCount();
		//垂れ流しの音楽止めようね
		StopSoundMem(ui.mainmusic);
		while (ProgramLooping && status == TITLE)
		{
			ui.drawtime = GetNowCount();
			ClearDrawScreen();

			DrawGraph(0, 0, ui.titleGraph, false);
			text.settextsize(2, 2);
			//時間経過で順に描画
			text.textDrawMessage(800, 800, "Press Space", 11);

			ScreenFlip();

			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				status = TUTORIAL;
				//status = PLAY;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				ProgramLooping = false;
				break;
			}
		}

		WaitTimer(300);

		while (ProgramLooping && status == TUTORIAL)
		{
			ClearDrawScreen();
			//本文
			map.Drawtut();
			//text.textDrawMessage(200, 100, "press space", 11);
			DrawGraph(200, 100, ui.textGraph4, true);
			DrawGraph(200, 200, ui.tutgraph, true);
			//text.textDrawMessage(600, 100, "press space", 11);
			DrawGraph(600, 100, ui.textGraph, true);
			DrawGraph(600, 200, ui.tutgraph2, true);
			ScreenFlip();
			//描画

			if (CheckHitKey(KEY_INPUT_SPACE) == 1)
			{
				map.InitMain();
				status = PLAY;
			}
			if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				ProgramLooping = false;
				break;
			}
		}

		//ゲーム中に音を流す
		PlaySoundMem(ui.mainmusic, DX_PLAYTYPE_BACK);
		PlaySoundMem(ui.mainmusic, DX_PLAYTYPE_LOOP);
		while (ProgramLooping && status == PLAY)
		{
			//これがないと残像が発生する
			ClearDrawScreen();
			ui.framenum++;
			//以下ゲーム

			//機能確認済み
			player.Update(scroll);

			//7回しか回さない
			for (int i = 0; i < SHOT; i++)
			{
				//一発ずつ発射成功
				if (shot[i].Shotflag == false && player.shotIntervalCount == 0)
				{
					//フラグがあってて待ち時間がないなら打つ
					shot[i].Setshot(&player);
				}

				for (int j = 0; j < ENEMY; j++)
				{
					//動いている
					enemyshot[i][j].Update(scroll);

					//ここはプレイヤーは分身しないからショットを回すだけでいい
					hitcheck.hitcheck_pes(player, enemyshot[i][j], ui);
					if (shot[i].Shotflag == true && enemy[j].aliveFlag == true)
					{
						hitcheck.hitcheck_pse(shot[i], enemy[j], ui);
					}
				}

				shot[i].Update(scroll);

				for (int j = 0; j < TARGET; j++)
				{
					hitcheck.hitcheck_psc(target[j], shot[i], ui);
				}
			}

			for (int j = 0; j < ENEMY; j++)
			{
				for (int i = 0; i < SHOT; i++)
				{
					if (enemyshot[i][j].enemyShotflag == false && enemy[j].enemyShotintarvalcount == 0 && enemy[j].HitFlag == true && enemy[j].outsideScreen == false)//ここに入ってきてしまう
					{
						//画面上限界が一体につき7発になっている
						enemyshot[i][j].enemyShotSet(player, enemy[j]);
					}
				}
			}

			for (int i = 0; i < TARGET; i++)
			{
				target[i].Update();
			}

			for (int i = 0; i < ENEMY; i++)
			{
				if (i == 0)
				{
					ui.enemycount = 0;
					ui.enemycount2 = 0;
					ui.enemycount3 = 0;
					ui.enemycount4 = 0;
				}

				if (enemy[i].aliveFlag == true)
				{
					if ((enemy[i].positionX + enemy[i].W < 1920 && enemy[i].positionX > 64) &&
						(enemy[i].positionY > 64 && enemy[i].positionY + enemy[i].H < 1080))
					{
						ui.enemycount++;
					}

					if ((enemy[i].positionX + enemy[i].W < 1920 && enemy[i].positionX > 64) &&
						(enemy[i].positionY > 1080 && enemy[i].positionY + enemy[i].H < 2176))
					{
						ui.enemycount2++;
					}

					if ((enemy[i].positionX + enemy[i].W < 3840 && enemy[i].positionX > 1920) &&
						(enemy[i].positionY > 1080 && enemy[i].positionY + enemy[i].H < 2176))
					{
						ui.enemycount3++;
					}

					if ((enemy[i].positionX + enemy[i].W < 3840 && enemy[i].positionX > 1920) &&
						(enemy[i].positionY > 64 && enemy[i].positionY + enemy[i].H < 1080))
					{
						ui.enemycount4++;
					}
				}

				//敵を出現させるためのもの
				if (ui.framenum % 150 == 0 && enemy[i].aliveFlag == false && player.witeTime == 0)
				{

					//左上
					if (ui.enemycount < 5)
					{
						if ((player.positionX + player.width < 1920 && player.positionX > 64) &&
							(player.positionY > 64 && player.positionY + player.height < 1080))
						{
							enemy[i].positionX = rand() % (1664) + (128);
							enemy[i].positionY = rand() % (824) + (128);
							enemy[i].aliveFlag = true;
							enemy[i].Life = 3;
							player.witeTime = 60;
						}
					}

					//左下
					if (ui.enemycount2 < 5)
					{
						if ((player.positionX + player.width < 1920 && player.positionX > 64) &&
							(player.positionY > 1080 && player.positionY + player.height < 2176))
						{
							enemy[i].positionX = rand() % (1664) + (128);
							enemy[i].positionY = rand() % (824) + (128);
							enemy[i].positionY += scroll.positionY;
							enemy[i].aliveFlag = true;
							enemy[i].Life = 3;
							player.witeTime = 60;
						}
					}

					//右下
					if (ui.enemycount3 < 5)
					{
						if ((player.positionX + player.width < 3840 && player.positionX > 1920) &&
							(player.positionY > 1080 && player.positionY + player.height < 2176))
						{
							enemy[i].positionX = rand() % (1664) + (128);
							enemy[i].positionX += scroll.positionX;
							enemy[i].positionY = rand() % (824) + (128);
							enemy[i].positionY += scroll.positionY;
							enemy[i].aliveFlag = true;
							enemy[i].Life = 3;
							player.witeTime = 60;
						}
					}
					//右上
					if (ui.enemycount4 < 5)
					{
						if ((player.positionX + player.width < 3840 && player.positionX > 1920) &&
							(player.positionY > 64 && player.positionY + player.height < 1080))
						{
							enemy[i].positionX = rand() % (1664) + (128);
							enemy[i].positionX += scroll.positionX;
							enemy[i].positionY = rand() % (824) + (128);
							enemy[i].aliveFlag = true;
							enemy[i].Life = 3;
							player.witeTime = 60;
						}
					}
				}
				if (enemy[i].aliveFlag == true)
				{
					enemy[i].Update(player, scroll);
				}
			}
			bouns.Update(player);
			//スクロールさせる
			scroll.Update(player);
			//以下描画
			map.DrawMain(scroll);
			for (int i = 0; i < ENEMY; i++)
			{
				//エネミーの発生は時間がかかるから少し待つ
				enemy[i].Draw(scroll);
			}
			for (int i = 0; i < TARGET; i++)
			{
				//的の描画
				target[i].Draw(scroll);
			}
			for (int i = 0; i < SHOT; i++)
			{
				//描画完了動く
				shot[i].Draw(scroll);
			}
			//光るエネミーショット及びプレイヤーショットここから
			for (int i = 0; i < SHOT; i++)
			{
				for (int j = 0; j < ENEMY; j++)
				{
					enemyshot[i][j].Draw(scroll);
				}
			}
			//ここの中に入れると通常描画＋加算描画される
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			for (int i = 0; i < SHOT; i++)
			{
				shot[i].Draw(scroll);
			}
			for (int i = 0; i < SHOT; i++)
			{
				for (int j = 0; j < ENEMY; j++)
				{
					enemyshot[i][j].Draw(scroll);
				}
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			//光るエネミーショット及びプレイヤーショットここまで

			player.Draw(scroll);

			//フォントサイズの倍率変更
			text.settextsize(2, 2);
			//文字の描画
			char buf[128];
			sprintf(buf, "Score : %d", player.playerScore);
			//文字色　黒
			text.setFontColor(255, 0, 128);
			//文字の影の色　紫
			text.setFontColorShadow(128, 0, 255);
			//影の位置
			text.setFontShadowOffset(3, 3);
			//場所
			text.textDrawWithShadow(1200, 0, buf);

			//フォントサイズの倍率変更
			text.settextsize(2, 2);
			sprintf(buf, "Time : %d", 90 - (ui.framenum / 60));
			//文字色　黒
			text.setFontColor(255, 128, 0);
			//文字の影の色　紫
			text.setFontColorShadow(225, 0, 225);
			//影の位置
			text.setFontShadowOffset(3, 3);
			//場所
			text.textDrawWithShadow(750, 0, buf);

			//フォントサイズの倍率変更
			text.settextsize(2, 2);
			sprintf(buf, "Player HP : %d", player.hitPoint);
			//文字色　黒
			text.setFontColor(0, 255, 128);
			//文字の影の色　緑
			text.setFontColorShadow(128, 0, 255);
			//影の位置
			text.setFontShadowOffset(3, 3);
			//場所
			text.textDrawWithShadow(20, 0, buf);
			//プレイヤーが死ぬ、時間経過、LALTを押すとゲームオーバー
			if (player.hitPoint <= 0 || (ui.framenum / 60) >= 90 || CheckHitKey(KEY_INPUT_LALT))
			{
				status = OVER;
			}
			//escapeを押すとゲームを終わる
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				ProgramLooping = false;
				break;
			}
			//画面フリップ
			ScreenFlip();
		}

		StopSoundMem(ui.mainmusic);
		//リザルト画面
		while (ProgramLooping && status == OVER)
		{
			ClearDrawScreen();
			DrawGraph(0, 0, ui.endGraph, true);
			char buf[128];

			sprintf(buf, "Your Score : %d", player.score + (player.hitPoint * 100));
			//文字色　黒
			text.setFontColor(255, 255, 255);
			//文字の影の色　紫
			text.setFontColorShadow(128, 0, 255);
			//影の位置
			text.setFontShadowOffset(3, 3);
			//場所
			text.textDrawWithShadow(600, 600, buf);

			sprintf(buf, "Press Escape");
			//文字色　黒
			text.setFontColor(255, 255, 255);
			//文字の影の色　紫
			text.setFontColorShadow(128, 0, 255);
			//影の位置
			text.setFontShadowOffset(3, 3);
			//場所
			text.textDrawWithShadow(1100, 800, buf);
			DrawGraph(1100, 900, ui.textGraph2, true);

			sprintf(buf, "Press Space");
			//文字色　黒
			text.setFontColor(255, 255, 255);
			//文字の影の色　紫
			text.setFontColorShadow(128, 0, 255);
			//影の位置
			text.setFontShadowOffset(3, 3);
			//場所
			text.textDrawWithShadow(400, 800, buf);
			DrawGraph(400, 900, ui.textGraph3, true);

			//タイトルへ
			ScreenFlip();
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				status = TITLE;
			}
			//ゲーム終了
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				ProgramLooping = false;
				break;
			}
		}
		if (ProgramLooping == false)
		{
			break;
		}
	}
	DxLib_End();
	return 0;
}