#ifndef HOLLYFPAYROLL_TRLEMBUR_H
#define HOLLYFPAYROLL_TRLEMBUR_H

void ajukanLembur (char idEmp[])
{
    char kodeLembur[] = {"LBR"};
    int id_terakhir = 0;
    char tgl[15];
    gettodayDate(tgl);
    int x;

    dataLembur = fopen ("DAT/TRdataLembur.dat", "ab+");
    while (fread(&lembur, sizeof(lembur), 1, dataLembur) == 1)
    {
        //MEMBACA BAGIAN INTEGER DARI STRING ID Peminjaman KEMUDIAN INTEGER HASIL PEMBACAAN DISIMPAN DI VARIABEL IDTERAKHIR
        sscanf(lembur.id_lembur, "%*[^0-9]%d", &id_terakhir);
    }
    for (int i = id_terakhir+1; i <= id_terakhir + 1; i++)
    {
        gotoxy(row, 5);SetColor(colorScText);
        // generate id otomatis denan menggabungkan 2 variable string & integer
        snprintf(lembur.id_lembur, sizeof (lembur.id_lembur), "%s%d", kodeLembur, i);

        // mengisi isi dari data lembur
        strcpy (lembur.id_karyawan, idEmp); // copy id karyawan

        SetColor(colorScText);
        gotoxy(row+10, 12); getDate(lembur.tggl_lembur);
        gotoxy(row+10, 17); getnum(&lembur.lama_lembur, 1);
        lembur.gaji_lembur = lembur.lama_lembur*50000; // mengisi upah lembur

        strcpy(lembur.tggl_pengajuan, tgl); // mengisi tanggal pengajuan
        strcpy(lembur.status_lembur, "Pending"); // otomatis mengisi pending...

        int hri, bulan, thun;
        bulanTahun(lembur.tggl_lembur, &hri, &bulan, &thun);
        sscanf(idEmp, "%*[^0-9]%d", &x);
        snprintf(lembur.id_gaji, sizeof(lembur.id_gaji), "%s%d%d%d", "GJ", x, bulan, thun);
        // menyimpan data lembur
        fwrite(&lembur, sizeof(lembur), 1, dataLembur);
    }
    fclose(dataLembur);
}
void readPengajuanLembur(char idEMP[])
{
    int yTeks = 4;
    char printRP[10];
    int i = 1;
    int fd = 0;
    char namaemp[30];
    cariNamaKaryawan(idEMP, namaemp);

    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
    if (dataLembur == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        gotoxy(0, 3); SetColor(colorScText);
        gotoxy(3, 2); printf(" %-5s  %-25s  %-15s  %-10s  %-15s  %-15s  %-10s ",
                             "ID", "NAMA", "TGL LBR", "JAM LBR", "UPAH", "PENGAJUAN", "STATUS");
        while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
            if (strcmp(idEMP, lembur.id_karyawan) == 0) {
                fd = 1;
                rupiah(lembur.gaji_lembur, printRP);
                gotoxy(3, yTeks);
                printf(" %-5s  %-25s  %-15s     %-7d  Rp. %-11s  %-15s  %-10s ",
                       lembur.id_lembur,
                       namaemp,
                       lembur.tggl_lembur,
                       lembur.lama_lembur,
                       printRP,
                       lembur.tggl_pengajuan,
                       lembur.status_lembur);
                if (i % 35 == 0) {
                    getchar();
                    cleanKiri();
                    yTeks = 3;
                }
                i++;
                yTeks++;
            }
        }
        printTable(3, 110, 1, 42);
        if (fd != 1) {
            showMessage("ALERT!", "Anda Belum Pernah Mengajukan Lembur!");
        }
    }
    fclose(dataLembur);
}
void readPengajuanLemburALL()
{
    int yTeks = 4;
    char printRP[10];
    int i = 1;
    char namaemp[30];

    gotoxy(0, 3); SetColor(colorScText);
    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
        printTable(3, 110, 1, 42);
        gotoxy(3, 2); printf(" %-5s  %-25s  %-15s  %-10s  %-15s  %-15s  %-10s ",
                             "ID", "NAMA", "TGL LBR", "JAM LBR", "UPAH", "PENGAJUAN", "STATUS");
        rupiah(lembur.gaji_lembur, printRP);
        cariNamaKaryawan(lembur.id_karyawan, namaemp);
        gotoxy(3, yTeks);
        printf(" %-5s  %-25s  %-15s     %-7d  Rp. %-11s  %-15s  %-10s ",
               lembur.id_lembur,
               namaemp,
               lembur.tggl_lembur,
               lembur.lama_lembur,
               printRP,
               lembur.tggl_pengajuan,
               lembur.status_lembur);
        if (i % 35 == 0) {
            getchar();
            cleanKiri();
            yTeks = 3;
        }
        i++;
        yTeks++;
    }
    fclose(dataLembur);
}

int cekBrchKaryawan(char idEmp[], char idBrc[]) {
    int fd = 0;
    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0 && strcmp(idBrc, karyawan.id_cabang) == 0) {
            fd = 1;
            break;
        }
    }
    fclose(dataKaryawan);
    if (fd == 1) {
        return 1;
    } else {
        return 0;
    }
}
void updstsLembur(char Brc[]) {
    int found = 0;
    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
    dataLemburTemp = fopen("TEMP/TRdataLemburTemp.dat", "wb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
        if (strcmp(lembur.status_lembur, "Pending") == 0 && cekBrchKaryawan(lembur.id_karyawan, Brc) == 1) {
            found = 1;
            cleanKiri();
            SetColor(colorScText);
            gotoxy(5, 5);
            printf("ID Lembur");
            gotoxy(5 + 50, 5);
            printf("| %-40s|", lembur.id_lembur);

            gotoxy(5, 9);
            printf("Nama Karyawan");
            gotoxy(5 + 50, 9);
            char namaEmp[30];
            cariNamaKaryawan(lembur.id_karyawan, namaEmp);
            printf("| %-40s|", namaEmp);

            gotoxy(5, 13);
            printf("Tanggal Pengajuan");
            gotoxy(5 + 50, 13);
            printf("| %-40s|", lembur.tggl_pengajuan);

            gotoxy(5, 17);
            printf("Tanggal Lembur");
            gotoxy(5 + 50, 17);
            printf("| %-40s|", lembur.tggl_lembur);

            gotoxy(5, 21);
            printf("Jam Lembur");

            gotoxy(5 + 50, 21);
            printf("| %-5d%-35s|", lembur.lama_lembur, "Jam");

            strcpy(lembur.id_lembur, lembur.id_lembur);
            strcpy(lembur.id_karyawan, lembur.id_karyawan);
            strcpy(lembur.id_gaji, lembur.id_gaji);
            strcpy(lembur.tggl_lembur, lembur.tggl_lembur);
            strcpy(lembur.tggl_pengajuan, lembur.tggl_pengajuan);
            lembur.lama_lembur = lembur.lama_lembur;
            lembur.gaji_lembur = lembur.gaji_lembur;
            if (ACC() == 1) {
                strcpy(lembur.status_lembur, "Diterima");
            } else {
                strcpy(lembur.status_lembur, "Ditolak");
            }
            fwrite(&lembur, sizeof(data_Lembur), 1, dataLemburTemp);
        } else {
            fwrite(&lembur, sizeof(data_Lembur), 1, dataLemburTemp);
        }
    }
    if (!found) {
        showMessage("ATTENTION", "TIDAK ADA YANG PERLU APPROVAL");
    }
    fclose(dataLembur);
    fclose(dataLemburTemp);
}
void approvalLembur(char Branch[]) {
    updstsLembur(Branch);
    dataLembur = fopen ("DAT/TRdataLembur.dat", "wb");
    dataLemburTemp = fopen("TEMP/TRdataLemburTemp.dat", "rb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLemburTemp) == 1) {
        fwrite(&lembur, sizeof(data_Lembur), 1, dataLembur);
    }
    fclose(dataLembur);
    fclose(dataLemburTemp);
}

int cariTotLembur(char idEMP[])
{
    int fd = 0;
    int totLembur =0;
    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
        while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
            if (strcmp(idEMP, lembur.id_karyawan) == 0 && strcmp(lembur.status_lembur, "Diterima") == 0) {
                fd = 1;
                totLembur += lembur.lama_lembur;
            } else {
                continue;
            }
        }
    fclose(dataLembur);
    if (fd != 1) {
        return 0;
    } else {
        return totLembur;
    }
}
int cariTotLemburBulan(char idEMP[], int bulan, int tahun)
{
    int fd = 0;
    int totLembur =0;
    int bl,hr,th;
    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
        bulanTahun(lembur.tggl_lembur, &hr, &bl, &th);
        if (strcmp(idEMP, lembur.id_karyawan) == 0 && strcmp(lembur.status_lembur, "Diterima") == 0 && bulan == bl && tahun == th) {
            fd = 1;
            totLembur += lembur.lama_lembur;
        } else {
            continue;
        }
    }
    fclose(dataLembur);
    if (fd != 1) {
        return 0;
    } else {
        return totLembur;
    }
}

#endif //HOLLYFPAYROLL_TRLEMBUR_H
