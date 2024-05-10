#ifndef HOLLYFPAYROLL30012024_LAPORANPRJ_H
#define HOLLYFPAYROLL30012024_LAPORANPRJ_H

void lihatSlipGaji(char idemp[], char tanggalGaji[]) {
    int hr, bl, th, hr2, bl2, th2;
    char namaDia[30];
    char jabatan[15];
    char namaReg[15];
    char cabang[15];
    int fd = 0;

    bulanTahun(tanggalGaji, &hr, &bl, &th);
    dataGajian = fopen("DAT/TRdataGajian.dat", "rb");
    if (dataGajian == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        while (fread(&gaji, sizeof(gaji), 1, dataGajian) == 1) {
            bulanTahun(gaji.tanggal, &hr2, &bl2, &th2);
            if (strcmp(idemp, gaji.idKrywn) == 0 && bl == bl2 && th == th2) {
                fd = 1;
                break;
            }
        }
        if (fd == 1) {
            cariDataKarywn(gaji.idKrywn, namaDia, jabatan, namaReg, cabang);
            int printDataKrywn = 130;
            int x = 20;
            gotoxy(printDataKrywn, x);
            printf(":\t %s", idemp);
            gotoxy(printDataKrywn, x + 2);
            printf(":\t %s", namaDia);
            gotoxy(printDataKrywn, x + 4);
            printf(":\t %s", jabatan);
            gotoxy(printDataKrywn, x + 6);
            printf(":\t %s", cabang);
            gotoxy(printDataKrywn, x + 8);
            printf(":\t %s", namaReg);
            gotoxy(printDataKrywn, x + 10);
            printf(":\t %s", gaji.tanggal);

            int printGaji = 80;
            char gp[15];
            rupiah(gaji.gajiPokok, gp);
            char tj[15];
            rupiah(gaji.tJabatan, tj);
            char bn[15];
            rupiah(gaji.bRating, bn);
            char upl[15];
            rupiah(gaji.uLembur, upl);
            char tgj[15];
            rupiah(gaji.totGaji, tgj);
            char pt[15];
            rupiah(gaji.potong, pt);
            char gdtr[15];
            rupiah(gaji.gjTerima, gdtr);

            gotoxy(printGaji, 15);
            printf("Rp. %s", gp);
            gotoxy(printGaji, 18);
            printf("Rp. %s", tj);
            gotoxy(printGaji, 21);
            printf("Rp. %s", bn);
            gotoxy(printGaji, 24);
            printf("Rp. %s", upl);
            gotoxy(printGaji, 30);
            printf("Rp. %s", tgj);
            gotoxy(printGaji, 33);
            printf("Rp. %s", pt);
            gotoxy(printGaji, 38);
            printf("Rp. %s", gdtr);
            gotoxy(120, 40);
            printf("Klik ENTER untuk kembali...");
            getchar();
        } else {
            showMessage("ALERT!", "\tTIDAK ADA DATA\t");
        }
    }
    fclose(dataGajian);
}

void menuKinerja();
int validasiBulan(int bulan);
int validasiTahun(int tahun);
void laporanRatingTgl();
void laporanRatingAll();
char* cariNamaRating(char kodeRating[]);
char* cariKdRating(char idkrywn[], int bl, int th)
{
    int hr2,bl2,th2;
    int fd = 0;
    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "rb");
    while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1)
    {
        bulanTahun(trRating.tgl, &hr2,&bl2,&th2);
        // jika ditemukan nama trRating maka akan dicopy kedalam
        if (strcmp(idkrywn, trRating.idKrywn) == 0 && bl == bl2 && th == th2) {
            fd = 1;
            break;
        }
    }
    fclose(dataRating);

    if (fd != 1) {
        return "-";
    } else {
        return trRating.kRating;
    }
}

void menuKinerja()
{
    int pilihan;
    switch (pilihan)
    {
        case 1:laporanRatingTgl();
            break;
        case 2:
//            laporanRatingAll();
            break;
        case 3:
            //     TODO: KELUAR PROGRAM
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
    }
    exit(0);
}

void laporanRatingTgl()
{
    int bulan, tahun;
    int data_day, data_month, data_year;
    int fd = 0;

    // input bulan dan tahun untuk diteampilkan
    printf("Masukkan bulan: "); getnum(&bulan, 2);
    printf("Masukkan tahun: "); getnum(&tahun,4);

    // check validasi input buland dan tahun
    if (!validasiBulan(bulan) || !validasiTahun(tahun))
    {
        printf("Bulan tidak valid\n");
        exit(2);
    } else {
        dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "rb");
        while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1)
        {
            sscanf(trRating.tgl, "%d-%d-%d", &data_day, &data_month, &data_year);
            if (data_month == bulan && data_year == tahun)
            {
                fd = 1;
                char namaemp[30]; char namaRating[30];
                cariNamaKaryawan(trRating.idKrywn, namaemp);
                printf("| %-20s| %-10s| %-10s| %-10s| %-10i|\n",
                       namaemp, trRating.kRating, namaRating, trRating.tgl, trRating.bonus);
            }
        }
        fclose(dataTrRating);
        if (fd != 1) {
            showMessage("ALERT!", "TIDAK ADA DATA!");
        }
    }
}

int validasiBulan(int bulan) {
    // validasi jika input bulan diluar nalar
    if (bulan < 1 || bulan > 12) {
        return 0;
    } else {
        return 1;
    }
}

int validasiTahun(int tahun) {
    // validasi jika input tahun hanya 2018 - 2024
    if (tahun < 2018 || tahun > 2024) {
        return 0;
    } else {
        return 1;
    }
}

char* cariNamaRating(char kodeRating[]) {
    int fd = 0;
    dataRating = fopen("DAT/dataRating.dat", "rb");
    while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
        // jika ditemukan nama rating maka akan dicopy kedalam
        if (strcmp(kodeRating, rating.kode_rating) == 0) {
            fd = 1;
            break;
        }
    }
    fclose(dataRating);
    if (fd == 1) {
        return rating.nama;
    } else {
        return "-";
    }
}

void laporanKinerjaBulanan(int bulan, int tahun)
{

    int data_day, data_month, data_year;
    int fd = 0;
    char tgl[15];
    snprintf(tgl, 15, "27-%02d-%04d", bulan, tahun);

    // check validasi input buland dan tahun
    if (cekAdaMr(tgl) == 1)
    {
        showMessage("ALERT!", "TIDAK ADA DATA");
    } else {
        int i = 1;
        int yTeks = 4;
        char namajab[30];

        dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
        while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
            {
                printTable(3, 110, 1, 42);
                gotoxy(3, 2);
                printf("%-5s %-20s %-13s %-6s  %-6s  %-6s  %-12s %-12s %-10s",
                       "ID", "NAMA", "JABATAN", "RATING", "LEMBUR", "PRESENSI", "PINJAMAN", "CLAIM", "KET");

                SetColor(colorScText);
                gotoxy(3, yTeks);
                printf("%-5s  %-20s %-13s  %-6s  %-6d  %-6d  %-12d %-12d %-10s",
                       karyawan.id_karyawan,
                       karyawan.nama_karyawan,
                       cariNamaJabatan(karyawan.id_jabatan),
                       cariKdRating(karyawan.id_karyawan, bulan, tahun),
                       cariTotLemburBulan(karyawan.id_karyawan, bulan, tahun),
                       cariPresensiBulanan(karyawan.id_karyawan, bulan, tahun),
                       caritotalPinjamBulanan(karyawan.id_karyawan, bulan, tahun),
                       cariTotClaimBulanan(karyawan.id_karyawan, bulan, tahun),
                       cariNamaRating(cariKdRating(karyawan.id_karyawan, bulan, tahun)));

                if (i % 35 == 0) {
                    getchar();
                    cleanKiri();
                    yTeks = 3;
                }
                i++;
                yTeks++;
            }
        }
    }
}

#endif //HOLLYFPAYROLL30012024_LAPORANPRJ_H
