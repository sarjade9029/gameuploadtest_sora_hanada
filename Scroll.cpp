#include "Scroll.h"
void Scroll::Init()
{
	scrollPositionX = 0;
	scrollPositionY = 0;
}
void Scroll::Update(Player&player)
{
	if (player.positionY > scrollPositionY + 720)
	{
		if (scrollPositionY < 1096 )
		{
			scrollPositionY += (player.positionY - (scrollPositionY + 720));
		}
	}
	if (player.positionY < scrollPositionY + 360)
	{
		if (scrollPositionY > 0)
		{
			scrollPositionY += (player.positionY - (scrollPositionY + 360));
		}
	}
	if (player.positionX > scrollPositionX + 1280)
	{
		if (scrollPositionX < 1920 )
		{
			scrollPositionX += (player.positionX - (scrollPositionX + 1280));
		}
	}
	if (player.positionX < scrollPositionX + 640)
	{
		if (scrollPositionX > 0)
		{
			scrollPositionX += (player.positionX - (scrollPositionX + 640));
		}
	}
}