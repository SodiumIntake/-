#include <bangtal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

SceneID scene1;
TimerID timer;
ObjectID ob[12], startButton,init_ob[12];
time_t start, end;
int result;
const char* image[12] = {
	"Images\\최예나_001.png",
	"Images\\최예나_002.png",
	"Images\\최예나_003.png",
	"Images\\최예나_004.png",
	"Images\\최예나_005.png",
	"Images\\최예나_006.png",
	"Images\\최예나_007.png",
	"Images\\최예나_008.png",
	"Images\\최예나_009.png",
	"Images\\최예나_010.png",
	"Images\\최예나_011.png",
	"Images\\최예나_012.png" };
int lcx[12] = { 0,320,640,960,0,320,640,960,0,320,640,960 };
int lcy[12] = { 480,480,480,480,240,240,240,240,0,0,0,0 };
int tmp,mixcount;

ObjectID createObject(const char* image, SceneID scene, int x, int y , bool shown) {

	ObjectID object = createObject(image);
	if (shown == true) {
		locateObject(object, scene, x, y);
		showObject(object);
	}

	return object;
}

int blank;

void swap(int index) {
	ObjectID t = ob[blank];
	ob[blank] = ob[index];
	ob[index] = t;

	locateObject(ob[blank], scene1, lcx[blank], lcy[blank]);
	locateObject(ob[index], scene1, lcx[index], lcy[index]);
	
	blank = index;
}

int ob_index(ObjectID object) {
	for (int i = 0; i < 12; i++) {
		if (ob[i] == object) return i;
	}
	return -1;
}

bool Changeable(int index) {
	if (lcx[index] == lcx[blank] + 320 && lcy[index] == lcy[blank]) {
		return(true);
	}
	else if (lcx[index] == lcx[blank] - 320 && lcy[index] == lcy[blank]) {
		return(true);
	}
	else if (lcx[index] == lcx[blank] && lcy[index] == lcy[blank] + 240) {
		return(true);
	}
	else if (lcx[index] == lcx[blank] && lcy[index] == lcy[blank] - 240) {
		return(true);
	}
	else {
		return(false);
	}
}

void mixmix() {
	int index;
	
	do {
		switch (rand() % 4) {
		case 0: index = blank - 1; break;
		case 1: index = blank + 1; break;
		case 2: index = blank - 4; break;
		case 3: index = blank + 4; break;
		}
	}while (!Changeable(index));
	swap(index);
}



void timerCallback(TimerID timer) {
	mixcount--;

	if (mixcount > 0) {
		mixmix();
	}
	
	setTimer(timer, 0.1f);
	startTimer(timer);
}

bool completed() {
	for (int i = 0; i < 12; i++) {
		if (init_ob[i] != ob[i]) return false;
	}

	return true;
}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == startButton) {
		start = time(NULL);
		hideObject(startButton);
		mixcount = 10;

		setTimer(timer, 0.1f);
		startTimer(timer);
	}
	else {
		int index = ob_index(object);
		if (Changeable(index))
			swap(index);
		if (completed() == true) {
			showMessage("예나 완성!");
			end = time(NULL);
			result = end - start;
			showObject(startButton);
			}
	}
}

int main() {
	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	scene1 = createScene("예나 맞추기", "Images\\배경.png");
	for (int i = 0; i < 12; i++) {
		ob[i] = createObject(image[i]);
		init_ob[i] = ob[i];
		locateObject(ob[i], scene1, lcx[i], lcy[i]);
		showObject(ob[i]);
	}
	blank = 0;
	hideObject(ob[blank]);
	
	startButton = createObject("Images\\start.png", scene1, 540, 100, true);
	scaleObject(startButton, 2.0f);
	timer = createTimer(0.1f);
	startTimer(timer);
	startGame(scene1);	
}
