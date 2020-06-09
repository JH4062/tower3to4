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

const int playerX_MIN = 50, playerX_MAX = 1150;

// Location of icon
int iconX = 644;
int iconY = 200;
int dxIcon = 0;
int dyIcon = 0;

const int iconX_MIN = 333, iconX_MAX = 943, iconX_SIZE = 40;
const int iconY_MIN = 150, iconY_MAX = 320, iconY_SIZE = 70;

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
int turnNum = 0;

// Gold
int gold = 359;
ObjectID goldList[3];
int goldX[3] = { 1040, 1067, 1094 };
int goldY = 595;

//turn
int turnCnt = 0;
const int TURN_TIME = 20;
const Second TURN_TICK = 0.05f;



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


void Turn() {
	// Player Turn
	if (turnNum % 2 == 0) {
		showObject(attack);
		showObject(item);
		showObject(avoid);
	}
	// Enemy Turn
	else if (turnNum % 2 == 1) { // if it's com turn
		RandAtt();
	}
}

void showGold(void) {
	// Shows a gold.

	int temp = gold;
	if (0 <= gold and gold < 10) {
		for (int i = 0; i <= 0; i++) {
			int num = temp % 10;
			temp /= 10;

			char imageName[30];
			sprintf_s(imageName, sizeof(imageName), "./Images/Numbers/%d_R.png", num);
			setObjectImage(goldList[i], imageName);
			showObject(goldList[i]);
		}

		for (int i = 1; i <= 2; i++) {
			hideObject(goldList[i]);
		}
	}
	else if (10 <= gold and gold < 100) {
		for (int i = 0; i <= 1; i++) {
			int num = temp % 10;
			temp /= 10;

			char imageName[30];
			sprintf_s(imageName, sizeof(imageName), "./Images/Numbers/%d_R.png", num);
			setObjectImage(goldList[1 - i], imageName);
			showObject(goldList[1 - i]);
		}

		for (int i = 2; i <= 2; i++) {
			hideObject(goldList[i]);
		}
	}
	else if (100 <= gold and gold < 1000) {
		for (int i = 0; i <= 2; i++) {
			int num = temp % 10;
			temp /= 10;

			char imageName[30];
			sprintf_s(imageName, sizeof(imageName), "./Images/Numbers/%d_R.png", num);
			setObjectImage(goldList[2 - i], imageName);
			showObject(goldList[2 - i]);
		}
	}
	else {
		// Not implemented when gold >= 1000.
		printf("showGold: Gold is over 999 \n");

		for (int i = 0; i < 3; i++) {
			setObjectImage(goldList[i], "./Images/Numbers/0_R.png");
			showObject(goldList[i]);
		}
	}
}


void Gameinit() {

	// Scenes
	towerInside3 = createScene(" towerLevel3", "./Images/Backgrounds/Tower_Inside.png");
	fight3 = createScene("zombie", "./Images/Backgrounds/Battle.png");
	towerInside4 = createScene("towerLevel4", "towerInside.jpg");

	// Timer for animation
	moveTimer = createTimer(ANIMATION_TIME);
	startTimer(moveTimer);

	turnTimer = createTimer(ANIMATION_TIME);

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

	// icon
	icon = createObject("./Images/Characters/Warrior_I.png");
	locateObject(icon, fight3, iconX, iconY);
	showObject(icon);

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

	// show gold
	showGold();
}


bool checkCollision(int xStart, int xEnd, int yStart, int yEnd) {
	// Check a collsion, then return a result.

	// About Collision:
	// We can find 'collision' with position and size.
	// If enemy attack's X is about 400 ~ 600,
	// then X_MIN <= player's X <= 360 (360 can be replaced with 400 - SIZE) or 600 <= player's X <= X_MAX
	// If enemy attack's Y is about 230 ~ 300,
	// then Y_MIN <= player's Y <= 160 (160 can be replaced with 230 - SIZE) or 300 <= player's Y <= Y_MAX

	// Conclusion:
	// If a <= attack's range <= b, then player will be hit when (a - SIZE) < player's position < b

	bool xCollision = ((xStart - iconX_SIZE) < iconX) and (iconX < xEnd);
	bool yCollision = ((yStart - iconY_SIZE) < iconY) and (iconY < yEnd);

	return xCollision and yCollision;


}

void Move() {

	// Movement of warrior
	if (sceneNum == 3) {

		x += dx;
	
		
		if (dx < 0) {
			setObjectImage(warriorR, "./Images/Characters/Warrior_L.png");
		}
		else if (dx > 0) {
			setObjectImage(warriorR, "./Images/Characters/Warrior_R.png");
		}

		if (x < playerX_MIN) {
			x = playerX_MIN;
		}
		else if (x > playerX_MAX) {
			x = playerX_MAX;
		}

		locateObject(warriorR, towerInside3, x, 180);




	}
	
	// Movement of icon
	else if (sceneNum == 4) {

		locateObject(icon, fight3, iconX, iconY);

		// Set a restriction.
		iconX += dxIcon;
		if (iconX < iconX_MIN) {
			iconX = iconX_MIN;
		}
		else if (iconX > iconX_MAX) {
			iconX = iconX_MAX;
		}

		iconY += dyIcon;
		if (iconY < iconY_MIN) {
			iconY = iconY_MIN;
		}
		else if (iconY > iconY_MAX) {
			iconY = iconY_MAX;
		}
	}
			

	setTimer(moveTimer, ANIMATION_TIME);
	startTimer(moveTimer);

}

// Random Pattern
void RandAtt() {

	repeatNum = 0; //reset repeatNumber

	srand((unsigned int)time(NULL));
	int num = rand() % 3;

	switch (num) {
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

	turnNum += 1;
	turnCnt = TURN_TIME * 3;
	setTimer(turnTimer, TURN_TICK);
	startTimer(turnTimer);
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

	if (checkCollision(xZombie[repeatNum], (xZombie[repeatNum] + 200), yZombie, yZombie + 354) == true) {
		showMessage("be collided!"); 
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

		if (checkCollision(xBlood1, xBlood1 + 30, 250, 250 + 30) == true) {
			showMessage("be collided!");
		}

		else if (checkCollision(xBlood2, xBlood2 + 30, 250, 250 + 30) == true) {
			showMessage("be collided!");
		}

		else if (checkCollision(644, 644 + 30, yBlood1, yBlood1 + 30) == true) {
			showMessage("be collided!");
		}

		else if (checkCollision(644, 644 + 30, yBlood2, yBlood2 + 30) == true) {
			showMessage("be collided!");
		}

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

	if (checkCollision(xZomhand[repeatNum], (xZomhand[repeatNum] + 50), yZomhand, yZombie + 70) == true) {
		showMessage("be collided!");
	}
}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == zombieF) {
		RandAtt();
	}

	// If player clicked attack, then player attacks zombie as much as weapon's level
	if (object == attack) {
		printf("MouseCallback: monster hurted \n");

		hideObject(attack);
		hideObject(item);
		hideObject(avoid);

		turnNum += 1;
		turnCnt = TURN_TIME;
		setTimer(turnTimer, TURN_TICK);
		startTimer(turnTimer);
	}

	if (object == item) {


	}

	// If player clicked avoid, then player goes back to towerInside3
	if (object == avoid) {
		enterScene(towerInside3);
		sceneNum = 3;

		turnCnt = 0;
		turnNum = 0;
	}
}



void timerCallback(TimerID timer) {

	if (timer == moveTimer) {
		//animation of movement
		Move();
	}

	if (timer == turnTimer) {
		// Making a turn
		if (turnCnt > 0) {
			turnCnt -= 1;

			setTimer(turnTimer, TURN_TICK);
			startTimer(turnTimer);
		}
		else {
			if (turnNum % 2 == 0) {
				printf("TimerCallback: Turn() - Player \n");
			}
			else if (turnNum % 2 == 1) {
				printf("TimerCallback: Turn() - Enemy \n");
			}

			Turn();
		}
	}

	//animation of zombie attack pattern 0
	if (repeatNum < 3 && timer == attTimer0) {
		ZombieAtt0();

		if (repeatNum == 3) {
			locateObject(zombieF, fight3, 600, 480);
		}

	}

	//animation of zombie attack pattern 1a
	if (timer == attTimer1a) {
		hideObject(brain);
		locateObject(explosion, fight3, 644, 250);
		showObject(explosion);
		playSound(explo);
		startTimer(attTimer1b);

	}

	//animation of zombie attack patter 1b
	if (timer == attTimer1b) {
		ZombieAtt1b();
	}

	////animation of zombie attack patter 2
	if (repeatNum < 5 && timer == attTimer2) {
		ZombieAtt2();

	}
}

void keyboardCallback(KeyCode code, KeyState state) {
	// Processing a keyboard input.
	// If player pressed an Up arrow at structures, then player go there. (Not Implemented) 

	if (code == 83) {				// RIGHT

		dx += (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
		dxIcon += (state == KeyState::KEYBOARD_PRESSED ? ANIMATION_STEP : -ANIMATION_STEP);
	}

	else if (code == 82) {			//LEFT

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