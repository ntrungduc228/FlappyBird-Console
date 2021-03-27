/*========================== DUC NGUYEN ============================ */
#include"myLib.h"
#pragma comment (lib, "winmm.lib")

const int ConsoleWidth = 150; // chieu ngang man hinh
const int ConsoleHeight = 100; // chieu doc man hinh
const int soOngNuoc = 3; // tong so ong nuoc 
const int khoangCachOngTrenVaDuoi = 37; // khoang cach 2 ong nuoc tren va duoi
const int khoangCach2OngNuoc = 80; // khoang cach giua 2 ong nuoc truoc va sau
const int ChuSoWidth = 3 ; // chieu rong cua diem so
const int ChuSoHeight = 6; // chieu cao cua diem so
const int khoangCach2ChuSo = 1; // khoang cach giua 2 chu so
const int toaDoYDiemPlayer = 10; // toa do Y cua diem tren man hinh trong Game

struct ongNuoc
{
	int x; // toa do ong nuoc
	int doDai; // do dai ong nuoc
};

ongNuoc ongNuocThu[soOngNuoc];
int bird[20][20]; // mang 2 chieu luu hinh anh con chim
int birdHeight, birdWidth; // chieu cao va chieu rong cua hinh anh con chim
int logoGameOver[100][100]; // mang luu Logo xuat hien khi thua game
int logoGoverWidth, logoGoverHeight; // 
int birdX = 40, birdY=0; // toa do ban dau cua con chim
int buocNhay; // buoc nhay cua FlappyBird khi Player an phim SPACE
bool gameOver; // kiem tra thua game
int so[15][15][15]; // mang 3 chieu luu hinh anh con so
int diemPlayer, diemCaoNhat;
int dangQua;
int viTriChon, tongMuc=4;
/*
	- tro choi moi
	- diem cao nhat
	- thong tin
	- thoat
*/

/*====================  KHAI BAO NGUYEN MAU HAM ====================*/

void layDuLieu(); // lay du lieu ban dau cho game
void layDuLieuFlappyBird(int &birdWidth, int &birdH);
void layDuLieuChuSo();
void layLogoGameOver(int &logoGoverWidth,int &logoGoverHeight);
void veFlappyBird(int birdX, int birdY);
void veFlappyBirdDown(int birdX, int birdY);
void velogoGameOver(int diemPlayer, int diemCaoNhat);
void veOngNuoc(int ongNuocX, int chieuDaiOngTren);
void veMangOngNuoc();
void caiDatManHinhKhiChoi();
void khoiTaoGame();
void xuLyOngNuoc();
void xuLyFlappyBird();
bool kiemTraGameOver();
void veDiemSo(int diem, int toaDoY);
int layDiemCaoNhat();

/*======= thiet ke menu =======*/
int heightMenu = 30;
int widthMenu= 80;

void caiDat();
void luaChonMenu();
void menuChinh(int viTriChon);
void layLogoFlappyBird();
void troChoiMoi();
void vietDiemCaoNhat();
void thongTin();
void thoat();
void nutTroVe();


int main()
{
	hidecursor(); // an con tro man hinh
	layDuLieu(); 
	caiDat();
	
	viTriChon = 0;
	
	luaChonMenu();
	
	return 0;
}



/*==================  DINH NGHIA NGUYEN MAU HAM ====================*/

void layDuLieu()
{
	initlibrary(); // khoi tao thu vien do hoa
	layDuLieuFlappyBird(birdWidth, birdHeight);
	layDuLieuChuSo();
	layLogoGameOver(logoGoverWidth,logoGoverHeight);
	diemCaoNhat = layDiemCaoNhat();
}

void caiDat()
{
	SetConsoleTitle(TEXT("FLAPPYBIRD CONSOLE - DUC NGUYEN"));
	int dong = 0;

	resizeConsole(widthMenu, heightMenu);
	SetFontApp(8, 16);
	clrscr(cllightblue); // xoa man hinh
	veFlappyBird(2, 4);
	layLogoFlappyBird();
}

void khoiTaoGame()
{
	gameOver = false;
	buocNhay = 0;
	diemPlayer = 0;

	srand(time(NULL));
	// khoi tao ong nuoc
	for (int i = 0; i < soOngNuoc; i++)
	{
		ongNuocThu[i].x = ConsoleWidth - 1 + i * khoangCach2OngNuoc;
		// rand() % (b - a + 1 ) + a;  ==> random trong khoang [a;b]
		ongNuocThu[i].doDai = rand() % (ConsoleHeight - 10 - khoangCachOngTrenVaDuoi-10 + 1 ) + 10;
	}
}


void layLogoGameOver(int& logoGoverWidth, int& logoGoverHeight)
{
	string duLieuMotHang;
	int dong = 0, cot = 0;
	ifstream fileIn;
	fileIn.open("data\\GameOverImg.txt", ios_base::in);
	while (!fileIn.eof())
	{
		getline(fileIn, duLieuMotHang);// lay so ki tu cua tung hang

		for (cot = 0; cot < duLieuMotHang.length(); cot++)
		{
			char kiTu = duLieuMotHang[cot];
			logoGameOver[dong][cot] = kiTu;
		}

		dong++;

		if (fileIn.eof())
		{
			break;
		}

	}

	logoGoverHeight = dong;
	logoGoverWidth = duLieuMotHang.length();

	fileIn.close();
}

void velogoGameOver(int diemPlayer, int diemCaoNhat)
{
	if (diemPlayer > diemCaoNhat) {
		diemCaoNhat = diemPlayer;
		ofstream fileOut;
		fileOut.open("data\\bestScore.txt",ios_base::out);
		fileOut << diemCaoNhat;
		fileOut.close();
	}

	for (int i = 0; i < logoGoverHeight; i++)
	{

		for (int j = 0; j < logoGoverWidth; j++)
		{
			gotoxy((ConsoleWidth - logoGoverWidth +1) / 2+j,(ConsoleHeight-logoGoverHeight+1)/2+i );
			char kiTu = logoGameOver[i][j];
			if (kiTu == 'B')
			{
				SetConsoleColor(clgreen, clgray);
				kiTu = 219;
			}
			else if (kiTu == 'X')
			{
				SetConsoleColor(cllightred, clblack);
				kiTu = 219;
			}
			else if (kiTu == '#')
			{
				SetConsoleColor(clblue, clblack);
				kiTu = 219;
			}
			else
			{
				SetConsoleColor(cllightwhite, clgray);
				kiTu = 176;
			}
			cout << kiTu;

		}
		
	}
	int toaDoYDiemCaoNhat = (ConsoleHeight - 16) / 2 +1 ;
	int toaDoYDiem = toaDoYDiemCaoNhat + 7;
	veDiemSo(diemCaoNhat,toaDoYDiemCaoNhat);
	veDiemSo(diemPlayer, toaDoYDiem);
}

void layDuLieuFlappyBird(int& birdWidth, int& birdHeight)
{
	string duLieuMotHang;
	int dong = 0, cot=0;
	ifstream fileIn;
	fileIn.open("data\\flappybird.txt", ios_base::in);
	while (!fileIn.eof())
	{
		getline(fileIn, duLieuMotHang);// lay so ki tu cua tung hang
	
		for ( cot = 0; cot < duLieuMotHang.length(); cot++)
		{
			char kiTu = duLieuMotHang[cot];
			bird[dong][cot] = kiTu;
		}

		dong++;

		if (fileIn.eof())
		{
			break;
		}
		
	}

	birdHeight = dong;
	birdWidth = duLieuMotHang.length();
	 
	fileIn.close();
}

void veFlappyBird(int birdX, int birdY)
{
	// i tuong ung voi dong, j tuong ung voi cot
	for (int i = 0; i < birdHeight; i++)
	{
		for (int j = 0; j < birdWidth; j++)
		{
			char kiTu = bird[i][j];
			//gotoxy(birdX + j, birdY);
			if (kiTu == 'B')
			{
				SetConsoleColor(clblack, clwhite);
				kiTu = 219;
				gotoxy(birdX + j, birdY);
				//cout << kiTu;
			}
			else if (kiTu == 'R')
			{
				SetConsoleColor(cllightred, clwhite);
				kiTu = 219;
				gotoxy(birdX + j, birdY);
				//cout << kiTu;
			}
			else if (kiTu == 'Y')
			{
				SetConsoleColor(cllightyellow, cllightblue);
				kiTu = 219;
				gotoxy(birdX + j, birdY);
				//cout << kiTu;
			}
			else if (kiTu == 'W')
			{
				SetConsoleColor(cllightwhite, clwhite);
				kiTu = 219;
				gotoxy(birdX + j, birdY);
				//cout << kiTu;
			}
			else if (kiTu == 'O')
			{
				SetConsoleColor(cllightgreen, cllightblue);
				kiTu = 219;
				gotoxy(birdX + j, birdY);
				//cout << kiTu;
			}
			else
			{
				SetConsoleColor(cllightblue, cllightblue);
				gotoxy(birdX +j, birdY);
				//cout << kiTu;
			}
			cout << kiTu;
		}
		birdY++;
	}
}

void veFlappyBirdDown(int birdX, int birdY)
{
	int c = 0;
	
	for (int j = 0; j < birdWidth; j++)
	{
		gotoxy(birdX, birdY);
		for (int i = birdHeight-1 ; i >= 0; i--)
		{
			
			char kiTu = bird[i][j];
			if (kiTu == 'B')
			{
				SetConsoleColor(clblack, clwhite);
				kiTu = 219;
			
				//cout << kiTu;
			}
			else if (kiTu == 'R')
			{
				SetConsoleColor(cllightred, clwhite);
				kiTu = 219;
				
				//cout << kiTu;
			}
			else if (kiTu == 'Y')
			{
				SetConsoleColor(cllightyellow, cllightblue);
				kiTu = 219;
			
				//cout << kiTu;
			}
			else if (kiTu == 'W')
			{
				SetConsoleColor(cllightwhite, clwhite);
				kiTu = 219;
				
				//cout << kiTu;
			}
			else if (kiTu == 'O')
			{
				SetConsoleColor(cllightgreen, cllightblue);
				kiTu = 219;
				//cout << kiTu;
			}
			else
			{
				SetConsoleColor(cllightblue, cllightblue);
			
				//cout << kiTu;
			}
			cout << kiTu;
		}
		birdY++;
	}
}

void veOngNuoc(int ongNuocX, int chieuDaiOngTren)
{
	if (ongNuocX < ConsoleWidth) 
	{
		// ve ong tren
		for (int i = chieuDaiOngTren; i > 0; i--)
		{
			SetConsoleColor(((i % 2 == 0) ? cllightwhite : cllightred), clblack);
			gotoxy(ongNuocX, i);
			cout << char(177) << char(219) << char(177);
		}
			
		// ve ong duoi
		for (int i = 0; i < ConsoleHeight -chieuDaiOngTren- khoangCachOngTrenVaDuoi; i++)
		{
			SetConsoleColor(((i % 2 == 0) ? cllightwhite : cllightred), clblack);
			gotoxy(ongNuocX, ConsoleHeight -i);
			cout << char(177) << char(219) << char(177);
		}
	}
}

void veMangOngNuoc()
{
	for (int i = 0; i < soOngNuoc; i++)
	{
		veOngNuoc(ongNuocThu[i].x, ongNuocThu[i].doDai);
	}
}

void caiDatManHinhKhiChoi()
{
	resizeConsole(ConsoleWidth, ConsoleHeight);
	//system("MODE CON COLS=150 LINES=100");
	SetFontApp(4, 6);
	MaximizeWindow();
}

void xuLyOngNuoc()
{
	srand(time(NULL));
	// thay doi vi tri cac ong nuoc 
	for (int i = 0; i < soOngNuoc; i++)
	{
		ongNuocThu[i].x -= 3;
	}

	// tao ong nuoc moi
	if (ongNuocThu[0].x <= 0)
	{
		for (int i = 0; i <= soOngNuoc - 2; i++)
		{
			ongNuocThu[i].x = ongNuocThu[i + 1].x;
			ongNuocThu[i].doDai = ongNuocThu[i + 1].doDai;
		}
	}
	ongNuocThu[soOngNuoc - 1].x = ongNuocThu[soOngNuoc - 2].x + khoangCach2OngNuoc;
	ongNuocThu[soOngNuoc - 1].doDai = rand() % ( ConsoleHeight - 10 - khoangCachOngTrenVaDuoi - 10 + 1 ) + 10;
	
}

void xuLyFlappyBird()
{
	if (GetAsyncKeyState(VK_SPACE)) // Player nhan phim SPACE
	{
		PlaySound(TEXT("sound\\sfx_wing.wav"), NULL, SND_ASYNC);
		buocNhay = 7;
	}
	
	if (buocNhay > 0) {
		
		birdY -= buocNhay; //  <==> birdY = birdY - buocNhay
		buocNhay--; 
	}
	else
	{
		birdY += 4;
	}
	if (buocNhay < 5) { buocNhay = 0; }
	if (birdY < 0) { birdY = 0; }
}

bool kiemTraGameOver()
{
/*
			| |
			| |
bien tren->	| |
			
			=@>
bien duoi->
			| |
			| |
			| |
*/
	
	int bienTren, bienDuoi; // bienDuoi = bienTren + khoangCachOngTrenVaDuoi

	if (birdY + birdHeight >= ConsoleHeight-1) return true;

	for (int i = 0; i < soOngNuoc; i++)
	{
		bienTren = ongNuocThu[i].doDai;
		bienDuoi = ongNuocThu[i].doDai + khoangCachOngTrenVaDuoi;

		
		// kiem tra tang diemPlayer
		if ((ongNuocThu[i].x > birdX) && (ongNuocThu[i].x <= (birdX + birdWidth)))
		{
			 dangQua = true;
			
		}
		if ((dangQua == true)&&(ongNuocThu[i].x < birdX ))
		{
			diemPlayer++;
			PlaySound(TEXT("sound\\sfx_point.wav"), NULL, SND_ASYNC);
			dangQua = false;
		}
		// kiem tra dung ong nuoc
		if ((ongNuocThu[i].x > birdX ) && (ongNuocThu[i].x < (birdX + birdWidth) ) && ((bienTren > birdY) || (bienDuoi < (birdY+ birdHeight))))  
		{
			
			PlaySound(TEXT("sound\\sfx_hit.wav"), NULL, SND_ASYNC);
			return true;
		}
		
		
	}
	
	// nhan ESC de quay tro lai man hinh chinh
		if (GetAsyncKeyState(VK_ESCAPE)) 
		{
			caiDat();
			viTriChon = 0;
			luaChonMenu();
			
		}
	
	return false;
}

/*void layDuLieuChuSo()
{
	string duLieuMotHang;
	int dong = 0, cot;
	ifstream fileIn;
		fileIn.open("data\\1.txt", ios_base::in);
		while (!fileIn.eof())
		{
			getline(fileIn, duLieuMotHang);// lay so ki tu cua tung hang
			for (cot = 0; cot < duLieuMotHang.length(); cot++)
			{
				char kiTu = duLieuMotHang[cot];
				so[1][dong][cot] = kiTu;

			}

			dong++;

			if (fileIn.eof())
			{
				break;
			}
		}
		a = dong;
		b = cot;
		fileIn.close();
	
}*/

void layDuLieuChuSo()
{
	string duLieuMotHang;
	int dong = 0, cot;
	ifstream fileIn;
	fileIn.open("data\\number.txt", ios_base::in);
	
	char kiTu;
	bool chuaDocXong;
	while (!fileIn.eof())
	{
		
			for (int i = 0; i <=9; i++)
			{
				chuaDocXong = true;
				
				while(chuaDocXong)
				{ 
					if (fileIn.eof()) break;
				
					getline(fileIn, duLieuMotHang);// lay so ki tu cua tung hang
					
					for (cot = 0; cot < duLieuMotHang.length(); cot++)
					{
							kiTu = duLieuMotHang[cot];
						if (kiTu == (i + 48)) // so nguyen i chuyen thanh chu so i thi i + 48
						{
								dong = 0;
								chuaDocXong = false;
								continue;
						}
						else { 
								so[i][dong][cot] = kiTu; 
								
							}

					}
					dong++;
					cout << endl;
				}

			}
		if (fileIn.eof())
		{
			break;
		}
	}
		fileIn.close();
	
}


void veDiemSo(int diem,  int toaDoY)
{
	int diemSoWidth;
	int temp = diem;
	int index = 0; int num[100];
	do
	{
		num[index] = temp % 10;
		temp = temp / 10;
		index++;
	} while (temp != 0);
	diemSoWidth = ChuSoWidth * (index)+(index - 1) * khoangCach2ChuSo;
	int diemSoX = (ConsoleWidth - diemSoWidth) / 2;
	int toaDoX = diemSoX;
	
	SetConsoleColor(cllightyellow, clblack);


	for (int chuSo = index - 1; chuSo >= 0; chuSo--)
	{

		for (int i = 1; i <= ChuSoHeight; i++)
		{

			for (int j = 0; j < ChuSoWidth; j++)
			{
				gotoxy(toaDoX + j, toaDoY + i);
				if (so[num[chuSo]][i][j] == 78) // 78 = 'N' ASCII
				{
					cout << char(219);
				}
				else cout << " ";

			}
		}
		toaDoX = toaDoX + ChuSoWidth + khoangCach2ChuSo;
	}
}

int layDiemCaoNhat()
{
	ifstream fileIn;
	int diem=0;
	fileIn.open("data\\bestScore.txt", ios_base::in);
	while (!fileIn.eof())
	{
		fileIn >> diem;
	}
	fileIn.close();
	return diem;
}


/*========== thiet ke menu ============*/

void layLogoFlappyBird()
{
	string duLieuMotHang;
	ifstream fileIn;
	fileIn.open("data\\logoFlappyBird.txt", ios_base::in);
	int dong = 6;
	SetConsoleColor(cllightyellow, cllightblue);
	while (!fileIn.eof())
	{
		getline(fileIn, duLieuMotHang);
		gotoxy(20, dong);
		cout << duLieuMotHang;
		if (fileIn.eof())
		{
			break;
		}
		dong++;
	}
	fileIn.close();
}

void luaChonMenu()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_UP))
		{
			PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);
			--viTriChon;

			if (viTriChon < 0)
			{
				viTriChon = tongMuc - 1;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);
			++viTriChon;

			if (viTriChon == tongMuc)
			{
				viTriChon = 0;
			}
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);
			exit(0);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);
			if (viTriChon == 0)
			{
				troChoiMoi();
			}
			else if (viTriChon == 1)
			{
				hidecursor();
				vietDiemCaoNhat();

			}
			else if (viTriChon == 2)
			{
				thongTin();
			}
			else if (viTriChon == 3)
			{
				thoat();
			}
			break;
		}

		menuChinh(viTriChon);
		Sleep(100);
	}
}

void menuChinh(int viTriChon)
{
	
	int dong = 0;

	SetConsoleColor(cllightyellow, (viTriChon==0?clpurple:cllightblue));
	string textMenu = "  TRO CHOI MOI  ";
	gotoxy((widthMenu - textMenu.length()) / 2, (heightMenu/2) +dong);
	cout << textMenu; 
	dong += 1;

	SetConsoleColor(cllightyellow, (viTriChon == 1 ? clpurple : cllightblue));
	 textMenu = "  DIEM CAO NHAT  ";
	gotoxy((widthMenu - textMenu.length()) / 2, (heightMenu / 2)+dong);
	cout << textMenu;
	dong += 1;

	SetConsoleColor(cllightyellow, (viTriChon == 2 ? clpurple : cllightblue));
	 textMenu = "  THONG TIN  ";
	gotoxy((widthMenu - textMenu.length()) / 2, (heightMenu / 2)+dong);
	cout << textMenu;
	dong += 1;

	SetConsoleColor(cllightyellow, (viTriChon == 3 ? clpurple : cllightblue));
	textMenu = "  THOAT  ";
	gotoxy((widthMenu - textMenu.length()) / 2, (heightMenu / 2)+dong);
	cout << textMenu;
}

void troChoiMoi()
{

	clrscr(cllightblue);
	caiDatManHinhKhiChoi();
	int tamDung = false;
	khoiTaoGame(); int giaTocRoi = 0; birdY = 0;
	do {
		while (!gameOver && !tamDung)
		{
			clrscr(cllightblue);

			gameOver = kiemTraGameOver();
			if (gameOver == false)
			{
				veFlappyBird(birdX, birdY);
				xuLyFlappyBird();
				if (GetAsyncKeyState(VK_RETURN))
				{
					if (tamDung == false) { tamDung = true; }
				}
				veDiemSo(diemPlayer, toaDoYDiemPlayer);
				veMangOngNuoc();
				xuLyOngNuoc();
				Sleep(10);

				
			}
			else {

				while (birdY != ConsoleHeight - birdWidth + 1)
				{
					clrscr(cllightblue); ; veDiemSo(diemPlayer, toaDoYDiemPlayer);
					birdY = birdY + 1.5 * (++giaTocRoi);

					if (birdY + birdWidth > ConsoleHeight)
					{
						birdY = ConsoleHeight - birdWidth + 1;
					}
					veFlappyBirdDown(birdX, birdY);
					veMangOngNuoc();
				}
				
				PlaySound(TEXT("sound\\sfx_die.wav"), NULL, SND_SYNC);
				velogoGameOver(diemPlayer, diemCaoNhat);
				PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);

				while (true) {
					if (GetAsyncKeyState(VK_RETURN)) // enter
					{
						caiDat();
						viTriChon = 0;
						luaChonMenu();
						Sleep(100);
						break;
					}
				}
			}
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);
			if (tamDung = true) tamDung = false;
		}
	} while (true);
}

void vietDiemCaoNhat()
{
	hidecursor();
	diemCaoNhat = layDiemCaoNhat();
	caiDat();
	SetConsoleColor(cllightgreen,clblack);
	gotoxy((widthMenu - 18) / 2, (heightMenu) / 2 + 1);
	cout << "  DIEM CAO NHAT: " << diemCaoNhat;
	gotoxy((widthMenu - 18) / 2+4, (heightMenu) / 2 + 2);
	nutTroVe();
}
void thongTin()
{
	hidecursor();
	caiDat();
	
	string duLieuMotHang;
	ifstream fileIn;
	fileIn.open("data\\about.txt", ios_base::in);
	SetConsoleColor(clwhite, clblue);
	int dong = 0;
	while (!fileIn.eof())
	{
		getline(fileIn, duLieuMotHang);
		gotoxy((widthMenu - duLieuMotHang.length()) / 2, (heightMenu)/2+dong);
		cout << duLieuMotHang;
		if (fileIn.eof()) {
			gotoxy((widthMenu-10) / 2, (heightMenu) / 2 + dong + 1);
			nutTroVe();
			break;
		}
		else { dong++; }
	}
	
	fileIn.close();
	
	;
}
void thoat()
{
	// thoat chuong trinh
	exit(0);
}

void nutTroVe()
{
	
	SetConsoleColor(cllightyellow, cllightpurple);
	cout << "  TRO VE  ";
	while (true) {
		if (GetAsyncKeyState(VK_RETURN)) // enter
		{
			PlaySound(TEXT("sound\\sfx_swooshing.wav"), NULL, SND_ASYNC);
			caiDat();
			viTriChon = 0;
			luaChonMenu();
			Sleep(100);
			break;
		}
	}
	
}
