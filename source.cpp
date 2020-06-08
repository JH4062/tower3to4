/* ======================================================
need to make 
	a. function related to collision (when icon collides to enemy, MyHP decrease)
	c. MyHP and enemyHP
	d. turn 
	e. attack 
	f. item
	g. add bgm
====================================================== */


// Preprocessor
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANIMATION_TIME		0.05f
#define ANIMATION_STEP		30 // movement speed

// Scenes and Objects.
SceneID towerInside3, fight3, towerInside4;
ObjectID warriorR, warriorL, zombieT;
ObjectID zombieF, icon, enemyHP[6], attack, item, avoid ;
ObjectID brain, explosion, blood[4], zomhand;


//Timer for animation
TimerID  moveTimer, attTimer0, attTimer1a, attTimer1b, attTimer2, turnTimer;

// Sounds
SoundID zom, explo, hand;

// Location of warrior
int x = 750;
int dx = 0;

// Location of icon
int xIcon = 644;
int yIcon = 200;
int dxIcon = 0;
int dyIcon = 0;

// Location of zombie
int xZombie[3] = { 600, 450, 750 };
int yZombie = 480;

// Location of blood 
int xBlood1 = 644;
int xBlood2 = 644;
int yBlood1 = 250;
int yBlood2 = 250;

// Location of zomhand
int xZomhand[5] = { 440, 540, 640, 740, 840 };
int yZomhand = 500;

// curret numbers
int repeatNum = 0;
int sceneNum = 3;
int turnNum = 1;

// ====================================================================================
// Functions

void mouseCallback(ObjectID obj, int x, int y, MouseAction action);
void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);
void Gameinit();
void Move();
void RandAtt();
void Turn();
void ZombieAtt0();
void ZombieAtt1a();
void ZombieAtt1b();
void ZombieAtt2();
// ====================================================================================



void Gameinit() {

	// Scenes
	towerInside3 = createScene(" towerLevel3", "./Images/Backgrounds/Tower_Inside.png");
	fight3 = createScene("zombie", "./Images/Backgrounds/Battle.png");
	towerInside4 = createScene("towerLevel4", "towerInside.jpg");

	// Timer for animation
	moveTimer = createTimer(ANIMATION_TIME);
	startTimer(moveTimer);

	attTimer0 = createTimer();
	attTimer1a = createTimer(1.0f);
	attTimer1b = createTimer();
	attTimer2 = createTimer();

	// Sound effects
	zom = createSound("./Audios/tower3/zombieWalk.mp3");
	explo = createSound("./Audios/tower3/explosion.mp3");
	hand = createSound("./Audios/tower3/zombieHand.mp3");

	// zombie
	zombieT = createObject("./Images/Enemies/tower3/zombie.png"); // zombie Tower
	locateObject(zombieT, towerInside3, 750, 180);
	scaleObject(zombieT, 0.5f);
	showObject(zombieT);

	zombieF = createObject("./Images/Enemies/tower3/zombie.png"); // zombie Fight
	locateObject(zombieF, fight3, 600, 480);
	scaleObject(zombieF, 0.6f);
	showObject(zombieF);

	// main character Warrior
	warriorR = createObject("./Images/Characters/warrior_R.png"); // set warriorR as a default status
	locateObject(warriorR, towerInside3, 350, 180);
	showObject(warriorR);
	scaleObject(warriorR, 0.5f);

	warriorL = createObject("./Images/Characters/warrior_L.png");
	locateObject(warriorL, towerInside3, 350, 180);
	scaleObject(warriorL, 0.5f);

	// icon
	icon = createObject("./Images/Characters/Warrior_I.png");
	locateObject(icon, fight3, xIcon, yIcon);
	showObject(icon);

	// enemyHP

	// myHP

	// attack
	attack = createObject("./Images/UI/Battle/attack.png");
	locateObject(attack, fight3, 310, 80);
	scaleObject(attack, 0.65f);
	showObject(attack);

	// item
	item = createObject("./Images/UI/Battle/item.png");
	locateObject(item, fight3, 610, 80);
	scaleObject(item, 0.65f);
	showObject(item);

	// avoid
	avoid = createObject("./Images/UI/Battle/avoid.png");
	locateObject(avoid, fight3, 900, 80);
	scaleObject(avoid, 0.6f);
	showObject(avoid);

	// brain
	brain = createObject("./Images/Enemies/tower3/brain.png");

	// explosion
	explosion = createObject("./Images/Enemies/tower3/explosion.png");

	// blood
	char bloodImage[100];
	for (int i = 0; i < 4; i++) {
		sprintf_s(bloodImage, "./Images/Enemies/tower3/blood%d.png", i);
		blood[i] = createObject(bloodImage);
	}
		
	// zomebi's hand
	zomhand = createObject("./Images/Enemies/tower3/zomhand.png");

}

void Turn() {
	RandAtt();
	if (turnNum % 2 == 0) { // if it's my turn 
		showObject(attack);
		showObject(item);
		showObject(avoid);
	}

	if (turnNum % 2 == 1) { // if it's com turn
		
		hideObject(attack);
		hideObject(item);
		hideObject(avoid);
	}

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

		// enable icon to move in the range of gray rectangle
		if (xIcon >= 340 && xIcon <= 940 && yIcon >= 150 && yIcon <= 320) {
			xIcon += dxIcon;
			yIcon += dyIcon;
			locateObject(icon, fight3, xIcon, yIcon);
						 
			if (xIcon <= 340) { xIcon = 340; }
			if (xIcon >= 940) { xIcon = 940; }
			if (yIcon <= 150) { yIcon = 150; }
			if (yIcon >= 320) { yIcon = 320; }
		}
	}
			
	// need to make function which sense collision
	else if (xIcon >= 500 && xIcon <= 600 && yIcon >= 500 && yIcon <= 600) { 
			showMessage("heart -1");
		}

	setTimer(moveTimer, ANIMATION_TIME);
	startTimer(moveTimer);

}

// Random Pattern
void RandAtt() {

	repeatNum = 0; //reset repeatNumber

	srand((unsigned int)time(NULL));
	int num = rand() % 3;

	turnNum += 1;

	switch (num){
	case 0:
		ZombieAtt0();
		startTimer(attTimer0);
		break;

	case 1:
		ZombieAtt1a();
		break;

	case 2:ZombieAtt2();
		ZombieAtt2();
		startTimer(attTimer2);
		break;
	}


}

// pattern0 : zombie itself goes down
void ZombieAtt0() {	
	
	playSound(zom);

	if (yZombie >= 0) {
	
		yZombie -= 60;
		locateObject(zombieF, fight3, xZombie[repeatNum], yZombie);
		
		setTimer(attTimer0, ANIMATION_TIME);
		startTimer(attTimer0);
		
		if (yZombie < 0) {
			yZombie = 900;
			repeatNum++;
		}		
	}
}

// pattern1a : brain appears at the center and explodes in 1 sec. 
void ZombieAtt1a() {

	setTimer(attTimer1a, 0.5f);
	startTimer(attTimer1a);

	for (int i = 0; i < 4; i++) {
		showObject(blood[i]);
		locateObject(blood[i], fight3, 644, 250);
	}


	locateObject(brain, fight3, 644, 250);
	showObject(brain);


}

// pattern1b : after explosion, four blood cells flies away in a form of cross
void ZombieAtt1b() { 
	if (xBlood1 >= 340 && xBlood2 <= 940 && yBlood2 >= 150 && yBlood1 <= 320) {

		xBlood1 -= 40;
		xBlood2 += 40;
		yBlood1 -= 40;
		yBlood2 += 40;

		locateObject(blood[0], fight3, xBlood1, 250);
		locateObject(blood[1], fight3, xBlood2, 250);
		locateObject(blood[2], fight3, 644, yBlood1);
		locateObject(blood[3], fight3, 644, yBlood2);

		setTimer(attTimer1b, ANIMATION_TIME);
		startTimer(attTimer1b);

		// if blood cells go outside of rectangle, it disappears 
		if (xBlood1 <= 340 && xBlood2 >= 940 && yBlood1 <= 150 && yBlood2 >= 320) {

			
			for (int i = 0; i < 4; i++) {
				hideObject(blood[i]);
			}

			stopTimer(attTimer1b);

			xBlood1 = 644;
			xBlood2 = 644;
			yBlood1 = 250;
			yBlood2 = 250;
			

			hideObject(explosion);

		
		}

	
	}	
		
	
}

void ZombieAtt2(){ // pattern2 : zombie's hand appears at random X, certain Y and goes down. repeats for five times.

	playSound(hand);
	yZomhand -= 50;
	locateObject(zomhand, fight3, xZomhand[repeatNum], yZomhand);
	showObject(zomhand);

	if (yZomhand < 0) {
		hideObject(zomhand);
		yZomhand = 500;
		repeatNum++;
	}

	setTimer(attTimer2, ANIMATION_TIME);
	startTimer(attTimer2);
}

// void Collision() {}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == zombieF) {
		RandAtt();
	}

	// If player clicked attack, then player attacks zombie as much as weapon's level
	if (object == attack) {
		showMessage("monster hurted");
		
		turnNum += 1;
	
	}

	if (object == item) {

		
	}

	// If player clicked avoid, then player goes back to towerInside3
	if (object == avoid) {
		enterScene(towerInside3);
		sceneNum = 3;
		turnNum = 1;
	}
}	

void timerCallback(TimerID timer) {

	if (timer == moveTimer) {
		//animation of movement
		Move();
	}

	if (repeatNum < 3 && timer == attTimer0) {
		ZombieAtt0();

		if (repeatNum == 3) {
			locateObject(zombieF, fight3, 600, 480);
		}
		
	}


	if (timer == attTimer1a) {
		hideObject(brain);
		locateObject(explosion, fight3, 644, 250);
		showObject(explosion);
		playSound(explo);
		startTimer(attTimer1b);
	
	}

	if (timer == attTimer1b) {
		ZombieAtt1b();
	}

	if (repeatNum < 5 && timer == attTimer2) {
		ZombieAtt2();
	
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

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);

	//Setting elements needed to play game
	Gameinit();

	// Starting a game
	startGame(towerInside3); 

}