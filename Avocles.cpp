#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define lebarlayar 100
#define tinggilayar 26
#define lebarwindow 75
#define lebarmenu 30
#define GAP_SIZE 7
#define PIPE_DIF 45

using namespace std;
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipa[3];
int lubang[3];
int pipeFlag[3];
char burung[2][6] = { '/','-','-','o','\\',' ',
					'|','_','_','_',' ','>' };
int birdPos = 6;
int skor = 0;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void border(){ 
	
	for(int i = 0; i < lebarlayar; i++) {
		gotoxy(i, 0); 
		cout << "-";
		gotoxy(i, tinggilayar); 
		cout << "-";
	}
	for(int i = 0; i < tinggilayar; i++) {
		gotoxy(0, i); 
		cout << "|";
		gotoxy(lebarlayar,i); 
		cout << "|";
	}
	for(int i = 0; i < tinggilayar; i++) {
		gotoxy(lebarwindow,i); 
		cout << "|";
	}
}

void tampilPipa(int ind) {
	lubang[ind] = 3 + rand()%14; 
}
