#pragma once
#include "DxLib.h"
#include "Shot.h"
#include "Enemy.h"
#include "target.h"
#include "EnemyShot.h"
#include "Player.h"
#include "Common.h"
#include "UI.h"
class HitCheck
{
public:
	//プレイヤーと敵弾の当たり判定
	void hitcheck_pes(Player& player,EnemyShot& enemyshot,UI& ui);

	//自弾と敵の当たり判定
	void hitcheck_pse(Shot& shot,Enemy& enemy,UI& ui);

	//自弾とクリスタルの当たり判定
	void hitcheck_psc(Tg& target,Shot& shot,UI& ui);

	//自機とクリスタルの当たり判定(未完
	void hitcheck_pc(Tg& target,Player& player);
};