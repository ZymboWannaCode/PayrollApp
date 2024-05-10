#ifndef HOLLYFPAYROLL_TRCUTI_H
#define HOLLYFPAYROLL_TRCUTI_H

void findEmptoUpd2(char No[10], int lama) {
    int found;
    found = 0;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "wb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(No, karyawan.id_karyawan) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
        }
    }
    if (found == 1) {
        // MENAMPILKAN TEKS UNTUK INPUT
        strcpy(karyawan.id_karyawan, karyawan.id_karyawan);
        strcpy(karyawan.id_cabang, karyawan.id_cabang);
        strcpy(karyawan.id_jabatan, karyawan.id_jabatan);
        strcpy(karyawan.nama_karyawan, karyawan.nama_karyawan);
        strcpy(karyawan.tanggalLahir_karyawan, karyawan.tanggalLahir_karyawan);
        strcpy(karyawan.alamat_karyawan, karyawan.alamat_karyawan);
        strcpy(karyawan.gender_karyawan, karyawan.gender_karyawan);
        strcpy(karyawan.tgglMulaiKerja_karyawan, karyawan.tgglMulaiKerja_karyawan);
        karyawan.jatahCuti_karyawan = karyawan.jatahCuti_karyawan-lama;
        karyawan.plafonAsuransi = karyawan.plafonAsuransi;
        strcpy(karyawan.status_karyawan, karyawan.status_karyawan);
        strcpy(karyawan.password, karyawan.password);
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
        while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
        }
    } else {
        showMessage("ALERT!", "Id Karyawan tidak ditemukan!");
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}
void updateSisaCuti(char id[], int bnyakCuti) {
    findEmptoUpd2(id, bnyakCuti);

    dataKaryawan = fopen("DAT/dataEmp.dat", "wb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp)==1) {
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawan);
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}
int checkCuti(int lama, char idEMP[]) {
    int found = 0;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEMP, karyawan.id_karyawan) == 0 && karyawan.jatahCuti_karyawan - lama >= 0) {
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
int sisaCuti(char idEmp[]) {
    int found = 0;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0) {
            found = 1;
            break;
        }
    }
    fclose(dataKaryawan);
    if (found == 1) {
        return karyawan.jatahCuti_karyawan;
    } else {
        return 0;
    }
}

void ajukanCuti(char idEmp[]) {
    int found = 0;
    int lastID = 0;
    char tgl[15];
    gettodayDate(tgl);

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0 && karyawan.jatahCuti_karyawan > 0) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        datatrCuti = fopen("DAT/TRdataCuti.dat", "ab+");
        while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
            sscanf(trCuti.idCuti, "%*[^0-9]%d", &lastID);
        }
        snprintf(trCuti.idCuti, sizeof(trCuti.idCuti), "%s%d", "CT", lastID+1);

        gotoxy(0, 10); SetColor(colorScText);
        gotoxy(row+10, 12); getDate(trCuti.tglCuti);
        int hari;
        gotoxy(row+10, 17); getnum(&hari, 1);
        if (checkCuti(hari, idEmp) == 1) {
            trCuti.jumlahHari = hari;

            SetColor(colorScText);
            gotoxy(row+10, 22); getteks(trCuti.ketCuti, 50);
            strcpy(trCuti.idKaryawan, idEmp);
            strcpy(trCuti.tglPengajuan, tgl);
            strcpy(trCuti.sts, "Diterima");

            fwrite(&trCuti, sizeof (dataCuti), 1, datatrCuti);
            updateSisaCuti(idEmp, hari);
            showMessage("ATTENTION!!", "Data berhasil disimpan!");
        } else {
            showMessage("ALERT!", "Jatah Cuti Anda Habis!\nLama Cuti Harus Lebih Sedikit!");
            trCuti.jumlahHari = hari;
            gotoxy(row+10, 22); getteks(trCuti.ketCuti, 50);
            strcpy(trCuti.idKaryawan, idEmp);
            strcpy(trCuti.tglPengajuan, tgl);
            strcpy(trCuti.sts, "Ditolak");

            fwrite(&trCuti, sizeof (dataCuti), 1, datatrCuti);
        }
        fclose(datatrCuti);
    } else {
        showMessage("ALERT!", "Jatah Cuti Anda Sudah Habis!");
    }
    fclose(dataKaryawan);
}
void readtrCuti(char idEmp[]) {
    int yTeks = 4;
    int fd = 0;
    char namaemp[30];
    cariNamaKaryawan(idEmp, namaemp);

    datatrCuti = fopen("DAT/TRdataCuti.dat", "rb");
    if(datatrCuti == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        int i = 1;
        while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
            if (strcmp(idEmp, trCuti.idKaryawan) == 0) {
                printTable(3, 110, 1, 42);
                gotoxy(0, 3); SetColor(colorScText);
                gotoxy(3, 2); printf(" %-5s  %-20s  %-10s  %-5s  %-30s  %-15s  %-10s ",  "ID",
                                     "NAMA",
                                     "TANGGAL",
                                     "JML",
                                     "KETERANGAN",
                                     "PENGAJUAN",
                                     "STATUS");
                fd = 1;
                gotoxy(3, yTeks);
                printf(" %-5s  %-20s  %-10s   %-5d %-30s  %-15s  %-10s ",
                       trCuti.idCuti,
                       namaemp,
                       trCuti.tglCuti,
                       trCuti.jumlahHari,
                       trCuti.ketCuti,
                       trCuti.tglPengajuan,
                       trCuti.sts);
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
            showMessage("ALERT!", "Anda Belum Pernah Cuti!");
        }
    }
    fclose(datatrCuti);
}
void readtrCutiALL() {
    int yTeks = 4;
    char namaemp[30];


    datatrCuti = fopen("DAT/TRdataCuti.dat", "rb");
    if(datatrCuti == NULL) {
        showMessage("ALERT!", "TIDAK ADA DATA");
    } else {
        int i = 1;
        while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
            gotoxy(0, 3); SetColor(colorScText);
            printTable(3, 110, 1, 42);
            gotoxy(3, 2); printf(" %-5s  %-20s  %-10s  %-7s   %-25s %-15s  %-10s ",  "ID",
                                 "NAMA",
                                 "TANGGAL",
                                 "JML HR",
                                 "KETERANGAN",
                                 "PENGAJUAN",
                                 "STATUS");
            cariNamaKaryawan(trCuti.idKaryawan, namaemp);
            gotoxy(3, yTeks);
            printf(" %-5s  %-20s  %-10s    %-6d  %-25s %-15s  %-10s ",
                   trCuti.idCuti,
                   namaemp,
                   trCuti.tglCuti,
                   trCuti.jumlahHari,
                   trCuti.ketCuti,
                   trCuti.tglPengajuan,
                   trCuti.sts);
            if (i % 35 == 0) {
                getch();
                cleanKiri();
                yTeks = 3;
            }
            i++;
            yTeks++;
        }
    }
    fclose(datatrCuti);
}

int cariPresensi(char idEmp[]) {
    int fd = 0;
    int totAbsen = 0;
    datatrCuti = fopen("DAT/TRdataCuti.dat", "rb");
    if(datatrCuti == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
            if (strcmp(idEmp, trCuti.idKaryawan) == 0 && strcmp(trCuti.sts, "Diterima") == 0) {
                fd = 1;
                totAbsen += trCuti.jumlahHari;
            } else {
                continue;
            }
        }
        fclose(datatrCuti);
        if (fd != 1) {
            return 25;
        } else {
            if (25 - totAbsen < 0) {
                return 0;
            } else {
                return 25 - totAbsen;
            }
        }
    }
    fclose(datatrCuti);
}
int cariPresensiBulanan(char idEmp[], int bulan, int tahun) {
    int fd = 0;
    int totAbsen = 0;
    int bl,hr,th;
    datatrCuti = fopen("DAT/TRdataCuti.dat", "rb");
    if(datatrCuti == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
            bulanTahun(trCuti.tglCuti, &hr, &bl, &th);
            if (strcmp(idEmp, trCuti.idKaryawan) == 0 && strcmp(trCuti.sts, "Diterima") == 0 && bl == bulan && tahun == th) {
                fd = 1;
                totAbsen += trCuti.jumlahHari;
            } else {
                continue;
            }
        }
        fclose(datatrCuti);
        if (fd != 1) {
            return 25;
        } else {
            if (25 - totAbsen < 0) {
                return 0;
            } else {
                return 25 - totAbsen;
            }
        }
    }
    fclose(datatrCuti);
}

#endif //HOLLYFPAYROLL_TRCUTI_H
