#include "Scr.h"
void Scr::Init()
{
	scrX = 0;
	scrY = 0;
}
void Scr::Update(Player&player)
{
	if (player.Y > scrY + 720)//下に進
	{
		if (scrY < 1096 )
		{
			scrY += (player.Y - (scrY + 720));
		}
	}
	if (player.Y < scrY + 360)
	{
		if (scrY > 0)
		{
			scrY += (player.Y - (scrY + 360));
		}
	}
	if (player.X > scrX + 1280)//右に進
	{
		if (scrX < 1920 )
		{
			scrX += (player.X - (scrX + 1280));
		}
	}
	if (player.X < scrX + 640)
	{
		if (scrX > 0)
		{
			scrX += (player.X - (scrX + 640));
		}
	}
}