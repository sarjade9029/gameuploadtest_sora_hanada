#include "hitcheck.h"

//入れる場所はそれぞれ違う


void HitCheck::hitcheck_pes(Player& player,EnemyShot& enemyshot,UI&ui)
{
	//敵弾とプレイヤーの座標
	if (enemyshot.enemyShotVisibleFlag == true && player.HitFlag == true)
	{
		// エネミーと弾の当たり判定
		if (((enemyshot.enemyShotX > player.X && enemyshot.enemyShotX < player.X + player.W * 1.5) ||
			(player.X > enemyshot.enemyShotX && player.X < enemyshot.enemyShotX + enemyshot.enemyShotW)) &&
			((enemyshot.enemyShotY > player.Y && enemyshot.enemyShotY < player.Y + player.H * 1.5) ||
			(player.Y > enemyshot.enemyShotY && player.Y < enemyshot.enemyShotY + enemyshot.enemyShotH)))
		{
			// 接触している場合は当たった弾の存在を消す
			enemyshot.enemyShotVisibleFlag = false;
			//ここに敵ダメージ処理を入れる
			player.Hp -= enemyshot.enemyShotDmg;
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
				if (((shot.X > enemy.X && shot.X < enemy.X + enemy.W * 1.5) ||
					(enemy.X > shot.X && enemy.X < shot.X + shot.H)) &&
					((shot.Y > enemy.Y && shot.Y < enemy.Y + enemy.H * 1.5) ||
					(enemy.Y > shot.Y && enemy.Y < shot.Y + shot.W)))
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
		if (((shot.X > enemy.X && shot.X < enemy.X + enemy.W * 1.5) ||
			(enemy.X > shot.X && enemy.X < shot.X + shot.W)) &&
			((shot.Y > enemy.Y && shot.Y < enemy.Y + enemy.H * 1.5) ||
			(enemy.Y > shot.Y && enemy.Y < shot.Y + shot.H)))
		{
			// 接触している場合は当たった弾の存在を消す
			shot.VisibleFlag = false;
			//ここに敵ダメージ処理を入れる
			enemy.Life -= shot.Dmg;
			PlaySoundMem(ui.shothit, DX_PLAYTYPE_BACK);
		}
	}
}

void HitCheck::hitcheck_psc(Tg& target, Shot&shot,UI&ui)
{
	if (shot.VisibleFlag == true && target.Thp < 4)
	{
		// ターゲットと自弾の当たり判定
		if (((shot.X > target.X && shot.X < target.X + target.W * 1.55) ||
			(target.X > shot.X && target.X < shot.X + shot.W)) &&
			((shot.Y > target.Y && shot.Y < target.Y + target.H * 1.55) ||
			(target.Y > shot.Y && target.Y < shot.Y + shot.H)))
		{
			// 接触している場合は当たった弾の存在を消す
			shot.VisibleFlag = false;
			//ここにクリスタルダメージ処理を入れる色の変更はtarget.updateにある
			target.Thp += shot.Dmg;
		}
	}
}

void HitCheck::hitcheck_pc(Tg& target, Player&player)
{
	if (player.HitFlag == true && target.Thp < 5)
	{
		// ターゲットと自弾の当たり判定
		if (((player.X > target.X && player.X < target.X + target.W * 1.55) ||
			(target.X > player.X && target.X < player.X + player.W * 1.5)) &&
			((player.Y > target.Y && player.Y < target.Y + target.H * 1.55) ||
			(target.Y > player.Y && target.Y < player.Y + player.H * 1.5)))
		{
			//接触しているだけ,hpと引き換えに相手にダメージ？
			//ここで止めるなり戻すなりする
			if (player.X > target.X && player.X <= target.X + target.W * 1.55)
			{
				player.X = target.X + target.W * 1.55 + 7;
			}
		}
		else
		{
			player.Ys = 7;
			player.Xs = 7;
		}
	}
}