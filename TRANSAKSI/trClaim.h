#ifndef HOLLYFPAYROLL_TRCLAIM_H
#define HOLLYFPAYROLL_TRCLAIM_H

void ajukanClaim(char idEmp[]) {
    char kdClaim[] = "CA";
    int idterakhir = 0;
    char tgl[15];
    gettodayDate(tgl);

    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "ab+");

    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
        sscanf(trClaim.idClaim, "%*[^0-9]%d", &idterakhir);
    }
    fclose(dataClaimAsuransi);

    dataClaimAsuransi  = fopen("DAT/TRdataClaim.dat", "ab");
    for (int i = idterakhir + 1; i <= idterakhir+1; i++) {
        snprintf(trClaim.idClaim, sizeof(trClaim.idClaim), "%s%d", kdClaim, idterakhir+1); // ini untuk menggabungkan 2 variable
        strcpy(trClaim.idKrywn, idEmp);

        SetColor(colorScText);
        getRp(&trClaim.jmlClaim, 5, 7, row+14, 12);
        gotoxy(row+10, 17); getteks(trClaim.tempatClaim, 18);
        gotoxy(row+10, 22); getteks(trClaim.keterangan, 18);
        strcpy(trClaim.tgl, tgl);
        strcpy(trClaim.status, "Pending");

        fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(dataClaimAsuransi);
}

void readClaim(char idEMP[]) {
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = "ID";
    char tpt[] = "TPT_KLAIM";
    char krywn[] = "NAMA_EMP";
    char tgl[] = "TGL_KLAIM";
    char bon[] = "JML_KLAIM";
    char ket[] = "KET_KLAIM";
    char sts[] = "STATUS";
    int i = 1;
    int yTeks = 4;
    int fd = 0;
    char printRP[10];
    char namaemp[30];
    cariNamaKaryawan(idEMP, namaemp);

    //MEMBUKA FILE DENGAN MODE RB
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "rb");

    if (dataClaimAsuransi == NULL) {
        showMessage("ALERT!", "Anda Belum Pernah Mengajukan Claim!");
    } else {
        //MENAMPILKAN KE LAYAR ISI DARI FILE
        while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
            if (strcmp(idEMP, trClaim.idKrywn) == 0) {
                printTable(3, 110, 1, 42);
                gotoxy(0, 3); SetColor(colorScText);
                gotoxy(3, 2); printf("  %-5s  %-15s  %-12s  %-15s  %-18s  %-18s  %-10s ",
                                     id,krywn, tgl, bon, tpt, ket, sts);
                fd = 1;
                rupiah(trClaim.jmlClaim, printRP);
                gotoxy(3, yTeks); printf( "  %-5s  %-15s  %-12s  Rp. %-11s  %-18s  %-18s  %-10s ",
                                          trClaim.idClaim, namaemp, trClaim.tgl,
                                          printRP, trClaim.tempatClaim, trClaim.
                                keterangan, trClaim.status);
                if (i % 35 == 0) {
                    getch();
                    cleanKiri();
                    yTeks = 3;
                }

                i++;
                yTeks++;
            }
        }
        if (fd != 1) {
            showMessage("ALERT!", "Anda Belum Pernah Mengajukan Claim!");
        }
    }
    //MENUTUP FILE
    fclose(dataClaimAsuransi);
}

void readClaimALL() {
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = "ID";
    char tpt[] = "TPT_KLAIM";
    char krywn[] = "NAMA";
    char tgl[] = "TGL_KLAIM";
    char bon[] = "JML_KLAIM";
    char ket[] = "KET_KLAIM";
    char sts[] = "STATUS";
    int i = 1;
    int yTeks = 4;
    char printRP[10];

    //MEMBUKA FILE DENGAN MODE RB
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "rb");

    if (dataClaimAsuransi == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    }
    char namaemp[30];
    //MENAMPILKAN KE LAYAR ISI DARI FILE
    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
        printTable(3, 110, 1, 42);
        rupiah(trClaim.jmlClaim, printRP);
        cariNamaKaryawan(trClaim.idKrywn, namaemp);
        gotoxy(0, 3); SetColor(colorScText);
        gotoxy(3, 2); printf("  %-5s  %-15s  %-10s  %-14s  %-20s  %-20s  %-10s ",
                             id,krywn, tgl, bon, tpt, ket, sts);
        gotoxy(3, yTeks); printf( "  %-5s  %-15s  %-10s  Rp. %-10s  %-20s  %-20s  %-10s ",
               trClaim.idClaim, namaemp, trClaim.tgl,
               printRP, trClaim.tempatClaim, trClaim.
                        keterangan, trClaim.status);
        if (i % 35 == 0) {
            getch();
            cleanKiri();
            yTeks = 3;
        }
        i++;
        yTeks++;
    }
    //MENUTUP FILE
    fclose(dataClaimAsuransi);
}

int sisaPlafon(char idEmp[]) {
    int found = 0;
    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    gotoxy(0, 3); SetColor(colorScText);
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0) {
            found = 1;
            break;
        }
    }
    fclose(dataKaryawan);
    if (found == 1) {
        return karyawan.plafonAsuransi;
    } else {
        return 0;
    }
}

int cariTotClaimBulanan(char idEmp[], int bulan, int tahun) {
    int found = 0;
    int total = 0;
    int bl,hr,th;
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "rb");
    while (fread(&trClaim, sizeof(trClaim), 1, dataClaimAsuransi) == 1) {
        if (strcmp(idEmp, trClaim.idKrywn) == 0 && strcmp(trClaim.status, "Diterima") == 0 && bl == bulan && tahun == th) {
            found = 1;
            total += trClaim.jmlClaim;
        }
    }
    fclose(dataClaimAsuransi);
    if (found == 1) {
        return total;
    } else {
        return 0;
    }
}


/////ACC CLAIMM BENERAN FINAL INI MF


void updKlaimPlafon(char idEmp[], int jmlKlaim) {
    int found;
    found = 0;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "wb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
        }
    }
    if (found == 1) {
        karyawan.plafonAsuransi -= jmlKlaim;
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
    }
    while (fread(&karyawan, sizeof(data_karyawan), 1, dataKaryawan) == 1) {
        fwrite(&karyawan, sizeof(data_karyawan), 1, dataKaryawanTemp);
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}
void accPlafon(char idEmp[], int jml) {
    updKlaimPlafon(idEmp, jml);
    dataKaryawan = fopen("DAT/dataEmp.dat", "wb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "rb");

    while (fread(&karyawan, sizeof(data_karyawan), 1, dataKaryawanTemp)==1) {
        fwrite(&karyawan, sizeof(data_karyawan), 1, dataKaryawan);
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}

void updStatusClaim(char idemp[]) {
    int found = 0;
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "rb");
    dataClaimAsuransiTemp = fopen("TEMP/TRdataClaimTemp.dat", "wb");
    rewind(dataClaimAsuransi);
    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
        if (strcmp(trClaim.status, "Pending") == 0 && strcmp(trClaim.idKrywn, idemp) == 0) {
            found = 1;
            cleanKiri();
            SetColor(colorScText);
            gotoxy(5, 5);
            printf("ID Claim");
            gotoxy(5 + 50, 5);
            printf("| %-40s|", trClaim.idClaim);
            gotoxy(5, 9);
            printf("Tanggal Pengajuan");
            gotoxy(5 + 50, 9);
            printf("| %-40s|", trClaim.tgl);
            gotoxy(5, 13);
            printf("Nama Karyawan");
            gotoxy(5 + 50, 13);
            char namaEmp[30];
            cariNamaKaryawan(trClaim.idKrywn, namaEmp);
            printf("| %-40s|", namaEmp);
            gotoxy(5, 17);
            printf("Jumlah Claim");
            char rp[10];
            rupiah(trClaim.jmlClaim, rp);
            gotoxy(5 + 50, 17);
            printf("| Rp. %-36s|", rp);
            gotoxy(5, 21);
            printf("Tempat Claim");
            gotoxy(5 + 50, 21);
            printf("| %-40s|", trClaim.tempatClaim);
            gotoxy(5, 25);
            printf("Keterangan Claim");
            gotoxy(5 + 50, 25);
            printf("| %-40s|", trClaim.keterangan);
            if (ACC() == 1) {
                strcpy(trClaim.status, "Diterima");
                accPlafon(idemp, trClaim.jmlClaim);
            } else {
                strcpy(trClaim.status, "Ditolak");
            }
            fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransiTemp);
        } else {
            fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransiTemp);
        }
    }
    if (!found) {
        showMessage("ATTENTION", "TIDAK ADA YANG PERLU APPROVAL");
    }
    fclose(dataClaimAsuransiTemp);
    fclose(dataClaimAsuransi);
}
void approvalClaim(char idemp[]) {
    updStatusClaim(idemp);
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "wb");
    dataClaimAsuransiTemp = fopen("TEMP/TRdataClaimTemp.dat", "rb");
    rewind(dataClaimAsuransi);
    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransiTemp) == 1) {
        fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi);
    }
    fclose(dataClaimAsuransiTemp);
    fclose(dataClaimAsuransi);
}

int checkCabangKar(char idEmp[], char idCab[]) {
    int found =0;
    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0 && strcmp(idCab, karyawan.id_cabang) == 0) {
            found = 1;
            break;
        }
    }
    fclose(dataKaryawan);
    if (found == 1) {
        return 1;
    } else {
        return 0;
    }
}

void approvalClaimFinal(char Brc[]) {
    int i = 0;
    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "rb");

    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
        if (checkCabangKar(trClaim.idKrywn, Brc) == 1) {
            approvalClaim(trClaim.idKrywn);
        }
    }
    fclose(dataKaryawan);
    fclose(dataClaimAsuransi);
}



#endif //HOLLYFPAYROLL_TRCLAIM_H
