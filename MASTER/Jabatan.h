#ifndef HOLLYFPAYROLL_JABATAN_H
#define HOLLYFPAYROLL_JABATAN_H

//PROSEDUR CREATE DATA JABATAN
void createDataJabatan(int n) {
    cleanKiri();

    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char kodeJabatan[] = {"JB"};
    int idterakhir = 0;

    File = fopen("DAT/dataJab.dat", "ab+");
    while (fread(&jabatan, sizeof(jabatan), 1, File) == 1){
        sscanf(jabatan.id, "%*[^0-9]%d", &idterakhir);
    }
    fclose(File);

    //Membuka file
    File = fopen("DAT/dataJab.dat", "ab");
    //Looping penambahan karyawan
    for (int i = idterakhir + 1; i <= idterakhir + n; i++) {
        snprintf(jabatan.id, sizeof(jabatan.id), "%s%d", kodeJabatan, i);

        SetColor(colorMainText);
        gotoxy(15, 10); printf("ID Jabatan");
        gotoxy(15, 12); printf("[   %-17s]", jabatan.id);

        gotoxy(15, 15); printf("Nama Jabatan");
        gotoxy(15, 17); printf("[                    ]");

        gotoxy(15, 20); printf("Tunjangan");
        gotoxy(15, 22); printf("[ Rp.                ]");

        SetColor(colorScText);
        gotoxy(17, 17); getteks(jabatan.nama, 15);
        getRp(&jabatan.tunjangan, 5, 8, 21, 22);

        fwrite(&jabatan, sizeof(jabatan), 1, File);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(File);
}
//Prosedur baca file
void readDataJabatan() {
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = {"ID"};
    char nama[] = {"JABATAN"};
    char tunjangan[] = {"TUNJANGAN"};
    int yTeks = 7;
    int i = 1;


    File = fopen("DAT/dataJab.dat", "rb");
    if (File == NULL) {
        printf("Gagal membuka file\n");
    }
    
    //MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
        gotoxy(0, 6); SetColor(colorScText);
        printTable(25, 82, 4, 38);
        gotoxy(25, 5);printf("  %-10s  %-20s  %-20s ", id, nama, tunjangan);
        char tunj[20];
        rupiah(jabatan.tunjangan, tunj);
        gotoxy(25, yTeks); printf("  %-10s  %-20s  Rp. %-16s ", jabatan.id, jabatan.nama, tunj);
        if (i % 35 == 0) {
            getch();
            cleanKiri();
            yTeks = 6; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    fclose(File);
}
//PROSEDUR UPDATE DATA
void findJabatantoUpd() {
    int found;
    found = 0;
    char idJab[10];

    retype:
    gotoxy(row + 24, 15); getteks(idJab, 6);

    File = fopen("DAT/dataJab.dat", "rb");
    Tempfile = fopen("TEMP/dataJabTemp.dat", "wb");

    while (found == 0 && fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
        if (strcmp(idJab, jabatan.id) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
        }
    }

    if (found == 1) {
        cleanKiri();
        SetColor(colorMainText);
        gotoxy(5, 3); printf("ID Jabatan");
        gotoxy(5+50, 3); printf(": %-40s", jabatan.id);

        gotoxy(5, 5); printf("Nama Jabatan");
        gotoxy(5+50, 5); printf(": %-40s", jabatan.nama);

        char gjPokok[20];
        rupiah(jabatan.tunjangan, gjPokok);
        gotoxy(5, 7); printf("Tunjangan");
        gotoxy(5+50, 7); printf(": Rp. %-36s", gjPokok);

        SetColor(colorHeadText);
        gotoxy(5, 13); printf(">>         MASUKKAN DATA YANG BARU         <<");

        SetColor(colorMainText);
        gotoxy(5, 17); printf("ID Jabatan");
        gotoxy(55, 17); printf("   %-30s ", jabatan.id);
        printKotak(40,1,55,17);

        gotoxy(5, 22); printf("Nama Jabatan");
        gotoxy(55, 22); printf("   %-30s ", " ");
        printKotak(40,1,55,22);

        gotoxy(5, 27); printf("Tunjangan Terbaru");
        gotoxy(55, 27); printf("  Rp.                         ");
        printKotak(40,1,55,27);

        SetColor(colorScText);
        char nmJabtemp[20];
        gotoxy(57, 22); getteks(nmJabtemp, 15);
        int tunjtemp;
        getRp(&tunjtemp, 3, 8, 61, 27);

        if (doaction("UBAH DATA") == 1) {
            strcpy(jabatan.id, jabatan.id);
            strcpy(jabatan.nama, nmJabtemp);
            jabatan.tunjangan = tunjtemp;
            fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
                fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
                fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Jabatan tidak ditemukan");
        gotoxy(row + 24, 15); printf("       ");
        goto retype;
    }
    fclose(File);
    fclose(Tempfile);
}
void updateDataJabatan() {
    findJabatantoUpd();
    File = fopen("DAT/dataJab.dat", "wb");
    Tempfile = fopen("TEMP/dataJabTemp.dat", "rb");

    while (fread(&jabatan, sizeof(jabatan), 1, Tempfile)==1) {
        fwrite(&jabatan, sizeof(jabatan), 1, File);
    }

    fclose(File);
    fclose(Tempfile);
}
void findJabatantoDel() {
    int found;
    found = 0;
    char idJab[10];

    retype:
    gotoxy(row + 24, 15); getteks(idJab, 6);

    File = fopen("DAT/dataJab.dat", "rb");
    Tempfile = fopen("TEMP/dataJabTemp.dat", "wb");

    while (found == 0 && fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
        if (strcmp(idJab, jabatan.id) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
        }
    }
    if (found == 1) {
        if (deleteData() == 1) {
            while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
                fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            } showMessage("ATTENTION!!", "Data berhasil dihapus!");
        } else {
            fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
                fwrite(&jabatan, sizeof(jabatan), 1, Tempfile);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Jabatan tidak ditemukan");
        gotoxy(row + 24, 15); printf("       ");
        goto retype;
    }
    fclose(File);
    fclose(Tempfile);
}
void deleteDataJabatan() {
    findJabatantoDel();
    File = fopen("DAT/dataJab.dat", "wb");
    Tempfile = fopen("TEMP/dataJabTemp.dat", "rb");

    while (fread(&jabatan, sizeof(jabatan), 1, Tempfile)==1) {
        fwrite(&jabatan, sizeof(jabatan), 1, File);
    }
    fclose(File);
    fclose(Tempfile);
}

#endif //HOLLYFPAYROLL_JABATAN_H
