/*Snake Game In C Language By Hardik */
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int ts=500; // target Score

void Instructions()
{
	char key;
	start:
	clrscr();
	printf("Read The Instruction Before Play The Game.\n");
	printf("Game Controls.\n");
	printf("Movement W,A,S,D or w,a,s,d or Use Arrow Keys.\n");
	printf("Press X to Exit.\n");
	printf("Press P to Pause and Resume.\n");
	printf("Press R to Restart Game.\n");
	printf("Press Q to speed up snake.\n");
	printf("Press E to speed down snake.\n");
	printf("Hope You Enjoy The Game.\n");
	printf("Created By Hardik Mandiya.\n\n\n");
	printf("Press P to Play.   OR\nPress T to set Target Score.\n");
	key = getch();
	if(key == 'T' || key == 't')
	{
		printf("Target Score is 500 by Default.\nEnter Target Score(0-1000) : ");
		scanf("%i",&ts);
	}
	else if(key =='X' || key == 'x')
	{
		exit(0);
	}
	else if(!(key == 'P' || key == 'p'))
		goto start;

}

void main()
{
	// variables Used in program.
	int snkx[200],snky[200],i,restart=1,sz,d,fx,fy,score,speed=1,snkc=14,fc=3,tar_Score=ts;
	char key;
	//you can change player and foods ascii value from here.
	char player=2,food=4;
	clrscr();
	_setcursortype(_NOCURSOR);
	textcolor(WHITE);
	while(1)
	{
		if(restart)
		{
			Instructions();
			sz = 5;
			for(i=0;i<=sz;i++)
			snkx[i] = 40+i*2;
			for(i=0;i<=sz;i++)
			snky[i] = 9;
			d = LEFT;
			restart = 0;
			tar_Score = ts;
			window(0,0,78,24);
			randomize();
			fx = random(70)+6;
			fy = random(16)+3;
			if(fx%2==1)fx+=1;
			if(fy%2==1)fy+=1;
			score=0;
		}

		//print score And speed
		gotoxy(0,0);
		printf("Score : %i  |  Target : %i   |  Speed : %i",score,tar_Score,speed);

		//print food
		textcolor(fc);
		gotoxy(fx,fy);
		cprintf("%c",food);
		textcolor(WHITE);

		//print Snake
		for(i=0;i<sz;i++)
		{
			gotoxy(snkx[i],snky[i]);
			textcolor(snkc);
			cprintf("%c",player);
			textcolor(15);
		}

		//direction selection for snake movement
		switch(d)
		{
			case RIGHT :snkx[0]+=2;	break;
			case LEFT  :snkx[0]-=2;	break;
			case UP :snky[0]-=1;break;
			case DOWN  :snky[0]+=1;	break;
		}

		//after moving snake head move snake body.
		for(i=sz;i>0;i--)
		{
			snkx[i] = snkx[i-1];
			snky[i] = snky[i-1];
		}

		//score increament and genrate next food
		if(snkx[0] == fx && snky[0] == fy)
		{
			fx = random(70)+6;
			fy = random(16)+3;
			snkc = fc;
			fc = random(14)+1;
			if(fx%2==1)fx+=1;
			if(fy%2==1)fy+=1;
			sz++;
			score+=10;
		}

		//change diraction of snake And other functionalities
		if(kbhit())
		{
			key = getch();
			if(key == 'x'||key == 'X')
			exit(0);

			if((key == 'w'||key == 'W' || key == 72) && d != DOWN)
				d = UP;
			if((key == 'a' || key == 'A'|| key == 75) && d != RIGHT)
				d = LEFT;
			if((key == 'd' || key == 'D' || key == 77) && d != LEFT)
				d = RIGHT;
			if((key == 's' || key == 'S' || key == 80) && d != UP)
				d = DOWN;
			if(key == 'q'|| key == 'Q')
			{
				if(speed<10 )
				{
					speed++;
				}
			}
			if(key == 'e'|| key == 'E')
			{
				if(speed>1)
				{
					speed--;
				}
			}
			if(key == 'P' || key == 'p')
			{
				gamePause:
				gotoxy(25,12);
				printf("Game Paused...Press P to Resume.");
				key = getch();
				if(!(key == 'P' ||key == 'p'))
				{
					goto gamePause;
				}
			}
			if(key == 'R' || key == 'r')
			restart = 1;
		}

		//move Snake Through the screen.
		if(snkx[0]>80)
			snkx[0]=2;
		if(snkx[0]<1)
			snkx[0] = 78;
		if(snky[0]>24)
			snky[0] = 2;
		if(snky[0]<1)
			snky[0]=23;

		//speed maintain
		delay(20*(10-speed));
		clrscr();
		if(score == tar_Score)
		{
			gotoxy(30,12);
			printf("You Won The Game.");
			getch();
			restart = 1;
		}
	}
}//main