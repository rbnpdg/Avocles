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
char burung[2][6] = { '/','-','-','o','\\',' ','|','_','_','_',' ','>' };
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
void buatPipa(int ind){
	if( pipeFlag[ind] == true ){
		for(int i = 0; i < lubang[ind]; i++){ 
			gotoxy(lebarwindow - pipa[ind],i + 1); 
			cout << "==="; 
		}
		for(int i = lubang[ind] + GAP_SIZE; i < tinggilayar - 1; i++){ 
			gotoxy(lebarwindow - pipa[ind],i + 1); 
			cout<<"===";
		}
	} 
}

void hapusPipa(int ind){
	if( pipeFlag[ind] == true ){
		for(int i = 0; i < lubang[ind]; i++){ 
			gotoxy(lebarwindow - pipa[ind], i + 1); 
			cout << "   "; 
		}
		for(int i = lubang[ind] + GAP_SIZE; i < tinggilayar - 1; i++){ 
			gotoxy(lebarwindow - pipa[ind], i + 1); 
			cout << "   "; 
		}
	}
}

void tampilBurung(){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 6; j++){
			gotoxy(j + 2,i + birdPos);
			cout << burung[i][j];
		}
	}
}
void hapusBurung(){
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 6; j++){
			gotoxy(j + 2, i + birdPos); 
			cout << " ";
		}
	}
}

int tabrakan(){
	if( pipa[0] >= 61  ){
		if(birdPos < lubang[0] || birdPos > lubang[0] + GAP_SIZE){
			return 1;
		}
	}
	return 0;
}

void gameover() {
	system("cls");
	cout << endl;
	cout << "\t\t__________________________" << endl;
	cout << "\t\t|        Game Over       |" << endl;
	cout << "\t\t|________________________|" << endl << endl;
	cout << "\t\tPress any key to go back to menu.";
	getch();
}
void updateskor(){
	gotoxy(lebarwindow, 7);
	cout << "Skor : " << skor << endl;
}

void mulai(){
	
	birdPos = 6;
	skor = 0;
	pipeFlag[0] = 1; 
	pipeFlag[1] = 0;
	pipa[0] = pipa[1] = 4;
	
	system("cls"); 
	border();
	tampilPipa(0);
	updateskor();
	
	gotoxy(lebarwindow, 2);
	cout<<"Avocles!";

	gotoxy(lebarwindow, 13);
	cout<<"Tekan spasi untuk lompat";
	
	gotoxy(10, 5);
	cout<<"Tekan sembarang tombol untuk mulai";
	getch();
	gotoxy(10, 5);
	cout<<"                      ";
	
	while(1){
		 
		if(kbhit()){
			char ch = getch();
			if(ch == 32){
				if( birdPos > 3 )
					birdPos -= 3;
			} 
			if(ch == 27){
				break;
			}
		}
		
		tampilBurung();
		buatPipa(0);
		buatPipa(1);
		
		if( tabrakan() == 1 ){
			gameover();
			return;
		}
		Sleep(100);
		hapusBurung();
		hapusPipa(0);
		hapusPipa(1);
		birdPos += 1;
		
		if( birdPos > tinggilayar - 2 ){
			gameover();
			return;
		}
		
		if( pipeFlag[0] == 1 )
			pipa[0] += 2;
		
		if( pipeFlag[1] == 1 )
			pipa[1] += 2;
		
		if( pipa[0] >= 40 && pipa[0] < 42 ){
			pipeFlag[1] = 1;
			pipa[1] = 4;
			tampilPipa(1);
		}
		if( pipa[0] > 68 ){
			skor++;
			updateskor();
			pipeFlag[1] = 0;
			pipa[0] = pipa[1];
			lubang[0] = lubang[1];
		}
		
	}
	 
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	
//	mulai();
	
	do{
		system("cls");
		gotoxy(10,5); cout<<"  ________________________ "; 
		gotoxy(10,6); cout<<" |        Avocles!        | "; 
		gotoxy(10,7); cout<<" |________________________| ";
		gotoxy(10,9); cout<<"Mulai[1]";
		gotoxy(10,10); cout<<"Keluar[2]";	 
		gotoxy(10,11); cout<<"Masukkan pilihan : ";
		char op = getche();
		
		if( op=='1') mulai();
		else if( op=='2') exit(0);
		
	}while(1);
	
	return 0;
}
