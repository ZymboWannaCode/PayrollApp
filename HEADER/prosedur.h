#ifndef UIPRJ_PROSEDUR_H
#define UIPRJ_PROSEDUR_H

const int colorMainText = 10;
const int colorHeadText = 160;
const int colorScText = 11;
const int colorThdText = 112;
const int text2 = 4;
void SetColor(unsigned short color)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleOutput,color);
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void PrintFile(char file[], int x, int y)
{
    FILE *Text;
    char Data[100];
    if((Text=fopen(file, "r")) == NULL)
    {
        system("cls");
    }
    while(fgets(Data, 100, Text))
    {
        gotoxy(x, y);
        printf("%s", Data);
        y++;
    }
    fclose(Text);
}
void showMessage(const char *title, const char *message) {
    MessageBox(NULL, message, title, MB_OK | MB_ICONINFORMATION);
}
void fullscreen()
{
    keybd_event(VK_MENU,0x38,0,0);
    keybd_event(VK_RETURN,0x1c,0,0);
    keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
void cleanKanan() {
    char space = ' ';
    for (int i = 1; i <= 42; i++) {
        gotoxy(113, i);
        printf("%-40c", space);
    }
}
void cleanKiri() {
    char space = ' ';
    for (int i = 1; i < 43; i++) {
        gotoxy(1, i);
        printf("%-110c", space);
    }
}

void printASCII(int code, int x, int y) {
    gotoxy(x, y); printf("%c", code);
}

void gettodayDate(char dateNow[]) {
    // Mendapatkan waktu saat ini
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    // Format tanggal sebagai string DD/MM/YYYY
    sprintf(dateNow, "%02d-%02d-%d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}
int maxWidht = 155;
int maxHeight = 43;

void frame() {
    SetColor(colorMainText);

    printASCII(200, 0,maxHeight);
    printASCII(201, 0,0);
    printASCII(187, maxWidht,0);
    printASCII(188, maxWidht,maxHeight);
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, 0);
        printASCII(205, i, maxHeight);
    }
    for (int i = 1; i < maxHeight; i++) {
        printASCII(186, 112, i);
        printASCII(186, 0, i);
        printASCII(186, maxWidht, i);
    }
    printASCII(203, 112, 0);
    printASCII(202, 112, maxHeight);
}
void templateUI() {
    SetColor(colorMainText);

    PrintFile("Txt/template.txt", 20, 6);
    PrintFile("Txt/food.txt", 112, 33);
    PrintFile("Txt/hollyfoodasciiart.txt", 25, 12);

    printASCII(200, 0,maxHeight);
    printASCII(201, 0,0);
    printASCII(187, maxWidht,0);
    printASCII(188, maxWidht,maxHeight);
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, 0);
    }
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, maxHeight);
    }
    for (int i = 1; i < maxHeight; i++) {
        printASCII(186, 0, i);
        printASCII(186, maxWidht, i);
    }
}
void templateUI2() {
    SetColor(colorMainText);

    PrintFile("Txt/template.txt", 15, 6);
    PrintFile("Txt/hollyfoodasciiart.txt", 25, 12);

    frame();
}

int row = 112;
int keluar() {
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(67, 18); printf("YAKIN MAU LOGOUT?");
    gotoxy(75, 21); printf("YES");
    gotoxy(75, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row -32, 21 + (i - 1) * 2);
                printASCII(174, row -31, 21 + (i - 1) * 2);
                printASCII(174, row -30, 21 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row -32, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                system("cls");
                return pil;
        }
    }
}
int lihatDetilKrywn() {
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(63, 18); printf("LIHAT DETAIL DATA KARYAWAN?");
    gotoxy(75, 21); printf("YES");
    gotoxy(75, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row -32, 21 + (i - 1) * 2);
                printASCII(174, row -31, 21 + (i - 1) * 2);
                printASCII(174, row -30, 21 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row -32, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                return pil;
        }
    }
}
int deleteData() {
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(67, 18); printf("YAKIN HAPUS INI?");
    gotoxy(75, 21); printf("YES");
    gotoxy(75, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row -32, 21 + (i - 1) * 2);
                printASCII(174, row -31, 21 + (i - 1) * 2);
                printASCII(174, row -30, 21 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row -32, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                cleanKiri();
                return pil;
        }
    }
}
int doaction(char text[]) {
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(70, 18); printf("YAKIN MAU %s?", text);
    gotoxy(78, 21); printf("YES");
    gotoxy(78, 23); printf("NO");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, 88, 21 + (i - 1) * 2);
                printASCII(174, 89, 21 + (i - 1) * 2);
                printASCII(174, 90, 21 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(88, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                cleanKiri();
                return pil;
        }
    }
}
int doactionFitur(char text[]) {
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(70, 19); printf("YAKIN MAU %s?", text);
    gotoxy(75, 21); printf("YES");
    gotoxy(68, 23); printf("LIHAT DATA %s", text);

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, 88, 21 + (i - 1) * 2);
                printASCII(174, 89, 21 + (i - 1) * 2);
                printASCII(174, 90, 21 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(88, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                cleanKiri();
                return pil;
        }
    }
}
int doactionUpdMr() {
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(65, 18); printf("YAKIN MAU UPDATE RATING?");
    gotoxy(75, 21); printf("YES");
    gotoxy(70, 23); printf("LIHAT DATA SAJA");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, 88, 21 + (i - 1) * 2);
                printASCII(174, 89, 21 + (i - 1) * 2);
                printASCII(174, 90, 21 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(88, 21 + (i - 1) * 2);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                cleanKiri();
                return pil;
        }
    }
}
void popUpPlafon(char value[]) {
    cleanKiri();
    templateUI2();
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(65, 18); printf("SISA PLAFON ASURANSI ANDA");
    gotoxy(70, 21); printf("Rp. %s", value);
    getchar();
    cleanKiri();
}
void popUpCuti(int value) {
    cleanKiri();
    templateUI2();
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(67, 18); printf("SISA JATAH CUTI ANDA");
    gotoxy(72, 21); printf("%d HARI LAGI", value);
    getchar();
    cleanKiri();
}
void popUpPinjam(char value[]) {
    cleanKiri();
    templateUI2();
    for (int j = 13; j < 27; j++) {
        for (int i = 46; i < 108; i++) {
            gotoxy(i, j); printf(" ");
        }
    }
    SetColor(colorMainText);
    for (int i = 50; i < 105; i++) { // garis H atas
        printASCII(205, i, 15);
    }
    for (int i = 50; i < 105; i++) { // garis H bawah
        printASCII(205, i, 25);
    }
    for (int i = 15; i < 25; i++) { // garis V kanan kiri
        printASCII(186, 50, i);
        printASCII(186, 105, i);
    }
    printASCII(200, 50,25);
    printASCII(201, 50,15);
    printASCII(187, 105,15);
    printASCII(188, 105,25);

    SetColor(colorScText);
    gotoxy(67, 18); printf("TOTAL PINJAMAN ANDA");
    gotoxy(72, 21); printf("Rp. %s", value);
    getchar();
    cleanKiri();
}

void printTable(int btsKiri, int btsKanan, int atas, int bawah) {
    SetColor(colorMainText);
    for (int i = btsKiri; i < btsKanan; i++) {
        printASCII(205, i, atas);
        printASCII(205, i, atas+2);
        printASCII(196, i, bawah);
    }
    SetColor(colorScText);
}
void printKotak(int lebar, int tinggi, int x, int y) {
    SetColor(colorMainText);
    int j = 0;
    for (int i = x; i < x + lebar +1; i++) {
        printASCII(196, i, y-1);
        printASCII(196, i, y + tinggi);
        j++;
    }
    int k = 0;
    for (int i = y; i < y + tinggi; i++) {
        printASCII(179, x, i);
        printASCII(179, x + lebar, i);
        k++;
    }
    printASCII(191, x + lebar, y-1);
    printASCII(218, x, y-1);
    printASCII(217, x+lebar, y+tinggi);
    printASCII(192, x, y+tinggi);
}
int ACC() {
    SetColor(colorMainText);
    for (int i = 120; i < 147; i++) { // garis H atas
        printASCII(205, i, 23);
    }
    for (int i = 120; i < 147; i++) { // garis H bawah
        printASCII(205, i, 30);
    }
    for (int i = 23; i < 30; i++) { // garis V kanan kiri
        printASCII(186, 120, i);
        printASCII(186, 147, i);
    }
    printASCII(200, 120,30);
    printASCII(201, 120,23);
    printASCII(187, 147,23);
    printASCII(188, 147,30);

    SetColor(colorScText);
    gotoxy(125, 25); printf("T E R I M A");
    gotoxy(125, 28); printf("T O L A K");

    int pil = 1;
    int banyakMenu = 2;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                printASCII(174, 140, 25 + (i - 1) * 3);
                printASCII(174, 141, 25 + (i - 1) * 3);
                printASCII(174, 142, 25 + (i - 1) * 3);
            } else {
                gotoxy(140, 25 + (i - 1) * 3);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                cleanKiri();
                return pil;
        }
    }
}
void bulanTahun(char tanggal[], int *hari, int *bulan, int *tahun) {
    sscanf(tanggal, "%d-%d-%d", hari, bulan, tahun);
}

#endif //UIPRJ_PROSEDUR_H
