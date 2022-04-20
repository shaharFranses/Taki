
//name: Shahar Franses
//id:208956557
#define _CRT_SECURE_NO_WARNINGS
#define MAX_NAME_LENGTH 20
#define NUM_OF_START_CARDS 4
#define numOfCardTYPES 14
#define HALFARRAY 7
#include <stdio.h>	
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>



struct Card {
	char type;
	char color;
};
typedef struct Card CARD;

struct CardStats {
	char type[MAX_NAME_LENGTH];
	int frequency;
};
typedef struct CardStats CARDSTATS;



struct Player {
	char name[MAX_NAME_LENGTH];
	CARD* cards;
	int numOfCards;
	int deckSize;
	
};
typedef struct Player  PLAYER;



int getNumOfPlayers();
void getPlayerName(PLAYER* player, int num);
void givehand(CARD* deck);
CARD givecard();
PLAYER* startGame(int* numofplayers, PLAYER* players, CARD* currentCard);
void printCard(CARD card);
bool runTurn(PLAYER* player, int* turn, int* direction, CARD* currentCard, int numOfPlayers, int* playerAction);
CARD* myRealloc(PLAYER* player, CARD* cardArr);
bool cardValidation(CARD playerChosenCard, CARD currentCard);
void removeCard(PLAYER* player, int cardIndex);
void taki(PLAYER* player, CARD* currentCard, int* turn, int* direction);
void changeColor(CARD* card);
int turnDecision(int turn, int direction, int numOfplayers, CARD card, int playerChoice);
void specialCard(CARD* currentCard, int* direction, int* turn, PLAYER* player);
void red();
void blue();
void green();
void yellow();
void printStats(CARDSTATS unordredArray[]);
void mergSort(CARDSTATS unordredArray[], int size);
CARDSTATS* merge(CARDSTATS firstArr[], int firstSize, CARDSTATS secondArr[], int secondSize);

CARDSTATS statsArray[numOfCardTYPES] = { {"1",0},{"2",0},{"3",0},{"4",0},{"5",0},{"6",0},{"7",0},{"8",0},{"9",0},{"+",0},{"STOP",0},{"<->",0},{"TAKI",0},{"COLOR",0} };

int main() {
	//variables declerations
	int numOfPlayers;
	int turn = 0;
	int direction = 1;
	CARD currentCard = { ' ',' ' };
	CARD* pcurrentcard = &currentCard;
	
	int playerChoice = 1;
	bool winner = 0;
	PLAYER* players = NULL;
	srand(time(NULL));
	players=startGame(&numOfPlayers,players,&currentCard);
	while (winner == 0) {
		winner = runTurn(&players[turn], &turn,&direction, pcurrentcard,numOfPlayers,&playerChoice);
		if (winner == 1) {
			printf("the winner is %s Congratulations!", players[turn].name);
		}
		turn = turnDecision(turn, direction, numOfPlayers, currentCard,playerChoice);
	}
	
	printStats(statsArray);
	
}

//initialization functions


//the function will initaaliz the game 
PLAYER* startGame(int* numofplayers,PLAYER* players,CARD* currentCard ) {
	printf("********wlecome to Taki game*******\n");
	int i;
	CARD startCard;
	*numofplayers = getNumOfPlayers();
	players = (PLAYER*)malloc(*numofplayers * sizeof(PLAYER));
	if (players == NULL) {
		exit(1);
	}
	getPlayerName(players, *numofplayers);
	for (i = 0; i < *numofplayers; i++) {
		givehand((players+i)->cards);
		(players + i)->numOfCards = 4;
		(players + i)->deckSize = 4;
	}
	startCard = givecard(statsArray);
	while (startCard.type-'9'> 9)
	{
		startCard = givecard(statsArray);
	}
	*currentCard = startCard;
	return players;
}
//the function will get the number of player 
int getNumOfPlayers() {
	int numOfPlayers = 0;
	printf("please enter the number of players:\n\n");
	scanf("%d", &numOfPlayers);
	return numOfPlayers;
}
//the function will get the name of each player and allocate an array for his cards
void getPlayerName(PLAYER* player, int num) {
	int i;
	for (i = 0; i < num; i++){
		printf("please enter the first  name of player #%d\n", i + 1);
		scanf("%s", (player + i)->name);
			(player+i)->cards = (CARD*)malloc(NUM_OF_START_CARDS * sizeof(CARD));
			
	}
}
//the function will give the player is first hand
void givehand(CARD* deck) {
	int i;
	for (i = 0; i < NUM_OF_START_CARDS; i++) {
		deck[i]=givecard(statsArray);


	}
}
//the function will give a card
CARD givecard() {
	int cardtype = rand() % 14;
	int cardcolortype = rand() % 4;
	char cardsymbol = ' ';
	char cardColor = ' ';
	switch (cardtype)
	{
	case 0:
		cardsymbol = '1';
		statsArray[0].frequency++;
	break;
	case 1:
		cardsymbol = '2';
		statsArray[1].frequency++;
		break;
	case 2:
		cardsymbol = '3';
		statsArray[2].frequency++;
		break;
	case 3:
		cardsymbol = '4';
		statsArray[3].frequency++;
		break;
	case 4:
		cardsymbol = '5';
		statsArray[4].frequency++;
		break;
	case 5:
		cardsymbol = '6';
		statsArray[5].frequency++;
		break;
	case 6:
		cardsymbol = '7';
		statsArray[6].frequency++;
		break;
	case 7:
		cardsymbol = '8';
		statsArray[7].frequency++;
		break;
	case 8:
		cardsymbol = '9';
		statsArray[8].frequency++;
		break;
	case 9:
		//PLUS type
		cardsymbol = 'P';
		statsArray[9].frequency++;
		break;
	case 10:
		//STOP type
		cardsymbol = 'S';
		statsArray[10].frequency++;
		break;
	case 11:
		//Change direction type
		cardsymbol = 'D';
		statsArray[11].frequency++;
		break;
	case 12:
		//Taki type
		cardsymbol = 'T';
		statsArray[12].frequency++;
		break;
	case 13:
		//Color change  type
		cardsymbol = 'C';
		statsArray[13].frequency++;
		break;
	}
	if (cardtype < 13) {
		switch (cardcolortype) {

		case 0:
			//yellow color
			cardColor = 'Y';
			break;
		case 1:
			//Red color **yalla hapoel!**
			cardColor = 'R';
			break;
		case 2:
			//Blue color
			cardColor = 'B';
			break;
		case 3:
			//Green color
			cardColor = 'G';
			break;
		default:
			cardColor = ' ';
			break;
		}
	}
	 CARD card;
	card.color = cardColor;
	card.type = cardsymbol;
	return card;
}


//***gameplay functions*****
//will run each turn and check for winner at ther end of it
//the function will triigger basesd on the player action-taking card/putting card on the top
bool runTurn(PLAYER* player, int* turn,int * direction, CARD* currentCard, int numOfPlayers,int * playerAction) {
	int j;
	int playerChoice;
	bool turnEnd = 0;
	printf("Upper card:\n");
	printCard(*currentCard);
	printf("%s's turn:\n", (player)->name);
		for (j = 0; j < player->numOfCards; j++) {
			printCard(player->cards[j]);
		}
		while (turnEnd==0) {
			printf("Please enter 0 if you want to take a card from the deck\n");
			printf("or 1-%d if you want to put one of your cards in the middle:", player->numOfCards);
			scanf("%d", &playerChoice);
			if (playerChoice > player->numOfCards)
			{
				printf("Invalid card! Try again.");
				turnEnd = 0;
			}
			else if (playerChoice == 0) {	
				player->numOfCards++;
				if (player->deckSize < player->numOfCards)
				{
					player->cards=myRealloc(player, player->cards);
				}
				player->cards[player->numOfCards-1]=givecard(statsArray);
				
				turnEnd = 1;
			}
			else {
				turnEnd = cardValidation(player->cards[playerChoice-1], *currentCard); 
				if (turnEnd == 1) {
					*currentCard = player->cards[playerChoice-1];
					removeCard(player, playerChoice);
			

				}
				else {
					printf("Invalid card! Try again.\n");
				}

			}
		
		}
		//special occasion and edge cases

		//cheks if player put stop and number of players is 2
		if (numOfPlayers == 2 && currentCard->type == 'S' && playerChoice != 0) {
			player->numOfCards++;
			if (player->deckSize < player->numOfCards)
			{
				player->cards = myRealloc(player, player->cards);
			}
			player->cards[player->numOfCards - 1] = givecard(statsArray);
		}

		//checks if a special card was played and
		if ((currentCard->type - '9' )> 9 && playerChoice!=0)
		{
			specialCard(currentCard, direction, turn,player);
		}
		//check if the player is the winner that is last card wasnt plus
		 if (player->numOfCards == 0 ) {
			 if (currentCard->type == 'P') {
				 player->cards[0] = givecard(statsArray);
				 player->numOfCards++;
				 *playerAction = playerChoice;
				 return 0;
			 }
			 else {
				 *playerAction = playerChoice;
				 return 1;
			 }
		 }
		 else {
			 *playerAction = playerChoice;
			 return 0;
		 }
}
//the function will validate that it is legel to put the chosen card on top of the last one 
bool cardValidation(CARD playerChosenCard, CARD currentCard) {
	if (playerChosenCard.type == 'C') {
		return 1;
	}
	
	else if (playerChosenCard.color == currentCard.color || playerChosenCard.type==currentCard.type) {
		return 1;
	}
	else  {
		return 0;
	}

}
//the function will remove the card fron the players deck
void removeCard(PLAYER* player, int cardIndex) {
	player->cards[cardIndex-1] = player->cards[(player->numOfCards)-1];
	player->numOfCards -= 1;
}
//the function will trigger once a player put taki card on top,wil act according to the rules of taki
void taki(PLAYER* player,CARD* currentCard, int* turn, int* direction) {
	int i;
	int playerChoice;
	bool takiClose = 0;
	while (takiClose == 0) {
		printf("Upper card:\n");
		printCard(*currentCard);
		printf("%s's turn:\n",player->name);
		for (i = 0; i < player->numOfCards; i++) {
			printCard(player->cards[i]);
		}
		printf("Please enter 0 if you want to take a card from the deck\n");
		printf("or 1-%d if you want to put one of your cards in the middle:", player->numOfCards);
		scanf("%d", &playerChoice);
		if (playerChoice > player->numOfCards )
		{
			printf("Invalid card! Try again.");
		
		}
		if(currentCard->color != player->cards[playerChoice - 1].color && playerChoice!=0){
			printf("Invalid card! Try again.");
		}
		
		else if (currentCard->color == player->cards[playerChoice-1].color) {
			*currentCard = player->cards[playerChoice-1];
			removeCard(player,playerChoice);
			if (player->numOfCards==0 && currentCard->type!='P'&& currentCard->type != 'S'){
				takiClose = 1;
			}
		}
		else if (player->cards[playerChoice-1].type == 'C')
		{
			takiClose = 1;
		}
		else if (playerChoice == 0) {
			takiClose = 1;
		}


	}

	//check if player last card in the taki was special if it does acts according to it
	switch (currentCard->type)
	{
		//PLUS type
	case  'P':
		*turn -= 1;
		if (player->numOfCards == 0) {
			player->numOfCards++;
			player->cards[0] = givecard(statsArray);
		}
		break;

		//STOP type
	case  'S':
		*turn += 1;
		if (player->numOfCards == 0) {
			player->numOfCards++;
			player->cards[0] = givecard(statsArray);
		}
		break;

		//Change direction type
	case  'D':
		*direction =*direction  * -1;
		break;

		//Color change  type
	case  'C':
		//changeColor();
		break;
	default:
		break;
	}

}
//the function will trigger once a player put change color card on top,wil act according to the rules of change color
void changeColor(CARD* card) {
	int playerChoice;
	bool chosenRight = 0;
	while (chosenRight == 0) {
		printf("Please enter your color choice:\n");
		printf("1 - Yellow\n");
		printf("2 - Red\n");
		printf("3 - Blue\n");
		printf("4 - Green\n");
		scanf("%d", &playerChoice);
		if (playerChoice > 4 || playerChoice < 1) {
			printf("Invalid choice! Try again.");
		}
		else {
			chosenRight = 1;
			switch (playerChoice)
			{
			case 1:
				card->color = 'Y';
			
				break;
			case 2:
				card->color = 'R';
				break;
			case 3:
				card->color = 'B';
				break;
			case 4:
				card->color = 'G';
				break;
			default:
				break;
			}
		
		}

	}
}
//the function will determine whos next turn is
 int turnDecision(int turn,int direction,int numOfplayers,CARD card,int playerChoice) {
	 int  playerTurn = 0;

	 //move turn in the direction of game
		 if(direction==1)
		 { 
			 turn += 1;
		 playerTurn = turn;
		 }
		 else {
			 turn -= 1;
			 playerTurn = turn ;
		 }
		

		 //checks if thr round has ende and initaliazing a new one 
		 //if the last player of the round stopped the first player of the round:(round is + directions)
		 if ((turn - numOfplayers) >= 1) {
			 playerTurn = 1;
		 }
		 //if the last p[layer of the round has benn stopped
		 else if (turn == numOfplayers) {
			 playerTurn = 0;
		 }


		 if (turn == -1) {
			 playerTurn = numOfplayers - 1;
		 }
		 if (turn==-2){
			 playerTurn = numOfplayers - 2;
		}
	
	 return playerTurn;
}
 //the function will triger once a  player put a card that is not a number
 void specialCard(CARD* currentCard, int* direction, int* turn,PLAYER* player) {

	 if (*direction == 1) {
		 switch (currentCard->type)
		 {
			 //PLUS type
		 case  'P':
			 *turn -= 1;
			 break;

			 //STOP type
		 case  'S':
			 *turn += 1;
			 break;

			 //Change direction type
		 case  'D':
			 *direction *= -1;
			 break;

			 //Taki type
		 case 'T':
			 taki(player, currentCard, turn, direction);
			 break;

			 //Color change  type
		 case  'C':
			 changeColor(currentCard);
			 break;
		 default:
			 break;
		 }
	 }
	 else if (*direction == -1) {
		 switch (currentCard->type)
		 {
			 //PLUS type
		 case  'P':
			 *turn += 1;
			 break;

			 //STOP type
		 case  'S':
			 *turn -= 1;
			 break;

			 //Change direction type
		 case  'D':
			 *direction *= -1;
			 break;

			 //Taki type
		 case 'T':
			 taki(player, currentCard, turn, direction);
			 break;

			 //Color change  type
		 case  'C':
			 changeColor(currentCard);
			 break;
		 default:
			 break;
		 }
	 }

 }

 //***printing functions***
  
 //change color to red
void red() {
	printf("\033[0;31m");
}
//change color to blue
void blue() {
	printf("\033[0;34m");
}
//change color to yellow
void yellow() {
	printf("\033[0;33m");
}
//change color to green
void green () {
	printf("\033[0;32m");
}
//the function will print a given card
void printCard(CARD card) {
	char color = card.color;
	char cardType = card.type;
	switch (color)
	{
	case 'Y':
		yellow();
		break;
	case 'B':
		blue();
		break;
	case 'R':
		red();
		break;
	case 'G':
		green();
		break;

	default:
		break;
	};
	if (cardType - '9' <= 9) {
		printf("*********\n");
		printf("*       *\n");
		printf("*   %c   *\n", cardType);
		printf("*   %c   *\n", color);
		printf("*       *\n");
		printf("*********\n");
	}
	else {
		switch (cardType) {
		case 'P':
			printf("*********\n");
			printf("*       *\n");
			printf("*   +   *\n");
			printf("*   %c   *\n", color);
			printf("*       *\n");
			printf("*********\n");
			break;
		case  'S':
			printf("*********\n");
			printf("*       *\n");
			printf("* STOP  *\n");
			printf("*   %c   *\n", color);
			printf("*       *\n");
			printf("*********\n");
			break;
		case  'D':
			printf("*********\n");
			printf("*       *\n");
			printf("*  <->  *\n");
			printf("*   %c   *\n", color);
			printf("*       *\n");
			printf("*********\n");
			break;
		case 'T':
			printf("*********\n");
			printf("*       *\n");
			printf("* TAKI  *\n");
			printf("*   %c   *\n", color);
			printf("*       *\n");
			printf("*********\n");
			break;
		case 'C':
			printf("*********\n");
			printf("*       *\n");
			printf("* COLOR *\n");
			printf("*   %c   *\n", color);
			printf("*       *\n");
			printf("*********\n");
			break;
		}

	}
	printf("\033[0m");
}

//***allocations and statistics***

//the function 
CARD* myRealloc (PLAYER* player,CARD* cardArr) {
	int i;
	CARD* temp=(CARD*)malloc(player->numOfCards  * sizeof(CARD));
	if (temp == NULL) {
		exit(1);
	}
	for (i = 0; i < player->numOfCards; i++) {
		temp[i] = player->cards[i];
	}
	free(player->cards);
		player->cards = (CARD*)malloc(player->deckSize * 2 * sizeof(CARD));
		if (player->cards == NULL) {
			exit(1);
		}
	
	for (i = 0; i < player->numOfCards; i++) {
		player->cards[i] = temp[i];
	}
	free(temp);
	player->deckSize *= 2;
	
	return player->cards;
}
void printStats(CARDSTATS unordredArray[]) {
	int i;
	mergSort(unordredArray, numOfCardTYPES);
	printf("****** Game Statistics ******\n");
	printf("_____________________\n");
	for (i = numOfCardTYPES - 1; i >= 0; i--) {
		printf(" %-5s|  %-5d \n", unordredArray[i].type, unordredArray[i].frequency);
	}

}
void mergSort(CARDSTATS unordredArray[], int size) {
	int i;
	CARDSTATS* temp = NULL;
	if (size <= 1)
	{
		return;
	}
	mergSort(unordredArray, size / 2);
	mergSort(unordredArray + size / 2, size - size / 2);
	temp = merge(unordredArray, size / 2, unordredArray + (size / 2), size - size / 2);
	if (temp == NULL) {
		exit(1);

	}
	else {
		for (i = 0; i < size; i++) {
			unordredArray[i] = temp[i];
		}

	}

	free(temp);
}
CARDSTATS* merge(CARDSTATS firstArr[], int firstSize, CARDSTATS secondArr[], int secondSize) {
	int firstArrayIndex = 0;
	int secondArrayIndex = 0;
	int orderedArrayIndex = 0;
	CARDSTATS* orderedArray = (CARDSTATS*)malloc((firstSize + secondSize) * sizeof(CARDSTATS));
	if (orderedArray == NULL) {
		exit(1);
	}

	while ((firstArrayIndex < firstSize) && (secondArrayIndex < secondSize)) {
		if (firstArr[firstArrayIndex].frequency <= secondArr[secondArrayIndex].frequency) {
			orderedArray[orderedArrayIndex] = firstArr[firstArrayIndex];
			firstArrayIndex++;
		}
		else {
			orderedArray[orderedArrayIndex] = secondArr[secondArrayIndex];
			secondArrayIndex++;
		}
		orderedArrayIndex++;
	}

	while (firstArrayIndex < firstSize) {
		orderedArray[orderedArrayIndex] = firstArr[firstArrayIndex];
		firstArrayIndex++;
		orderedArrayIndex++;
	}
	while (secondArrayIndex < secondSize) {
		orderedArray[orderedArrayIndex] = secondArr[secondArrayIndex];
		secondArrayIndex++;
		orderedArrayIndex++;
	}
	return orderedArray;
}