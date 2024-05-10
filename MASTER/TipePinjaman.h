#ifndef HOLLYFPAYROLL_TIPEPINJAMAN_H
#define HOLLYFPAYROLL_TIPEPINJAMAN_H

char kodeTipePinjaman[] = {"TP"};

void createTipePinjaman(int n) {
    cleanKiri();

    int idterakhir = 0;
    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "ab+");
    while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
        sscanf(tipePinjam.id_tipePinjaman, "%*[^0-9]%d", &idterakhir);
    }
    fclose(data_tipePinjaman);

    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "ab");
    for (int i = idterakhir + 1; i <= idterakhir + n; i++) {
        snprintf(tipePinjam.id_tipePinjaman, sizeof(tipePinjam.id_tipePinjaman), "%s%d", kodeTipePinjaman, i);

        SetColor(colorMainText);
        gotoxy(15, 10); printf("Tipe Pinjam");
        gotoxy(15, 12); printf("[   %-16s ]", tipePinjam.id_tipePinjaman);

        gotoxy(15, 15); printf("Batas Pinjaman");
        gotoxy(15, 17); printf("[ Rp.                ]");

        gotoxy(15, 20); printf("Durasi Tempo");
        gotoxy(15, 22); printf("[               Hari ]");

        SetColor(colorScText);
        getRp(&tipePinjam.max_tipePinjaman, 3, 8, 21, 17);
        gotoxy(17, 22); getnum(&tipePinjam.durasiPinjam, 3);

        fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(data_tipePinjaman);
}
void readTipePijaman() {
    int yTeks = 7;
    char batas[20];

    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "rb");
    if (data_tipePinjaman == NULL) {
        showMessage("ALERT!", "DATA MASIH KOSONG!");
    }

    gotoxy(0, 5); SetColor(colorScText);
    gotoxy(25, 5); printf("  %-10s  %-20s  %-40s ", "ID", "BATAS PINJAM", "DURASI TEMPO");
    while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
        rupiah(tipePinjam.max_tipePinjaman, batas);
        gotoxy(25, yTeks); printf("  %-10s  Rp. %-16s  %-10d%-20s ", tipePinjam.id_tipePinjaman, batas, tipePinjam.durasiPinjam, "Hari");
        yTeks++;
    }
    fclose(data_tipePinjaman);
    printTable(25, 82, 4, 38);
}

void findTipePinjamtoUpd() {
    int found;
    found = 0;
    char No[15];

    retype:
    gotoxy(row + 28, 15); getteks(No, 4);

    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "rb");
    data_tipePinjaman_temp = fopen("TEMP/datatipePinjamanTEMP.dat", "wb");

    while (found == 0 && fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
        if (strcmp(No, tipePinjam.id_tipePinjaman) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
        }
    }
    if (found == 1) {
        int leftMarg = 5;
        cleanKiri();
        SetColor(colorMainText);
        gotoxy(leftMarg, 3); printf("Tipe Pinjaman");
        gotoxy(leftMarg+50, 3); printf("| %-40s|", tipePinjam.id_tipePinjaman);

        gotoxy(leftMarg, 5); printf("Batas Pinjam");
        gotoxy(leftMarg+50, 5); printf("| %-40d|", tipePinjam.max_tipePinjaman);

        gotoxy(leftMarg, 7); printf("ID Jabatan");
        gotoxy(leftMarg+50, 7); printf("| %-40d|", tipePinjam.durasiPinjam);

        SetColor(colorHeadText);
        gotoxy(leftMarg, 13); printf(">>         MASUKKAN DATA YANG BARU         <<");

        SetColor(colorMainText);
        gotoxy(5, 17); printf("Tipe Pinjam");
        gotoxy(55, 17); printf("[   %-16s ]", tipePinjam.id_tipePinjaman);

        gotoxy(5, 22); printf("Batas Pinjaman Terbaru");
        gotoxy(55, 22); printf("[ Rp.                ]");

        gotoxy(5, 27); printf("Durasi Tempo Terbaru");
        gotoxy(55, 27); printf("[               Hari ]");

        SetColor(colorScText);
        int jmltemp, tempotemp;
        getRp(&jmltemp, 3, 8, 61, 22);
        gotoxy(57, 27); getnum(&tempotemp, 3);

        if (doaction("UBAH DATA") == 1) {
            strcpy(tipePinjam.id_tipePinjaman, tipePinjam.id_tipePinjaman);
            tipePinjam.max_tipePinjaman = jmltemp;
            tipePinjam.durasiPinjam = tempotemp;
            fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
            while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
                fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
            }
        } else {
            fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
            while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
                fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Tipe Pinjam tidak ditemukan/tidak ada");
        gotoxy(row + 28, 15); printf("    ");
        goto retype;
    }
    fclose(data_tipePinjaman);
    fclose(data_tipePinjaman_temp);
}
void updateTipePinjaman() {
    findTipePinjamtoUpd();

    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "wb");
    data_tipePinjaman_temp = fopen("TEMP/datatipePinjamanTEMP.dat", "rb");

    while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp) == 1) {
        fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman);
    }
    fclose(data_tipePinjaman);
    fclose(data_tipePinjaman);
}

void findTipePinjamtoDel() {
    int found;
    found = 0;
    char No[15];

    retype:
    gotoxy(row + 28, 15); getteks(No, 4);

    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "rb");
    data_tipePinjaman_temp = fopen("TEMP/datatipePinjamanTEMP.dat", "wb");

    while (found == 0 && fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
        if (strcmp(No, tipePinjam.id_tipePinjaman) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
        }
    }
    if (found == 1) {
        if (deleteData() == 1) {
            while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
                fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
            } showMessage("ATTENTION!!", "Data berhasil dihapus!");
        } else {
            fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp);
        }

    }
    else {
        showMessage("ALERT!", "ID Tipe Pinjam tidak ditemukan/tidak ada");
        gotoxy(row + 28, 15); printf("    ");
        goto retype;
    }
    fclose(data_tipePinjaman);
    fclose(data_tipePinjaman_temp);
}
void deleteTipePinjaman() {
    findTipePinjamtoDel();

    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "wb");
    data_tipePinjaman_temp = fopen("TEMP/datatipePinjamanTEMP.dat", "rb");

    while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman_temp) == 1) {
        fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman);
    }
    fclose(data_tipePinjaman);
    fclose(data_tipePinjaman);
}

#endif //HOLLYFPAYROLL_TIPEPINJAMAN_H
