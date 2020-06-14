// Preprocessor
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Animation for character's movement
TimerID moveTimer;
const Second MOVE_TICK = 0.025f;
const int MOVE_SPEED = 10;

// Scenes and Objects.
SceneID tower3F_Scene, battle3F_Scene, tower4F_Scene, game4F_Scene;
ObjectID zombieT;
ObjectID attack, item, avoid, zombieF, brain, explosion, blood[4], zomhand;

SceneID currentScene;

//Timer for animation in tower3
TimerID attTimer0, attTimer1a, attTimer1b, attTimer2;
const Second ATT_TICK = 0.05f;

//Timer for animation in tower4
TimerID frogSpawnTimer, frogFlyTimer0, frogFlyTimer1, frogFlyTimer2, spearTimer;;

// Sounds
SoundID zom, explo, hand;

// Player
ObjectID player;
int playerX, playerY;
int dx, dy;

const int playerX_MIN = 50, playerX_MAX = 1150;
const int playerY_FIXED = 175;

ObjectID playerIcon;
ObjectID playerHpBar;
int iconX, iconY;
int iconDx, iconDy;
const int iconX_MIN = 333, iconX_MAX = 943, iconX_SIZE = 40;
const int iconY_MIN = 150, iconY_MAX = 320, iconY_SIZE = 70;
const int playerHpBarX_FIXED = 333, playerHpBarY_FIXED = 50;

int playerHp, playerMaxHp, playerAtk, playerDef;

// Location of zombie
int zombieX[3] = { 600, 450, 750 };
int zombieY = 400;

//  blood 
int bloodX1 = 644;
int bloodX2 = 644;
int bloodY1 = 250;
int bloodY2 = 250;

// Location of zomhand
int zomhandX[5] = { 440, 540, 640, 740, 840 };
int zomhandY = 500;

// curret numbers
int repeatNum = 0;
int turnNum = 0;

// Gold
int gold = 10;
ObjectID goldList[3];
int goldX[3] = { 1040, 1067, 1094 };
int goldY = 595;

//turn ========================================================
TimerID turnTimer;
int turnCnt = 0;
const int TURN_TIME = 20;
const Second TURN_TICK = 0.05f;

// Const variable for turn
const int PLAYER = 0;
const int ENEMY = 1;

// ===============================================================

// Variables about immune
TimerID immuneTimer;
int immuneCnt = 0;
const int IMMUNE_TIME = 20;
const Second IMMUNE_TICK = 0.05f;
bool hitAlready = false;

// Enemy
ObjectID enemy;
ObjectID enemyHpBar;
int enemyX, enemyY;
int enemyHp, enemyMaxHp, enemyAtk, enemyDef;
const int enemyY_FIXED = 410;
const int enemyHpBarX_FIXED = 333, enemyHpBarY_FIXED = 660;

// minigame4 ========================================================

ObjectID miniGameMessage4;

SoundID throwSpearSound;

ObjectID frogT, playerWing;
bool enemyShown = true;
int playerWingX = 100, playerWingY = 300;
int playerWingDx = 0, playerWingDy = 0;
const int playerWingX_SIZE = 100, playerWingY_SIZE = 149;
const int playerWingX_MIN = 0, playerWingX_MAX = 1200;
const int playerWingY_MIN = 30, playerWingY_MAX = 650;

ObjectID spear, frog[5], miniHeart[3];

int heartX[3] = {100,150,200};
const int heartY = 600;
int miniHP = 3;

const int frogY[3] = {100, 300, 500};
int frogX = 1300;
int frogY2 = 600;
int frogRand = 0;
bool frogDown = true;
int frogKill = 0;
const int frogKill_MAX = 10; // the number of frog that player has to kill

int spearX = playerWingX;
int spearY = playerWingY + 50;
const int spearX_SIZE = 160, spearY_SIZE = 30;
bool spearShown = false;

// casino =========================================================================

const int APPLE = 0;
const int GRAPE = 1;
const int ORANGE = 2;

const Second  ROULETTE_TICK = 0.05f; // time gap of question mark appears

ObjectID fruitA[3], fruitB[3], fruitC[3];
int slotNumA, slotNumB, slotNumC;

SceneID casinoScene;
ObjectID questionMark, machine;

TimerID casinoTimer;

SoundID casinoBgm, coin, win;

int spinTime = 0;
bool isSpin = false; // is it spin?

int slotX[3] = { 430, 580, 730 }; // the x of casino slot A, B, C

// miniGame2 =======================================================================================

TimerID bombDropTimer0, bombDropTimer1, bombDropTimer2, bombDropTimer3, bombDropTimer4;

ObjectID playerCart, bomb[4];

SceneID tower2F_Scene, game2F_Scene;

int playerCartX = 300, playerCartDx = 0;
int bombX[5] = { 50, 200, 350, 600, 750 };
int bombY = 600;

// ==========================================================================================

// Functions
void mouseCallback(ObjectID obj, int x, int y, MouseAction action);
void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);
void gameInit();
void playerMove();
void playerIconMove();
void playerWingMove();
void Turn();
// casino
int slotA();
int slotB();
int slotC();
void spin();
void roulette();
// fight3
void randAtt();
void zombieAtt0();
void zombieAtt1a();
void zombieAtt1b();
void zombieAtt2();
// minigame4
void miniCheckHP();
void frogFly0();
void frogFly1();
void frogFly2();
void throwSpear();

// minigame2
void playerCartMove();
void bombDrop();

// ==================================================================================================================================================================

void Turn() {
	// Player Turn
	if (turnNum % 2 == 0) {
		showObject(attack);
		showObject(item);
		showObject(avoid);
	}
	// Enemy Turn
	else if (turnNum % 2 == 1) { // if it's com turn
		randAtt();
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

//Setting elements needed to play game
void gameInit() {

	// Scenes

	game2F_Scene = createScene(" minigame2", "./Images/Backgrounds/Tower_Inside.png");
	tower3F_Scene = createScene(" towerLevel3", "./Images/Backgrounds/Tower_Inside.png");
	battle3F_Scene = createScene("zombie", "./Images/Backgrounds/Battle.png");
	tower4F_Scene = createScene("towerLevel4", "./Images/Backgrounds/Tower_Inside.png");
	game4F_Scene = createScene("minigame4", "./Images/Backgrounds/mini3Background.jpg");

	// ====================================================================

	// Timer for moving
	moveTimer = createTimer(MOVE_TICK);
	startTimer(moveTimer);

	// Timer for turn
	turnTimer = createTimer(MOVE_TICK); // revision! :: modify MOVE_TICK to STH else

	// Timer for zombie fight 3 animation
	attTimer0 = createTimer();
	attTimer1a = createTimer(1.0f);
	attTimer1b = createTimer();
	attTimer2 = createTimer();

	// Timer for immune
	immuneTimer = createTimer(IMMUNE_TICK);

	// Timer for minigame 4
	frogSpawnTimer = createTimer(1.0f);
	frogFlyTimer0 = createTimer();
	frogFlyTimer1 = createTimer();
	frogFlyTimer2 = createTimer();

	spearTimer = createTimer();

	// Timer for minigame 2
	bombDropTimer0 = createTimer();
	bombDropTimer1 = createTimer();
	bombDropTimer2 = createTimer();
	bombDropTimer3 = createTimer();


	// =====================================================================

	// Sound effects
	zom = createSound("./Audios/tower3/zombieWalk.mp3");
	explo = createSound("./Audios/tower3/explosion.mp3");
	hand = createSound("./Audios/tower3/zombieHand.mp3");

	// player
	player = createObject("./Images/Characters/Warrior_R.png");
	scaleObject(player, 0.5f);
	playerX = 100;
	playerY = playerY_FIXED;
	locateObject(player, currentScene, playerX, playerY);
	showObject(player);

	playerHp = 100;
	playerMaxHp = 100;
	playerAtk = 5;
	playerDef = 3;

	playerHpBar = createObject("./Images/UI/Battle/HP/Hp_100%.png");
	locateObject(playerHpBar, battle3F_Scene, playerHpBarX_FIXED, playerHpBarY_FIXED);
	showObject(playerHpBar);

	// zombie
	zombieT = createObject("./Images/Enemies/tower3/zombie.png"); // zombie Tower
	locateObject(zombieT, tower3F_Scene, 750, 180);
	scaleObject(zombieT, 0.5f);
	showObject(zombieT);

	zombieF = createObject("./Images/Enemies/tower3/zombie.png"); // zombie Fight
	locateObject(zombieF, battle3F_Scene, zombieX[0], zombieY);
	scaleObject(zombieF, 0.6f);
	showObject(zombieF);

	enemyHpBar = createObject("./Images/UI/Battle/Hp/Hp_100%.png");
	locateObject(enemyHpBar, battle3F_Scene, enemyHpBarX_FIXED, enemyHpBarY_FIXED);
	showObject(enemyHpBar);


	// icon
	playerIcon = createObject("./Images/Characters/Warrior_I.png");
	iconX = 943;
	iconY = 320;
	locateObject(playerIcon, battle3F_Scene, iconX, iconY);
	showObject(playerIcon);

	// attack
	attack = createObject("./Images/UI/Battle/attack.png");
	locateObject(attack, battle3F_Scene, 310, 80);
	scaleObject(attack, 0.65f);
	showObject(attack);

	// item
	item = createObject("./Images/UI/Battle/item.png");
	locateObject(item, battle3F_Scene, 610, 80);
	scaleObject(item, 0.65f);
	showObject(item);

	// avoid
	avoid = createObject("./Images/UI/Battle/avoid.png");
	locateObject(avoid, battle3F_Scene, 900, 80);
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

	// casion ===================================================================================

	casinoScene = createScene("casino", "./Images/Backgrounds/Casino_Inside.png");
	machine = createObject("./Images/Items/Casino/machine.png");
	locateObject(machine, casinoScene, 260, 25);
	scaleObject(machine, 2.5f);
	showObject(machine);

	char fruitImage[100];
	for (int i = 0; i < 3; i++) {
		sprintf_s(fruitImage, "./Images/Items/Casino/fruitA%d.png", i);
		sprintf_s(fruitImage, "./Images/Items/Casino/fruitB%d.png", i);
		sprintf_s(fruitImage, "./Images/Items/Casino/fruitC%d.png", i);
		fruitA[i] = createObject(fruitImage);
		fruitB[i] = createObject(fruitImage);
		fruitC[i] = createObject(fruitImage);
	}

	casinoBgm = createSound("./Audios/casino/casinoBackground.wav");

	//playSound(bgm);  NEED TO REVISION :: when player enters casion, play this bgm

	coin = createSound("./Audios/casino/coinEffect.wav"); 

	questionMark = createObject("./Images/Items/Casino/questionMark.png"); 

	win = createSound("./Audios/casino/win.mp3"); // sound effect when the three images of fruit equal 

	casinoTimer = createTimer();

	// =====================================================================================================

	// show gold

	goldList[0] = createObject("./Images/Numbers/0_R.png");
	goldList[1] = createObject("./Images/Numbers/1_R.png");
	goldList[2] = createObject("./Images/Numbers/2_R.png");

	for (int i = 0; i < 3; i++) {
		scaleObject(goldList[i], 0.8f);
		locateObject(goldList[i], casinoScene, goldX[i], goldY);  // NEED TO REIVSE
	}

	showGold();


	// minigame 4 ============================================================================

	miniGameMessage4 = createObject("./Images/Messages/miniGameMessage4.png");
	locateObject(miniGameMessage4, game4F_Scene, 0, 0);

	throwSpearSound = createSound("./Audios/tower4/throwSpear.wav");

	frogT = createObject("./Images/Enemies/tower4/flyingFrog1.png");
	locateObject(frogT, tower4F_Scene, 800, 180);
	scaleObject(frogT, 1.5f);
	showObject(frogT);

	playerWing = createObject("./Images/Characters/flyingWarrior.png");
	locateObject(playerWing, game4F_Scene, 100, 300);
	showObject(playerWing);
	
	spear = createObject("./Images/Enemies/tower4/spear.png");

	char frogImage[100];
	for (int i = 0; i < 3; i++) {
		sprintf_s(frogImage, "./Images/Enemies/tower4/flyingFrog%d.png", i);
		frog[i] = createObject(frogImage);
	}

	char heartImage[100];
	for (int i = 0; i < 3; i++) {
		sprintf_s(heartImage, "./Images/Enemies/tower4/H%d.png", i);
		miniHeart[i] = createObject(heartImage);
		locateObject(miniHeart[i], game4F_Scene, heartX[i],heartY);
		showObject(miniHeart[i]);
		scaleObject(miniHeart[i], 0.5f);
	}

	// minigame 2 =====================================================================
	
	playerCart = createObject("./Images/UI/MiniGame2/Cart.png");
	locateObject(playerCart, game2F_Scene, playerCartX, playerY);
	showObject(playerCart);
	
	char bombImage[100];
	for (int i = 0; i < 4; i++) {
		sprintf_s(bombImage, "./Images/UI/MiniGame2/Bomb_%d.png", i);
		bomb[i] = createObject(bombImage);
		locateObject(bomb[i], game2F_Scene, bombX[i], bombY);
		showObject(bomb[i]);
	}

}

bool checkCollision(ObjectID object, int xStart, int xEnd, int yStart, int yEnd) {
	// Check a collsion, then return a result.

	// About Collision:
	// We can find 'collision' with position and size.
	// If enemy attack's X is about 400 ~ 600,
	// then X_MIN <= player's X <= 360 (360 can be replaced with 400 - SIZE) or 600 <= player's X <= X_MAX
	// If enemy attack's Y is about 230 ~ 300,
	// then Y_MIN <= player's Y <= 160 (160 can be replaced with 230 - SIZE) or 300 <= player's Y <= Y_MAX

	// Conclusion:
	// If a <= attack's range <= b, then player will be hit when (a - SIZE) < player's position < b

	if (object == playerIcon) {
		bool xCollision = ((xStart - iconX_SIZE) < iconX) and (iconX < xEnd);
		bool yCollision = ((yStart - iconY_SIZE) < iconY) and (iconY < yEnd);

		return xCollision and yCollision;
	}
	
	if (object == spear) {
		bool xCollision = ((xStart - spearX_SIZE) < spearX) and (spearX < xEnd);
		bool yCollision = ((yStart - spearY_SIZE) < spearY) and (spearY < yEnd);
		return xCollision and yCollision;

	}


}

void playerMove(void) {
	// Move a player. (towerScene)

	playerX += dx;

	// Bug fix:
	// Fixed a bug - Difference between player's direction and image.
	// Change an image with player's direction.
	if (dx < 0) {
		setObjectImage(player, "./Images/Characters/Warrior_L.png");
	}

	else if (dx > 0) {
		setObjectImage(player, "./Images/Characters/Warrior_R.png");
	}

	if (dx < -MOVE_SPEED) {
		dx = -MOVE_SPEED;
	}
	else if (dx > MOVE_SPEED) {
		dx = MOVE_SPEED;
	}
	if (dy < -MOVE_SPEED) {
		dy = -MOVE_SPEED;
	}
	else if (dy > MOVE_SPEED) {
		dy = MOVE_SPEED;
	}

	// Set a restriction.
	if (playerX < playerX_MIN) {
		playerX = playerX_MIN;
	}
	else if (playerX > playerX_MAX) {
		playerX = playerX_MAX;
	}

	locateObject(player, currentScene, playerX, playerY);

	setTimer(moveTimer, MOVE_TICK);
	startTimer(moveTimer);
}

void playerIconMove(void) {
	// Move a player-icon. (battleScene)

	// Bug fix:
	// Fixed a bug.
	if (iconDx < -MOVE_SPEED) {
		iconDx = -MOVE_SPEED;
	}
	else if (iconDx > MOVE_SPEED) {
		iconDx = MOVE_SPEED;
	}
	if (iconDy < -MOVE_SPEED) {
		iconDy = -MOVE_SPEED;
	}
	else if (iconDy > MOVE_SPEED) {
		iconDy = MOVE_SPEED;
	}


	// Set a restriction.
	iconX += iconDx;
	if (iconX < iconX_MIN) {
		iconX = iconX_MIN;
	}
	else if (iconX > iconX_MAX) {
		iconX = iconX_MAX;
	}

	iconY += iconDy;
	if (iconY < iconY_MIN) {
		iconY = iconY_MIN;
	}
	else if (iconY > iconY_MAX) {
		iconY = iconY_MAX;
	}

	locateObject(playerIcon, currentScene, iconX, iconY);

	setTimer(moveTimer, MOVE_TICK);
	startTimer(moveTimer);
}

void playerWingMove(void) {

	// Movemnet of Flying Warrior
	if (currentScene == game4F_Scene) {
		playerWingX += playerWingDx;
		playerWingY += playerWingDy;

		locateObject(playerWing, game4F_Scene, playerWingX, playerWingY);

	}

	if (playerWingX < playerWingX_MIN) {
		playerWingX = playerWingX_MIN;
	}
	else if (playerWingX > playerWingX_MAX) {
		playerWingX = playerWingX_MAX;
	}

	if (playerWingY < playerWingY_MIN) {
		playerWingY = playerWingY_MIN;
	}
	else if (playerWingY > playerWingY_MAX) {
		playerWingY = playerWingY_MAX;
	}

	setTimer(moveTimer, MOVE_TICK);
	startTimer(moveTimer);

}

//minigame2
void playerCartMove(void) {

	playerCartX += playerCartDx;

	// Set a restriction.
	/*
	if (playerCartX < playerX_MIN) {
		playerCartX = playerX_MIN;
	}
	else if (playerCartX > playerX_MAX) {
		playerCartX = playerX_MAX;
	}
	*/

	locateObject(playerCart, game2F_Scene, playerCartX, playerY);

	setTimer(moveTimer, MOVE_TICK);
	startTimer(moveTimer);
}

void checkHp(int kind) {
	// Check object's Hp and change Hp bar with their Hp percent.

	float hpPercent;
	ObjectID hpBar;
	if (kind == PLAYER) {
		hpPercent = static_cast<float>(playerHp) / static_cast<float>(playerMaxHp);
		hpBar = playerHpBar;
	}
	else if (kind == ENEMY) {
		hpPercent = static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp);
		hpBar = enemyHpBar;
	}

	if (0.75f < hpPercent and hpPercent <= 1.0f) {
		setObjectImage(hpBar, "./Images/UI/Battle/Hp/Hp_100%.png");
	}
	else if (0.5f < hpPercent and hpPercent <= 0.75f) {
		setObjectImage(hpBar, "./Images/UI/Battle/Hp/Hp_75%.png");
	}
	else if (0.25f < hpPercent and hpPercent <= 0.5f) {
		setObjectImage(hpBar, "./Images/UI/Battle/Hp/Hp_50%.png");
	}
	else if (0.1f < hpPercent and hpPercent <= 0.25f) {
		setObjectImage(hpBar, "./Images/UI/Battle/Hp/Hp_25%.png");
	}
	else if (0.0f < hpPercent and hpPercent <= 0.1f) {
		setObjectImage(hpBar, "./Images/UI/Battle/Hp/Hp_10%.png");
	}
	else {
		// HP is 0, so we have to do something at here.
		setObjectImage(hpBar, "./Images/UI/Battle/Hp/Hp_0%.png");
	}
}

// ===========================================================================================================

// make random number for slot A
int slotA() {  
	slotNumA = rand() % 3;
	return slotNumA;
}

//make random number for slot B
int slotB() { 
	slotNumB = rand() % 3;
	return slotNumB;
}

//make random number for slot C
int slotC() { 
	slotNumC = rand() % 3;
	return slotNumC;
}

// question mark appears every slot in turn.
void spin() { // the question mark appears 

	isSpin = true; // it's spinning

	for (int i = 0; i < 3; i++) { // reset every slot
		hideObject(fruitA[i]);
		hideObject(fruitB[i]);
		hideObject(fruitC[i]);
	}

	spinTime += 30;

	//animation for spinning
	if (spinTime < 100) {
		hideObject(questionMark);
		showObject(questionMark);
		locateObject(questionMark, casinoScene, slotX[0], 300);
		setTimer(casinoTimer, ROULETTE_TICK);
		startTimer(casinoTimer);


	}
	else if (spinTime > 100 && spinTime < 200) {
		hideObject(questionMark);
		locateObject(questionMark, casinoScene, slotX[1], 300);
		showObject(questionMark);
		setTimer(casinoTimer, ROULETTE_TICK);
		startTimer(casinoTimer);
	}

	else if (spinTime > 200 && spinTime <= 300) {
		hideObject(questionMark);
		locateObject(questionMark, casinoScene, slotX[2], 300);
		showObject(questionMark);
		setTimer(casinoTimer, ROULETTE_TICK);
		startTimer(casinoTimer);
	}

	else {
		hideObject(questionMark);
		roulette(); // after question mark appears slotC, random fruits appear at the screen
	}
}

// fruits appear every slot
void roulette() {

	isSpin = false; // spin stopped

	locateObject(fruitA[slotA()], casinoScene, slotX[0], 310); 
	showObject(fruitA[slotNumA]);

	locateObject(fruitB[slotB()], casinoScene, slotX[1], 310); 
	showObject(fruitB[slotNumB]);

	locateObject(fruitC[slotC()], casinoScene, slotX[2], 310); 
	showObject(fruitC[slotNumC]);

	if (slotNumA == slotNumB && slotNumB == slotNumC && slotNumC == APPLE) {
		gold += 5;
		showGold();

		playSound(win);
	}

	else if (slotNumA == slotNumB && slotNumB == slotNumC && slotNumC == GRAPE) {
		gold += 8;
		showGold();

		playSound(win);
	}	

	else if (slotNumA == slotNumB && slotNumB == slotNumC && slotNumC == ORANGE) {
		gold += 10;
		showGold();

		playSound(win);
	}

}

// ===========================================================================================================
// Random Pattern
void randAtt() {

	repeatNum = 0; //reset repeatNumber

	srand((unsigned int)time(NULL));
	int num = rand() % 3;

	switch (num) {
	case 0:
		zombieAtt0();
		startTimer(attTimer0);
		break;

	case 1:
		zombieAtt1a();
		break;

	case 2:zombieAtt2();
		zombieAtt2();
		startTimer(attTimer2);
		break;
	}

	turnNum += 1;
	turnCnt = TURN_TIME * 3;
	setTimer(turnTimer, TURN_TICK);
	startTimer(turnTimer);
}

// pattern0 : zombie itself goes down
void zombieAtt0() {

	playSound(zom);

	if (zombieY >= 0) {

		zombieY -= 60;
		locateObject(zombieF, battle3F_Scene, zombieX[repeatNum], zombieY);

		setTimer(attTimer0, ATT_TICK);
		startTimer(attTimer0);

		if (zombieY < 0) {
			zombieY = 900;
			repeatNum++;
		}
	}

	if (checkCollision(playerIcon, zombieX[repeatNum], (zombieX[repeatNum] + 200), zombieY, zombieY + 354) && hitAlready == false) {

		hitAlready = true;
		immuneCnt = IMMUNE_TIME;
		setTimer(immuneTimer, IMMUNE_TICK);
		startTimer(immuneTimer);

		playerHp -= 20; // NEED TO REVISE
		checkHp(PLAYER);
	}
}

// pattern1a : brain appears at the center and explodes in 1 sec. 
void zombieAtt1a() {

	setTimer(attTimer1a, 0.5f);
	startTimer(attTimer1a);

	for (int i = 0; i < 4; i++) {
		showObject(blood[i]);
		locateObject(blood[i], battle3F_Scene, 644, 250);
	}


	locateObject(brain, battle3F_Scene, 644, 250);
	showObject(brain);


}

// pattern1b : after explosion, four blood cells flies away in a form of cross
void zombieAtt1b() {
	if (bloodX1 >= 340 && bloodX2 <= 940 && bloodY2 >= 150 && bloodY1 <= 320) {

		bloodX1 -= 40;
		bloodX2 += 40;
		bloodY1 -= 40;
		bloodY2 += 40;

		locateObject(blood[0], battle3F_Scene, bloodX1, 250);
		locateObject(blood[1], battle3F_Scene, bloodX2, 250);
		locateObject(blood[2], battle3F_Scene, 644, bloodY1);
		locateObject(blood[3], battle3F_Scene, 644, bloodY2);

		setTimer(attTimer1b, ATT_TICK);
		startTimer(attTimer1b);

		if (checkCollision(playerIcon, bloodX1, bloodX1 + 30, 250, 250 + 30) == true && hitAlready == false) {

			

			hitAlready = true;
			immuneCnt = IMMUNE_TIME;
			setTimer(immuneTimer, IMMUNE_TICK);
			startTimer(immuneTimer);

			playerHp -= 20; // NEED TO REVISE
			checkHp(PLAYER);
		}

		else if (checkCollision(playerIcon, bloodX2, bloodX2 + 30, 250, 250 + 30) == true && hitAlready == false) {

			hitAlready = true;
			immuneCnt = IMMUNE_TIME;
			setTimer(immuneTimer, IMMUNE_TICK);
			startTimer(immuneTimer);

			playerHp -= 20; // NEED TO REVISE
			checkHp(PLAYER);
		}

		else if (checkCollision(playerIcon, 644, 644 + 30, bloodY1, bloodY1 + 30) == true && hitAlready == false) {

		
			hitAlready = true;
			immuneCnt = IMMUNE_TIME;
			setTimer(immuneTimer, IMMUNE_TICK);
			startTimer(immuneTimer);

			playerHp -= 20; // NEED TO REVISE
			checkHp(PLAYER);

		}

		else if (checkCollision(playerIcon, 644, 644 + 30, bloodY2, bloodY2 + 30) == true && hitAlready == false) {

			hitAlready = true;
			immuneCnt = IMMUNE_TIME;
			setTimer(immuneTimer, IMMUNE_TICK);
			startTimer(immuneTimer);

			playerHp -= 20; // NEED TO REVISE
			checkHp(PLAYER);
		}

		// if blood cells go outside of rectangle, it disappears 
		if (bloodX1 <= 340 && bloodX2 >= 940 && bloodY1 <= 150 && bloodY2 >= 320) {


			for (int i = 0; i < 4; i++) {
				hideObject(blood[i]);
			}

			stopTimer(attTimer1b);

			bloodX1 = 644;
			bloodX2 = 644;
			bloodY1 = 250;
			bloodY2 = 250;


			hideObject(explosion);
		}

	}

}

// pattern2 : zombie's hand appears at random X, certain Y and goes down. repeats for five times.
void zombieAtt2() { 

	playSound(hand);
	zomhandY -= 50;
	locateObject(zomhand, battle3F_Scene, zomhandX[repeatNum], zomhandY);
	showObject(zomhand);

	if (zomhandY < 0) {
		hideObject(zomhand);
		zomhandY = 500;
		repeatNum++;
	}

	setTimer(attTimer2, ATT_TICK);
	startTimer(attTimer2);

	if (checkCollision(playerIcon, zomhandX[repeatNum], (zomhandX[repeatNum] + 50), zomhandY, zomhandY + 70) == true && hitAlready == false) {

		hitAlready = true;
		immuneCnt = IMMUNE_TIME;
		setTimer(immuneTimer, IMMUNE_TICK);
		startTimer(immuneTimer);

		playerHp -= 20; // NEED TO REVISE
		checkHp(PLAYER);
	}
}

// ========================================================================================================

// in minigame, check my heart 
void miniCheckHP() {

	miniHP--;
	
	if (miniHP == 2) {
		hideObject(miniHeart[2]);
	}

	else if (miniHP == 1) {
		hideObject(miniHeart[1]);
	}

	else if (miniHP == 0) {
		playerHp -= 20;

		hideObject(miniHeart[0]);
		enterScene(tower4F_Scene);
		currentScene = tower4F_Scene;

	}
}

// angel flies to left side
void frogFly0() { 
	
	if (frogX < 0) {

		hideObject(frog[0]);
		stopTimer(frogFlyTimer0);
		setTimer(frogSpawnTimer, 1.0f);
		startTimer(frogSpawnTimer);

	}

	else {

		frogX -= 80;
		locateObject(frog[0], game4F_Scene, frogX, frogY[1]);
		showObject(frog[0]);
		setTimer(frogFlyTimer0, ATT_TICK);
		startTimer(frogFlyTimer0);
		
		if (checkCollision(spear, frogX, frogX + 100, frogY[1], frogY[1] + 110) == true && spearShown == true) { 

			//when player throws spear to angel, heart disappears
			miniCheckHP();

			hideObject(frog[0]);
			stopTimer(frogFlyTimer0);
			setTimer(frogSpawnTimer, 1.0f);
			startTimer(frogSpawnTimer);


		}

	}
}

// frog flies fast to left side
void frogFly1() {

	if (frogX < 0) {
		miniCheckHP();
		hideObject(frog[1]);
		stopTimer(frogFlyTimer1);
		setTimer(frogSpawnTimer, 1.0f);
		startTimer(frogSpawnTimer);

	}

	else {

		frogX -= 60;
		locateObject(frog[1], game4F_Scene, frogX, frogY[1]);
		showObject(frog[1]);
		setTimer(frogFlyTimer1, ATT_TICK);
		startTimer(frogFlyTimer1);

		if (checkCollision(spear, frogX, frogX + 100, frogY[1], frogY[1] + 110) == true && spearShown == true) {

			//when player throws spear to angel, heart disappears

			hideObject(frog[1]);
			stopTimer(frogFlyTimer1);
			setTimer(frogSpawnTimer, 1.0f);
			startTimer(frogSpawnTimer);
			frogKill++;


		}



	}
}

// frog flies slow, but it fluctuates
void frogFly2() { 

	if (frogX < 0) {
		frogY2 = 600;
		hideObject(frog[2]);
		stopTimer(frogFlyTimer2);
		setTimer(frogSpawnTimer, 1.0f);
		startTimer(frogSpawnTimer);

		// when frog goes outside of screen, heart disapears
		miniCheckHP();

	}

	else {

		if (frogDown == true) {

			frogX -= 20;
			frogY2 -= 30;
			locateObject(frog[2], game4F_Scene, frogX, frogY2);
			showObject(frog[2]);
			setTimer(frogFlyTimer2, ATT_TICK);
			startTimer(frogFlyTimer2);

			if (checkCollision(spear, frogX, frogX + 100, frogY2, frogY2 + 80) == true && spearShown == true) {
				frogKill++;
				hideObject(frog[2]);
				stopTimer(frogFlyTimer2);
				setTimer(frogSpawnTimer, 1.0f);
				startTimer(frogSpawnTimer);
			}


			else if (frogY2 <= 100) {
				frogDown = false;
			}

		}

		else if (frogDown == false) {

			frogX -= 20;
			frogY2 += 30;
			locateObject(frog[2], game4F_Scene, frogX, frogY2);
			showObject(frog[2]);
			setTimer(frogFlyTimer2, ATT_TICK);
			startTimer(frogFlyTimer2);

			if (checkCollision(spear, frogX, frogX + 100, frogY2, frogY2 + 80) == true && spearShown == true) {
				frogKill++;
				hideObject(frog[2]);
				stopTimer(frogFlyTimer2);
				setTimer(frogSpawnTimer, 1.0f);
				startTimer(frogSpawnTimer);
			}

		

			else if (frogY2 >= 500) {
				frogDown = true;
			}

		}

	}

}

// In minigame, the player throws spear to the right side
void throwSpear() {
	if (spearX > 1280) {
		hideObject(spear);
		stopTimer(spearTimer);
		spearShown = false;
	}

	else {
		spearX += 100; // spear speed
		locateObject(spear, game4F_Scene, spearX, spearY);
		showObject(spear);

		
		setTimer(spearTimer, ATT_TICK);
		startTimer(spearTimer);
		spearShown = true;
	}
	
}

// ========================================================================================================

void bombDrop(){
	
	bombY -= 30;
	
	for (int i = 0; i < 4; i++) {
	locateObject(bomb[i], game2F_Scene, bombX[i], bombY);
	}

	setTimer(bombDropTimer0, MOVE_TICK);
	startTimer(bombDropTimer0);
	
	setTimer(bombDropTimer1, MOVE_TICK);
	startTimer(bombDropTimer1);
							  
	setTimer(bombDropTimer2, MOVE_TICK);
	startTimer(bombDropTimer2);
							  
	setTimer(bombDropTimer3, MOVE_TICK);
	startTimer(bombDropTimer3);

	}

// ========================================================================================================

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	

	// If player clicked attack, then player attacks zombie as much as weapon's level
	if (object == attack) {
		enemyHp -= 20; // NEED TO REVISE!
		checkHp(ENEMY);

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
		enterScene(tower3F_Scene);// revision! :: currentScene = where?
		
		
		turnCnt = 0;
		turnNum = 0;
	}

	else if (object == miniGameMessage4) {

		frogKill = 0;
		miniHP = 3;
		for (int i = 0; i < 3; i++) {
			showObject(miniHeart[i]);
		}

		startTimer(frogSpawnTimer);

		hideObject(miniGameMessage4);
	}
}

void timerCallback(TimerID timer) {

	if (timer == moveTimer) {

		if (currentScene == tower3F_Scene || currentScene == tower4F_Scene) {
			playerMove();
		}

		else if (currentScene == battle3F_Scene) {
			playerIconMove();
		}
		else if (currentScene == game4F_Scene) {
			playerWingMove();
		}

		else if (currentScene == game2F_Scene) {
			playerCartMove();
		}

	}
	
	

	if (timer == casinoTimer) {
		spin();
	}

	if (timer == turnTimer) {
		// Make a turn.
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

	if (timer == immuneTimer) {
		// Make a player immune state.
		if (immuneCnt > 0) {
			immuneCnt -= 1;

			setTimer(immuneTimer, IMMUNE_TICK);
			startTimer(immuneTimer);
		}
		else {
			hitAlready = false;
		}
	}

	//=======================================================================================

	//animation of zombie attack pattern 0
	if (repeatNum < 3 && timer == attTimer0) {
		zombieAtt0();

		if (repeatNum == 3) {
			locateObject(zombieF, battle3F_Scene, 600, 400);
		}

	}

	//animation of zombie attack pattern 1a
	if (timer == attTimer1a) {
		hideObject(brain);
		locateObject(explosion, battle3F_Scene, 644, 250);
		showObject(explosion);
		playSound(explo);
		startTimer(attTimer1b);

	}

	//animation of zombie attack patter 1b
	if (timer == attTimer1b) {
		zombieAtt1b();
	}

	//animation of zombie attack patter 2
	if (repeatNum < 5 && timer == attTimer2) {
		zombieAtt2();

	}

	//=======================================================================================

	if (timer == frogSpawnTimer) {

		if (frogKill < frogKill_MAX) { // player has to kill frog as much as frog kill_MAX

		frogX = 1300;

		srand((unsigned int)time(NULL));
		frogRand = rand() % 3;

			switch (frogRand) {
			case 0:
				frogFly0();
				startTimer(frogFlyTimer0);
				break;
	
			case 1:
				frogFly1();
				startTimer(frogFlyTimer1);
				break;

			case 2:
				frogFly2();
				startTimer(frogFlyTimer2);
				break;
			}

		}

		else { // if player kills frog as much as frogKill_MAX, player can go next floor

			hideObject(frogT);
			enemyShown = false;

			currentScene = tower4F_Scene;
			enterScene(tower4F_Scene);

		}
	}

	if (timer == frogFlyTimer0) {

		frogFly0();
	}

	if (timer == frogFlyTimer1) {

		frogFly1();
	}

	if (timer == frogFlyTimer2) {
		frogFly2();
	}

	if (timer == spearTimer) {
		throwSpear();
	}


	//=======================================================================================
}

void keyboardCallback(KeyCode code, KeyState state) {
	// Processing a keyboard input.
	// If player pressed an Up arrow at structures, then player go there. (Not Implemented) 

	if (code == 83) {				// RIGHT

		
		if (currentScene == tower3F_Scene || currentScene == tower4F_Scene) {
			dx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);

		}

		if (currentScene == battle3F_Scene) {
			iconDx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}
		
		if (currentScene == game4F_Scene) {
			playerWingDx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

		if (currentScene == game2F_Scene) {
			playerCartDx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

		
	}

	else if (code == 82) {			//LEFT

		if (currentScene == tower3F_Scene || currentScene == tower4F_Scene) {
			dx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);

		}

		if (currentScene == battle3F_Scene) {
			iconDx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

		if (currentScene == game4F_Scene) {
			playerWingDx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

		if (currentScene == game2F_Scene) {
			playerCartDx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

	}

	else if (code == 84) {			// UP

		if (currentScene == tower3F_Scene && playerX >= 750) { 
			currentScene = battle3F_Scene;
			enterScene(battle3F_Scene);
						
		}

		if (currentScene == battle3F_Scene) {
			iconDy += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);

		}

		if (enemyShown == true && currentScene == tower4F_Scene && playerX >= 750) {
			
			// in case player tries minigame again
			showObject(miniGameMessage4);
			stopTimer(frogSpawnTimer);
			stopTimer(frogFlyTimer0);
			stopTimer(frogFlyTimer1);
			stopTimer(frogFlyTimer2);

			currentScene = game4F_Scene;
			enterScene(game4F_Scene);
			
		}

		if (currentScene == game4F_Scene) {
			playerWingDy += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}
		
	}

	else if (code == 85) {		// DOWN

		if (currentScene == battle3F_Scene) {
			iconDy -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

		if (currentScene == game4F_Scene) {
			playerWingDy -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}


	}

	else if (code == 75) {		// SPACEBAR
		
		if (currentScene == casinoScene && isSpin == false && gold > 0 && state == KeyState::KEYBOARD_PRESSED) {

			gold -= 1;
			showGold();

			spinTime = 0;
			spin();
			playSound(coin);

		}

		if (currentScene == game4F_Scene && spearShown == false && state == KeyState::KEYBOARD_PRESSED ) {
			playSound(throwSpearSound);
			spearX = playerWingX;
			spearY = playerWingY + 50;
			throwSpear();
		}
		
	}

}

int main() {

	srand((unsigned int)time(NULL));

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);

	gameInit();
	
	// Starting a game

	enemyHp = 100;
	enemyMaxHp = 100;

	currentScene = game2F_Scene; //revision! 
	startGame(currentScene);

}