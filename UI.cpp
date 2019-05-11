#include "UI.h"
void UI::Init(BitmapText &text)
{

	text.setFontImage(16, 6, "font.bmp");
	text.reMapText(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_\tabcdefghijklmnopqrstuvwxyz{|}~\\");
	mainmusic = LoadSoundMem("data/sound/play.mp3");			
	shothit = LoadSoundMem("data/sound/hit.mp3");				
	titleGraph = LoadGraph("data/texture/title.png");			
	endGraph = LoadGraph("data/texture/over.png");			
	tutgraph = LoadGraph("data/texture/wasd.png");
	tutgraph2 = LoadGraph("data/texture/houkouki-.png");
	textGraph = LoadGraph("data/texture/shottext1.png");
	textGraph2 = LoadGraph("data/texture/endtext1.png");
	textGraph3 = LoadGraph("data/texture/titletext1.png");
	textGraph4 = LoadGraph("data/texture/movetext1.png");
	shiftGraph = LoadGraph("data/texture/Shift.png");
	framenum = 0;												
	drawtime = 0;												
	waittime = 0;
	zerotime = 0;
	starttime = 0;
	enemycount = 0;
	enemycount2 = 0;
	enemycount3 = 0;
	enemycount4 = 0;
}
void UI::Draw(Tg&target)
{

}