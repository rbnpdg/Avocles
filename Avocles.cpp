/* 
Nama Anggota kelompok
1. Adiska Bayu Saputra (2257051034)
2. Lira Septiyani (2217051151)
3. Ruben Pandega Aditama (2217051085)
 */

#include <iostream>		//lib untuk cout
#include <conio.h>		//lib untuk getche
#include <windows.h>	//lib untuk clearscreen dgn system("cls") dan set kecepatan game Sleep()

#define lebarlayar 100		//definisi lebar layar saat bermain
#define tinggilayar 26		//definisi tinggi layar saat bermain
#define lebarwindow 75		//definisi area karakter bermain
#define ukuranlubang 7		//definisi ukuran lubang untuk lewat karakter

using namespace std;
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipa[3];		//definisi pipa
int lubang[3];		//definisi lubang pipa
int masukpipa[3];
char burung[2][6] = { '/','-','-','o','\\',' ','|','_','_','_',' ','>' }; //definisi karakter burung
int posisiburung = 1;
int skor = 0;

void gotoxy(int x, int y) {
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
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

void tampilPipa(int ind) { //menampilkan pipa, rand() untuk mengacak area lubang yang akan dilewati burung
	lubang[ind] = 3 + rand()%20; 
}
void buatPipa(int ind){ //generate pipa
	if( masukpipa[ind] == true ){
		for(int i = 0; i < lubang[ind]; i++){ 
			gotoxy(lebarwindow - pipa[ind],i + 1); 
			cout << "==="; 
		}
		for(int i = lubang[ind] + ukuranlubang; i < tinggilayar - 1; i++){ 
			gotoxy(lebarwindow - pipa[ind],i + 1); 
			cout<<"===";
		}
	} 
}

void hapusPipa(int ind){ //menghapus pipa ketika sudah dilewati burung
	if( masukpipa[ind] == true ){
		for(int i = 0; i < lubang[ind]; i++){ 
			gotoxy(lebarwindow - pipa[ind], i + 1); 
			cout << "   "; 
		}
		for(int i = lubang[ind] + ukuranlubang; i < tinggilayar - 1; i++){ 
			gotoxy(lebarwindow - pipa[ind], i + 1); 
			cout << "   "; 
		}
	}
}

void tampilBurung(){ //menampilkan karakter burung
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 6; j++){
			gotoxy(j + 2,i + posisiburung);
			cout << burung[i][j];
		}
	}
}
void hapusBurung(){	//menghapus karakter ketika endgame
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 6; j++){
			gotoxy(j + 2, i + posisiburung); 
			cout << " ";
		}
	}
}

int tabrakan(){	//saat burung menabrak pipa
	if( pipa[0] >= 61  ){
		if(posisiburung < lubang[0] || posisiburung > lubang[0] + ukuranlubang){
			return 1;
		}
	}
	return 0;
}

void gameover() {  //tampilan ketika gameover
	system("cls");
	cout << endl;
	gotoxy(45,8); cout << "__________________________";
	gotoxy(45,9); cout << "|        Game Over       |";
	gotoxy(45,10); cout << "|________________________|";
	gotoxy(42,13); cout << "Press any key to go back to menu.";
	getch();
}
void updateskor(){  //fungsi untuk menjalankan skor
	gotoxy(lebarwindow + 8, 7);
	cout << "Skor : " << skor << endl;
}

void mulai(){ //fungsi ketika mulai game
	
	posisiburung = 6;
	skor = 0;
	masukpipa[0] = 1; 
	masukpipa[1] = 0;
	pipa[0] = pipa[1] = 4;
	
	system("cls"); 
	border();
	tampilPipa(0);
	updateskor();
	
	gotoxy(lebarwindow + 8, 2);
	cout<<"Avocles!";

	gotoxy(lebarwindow + 1, 13);
	cout<<"Tekan spasi untuk lompat";
	
	gotoxy(10, 5);
	cout<<"Tekan sembarang tombol untuk mulai";
	getch();
	gotoxy(10, 5);
	cout<<"                                        ";
	
	while(1){
		 
		if(kbhit()){ //ukuran lompat burung ketika menekan spasi
			char ch = getch();
			if(ch == 32){
				if( posisiburung > 3 )
					posisiburung -= 3;
			} 
		}
		
		tampilBurung();
		buatPipa(0);
		buatPipa(1);
		
		if( tabrakan() == 1 ){ //ketika tabrakan, maka game berhenti
			gameover();		   //menmpilkan fungsi gameover
			return;
		}
		Sleep(100); //kecepatan game
		hapusBurung();
		hapusPipa(0);
		hapusPipa(1);
		posisiburung += 1;
		
		if( posisiburung > tinggilayar - 2 ){ //endgame kalau burung jatuh
			gameover();
			return;
		}
		
		if( masukpipa[0] == 1 )
			pipa[0] += 2;
		
		if( masukpipa[1] == 1 )
			pipa[1] += 2;
		
		if( pipa[0] >= 40 && pipa[0] < 42 ){
			masukpipa[1] = 1;
			pipa[1] = 4;
			tampilPipa(1);
		}
		if( pipa[0] > 68 ){
			skor++;
			updateskor();
			masukpipa[1] = 0;
			pipa[0] = pipa[1];
			lubang[0] = lubang[1];
		}
		
	}
	 
}

int main()
{
	
//	mulai();
	
	do{
		system("cls");
		gotoxy(45,5); cout<<"  ________________________ "; 
		gotoxy(45,6); cout<<" |        Avocles!        | "; 
		gotoxy(45,7); cout<<" |------------------------| ";
		gotoxy(45,8); cout<<" |  Avoid the Obstacles!  | ";
		gotoxy(45,9); cout<<" |________________________| ";
		gotoxy(48,11); cout<<"Tekan 1 untuk mulai";
		gotoxy(48,12); cout<<"Tekan 2 untuk keluar";	 
		gotoxy(48,13); cout<<"";
		char op = getche();
		
		if( op=='1') mulai();	//ketika ketik 1, maka game mulai
		else if( op=='2') exit(0);  //ketika ketik 2, maka keluar
		
	}while(1);
	
	return 0;
}
