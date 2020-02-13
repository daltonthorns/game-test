#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <stdbool.h>
#include <ctype.h>
#include <malloc.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

//Daltons globals
int x = 0, y = 0;
int map[20][20];
FILE* fptr;
FILE* fptr2;
char path2[20] = "text.txt";
int room1clear = 0, room2clear = 0, room3clear = 0, room4clear = 0;
int room5clear = 0, room6clear = 0, room7clear = 0, room8clear = 0;
int honeydew = 0;

//CURRENTLY WORKING ON: MINIGAME IMPLEMENTATION

//Matt's globals
#define WON 0
#define LOSE 1
int Played = LOSE;
int cheated = 0;
int DiceSwitch = 0;
int Fair = 0;

/*******************************************************************************
 * Function Signatures
 ******************************************************************************/
int rollDice6(void);
int rollDice20(void);
int PlaytoWin(void);
int PlayFair(void);
int NoSwitch(void);
int SwitchSuccess(void);


/*******************************************************************************
 * Function definitions
 ******************************************************************************/

//Josh's globals
int Incorrect_Answer = 6;

//Andrew's globals
int player;

void delay(int number_of_seconds)
{
	// Converting time into milli_seconds 
	int milli_seconds = 25 * number_of_seconds;

	// String start time 
	clock_t start_time = clock();

	// looping till required time is not achieved 
	while (clock() < start_time + milli_seconds)
		;
}

//Room 1 mintaur encounter, simple multiple choice, 50/50 chance to win/lose
int room1()
{
	//Check if room is cleared, if so let user know and go to movement
	if (room1clear > 0)
	{
		//printf("\nYou are now in room %dx%d\n", x, y);
		//printf("This room has been cleared.\n");
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou are now in room %dx%d\n\nThis room has been cleared.\n", x, y);
		fflush(fptr2);
		scrolltext();
		movement();
	}
	char path[20] = "minotaur.txt";
	fptr = fopen(path, "r");
	fptr2 = fopen(path2, "w");
	char str1;

	fprintf(fptr2, "\nYou sneak your way into the dimly lit room.\n\nYou are now in room %dx%d.\n", x, y);
	fflush(fptr2);
	scrolltext();
	delay(10);

	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nYou begin to hear something approaching..\n");
	fflush(fptr2);
	scrolltext();
	PlaySound("D:\\music\\chains.wav", NULL, SND_ASYNC);
	delay(200);

	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nUh oh..\n");
	fflush(fptr2);
	scrolltext();
	PlaySound("D:\\music\\growl.wav", NULL, SND_ASYNC);
	delay(150);
	PlaySound("D:\\music\\battle.wav", NULL, SND_ASYNC);
	//delay(10);

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}
	delay(10);

	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\n\nA Minotaur suddenly appears! What will you do? \nA. Run\nB. Fight\nC. Hide\nD. Cower in fear\n");
	fflush(fptr2);
	fclose(fptr, fptr2);
	scrolltext();
	actions();
}

//Scrolling text effect, write to file then call function to print characters
//one by one until end of text file
int scrolltext()
{
	char path[20] = "text.txt";
	fptr2 = fopen(path, "r");
	char str1;

	str1 = fgetc(fptr2);
	while (str1 != EOF)
	{
		printf("%c", str1);
		_beep(1000, 1);
		delay(1);
		str1 = fgetc(fptr2);
	}
	fclose(fptr2);
}

//Room 2 encounter - elf
int room2()
{
	if (honeydew > 3)
	{
		endgame();
	}
	//Check if elf quest has been accepted
	else if (room2clear == 1)
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou are now in room %dx%d\n\nThe elf silently sits and waits for the honeydew you promised him.\n", x, y);
		fflush(fptr2);
		scrolltext();
		movement();
	}
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nYou find yourself in a dark corridor..\n\nYou are now in room %dx%d.\n\nA small elf is sitting in the corner of the room..\n\nWhat will you do?\nA.Talk\nB.Leave\n", x, y);
	fflush(fptr2);
	scrolltext();
	actions2();
}

//Room 3 encounter - dice
int room3()
{
	//Check if room is cleared, if so let user know and go to movement
	if (room3clear > 0)
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou are now in room %dx%d\n\nThis room has been cleared.\n", x, y);
		fflush(fptr2);
		scrolltext();
		movement();
	}
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nYou are now in room %dx%d.\n", x, y);
	fflush(fptr2);
	scrolltext();
	delay(10);
	PlaySound("D:\\music\\casino.wav", NULL, SND_ASYNC);
	delay(100);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nWhat the.. Wait a second.. Is this a casino? How is this even possible? I was just in the dungeon..\n\nTwo men eagerly approach you.\n");
	fflush(fptr2);
	scrolltext();
	delay(100);
	char path[20] = "diceguys.txt";
	fptr = fopen(path, "r");
	char str1;

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}
	delay(10);

	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\n\nHello, hello young fellow.. care to play a game of dice?\n");
	fflush(fptr2);
	scrolltext();
	delay(100);
	room3clear++;
	honeydew++;
	dicegame();
}

//Room 4 encounter - hangman
int room4()
{
	if (room4clear > 0)
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou are now in room %dx%d\n\nThis room has been cleared.\n", x, y);
		fflush(fptr2);
		scrolltext();
		movement();
	}
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nYou are now in room %dx%d\n\n", x, y);
	fflush(fptr2);
	scrolltext();
	delay(50);
	PlaySound("D:\\music\\hangman.wav", NULL, SND_ASYNC);
	delay(50);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "What the...\n\n");
	fflush(fptr2);
	scrolltext();
	delay(100);
	room4clear++;
	honeydew++;
	hangmangame();
}

//Room 5 encounter - rockpaperscissors
int room5()
{
	if (room5clear > 0)
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou are now in room %dx%d\n\nThis room has been cleared.\n", x, y);
		fflush(fptr2);
		scrolltext();
		movement();
	}
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nYou are now in room %dx%d\n\n", x, y);
	fflush(fptr2);
	scrolltext();
	delay(50);
	PlaySound("D:\\music\\rps.wav", NULL, SND_ASYNC);
	delay(50);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "What the...\n\n");
	fflush(fptr2);
	scrolltext();
	delay(100);
	room5clear++;
	honeydew++;
	rockpaperscissors();
}

//Final room encounter - escape game
int endgame()
{
	char path[20] = "elf.txt";
	char str1;
	fptr = fopen(path, "r");

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}
	PlaySound("D:\\music\\endgame.wav", NULL, SND_ASYNC);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\n\nYou hand the elf the honeydew.\n\nThank you so much adventurer, I can't thank you enough.\n\nCome now, we will escape this place together.\n\n"
		           "You follow the elf through the dungeon very closely as he leads you to the exit.\n\n");
	fflush(fptr2);
	scrolltext();
	delay(200);
	PlaySound("D:\\music\\elfsong.wav", NULL, SND_ASYNC);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "Go now adventurer, run through the town and escape!\n\nMe? I'll be fine, don't worry. I have my own plans.\n\nHowever, this is where we must depart. Goodbye.\n\n");
	fflush(fptr2);
	scrolltext();
	delay(200);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "You make your way through the town trying not to get caught as you regain your memory.\n\nYou remember your partner said when you escape he'll be at the inn.\n\n");
	fflush(fptr2);
	scrolltext();
	delay(200);
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "You manage to make it to the inn where your partner awaits.\n\n");
	fflush(fptr2);
	scrolltext();
	delay(100);
	escape();
}

//Room 2 action choice, help elf or not, talk = dialogue leave = you lose
int actions2()
{
	room2clear++;
	char choice[5];

repeat2:
	scanf("%s", choice);

	for (int i = 0; choice[i]; i++)
	{
		choice[i] = tolower(choice[i]);
	}

	if (!strcmp(choice, "a"))
	{
		char path[20] = "elf.txt";
		char str1;
		fptr = fopen(path, "r");

		str1 = fgetc(fptr);
		while (str1 != EOF)
		{
			printf("%c", str1);
			str1 = fgetc(fptr);
		}

		PlaySound("D:\\music\\elfsong.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\n\nHello young adventuruer.. I need some help..\nWill you please fetch me some honeydew? I seem to be dying..\nA. Yes\nB. No\n");
		fflush(fptr2);
		scrolltext();

	repeat1:
		scanf("%s", choice);

		for (int i = 0; choice[i]; i++)
		{
			choice[i] = tolower(choice[i]);
		}

		if (!strcmp(choice, "a"))
		{
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nThank you.. Thank you adventurer! Please, return the honeydew as soon as possible.\n");
			fflush(fptr2);
			scrolltext();
			delay(100);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			movement();
		}
		else if (!strcmp(choice, "b"))
		{
			PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou leave the elf to die.. Truly heartless..\n\nGame over.");
			fflush(fptr2);
			scrolltext();
			delay(300);
			return(0);
		}
		else
		{
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nInvalid Choice.\n");
			fflush(fptr2);
			scrolltext();
			goto repeat1;
		}
	}
	else if (!strcmp(choice, "b"))
	{
		PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou leave the elf to die.. Truly heartless..\n\nGame over.");
		fflush(fptr2);
		scrolltext();
		delay(300);
		return(0);
	}
	else
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nInvalid Choice.\n");
		fflush(fptr2);
		scrolltext();
		goto repeat2;
	}
}

int actions()
{
	char choice[5];

	scanf("%s", choice);

	for (int i = 0; choice[i]; i++)
	{
		choice[i] = tolower(choice[i]);
	}

	if (!strcmp(choice, "a"))
	{
		PlaySound("D:\\music\\run.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou try to run away..\n");
		fflush(fptr2);
		scrolltext();
		delay(200);
		PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou lived!\n");
		fflush(fptr2);
		scrolltext();
		delay(200);
		PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
		room1clear++;
		honeydew++;
		if (honeydew > 3)
		{
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
			fflush(fptr2);
			scrolltext();
			delay(50);
		}
		room1();
	}
	else if (!strcmp(choice, "b"))
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou try to fight the minotaur..\n");
		fflush(fptr2);
		scrolltext();
		delay(100);
		PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou died!\n");
		fflush(fptr2);
		scrolltext();
		delay(300);
		return(0);
	}
	else if (!strcmp(choice, "c"))
	{
		PlaySound("D:\\music\\run.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou try to hide..\n");
		fflush(fptr2);
		scrolltext();
		delay(200);
		PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou lived!\n");
		fflush(fptr2);
		scrolltext();
		delay(200);
		PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
		room1clear++;
		honeydew++;
		if (honeydew > 3)
		{
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
			fflush(fptr2);
			scrolltext();
			delay(50);
		}
		room1();
	}
	else if (!strcmp(choice, "d"))
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou cower in fear..\n");
		fflush(fptr2);
		scrolltext();
		delay(100);
		PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nYou died!\n");
		fflush(fptr2);
		scrolltext();
		delay(300);
		return(0);
	}
	else
	{
		printf("Invalid choice.\n");
		actions();
	}
}

int movement()
{
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nWhich room would you like to traverse? (N,E,S,W)\n");
	fflush(fptr2);
	scrolltext();

	char choice[5];

	scanf("%s", choice);

	for (int i = 0; choice[i]; i++)
	{
		choice[i] = tolower(choice[i]);
	}

	if (!strcmp(choice, "n") && y != 0)
	{
		y--;
		rooms();
	}
	else if (!strcmp(choice, "e") && x < 2)
	{
		if ((y == 2 && x == 0) || (y == 1 && x == 1))
		{
			goto invalidroom;
		}
		x++;
		rooms();
	}
	else if (!strcmp(choice, "w") && x != 0)
	{
		x--;
		rooms();
	}
	else if (!strcmp(choice, "s") && y < 2)
	{
		if ((y == 0 && x == 2) || (y == 1 && x == 1))
		{
			goto invalidroom;
		}
		y++;
		rooms();
	}
	else
	{
		invalidroom:
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nInvalid choice or you have reached the edge of the dungeon.\n");
		fflush(fptr2);
		scrolltext();
		movement();
	}
}

int rooms()
{
	if (x == 1 && y == 0)
	{
		room2();
	}
	else if (x == 1 && y == 1)
	{
		room1();
	}
	else if (x == 0 && y == 1)
	{
		room3();
	}
	else if (x == 2 && y == 0)
	{
		room4();
	}
	else if (x == 0 && y == 2)
	{
		room5();
	}
	else
	{
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nInvalid choice or you have reached the edge of the dungeon.\n");
		fflush(fptr2);
		scrolltext();
		movement();
	}
}

int main()
{
	PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);

	char path[20] = "title.txt";
	fptr = fopen(path, "r");
	char str1;

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}

	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nYou are a young man with dreams of adventure.. You begin your adventure "
		"in the depths of the dungeon\nwith no recollection of how you got there.\n"
		"\nYou are now in room %dx%d.\n", x, y);
	fflush(fptr2);
	scrolltext();
	//endgame();
	//return(0);
	movement();
}

//dice game
/*----------------------------------------------------------------------------*/
int rollDice20(void) {/*Gets a random number for a die 1-20, used in switch success*/
	return ((rand() % 20) + 1);
}

/*----------------------------------------------------------------------------*/
int rollDice6(void) {/*Gets a random number for a die 1-6*/
	return ((rand() % 6) + 1);
}

/*----------------------------------------------------------------------------*/
int PlaytoWin(void) {/*you have successfully switched to loaded dice*/
	int dice_1 = 5;
	int dice_2 = 6;
	int sum = dice_1 + dice_2;
	int result;
	fprintf(fptr2, "\nFirst roll coming out!!\n\n...\n\n");
	fflush(fptr2);
	scrolltext();
	delay(50);
	fgetc(stdin);
	sum = dice_1 + dice_2;
	printf("The roll is D1:%2d - D2:%2d - Sum:%2d\n", dice_1, dice_2, sum);
	result = WON;
	return result;
}

/*----------------------------------------------------------------------------*/
int PlayFair(void) {/*Play a fair dice game with standard craps rules*/
	int dice_1 = 0;
	int dice_2 = 0;
	int sum = 0;
	int result;
	int point = 0;
	time_t t;
	bool playForPoint = false;

	srand(time(&t)); // Initialize random seed
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nFirst roll coming out!!\n\n...\n\n");
	fflush(fptr2);
	scrolltext();
	delay(50);
	fgetc(stdin);
	dice_1 = rollDice6();
	dice_2 = rollDice6();
	sum = dice_1 + dice_2;
	printf("The roll is D1:%2d - D2:%2d - Sum:%2d\n", dice_1, dice_2, sum);

	switch (sum)
	{
	case 7:
	case 11:
		result = WON;
		break;
	case 2:
	case 3:
	case 12:
		result = LOSE;
		break;
	default:
		playForPoint = true;
		point = sum;
		printf("Playing for point: %d. Please hit [ENTER].\n", point);
		fgetc(stdin);
		break;
	}

	while (playForPoint)
	{
		dice_1 = rollDice6();
		dice_2 = rollDice6();
		sum = dice_1 + dice_2;
		printf("D1:%2d - D2:%2d - Sum:%2d\n", dice_1, dice_2, sum);
		if (sum == 7) {
			playForPoint = false;
			result = LOSE;
		}
		else if (sum == point) {
			playForPoint = false;
			result = WON;
		}
		else {
			printf("Please roll the dice again with [ENTER].\n");
			fgetc(stdin);
		}
	}

	return result;
}

/*----------------------------------------------------------------------------*/
int NoSwitch(void) {/*You decide not to switch dice, you will lose for sure the first 4 times you choose not to switch die*/
	int dice_1 = 6;
	int dice_2 = 6;
	int sum = dice_1 + dice_2;
	int result;
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\nFirst roll coming out!!\n\n...\n\n");
	fflush(fptr2);
	scrolltext();
	delay(50);
	fgetc(stdin);
	sum = dice_1 + dice_2;
	cheated = cheated + 1;
	printf("\nThe roll is D1:%2d - D2:%2d - Sum:%2d\n", dice_1, dice_2, sum);
	result = LOSE;
	return result;
}
/*----------------------------------------------------------------------------*/
int SwitchSuccess(void) {/*Play a fair dice game with standard craps rules*/
	time_t t;
	srand(time(&t)); // Initialize random seed
	int dice_1 = rollDice20();
	int result;

	if (Fair == 1)/*you have decided to switch to FAIR Dice, 85% chance of success*/
	{
		switch (dice_1)
		{
		case 1:
		case 2:
		case 3:
			result = LOSE;
			break;
		default:
			result = WON;
			break;
		}
	}
	else/*you have decided to switch to Loaded Dice 35% chance of success*/
	{
		switch (dice_1)
		{
		case 20:
		case 19:
		case 18:
		case 17:
		case 16:
		case 15:
		case 14:
			result = WON;
			break;
		default:
			result = LOSE;
			break;
		}
	}
	return result;
}
/*----------------------------------------------------------------------------*/

int dicegame(void) {
	if (Played == LOSE) {
		printf("\nYou are about to play dice with what look to be VERY shady fellows!!\n");
		printf("However, the dice look strangely similar to the two sets you have in your pack.\n");
		printf("\n");
		printf("One of your sets are FAIR dice, and you know that with these dice, win or lose, you weren't cheated.\n");
		printf("You further know that the dice are almost identical to the ones being used by the shady fellows\n");
		printf("so the chances of being caught switching to them is extremely LOW.\n");
		printf("\n");
		printf("Your second set are Loaded dice, and you know that with these dice you will win, but they are slightly\n");
		printf("different in size.  This means the chances of being caught switching to them is higher.\n");
		printf("\nWill you switch the dice?? (y/n)\n");
		char Decision_1 = getchar();
		while ((Decision_1 = getchar()) != '\n')
		switch (Decision_1)
		{
		case 'Y':
		case 'y':
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou will attempt to switch the dice.\n");
			fflush(fptr2);
			scrolltext();
			break;
		default:
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou will not attempt to switch the dice.\n");
			fflush(fptr2);
			scrolltext();
			int result = NoSwitch();
			switch (result)
			{
			case WON:
				delay(50);
				PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've won the game?! That shouldn't be poss-...  I mean well played sir..\n\nThe room slowly fades into a dimly lit hallway.. How strange..\n");
				fflush(fptr2);
				scrolltext();
				Played = WON;
				delay(200);
				PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
				fptr2 = fopen(path2, "w");
				if (honeydew > 3)
				{
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
					fflush(fptr2);
					scrolltext();
					delay(50);
				}
				movement();
				//break;
			case LOSE:
				delay(50);
				PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou lost the game. The men take all your belongings as the room slowly fades into a dimly lit hallway.\n");
				fflush(fptr2);
				scrolltext();
				delay(300);
				PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
				if (honeydew > 3)
				{
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
					fflush(fptr2);
					scrolltext();
					delay(50);
				}
				movement();
				//break;
			default:
				printf("Something went wrong in the program.\n");
				break;
			}

			if (result == LOSE) { return 0; }
		}
		fptr2 = fopen(path2, "w");
		fprintf(fptr2, "\nWill you try to switch to the FAIR dice?? (y/n)\n");
		fflush(fptr2);
		scrolltext();
		char Decision_2 = getchar();
		if (Decision_2 == '\n') {
			Decision_2 = getchar();
		}

		switch (Decision_2)
		{
		case 'Y':
		case 'y':
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou will attempt to switch to the FAIR dice.\n");
			fflush(fptr2);
			scrolltext();
			Fair = 1;
			int result1 = SwitchSuccess();
			switch (result1)
			{
			case WON:
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've switched the dice successfully!\n");
				fflush(fptr2);
				scrolltext();
				int result2 = PlayFair();

				switch (result2)
				{
				case WON:
					delay(50);
					PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou've won the game?! That shouldn't be poss-...  I mean well played sir..\n\nThe room slowly fades into a dimly lit hallway.. How strange..\n");
					fflush(fptr2);
					scrolltext();
					Played = WON;
					delay(200);
					PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
					if (honeydew > 3)
					{
						fptr2 = fopen(path2, "w");
						fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
						fflush(fptr2);
						scrolltext();
						delay(50);
					}
					movement();
					//break;
				case LOSE:
					delay(50);
					PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou lost the game. The men take all your belongings as the room slowly fades into a dimly lit hallway.\n");
					fflush(fptr2);
					scrolltext();
					delay(300);
					PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
					if (honeydew > 3)
					{
						fptr2 = fopen(path2, "w");
						fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
						fflush(fptr2);
						scrolltext();
						delay(50);
					}
					movement();
					//break;
				default:
					printf("Something went wrong in the program.\n");
					break;
				}
				return 0;
			case LOSE:
				delay(50);
				PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou are caught switching the dice. You lost the game. The men take all your belongings as the room slowly fades into a dimly lit hallway.\n\n");
				fflush(fptr2);
				scrolltext();
				delay(300);
				PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
				if (honeydew > 3)
				{
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
					fflush(fptr2);
					scrolltext();
					delay(50);
				}
				movement();
				//break;
			default:
				printf("Something went wrong in the program.\n");
				break;
			}
			if (result1 == LOSE) { return 0; }


		default:
			fptr2 = fopen(path2, "w");
			fprintf(fptr2, "\nYou will attempt to switch to the loaded dice.\n");
			fflush(fptr2);
			scrolltext();
			Fair = 0;
			int result3 = SwitchSuccess();
			switch (result3)
			{
			case WON:
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've switched the dice successfully!\n");
				fflush(fptr2);
				scrolltext();
				int result4 = PlaytoWin();
				switch (result4)
				{
				case WON:
					delay(50);
					PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou've won the game?! That shouldn't be poss-...  I mean well played sir..\n\nThe room slowly fades into a dimly lit hallway.. How strange..\n");
					fflush(fptr2);
					scrolltext();
					Played = WON;
					delay(200);
					PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
					if (honeydew > 3)
					{
						fptr2 = fopen(path2, "w");
						fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
						fflush(fptr2);
						scrolltext();
						delay(50);
					}
					movement();
					//break;
				case LOSE:
					delay(50);
					PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou lost the game. The men take all your belongings as the room slowly fades into a dimly lit hallway.\n");
					fflush(fptr2);
					scrolltext();
					delay(300);
					PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
					if (honeydew > 3)
					{
						fptr2 = fopen(path2, "w");
						fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
						fflush(fptr2);
						scrolltext();
						delay(50);
					}
					movement();
					//break;
				default:
					printf("Something went wrong in the program.\n");
					break;
				}
				return 0;
			case LOSE:
				delay(50);
				PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou are caught switching the dice. You lost the game. The men take all your belongings as the room slowly fades into a dimly lit hallway.\n\n");
				fflush(fptr2);
				scrolltext();
				delay(300);
				PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
				if (honeydew > 3)
				{
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
					fflush(fptr2);
					scrolltext();
					delay(50);
				}
				movement();
				//break;
			default:
				printf("Something went wrong in the program.\n");
				break;
			}
			return 0;
		}
	}
	return 0;
}

//hangman game
void Hangman_Visual(int);
int hangmangame(void)
{
	// Initialize variables and arrays for the rest of the program
	char Secret_Word[100] = "sand";
	char Temp_Word[100];
	char Output_Word[100];
	//int Incorrect_Answer = 6;                      //Number of Tries before failing
	int Correct_Answer = 0;                        //Number of Tries if correct letter is inputted.
	int counter = 0;
	int position = 0;
	int winner, length, i;
	char Alphabet_User;                           //Characters input by user

	system("cls");
	//printf("HIT [ENTER]");
	//getchar();
	length = strlen(Secret_Word);

	system("cls");

	char path[20] = "demon.txt";
	fptr = fopen(path, "r");
	char str1;

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}
	
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\n\nWelcome to the my Challenge! Guess the correct word or die trying.\nThe riddle is easy, I promise!"
				   "\nYou will get 6 chances to guess the correct word which completes the riddle.\nInputting a correct letter numerous times will not penalize you."
				   "\n\n\GOODLUCK YOU SAD FOOL! HAHAHAHA!\n\n...\n\n*Ahem* I mean.. Good luck adventurer.");
	fflush(fptr2);
	scrolltext();

	getchar();
	printf("\n\nPress [ENTER] to continue.");
	getchar();
	system("cls");

	//SHOWS THE ACTUAL HANGMAN POST
	printf("\n\t||===== ");
	printf("\n\t||    | ");
	printf("\n\t||      ");
	printf("\n\t||      ");
	printf("\n\t||      ");
	printf("\n\t||      ");
	printf("The word has %d letters.", length);  //Hint for the user playing

	//Function of the game from here down
	for (i = 0; i < length; i++)
	{
		Output_Word[i] = '_';
		Output_Word[length] = '\0';
	}

	for (i = 0; i < length; i++)
	{
		printf(" ");
		printf("%c", Output_Word[i]);
	}
	while (Incorrect_Answer != 0)
	{
		Correct_Answer = 0;
		printf("\n\nRiddle:\nI cover cities and destroy mountains,\nI make men blind, yet help them see.");
		printf("\n\nEnter the correct letters here: ");

		fflush(stdin);

		scanf("%c", &Alphabet_User);                      //Scans the number of places the user has used to input a letter. Fills space and leaves the rest open
		if (Alphabet_User < 'a' || Alphabet_User > 'z')
		{
			system("cls");
			printf("Invalid input. Try again! Your death draws near!");
			Correct_Answer = 2;
		}
		fflush(stdin);
		if (Correct_Answer != 2)       //If correct letter is inputted
		{
			for (counter = 0; counter < length; counter++)
			{
				if (Alphabet_User == Secret_Word[counter])
				{
					Correct_Answer = 1;
				}
			}
			if (Correct_Answer == 0)     //If incorrect letter is inputted
			{
				printf("\n\nYou only have %d chances left....", --Incorrect_Answer);     //If the incorrect letter is inputted 6 times, game over.
				//getchar();
				Hangman_Visual(Incorrect_Answer);
				//getchar();
			}
			else
			{
				for (counter = 0; counter < length; counter++)   //Counts the amout of letters left.
				{
					Correct_Answer = 0;
					if (Alphabet_User == Secret_Word[counter])
					{
						position = counter;
						Correct_Answer = 1;
					}
					if (Correct_Answer == 1)
					{
						for (i = 0; i < length; i++)
						{
							if (i == position)
							{
								Output_Word[i] = Alphabet_User;     //Output word will be inputted and equal to what the user inputs
							}
							else if (Output_Word[i] >= 'a' && Output_Word[i] <= 'z')
							{
								continue;
							}
							else
							{
								Output_Word[i] = '_';              //Underscores to fill in spaces of unknown letters
							}
						}
						Temp_Word[position] = Alphabet_User;
						Temp_Word[length] = '\0';
						winner = strcmp(Temp_Word, Secret_Word);   //Compare the temporary word to the secret word

						if (winner == 0)                           //Winner scenario
						{
							PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
							printf("\n\nCongratulations, you made it out alive!!!!");
							printf("\n\nThe Word was '%s'.\n", Secret_Word);
							//getchar();
							delay(200);
							PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
							if (honeydew > 3)
							{
								fptr2 = fopen(path2, "w");
								fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
								fflush(fptr2);
								scrolltext();
								delay(50);
							}
							movement();
						}
					}
				}
			}
		}


		printf("\n\n\t");
		for (i = 0; i < length; i++)
		{
			printf(" ");
			printf("%c", Output_Word[i]);                //Show the original Word With blanks
		}

		getchar();
	}

	//if the player can not guess the whole word in 5 trys
	if (Incorrect_Answer <= 0)                //If number of tries = 0 (The hang-man is complete)                    
	{
		printf("\n\n\t The Word was %s ", Secret_Word);
		printf("\n\n\t YOU DIED!!!\n\n");

	}
	//getchar();
	return 0;
}                                             //End of main functions of the game



void Hangman_Visual(int choice)
{
	//This function show the hangman after each wrong answer
	//For each wrong letter inputted, the hangman drawing will gain more and more pieces
	//Seperate Cases for each additional piece
	switch (choice)
	{

	case 0:
		system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/", '\\');
		printf("\n\t||    | ");
		printf("\n\t||   / %c", '\\');
		printf("\n\t||      ");
		printf("\n\nYou only have %d chances left....", Incorrect_Answer);
		break;
	case 1:
		system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/", '\\');
		printf("\n\t||    | ");
		printf("\n\t||     %c", '\\');
		printf("\n\t||      ");
		printf("\n\nYou only have %d chances left....", Incorrect_Answer);
		break;
	case 2:
		system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/", '\\');
		printf("\n\t||    | ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\nYou only have %d chances left....", Incorrect_Answer);
		break;
	case 3:
		system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO/", '\\');
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\nYou only have %d chances left....", Incorrect_Answer);
		break;
	case 4:
		system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||   %cO ", '\\');
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\nYou only have %d chances left....", Incorrect_Answer);
		break;
	case 5:
		system("cls");
		printf("\n\t||===== ");
		printf("\n\t||    | ");
		printf("\n\t||    O ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\t||      ");
		printf("\n\nYou only have %d chances left....", Incorrect_Answer);
		break;
	}
	return;
}

//escape game
int escape()
{
	/* This program prompts the user to use their inventory items to escape from persuers.
The persuers chase the player through the small town.
Use the smokebomb at a bust intersection to confuse them.
Get to highest building.
Use the Rope to reple down.
Use the fire crackers to spook animals to make them panic.
*/
	
	// print narritve
	// pursuers will begin at 0 distance.
	// the player will begin at 11 distance.
	// the player must reach a differnce of.
	
	char path[20] = "bar.txt";
	char str1;
	fptr = fopen(path, "r");

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}

	unsigned int pursuit, player, goal, visit, gcnt; //counter for the disance of each piece
	do
	{
		PlaySound("D:\\music\\escape.wav", NULL, SND_ASYNC);
		printf("\n\n\tYou have come to an inn to enjoy mug of ale with your shifty friend.\n\tLet's look over the map one more time. Dardemel gently unfurls the map."
			   "\n\tThe parchment is all but blank, except for the shimmering golden X right in the middle.\n\tYou notice that the X isn't mear paint, but it is ink and letters."
			   "\n\tThe X constructed of words from a differenet language you cannont comprehend.\n\tAll of the sudden, a comotion from town."
			   "\n\tThe Royal Guards have appeared, and they waving around wanted posters for you and Dardemel's head!\n");
		delay(300);
		pursuit = 0, gcnt = 0, visit = 0;
		player = 11;
		goal = 20;
		char str1[20];

		while (player != goal) {
			//printf for the procedure
			printf("\n\tChoose the right item in your inventory to go the fastest!");
			//while (player > pursuit) {
			unsigned int i = 4;
			// CONFUSE THE GUARDS WITH A SMOKE BOMB ////////////////////////////////////
			//printf task: SmokeBomb, Rope, FireCracker
			// which item in the inventory is best for the situation
			if (gcnt == 0) {
				//fptr = fopen(pathS, "r");
				printf("\n\tThe guards right on your heels! You are running through the market, pushing people out of your way."
					   "\n\tYou come to a fountain with many people gathered around.\n\tYou dance around them to look over your shoulder."
					   "\n\tThe guards are near.There're three ways to leave the fountain square.\n\tOne of which leads to the stables."
					   "\n\tYou can't let the guards know which way you're going, what can you possible use to blind them?\n");
				printf("\nBlanket, Smokebomb, Oil.\nType in the exact item you want to use: "); //choose an item
				scanf("%s", &str1); // item chosen will add of add to the disance. Correct item increment by 3. unusfull items increment by 1.
				if (!(strcmp(str1, "Smokebomb")))
				{
					player = player + 3;
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\n\tYes, faster faster!\n");
					fflush(fptr2);
					scrolltext();
					delay(100);
				}
				else {
					player = player + 1;
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\n\tNot fast enough, they're going to catch us, hurry!\n");
					fflush(fptr2);
					scrolltext();
					delay(100);
					
				}
				// CONFUSE THE GUARDS WITH A SMOKE BOMB ////////////////////////////////////

				gcnt++;
			}
			else if (gcnt == 1) {
				//fptr = fopen(pathR, "r");
				printf("\n\tThe guards are surrounding you!\n\tClimb up the tower to gain distance from them.\n\tFigure out a way down once all the guards have chased you up the tower.\n");
				printf("\nBelt, Knife, Rope\nType in the exact item you want to use: "); //choose an item
				scanf("%s", &str1); // item chosen will add of add to the disance. Correct item increment by 3. unusfull items increment by 1.
				if (!(strcmp(str1, "Rope")))
				{
					player = player + 3;
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\n\tYes, faster faster!\n");
					fflush(fptr2);
					scrolltext();
					delay(100);
				}
				else {
					player = player + 1;
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\n\tNot fast enough, they're going to catch us, hurry!\n");
					fflush(fptr2);
					scrolltext();
					delay(100);
				}
				gcnt++;
			}
			else if (gcnt == 2) {

				printf("\n\tYou've reached the stables!\n\tAll of the guards horses are tied up! Don't let the guards chase on horse back.\n\tFind a way to untie the horses and scare them off.\n");
				printf("\nFirecracker, Stalebread, Apples\nType in the exact item you want to use: "); //choose an item
				scanf("%s", &str1); // item chosen will add of add to the disance. Correct item increment by 3. unusfull items increment by 1.
				if (!(strcmp(str1, "Firecracker")))
				{
					player = player + 3;
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\n\tYes, faster faster!\n");
					fflush(fptr2);
					scrolltext();
					delay(100);
				}
				else {
					player = player + 1;
					fptr2 = fopen(path2, "w");
					fprintf(fptr2, "\n\tNot fast enough, they're going to catch us, hurry!\n");
					fflush(fptr2);
					scrolltext();
					delay(100);
				}
				gcnt++;
			}

			printf("\n%s\n", str1);
			if (player >= goal)
			{
				PlaySound("D:\\music\\endgame.wav", NULL, SND_ASYNC);
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\n\tYou have made a daring escape!\n\tThe royal guards have stumbled into a pile of barrels.\n\tYou and your compatriot reached some horses, and ride into the country."
							   "\n\tCongratulations, YOU WON!\n\n\n");
				fflush(fptr2);
				scrolltext();
				visit = visit + 1;
				delay(350);
				exit(0);
			}
			else if (player <= pursuit)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\n\tBlast! You have been seized by the guards!\n\tTry again to be quicker and escape!\n\n");
				fflush(fptr2);
				scrolltext();
				PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
				delay(350);
				PlaySound("D:\\music\\escape.wav", NULL, SND_ASYNC);
				player = 11, gcnt = 0, pursuit = 0;
			}
			pursuit = pursuit + 4; // The persuers will increment by 4 very time.
		}

	} while (visit != 0);
	printf("\n You have already visited this room. Venture elsewhere.");
}//End main.

int CHOOSER(PICKER) {
	while (1) {
		time_t t;
		srand(time(&t));
		PICKER = rand() % 3 + 0;
		RPS(PICKER);
		break;
	}
	return(0);
}
int RPS(PICKER) {
	char input[10];
	scanf("%s", input);

	if (PICKER == 0) {
		if ((strcmp(input, "rock")) == 0) {
			printf("Opponent chose ROCK you chose %s\nYou TIED, try again\n\n", input); CHOOSER(PICKER);
		}
		if ((strcmp(input, "paper")) == 0) {
			printf("Opponent chose ROCK you chose %s\nYou WIN\n", input);
			PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
			delay(200);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			if (honeydew > 3)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
				fflush(fptr2);
				scrolltext();
				delay(50);
			}
			movement();
			//return(0);
		}
		if ((strcmp(input, "scissors")) == 0) {
			printf("Opponent chose ROCK you chose %s\nYou LOSE\n", input);
			PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
			delay(350);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			if (honeydew > 3)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
				fflush(fptr2);
				scrolltext();
				delay(50);
			}
			movement();
			//return(0);
		}
	}
	if (PICKER == 1) {
		if ((strcmp(input, "rock")) == 0) {
			printf("Opponent chose PAPER you chose %s\nYou LOSE\n", input);
			PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
			delay(350);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			if (honeydew > 3)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
				fflush(fptr2);
				scrolltext();
				delay(50);
			}
			movement();
			//return(0);
		}
		if ((strcmp(input, "paper")) == 0) {
			printf("Opponent chose PAPER you chose %s\nYou TIED, try again\n\n", input);
			CHOOSER(PICKER);
		}
		if ((strcmp(input, "scissors")) == 0) {
			printf("Opponent chose PAPER you chose %s\nYou WIN\n", input);
			PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
			delay(200);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			if (honeydew > 3)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
				fflush(fptr2);
				scrolltext();
				delay(50);
			}
			movement();
			//return(0);
		}
	}
	if (PICKER == 2) {
		if ((strcmp(input, "rock")) == 0) {
			printf("Opponent chose SCISSORS you chose %s\nYou WIN\n", input);
			PlaySound("D:\\music\\victory.wav", NULL, SND_ASYNC);
			delay(200);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			if (honeydew > 3)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
				fflush(fptr2);
				scrolltext();
				delay(50);
			}
			movement();
		}
		if ((strcmp(input, "paper")) == 0) {
			printf("Opponent chose SCISSORS you chose %s\nYou LOSE\n", input);
			PlaySound("D:\\music\\gameover.wav", NULL, SND_ASYNC);
			delay(350);
			PlaySound("D:\\music\\music.wav", NULL, SND_ASYNC);
			if (honeydew > 3)
			{
				fptr2 = fopen(path2, "w");
				fprintf(fptr2, "\nYou've found the honeydew! You should bring it back to the elf now. (Room 0x1)\n");
				fflush(fptr2);
				scrolltext();
				delay(50);
			}
			movement();
			//return(0);
		}
		if ((strcmp(input, "scissors")) == 0) {
			printf("Opponent chose SCISSORS you chose %s\nYou TIED, try again\n\n", input);
			CHOOSER(PICKER);
		}
	}
	else {
		printf("\nNot a valid answer\n\n");
		CHOOSER(PICKER);
	}
	return(0);
}

int rockpaperscissors() {
	char path2[20] = "text.txt";
	FILE* fptr2;
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "You begin to hear something approaching..\n\nIt's not a monster thankfully..\n\nBut there does seem to be a strange fellow coming..\n\n");
	fflush(fptr2);
	scrolltext();
	delay(100);

	char path[20] = "rpsguy.txt";
	fptr = fopen(path, "r");
	char str1;

	str1 = fgetc(fptr);
	while (str1 != EOF)
	{
		printf("%c", str1);
		str1 = fgetc(fptr);
	}

	char input[10];
	fptr2 = fopen(path2, "w");
	fprintf(fptr2, "\n\nHello, hello buddy..\n\nI like me a mean game of rock paper scissors see?\n\nIt really gets my blood pumping..\n\nHeheheh..\n\n"
		"You are forced into a game of rock paper scissors with the strange fellow\n\nChoose (type) rock paper or scissors: ");
	fflush(fptr2);
	scrolltext();

	int PICKER = 0;
	CHOOSER(PICKER);
}