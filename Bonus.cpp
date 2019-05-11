#include "Bonus.h"
void Bonus::Init()
{
	aliveflag = false;
	blueflag = false;
	blueflag2 = false;
	blueflag3 = false;
	blueflag4 = false;

	point = 1000;
}

void Bonus::Update(Player&player)
{
	if (blueflag == true && blueflag2 == true && blueflag3 == true && blueflag4 == true)
	{
		aliveflag = true;
		player.score += point;
	}
	if (aliveflag == true)
	{
		aliveflag = false;
	}
}
