// Preprocessor
#include <bangtal.h>
#include <stdio.h>

#define ANIMATION_TIME		0.05f
#define ANIMATION_STEP		30 // movement speed

// Scenes and Objects.
SceneID towerInside3, fight3, towerInside4;
ObjectID warriorR, warriorL,zombieT, zombieF, icon;
TimerID timer, moveTimer;

// Location of warrior

int x = 750;
int dx = 0;

// Location of icon
int xIcon = 600;
int yIcon = 100;

int dxIcon = 0;
int dyIcon = 0;

// current scene number
int sceneNum = 3;
W
// ====================================================================================

// Functions

//void mouseCallback(ObjectID obj, int x, int y, MouseAction action);
void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);
void Gameinit();
void Move();

// ====================================================================================


void Gameinit() {

	// Scenes
	towerInside3 = createScene(" towerLevel3", "towerInside.jpg");
	fight3 = createScene("zombie", "need to set interface image");
	towerInside4 = createScene("towerLevel4", "towerInside.jpg");

	// main character Warrior
	warriorR = createObject("warrior-R.png"); // set warriorR as a default status
	locateObject(warriorR, towerInside3, 350, 180);
	showObject(warriorR);
	scaleObject(warriorR, 0.5f);

	warriorL = createObject("warrior-L.png");
	locateObject(warriorL, towerInside3, 350, 180);
	scaleObject(warriorL, 0.5f);

	// zombie
	zombieT = createObject("zombie.png"); // zombie Tower
	locateObject(zombieT, towerInside3, 750, 180);
	scaleObject(zombieT, 0.5f);
	showObject(zombieT);

	zombieF = createObject("zombie.png"); // zombie Fight
	locateObject(zombieF, fight3, 550, 500);
	scaleObject(zombieF, 0.6f);
	showObject(zombieF);
	
	// icon
	icon = createObject("icon.png");
	locateObject(icon, fight3, 600, 100);
	showObject(icon);
	

}

void Move() {

	// Movement of warrior
	if (sceneNum == 3) {
		x += dx;
		locateObject(warriorL, towerInside3, x, 180);
		locateObject(warriorR, towerInside3, x, 180);
	}
	
	// Movement of icon
	else if (sceneNum == 4) {
		xIcon += dxIcon;
		yIcon += dyIcon;
		locateObject(icon, fight3, xIcon, yIcon);


		if (xIcon >= 500 && xIcon <= 600 && yIcon >= 500 && yIcon <= 600) { // need to make function which sense collision
			showMessage("heart -1");
		}
	}

	setTimer(moveTimer, ANIMATION_TIME);
	startTimer(moveTimer);

}



void timerCallback(TimerID timer) {

	if (timer == moveTimer) {
		//animation of movement
		Move();
	}

}

void keyboardCallback(KeyCode code, KeyState state) {
	// Processing a keyboard input.
	// If player pressed an Up arrow at structures, then player go there. (Not Implemented) 

	if (code == 83) {				// RIGHT
		showObject(warriorR);
		hideObject(warriorL);
		dx += (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		dxIcon += (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}

	else if (code == 82) {			//LEFT
		showObject(warriorL);
		hideObject(warriorR);
		dx -= (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		dxIcon -= (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);

	}

	else if (code == 84) {			// UP

		if (sceneNum == 3 && x >= 750) {
			sceneNum = 4;
			enterScene(fight3);
		}

		dyIcon += (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}

	else if (code == 85) {		// DOWN
		dyIcon -= (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}
	
}


int main() {

	//setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);

	// Timer for animation
	moveTimer = createTimer(ANIMATION_TIME);
	startTimer(moveTimer);

	//Setting elements needed to play game
	Gameinit();

	// Starting a game
	startGame(towerInside3);

}