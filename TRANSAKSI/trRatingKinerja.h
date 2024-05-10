#ifndef HOLLYFPAYROLL_TRRATINGKINERJA_H
#define HOLLYFPAYROLL_TRRATINGKINERJA_H

int updRating() {
    SetColor(text2);
    int lebar = 10;
    int tinggi = 20;
    for (int j = 12; j < 14+tinggi; j++) {
        for (int i = 127; i < lebar+127; i++) {
            printASCII(244, i, j);
        }
    }
    SetColor(colorScText);
    printASCII(200, 126,34);
    printASCII(201, 126,11);
    printASCII(187, 137,11);
    printASCII(188, 137,34);

    SetColor(colorMainText);
    gotoxy(126, 9);printf("UPDATE RATING");
    gotoxy(132, 14); printf("S");
    gotoxy(132, 18); printf("A");
    gotoxy(132, 22); printf("B");
    gotoxy(132, 26); printf("C");
    gotoxy(132, 30); printf("D");

    int pil = 1;
    int banyakMenu = 5;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, 137, 14 + (i - 1) * 4);
                printASCII(174, 138, 14 + (i - 1) * 4);
                printASCII(174, 139, 14 + (i - 1) * 4);
            } else {
                SetColor(colorMainText);
                gotoxy(137, 14 + (i - 1) * 4);
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
int cekAdaMr(char tanggalMR[]) {
    int hr, bl,th;
    int hr2, bl2,th2;
    int fd = 0;
    bulanTahun(tanggalMR, &hr, &bl, &th);
    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "rb");
    while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1) {
        bulanTahun(trRating.tgl, &hr2, &bl2, &th2);
        if (bl == bl2 && th == th2) {
            fd = 1;
            break;
        }
    }
    fclose(dataTrRating);
    if (fd == 1) {
        return 0;
    } else {
        return 1;
    }
}
void updateRatingKrywn(char idBrc[]) {
    int leftMarg  = 5;
    char idMR[] = "MR";
    int idterakhir = 0;
    char tglMR[15];

    gotoxy(row+14, 16); getDate(tglMR);
    cleanKanan();
    if (cekAdaMr(tglMR) == 1) {
        dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
        dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "ab+");
        while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1) {
            sscanf(trRating.idMR, "%*[^0-9]%d", &idterakhir);
        }
        int i = 1;
        while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
            if (strcmp(karyawan.id_cabang, idBrc) == 0 && (strcmp(karyawan.status_karyawan, "aktif") == 0 || strcmp(karyawan.status_karyawan, "Aktif") == 0) && strcmp(karyawan.id_jabatan, "JB1") == 0) {
                cleanKiri();
                SetColor(colorScText);
                gotoxy(5, 5); printf("ID Karyawan");
                gotoxy(5, 7); printf("ID Cabang");
                gotoxy(5, 9); printf("ID Jabatan");
                gotoxy(5, 11); printf("Nama Karyawan");
                gotoxy(5, 13); printf("Tanggal Lahir");
                gotoxy(5, 15); printf("Alamat");
                gotoxy(5, 17); printf("Sex");
                gotoxy(5, 19); printf("Tanggal Mulai Kerja");
                gotoxy(5, 21); printf("Jatah Cuti");
                gotoxy(5, 23); printf("Plafon Asuransi");
                gotoxy(5, 25); printf("Status");

                snprintf(trRating.idMR, sizeof(trRating.idMR), "%s%d", idMR, idterakhir + 1);

                gotoxy(leftMarg+50, 5); printf("| %-40s|", karyawan.id_karyawan);
                gotoxy(leftMarg+50, 7); printf("| %-40s|", karyawan.id_cabang);
                gotoxy(leftMarg+50, 9); printf("| %-40s|", karyawan.id_jabatan);
                gotoxy(leftMarg+50, 11); printf("| %-40s|", karyawan.nama_karyawan);
                gotoxy(leftMarg+50, 13); printf("| %-40s|", karyawan.tanggalLahir_karyawan);
                gotoxy(leftMarg+50, 15); printf("| %-40s|", karyawan.alamat_karyawan);
                gotoxy(leftMarg+50, 17); printf("| %-40s|", karyawan.gender_karyawan);
                gotoxy(leftMarg+50, 19); printf("| %-40s|", karyawan.tgglMulaiKerja_karyawan);
                gotoxy(leftMarg+50, 21); printf("| %-40d|", karyawan.jatahCuti_karyawan);
                gotoxy(leftMarg+50, 23); printf("| %-40d|", karyawan.plafonAsuransi);
                gotoxy(leftMarg+50, 25); printf("| %-40s|", karyawan.status_karyawan);

                strcpy(trRating.idKrywn, karyawan.id_karyawan);
                switch (updRating()) {
                    case 1:
                        strcpy(trRating.kRating,"S");
                        break;
                    case 2:
                        strcpy(trRating.kRating,"A");
                        break;
                    case 3:
                        strcpy(trRating.kRating,"B");
                        break;
                    case 4:
                        strcpy(trRating.kRating,"C");
                        break;
                    case 5:
                        strcpy(trRating.kRating,"D");
                        break;
                }

                strcpy(trRating.tgl, tglMR);

                dataRating = fopen ("DAT/dataRating.dat", "rb");
                while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
                    if (strcmp(trRating.kRating, rating.kode_rating) == 0) {
                        trRating.bonus = rating.bonus_rating;
                        break;
                    }
                }
                fclose(dataRating);

                fwrite(&trRating, sizeof(trRating), 1, dataTrRating);
                idterakhir++;
                i++;
            }
        }
        fclose(dataKaryawan);
        fclose(dataTrRating);
        showMessage("ATTENTION!", "Data Berhasil Disimpan!\nSee You Next Month!");
    } else {
        showMessage("ALERT!", "Rating Bulan Tersebut Sudah Diupdate!");
    }
    cleanKiri();
}
void readMonthlyRating(char idBrc[]) {
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = "ID";
    char kode[] = "RATING";
    char krywn[] = "NAMA";
    char tgl[] = "TANGGAL";
    cleanKiri();


    //MEMBUKA FILE DENGAN MODE RB
    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "rb");
    int i = 1;
    int yTeks = 4;

    while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1) {
        printTable(20, 83, 1, 42);
        gotoxy(0, 3); SetColor(colorScText);
        gotoxy(20, 2); printf("  %-10s  %-20s  %-10s  %-10s ", id, krywn, kode, tgl);
        char namaemp[30];
        cariNamaKaryawan(trRating.idKrywn, namaemp);
        gotoxy(20, yTeks);
        printf("  %-10s  %-20s    %-7s  %-10s ", trRating.idMR, namaemp,
               trRating.kRating,
               trRating.tgl);

        if (i % 35 == 0) {
            getch();
            cleanKiri();
            yTeks = 3;
        }
        i++;
        yTeks++;
    }
    //MENUTUP FILE
    fclose(dataTrRating);

    getch();
    system("cls");
}

#endif //HOLLYFPAYROLL_TRRATINGKINERJA_H
