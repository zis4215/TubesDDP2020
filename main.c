/* Program Tictactoe.c
Nama /Author 	: Aqil Rahman & Nuno Alwi Azimah
*/

//header
#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

//modul
void game();
	void setGrid();
	int setLevel();
	void setNama();
	void setRonde();
	
	void grid1();
	void grid2();
	void grid3();

	void resetGrid();
	bool fillGrid();
	bool cekStatusGrid();
	bool cekLine();
	
	void viewScore();
	void resetScore();
	void viewGiliran();
	bool switchGiliran();
	
	void showJuara();
	void timeOut();
void help();
void about();


//struct 
typedef struct {
	int index;
	char nama[100];
	int score;
	bool status;
} Player;

typedef struct {
	int pola;
	char ordo[9][9];
	int ordoDone[9][9];
	int ordoStatus[9][9];
	bool status;
	int waktu;
	int ronde;
} Grid;

typedef struct {
	bool active;
	char nama[100];
	int score;
	bool status;
	int level;
} Komputer;


//Variabel Global
Player pemain[2];
Grid papan;
Komputer bot;

int i,j;

//Program utama
int main(){
	int pilihan,error=0;
	
	do{
		system("cls");
		printf("||=========   Main Menu   =========||\n");
		printf("|| 1) Start Game                   ||\n");
		printf("|| 2) Help                         ||\n");
		printf("|| 3) About                        ||\n");
		printf("|| 4) Exit                         ||\n");
		printf("||=================================||\n\n\n");
		if(error == 1)printf("Inputan Error\n");
		error=0;
		printf("Masukan pilihan : ");
		scanf("%d",&pilihan);
	
		switch(pilihan){
			case 1:
				game();
				break;
				
			case 2:
				help();
				break;
				
			case 3:
				about();
				break;
				
			case 4:
				break;
				
			default:
				error=1;
				break;
		}
	}while(pilihan != 4);
	
	return 0;
}


void game(){
	int s,vsBot = 1;
	bool gameEnd = false;
	setGrid();
	if(setLevel() == 4){
		vsBot = 2;
	}
	setNama(vsBot);
	setRonde();
	
	system("cls");
	do{
		switch(papan.pola){
			case 1:
				grid1();
				break;

			case 2:
				grid2();
				break;

			case 3:
				grid3();
				break;

			default:
				break;
		}
	}while(gameEnd);
	
}

int setLevel(){
	int pilihan;
	bot.active = false;
	
	do{
		system("cls");
		printf("||===========   Level   ===========||\n");
		printf("|| 1) Easy                         ||\n");
		printf("|| 2) Medium                       ||\n");
		printf("|| 3) Hard                         ||\n");
		printf("|| 4) VS Player                    ||\n");
		printf("||=================================||\n\n\n");
		printf("Masukan level : ");
		scanf("%d",&pilihan);
		if(pilihan != 4){
			bot.active = true;
			bot.level = pilihan;
		}
	}while(pilihan > 4 || pilihan < 0);
	
	return pilihan;
}

void setGrid(){
	do{
		system("cls");
		printf("||===========    Grid    ===========||\n");
		printf("|| 1) 3 X 3                         ||\n");
		printf("|| 2) 5 X 5                         ||\n");
		printf("|| 3) 7 X 7                         ||\n");
		printf("||==================================||\n\n\n");
		printf("Masukan Grid : ");
		scanf("%d",&papan.pola);
	}while(papan.pola > 3 || papan.pola < 0);
}

void setNama(int player){
	int i;
	for(i=0;i<player;i++){
		system("cls");
		printf("||===========    Name    ===========||\n");
		if(player>1) printf("Masukan Nama Player %d:\n",i+1);
			else printf("Masukan Nama :\n");
		scanf("%s",&pemain[i].nama);
		pemain[i].index=i;
	}
}

void setRonde(){
	bool salah=false;
	
	do{
		system("cls");
		printf("||===========    Ronde    ===========||\n");
		if(salah==true) printf("Ronde harus ganjil\n");
		printf("Berapa ronde anda ingin bermain ? ");
		scanf("%d",&papan.ronde);
		if(papan.ronde % 2 == 0) salah=true;
	}while(papan.ronde % 2 == 0);
	
}

int timeout ( int seconds ){
	clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;

    while (clock() < endwait) {}
    return  1;
}

void grid1(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetGrid(1);
	resetScore();
	do{
		do{
			system("cls");
			printf("==========   PAPAN PERMAINAN   ==========\n");
			viewScore();
			printf("Ronde   : %d\n",ronde+1);
			viewGiliran(giliran);
			printf("||===========||===========||===========||\n");
			printf("||1          ||2          ||3          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||\n",papan.ordo[0][0],papan.ordo[0][1],papan.ordo[0][2]);
			printf("||           ||           ||           ||\n");
			printf("||===========||===========||===========||\n");
			printf("||4          ||5          ||6          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||\n",papan.ordo[1][0],papan.ordo[1][1],papan.ordo[1][2]);
			printf("||           ||           ||           ||\n");
			printf("||===========||===========||===========||\n");
			printf("||7          ||8          ||9          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||\n",papan.ordo[2][0],papan.ordo[2][1],papan.ordo[2][2]);
			printf("||           ||           ||           ||\n");
			printf("||===========||===========||===========||\n\n\n");
			if(errorPilih==true) printf("Nomor tidak ada atau sudah diisi!\n");
			errorPilih = fillGrid(giliran,1);
		}while(errorPilih == true);
		if(cekStatusGrid(1) == false)resetGrid(1); 
		if(switchGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekLine(giliran,1) == true)ronde++;
	}while(ronde < papan.ronde);
	if(switchGiliran(giliran) == true) giliran++;
		else giliran--;
	showJuara(giliran);
}

void grid2(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetGrid(2);
	do{
		do{
			system("cls");
			printf("==========   PAPAN PERMAINAN   ==========\n");
			viewScore();
			printf("Ronde   : %d\n",ronde+1);
			viewGiliran(giliran);
			
			printf("=======================   PAPAN PERMAINAN   =======================\n\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||1          ||2          ||3          ||4          ||5          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[0][0],papan.ordo[0][1],papan.ordo[0][2],papan.ordo[0][3],papan.ordo[0][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||6          ||7          ||8          ||9          ||10         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[1][0],papan.ordo[1][1],papan.ordo[1][2],papan.ordo[1][3],papan.ordo[1][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||11         ||12         ||13         ||14         ||15         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[2][0],papan.ordo[2][1],papan.ordo[2][2],papan.ordo[2][3],papan.ordo[2][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||16         ||17         ||18         ||19         ||20         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[3][0],papan.ordo[3][1],papan.ordo[3][2],papan.ordo[3][3],papan.ordo[3][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n");
			printf("||21         ||22         ||23         ||24         ||25         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[4][0],papan.ordo[4][1],papan.ordo[4][2],papan.ordo[4][3],papan.ordo[4][4]);
			printf("||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||\n\n\n");
			if(errorPilih==true) printf("Nomor tidak ada atau sudah diisi!\n");
			errorPilih = fillGrid(giliran,2);
		}while(errorPilih == true);
		if(cekStatusGrid(2) == false)resetGrid(2); 
		if(switchGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekLine(giliran,2) == true)ronde++;
	}while(ronde < papan.ronde);
}

void grid3(){
	int giliran=0,ronde=0;
	bool errorPilih=false;

	resetGrid(3);
	resetScore();
	do{
		do{
			system("cls");
			printf("==========   PAPAN PERMAINAN   ==========\n");
			viewScore();
			printf("Ronde   : %d\n",ronde+1);
			viewGiliran(giliran);
			printf("====================================   PAPAN PERMAINAN   ====================================\n\n");			
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||1          ||2          ||3          ||4          ||5          ||6          ||7          ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[0][0],papan.ordo[0][1],papan.ordo[0][2],papan.ordo[0][3],papan.ordo[0][4],papan.ordo[0][5],papan.ordo[0][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||8          ||9          ||10         ||11         ||12         ||13         ||14         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[1][0],papan.ordo[1][1],papan.ordo[1][2],papan.ordo[1][3],papan.ordo[1][4],papan.ordo[1][5],papan.ordo[1][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||15         ||16         ||17         ||18         ||19         ||20         ||21         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[2][0],papan.ordo[2][1],papan.ordo[2][2],papan.ordo[2][3],papan.ordo[2][4],papan.ordo[2][5],papan.ordo[2][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||22         ||23         ||24         ||25         ||26         ||27         ||28         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[3][0],papan.ordo[3][1],papan.ordo[3][2],papan.ordo[3][3],papan.ordo[3][4],papan.ordo[3][5],papan.ordo[3][6]);			
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||29         ||30         ||31         ||32         ||33         ||34         ||35         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[4][0],papan.ordo[4][1],papan.ordo[4][2],papan.ordo[4][3],papan.ordo[4][4],papan.ordo[4][5],papan.ordo[4][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||36         ||37         ||38         ||39         ||40         ||41         ||42         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[5][0],papan.ordo[5][1],papan.ordo[5][2],papan.ordo[5][3],papan.ordo[5][4],papan.ordo[5][5],papan.ordo[5][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n");
			printf("||43         ||44         ||45         ||46         ||47         ||48         ||49         ||\n");
			printf("||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||     %c     ||\n"
			,papan.ordo[6][0],papan.ordo[6][1],papan.ordo[6][2],papan.ordo[6][3],papan.ordo[6][4],papan.ordo[6][5],papan.ordo[6][6]);
			printf("||           ||           ||           ||           ||           ||           ||           ||\n");
			printf("||===========||===========||===========||===========||===========||===========||===========||\n\n\n");
			if(errorPilih==true) printf("Nomor tidak ada atau sudah diisi!\n");
			errorPilih = fillGrid(giliran,3);
		}while(errorPilih == true);
		if(cekStatusGrid(3) == false)resetGrid(3); 
		if(switchGiliran(giliran) == true) giliran++;
			else giliran--;
		if(cekLine(giliran,3) == true)ronde++;
	}while(ronde < papan.ronde);
	if(switchGiliran(giliran) == true) giliran++;
		else giliran--;
	showJuara(giliran);
}

bool fillGrid(giliran,grid){
	int pilih,noGrid=1;
	bool errorPilih=false;
	
	printf("Masukan nomor grid yang akan diisi : ");
	scanf("%d",&pilih);

	switch(grid){
		case 1:
			if(pilih > 9 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 0){
						papan.ordo[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 1){
						papan.ordo[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
			
		case 2:
			if(pilih > 25 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 0){
						papan.ordo[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 1){
						papan.ordo[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
			
		case 3:
			if(pilih > 49 || pilih < 0){
				errorPilih = true;
			}else{
				errorPilih = false;
			}
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){			
					if(pilih == papan.ordoStatus[i][j]){
						errorPilih = true;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 0){
						papan.ordo[i][j] = 'X';
						papan.ordoDone[i][j] = 0;
						papan.ordoStatus[i][j] = pilih;
					}else if(pilih == papan.ordoDone[i][j] && pemain[giliran].index == 1){
						papan.ordo[i][j] = 'O';
						papan.ordoDone[i][j] = 100;
						papan.ordoStatus[i][j] = pilih;
					}
				}
			}
			break;
	}
	
	

	return errorPilih;
}

void resetGrid(grid){
	int i,j,noGrid=1;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){    
					papan.ordo[i][j] = '-';
					papan.ordoDone[i][j] = noGrid;
					papan.ordoStatus[i][j] = 0;
					noGrid++;
				}
			}
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){    
					papan.ordo[i][j] = '-';
					papan.ordoDone[i][j] = noGrid;
					papan.ordoStatus[i][j] = 0;
					noGrid++;
				}
			}
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){    
					papan.ordo[i][j] = '-';
					papan.ordoDone[i][j] = noGrid;
					papan.ordoStatus[i][j] = 0;
					noGrid++;
				}
			}
			break;
	}
	

}

bool cekStatusGrid(grid){
	int noGrid=1, hasil=0;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					
					if(papan.ordoStatus[i][j] == noGrid) hasil++;
					noGrid++;
					
				}
			}
			
			if(hasil == 9) return false;
				else return true;
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){
					
					if(papan.ordoStatus[i][j] == noGrid) hasil++;
					noGrid++;
					
				}
			}
			
			if(hasil == 25) return false;
				else return true;
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){
					
					if(papan.ordoStatus[i][j] == noGrid) hasil++;
					noGrid++;
					
				}
			}
			
			if(hasil == 49) return false;
				else return true;
			break;
	}
}

bool cekLine(giliran,grid){
	bool ronde=false;
	int putaran,miringkanan;
	
	switch(grid){
		case 1:
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){					
					if((papan.ordoDone[i][0] == papan.ordoDone[i][1] && papan.ordoDone[i][1] == papan.ordoDone[i][2]) ||
					(papan.ordoDone[0][j] == papan.ordoDone[1][j] && papan.ordoDone[1][j] == papan.ordoDone[2][j]) || 
					(papan.ordoDone[0][0] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][2]) ||
					(papan.ordoDone[0][2] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][0]) ){	
						ronde = true;
						if(pemain[giliran].index == 0) pemain[1].score++;
							else pemain[0].score++;
						resetGrid(1);
					}
				}
			}
			break;
			
		case 2:
			for(i=0;i<5;i++){
				for(j=0;j<5;j++){					
					if((papan.ordoDone[i][0] == papan.ordoDone[i][1] && papan.ordoDone[i][1] == papan.ordoDone[i][2]) ||
					(papan.ordoDone[0][j] == papan.ordoDone[1][j] && papan.ordoDone[1][j] == papan.ordoDone[2][j]) || 
					(papan.ordoDone[0][0] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][2]) ||
					(papan.ordoDone[0][2] == papan.ordoDone[1][1] && papan.ordoDone[1][1] == papan.ordoDone[2][0]) ){	
						ronde = true;
						if(pemain[giliran].index == 0) pemain[1].score++;
							else pemain[0].score++;
						resetGrid(1);
					}
				}
			}
			break;
			
		case 3:
			for(i=0;i<7;i++){
				for(j=0;j<7;j++){		
				
					for(putaran=0;putaran<3;putaran++){
						if(
						//horizontal
						(papan.ordoDone[i][0+putaran] == papan.ordoDone[i][1+putaran] && papan.ordoDone[i][1+putaran] == papan.ordoDone[i][2+putaran] &&
				 		papan.ordoDone[i][2+putaran] == papan.ordoDone[i][3+putaran] && papan.ordoDone[i][3+putaran] == papan.ordoDone[i][4+putaran])||
				 		
				 		//vertikal
						(papan.ordoDone[0+putaran][j] == papan.ordoDone[1+putaran][j] && papan.ordoDone[1+putaran][j] == papan.ordoDone[2+putaran][j] &&
						papan.ordoDone[2+putaran][j] == papan.ordoDone[3+putaran][j] && papan.ordoDone[3+putaran][j] == papan.ordoDone[4+putaran][j])|| 
						
						//miring
						(papan.ordoDone[0+putaran][0+putaran] == papan.ordoDone[1+putaran][1+putaran] && papan.ordoDone[1+putaran][1+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][3+putaran] && papan.ordoDone[3+putaran][3+putaran] == papan.ordoDone[4+putaran][4+putaran]) ||
						
						(papan.ordoDone[0+putaran][6-putaran] == papan.ordoDone[1+putaran][5-putaran] && papan.ordoDone[1+putaran][5-putaran] == papan.ordoDone[2+putaran][4-putaran] &&
						papan.ordoDone[2+putaran][4-putaran] == papan.ordoDone[3+putaran][3-putaran] && papan.ordoDone[3+putaran][3-putaran] == papan.ordoDone[4+putaran][2-putaran])
						){	ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(3);
						}			
					}
					
					for(putaran=0;putaran<2;putaran++){
						if(
						//miring 2 kali
						(papan.ordoDone[0+putaran][1+putaran] == papan.ordoDone[1+putaran][2+putaran] && papan.ordoDone[1+putaran][2+putaran] == papan.ordoDone[2+putaran][3+putaran] &&
						papan.ordoDone[2+putaran][3+putaran] == papan.ordoDone[3+putaran][4+putaran] && papan.ordoDone[3+putaran][4+putaran] == papan.ordoDone[4+putaran][5+putaran]) ||
						
						(papan.ordoDone[1+putaran][0+putaran] == papan.ordoDone[2+putaran][1+putaran] && papan.ordoDone[2+putaran][1+putaran] == papan.ordoDone[3+putaran][2+putaran] &&
						papan.ordoDone[3+putaran][2+putaran] == papan.ordoDone[4+putaran][3+putaran] && papan.ordoDone[4+putaran][3+putaran] == papan.ordoDone[5+putaran][4+putaran]) ||
						
						(papan.ordoDone[0+putaran][5-putaran] == papan.ordoDone[1+putaran][4-putaran] && papan.ordoDone[1+putaran][4-putaran] == papan.ordoDone[2+putaran][3-putaran] &&
						papan.ordoDone[2+putaran][3-putaran] == papan.ordoDone[3+putaran][2-putaran] && papan.ordoDone[3+putaran][2-putaran] == papan.ordoDone[4+putaran][1-putaran]) ||
						
						(papan.ordoDone[1+putaran][6-putaran] == papan.ordoDone[2+putaran][5-putaran] && papan.ordoDone[2+putaran][5-putaran] == papan.ordoDone[3+putaran][4-putaran] &&
						papan.ordoDone[3+putaran][4-putaran] == papan.ordoDone[4+putaran][3-putaran] && papan.ordoDone[4+putaran][3-putaran] == papan.ordoDone[5+putaran][2-putaran])
						){
						ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(3);
						}
					}
					
					for(putaran=0;putaran<=2;putaran+=2){
						if(
						//miring 1 kali
						(papan.ordoDone[0+putaran][2-putaran] == papan.ordoDone[1+putaran][3-putaran] && papan.ordoDone[1+putaran][3-putaran] == papan.ordoDone[2+putaran][4-putaran] &&
						papan.ordoDone[2+putaran][4-putaran] == papan.ordoDone[3+putaran][5-putaran] && papan.ordoDone[3+putaran][5-putaran] == papan.ordoDone[4+putaran][6-putaran]) ||
						
						(papan.ordoDone[0+putaran][4+putaran] == papan.ordoDone[1+putaran][3+putaran] && papan.ordoDone[1+putaran][3+putaran] == papan.ordoDone[2+putaran][2+putaran] &&
						papan.ordoDone[2+putaran][2+putaran] == papan.ordoDone[3+putaran][1+putaran] && papan.ordoDone[3+putaran][1+putaran] == papan.ordoDone[4+putaran][0+putaran])
						){
						ronde = true;
							if(pemain[giliran].index == 0) pemain[1].score++;
								else pemain[0].score++;
							resetGrid(3);
						}
					}
					
				}
			}
			break;		
	}
	
	return ronde;
}

void viewScore(){
	if(bot.active == false){
		printf("Score %s : %d     Score %s : %d\n\n",pemain[0].nama,pemain[0].score,pemain[1].nama,pemain[1].score);
	}else{
		printf("Score %s : %d     Score Komputer : %d\n\n",pemain[0].nama,pemain[0].score,bot.score);		
	}
}

void resetScore(){
	pemain[0].score = 0;
	pemain[0].score = 0;
	bot.score = 0;	
}

void viewGiliran(int giliran){
	printf("Giliran : %s\n\n",pemain[giliran].nama);
}

bool switchGiliran(int giliran){
	if(giliran == 0){
		pemain[giliran].status = false;
		return true;
	}else{
		pemain[giliran].status = false;
		return false;
	}
}

void showJuara(int giliran){
	char pilihan='N';

	do{
		system("cls");
		printf("||==========   Juara   ==========||\n");
		printf("Juaranya adalah : %s\n",pemain[giliran].nama);
		if(giliran  == 0) printf("Score           : %d - %d\n",pemain[0].score,pemain[1].score);
			else printf("Score           : %d - %d\n",pemain[0].score,pemain[1].score);
		printf("||================================||\n\n\n");
		printf("Masukan Y untuk kembali : ");
		scanf("%c",&pilihan);
	}while(tolower(pilihan)!= 'y');
}

void help(){
	char buff[255];
	char pilihan='N';

  	FILE *how;
	// membuka file
	
	if ((how = fopen("howtolpay.txt","r")) == NULL){
    	printf("Error: File tidak ada!");
	    exit(1);
	}
	
	fgets(buff, 255, how);
	do{
		system("cls");
		printf("%s", buff);
		printf("Masukan Y untuk kembali : ");
		scanf("%c",&pilihan);
	}while(tolower(pilihan)!= 'y');
	
	fclose(how);
}

void about(){
	char pilihan='N';
	
	do{
		system("cls");
		printf("||===========   About   ===========||\n");
		printf("||                                 ||\n");
		printf("||                                 ||\n");
		printf("||                                 ||\n");
		printf("||                                 ||\n");
		printf("||=================================||\n\n\n");
		printf("Masukan Y untuk kembali : ");
		scanf("%c",&pilihan);
	}while(tolower(pilihan) != 'y');
}
