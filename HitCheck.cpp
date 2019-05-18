#include "hitcheck.h"

//入れる場所はそれぞれ違う


void HitCheck::hitcheck_pes(Player& player,EnemyShot& enemyshot,UI&ui)
{
	//敵弾とプレイヤーの座標
	if (enemyshot.enemyShotVisibleFlag == true && player.hitFlag == true)
	{
		// エネミーと弾の当たり判定
		if (((enemyshot.enemyShotX > player.positionX && enemyshot.enemyShotX < player.positionX + player.width * 1.5) ||
			(player.positionX > enemyshot.enemyShotX && player.positionX < enemyshot.enemyShotX + enemyshot.enemyShotW)) &&
			((enemyshot.enemyShotY > player.positionY && enemyshot.enemyShotY < player.positionY + player.height * 1.5) ||
			(player.positionY > enemyshot.enemyShotY && player.positionY < enemyshot.enemyShotY + enemyshot.enemyShotH)))
		{
			// 接触している場合は当たった弾の存在を消す
			enemyshot.enemyShotVisibleFlag = false;
			//ここに敵ダメージ処理を入れる
			player.hitPoint -= enemyshot.enemyShotDmg;
			PlaySoundMem(ui.shothit, DX_PLAYTYPE_BACK);
		}
	}
}

void HitCheck::hitcheck_pse(Shot& shot,Enemy& enemy,UI&ui)
{
	//自弾と敵の座標
	if (shot.VisibleFlag == true && enemy.HitFlag == true)
	{
		if (shot.East || shot.West)
		{
			if (!shot.South && !shot.North)
			{
				if (((shot.positionX > enemy.positionX && shot.positionX < enemy.positionX + enemy.W * 1.5) ||
					(enemy.positionX > shot.positionX && enemy.positionX < shot.positionX + shot.H)) &&
					((shot.positionY > enemy.positionY && shot.positionY < enemy.positionY + enemy.H * 1.5) ||
					(enemy.positionY > shot.positionY && enemy.positionY < shot.positionY + shot.W)))
				{
					// 接触している場合は当たった弾の存在を消す
					shot.VisibleFlag = false;
					//ここに敵ダメージ処理を入れる
					enemy.Life -= shot.Dmg;
					PlaySoundMem(ui.shothit, DX_PLAYTYPE_BACK);
				}
			}
		}
		// エネミーと弾の当たり判定
		if (((shot.positionX > enemy.positionX && shot.positionX < enemy.positionX + enemy.W * 1.5) ||
			(enemy.positionX > shot.positionX && enemy.positionX < shot.positionX + shot.W)) &&
			((shot.positionY > enemy.positionY && shot.positionY < enemy.positionY + enemy.H * 1.5) ||
			(enemy.positionY > shot.positionY && enemy.positionY < shot.positionY + shot.H)))
		{
			// 接触している場合は当たった弾の存在を消す
			shot.VisibleFlag = false;
			//ここに敵ダメージ処理を入れる
			enemy.Life -= shot.Dmg;
			PlaySoundMem(ui.shothit, DX_PLAYTYPE_BACK);
		}
	}
}

void HitCheck::hitcheck_psc(Target& target, Shot&shot,UI&ui)
{
	if (shot.VisibleFlag == true && target.state < 4)
	{
		// ターゲットと自弾の当たり判定
		if (((shot.positionX > target.positionX && shot.positionX < target.positionX + target.W * 1.55) ||
			(target.positionX > shot.positionX && target.positionX < shot.positionX + shot.W)) &&
			((shot.positionY > target.positionY && shot.positionY < target.positionY + target.H * 1.55) ||
			(target.positionY > shot.positionY && target.positionY < shot.positionY + shot.H)))
		{
			// 接触している場合は当たった弾の存在を消す
			shot.VisibleFlag = false;
			//ここにクリスタルダメージ処理を入れる色の変更はtarget.updateにある
			target.state += shot.Dmg;
		}
	}
}

void HitCheck::hitcheck_pc(Target& target, Player&player)
{
	if (player.hitFlag == true && target.state < 5)
	{
		// ターゲットと自弾の当たり判定
		if (((player.positionX > target.positionX && player.positionX < target.positionX + target.W * 1.55) ||
			(target.positionX > player.positionX && target.positionX < player.positionX + player.width * 1.5)) &&
			((player.positionY > target.positionY && player.positionY < target.positionY + target.H * 1.55) ||
			(target.positionY > player.positionY && target.positionY < player.positionY + player.height * 1.5)))
		{
			//接触しているだけ,hpと引き換えに相手にダメージ？
			//ここで止めるなり戻すなりする
			if (player.positionX > target.positionX && player.positionX <= target.positionX + target.W * 1.55)
			{
				player.positionX = target.positionX + target.W * 1.55 + 7;
			}
		}
		else
		{
			player.ySpeed = 7;
			player.xSpeed = 7;
		}
	}
}