#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#define endl printf("\n");
#define forfor(X) for(int i = 0;i < X;i++)for(int j=0;j < X;j++)
#define fore(X) for(int i = 0;i < X;i++)

char cPlayer = 'O';
char cEmpty = ' ';
char cBlock = '#';
char cFruit = '*';
bool wall = true;


typedef struct point{
	int cx;
	int cy;
	bool visited;
	char data;
}point;

typedef struct star{
	int x;
	int y;
}Star;

enum key{up,down,left,right,enter,esc};
enum option{aiplay,selfplay,settings,quit};

point map[5][10];
int X;
int Y;
Star star; 

void init_map(int maxX, int maxY){
	char temp;
	FILE *fptr;
	char filedir[200];
	printf("Enter file directory: ");
	scanf("%s" , filedir);
	fptr = fopen(filedir,"r");
	while(fptr == NULL)
	{
		printf("Enter file directory: ");
		scanf("%s" , filedir);
		fptr = fopen(filedir,"r");
	}
	for(int i = 0;i < maxX;i++)
	for(int j = 0;j < maxY;j++)
	{
		while ((temp = getc(fptr)) != EOF)
		{
			if(temp == '0')
			{
				map[i][j].data=cEmpty;
				X = i;
				Y = j;
				break;
			}
			else if(temp == '1')
			{
				map[i][j].data= cEmpty;
				break;
			}
			else if(temp == '#')
			{
				map[i][j].data= cBlock;
				break;
			}
			else if(temp == '*')
			{
				map[i][j].data= cFruit;
				break;
			}
			else continue;
		}
		
		map[i][j].cx = -1;
		map[i][j].cy = -1;
		map[i][j].visited = false;
	}
	fclose(fptr);
}

void printMap(int x , int y){
	fore(y)printf("_");printf("__\n");
	for(int i = 0;i < x;i++)
	{
		printf("|");
		for(int j = 0;j < y;j++)
		{
			if(i == X && j == Y)printf("%c" , cPlayer);
			else
			printf("%c" , map[i][j].data);
			
		}
		printf("|");
		endl
	}
	printf("|");fore(y)printf("_");printf("|");
	endl
}



void findStar(int maxX,int maxY){
	for(int i = 0;i < maxX;i++)
	for(int j = 0;j < maxY;j++)
	{
		if(map[i][j].data == cFruit)
		{
			star.x = i;
			star.y = j;
			return;
		}
	}
	
	star.x = -1; //No Star?
	star.y = -1;
}


bool checkEnd(int maxX,int maxY){
	if(map[X][Y].data==cFruit)
		{
			map[X][Y].data= cEmpty;
			findStar(maxX,maxY);
			if(star.x == -1) return true;

		}
		return false;
}

int getKey(){
	int ch1, ch2;
	ch1 = getch();
	if(ch1 == 13)return enter;
	if(ch1 == 27)return esc;
	ch2 = 0;
	if (ch1 == 0xE0) {
		ch2 = getch();
		switch(ch2)
		{
			case 72: return up;
			case 80: return down;
			case 75: return left;
			case 77: return right;
			default:
			return getKey();
		};
	}
	else
	{
		return getKey();
	}
}



void gotoxy(int eex, int eey)
{
  COORD coord;
  coord.X = eex;
  coord.Y = eey;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


int main(){
	while(1)
	{
			init_map(5,10);
			system("@cls||clear");
			printMap(5,10);
			while(1)
			{
				if(checkEnd(5,10)) break;
				int key = getKey();
				if(key == up)
				{
					if(X == 0 && !wall && map[4][Y].data != cBlock)
						X = 4;
					else if(X != 0 && map[X-1][Y].data != cBlock) 
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						X--;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == down)
				{
					if(X == 4 && !wall && map[0][Y].data != cBlock)
						X = 0;
					else if(X != 4 && map[X+1][Y].data != cBlock) 
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						X++;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == right)
				{
					if(Y == 9 && !wall  && map[X][0].data != cBlock)
						Y = 0;
					else if(Y != 9 && map[X][Y+1].data != cBlock) 
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						Y++;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == left)
				{
					if(Y == 0 && !wall && map[X][9].data != cBlock)
						Y = 9;
					else if(Y != 0 && map[X][Y-1].data != cBlock)
					{
						gotoxy(Y+1,X+1);
						printf("%c" , map[X][Y].data);
						Y--;
						gotoxy(Y+1,X+1);
						printf("%c\b" , cPlayer);
					}
				}
				if(key == esc)
				{
					break;
				}
				
			}
		}
	}
	
