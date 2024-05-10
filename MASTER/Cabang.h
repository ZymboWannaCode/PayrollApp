#ifndef HOLLYFPAYROLL_CABANG_H
#define HOLLYFPAYROLL_CABANG_H

void carinamaCabReg(char idcab[], char *namaRegion) {
    dataCabang = fopen("DAT/dataCab.dat", "rb");
    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        if (strcmp(idcab, cabang.id_cabang) == 0) {
            break;
        }
    }
    dataRegion = fopen("DAT/dataReg.dat", "rb");
    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        if (strcmp(cabang.id_region, reg.id) == 0) {
            strcpy(namaRegion, reg.nama);
            break;
        }
    }
    fclose(dataRegion);
    fclose(dataCabang);
}
void carinamaCab(char idcab[], char *namaCab) {
    dataCabang = fopen("DAT/dataCab.dat", "rb");
    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        if (strcmp(idcab, cabang.id_cabang) == 0) {
            strcpy(namaCab, cabang.alamat_cabang);
            break;
        }
    }
    fclose(dataCabang);
}
void carinamaReg(char idReg[], char *namaRegion) {
    dataRegion = fopen("DAT/dataReg.dat", "rb");
    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        if (strcmp(idReg, reg.id) == 0) {
            strcpy(namaRegion, reg.nama);
            break;
        }
    }
    fclose(dataRegion);
}

int checkRegion(char idReg[]) {
    dataRegion = fopen("DAT/dataReg.dat", "rb");    //PENGECEKAN ID REGION
    int found = 0;
    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1){
        if (strcmp(idReg, reg.id) == 0) {
            found = 1;
            break;
        }
    }
    fclose(dataRegion);
    if (found == 1) {
        return 1;
    } else {
        return 0;
    }
}


void createtambahDataCab(int n) {
    cleanKiri();

    char kodecabang[] = "BRC";
    int idterakhir = 0;
    char idReg[10];

    // MEMBUKA FILE DENGAN MODE AB+ UNTUK MENGETAHUI ID TERAKHIR YANG TELAH DITAMBAHKAN
    dataCabang = fopen("DAT/dataCab.dat", "ab+");
    // MEMBACA FILE UNTUK MENDAPATKAN ID CABANG TERAKHIR
    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        // MEMBACA BAGIAN INTEGER DARI STRING ID CABANG KEMUDIAN INTEGER HASIL PEMBACAAN DISIMPAN DI VARIABEL IDTERAKHIR
        sscanf(cabang.id_cabang, "%*[^0-9]%d", &idterakhir);
    }
    fclose(dataCabang);

    dataCabang = fopen("DAT/dataCab.dat", "ab");
    //LOOPING PEMBUATAN ID CABANG SESUAI INPUTAN USER
    for (int i = idterakhir+1; i <= idterakhir+n; i++) {
        //GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(cabang.id_cabang, sizeof(cabang.id_cabang), "%s%d", kodecabang, i);

        SetColor(colorMainText);
        gotoxy(15, 10); printf("ID Cabang");
        gotoxy(15, 12); printf("[   %-27s]", cabang.id_cabang);

        gotoxy(15, 15); printf("ID Region");
        gotoxy(15, 17); printf("[                              ]");

        gotoxy(15, 20); printf("Alamat");
        gotoxy(15, 22); printf("[                              ]");

        SetColor(colorScText);
    ulang:
        //INPUT ID REGION PADA CABANG
        gotoxy(17, 17); getteks(idReg, 6);

        if (checkRegion(idReg) == 1) {
            strcpy(cabang.id_region, idReg);
        } else {
            showMessage("ALERT", "ID Region Tidak Ada");
            gotoxy(17, 17); printf("            ");
            goto ulang;
        }

        //INPUT ALAMAT CABANG
        gotoxy(17, 22); getteks(cabang.alamat_cabang, 25);

        //MENYIMPAN KE DALAM FILE
        fwrite(&cabang, sizeof(cabang), 1, dataCabang);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(dataCabang); //MENUTUP FILE SETELAH DIGUNAKAN
}

//PROSEDUR READ DATA CABANG
void readDataCab() {
    // DEKLARASI VARIABLE LOKAL PADA PROSEDUR YANG AKAN DIGUNAKAN
    char id[] = {"ID"};
    char idRG[] = {"REGION"};
    char addrs[] = {"ALAMAT"};
    int yTeks = 7;
    int i = 1;

    //MEMBUKA FILE DENGAN MODE RB
    dataCabang = fopen("DAT/dataCab.dat", "rb");

    //MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        printTable(15, 92, 4, 38);
        //MEMBACA SELURUH DATA DARI FILE CABANG
        SetColor(colorScText);
        gotoxy(15,5); printf("  %-10s  %-30s  %-30s ",
                             id, idRG, addrs);    //NAMA-NAMA KOLOM
        char name[20];
        carinamaReg(cabang.id_region, name);
        gotoxy(15, yTeks); printf("  %-10s  %-30s  %-30s ",
                                 cabang.id_cabang,
                                 name,
                                 cabang.alamat_cabang);
        if (i % 35 == 0) {
            getch();
            cleanKiri();
            yTeks = 6;
        }
        i++;
        yTeks++;
    }
    fclose(dataCabang);
    getch();
}

//Prosedur update data file
void findCabtoUpd() {
    int found;
    found = 0;
    char idCab[10];

    retype:
    gotoxy(row + 24, 15); getteks(idCab, 6);

    dataCabang = fopen("DAT/dataCab.dat", "rb");
    dataCabangTemp = fopen("TEMP/dataCabTemp.dat", "wb");
    while (found == 0 && fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        if (strcmp(idCab, cabang.id_cabang) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
        }
    }
    if (found == 1) {
        cleanKiri();
        SetColor(colorMainText);
        gotoxy(5, 3); printf("ID Cabang");
        gotoxy(5+50, 3); printf(": %-40s", cabang.id_cabang);

        gotoxy(5, 5); printf("ID Region");
        gotoxy(5+50, 5); printf(": %-40s", cabang.id_region);

        gotoxy(5, 7); printf("Alamat");
        gotoxy(5+50, 7); printf(": %-36s", cabang.alamat_cabang);

        SetColor(colorHeadText);
        gotoxy(5, 13); printf(">>         MASUKKAN DATA YANG BARU         <<");

        SetColor(colorMainText);
        gotoxy(5, 17); printf("ID Cabang");
        gotoxy(57, 17); printf("   %-26s ", cabang.id_cabang);
        printKotak(40,1,55,17);

        gotoxy(5, 22); printf("ID Region");
        gotoxy(55, 22); printf(":   %-26s ", " ");
        printKotak(40,1,55,22);

        gotoxy(5, 27); printf("Alamat");
        gotoxy(55, 27); printf(":   %-26s ", " ");
        printKotak(40,1,55,27);
        
        char ID[10];

        SetColor(colorScText);
    reType:
        gotoxy(58, 22); getteks(ID, 6);

        if (checkRegion(ID) != 1) {
            showMessage("ALERT", "ID Region Tidak Ada");
            gotoxy(58, 22); printf("         ");
            goto reType;
        }

        //INPUT ALAMAT CABANG
        char almttemp[20];
        gotoxy(58, 27); getteks(almttemp, 25);

        if (doaction("UBAH DATA") == 1) {
            strcpy(cabang.id_cabang, cabang.id_cabang);
            strcpy(cabang.id_region, ID);
            strcpy(cabang.alamat_cabang, almttemp);
            fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
                fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            //Menyimpan nama kota yang baru ke dalam file
            fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
                fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Cabang tidak ditemukan/tidak ada");
        gotoxy(row + 24, 15); printf("      ");
        goto retype;
    }
    fclose(dataCabang);
    fclose(dataCabangTemp);
}
void updateDataCab() {
    findCabtoUpd();
    dataCabang = fopen("DAT/dataCab.dat", "wb");
    dataCabangTemp = fopen("TEMP/dataCabTemp.dat", "rb");
    while (fread(&cabang, sizeof(cabang), 1, dataCabangTemp)==1) {
        fwrite(&cabang, sizeof(cabang), 1, dataCabang);
    }
    fclose(dataCabang);
    fclose(dataCabangTemp);
}

//Prosedur delete data dalam file
void findCabtoDel() {
    int found;
    found = 0;
    char ID[10];

    retype:
    gotoxy(row + 24, 15); getteks(ID, 6);

    dataCabang = fopen("DAT/dataCab.dat", "rb");
    dataCabangTemp = fopen("TEMP/dataCabTemp.dat", "wb");
    while (found == 0 && fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        if (strcmp(ID, cabang.id_cabang) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
        }
    }
    if (found == 1) {
        if (deleteData() == 1) {
            while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
                fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            } showMessage("ATTENTION!!", "Data berhasil dihapus!");
        } else {
            fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
                fwrite(&cabang, sizeof(cabang), 1, dataCabangTemp);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Cabang tidak ditemukan/tidak ada");
        gotoxy(row + 24, 15); printf("      ");
        goto retype;
    }
    fclose(dataCabang);
    fclose(dataCabangTemp);
}
void deleteDataCab() {
    findCabtoDel();
    dataCabang = fopen("DAT/dataCab.dat", "wb");
    dataCabangTemp = fopen("TEMP/dataCabTemp.dat", "rb");
    while (fread(&cabang, sizeof(cabang), 1, dataCabangTemp)==1) {
        fwrite(&cabang, sizeof(cabang), 1, dataCabang);
    }
    fclose(dataCabang);
    fclose(dataCabangTemp);
}

#endif //HOLLYFPAYROLL_CABANG_H
