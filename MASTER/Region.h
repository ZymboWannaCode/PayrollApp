#ifndef HOLLYFPAYROLL_REGION_H
#define HOLLYFPAYROLL_REGION_H

//PROSEDUR CREATE DATA REGION
void createtambahDataReg(int n) {
    cleanKiri();

    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char kodeReg[] = {"REG"};
    int idterakhir = 0;

    //MEMBUKA FILE DENGAN MODE AB+
    dataRegion = fopen("DAT/dataReg.dat", "ab+");
    //MEMBACA FILE UNTUK MENDAPATKAN ID TERAKHIR
    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        sscanf(reg.id, "%*[^0-9]%d", &idterakhir);
    }
    fclose(dataRegion);

    dataRegion = fopen("DAT/dataReg.dat", "ab");
    //INPUT DATA REGION
    for (int i = idterakhir+1; i <= idterakhir+n; i++) {
        snprintf(reg.id, sizeof(reg.id), "%s%d", kodeReg, i);

        SetColor(colorMainText);
        gotoxy(15, 10); printf("ID Region");
        gotoxy(15, 12); printf("[   %-27s]", reg.id);

        gotoxy(15, 15); printf("Nama Region");
        gotoxy(15, 17); printf("[                              ]");

        gotoxy(15, 20); printf("Gaji Pokok");
        gotoxy(15, 22); printf("[ Rp.                          ]");

        SetColor(colorScText);
        gotoxy(17, 17); getteks(reg.nama, 25);  //INPUT NAMA REGION
        getRp(&reg.gaji, 6, 8, 21, 22);  //INPUT GAJI POKOK REGION

        fwrite(&reg, sizeof(reg), 1, dataRegion);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(dataRegion);
}
// PROSEDUR READ FILE
void readDataReg() {
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = {"ID"};
    char nama[] = {"NAMA"};
    char gaji[] = {"GAJI POKOK"};
    int yTeks = 7;

    int i = 1;

    //MEMBUKA FILE DENGAN MODE RB
    dataRegion = fopen("DAT/dataReg.dat", "rb");

    //MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        gotoxy(0, 6); SetColor(colorScText);
        gotoxy(25, 5);printf("  %-10s  %-15s  %-20s ", id, nama, gaji);
        char gjPokok[20];
        rupiah(reg.gaji, gjPokok);
        gotoxy(25, yTeks); printf("  %-10s  %-15s  Rp. %-16s ", reg.id, reg.nama, gjPokok);
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 6;
        }
        printTable(25, 82, 4, 38);
        i++;
        yTeks++;
    }
    fclose(dataRegion);
}
//PROSEDUR UPDATE DATA
void findRegtoUpd() {
    int found;
    found = 0;
    char idReg[10];

    retype:
    gotoxy(row + 24, 15); getteks(idReg, 6);

    dataRegion = fopen("DAT/dataReg.dat", "rb");
    dataRegionTemp = fopen("TEMP/dataRegTemp.dat", "wb");

    while (found == 0 && fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        if (strcmp(idReg, reg.id) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
        }
    }
    if (found == 1) {
        cleanKiri();
        SetColor(colorMainText);
        gotoxy(5, 3); printf("ID Region");
        gotoxy(5+50, 3); printf("| %-40s|", reg.id);

        gotoxy(5, 5); printf("Nama Region");
        gotoxy(5+50, 5); printf("| %-40s|", reg.nama);

        char gjPokok[20];
        rupiah(reg.gaji, gjPokok);
        gotoxy(5, 7); printf("Gaji Pokok");
        gotoxy(5+50, 7); printf("| Rp. %-36s|", gjPokok);

        SetColor(colorHeadText);
        gotoxy(5, 13); printf(">>         MASUKKAN DATA YANG BARU         <<");

        SetColor(colorMainText);
        gotoxy(5, 17); printf("ID Region");
        gotoxy(55, 17); printf("|   %-16s |", reg.id);

        gotoxy(5, 22); printf("Nama Region");
        gotoxy(55, 22); printf("|   %-16s |", reg.nama);

        gotoxy(5, 27); printf("Gaji Pokok Terbaru");
        gotoxy(55, 27); printf("| Rp.              |");

        SetColor(colorScText);
        int gjtemp;
        getRp(&gjtemp, 3, 8, 61, 27);

        if (doaction("UBAH DATA") == 1) {
            strcpy(reg.id, reg.id);
            strcpy(reg.nama, reg.nama);
            reg.gaji = gjtemp;
            fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
                fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
                fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Region tidak ditemukan");
        gotoxy(row + 24, 15); printf("       ");
        goto retype;
    }
    fclose(dataRegion);
    fclose(dataRegionTemp);
}
void updateDataReg() {
    findRegtoUpd();

    dataRegion = fopen("DAT/dataReg.dat", "wb");
    dataRegionTemp = fopen("TEMP/dataRegTemp.dat", "rb");

    while (fread(&reg, sizeof(reg), 1, dataRegionTemp) == 1) {
        fwrite(&reg, sizeof(reg), 1, dataRegion);
    }
    fclose(dataRegion);
    fclose(dataRegionTemp);
}
//Prosedur delete data dalam file
void findRegtoDel() {
    int found;
    found = 0;
    char idReg[10];

    retype:
    gotoxy(row + 24, 15); getteks(idReg, 6);

    dataRegion = fopen("DAT/dataReg.dat", "rb");
    dataRegionTemp = fopen("TEMP/dataRegTemp.dat", "wb");

    while (found == 0 && fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        if (strcmp(idReg, reg.id) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
        }
    }
    if (found == 1) {
        if (deleteData() == 1) {
            while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
                fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            } showMessage("ATTENTION!!", "Data berhasil dihapus!");
        } else {
            fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
                fwrite(&reg, sizeof(reg), 1, dataRegionTemp);
            }
        }
    }
    else {
        showMessage("ALERT!", "ID Region tidak ditemukan");
        gotoxy(row + 24, 15); printf("       ");
        goto retype;
    }
    fclose(dataRegion);
    fclose(dataRegionTemp);
}
void deleteDataReg() {
    findRegtoDel();

    dataRegion = fopen("DAT/dataReg.dat", "wb");
    dataRegionTemp = fopen("TEMP/dataRegTemp.dat", "rb");

    while (fread(&reg, sizeof(reg), 1, dataRegionTemp)==1) {
        fwrite(&reg, sizeof(reg), 1, dataRegion);
    }
    fclose(dataRegion);
    fclose(dataRegionTemp);
}

#endif //HOLLYFPAYROLL_REGION_H
