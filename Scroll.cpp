#include "Scroll.h"
void Scroll::Init()
{
	positionX = 0;
	positionY = 0;
}
void Scroll::Update(Player&player)
{
	if (player.positionY > positionY + 720)
	{
		if (positionY < 1096 )
		{
			positionY += (player.positionY - (positionY + 720));
		}
	}
	if (player.positionY < positionY + 360)
	{
		if (positionY > 0)
		{
			positionY += (player.positionY - (positionY + 360));
		}
	}
	if (player.positionX > positionX + 1280)
	{
		if (positionX < 1920 )
		{
			positionX += (player.positionX - (positionX + 1280));
		}
	}
	if (player.positionX < positionX + 640)
	{
		if (positionX > 0)
		{
			positionX += (player.positionX - (positionX + 640));
		}
	}
}