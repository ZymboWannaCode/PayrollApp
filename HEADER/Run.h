#ifndef HOLLYFPAYROLL_RUN_H
#define HOLLYFPAYROLL_RUN_H

void mainPage() {
    SetColor(text2);
    Sleep(10);
    printASCII(201, 0,0);
    printASCII(187, maxWidht,0);
    for (int i = 1; i < maxWidht; i++) {
        printASCII(205, i, 0);
        printASCII(205, maxWidht-i, maxHeight);
    }
    printASCII(200, 0,maxHeight);
    printASCII(188, maxWidht,maxHeight);
    for (int j = 1; j < maxHeight; j++) {
        printASCII(186, maxWidht, j);
        printASCII(186, 0, maxHeight-j);
        Sleep(10);
    }

    SetColor(colorMainText);
    Sleep(100);
    PrintFile("Txt/template.txt", 45, 6);
    PrintFile("Txt/hollyfoodasciiart.txt", 50, 12);

    Sleep(100);
    gotoxy(70, 40); printf("Press any key to next...");
    getch();
    system("cls");
}
void loginPage() {
    templateUI();
    SetColor(colorMainText);
    for (int j = 10; j < 31; j++) {
        printASCII(179, row-2, j);
        printASCII(179, row+22, j);
    }
    gotoxy(row+3, 15); printf("USER");
    gotoxy(row+3, 20); printf("PASSWORD");

    printKotak(16, 1, row+2, 17);
    printKotak(16, 1, row+2, 22);

    SetColor(colorHeadText);
    gotoxy(row-2, 10); printf("          LOGIN          ");
    gotoxy(row-2, 31); printf("                         ");
}
void logIn(char* iDEmp, char* Passwd) {
    loginPage();
    SetColor(colorScText);
    gotoxy(row+4, 17); getteks(iDEmp, 10);
    gotoxy(row+4, 22); getpass(Passwd, 8);
}
void checkLogin(char idEMP[], char pass[], int *acc, char* idjab, char* idCab) {
    int found = 0;
    if (strcmp(idEMP, "admin") == 0 && strcmp(pass, "admin") == 0) {
        *acc = 2;
    } else {
        dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
        while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
            if (strcmp(idEMP, karyawan.id_karyawan) == 0) {
                found = 1;
                break;
            }
        }
        if (found == 1 && strcmp(pass, karyawan.password) == 0) {
            *acc = 1;
            strcpy(idjab, karyawan.id_jabatan);
            strcpy(idCab, karyawan.id_cabang);
        } else {
            *acc = 3;
        }
        fclose(dataKaryawan);
    }
}

void karyawanMenuCuti(char idEMP[]) {
    cleanKanan();

    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>    PENGAJUAN CUTI    <<");


    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Tgl awal Cuti [DD-MM-YYYY]");
    printKotak(25, 1, row+8, 12);

    gotoxy(row+8, 15); printf("Lama Cuti");
    gotoxy(row+8, 17); printf("                    Hari  ");
    printKotak(25, 1, row+8, 17);

    gotoxy(row+8, 20); printf("Keterangan");
    printKotak(25, 1, row+8, 22);

    if (doactionFitur("CUTI") == 1) {
        templateUI2();
        ajukanCuti(idEMP);
        cleanKiri();
    }
    readtrCuti(idEMP);
    getch();
    popUpCuti(sisaCuti(idEMP));
    system("cls");
}
void karyawanMenuLEMBUR(char idEMP[]) {
    cleanKanan();

    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>   PENGAJUAN LEMBUR   <<");

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Tanggal Lembur [DD-MM-YYYY]");
    printKotak(25, 1, row+8, 12);

    gotoxy(row+8, 15); printf("Lama Lembur");
    gotoxy(row+8, 17); printf("                 Jam     ");
    printKotak(25, 1, row+8, 17);

    if (doaction("LEMBUR") == 1) {
        templateUI2();
        ajukanLembur(idEMP);
        cleanKiri();
    }
    readPengajuanLembur(idEMP);
    getch();
    system("cls");
}

void karyawanreadGaji(char id[]) {
    cleanKanan();
    char blnGaji[13];

    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>    LIHAT SLIP GAJI   <<");

    SetColor(colorMainText);
    gotoxy(row+9, 13); printf("Periode Gaji [DD-MM-YYYY]");
    printKotak(20, 1, row+11, 16);

    gotoxy(row+13, 16); getDate(blnGaji);

    system("cls");
    frame();

    SetColor(colorMainText);
    PrintFile("TXT/profile.txt", 121, 3);
    PrintFile("TXT/slip.txt", 8, 2);

    int x = 20;
    gotoxy(118, x); printf("ID");
    gotoxy(118, x+2); printf("NAMA");
    gotoxy(118, x+4); printf("JABATAN");
    gotoxy(118, x+6); printf("CABANG");
    gotoxy(118, x+8); printf("REGION");
    gotoxy(118, x+10); printf("TGL GAJI");

    gotoxy(10, 15); printf("GAJI POKOK");
    gotoxy(10, 18); printf("TUNJANGAN");
    gotoxy(10, 21); printf("BONUS");
    gotoxy(10, 24); printf("UPAH LEMBUR");
    gotoxy(10, 30); printf("TOTAL GAJI");
    gotoxy(10, 33); printf("POTONGAN");
    gotoxy(10, 38); printf("GAJI DITERIMA");

    for (int i = 10; i < 100; i++) {
        printASCII(196, i, 27);
        printf(" +");
    }
    for (int i = 10; i < 100; i++) {
        printASCII(196, i, 36);
        printf(" -");
    }

    lihatSlipGaji(id, blnGaji);
    system("cls");
}
void karyawanMenuPINJAM(char idEMP[]) {
    cleanKanan();

    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    gotoxy(row+3, 2); SetColor(colorHeadText); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>       PINJAMAN       <<");

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Jumlah Pinjam");
    gotoxy(row+8, 12); printf("  Rp.                     ");
    printKotak(25, 1, row+8, 12);

    gotoxy(row+8, 15); printf("Besar Bunga");
    printKotak(25, 1, row+8, 17);

    gotoxy(row+8, 20); printf("Jatuh Tempo");
    printKotak(25, 1, row+8, 22);

    if (doactionFitur("PINJAM") == 1) {
        templateUI2();
        ajukanPinjaman(idEMP);
    } else {
        char rp[10];
        rupiah(totalPinjam(idEMP), rp);
        popUpPinjam(rp);
    }
    readPinjaman(idEMP);
    getch();
    system("cls");
}
void karyawanMenuKLAIM(char idEMP[]) {
    cleanKanan();

    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>    KLAIM ASURANSI    <<");

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Jumlah Claim");
    gotoxy(row+8, 12); printf("  Rp.                     ");
    printKotak(25, 1, row+8, 12);

    gotoxy(row+8, 15); printf("Tempat Claim");
    printKotak(25, 1, row+8, 17);

    gotoxy(row+8, 20); printf("Keterangan Claim");
    printKotak(25, 1, row+8, 22);

    if (doactionFitur("KLAIM") == 1) {
        templateUI2();
        ajukanClaim(idEMP);
    }
    readClaim(idEMP);
    getch();
    char rp[10];
    rupiah(sisaPlafon(idEMP), rp);
    popUpPlafon(rp);
    system("cls");
}
void karyawanMenu(char ID[], int *out) {
    system("cls");
    int pil = 1;
    int submenu = 0;
    *out = 0;

    templateUI2();
    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row + 2, 2); printf("   %-35s", kar);
    gotoxy(row + 2, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row + 5, 6); printf(">  LIHAT SLIP GAJI");
    gotoxy(row + 5, 8); printf(">  PENGAJUAN CUTI");
    gotoxy(row + 5, 10); printf(">  PENGAJUAN LEMBUR");
    gotoxy(row + 5, 12); printf(">  PENGAJUAN PINJAMAN");
    gotoxy(row + 5, 14); printf(">  KLAIM ASURANSI");
    gotoxy(row + 5, 16); printf(">  LOGOUT");
    showMessage("WELCOME!", "\tAnda Login Sebagai Karyawan!\t");

    int banyakMenu = 6;
    while (!submenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+27, 6 + (i-1) * 2);
                printASCII(174, row+28, 6 + (i-1) * 2);
                printASCII(174, row+29, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 27, 6 + (i-1) * 2);
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
                submenu = pil;
                break;
        }
    }
    switch (submenu) {
        case 1:
            karyawanreadGaji(ID);
            karyawanMenu(ID, out);
            break;
        case 2:
            karyawanMenuCuti(ID);
            karyawanMenu(ID, out);
            break;
        case 3:
            karyawanMenuLEMBUR(ID);
            karyawanMenu(ID, out);
            break;
        case 4:
            karyawanMenuPINJAM(ID);
            karyawanMenu(ID, out);
            break;
        case 5:
            karyawanMenuKLAIM(ID);
            karyawanMenu(ID, out);
            break;
        case 6:
            if (keluar() == 1) {
                *out = 1;
            } else {
                *out = 0;
                karyawanMenu(ID, out);
                break;
            }
    }
}

void karyawanMenuOther(char ID[], int *out) {
    system("cls");
    int pil = 1;
    int submenu = 0;
    *out = 0;

    templateUI2();
    char kar[] = "W E L C O M E  K A R Y A W A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row + 2, 2); printf("   %-35s", kar);
    gotoxy(row + 2, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row + 5, 6); printf(">  LIHAT SLIP GAJI");
    gotoxy(row + 5, 8); printf(">  PENGAJUAN CUTI");
    gotoxy(row + 5, 10); printf(">  KLAIM ASURANSI");
    gotoxy(row + 5, 12); printf(">  LOGOUT");
    showMessage("WELCOME!", "\tAnda Login Sebagai Karyawan!\t");

    int banyakMenu = 4;
    while (!submenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+27, 6 + (i-1) * 2);
                printASCII(174, row+28, 6 + (i-1) * 2);
                printASCII(174, row+29, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 27, 6 + (i-1) * 2);
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
                submenu = pil;
                break;
        }
    }
    switch (submenu) {
        case 1:
            karyawanreadGaji(ID);
            karyawanMenuOther(ID, out);
            break;
        case 2:
            karyawanMenuCuti(ID);
            karyawanMenuOther(ID, out);
            break;
        case 3:
            karyawanMenuKLAIM(ID);
            karyawanMenuOther(ID, out);
            break;
        case 4:
            if (keluar() == 1) {
                *out = 1;
            } else {
                *out = 0;
                karyawanMenuOther(ID, out);
                break;
            }
    }
}
void manajerMenuACCLbr(char Branch[]) {
    cleanKanan();

    char kar[] = "W E L C O M E  M A N A G E R";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>   APPROVAL LEMBUR    <<");

    SetColor(colorMainText);
    if (doactionFitur("APPROVAL") == 1) {
        templateUI2();
        approvalLembur(Branch);
    }
    readPengajuanLemburALL();
    getch();
    system("cls");
}
void manajerMenuUpd(char Branch[]) {
    cleanKanan();

    char kar[] = "W E L C O M E  M A N A G E R";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>    KINERJA KARYAWAN    <<");

    SetColor(colorMainText);
    if (doactionUpdMr() == 1) {
        templateUI2();
        SetColor(colorMainText);
        gotoxy(row+7, 13); printf("Tanggal Upd Rating [DD-MM-YYYY]");
        printKotak(20, 1, row+12, 16);
        updateRatingKrywn(Branch);
    }
    readMonthlyRating(Branch);
//    getch();
}
void manajerMenuLihatKinerja() {
    cleanKanan();

    templateUI2();
    char kar[] = "W E L C O M E  M A N A J E R";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">> LIHAT LAPORAN KINERJA <<");

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("BULAN     ");
    printKotak(15, 1, row+19, 10);
    gotoxy(row+8, 15); printf("TAHUN     ");
    printKotak(15, 1, row+19, 15);
    gotoxy(row+8, 12); printf("\x1B[3mContoh: September = 09.\x1B[0m\n");

    int sasi, taun, hr, bl, th;
    char tglSekarang[15];
    gettodayDate(tglSekarang);
    bulanTahun(tglSekarang, &hr,&bl,&th);

    SetColor(colorScText);
    gotoxy(row+22, 10); getnum(&sasi, 2);
    gotoxy(row+22, 15); getnum(&taun, 4);

    if (taun == th && sasi > bl) {
        showMessage("ALERT", "BULAN ATAU TAHUN TIDAK VALID!");
    } else if (taun > th) {
        showMessage("ALERT", "BULAN ATAU TAHUN TIDAK VALID!");
    } else {
        cleanKiri();
        SetColor(colorMainText);
        laporanKinerjaBulanan(sasi, taun);
        getch();
    }
    system("cls");
}
void manajerMenu(char idEmp[], int *out, char Cab[]) {
    system("cls");
    int menu = 0;
    *out = 0;

    templateUI2();
    char man[] = "W E L C O M E  M A N A J E R";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", man);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  UPDATE KINERJA STAFF");
    gotoxy(row+5, 8); printf(">  ACC PENGAJUAN LEMBUR");
    gotoxy(row+5, 10); printf(">  LIHAT LAPORAN KINERJA");
    gotoxy(row+5, 12); printf(">  LOGOUT");
    showMessage("WELCOME!", "\tAnda Login Sebagai Manajer!\t");

    int pil = 1;
    int banyakMenu = 4;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            int xChoose = 33;
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row + xChoose, 6 + (i - 1) * 2);
                printASCII(174, row + xChoose +1, 6 + (i - 1) * 2);
                printASCII(174, row + xChoose +2, 6 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + xChoose, 6 + (i - 1) * 2);
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
                menu = pil;
                break;
        }
    }
    switch (menu) {
        case 1:
            manajerMenuUpd(Cab);
            manajerMenu(idEmp, out, Cab);
            break;
        case 2:
            manajerMenuACCLbr(Cab);
            manajerMenu(idEmp, out, Cab);
            break;
        case 3:
            manajerMenuLihatKinerja();
            manajerMenu(idEmp, out, Cab);
            break;
        case 4:
            if (keluar() == 1) {
                *out = 1;
            } else {
                *out = 0;
                manajerMenu(idEmp, out, Cab);
            } break;
    }
}

void financeMenuACCClaim(char Branch[]) {
    cleanKanan();

    templateUI2();
    char kar[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>  APPROVAL ASURANSI  <<");

    SetColor(colorMainText);
    if (doactionFitur("APPROVAL") == 1) {
        templateUI2();
        approvalClaimFinal(Branch);
    }
    readClaimALL();
    getch();
    system("cls");
}
void financeMenuACCPinjaman(char Branch[]) {
    cleanKanan();

    templateUI2();
    char kar[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>  APPROVAL PINJAMAN   <<");

    SetColor(colorMainText);
    if (doactionFitur("APPROVAL") == 1) {
        templateUI2();
        accUpdPinjaman(Branch);
    }
    readPinjamanALL();
    getch();
    system("cls");
}
void financeMenuTfGaji(char Branch[]) {
    templateUI2();
    char kar[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    if (doaction("GAJIAN") == 1) {
        cleanKanan();
        templateUI2();

        SetColor(colorHeadText);
        gotoxy(row+8, 8); printf(">>      BUAT GAJI       <<");

        SetColor(colorMainText);
        gotoxy(row+9, 13); printf("Tanggal Gajian [DD-MM-YYYY]");
        printKotak(20, 1, row+11, 16);

        gajiBulanan(Branch);
    }
    system("cls");
}
void financeMenuLihatGaji() {
    cleanKanan();

    templateUI2();
    char kar[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">>  LIHAT LAPORAN GAJI  <<");

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("BULAN     ");
    printKotak(15, 1, row+19, 10);
    gotoxy(row+8, 15); printf("TAHUN     ");
    printKotak(15, 1, row+19, 15);
    gotoxy(row+8, 12); printf("\x1B[3mContoh: September = 09.\x1B[0m\n");

    int sasi, taun, hr, bl, th;
    char tglSekarang[15];
    gettodayDate(tglSekarang);
    bulanTahun(tglSekarang, &hr,&bl,&th);

    SetColor(colorScText);
    gotoxy(row+22, 10); getnum(&sasi, 2);
    gotoxy(row+22, 15); getnum(&taun, 4);

    if (taun == th && sasi > bl) {
        showMessage("ALERT", "BULAN ATAU TAHUN TIDAK VALID!");
    } else if (taun > th) {
        showMessage("ALERT", "BULAN ATAU TAHUN TIDAK VALID!");
    } else {
        cleanKiri();
        SetColor(colorMainText);
        readGajiBulan(sasi, taun);
        getch();
    }
    system("cls");
}
void financeMenuUpdBatasPinjam() {
    cleanKiri();
    cleanKanan();

    char hrd[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("ID Tipe Pinjam : [       ]");

    readTipePijaman();
    updateTipePinjaman();
    system("cls");
}
void financeMenuUpdGjPokok() {
    cleanKiri();
    cleanKanan();

    char hrd[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);


    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("ID Region: [       ]");

    readDataReg();
    updateDataReg();
    system("cls");
}
void financeMenuUpdTunj() {
    cleanKiri();
    cleanKanan();

    char hrd[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("ID Jabatan : [            ]");

    readDataJabatan();
    updateDataJabatan();
    system("cls");
}
void financeMenuUpdBonus() {
    cleanKiri();
    cleanKanan();

    char hrd[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Kode Rating : [       ]");

    readRating();
    updateDataRating();
    system("cls");
}
void financeMenu(char idEmp[], int *inout, char Cab[]) {
    system("cls");
    templateUI2();

    char man[] = "W E L C O M E  K E U A N G A N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", man);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 8); printf(">  ACC PINJAMAN");
    gotoxy(row+8, 10); printf(">  ACC KLAIM ASURANSI");
    gotoxy(row+8, 12); printf(">  UPDATE BATAS PINJAMAN");
    gotoxy(row+8, 14); printf(">  UPDATE GAJI POKOK");
    gotoxy(row+8, 16); printf(">  UPDATE TUNJANGAN");
    gotoxy(row+8, 18); printf(">  UPDATE BONUS");
    gotoxy(row+8, 20); printf(">  BUAT GAJIAN");
    gotoxy(row+8, 22); printf(">  LIHAT LAPORAN GAJI");
    gotoxy(row+8, 24); printf(">  LOGOUT");
    showMessage("WELCOME!", "\tAnda Login Sebagai Dept. Keuangan!\t");

    int pil = 1;
    int banyakMenu = 9;
    int submenu = 0;
    while (!submenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row + 35, 8 + (i - 1) * 2);
                printASCII(174, row + 36, 8 + (i - 1) * 2);
                printASCII(174, row + 37, 8 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 35, 8 + (i - 1) * 2);
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
                submenu = pil;
                break;
        }
    }
    switch (submenu) {
        case 1:
            financeMenuACCPinjaman(Cab);
            financeMenu(idEmp, inout, Cab);
            break;
        case 2:
            financeMenuACCClaim(Cab);
            financeMenu(idEmp, inout, Cab);
            break;
        case 3:
            financeMenuUpdBatasPinjam();
            financeMenu(idEmp, inout, Cab);
            break;
        case 4:
            financeMenuUpdGjPokok();
            financeMenu(idEmp, inout, Cab);
            break;
        case 5:
            financeMenuUpdTunj();
            financeMenu(idEmp, inout, Cab);
            break;
        case 6:
            financeMenuUpdBonus();
            financeMenu(idEmp, inout, Cab);
            break;
        case 7:
            financeMenuTfGaji(Cab);
            financeMenu(idEmp, inout, Cab);
            break;
        case 8:
            financeMenuLihatGaji();
            financeMenu(idEmp, inout, Cab);
            break;
        case 9:
            if (keluar() == 1) {
                *inout = 1;
            } else {
                *inout = 0;
                financeMenu(idEmp, inout, Cab);
            } break;
    }
}

void hrdMenuADD() {
    cleanKanan();

    int n;
    char hrd[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 2);

    create_karyawan(n);
    cleanKiri();

    readdataKarywnALL();

    system("cls");
}
void hrdMenuREAD() {
    char man[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readdataKarywnALL();
    getch();
    if (lihatDetilKrywn() == 1) {
        readdataKarywn1();
    }
    system("cls");
}
void hrdMenuUPD() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("ID : [        ]");

    readdataKarywnALL();
    updatedataKarywn();
    readdataKarywnALL();
    getch();
    system("cls");
}
void hrdMenuCRUD() {
    cleanKanan();

    int pil = 1;
    int subMenu = 0;

    templateUI2();
    char hrd[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 6); printf(">  TAMBAH DATA KARYAWAN");
    gotoxy(row+8, 8); printf(">  LIHAT DATA KARYAWAN");
    gotoxy(row+8, 10); printf(">  UPDATE DATA KARYAWAN");
    gotoxy(row + 8, 12); printf(">  KEMBALI");

    int banyakMenu = 4;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+32, 6 + (i-1) * 2);
                printASCII(174, row+33, 6 + (i-1) * 2);
                printASCII(174, row+34, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 32, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            hrdMenuADD();
            hrdMenuCRUD();
            break;
        case 2:
            hrdMenuREAD();
            hrdMenuCRUD();
            break;
        case 3:
            hrdMenuUPD();
            hrdMenuCRUD();
            break;
        case 4:
            cleanKanan();
            break;
    }
}
void hrdMenuLihatKinerja() {
    cleanKanan();

    templateUI2();
    char kar[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", kar);
    gotoxy(row+3, 41); printf("%-38c", space);
    gotoxy(row+8, 5); printf(">> LIHAT LAPORAN KINERJA <<");

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("BULAN     ");
    printKotak(15, 1, row+19, 10);
    gotoxy(row+8, 15); printf("TAHUN     ");
    printKotak(15, 1, row+19, 15);
    gotoxy(row+8, 12); printf("\x1B[3mContoh: September = 09.\x1B[0m\n");

    int sasi, taun, hr, bl, th;
    char tglSekarang[15];
    gettodayDate(tglSekarang);
    bulanTahun(tglSekarang, &hr,&bl,&th);

    SetColor(colorScText);
    gotoxy(row+22, 10); getnum(&sasi, 2);
    gotoxy(row+22, 15); getnum(&taun, 4);

    if (taun == th && sasi > bl) {
        showMessage("ALERT", "BULAN ATAU TAHUN TIDAK VALID!");
    } else if (taun > th) {
        showMessage("ALERT", "BULAN ATAU TAHUN TIDAK VALID!");
    } else {
        cleanKiri();
        SetColor(colorMainText);
        laporanKinerjaBulanan(sasi, taun);
        getch();
    }
    system("cls");
}
void hrdMenu(char idEmp[], int *inout, char Cab[]) {
    system("cls");
    templateUI2();
    char hrd[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  KELOLA DATA KARYAWAN");
    gotoxy(row+5, 8); printf(">  LIHAT KINERJA KARYAWAN");
    gotoxy(row + 5, 10); printf(">  LOGOUT");
    showMessage("WELCOME!", "\tAnda Login Sebagai HRD!\t");

    int pil = 1;
    int menu = 0;
    int banyakMenu = 3;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+30, 6 + (i-1) * 2);
                printASCII(174, row+31, 6 + (i-1) * 2);
                printASCII(174, row+32, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 30, 6 + (i-1) * 2);
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
                menu = pil;
                break;
        }
    }
    switch (menu) {
        case 1:
            hrdMenuCRUD();
            hrdMenu(idEmp, inout, Cab);
            break;
        case 2:
            hrdMenuLihatKinerja();
            hrdMenu(idEmp, inout, Cab);
            break;
        case 3:
            if (keluar() == 1) {
                *inout = 1;
            } else {
                *inout = 0;
                hrdMenu(idEmp, inout, Cab);
            } break;
    }
}

void adminCRUDJabAdd() {
    cleanKanan();

    int n;
    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 1);
    cleanKiri();

    createDataJabatan(n);
}
void adminCRUDJabRead() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readDataJabatan();
    getch();
}
void adminCRUDJabUpd() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Jabatan : [            ]");

    readDataJabatan();
    updateDataJabatan();
    readDataJabatan();
    getch();
}
void adminCRUDJabDel() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      DELETE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Jabatan : [            ]");

    readDataJabatan();
    deleteDataJabatan();
    readDataJabatan();
    getch();
}
void adminCRUDJab() {
    system("cls");
    int pil = 1;
    int subMenu = 0;

    templateUI2();
    char adm[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", adm);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CREATE DATA JABATAN");
    gotoxy(row+5, 8); printf(">  READ DATA JABATAN");
    gotoxy(row+5, 10); printf(">  UPDATE DATA JABATAN");
    gotoxy(row+5, 12); printf(">  DELETE DATA JABATAN");
    gotoxy(row + 5, 14); printf(">  KEMBALI");

    int banyakMenu = 5;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+30, 6 + (i-1) * 2);
                printASCII(174, row+31, 6 + (i-1) * 2);
                printASCII(174, row+32, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 30, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            adminCRUDJabAdd();
            adminCRUDJab();
            break;
        case 2:
            adminCRUDJabRead();
            adminCRUDJab();
            break;
        case 3:
            adminCRUDJabUpd();
            adminCRUDJab();
            break;
        case 4:
            adminCRUDJabDel();
            adminCRUDJab();
            break;
        case 5:
            break;
    }
}

void adminCRUDRegAdd() {
    cleanKanan();

    int n;
    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 1);
    cleanKiri();

    createtambahDataReg(n);
}
void adminCRUDRegRead() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readDataReg();
    getch();
}
void adminCRUDRegUpd() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Region : [            ]");

    readDataReg();
    updateDataReg();
    readDataReg();
    getch();
}
void adminCRUDRegDel() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';
    gotoxy(row+3, 2); SetColor(colorHeadText); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      DELETE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Region : [            ]");

    readDataReg();
    deleteDataReg();
    readDataReg();
    getch();
}
void adminCRUDReg() {
    system("cls");
    int pil = 1;
    int subMenu = 0;

    templateUI2();
    char adm[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", adm);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CREATE DATA REGION");
    gotoxy(row+5, 8); printf(">  READ DATA REGION");
    gotoxy(row+5, 10); printf(">  UPDATE DATA REGION");
    gotoxy(row+5, 12); printf(">  DELETE DATA REGION");
    gotoxy(row + 5, 14); printf(">  KEMBALI");

    int banyakMenu = 5;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+30, 6 + (i-1) * 2);
                printASCII(174, row+31, 6 + (i-1) * 2);
                printASCII(174, row+32, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 30, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            adminCRUDRegAdd();
            adminCRUDReg();
            break;
        case 2:
            adminCRUDRegRead();
            adminCRUDReg();
            break;
        case 3:
            adminCRUDRegUpd();
            adminCRUDReg();
            break;
        case 4:
            adminCRUDRegDel();
            adminCRUDReg();
            break;
        case 5:
            break;
    }
}

void adminMenuCabAdd() {
    cleanKanan();

    int n;
    char adm[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", adm);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 1);

    createtambahDataCab(n);
}
void adminCRUDCabRead() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readDataCab();
    getch();
}
void adminCRUDCabUpd() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Cabang  : [            ]");

    readDataCab();
    updateDataCab();
    readDataCab();
    getch();
}
void adminCRUDCabDel() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      DELETE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Cabang  : [            ]");

    readDataCab();
    deleteDataCab();
    readDataCab();
    getch();
}
void adminCRUDCab() {
    system("cls");
    int pil = 1;
    int subMenu = 0;

    templateUI2();
    char adm[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", adm);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CREATE DATA CABANG");
    gotoxy(row+5, 8); printf(">  READ DATA CABANG");
    gotoxy(row+5, 10); printf(">  UPDATE DATA CABANG");
    gotoxy(row+5, 12); printf(">  DELETE DATA CABANG");
    gotoxy(row + 5, 14); printf(">  KEMBALI");

    int banyakMenu = 5;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+30, 6 + (i-1) * 2);
                printASCII(174, row+31, 6 + (i-1) * 2);
                printASCII(174, row+32, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 30, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            adminMenuCabAdd();
            adminCRUDCab();
            break;
        case 2:
            adminCRUDCabRead();
            adminCRUDCab();
            break;
        case 3:
            adminCRUDCabUpd();
            adminCRUDCab();
            break;
        case 4:
            adminCRUDCabDel();
            adminCRUDCab();
            break;
        case 5:
            break;
    }
}

void adminCRUDRatAdd() {
    cleanKanan();
    templateUI2();

    int n;
    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 1);

    createRating(n);
}
void adminCRUDRatRead() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readRating();
    getch();
}
void adminCRUDRatUpd() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("Kode Rating : [   ]");

    readRating();
    updateDataRating();
    readRating();
    getch();
}
void adminCRUDRatDel() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      DELETE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("Kode Rating : [   ]");

    readRating();
    deleteDataRating();
    readRating();
    getch();
}
void adminCRUDRat() {
    system("cls");
    int pil = 1;
    int subMenu = 0;
    templateUI2();

    char adm[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", adm);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CREATE DATA RATING");
    gotoxy(row+5, 8); printf(">  READ DATA RATING");
    gotoxy(row+5, 10); printf(">  UPDATE DATA RATING");
    gotoxy(row+5, 12); printf(">  DELETE DATA RATING");
    gotoxy(row + 5, 14); printf(">  KEMBALI");

    int banyakMenu = 5;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+30, 6 + (i-1) * 2);
                printASCII(174, row+31, 6 + (i-1) * 2);
                printASCII(174, row+32, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 30, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            adminCRUDRatAdd();
            adminCRUDRat();
            break;
        case 2:
            adminCRUDRatRead();
            adminCRUDRat();
            break;
        case 3:
            adminCRUDRatUpd();
            adminCRUDRat();
            break;
        case 4:
            adminCRUDRatDel();
            adminCRUDRat();
            break;
        case 5:
            break;
    }
}

void adminCRUDEmpAdd() {
    cleanKanan();

    int n;
    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 1);

    create_karyawan(n);
}
void adminCRUDEmpRead() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readdataKarywnALL();
    getch();
    if (lihatDetilKrywn() == 1) {
        readdataKarywn1();
    } system("cls");
}
void adminCRUDEmpUpd() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("ID : [        ]");

    readdataKarywnALL();
    updatedataKarywn();
    readdataKarywnALL();
    getch();
}
void adminCRUDEmpDel() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      DELETE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+10, 15); printf("ID : [        ]");

    readdataKarywnALL();
    deletedataKarywn();
    readdataKarywnALL();
    getch();
}
void adminCRUDEmp() {
    system("cls");

    int pil = 1;
    int subMenu = 0;

    templateUI2();
    char hrd[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CREATE DATA KARYAWAN");
    gotoxy(row+5, 8); printf(">  READ DATA KARYAWAN");
    gotoxy(row+5, 10); printf(">  UPDATE DATA KARYAWAN");
    gotoxy(row+5, 12); printf(">  DELETE DATA KARYAWAN");
    gotoxy(row + 5, 14); printf(">  KEMBALI");

    int banyakMenu = 5;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+32, 6 + (i-1) * 2);
                printASCII(174, row+33, 6 + (i-1) * 2);
                printASCII(174, row+34, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 32, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            adminCRUDEmpAdd();
            adminCRUDEmp();
            break;
        case 2:
            adminCRUDEmpRead();
            adminCRUDEmp();
            break;
        case 3:
            adminCRUDEmpUpd();
            adminCRUDEmp();
            break;
        case 4:
            adminCRUDEmpDel();
            adminCRUDEmp();
            break;
        case 5:
            break;
    }
}

void adminCRUDTPPinjamAdd() {
    cleanKanan();

    int n;
    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+8, 10); printf("Banyak data : [   ]");

    SetColor(colorScText);
    gotoxy(row + 24, 10); getnum(&n, 1);

    createTipePinjaman(n);
}
void adminCRUDTPPinjamRead() {
    char man[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(115, 2); printf("   %-35s", man);
    gotoxy(115, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(123, 35); printf("Press ENTER to next...");

    readTipePijaman();
    getch();
}
void adminCRUDTPPinjamUpd() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Tipe Pinjam : [       ]");

    readTipePijaman();
    updateTipePinjaman();
    readTipePijaman();
    getch();
}
void adminCRUDTPPinjamDel() {
    cleanKanan();

    char hrd[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);
    gotoxy(row+8, 10); printf(">>      UPDATE DATA     <<");

    SetColor(colorMainText);
    gotoxy(row+8, 15); printf("ID Tipe Pinjam : [       ]");

    readTipePijaman();
    deleteTipePinjaman();
    readTipePijaman();
    getch();
}
void adminCRUDTPPinjam() {
    system("cls");
    int pil = 1;
    int subMenu = 0;

    templateUI2();
    char hrd[] = "W E L C O M E  H R D";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", hrd);
    gotoxy(row+3, 41); printf("%38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CREATE DATA TIPE PINJAM");
    gotoxy(row+5, 8); printf(">  READ DATA TIPE PINJAM");
    gotoxy(row+5, 10); printf(">  UPDATE DATA TIPE PINJAM");
    gotoxy(row+5, 12); printf(">  DELETE DATA TIPE PINJAM");
    gotoxy(row + 5, 14); printf(">  KEMBALI");

    int banyakMenu = 5;
    while (!subMenu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+32, 6 + (i-1) * 2);
                printASCII(174, row+33, 6 + (i-1) * 2);
                printASCII(174, row+34, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 32, 6 + (i-1) * 2);
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
                subMenu = pil;
                break;
        }
    }
    switch (subMenu) {
        case 1:
            adminCRUDTPPinjamAdd();
            adminCRUDTPPinjam();
            break;
        case 2:
            adminCRUDTPPinjamRead();
            adminCRUDTPPinjam();
            break;
        case 3:
            adminCRUDTPPinjamUpd();
            adminCRUDTPPinjam();
            break;
        case 4:
            adminCRUDTPPinjamDel();
            adminCRUDTPPinjam();
            break;
        case 5:
            break;
    }
}

void adminMenu(int *out) {
    system("cls");
    int pil = 1;
    int menu = 0;
    *out = 0;

    templateUI2();
    char adm[] = "W E L C O M E  A D M I N";
    char space = ' ';

    SetColor(colorHeadText);
    gotoxy(row+3, 2); printf("   %-35s", adm);
    gotoxy(row+3, 41); printf("%-38c", space);

    SetColor(colorMainText);
    gotoxy(row+5, 6); printf(">  CRUD DATA JABATAN");
    gotoxy(row+5, 8); printf(">  CRUD DATA REGION");
    gotoxy(row+5, 10); printf(">  CRUD DATA CABANG");
    gotoxy(row+5, 12); printf(">  CRUD DATA RATING");
    gotoxy(row+5, 14); printf(">  CRUD DATA KARYAWAN");
    gotoxy(row+5, 16); printf(">  CRUD DATA TIPE PINJAMAN");
    gotoxy(row+5, 18); printf(">  LOGOUT");
    showMessage("WELCOME!", "\tAnda Login Sebagai Admin!\t");

    int banyakMenu = 7;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row+35, 6 + (i-1) * 2);
                printASCII(174, row+36, 6 + (i-1) * 2);
                printASCII(174, row+37, 6 + (i-1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 35, 6 + (i-1) * 2);
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
            case 13:// Tombol Enter
                menu = pil;
                break;
        }
    }
    switch (menu) {
        case 1:
            adminCRUDJab();
            adminMenu(out);
            break;
        case 2:
            adminCRUDReg();
            adminMenu(out);
            break;
        case 3:
            adminCRUDCab();
            adminMenu(out);
            break;
        case 4:
            adminCRUDRat();
            adminMenu(out);
            break;
        case 5:
            adminCRUDEmp();
            adminMenu(out);
            break;
        case 6:
            adminCRUDTPPinjam();
            adminMenu(out);
            break;
        case 7:
            if (keluar() == 1) {
                *out = 1;
            } else {
                *out = 0;
                adminMenu(out);
                break;
            }
    }
}

void pilihRoleKARYAWAN(char id[], int *out) {
    system("cls");

    templateUI();
    SetColor(text2);
    for (int j = 10; j < 31; j++) {
        for (int i = 110; i < 135; i++) {
            printASCII(244, i, j);
        }
    }
    gotoxy(row-2, 10); SetColor(colorHeadText); printf("          LOGIN          ");
    gotoxy(row+16, 25);SetColor(colorMainText);
    gotoxy(row, 13); printf("1. KARYAWAN");

    gotoxy(row-2, 31); SetColor(colorHeadText); printf("                         ");
    gotoxy(row+16, 5);SetColor(colorMainText);

    getch();
    karyawanMenu(id, out);
    system("cls");
}
void pilihRoleHRD(char id[], int *out, char cabang[]) {
    system("cls");

    templateUI();
    SetColor(text2);
    for (int j = 10; j < 31; j++) {
        for (int i = 110; i < 135; i++) {
            printASCII(244, i, j);
        }
    }
    gotoxy(row-2, 10); SetColor(colorHeadText); printf("          LOGIN          ");
    gotoxy(row+16, 25);SetColor(colorMainText);
    gotoxy(row, 13); printf("1. KARYAWAN");
    gotoxy(row, 15); printf("2. HRD");

    gotoxy(row-2, 31); SetColor(colorHeadText); printf("                         ");
    gotoxy(row+16, 5);SetColor(colorMainText);

    int pil = 1;
    int banyakMenu = 2;
    int menu = 0;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row + 18, 13 + (i - 1) * 2);
                printASCII(174, row + 19, 13 + (i - 1) * 2);
                printASCII(174, row + 20, 13 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 18, 13 + (i - 1) * 2);
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
                menu = pil;
                system("cls");
                break;
        }
    }
    switch (menu) {
        case 1:
            karyawanMenuOther(id, out);
            break;
        case 2:
            hrdMenu(id, out, cabang);
            break;
    }
}
void pilihRoleFINANCE(char id[], int *out, char cabang[]) {
    system("cls");

    templateUI();
    SetColor(text2);
    for (int j = 10; j < 31; j++) {
        for (int i = 110; i < 135; i++) {
            printASCII(244, i, j);
        }
    }
    gotoxy(row-2, 10); SetColor(colorHeadText); printf("          LOGIN          ");
    gotoxy(row+16, 25);SetColor(colorMainText);
    gotoxy(row, 13); printf("1. KARYAWAN");
    gotoxy(row, 15); printf("2. DEPT. KEUANGAN");

    gotoxy(row-2, 31); SetColor(colorHeadText); printf("                         ");
    gotoxy(row+16, 5);SetColor(colorMainText);

    int pil = 1;
    int banyakMenu = 2;
    int menu = 0;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row + 18, 13 + (i - 1) * 2);
                printASCII(174, row + 19, 13 + (i - 1) * 2);
                printASCII(174, row + 20, 13 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 18, 13 + (i - 1) * 2);
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
                menu = pil;
                system("cls");
                break;
        }
    }
    switch (menu) {
        case 1:
            karyawanMenuOther(id, out);
            break;
        case 2:
            financeMenu(id, out, cabang);
            break;
    }
}
void pilihRoleMANAGER(char id[], int *out, char cabang[]) {
    system("cls");

    templateUI();
    SetColor(text2);
    for (int j = 10; j < 31; j++) {
        for (int i = 110; i < 135; i++) {
            printASCII(244, i, j);
        }
    }
    gotoxy(row-2, 10); SetColor(colorHeadText); printf("          LOGIN          ");
    gotoxy(row+16, 25);SetColor(colorMainText);
    gotoxy(row, 13); printf("1. KARYAWAN");
    gotoxy(row, 15); printf("2. MANAGER CABANG");

    gotoxy(row-2, 31); SetColor(colorHeadText); printf("                         ");
    gotoxy(row+16, 5);SetColor(colorMainText);

    int pil = 1;
    int banyakMenu = 2;
    int menu = 0;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row + 18, 13 + (i - 1) * 2);
                printASCII(174, row + 19, 13 + (i - 1) * 2);
                printASCII(174, row + 20, 13 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 18, 13 + (i - 1) * 2);
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
                menu = pil;
                system("cls");
                break;
        }
    }
    switch (menu) {
        case 1:
            karyawanMenuOther(id, out);
            break;
        case 2:
            manajerMenu(id, out, cabang);
            break;
    }
}
void pilihRoleADMIN(char id[], int *out, char cabang[]) {
    system("cls");

    templateUI();
    SetColor(text2);
    for (int j = 10; j < 31; j++) {
        for (int i = 110; i < 135; i++) {
            printASCII(244, i, j);
        }
    }
    gotoxy(row-2, 10); SetColor(colorHeadText); printf("          LOGIN          ");
    gotoxy(row+16, 25);SetColor(colorMainText);
    gotoxy(row, 13); printf("1. KARYAWAN");
    gotoxy(row, 15); printf("2. IT ADMIN");

    gotoxy(row-2, 31); SetColor(colorHeadText); printf("                         ");
    gotoxy(row+16, 5);SetColor(colorMainText);

    int pil = 1;
    int banyakMenu = 2;
    int menu = 0;
    while (!menu) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, row + 18, 13 + (i - 1) * 2);
                printASCII(174, row + 19, 13 + (i - 1) * 2);
                printASCII(174, row + 20, 13 + (i - 1) * 2);
            } else {
                SetColor(colorMainText);
                gotoxy(row + 18, 13 + (i - 1) * 2);
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
                menu = pil;
                system("cls");
                break;
        }
    }
    switch (menu) {
        case 1:
            karyawanMenuOther(id, out);
            break;
        case 2:
            adminMenu(out);
            break;
    }
}

void login() {
    int i = 0;
    char ID[10];
    int logout = 0;
    char PASS[10], Jab[10], Cab[10];
    int inOut;

    do {
        logIn(ID, PASS);
        checkLogin(ID, PASS, &inOut, Jab, Cab);
        switch (inOut) {
            case 1:
                if (strcmp(Jab, "JB1") == 0) {
                    pilihRoleKARYAWAN(ID, &logout);
                } else if (strcmp(Jab, "JB2") == 0) {
                    pilihRoleMANAGER(ID, &logout, Cab);
                } else if (strcmp(Jab, "JB3") == 0) {
                    pilihRoleHRD(ID, &logout, Cab);
                } else if (strcmp(Jab, "JB4") == 0) {
                    pilihRoleFINANCE(ID, &logout, Cab);
                } else {
                    pilihRoleADMIN(ID, &logout, Cab);
                }
                break;
            case 2:
                adminMenu(&logout);
                break;
            default:
                i++;
                showMessage("Peringatan!", "\tUser atau Password Salah\t"); //peringatan jika id & pass salah
                gotoxy(row+3, 17); printf("              ");
                gotoxy(row+3, 22); printf("              ");
                if (i >= 5) {
                    logout = 1;
                    system("cls");
                }
        }
    } while(logout == 0);
}

void apk() {
    int keluar = 0;

    fullscreen();
    Sleep(200);
    mainPage();
    login();
    do {
        templateUI();
        SetColor(colorMainText);
        for (int j = 15; j < 26; j++) {
            printASCII(179, row-2, j);
            printASCII(179, row+27, j);
        }
        gotoxy(row+3, 19); printf("L O G I N");
        gotoxy(row+3, 22); printf("K E L U A R");

        SetColor(colorHeadText);
        gotoxy(row-2, 15); printf("                              ");
        gotoxy(row-2, 26); printf("                              ");

        int pil = 1;
        int submenu = 0;
        int banyakMenu = 2;
        while (!submenu) {
            for (int i = 1; i <= banyakMenu; i++) {
                if (i == pil) {
                    SetColor(colorScText);
                    printASCII(174, 132, 19 + (i-1) * 3);
                    printASCII(174, 133, 19 + (i-1) * 3);
                } else {
                    SetColor(colorMainText);
                    gotoxy(132, 19 + (i-1) * 3);
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
                    submenu = pil;
                    system("cls");
                    break;
            }
        }
        switch (submenu) {
            case 1:
                login();
                break;
            case 2:
                keluar = 1;
                break;
        }
    } while (keluar != 1);
}

#endif //HOLLYFPAYROLL_RUN_H
