#include <bangtal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

SceneID scene1;
ObjectID ob[12], startButton;
int lcx[12] = {0,0,0,320,320,320,640,640,640,960,960,960};
int lcy[12] = {0,240,480,0,240,480,0,240,480,0,240,480};
int tmp, i, how;

ObjectID createObject(const char* image, SceneID scene, int x, int y , bool shown) {

	ObjectID object = createObject(image);
	if (shown == true) {
		locateObject(object, scene, x, y);
		showObject(object);
	}

	return object;
}



void swap(int x, int y) {
	tmp = x;
	x = y;
	y = tmp;
}


bool change(ObjectID object) {
	for (i = 1; i < 12; i++) {
		if (lcx[i] == lcx[0] + 320 && lcy[i] == lcy[0]) {
			return(true);
		}
		else if (lcx[i] == lcx[0] - 320 && lcy[i] == lcy[0]) {
			return(true);
		}
		else if (lcx[i] == lcx[0] && lcy[i] == lcy[0] + 240) {
			return(true);
		}
		else if (lcx[i] == lcx[0] && lcy[i] == lcy[0] - 240) {
			return(true);
		}
	}
	return(false);
}




void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) {
		hideObject(startButton);
		endGame();
	}
	for (i = 1; i < 12; i++) {
		if (object == ob[i]) {
			if (change(ob[i]) == true) {
				swap(lcx[0], lcx[i]);
				swap(lcy[0], lcy[i]);
				locateObject(ob[0], scene1, lcx[0], lcy[0]);
				locateObject(ob[i], scene1, lcx[i], lcy[i]);
			}
		}
		if (change(ob[i]) == false) {
			showMessage("이것과는 바꿀 수 없어.");
		}
	}
}

int main() {
	time_t start = time(NULL);
	setMouseCallback(mouseCallback);
	scene1 = createScene("예나 맞추기", "Images\\배경.png");

	ob[0] = createObject("Images\\빈칸.png", scene1, lcx[0], lcy[0], true);
	ob[1] = createObject("Images\\최예나_002.png", scene1, lcx[1], lcy[1], true);
	ob[2] = createObject("Images\\최예나_003.png", scene1, lcx[2], lcy[2], true);
	ob[3] = createObject("Images\\최예나_004.png", scene1, lcx[3], lcy[3], true);
	ob[4] = createObject("Images\\최예나_005.png", scene1, lcx[4], lcy[4], true);
	ob[5] = createObject("Images\\최예나_006.png", scene1, lcx[5], lcy[5], true);
	ob[6] = createObject("Images\\최예나_007.png", scene1, lcx[6], lcy[6], true);
	ob[7] = createObject("Images\\최예나_008.png", scene1, lcx[7], lcy[7], true);
	ob[8] = createObject("Images\\최예나_009.png", scene1, lcx[8], lcy[8], true);
	ob[9] = createObject("Images\\최예나_010.png", scene1, lcx[9], lcy[9], true);
	ob[10] = createObject("Images\\최예나_011.png", scene1, lcx[10], lcy[10], true);
	ob[11] = createObject("Images\\최예나_012.png", scene1, lcx[11], lcy[11], true);
	
	startButton = createObject("Images\\start.png", scene1, 540, 100, true);
	scaleObject(startButton, 2.0f);
	startGame(scene1);	
	time_t end = time(NULL);
	how = difftime(end, start);
}