// Preprocessor
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

// Enemy's attack
class Attack1 {
public:
	ObjectID obj;
	int x, y, dy;

public:
	Attack1(ObjectID obj, int x, int y, int dy) : obj(obj), x(x), y(y), dy(dy) {};
};

class Attack2 {
public:
	ObjectID left, right;
	ObjectID rect;
	int left_x, right_x, rect_x, y;
	int time;
	bool isRect;

public:
	Attack2(ObjectID left, ObjectID right, ObjectID rect, int y, int time) : left(left), right(right), rect(rect), y(y), time(time) {
		left_x = 983;
		right_x = 273;
		rect_x = 333;
		isRect = false;
	};
};

ObjectID casino;

// Animation for character's movement
TimerID moveTimer;
const Second MOVE_TICK = 0.025f;
const int MOVE_SPEED = 10;

// Scenes and Objects.
SceneID tower3F_Scene, battle3F_Scene, tower4F_Scene, game4F_Scene;
ObjectID zombieT;
ObjectID attack, item, avoid, zombieF, brain, explosion, blood[4], zomhand;
SceneID gameOverScene;
SceneID villageLeftScene;
SceneID villageScene;
SceneID tower5F_Scene, battle5F_Scene;
SceneID tower6F_Scene, game6F_Scene;
//SceneID tower1F_Scene, battle1F_Scene;
SceneID storeScene;

SceneID currentScene;

//Timer for animation in tower3
TimerID attTimer0, attTimer1a, attTimer1b, attTimer2;
const Second ATT_TICK = 0.05f;

//Timer for animation in tower4
TimerID frogSpawnTimer, frogFlyTimer0, frogFlyTimer1, frogFlyTimer2, spearTimer;;

// Sounds
SoundID zom, explo, hand;
SoundID hitSound;      // Player was hit.
SoundID attackSound;   // Player attacked.

// Days
int day = 1;
const int DAY_LIMIT = 14;
bool isNight = false;

// Structures and messages
ObjectID house;
ObjectID store, tower;
ObjectID messageObj;

// Objects about store
ObjectID item0, item1, item2, item3, item4, item5,item6, item7, item8, item9, item10, item11, item12;
ObjectID soldOut[10], box[10], price[10], itemBox, storePixel[3], storeRightArrow, storeLeftArrow, storeList1, storeList2, storeList3, storeBackGround, backToTown;

//Locations of storePixel
int storePixelX[3] = { 570, 770, 970 };
int storeListX[3] = { 530, 660, 790 };

//Check if items are sold or not
bool soldOuted[11] = { false, false, false, false, false, false, false, false, false, false, false };

// Characters (Not Implemented)
ObjectID merchant;

ObjectID CanNotRestMessage;


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

// Buttons
ObjectID attackButton, itemButton, avoidButton;
ObjectID outButton;
const int buttonY_FIXED = 80;

// Attack1
int enemyAtt1Cnt = 0, enemyAtt1MaxCnt = 40;
const int enemyAtt1StartCnt = 40;
const int enemyAtt1Y_FIXED = 440;
const int enemyAtt1X_SIZE = 34, enemyAtt1Y_SIZE = 30;

// Attack2
int enemyAtt2Cnt = 0, enemyAtt2MaxCnt = 10;
const int enemyAtt2StartCnt = 10;
const int enemyAtt2Time = 10;
const int enemyAtt2X_SIZE = 650, enemyAtt2Y_SIZE = 34;
int canMakeAtt2Cnt = 0;
bool canMakeAtt2 = true;

std::vector<Attack1> attacks1;
std::vector<Attack2> attacks2;

// Puzzle
const int emptyNum = 4;

class Puzzle {
public:
	ObjectID obj;
	int x, y, num;

public:
	Puzzle() : x(0), y(0), num(0) {
		obj = createObject("nothing");
	}
	Puzzle(int num, int x, int y) : x(x), y(y), num(num) {
		char imageName[60];
		sprintf_s(imageName, sizeof(imageName), "./Images/UI/Puzzle/Partitions2/%d.png", num);
		obj = createObject(imageName);

		locateObject(obj, game6F_Scene, x, y);
	};

public:
	void changeImage(int num) {
		this->num = num;

		char imageName[60];
		sprintf_s(imageName, sizeof(imageName), "./Images/UI/Puzzle/Partitions2/%d.png", num);
		setObjectImage(this->obj, imageName);

		if (this->num == emptyNum) {
			hideObject(this->obj);
		}
		else {
			showObject(this->obj);
		}
	}
	void changeLocation(int x, int y) {
		this->x = x;
		this->y = y;

		locateObject(this->obj, game6F_Scene, this->x, this->y);
	}
};

int puzzleX[3] = { 375, 552, 729 };
int puzzleY[3] = { 447, 270, 93 };
Puzzle puzzleList[3][3];
ObjectID puzzleT;
bool puzzleTShown = true;
const int puzzleTX_FIXED = 760, puzzleTY_FIXED = 200;

// ====================================================================================


// Location of zombie
int zombieX[3] = { 600, 450, 750 };
int zombieY = 400;
int zombieFHp = 100, zombieFHpMax = 100;

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

// Const variable for turn
const int PLAYER = 0;
const int ENEMY = 1;

// Animation for turn
TimerID turnTimer;
int turn = PLAYER;
int turnCnt = 0;
const int TURN_TIME = 20;
const Second TURN_TICK = 0.05f;

// ===============================================================

// Variables about immune
TimerID immuneTimer;
int immuneCnt = 0;
const int IMMUNE_TIME = 20;
const Second IMMUNE_TICK = 0.05f;
bool hitAlready = false;

// Animation for enemy's attack
TimerID enemyAtt1, enemyAtt2, enemyAtt3;
TimerID enemyAtt2Maker;
const Second ATTACK_TICK = 0.05f;
int GRAVITY = 2;

// Animation for message
TimerID messageTimer;
int messageCnt = 0;
const int MESSAGE_TIME = 1;
const Second MESSAGE_TICK = 1.0f;
/*
//Animation for 1st floor battle
TimerID dropTimer;
const Second SNOW_TICK = 0.1f;
*/
// Animation for game over
TimerID gameOverTimer;
int overCnt = 0;
const int OVER_TIME = 1;
const Second OVER_TICK = 1.0f;

// Enemy
ObjectID enemy;
ObjectID enemyT;
ObjectID enemyHpBar;
int enemyX, enemyY;
int enemyHp, enemyMaxHp, enemyAtk, enemyDef;
bool enemyTShown = true;
const int enemyY_FIXED = 410;
const int enemyTX_FIXED = 850, enemyTY_FIXED = 200;
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


// Functions
void mouseCallback(ObjectID obj, int x, int y, MouseAction action);
void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);
void gameInit();
void playerMove();
void playerIconMove();
void playerWingMove();

void changeToNight(void);
void rest(void);

void battle(void);
void enemyAttack(void);
void enemyAttack1(void);
void enemyAttack2(bool half);
void enemyAttack3(void);

void puzzleInit(void);
bool isEnd(void);
void isTouching(int x, int y);
void puzzleEnd(void);

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

// ==================================================================================================================================================================

void Turn() {
	// Player Turn
	if (turnNum % 2 == 0) {
		showObject(attackButton);
		showObject(itemButton);
		showObject(avoidButton);
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

	// setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	// Timers for turn, immune, and attacks
	enemyAtt1 = createTimer(ATTACK_TICK);
	enemyAtt2 = createTimer(ATTACK_TICK);
	enemyAtt3 = createTimer(ATTACK_TICK);
	enemyAtt2Maker = createTimer(ATTACK_TICK);
	messageTimer = createTimer(MESSAGE_TICK);
	gameOverTimer = createTimer(OVER_TICK);


	// Scenes
	villageScene = createScene("villageScene", "./Images/Backgrounds/DayTime.png");
	tower3F_Scene = createScene(" towerLevel3", "./Images/Backgrounds/Tower_Inside.png");
	battle3F_Scene = createScene("zombie", "./Images/Backgrounds/Battle.png");
	tower4F_Scene = createScene("towerLevel4", "./Images/Backgrounds/Tower_Inside.png");
	game4F_Scene = createScene("minigame4", "./Images/Backgrounds/mini3Background.jpg");
	tower5F_Scene = createScene("Tower - 5F", "./Images/Backgrounds/Tower_Inside.png");
	battle5F_Scene = createScene("Black Knight", "./Images/Backgrounds/Battle.png");
	tower6F_Scene = createScene("Tower - 6F", "./Images/Backgrounds/Tower_Inside.png");
	game6F_Scene = createScene("Puzzle", "./Images/Backgrounds/Puzzle_6F.png");
	villageLeftScene = createScene("Village", "./Images/Backgrounds/DayTime.png");
	// REVISION currentScene =
	
		// Buttons
	attackButton = createObject("./Images/UI/Battle/Attack.png");
	locateObject(attackButton, battle5F_Scene, 310, buttonY_FIXED);
	scaleObject(attackButton, 0.65f);
	showObject(attackButton);

	itemButton = createObject("./Images/UI/Battle/Item.png");
	locateObject(itemButton, battle5F_Scene, 610, buttonY_FIXED);
	scaleObject(itemButton, 0.65f);
	showObject(itemButton);

	avoidButton = createObject("./Images/UI/Battle/Avoid.png");
	locateObject(avoidButton, battle5F_Scene, 890, buttonY_FIXED);
	scaleObject(avoidButton, 0.65f);
	showObject(avoidButton);

	outButton = createObject("./Images/UI/Puzzle/OutButton.png");
	locateObject(outButton, game6F_Scene, puzzleX[2] + 187, puzzleY[2] - 5);
	showObject(outButton);
	


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

	// =====================================================================
		/*
	//Enemy in 1st floor
	ObjectID enemy1FTower;
	ObjectID enemy1FBattle;
	int enemyX, enemyY;
	int enemyHp, enemyMaxHp, enemyAtk, enemyDef;
	const int enemyY_FIXED = 410;
	const int enemyHpBarX_FIXED = 333, enemyHpBarY_FIXED = 660;

	//Enemy in 1st floor's monster attack
	ObjectID snow;
	int snowX[5] = { 410, 460, 510, 550, 590 };
	int snowY = 380;
	*/
	// =====================================================================
	// Sound effects
	zom = createSound("./Audios/tower3/zombieWalk.mp3");
	explo = createSound("./Audios/tower3/explosion.mp3");
	hand = createSound("./Audios/tower3/zombieHand.mp3");
	hitSound = createSound("./Audios/HitSound.wav");
	attackSound = createSound("./Audios/AttackSound.wav");


	// Enemy
	enemy = createObject("./Images/Enemies/BlackKnight.png");
	enemyX = 590;
	enemyY = enemyY_FIXED;
	enemyHp = 200;
	enemyMaxHp = 200;
	enemyAtk = 20;
	enemyDef = 10;
	locateObject(enemy, battle5F_Scene, enemyX, enemyY);
	scaleObject(enemy, 0.15f);
	showObject(enemy);

	enemyT = createObject("./Images/Enemies/BlackKnight.png");
	locateObject(enemyT, tower5F_Scene, enemyTX_FIXED, enemyTY_FIXED);
	scaleObject(enemyT, 0.22f);
	showObject(enemyT);

	enemyHpBar = createObject("./Images/UI/Battle/Hp/Hp_100%.png");
	locateObject(enemyHpBar, battle5F_Scene, enemyHpBarX_FIXED, enemyHpBarY_FIXED);
	showObject(enemyHpBar);

	// Puzzle
	puzzleT = createObject("./Images/UI/Puzzle/DoorT.png");
	locateObject(puzzleT, tower6F_Scene, puzzleTX_FIXED, puzzleTY_FIXED);
	showObject(puzzleT);


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
	// store  ===================================================================================
	storeScene = createScene("storeScene", "./Images/Backgrounds/Store_Inside.png");


	casino = createObject("./Images/Structures/Casino.png");
	locateObject(casino, villageLeftScene, 117, 195);
	showObject(casino);

	house = createObject("./Images/Structures/House.png");
	locateObject(house, villageLeftScene, 800, 195);
	showObject(house);

	for (int i = 0; i < 3; i++) {
			scaleObject(goldList[i], 0.8f);
			locateObject(goldList[i], storeScene, goldX[i], goldY);  // NEED TO REIVSE
		}



	//store
	store = createObject("./Images/Structures/Store.png");
	locateObject(store, villageScene, 117, 195);
	showObject(store);

	//tower
	tower = createObject("./Images/Structures/Tower.png");
	locateObject(tower, villageScene, 817, 195);
	showObject(tower);

	//storeArrow
	storeBackGround = createObject("./Images/Items/Store/UI/store_background.png");
	locateObject(storeBackGround, storeScene, 530, 180);
	scaleObject(storeBackGround, 0.55f);
	showObject(storeBackGround);

	//storePixel[3]
	for (int j = 0; j < 3; j++) {
		storePixel[j] = createObject("./Images/Items/Store/UI/StorePixel.png");
		locateObject(storePixel[j], storeScene, storePixelX[j], 192);
		scaleObject(storePixel[j], 0.5f);
		showObject(storePixel[j]);
	}

	//storeArrow
	storeRightArrow = createObject("./Images/Items/Store/UI/Store_rightarrow.png");
	locateObject(storeRightArrow, storeScene, 1175, 330);
	scaleObject(storeRightArrow, 0.6f);
	showObject(storeRightArrow);

	storeLeftArrow = createObject("./Images/Items/Store/UI/Store_leftarrow.png");
	locateObject(storeLeftArrow, storeScene, 1175, 330);
	scaleObject(storeLeftArrow, 0.6f);
	hideObject(storeLeftArrow);

	//coin
	coin = createObject("./Images/Items/Coin.png");
	locateObject(coin, storeScene, 1000, 650);
	scaleObject(coin, 0.6f);
	showObject(coin);

	//price[10]
	int priceX[3] = { 593, 793, 993 };
	int priceY = 200;

	price[0] = createObject("./Images/Numbers/1.png");
	locateObject(price[0], storeScene, priceX[0], priceY);
	scaleObject(price[0], 0.7f);
	showObject(price[0]);

	price[1] = createObject("./Images/Numbers/1.png");
	locateObject(price[1], storeScene, priceX[1], priceY);
	scaleObject(price[1], 0.7f);
	showObject(price[1]);

	price[2] = createObject("./Images/Numbers/5.png");
	locateObject(price[2], storeScene, priceX[2], priceY);
	scaleObject(price[2], 0.7f);
	showObject(price[2]);

	price[3] = createObject("./Images/Numbers/6.png");
	locateObject(price[3], storeScene, priceX[0], priceY);
	scaleObject(price[3], 0.7f);
	hideObject(price[3]);

	price[4] = createObject("./Images/Numbers/1.png");
	locateObject(price[4], storeScene, priceX[0], priceY);
	scaleObject(price[4], 0.7f);
	hideObject(price[4]);

	price[5] = createObject("./Images/Numbers/3.png");
	locateObject(price[5], storeScene, priceX[1], priceY);
	scaleObject(price[5], 0.7f);
	hideObject(price[5]);

	price[6] = createObject("./Images/Numbers/5.png");
	locateObject(price[6], storeScene, priceX[2], priceY);
	scaleObject(price[6], 0.7f);
	hideObject(price[6]);

	price[7] = createObject("./Images/Numbers/2.png");
	locateObject(price[7], storeScene, priceX[0], priceY);
	scaleObject(price[7], 0.7f);
	hideObject(price[7]);

	price[8] = createObject("./Images/Numbers/4.png");
	locateObject(price[8], storeScene, priceX[1], priceY);
	scaleObject(price[8], 0.7f);
	hideObject(price[8]);

	price[9] = createObject("./Images/Numbers/5.png");
	locateObject(price[9], storeScene, priceX[2], priceY);
	scaleObject(price[9], 0.7f);
	hideObject(price[9]);

	//storeList[3]

	storeList1 = createObject("./Images/Items/Store/UI/StoreList1.png");
	locateObject(storeList1, storeScene, 570, 472);
	scaleObject(storeList1, 0.6f);
	showObject(storeList1);

	storeList2 = createObject("./Images/Items/Store/UI/StoreList2.png");
	locateObject(storeList2, storeScene, 770, 472);
	scaleObject(storeList2, 0.6f);
	showObject(storeList2);

	storeList3 = createObject("./Images/Items/Store/UI/StoreList3.png");
	locateObject(storeList3, storeScene, 970, 472);
	scaleObject(storeList3, 0.6f);
	showObject(storeList3);

	//item[13]
	item0 = createObject("./Images/Items/Store/Equipments/Sword.png");
	locateObject(item0, storeScene, 600, 320);
	scaleObject(item0, 0.7f);
	showObject(item0);

	item1 = createObject("./Images/Items/Store/Equipments/Shield.png");
	locateObject(item1, storeScene, 790, 320);
	scaleObject(item1, 0.7f);
	showObject(item1);

	item2 = createObject("./Images/Items/Store/Equipments/Axe.png");
	locateObject(item2, storeScene, 1000, 320);
	scaleObject(item2, 0.7f);
	showObject(item2);

	item3 = createObject("./Images/Items/Store/Equipments/Spear.png");
	locateObject(item3, storeScene, 600, 320);
	scaleObject(item3, 0.7f);
	hideObject(item3);

	item4 = createObject("./Images/Items/Store/Potions/BluePotion.png");
	locateObject(item4, storeScene, 605, 320);
	scaleObject(item4, 0.5f);
	hideObject(item4);

	item10 = createObject("./Images/Items/Store/Potions/BluePotion.png");
	locateObject(item10, storeScene, 605, 320);
	scaleObject(item10, 0.5f);
	hideObject(item10);

	item5 = createObject("./Images/Items/Store/Potions/GreenPotion.png");
	locateObject(item5, storeScene, 805, 320);
	scaleObject(item5, 0.5f);
	hideObject(item5);

	item11 = createObject("./Images/Items/Store/Potions/GreenPotion.png");
	locateObject(item11, storeScene, 805, 320);
	scaleObject(item11, 0.5f);
	hideObject(item11);

	item6 = createObject("./Images/Items/Store/Potions/RedPotion.png");
	locateObject(item6, storeScene, 1005, 320);
	scaleObject(item6, 0.5f);
	hideObject(item6);

	item12 = createObject("./Images/Items/Store/Potions/RedPotion.png");
	locateObject(item12, storeScene, 1005, 320);
	scaleObject(item12, 0.5f);
	hideObject(item12);

	item7 = createObject("./Images/Items/Store/Potions/Meat.png");
	locateObject(item7, storeScene, 605, 320);
	scaleObject(item7, 0.5f);
	hideObject(item7);

	item8 = createObject("./Images/Items/Store/Potions/Mushroom.png");
	locateObject(item8, storeScene, 805, 320);
	scaleObject(item8, 0.5f);
	hideObject(item8);

	item9 = createObject("./Images/Items/Store/Potions/Carrot.png");
	locateObject(item9, storeScene, 1005, 320);
	scaleObject(item9, 0.3f);
	hideObject(item9);

	backToTown = createObject("./Images/UI/Store/BackToTown.png");
	locateObject(backToTown, storeScene, 24, 640);
	scaleObject(backToTown, 0.35f);
	showObject(backToTown);

	merchant = createObject("./Images/Characters/MerchantIcon.png");
	locateObject(merchant, storeScene, 130, 0);
	scaleObject(merchant, 1.1f);
	showObject(merchant);

	soldOut[0] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[0], storeScene, 563, 350);
	scaleObject(soldOut[0], 0.7f);
	hideObject(soldOut[0]);

	soldOut[3] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[3], storeScene, 563, 350);
	scaleObject(soldOut[3], 0.7f);
	hideObject(soldOut[3]);

	soldOut[4] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[4], storeScene, 563, 350);
	scaleObject(soldOut[4], 0.7f);
	hideObject(soldOut[4]);

	soldOut[7] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[7], storeScene, 563, 350);
	scaleObject(soldOut[7], 0.7f);
	hideObject(soldOut[7]);

	soldOut[1] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[1], storeScene, 763, 350);
	scaleObject(soldOut[1], 0.7f);
	hideObject(soldOut[1]);

	soldOut[5] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[5], storeScene, 763, 350);
	scaleObject(soldOut[5], 0.7f);
	hideObject(soldOut[5]);

	soldOut[8] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[8], storeScene, 763, 350);
	scaleObject(soldOut[8], 0.7f);
	hideObject(soldOut[8]);

	soldOut[2] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[2], storeScene, 963, 350);
	scaleObject(soldOut[2], 0.7f);
	hideObject(soldOut[2]);

	soldOut[6] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[6], storeScene, 963, 350);
	scaleObject(soldOut[6], 0.7f);
	hideObject(soldOut[6]);

	soldOut[9] = createObject("./Images/Items/Store/UI/soldOut.png");
	locateObject(soldOut[9], storeScene, 963, 350);
	scaleObject(soldOut[9], 0.7f);
	hideObject(soldOut[9]);

	int boxX[10] = { 573, 773, 973, 573, 598, 798, 998, 563, 757, 957 };
	int boxY[10] = { 180, 180, 180, 180, 180, 180, 180, 185, 185, 185 };
	char boxImage[100];
	for (int i = 0; i < 10; i++) {
		sprintf_s(boxImage, "./Images/Items/Store/UI/Box_%d.png", i);
		box[i] = createObject(boxImage);
		locateObject(box[i], storeScene, boxX[i], boxY[i]);
		scaleObject(box[i], 0.6f);
		if ((i == 0) || (i == 1) || (i == 2)) {
			showObject(box[i]);
		}
		else if ((i == 7) || (i == 8) || (i == 9)) {
			locateObject(box[i], storeScene, boxX[i] + 5, boxY[i]);
			scaleObject(box[i], 0.4f);
		}
		else {
			hideObject(box[i]);

		}
	}

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
		locateObject(goldList[i], storeScene, goldX[i], goldY);  // NEED TO REIVSE
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
		locateObject(miniHeart[i], game4F_Scene, heartX[i], heartY);
		showObject(miniHeart[i]);
		scaleObject(miniHeart[i], 0.5f);
	}

}
void changeToNight(void) {
	// Change a time to night.

	if (not isNight) {
		isNight = true;
		setSceneImage(villageLeftScene, "./Images/Backgrounds/NightTime.png");
		setSceneImage(villageScene, "./Images/Backgrounds/NightTime.png");
	}
}

void rest(void) {
	// Change a day to tomorrow.

	if (isNight) {
		if (day < DAY_LIMIT) {
			playerHp = playerMaxHp;
			day += 1;

			setSceneImage(villageLeftScene, "./Images/Backgrounds/DayTime.png");
			setSceneImage(villageScene, "./Images/Backgrounds/DayTime.png");
			isNight = false;
		}
		else {
			// At DAY_LIMIT, enter scene to game over.
			// gameOverScene = createScene("game over", "./Images/Backgrounds/GameOver.jpg");
			// enterScene(gameOverScene);
			// overCnt = OVER_TIME;
			// setTimer(gameOverTimer, OVER_TICK);
			// startTimer(gameOverTimer);
		}
	}
	else {
		showMessage("밤에만 잘 수 있어요");
	}
}

// ====================================================================================

void battle(void) {
	// Start a battle.
	// When battle ends: Player selects avoid, Player died, Enemy died.
	if (turn == PLAYER) {
		showObject(attackButton);
		showObject(itemButton);
		showObject(avoidButton);
	}
	else if (turn == ENEMY) {
		enemyAttack();
	}
}

void enemyAttack(void) {
	int a1_min = 0, a1_max = 0;
	int a2_min = 0, a2_max = 0;
	int a3_min = 0, a3_max = 0;
	if (0.75f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
		a1_min = 1;
		a1_max = 50;
		a2_min = 51;
		a2_max = 100;
	}
	else if (0.5f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
		a1_min = 1;
		a1_max = 40;
		a2_min = 41;
		a2_max = 80;
		a3_min = 81;
		a3_max = 100;
	}
	else if (0.25f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
		a1_min = 1;
		a1_max = 30;
		a2_min = 31;
		a2_max = 60;
		a3_min = 61;
		a3_max = 100;
	}
	else {
		a3_min = 1;
		a3_max = 100;
	}

	int strategy = rand() % 100 + 1;
	if (a1_min <= strategy and strategy <= a1_max) {
		enemyAttack1();

		turn = PLAYER;
		turnCnt = TURN_TIME * 5;
		setTimer(turnTimer, TURN_TICK);
		startTimer(turnTimer);
	}
	else if (a2_min <= strategy and strategy <= a2_max) {
		enemyAttack2(false);

		turn = PLAYER;
		turnCnt = TURN_TIME * 10;
		setTimer(turnTimer, TURN_TICK);
		startTimer(turnTimer);
	}
	else if (a3_min <= strategy and strategy <= a3_max) {
		enemyAttack3();

		turn = PLAYER;
		turnCnt = TURN_TIME * 6;
		setTimer(turnTimer, TURN_TICK);
		startTimer(turnTimer);
	}
}

void enemyAttack1(void) {
	if (0.5f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
		enemyAtt1MaxCnt = enemyAtt1StartCnt;
	}
	else if (0.25f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
		enemyAtt1MaxCnt = static_cast<int>(enemyAtt1StartCnt * 1.5f);
	}
	else {
		enemyAtt1MaxCnt = enemyAtt1StartCnt * 2;
	}

	enemyAtt1Cnt = enemyAtt1MaxCnt;

	setTimer(enemyAtt1, ATTACK_TICK);
	startTimer(enemyAtt1);
}

void enemyAttack2(bool half) {
	if (half) {
		enemyAtt2MaxCnt = static_cast<int>(enemyAtt2StartCnt * 0.5f);
	}
	else {
		enemyAtt2MaxCnt = enemyAtt2StartCnt;
	}

	enemyAtt2Cnt = enemyAtt2MaxCnt;

	setTimer(enemyAtt2, ATTACK_TICK);
	startTimer(enemyAtt2);
}

void enemyAttack3(void) {
	enemyAttack1();
	enemyAttack2(true);
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

// ====================================================================================

void puzzleInit(void) {
	Puzzle puzzleTempList[9];
	for (int i = 0; i < 9; i++) {
		puzzleTempList[i] = Puzzle(i, puzzleX[i % 3], puzzleY[i / 3]);
		if (i == emptyNum) {
			hideObject(puzzleTempList[i].obj);
		}
		else {
			showObject(puzzleTempList[i].obj);
		}
	}

	bool already[9] = { false };
	int puzzleRandomNum[9] = { 0 };
	int index = 0;
	while (index != 9) {
		int temp = rand() % 9;

		if (!already[temp]) {
			puzzleRandomNum[index++] = temp;
			already[temp] = true;
		}
	}
	index = 0;

	/*
	// Use it for check answer.
	// If you want to use it, you have to comment up-lines (bool already ~ index = 0;)
	int puzzleRandomNum[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int index = 0;
	*/

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			puzzleList[y][x] = puzzleTempList[puzzleRandomNum[index++]];
			puzzleList[y][x].changeLocation(puzzleX[x], puzzleY[y]);
		}
	}
}

bool isEnd(void) {
	int index = 0;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			if (puzzleList[y][x].num == index) index += 1;
			else return false;
		}
	}
	return true;
}

void isTouching(int x, int y) {
	if (puzzleList[y][x].num == emptyNum) {
		return;
	}

	if (0 <= x - 1) {
		if (puzzleList[y][x - 1].num == emptyNum) {
			puzzleList[y][x - 1].changeImage(puzzleList[y][x].num);
			puzzleList[y][x].changeImage(emptyNum);

			if (isEnd()) {
				puzzleEnd();
			}
		}
	}
	if (x + 1 <= 2) {
		if (puzzleList[y][x + 1].num == emptyNum) {
			puzzleList[y][x + 1].changeImage(puzzleList[y][x].num);
			puzzleList[y][x].changeImage(emptyNum);

			if (isEnd()) {
				puzzleEnd();
			}
		}
	}
	if (0 <= y - 1) {
		if (puzzleList[y - 1][x].num == emptyNum) {
			puzzleList[y - 1][x].changeImage(puzzleList[y][x].num);
			puzzleList[y][x].changeImage(emptyNum);

			if (isEnd()) {
				puzzleEnd();
			}
		}
	}
	if (y + 1 <= 2) {
		if (puzzleList[y + 1][x].num == emptyNum) {
			puzzleList[y + 1][x].changeImage(puzzleList[y][x].num);
			puzzleList[y][x].changeImage(emptyNum);

			if (isEnd()) {
				puzzleEnd();
			}
		}
	}
}

void puzzleEnd(void) {
	setObjectImage(puzzleT, "./Images/UI/Puzzle/DoorT_Open.png");
	puzzleTShown = false;

	currentScene = tower6F_Scene;
	enterScene(currentScene);
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

void checkHp(int kind) {
	// Check object's Hp and change Hp bar with their Hp percent.

	float hpPercent;
	ObjectID hpBar;
	if (kind == PLAYER) {
		hpPercent = static_cast<float>(playerHp) / static_cast<float>(playerMaxHp);
		hpBar = playerHpBar;
	}
	else if (kind == ENEMY) {
		if (currentScene == battle3F_Scene) {
			hpPercent = static_cast<float>(zombieFHp) / static_cast<float>(zombieFHpMax);
		}
		else if (currentScene == battle5F_Scene) {
			hpPercent = static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp);
		}
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

		playerHp -= 20;

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


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == CanNotRestMessage) {
		hideObject(CanNotRestMessage);
	}
	
	if (object == attackButton) {

		enemyHp -= (playerAtk - enemyDef > 0 ? playerAtk - enemyDef : 1);
		playSound(attackSound);
		checkHp(ENEMY);

		hideObject(attackButton);
		hideObject(itemButton);
		hideObject(avoidButton);

		if (currentScene == battle5F_Scene) {
			turn = ENEMY;
			turnCnt = TURN_TIME;
			setTimer(turnTimer, TURN_TICK);
			startTimer(turnTimer);
		}

		else if (currentScene == battle3F_Scene) {
			zombieFHp -= 20;
			turnNum += 1;
			turnCnt = TURN_TIME;
			setTimer(turnTimer, TURN_TICK);
			startTimer(turnTimer);
		}

		if (enemyHp <= 0 and currentScene == battle5F_Scene) {
			enemyTShown = false;
			hideObject(enemyT);

			gold += 100;

			currentScene = tower5F_Scene;
			enterScene(tower5F_Scene);
		}

		if (zombieFHp <= 0 and currentScene == battle3F_Scene) {
			enemyShown = false;
			hideObject(zombieT);

			gold += 10;

			currentScene = tower3F_Scene;
			enterScene(tower3F_Scene);

		}

		else {
			turn = ENEMY;
			turnCnt = TURN_TIME;
			setTimer(turnTimer, TURN_TICK);
			startTimer(turnTimer);
		}
	}
	
	else if (object == itemButton) {
		// do something with item.
	}
	else if (object == avoidButton) {
		enemyHp = enemyMaxHp;
		checkHp(ENEMY);

		hideObject(attackButton);
		hideObject(itemButton);
		hideObject(avoidButton);

		changeToNight();
		enterScene(villageLeftScene);
		currentScene = villageLeftScene;
	}

	// Puzzles
	else if (object == outButton) {
		playerHp -= static_cast<int>(playerMaxHp * 0.1f);
		for (int y = 0; y < 3; y++) {
			for (int x = 0; x < 3; x++) {
				hideObject(puzzleList[y][x].obj);
			}
		}

		// Player's hp can be 0
		if (playerHp <= 0) {
			// do something
		}

		currentScene = tower6F_Scene;
		enterScene(tower6F_Scene);
	}
	else if (object == puzzleList[0][0].obj) {
		isTouching(0, 0);
	}
	else if (object == puzzleList[0][1].obj) {
		isTouching(1, 0);
	}
	else if (object == puzzleList[0][2].obj) {
		isTouching(2, 0);
	}
	else if (object == puzzleList[1][0].obj) {
		isTouching(0, 1);
	}
	else if (object == puzzleList[1][1].obj) {
		isTouching(1, 1);
	}
	else if (object == puzzleList[1][2].obj) {
		isTouching(2, 1);
	}
	else if (object == puzzleList[2][0].obj) {
		isTouching(0, 2);
	}
	else if (object == puzzleList[2][1].obj) {
		isTouching(1, 2);
	}
	else if (object == puzzleList[2][2].obj) {
		isTouching(2, 2);
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
	//store
	else if (currentScene = storeScene) {
		if (object == backToTown) {
		enterScene(villageScene);
		currentScene = villageScene;
		showObject(player);
		}
		else if (object == merchant) {
		showMessage("you can buy things to kill monster");
		}
	
		else if (object == storeList1) {
			for (int i = 0; i < 3; i++) {
				showObject(box[i]);
				if (soldOuted[i] == true) {//if the user bought the item, show "soldOut.png" by determining bool soldOuted[i] 
					showObject(soldOut[i]);
				}
				showObject(price[i]);
			}
			showObject(item0);
			showObject(item1);
			showObject(item2);
			showObject(storeRightArrow);
			for (int i = 4; i < 10; i++) {
				hideObject(soldOut[i]);
				hideObject(box[i]);
				hideObject(price[i]);
			}
			hideObject(item3);
			hideObject(item4);
			hideObject(item5);
			hideObject(item6);
			hideObject(item7);
			hideObject(item8);
			hideObject(item9);
		}
	}

	else if (object == storeList2) {
		for (int i = 0; i < 4; i++) {
			hideObject(soldOut[i]);
			hideObject(box[i]);
			hideObject(price[i]);
		}
		hideObject(item0);
		hideObject(item1);
		hideObject(item2);
		hideObject(item3);
		hideObject(item8);
		hideObject(item9);
		for (int i = 7; i < 10; i++) {
			
			hideObject(soldOut[i]);
			hideObject(box[i]);
			hideObject(price[i]);
		}
		for (int i = 4; i < 7; i++) {
			showObject(box[i]);
			if (soldOuted[i] == true) {
				showObject(soldOut[i]);
			}
			showObject(price[i]);
		}
		showObject(item4);
		showObject(item5);
		showObject(item6);
		showObject(item7);
		hideObject(storeRightArrow);
		hideObject(storeLeftArrow);
	}
	else if (object == storeList3) {
		for (int i = 0; i < 8; i++) {
			hideObject(soldOut[i]);
			hideObject(box[i]);
			hideObject(price[i]);
		}
		hideObject(item0);
		hideObject(item1);
		hideObject(item2);
		hideObject(item3);
		hideObject(item4);
		hideObject(item5);
		hideObject(item6);
		hideObject(item7);

		for (int i = 7; i < 10; i++) {
			showObject(box[i]);
			showObject(price[i]);
			if (soldOuted[i] == true) {
				showObject(soldOut[i]);
			}
		}
		showObject(item7);
		showObject(item8);
		showObject(item9);
		hideObject(storeRightArrow);
		hideObject(storeLeftArrow);

	}
	else if (object == storeRightArrow) {
		for (int i = 0; i < 3; i++) {
			hideObject(soldOut[i]);
			hideObject(box[i]);
			hideObject(price[i]);
		}
		hideObject(item0);
		hideObject(item1);
		hideObject(item2);
		hideObject(storeRightArrow);
		showObject(item3);
		showObject(box[3]);
		showObject(price[3]);
		if (soldOuted[3] == true) {//if the user bought the item, show "soldOut.png" by determining bool soldOuted[i] 
			showObject(soldOut[3]);
		}
		showObject(storeLeftArrow);

	}
	else if (object == storeLeftArrow) {
		hideObject(item3);
		hideObject(box[3]);
		hideObject(soldOut[3]);
		hideObject(price[3]);
		showObject(storeRightArrow);
		hideObject(storeLeftArrow);
		for (int i = 0; i < 3; i++) {
			showObject(box[i]);
			showObject(price[i]);
			if (soldOuted[i] == true) {//if the user bought the item, show "soldOut.png" by determining bool soldOuted[i] 
				showObject(soldOut[i]);
			}
		}
		showObject(item0);
		showObject(item1);
		showObject(item2);
	}
	else if (object == item0) {

		if (gold > 10) {
			pickObject(item0);
			gold = gold - 10;
			showGold();
			showObject(soldOut[0]);
			soldOuted[0] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}


	else if (object == item1) {

		if (gold > 10) {
			pickObject(item1);
			gold = gold - 10;
			showGold();
			showObject(soldOut[1]);
			soldOuted[1] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}

	else if (object == item2) {

		if (gold > 30) {
			pickObject(item2);
			gold = gold - 30;
			showGold();
			showObject(soldOut[2]);
			soldOuted[2] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}

	}



	else if (object == item3) {

		if (gold > 50) {
			pickObject(item3);
			gold = gold - 50;
			showGold();
			showObject(soldOut[3]);
			soldOuted[3] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
		/*
		else if (currentScene = battle1F_Scene) {
			if (pushatk == true) {
				n = n + 35;;//will adapt changed checkhp method m means player's damage
			}
		}*/
	}
	else if (object == item4) {

		if (gold > 10) {
			pickObject(item4);
			gold = gold - 10;
			showGold();
			// playSound(cash);
			showObject(item10);
		}
		else {
			showMessage("you need more cash");
		}
	}
	else if (object == item10) {
		if (gold > 10) {
			pickObject(item10);
			gold = gold - 10;
			showGold();
			showObject(soldOut[4]);
			soldOuted[4] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}
	else if (object == item7) {
		if (gold > 15) {
			pickObject(item7);
			gold = gold - 15;
			showGold();
			showObject(soldOut[7]);
			soldOuted[7] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}

	else if (object == item5) {
		if (gold > 20) {
			pickObject(item5);
			gold = gold - 20;
			showGold();
			showObject(item11);
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}

	else if (object == item11) {
		if (gold > 20) {
			pickObject(item11);
			gold = gold - 20;
			showGold();
			showObject(soldOut[5]);
			soldOuted[5] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}

	else if (object == item6) {
		if (gold > 30) {
			pickObject(item6);
			gold = gold - 30;
			showGold();
			showObject(item12);
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}
	else if (object == item12) {
		if (gold > 30) {
			pickObject(item12);
			gold = gold - 30;
			showGold();
			showObject(soldOut[6]);
			soldOuted[6] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}
	else if (object == item8) {
		if (gold > 25) {
			pickObject(item8);
			gold = gold - 25;
			showGold();
			showObject(soldOut[8]);
			soldOuted[8] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}

	else if (object == item9) {
		if (gold > 30) {
			pickObject(item9);
			gold = gold - 30;
			showGold();
			showObject(soldOut[9]);
			soldOuted[9] = true;
			// playSound(cash);
		}
		else {
			showMessage("you need more cash");
		}
	}

}

void timerCallback(TimerID timer) {

	if (timer == moveTimer) {

		if (currentScene == villageScene or currentScene == villageLeftScene or currentScene == tower3F_Scene || currentScene == tower4F_Scene || currentScene == tower5F_Scene or currentScene == tower6F_Scene) {
			playerMove();
		}

		else if (currentScene == battle3F_Scene or currentScene == battle5F_Scene) {
			playerIconMove();
		}
		else if (currentScene == game4F_Scene) {
			playerWingMove();

		}

		else if (currentScene == game6F_Scene or currentScene == storeScene or currentScene == casinoScene) {
			setTimer(moveTimer, MOVE_TICK);
			startTimer(moveTimer);
		}

	}

	if (timer == casinoTimer) {
		spin();
	}


	if (timer == turnTimer) {
		if (currentScene == battle3F_Scene) {


			// Make a turn.
			if (turnCnt > 0) {
				turnCnt -= 1;

				setTimer(turnTimer, TURN_TICK);
				startTimer(turnTimer);
			}
			else {
				if (turnNum == 0) {
					printf("TimerCallback: Turn() - Player \n");
				}
				else if (turnNum % 2 == 1) {
					printf("TimerCallback: Turn() - Enemy \n");
				}

				Turn();
			}

		}

		else if (currentScene == battle5F_Scene) {
			if (turnCnt > 0) {
				turnCnt -= 1;

				setTimer(turnTimer, TURN_TICK);
				startTimer(turnTimer);
			}
			else {
				battle();
			}
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

	else if (timer == messageTimer) {
		if (messageCnt > 0) {
			messageCnt -= 1;

			if (messageCnt == 0) {
				hideObject(messageObj);
			}

			setTimer(messageTimer, MESSAGE_TICK);
			startTimer(messageTimer);
		}
	}
	else if (timer == gameOverTimer) {
		if (overCnt > 0) {
			overCnt -= 1;

			if (overCnt == 0) {
				endGame();
			}
		}
	}
	
	else if (timer == enemyAtt1) {
		if (enemyAtt1Cnt > 0) {
			attacks1.push_back(Attack1(createObject("./Images/Enemies/Att_Down.png"), iconX, enemyAtt1Y_FIXED, 0));

			enemyAtt1Cnt -= 1;
		}

		int erased = 0;
		for (int i = 0; i < (enemyAtt1MaxCnt - enemyAtt1Cnt); i++) {
			if (0.5f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
				attacks1[i].dy -= GRAVITY;
			}
			else if (0.25f < static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp)) {
				attacks1[i].dy -= static_cast<int>(GRAVITY * 1.5f);
			}
			else {
				attacks1[i].dy -= GRAVITY * 2;
			}

			attacks1[i].y += attacks1[i].dy;

			if (attacks1[i].y < 100) {
				hideObject(attacks1[i].obj);
				erased += 1;
			}
			else {
				locateObject(attacks1[i].obj, battle5F_Scene, attacks1[i].x, attacks1[i].y);
				showObject(attacks1[i].obj);

				if (checkCollision(playerIcon, attacks1[i].x + 3, attacks1[i].x + 3 + enemyAtt1X_SIZE, attacks1[i].y, attacks1[i].y + enemyAtt1Y_SIZE) and not hitAlready) {
					playerHp -= (enemyAtk - playerDef > 0 ? enemyAtk - playerDef : 1);
					playSound(hitSound);
					checkHp(PLAYER);

					if (playerHp <= 0) {
						// Player died (Not Implemented)

					}

					hitAlready = true;
					immuneCnt = IMMUNE_TIME;
					setTimer(immuneTimer, IMMUNE_TICK);
					startTimer(immuneTimer);
				}
			}
		}

		if (enemyAtt1Cnt != 0) {
			setTimer(enemyAtt1, ATTACK_TICK);
			startTimer(enemyAtt1);
		}
		else {
			if (erased != enemyAtt1MaxCnt) {
				setTimer(enemyAtt1, ATTACK_TICK);
				startTimer(enemyAtt1);
			}
			else {
				attacks1.clear();
			}
		}
	}
	else if (timer == enemyAtt2) {
		if (enemyAtt2Cnt > 0 and canMakeAtt2) {
			ObjectID left = createObject("./Images/Enemies/Att_Left.png");
			ObjectID right = createObject("./Images/Enemies/Att_Right.png");
			ObjectID rect = createObject("./Images/Enemies/Att_Rect.png");

			attacks2.push_back(Attack2(left, right, rect, iconY + 15, enemyAtt2Time));
			enemyAtt2Cnt -= 1;

			canMakeAtt2 = false;
			if (static_cast<float>(enemyHp) / static_cast<float>(enemyMaxHp) < 0.5f) {
				canMakeAtt2Cnt = static_cast<int>(enemyAtt2Time * 1.2f);
			}
			else {
				canMakeAtt2Cnt = static_cast<int>(enemyAtt2Time * 1.5f);
			}
			setTimer(enemyAtt2Maker, ATTACK_TICK);
			startTimer(enemyAtt2Maker);
		}

		int erased = 0;
		for (int i = 0; i < (enemyAtt2MaxCnt - enemyAtt2Cnt); i++) {
			if (not attacks2[i].isRect) {
				locateObject(attacks2[i].left, battle5F_Scene, attacks2[i].left_x, attacks2[i].y);
				locateObject(attacks2[i].right, battle5F_Scene, attacks2[i].right_x, attacks2[i].y);
				showObject(attacks2[i].left);
				showObject(attacks2[i].right);

				if (attacks2[i].time >= 0) {
					attacks2[i].time -= 1;
				}
				else {
					attacks2[i].time = enemyAtt2Time;
					attacks2[i].isRect = true;
				}
			}
			else {
				locateObject(attacks2[i].rect, battle5F_Scene, attacks2[i].rect_x, attacks2[i].y);
				showObject(attacks2[i].rect);
				hideObject(attacks2[i].left);
				hideObject(attacks2[i].right);

				if (attacks2[i].time >= 0) {
					attacks2[i].time -= 1;

					if (checkCollision(playerIcon, attacks2[i].rect_x, attacks2[i].rect_x + enemyAtt2X_SIZE, attacks2[i].y, attacks2[i].y + enemyAtt2Y_SIZE) and not hitAlready) {
						playerHp -= (enemyAtk - playerDef > 0 ? enemyAtk - playerDef : 1);
						playSound(hitSound);
						checkHp(PLAYER);

						if (playerHp <= 0) {
							// Player died (Not Implemented)

						}

						hitAlready = true;
						immuneCnt = IMMUNE_TIME;
						setTimer(immuneTimer, IMMUNE_TICK);
						startTimer(immuneTimer);
					}
				}
				else {
					hideObject(attacks2[i].rect);
					erased += 1;
				}
			}
		}

		if (enemyAtt2Cnt != 0) {
			setTimer(enemyAtt2, ATTACK_TICK);
			startTimer(enemyAtt2);
		}
		else {
			if (erased != enemyAtt2MaxCnt) {
				setTimer(enemyAtt2, ATTACK_TICK);
				startTimer(enemyAtt2);
			}
			else {
				attacks2.clear();
			}
		}
	}
	else if (timer == enemyAtt2Maker) {
		if (canMakeAtt2Cnt > 0) {
			canMakeAtt2Cnt -= 1;

			setTimer(enemyAtt2Maker, ATTACK_TICK);
			startTimer(enemyAtt2Maker);
		}
		else {
			canMakeAtt2 = true;
		}
	}


	//=======================================================================================
}

void keyboardCallback(KeyCode code, KeyState state) {
	// Processing a keyboard input.
	// If player pressed an Up arrow at structures, then player go there. (Not Implemented) 

	if (code == 83) {				// RIGHT

		
		if (currentScene == villageLeftScene or currentScene == villageScene or currentScene == tower3F_Scene || currentScene == tower4F_Scene or currentScene == tower5F_Scene or currentScene == tower6F_Scene) {
			dx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);

		}

		if (currentScene == battle3F_Scene or currentScene == battle5F_Scene) {
			iconDx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}
		
		if (currentScene == game4F_Scene) {
			playerWingDx += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

	
		
	}

	else if (code == 82) {			//LEFT

		if (currentScene == villageLeftScene or currentScene == villageScene or currentScene == tower3F_Scene || currentScene == tower4F_Scene or currentScene == tower5F_Scene or currentScene == tower6F_Scene or currentScene == villageScene) {
			dx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);

		}

		if (currentScene == battle3F_Scene or currentScene == battle5F_Scene) {
			iconDx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

		if (currentScene == game4F_Scene) {
			playerWingDx -= (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}

	}

	else if (code == 84) {			// UP

		if (currentScene == villageLeftScene && playerX >= 170 && playerX <= 270) {
			enterScene(casinoScene);
			currentScene = casinoScene;

			for (int i = 0; i < 3; i++) {
				scaleObject(goldList[i], 0.8f);
				locateObject(goldList[i], casinoScene, goldX[i], goldY);  // NEED TO REIVSE
			}

			showGold();

		}

		if (currentScene == tower3F_Scene && playerX >= 700 && playerX <= 800) { 

			attackButton = createObject("./Images/UI/Battle/Attack.png");
			locateObject(attackButton, battle3F_Scene, 310, buttonY_FIXED);
			scaleObject(attackButton, 0.65f);
			showObject(attackButton);

			itemButton = createObject("./Images/UI/Battle/Item.png");
			locateObject(itemButton, battle3F_Scene, 610, buttonY_FIXED);
			scaleObject(itemButton, 0.65f);
			showObject(itemButton);

			avoidButton = createObject("./Images/UI/Battle/Avoid.png");
			locateObject(avoidButton, battle3F_Scene, 890, buttonY_FIXED);
			scaleObject(avoidButton, 0.65f);
			showObject(avoidButton);


			currentScene = battle3F_Scene;
			enterScene(battle3F_Scene);
						
		}

		// If current scene is tower and player can battle, then change a scene.
		if (currentScene == villageLeftScene) {
			if (750 <= playerX and playerX <= 1050) {
				rest();
			}

			else if (playerX > playerX_MAX - 100) {
				currentScene = villageScene;

				playerX = 50;
				locateObject(player, currentScene, playerX, playerY_FIXED);

				enterScene(currentScene);
			}
		}
		
		if (currentScene == villageScene) {
			if ((200 < playerX) && (playerX < 300)) {
				currentScene = storeScene;
				enterScene(currentScene);
				hideObject(player);

				for (int i = 0; i < 3; i++) {
					scaleObject(goldList[i], 0.8f);
					locateObject(goldList[i], storeScene, goldX[i], goldY);  // NEED TO REIVSE
				}

				showGold();
				showGold();
			}
			else if ((900 < playerX) && (playerX < 1000)) {
				currentScene = tower3F_Scene;
				enterScene(currentScene);
				playerX = 50;
				locateObject(player, currentScene, playerX, 200);
			}
		}
		if (currentScene == tower5F_Scene) {
			if (enemyTX_FIXED - 30 < playerX and playerX < enemyTX_FIXED + 100 and enemyTShown) {
				currentScene = battle5F_Scene;
				enterScene(currentScene);

				locateObject(playerHpBar, battle5F_Scene, playerHpBarX_FIXED, playerHpBarY_FIXED);
				showObject(playerHpBar);

				dx = 0;
				iconDx = 0;
				iconDy = 0;

				battle();
			}
			else if (playerX > playerX_MAX - 100 and not enemyTShown) {
				currentScene = tower6F_Scene;

				playerX = 50;
				locateObject(player, currentScene, playerX, playerY_FIXED);

				enterScene(currentScene);
			}
		}

		if (currentScene == tower3F_Scene) {

			if (playerX > playerX_MAX - 100 and not enemyShown) {
				currentScene = tower4F_Scene;
				enemyShown = true;

				playerX = 50;
				locateObject(player, currentScene, playerX, playerY_FIXED);

				enterScene(currentScene);
			}

		}
		

		// Else if current scene is battle, then player move to upper direction.
		else if (currentScene == battle5F_Scene) {
			iconDy = MOVE_SPEED;
			iconDy += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}
		else if (currentScene == tower6F_Scene) {
			if (puzzleTX_FIXED - 30 < playerX and playerX < puzzleTX_FIXED + 300 and puzzleTShown) {
				currentScene = game6F_Scene;
				enterScene(currentScene);

				dx = 0;

				puzzleInit();
			}
			else if (puzzleTX_FIXED - 30 < playerX and playerX < puzzleTX_FIXED + 300 and not puzzleTShown) {
				// currentScene = tower7F_Scene;

				// playerX = 50;
				// locateObject(player, currentScene, playerX, playerY_FIXED);

				// enterScene(currentScene);
			}
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

		if (currentScene == tower4F_Scene && playerX > playerX_MAX - 100 and not enemyShown) {
			currentScene = tower5F_Scene;

			playerX = 50;
			locateObject(player, currentScene, playerX, playerY_FIXED);

			enterScene(currentScene);
		}

		

		if (currentScene == game4F_Scene) {
			playerWingDy += (state == KeyState::KEYBOARD_PRESSED ? MOVE_SPEED : -MOVE_SPEED);
		}
		
	}

	else if (code == 85) {		// DOWN

		if (currentScene == battle3F_Scene or currentScene == battle5F_Scene) {
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

	// 59: Escape key
	else if (code == 59) {
		if (currentScene == game6F_Scene) {
			playerHp -= static_cast<int>(playerMaxHp * 0.1f);
			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {
					hideObject(puzzleList[y][x].obj);
				}
			}

			// Player's hp can be 0
			if (playerHp <= 0) {
				// do something
			}

			currentScene = tower6F_Scene;
			enterScene(tower6F_Scene);
		}


		if (currentScene == casinoScene) {
			enterScene(villageLeftScene);
			currentScene = villageLeftScene;


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
	currentScene = villageLeftScene;
	startGame(currentScene);

}