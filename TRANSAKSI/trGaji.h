#ifndef HOLLYFPAYROLL30012024_TRGAJI_H
#define HOLLYFPAYROLL30012024_TRGAJI_H

void cariDataGaji(int *tjabatan, int *gajiPokok) {
    File = fopen("DAT/dataJab.dat", "rb");
    while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
        if (strcmp(jabatan.id, karyawan.id_jabatan) == 0) {
            *tjabatan = jabatan.tunjangan;
            break;
        }
    }
    fclose(File);

    char regionID[10];
    dataCabang = fopen("DAT/dataCab.dat", "rb");
    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        if (strcmp(cabang.id_cabang, karyawan.id_cabang) == 0) {
            strcpy(regionID, cabang.id_region);
            break;
        }
    }
    fclose(dataCabang);

    dataRegion = fopen("DAT/dataReg.dat", "rb");
    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
        if (strcmp(regionID, reg.id) == 0) {
            *gajiPokok = reg.gaji;
            break;
        }
    }
    fclose(dataRegion);
}
void cariMR(char idEMP[], int bulan, int tahun, int *bonus, char *idMR) {
    int hr, bl, th;
    int fd = 0;
    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "rb");
    if (dataTrRating == NULL) {
        *bonus = 0;
        strcpy(idMR, "-");
    } else {
        while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1) {
            bulanTahun(trRating.tgl, &hr, &bl, &th);
            if (strcmp(idEMP, trRating.idKrywn) == 0 && bl == bulan && th == tahun) {
                fd = 1;
                break;
            }
        } if (fd == 1) {
            *bonus = trRating.bonus;
            strcpy(idMR, trRating.idMR);
        } else {
            *bonus = 0;
            strcpy(idMR, "-");
        }
    }
    fclose(dataTrRating);
}

int cariUpahLembur(char tgl[], char idEmp[]) {
    int hri, bulan, thun, hr, bl,th;
    bulanTahun(tgl, &hri, &bulan, &thun);

    int upahLembur = 0;
    int fd = 0;
    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
        bulanTahun(lembur.tggl_lembur, &hr,&bl,&th);
        if (bl == bulan && thun == th &&
        strcmp(lembur.status_lembur, "Diterima") == 0 &&
        strcmp(lembur.id_karyawan, idEmp) == 0) {
            fd = 1;
            upahLembur += lembur.gaji_lembur;
        }
    }
    fclose(dataLembur);
    if (fd == 1) {
        return upahLembur;
    } else {
        return 0;
    }
}

int cekAdaGaji(char tanggalGaji[]) {
    int hr, bl, th, hr2, bl2, th2;
    int found = 0;
    bulanTahun(tanggalGaji, &hr, &bl, &th);
    dataGajian = fopen("DAT/TRdataGajian.dat", "rb");
    while (fread(&gaji, sizeof(gaji), 1, dataGajian) == 1) {
        bulanTahun(gaji.tanggal, &hr2, &bl2, &th2);
        if (bl == bl2 && th == th2) {
            found = 1;
            break;
        }
    }
    fclose(dataGajian);
    if (found == 1) {
        return 0;
    } else {
        return 1;
    }
}

void gajiBulanan(char cabang[]) {
    int tjab, gpokok, bonus;
    char MR[15];
    char idemp[10];
    int hri, bulan, thun;
    char tanggalGaji[15];
    int hr,bl,th;
    char tglSekarang[15];
    gettodayDate(tglSekarang);
    bulanTahun(tglSekarang, &hr, &bl, &th);

    gotoxy(row+14, 16); getDate(tanggalGaji);
    bulanTahun(tanggalGaji, &hri, &bulan, &thun);

    if (thun == th && bulan > bl) {
        showMessage("ALERT", "TANGGAL GAJIAN TIDAK VALID!");
    } else if (thun > th) {
        showMessage("ALERT", "TANGGAL GAJIAN TIDAK VALID!");
    } else {
        if (cekAdaGaji(tanggalGaji) != 1) {
            showMessage("ALERT!", "Data Gaji Bulan Tersebut Sudah Ada!");
        } else {
            dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
            dataGajianTemp = fopen("TEMP/TRdataGajianTemp.dat", "wb");
            while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
                if (strcmp(karyawan.id_cabang, cabang) == 0 && (strcmp(karyawan.status_karyawan, "aktif") == 0 || strcmp(karyawan.status_karyawan, "Aktif") == 0)) {
                    strcpy(idemp, karyawan.id_karyawan);

                    strcpy(gaji.idKrywn, idemp); // ID KRYWN

                    int x;
                    sscanf(idemp, "%*[^0-9]%d", &x);
                    snprintf(gaji.idGaji, sizeof(gaji.idGaji), "%s%d%d%d", "GJ", x, bulan, thun);

                    cariMR(karyawan.id_karyawan, bulan, thun, &bonus, MR);
                    strcpy(gaji.idPrating, MR); // ID MR

                    strcpy(gaji.tanggal, tanggalGaji); // TGL
                    cariDataGaji(&tjab, &gpokok);

                    gaji.gajiPokok = gpokok; // G POKOK
                    gaji.tJabatan = tjab; // T JABATAN
                    gaji.bRating = bonus; // BONUS
                    gaji.uLembur = cariUpahLembur(gaji.tanggal, karyawan.id_karyawan); // UP LEMBUR
                    gaji.totGaji = gaji.gajiPokok + gaji.tJabatan + gaji.bRating + gaji.uLembur; // TOT GAJI
                    gaji.pajak = 0.05 * (gaji.gajiPokok + gaji.tJabatan + gaji.bRating + gaji.uLembur); // PAJAK
                    gaji.potong = gaji.pajak; // POTONGAN
                    gaji.gjTerima = gaji.totGaji - gaji.potong; // GJ TERIMA

                    fwrite(&gaji, sizeof(gaji), 1, dataGajianTemp);
                }
            }
            showMessage("ATTENTION!", "DATA GAJI SELESAI DIBUAT!");
            //MENUTUP FILE SETELAH DIGUNAKAN
            fclose(dataGajianTemp);
            fclose(dataKaryawan);

            dataGajian = fopen("DAT/TRdataGajian.dat", "ab");
            dataGajianTemp = fopen("TEMP/TRdataGajianTemp.dat", "rb");
            while (fread(&gaji, sizeof(gaji), 1, dataGajianTemp) == 1) {
                fwrite(&gaji, sizeof(gaji), 1, dataGajian);
            }
            fclose(dataGajianTemp);
            fclose(dataGajian);
        }
    }
}



void readGajiALL() {
    int i = 1;
    int yTeks = 4;
    dataGajian = fopen("DAT/TRdataGajian.dat", "rb");
    while (fread(&gaji, sizeof(gaji), 1, dataGajian) == 1) {
        printTable(3, 110, 1, 42);
        SetColor(colorScText);
        gotoxy(3, 2); printf(" %-5s   %-13s  %-9s   %-9s   %-9s   %-9s   %-6s   %-9s    %-9s  ",
               "ID", "TGL GAJI", "G POKOK", "TUNJANGAN", "BONUS", "UPAH LBR", "POTONGAN", "TOT GAJI", "DITERIMA");
        char rp[10];
        rupiah(gaji.gajiPokok, rp);
        char rp1[10];
        rupiah(gaji.tJabatan, rp1);
        char rp2[10];
        rupiah(gaji.bRating, rp2);
        char rp3[10];
        rupiah(gaji.uLembur, rp3);
        char rp4[10];
        rupiah(gaji.potong, rp4);
        char rp5[10];
        rupiah(gaji.totGaji, rp5);
        char rp6[10];
        rupiah(gaji.gjTerima, rp6);
        gotoxy(3, yTeks);
        printf(" %-5s   %-13s  %-9s   %-9s   %-9s   %-9s   %-9s  %-9s    %-9s  ",
               gaji.idKrywn, gaji.tanggal, rp, rp1, rp2, rp3, rp4, rp5, rp6);
        if (i % 35 == 0) {
            getch();
            cleanKiri();
            yTeks = 3; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    fclose(dataGajian);
}

void readGajiBulan(int bulan, int tahun) {
    int i = 1;
    int fd = 0;
    int hr,bl,th;
    int yTeks = 4;
    dataGajian = fopen("DAT/TRdataGajian.dat", "rb");
    while (fread(&gaji, sizeof(gaji), 1, dataGajian) == 1) {
        bulanTahun(gaji.tanggal, &hr,&bl,&th);
        if (bl == bulan && th == tahun) {
            fd = 1;
            printTable(3, 110, 1, 42);
            SetColor(colorScText);
            gotoxy(3, 2); printf(" %-5s   %-13s  %-9s   %-9s   %-9s   %-9s   %-6s   %-9s    %-9s  ",
                                 "ID", "TGL GAJI", "G POKOK", "TUNJANGAN", "BONUS", "UPAH LBR", "POTONGAN", "TOT GAJI", "DITERIMA");
            char rp[10];
            rupiah(gaji.gajiPokok, rp);
            char rp1[10];
            rupiah(gaji.tJabatan, rp1);
            char rp2[10];
            rupiah(gaji.bRating, rp2);
            char rp3[10];
            rupiah(gaji.uLembur, rp3);
            char rp4[10];
            rupiah(gaji.potong, rp4);
            char rp5[10];
            rupiah(gaji.totGaji, rp5);
            char rp6[10];
            rupiah(gaji.gjTerima, rp6);
            gotoxy(3, yTeks);
            printf(" %-5s   %-13s  %-9s   %-9s   %-9s   %-9s   %-9s  %-9s    %-9s  ",
                   gaji.idKrywn, gaji.tanggal, rp, rp1, rp2, rp3, rp4, rp5, rp6);
            if (i % 35 == 0) {
                getch();
                cleanKiri();
                yTeks = 3;
            }
            i++;
            yTeks++;
        }
    }
    fclose(dataGajian);
    if (fd != 1) {
        showMessage("ALERT!", "TIDAK ADA DATA!");
    }
}


#endif //HOLLYFPAYROLL30012024_TRGAJI_H
