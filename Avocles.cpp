
#include <iostream>
#include <conio.h>
using namespace std;

void gameover() {
	system("cls");
	cout << endl;
	cout << "\t\t__________________________" << endl;
	cout << "\t\t|        Game Over       |" << endl;
	cout << "\t\t|________________________|" << endl << endl;
	cout << "\tTekan tombol sembarang untuk kembali ke menu!";
	getch();
}

int main() {
	gameover();
	
	system("cls");
	cout<<"  ________________________ \n"; 
	cout<<" |        Avocles!        | \n"; 
	cout<<" |________________________| \n";
	cout<<"Mulai[1]\n";
	cout<<"Keluar[2]\n";	 
	cout<<"Masukkan pilihan : \n";
}
