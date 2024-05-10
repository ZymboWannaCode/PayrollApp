#ifndef HOLLYFPAYROLL30012024_TRPINJAM_H
#define HOLLYFPAYROLL30012024_TRPINJAM_H

#define bunga 0.05 // deklarasi bunga akan selalu 5%



void cariMINMAX (int *nominal_minimal , int *nominal_maximal);
void tipePinjaman(int max_tipePinjaman);
int hitungBunga(int max_tipePinjaman);
void konversiTanggal(char *tglPinjam, tanggal *tgl);
void kalkulasiTempo(char tglPinjam[], char tipePinjam[]);
void readPinjaman(char ID[]);



void ajukanPinjaman (char idEmp[])
{
    char tipePinjam[10];
    char tanggalPinjam[15];
    gettodayDate(tanggalPinjam);
    int nominalPinjam;
    char kodePeminjaman[] = {"LOAN"};
    int id_terakhir = 0;
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "ab+");
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1)
    {
        sscanf(trPinjam.id_PPinjam, "%*[^0-9]%d", &id_terakhir);
    }
    for (int i = id_terakhir+1; i <= id_terakhir + 1; i++)
    {
        gotoxy(row, 5);SetColor(colorScText);
        snprintf(trPinjam.id_PPinjam, sizeof (trPinjam.id_PPinjam), "%s%d", kodePeminjaman, i);
        strcpy (trPinjam.id_karyawan, idEmp); // copy id karyawan otomatis
        strcpy(trPinjam.tgl_pinjam, tanggalPinjam); // otomatis mengisi tanggal peminjaman
        SetColor(colorScText);
        getRp(&trPinjam.jumlah_pinjam, 5, 8, row+14, 12);
        tipePinjaman(trPinjam.jumlah_pinjam);
        trPinjam.bunga_pinjam = hitungBunga(trPinjam.jumlah_pinjam);
        char rp[10];
        rupiah(trPinjam.bunga_pinjam, rp);
        gotoxy(row+12, 17); printf("Rp. %s", rp);

        kalkulasiTempo(tanggalPinjam, trPinjam.id_tipePinjam); // kalkulasi tempo pembayaran.
        strcpy(trPinjam.status_pinjam, "Pending"); // otomatis mengisi pending...
        gotoxy(row+12, 22); printf("%s", trPinjam.tanggalTempo);
        fwrite(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang);
    }
    fclose(dataPeminjamanUang);
}



int hitungBunga(int pinjam)
{
    return pinjam * bunga; // melakukan perhitungan bunga (nominal * 5%)
}

void cariMINMAX (int *nominal_minimal , int *nominal_maximal)
{
    // TODO: Check .dat tipe pinjaman (ada di cipung)
    data_tipePinjaman = fopen("DAT/tipePinjaman.dat", "rb");
    if (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1)
    {
        *nominal_minimal = tipePinjam.max_tipePinjaman;
        *nominal_maximal = tipePinjam.max_tipePinjaman;
    }
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1)
    {
        // inisialisasi jika ada bilangan yang lebih kecil dari nominal minimal
        if (tipePinjam.max_tipePinjaman < *nominal_minimal)
        {
            *nominal_minimal = tipePinjam.max_tipePinjaman;
        }
        // inisialisasi jika ada bilangan yang lebih besar dari nominal maximal
        if (tipePinjam.max_tipePinjaman > *nominal_maximal)
        {
            *nominal_maximal = tipePinjam.max_tipePinjaman;
        }
    }
    fclose(data_tipePinjaman);
}

void tipePinjaman(int max_tipePinjaman)
{
    int minimal, maximal;
    cariMINMAX(&minimal, &maximal);
    if (max_tipePinjaman <= 2500000)
    {
        strcpy(trPinjam.id_tipePinjam, "TP1");
        return;
    }
    else if (max_tipePinjaman <= 5000000)
    {
        strcpy(trPinjam.id_tipePinjam, "TP2");
        return;
    }
    else if (max_tipePinjaman <= 7500000)
    {
        strcpy(trPinjam.id_tipePinjam, "TP3");
        return;
    }
    else if (max_tipePinjaman <= 10000000)
    {
        strcpy(trPinjam.id_tipePinjam, "TP4");
        return;
    }
    else
    {
        printf("Batas nominal peminjaman adalah Rp.%.2lf-Rp.%.2lf", minimal, maximal);
    }
}

void konversiTanggal(char *tglPinjam, tanggal *tgl)
{
    sscanf(tglPinjam, "%i-%i-%i", &tgl->hari, &tgl->bulan, &tgl->tahun);
}

int cariKabisat(int tahun) {
    return (tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0);
}
int cariJmlHari(int blan, int tahun) {
    int jmlhari[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (blan == 2 && cariKabisat(tahun)) {
        return 29;
    }
    return jmlhari[blan];
}
void hitungTempo( char tglAwal[12], int banyakTambah, char* tglAkhir) {
    int hr,bl,th;
    bulanTahun(tglAwal, &hr,&bl,&th);
    for (int i = 0; i < banyakTambah; i++) {
        hr++;
        if (hr > cariJmlHari(bl, th)) {
            hr = 1;
            bl++;
            if (bl > 12) {
                bl = 1;
                th++;
            }
        }
    }
    snprintf(tglAkhir, 11, "%02d-%02d-%04d", hr, bl, th);
}

// masukkan tanggal pinjaman karyawan
void kalkulasiTempo(char tglPinjam[], char tipePinjam[])
{
    char output[15];
    // deklarasi struct
    tanggal tgl;

    // konversi tanggal
    konversiTanggal(tglPinjam, &tgl);


    int tambahHari;
    if (strcmp(tipePinjam, "TP1") == 0)
    {
        tambahHari= 90;
    }
    else if (strcmp(tipePinjam, "TP2") == 0)
    {
        tambahHari= 120;
    }
    else if (strcmp(tipePinjam, "TP3") == 0)
    {
        tambahHari= 240;
    }
    else if (strcmp(tipePinjam, "TP4") == 0)
    {
        tambahHari= 360;
    }

    hitungTempo(tglPinjam, tambahHari, trPinjam.tanggalTempo);
}

/*void approvalPinjaman(char id_Peminjaman)
{
    char idPinjam[50];
    char *approval;
    readPinjaman();
    printf("Masukkan id_Peminjaman: ");
    scanf(" %s", idPinjam);

    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1)
    {
        printf("Terima Proposal Peminjaman(Y/N): ");
        scanf(" %c", approval);
        if (strcasecmp(approval, "Y") == 0)
        {
            strcpy(lemburan.status_lembur, "Diterima");
            return;
        }
        else
        {
            strcpy(lemburan.status_lembur, "Ditolak");
            return;
        }
    }
}*/

// TODO: MASIH MENTAG NGIKUTIN PUNYA BUDI 😂
void readPinjamanALL()
{
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = "ID";
    char tipe[] = "TIPE";
    char krywn[] = "NAMA";
    char tggl[] = "PENGAJUAN";
    char tempo[] = "TEMPO";
    char nmnl[] = "NOMINAL";
    char riba[] = "BUNGA";
    char sts[] = "STATUS";
    cleanKiri();

    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "rb");

    int i = 1;
    int yTeks = 4;
    char namaemp[20];
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1)
    {
        char rp[15];
        char rp1[15];
        rupiah(trPinjam.jumlah_pinjam, rp);
        rupiah(trPinjam.bunga_pinjam, rp1);
        cariNamaKaryawan(trPinjam.id_karyawan, namaemp);
        SetColor(colorScText);
        gotoxy(3, 2); printf(" %-9s  %-5s  %-20s  %-12s  %-10s  %-10s  %-12s  %-10s ", id, tipe, krywn, tggl, nmnl, riba, tempo, sts);
        printTable(3, 110, 1, 42);
        gotoxy(3, yTeks);
        printf(" %-9s  %-5s  %-20s  %-12s  %-10s  %-10s  %-12s  %-10s ", trPinjam.id_PPinjam, trPinjam.id_tipePinjam, namaemp,
               trPinjam.tgl_pinjam, rp, rp1, trPinjam.tanggalTempo, trPinjam.status_pinjam);

        if (i % 35 == 0)
        {
            getch();
            cleanKiri();
            yTeks = 3;
        }
        i++;
        yTeks++;
    }
    //MENUTUP FILE
    fclose(dataPeminjamanUang);
}
void readPinjaman(char ID[])
{
    //DEKLARASI VARIABLE YANG DIGUNAKAN
    char id[] = "ID PINJAM";
    char tipe[] = "TIPE";
    char krywn[] = "NAMA EMP";
    char tggl[] = "TGL PINJAM";
    char tempo[] = "TEMPO";
    char nmnl[] = "NOMINAL";
    char riba[] = "BUNGA";
    char sts[] = "STATUS";
    int fd = 0;
    char namaemp[30];
    cariNamaKaryawan(ID, namaemp);
    cleanKiri();

    //MEMBUKA FILE DENGAN MODE RB
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "rb");

    if (dataPeminjamanUang == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        int i = 1;
        int yTeks = 4;
        //MENAMPILKAN KE LAYAR ISI DARI FILE
        gotoxy(0, 3); SetColor(colorScText);
        gotoxy(3, 2); printf(" %-9s  %-5s  %-20s  %-12s  %-10s  %-10s  %-12s  %-10s ", id, tipe, krywn, tggl, nmnl, riba, tempo, sts);
        while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1) {
            if (strcmp(ID, trPinjam.id_karyawan) == 0) {
                fd = 1;
                char rp[15];
                char rp1[15];
                rupiah(trPinjam.jumlah_pinjam, rp);
                rupiah(trPinjam.bunga_pinjam, rp1);
                gotoxy(3, yTeks);
                printf(" %-9s  %-5s  %-20s  %-12s  %-10s  %-10s  %-12s  %-10s ", trPinjam.id_PPinjam,
                       trPinjam.id_tipePinjam, namaemp,
                       trPinjam.tgl_pinjam, rp, rp1, trPinjam.tanggalTempo, trPinjam.status_pinjam);

                if (i % 35 == 0) {
                    getch();
                    cleanKiri();
                    yTeks = 3;
                }
                i++;
                yTeks++;
            }
        }
        printTable(3, 110, 1, 42);
        if (fd != 1) {
            showMessage("ALERT!", "Anda Belum Pernah Mengajukan Pinjaman!");
        }
    }
    fclose(dataPeminjamanUang);
}

int cekBrchKaryawan(char idEmp[], char idBrc[]);
void accPinjaman(char Branch[]) {
    int leftMarg  = 5;
    int found = 0;

    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "rb");
    dataPeminjamanUangTemp = fopen ("TEMP/TRdataPinjamanTemp.dat", "wb");
    //Pencarian data dalam file menggunakan looping
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1) {
        if (strcmp(trPinjam.status_pinjam, "Pending") == 0 && cekBrchKaryawan(trPinjam.id_karyawan, Branch) == 1) {
            found = 1;
            cleanKiri();
            SetColor(colorScText);
            gotoxy(5, 5);
            printf("ID Pinjaman");
            gotoxy(leftMarg + 50, 5); printf("| %-40s|", trPinjam.id_PPinjam);
            gotoxy(5, 9); printf("Tanggal Pengajuan");
            gotoxy(leftMarg + 50, 9); printf("| %-40s|", trPinjam.tgl_pinjam);

            char namaemp[30];
            cariNamaKaryawan(trPinjam.id_karyawan, namaemp);
            gotoxy(5, 13); printf("Nama Karyawan");
            gotoxy(leftMarg + 50, 13); printf("| %-40s|", namaemp);
            char rp[10];
            rupiah(trPinjam.jumlah_pinjam, rp);
            gotoxy(5, 17); printf("Jumlah Pinjaman");
            gotoxy(leftMarg + 50, 17); printf("| Rp. %-36s|", rp);
            char rp2[10];
            rupiah(trPinjam.bunga_pinjam, rp2);
            gotoxy(5, 21); printf("Bunga Pinjaman");
            gotoxy(leftMarg + 50, 21); printf("| Rp. %-36s|", rp2);
            gotoxy(5, 25); printf("Jatuh Tempo Pinjaman");
            gotoxy(leftMarg + 50, 25); printf("| %-40s|", trPinjam.tanggalTempo);

            strcpy(trPinjam.id_tipePinjam, trPinjam.id_tipePinjam);
            strcpy(trPinjam.tanggalTempo, trPinjam.tanggalTempo);
            strcpy(trPinjam.id_PPinjam, trPinjam.id_PPinjam);
            strcpy(trPinjam.id_karyawan, trPinjam.id_karyawan);
            strcpy(trPinjam.tgl_pinjam, trPinjam.tgl_pinjam);
            trPinjam.jumlah_pinjam = trPinjam.jumlah_pinjam;
            trPinjam.bunga_pinjam = trPinjam.bunga_pinjam;
            if (ACC() == 1) {
                strcpy(trPinjam.status_pinjam, "Diterima");
            } else {
                strcpy(trPinjam.status_pinjam, "Ditolak");
            }
            fwrite(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUangTemp);
        } else {
            fwrite(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUangTemp);
        }
    }
    if (!found) {
        showMessage("ATTENTION", "TIDAK ADA YANG PERLU APPROVAL");
    }
    fclose(dataPeminjamanUang);
    fclose(dataPeminjamanUangTemp);
}
void accUpdPinjaman(char Brch[]) {
    accPinjaman(Brch);
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "wb");
    dataPeminjamanUangTemp = fopen ("TEMP/TRdataPinjamanTemp.dat", "rb");
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUangTemp) == 1) {
        fwrite(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang);
    }
    fclose(dataPeminjamanUang);
    fclose(dataPeminjamanUangTemp);
}
int totalPinjam(char idEMp[]) {
    int fd = 0;
    int total = 0;
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "rb");
    if (dataPeminjamanUang == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1) {
            if (strcmp(idEMp, trPinjam.id_karyawan) == 0 && strcmp(trPinjam.status_pinjam, "Diterima") == 0) {
                fd = 1;
                total += trPinjam.jumlah_pinjam;
            }
        }
    }
    fclose(dataPeminjamanUang);
    if (fd != 1) {
        showMessage("ALERT!", "Anda Belum Pernah Mengajukan Pinjaman!");
        return 0;
    } else {
        return total;
    }
}
int caritotalPinjamBulanan(char idEMp[], int bulan, int tahun) {
    int fd = 0;
    int total = 0;
    int bl,hr,th;
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "rb");
    if (dataPeminjamanUang == NULL) {
        showMessage("ALERT!", "Data Masih Kosong!");
    } else {
        while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1) {
            bulanTahun(trPinjam.tgl_pinjam, &hr, &bl, &th);
            if (strcmp(idEMp, trPinjam.id_karyawan) == 0 && strcmp(trPinjam.status_pinjam, "Diterima") == 0 && bl == bulan && tahun == th) {
                fd = 1;
                total += trPinjam.jumlah_pinjam;
            }
        }
    }
    fclose(dataPeminjamanUang);
    if (fd != 1) {
        return 0;
    } else {
        return total;
    }
}

#endif //HOLLYFPAYROLL30012024_TRPINJAM_H
