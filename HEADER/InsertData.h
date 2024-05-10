#ifndef HOLLYFPAYROLL_INSERTDATA_H
#define HOLLYFPAYROLL_INSERTDATA_H

void insertEMP()
{

    // DEKLARASI VARIABLE LOKAL PADA PROSEDUR YANG AKAN DIGUNAKAN
    char kodekaryawan[] = {"EMP"};
    int idterakhir = 0;
    int leftMarg = 15;
    char *jbArray[] = {"JB3", "JB3", "JB3", "JB5", "JB4", "JB2", "JB1", "JB1", "JB1", "JB1",
                       "JB1", "JB1", "JB1", "JB1", "JB1", "JB1", "JB1", "JB1", "JB1", "JB1",
                       "JB1", "JB1", "JB1", "JB1", "JB1"};
    char names[][50] = {
            "Aji Shiori",
            "Simon Simamora",
            "Basri Hamid",
            "Imron Amelia",
            "Arief Suwarno",
            "Mardi Nasir",
            "Imam Hadi",
            "Febri Sukaesih",
            "Heru Karim",
            "Hendi Supriyanto",
            "Ahmad Umar",
            "Erik Irawan",
            "Ayi Anam",
            "Ardi Ayu",
            "Febri Latifah",
            "Edi Yani",
            "Dadang Anggraini",
            "Sulaeman Syahputra",
            "Al Suryana",
            "Gatot Cahyono",
            "Mariana Astutik",
            "Riska Rohimah",
            "Dg Siagian",
            "Yuyun Agustina",
            "Ramlah Syah"
    };
    char *dates[] = {
            "15-07-1990",
            "12-03-1985",
            "28-04-1998",
            "19-09-1982",
            "11-10-1995",
            "02-07-1987",
            "22-08-1992",
            "14-05-1984",
            "30-10-1988",
            "03-05-1993",
            "18-06-1999",
            "01-12-1986",
            "24-09-1991",
            "11-08-1983",
            "20-04-1996",
            "07-01-1989",
            "12-09-1994",
            "25-02-1981",
            "17-05-1997",
            "10-11-1984",
            "29-03-1990",
            "08-06-1995",
            "19-11-1987",
            "06-03-1992",
            "16-09-1983"
    };
    char *lokasi[] = {
            "Sawah Besar, Jakarta",
            "Genteng, Surabaya",
            "Pontianak Barat, Pontianak",
            "Grogol, Semarang",
            "Tanah Abang, Jakarta",
            "Koto Tangah, Padang",
            "Tanjung Priok, Jakarta",
            "Ciputat, Tangerang",
            "Banyumanik, Semarang",
            "Banjarmasin Utara, Banjarmasin",
            "Sukolilo, Surabaya",
            "Mangga Besar, Jakarta",
            "Banyuwangi, Banyuwangi",
            "Medan Baru, Medan",
            "Percut Sei Tuan, Medan",
            "Cengkareng, Jakarta",
            "Nanggalo, Padang",
            "Sidorejo, Salatiga",
            "Kramat Jati, Jakarta",
            "Tanjung Priok, Jakarta",
            "Kotabaru, Yogyakarta",
            "Cirebon, Cirebon",
            "Ngaliyan, Semarang",
            "Pulo Gadung, Jakarta",
            "Wonokromo, Surabaya"
    };
    char *numbers[] = {"75821904", "40369271", "18503762", "92651037", "57084329", "31924850", "62415098", "89142705", "23596814", "48601372", "79521084", "30752486", "14980532", "87246103", "61093275", "54321098", "92837450", "46718923", "35264018", "68031724", "21598730", "79403568", "3648219", "87051236", "21963570"};

    // MEMBUKA FILE DENGAN MODE AB+ UNTUK MENGETAHUI ID TERAKHIR YANG TELAH DITAMBAHKAN
    dataKaryawan = fopen("DAT/dataEmp.dat", "wb+");
    // MEMBACA FILE UNTUK MENDAPATKAN ID KARYAWAN TERAKHIR
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        //MEMBACA BAGIAN INTEGER DARI STRING ID CABANG KEMUDIAN INTEGER HASIL PEMBACAAN DISIMPAN DI VARIABEL IDTERAKHIR
        sscanf(karyawan.id_karyawan, "%*[^0-9]%d", &idterakhir);
    }

    int x = 0;
    gotoxy(leftMarg, 2);SetColor(colorScText);
    // LOOPING PEMBUATAN ID CABANG SESUAI INPUTAN USER
    for (int i = idterakhir+1; i <= idterakhir+25; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(karyawan.id_karyawan, sizeof(karyawan.id_karyawan), "%s%d", kodekaryawan, i); // ini untuk menggabungkan 2 variable
        strcpy(karyawan.id_cabang, "BRC1");
        strcpy(karyawan.id_jabatan, jbArray[x]);

        strcpy(karyawan.nama_karyawan, names[x]); // INPUT NAMA KARYAWAN

        strcpy(karyawan.tanggalLahir_karyawan, dates[x]); // INPUT TGL LAHIR KARYAAWAN

        strcpy(karyawan.alamat_karyawan, lokasi[x]); // INPUT ALAMAT KARYAWAN

        strcpy(karyawan.gender_karyawan, "l"); // INPUT GENDER KARYAWAN

        strcpy(karyawan.tgglMulaiKerja_karyawan, "03-12-2018");// INPUT TGL MULAI KERJA

        karyawan.jatahCuti_karyawan = 12; // INPUT JATAH CUTI KARYAWAN

        karyawan.plafonAsuransi = 5000000; // INPUT NOMINAL PLAFON ASURANSI

        strcpy(karyawan.status_karyawan, "aktif"); // INPUT STATUS KARYAWAN

        strcpy(karyawan.password, numbers[x]);

        // MENYIMPAN SEMUA HASIL INPUTAN KE FILE
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawan);
        x++;
    }
    fclose(dataKaryawan); //MENUTUP FILE SETELAH DIGUNAKAN
}
//void insertReg() {
//    //DEKLARASI VARIABLE YANG DIGUNAKAN
//    char kodeReg[] = {"REG"};
//    int idterakhir = 0;
//    char *region[] = {"Jakarta", "Surabaya"};
//    int gjp[2] = {5000000, 4700000};
//
//    //MEMBUKA FILE DENGAN MODE AB+
//    dataRegion = fopen("DAT/dataReg.dat", "ab+");
//    //MEMBACA FILE UNTUK MENDAPATKAN ID TERAKHIR
//    while (fread(&reg, sizeof(reg), 1, dataRegion) == 1) {
//        //MEMBACA ANGKA PADA STRING ID REGION
//        sscanf(reg.id, "%*[^0-9]%d", &idterakhir);
//    }
//    fclose(dataRegion);
//    int x = 0;
//    dataRegion = fopen("DAT/dataReg.dat", "ab");
//    //INPUT DATA REGION
//    for (int i = idterakhir+1; i <= idterakhir+2; i++) {
//        //GENERATE ID OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INT MENYIMPANNYA KE VARIABLE IDTERAKHIR
//        snprintf(reg.id, sizeof(reg.id), "%s%d", kodeReg, i);
//
//
//        strcpy(reg.nama, region[x]);  //INPUT NAMA REGION
//        reg.gaji = gjp[x];  //INPUT GAJI POKOK REGION
//
//        // MENYIMPAN HASIL INPUT KE FILE
//        fwrite(&reg, sizeof(reg), 1, dataRegion);
//        x++;
//    }
//    //Menutup file setelah menerima input user
//    fclose(dataRegion);
//}
//void insertJabatan() {
//    char *nama[] = {"Karyawan",
//                    "Manager",
//                    "HRD",
//                    "Finance",
//                    "IT Admin"
//    };
//    int tunj[5] ={0,
//            2500000,
//            1500000,
//            3000000,
//            3000000,
//    };
//    //DEKLARASI VARIABLE YANG DIGUNAKAN
//    char kodeJabatan[] = {"JB"};
//    int idterakhir = 0;
//
//    File = fopen("DAT/dataJab.dat", "ab+");
//    while (fread(&jabatan, sizeof(jabatan), 1, File) == 1){
//        sscanf(jabatan.id, "%*[^0-9]%d", &idterakhir);
//    }
//    fclose(File);
//
//    int x = 0;
//    //Membuka file
//    File = fopen("DAT/dataJab.dat", "wb");
//    //Looping penambahan karyawan
//    for (int i = idterakhir + 1; i <= idterakhir + 5; i++) {
//        snprintf(jabatan.id, sizeof(jabatan.id), "%s%d", kodeJabatan, i);
//
//        strcpy(jabatan.nama, nama[x]);
//        jabatan.tunjangan = tunj[x];
//        fwrite(&jabatan, sizeof(jabatan), 1, File);
//        x++;
//    }
//    fclose(File);
//}
//void insertCabang() {
//    char kodecabang[] = "BRC";
//    int idterakhir = 0;
//    char idReg[10];
//
//    // MEMBUKA FILE DENGAN MODE AB+ UNTUK MENGETAHUI ID TERAKHIR YANG TELAH DITAMBAHKAN
//    dataCabang = fopen("DAT/dataCab.dat", "ab+");
//    // MEMBACA FILE UNTUK MENDAPATKAN ID CABANG TERAKHIR
//    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
//        // MEMBACA BAGIAN INTEGER DARI STRING ID CABANG KEMUDIAN INTEGER HASIL PEMBACAAN DISIMPAN DI VARIABEL IDTERAKHIR
//        sscanf(cabang.id_cabang, "%*[^0-9]%d", &idterakhir);
//    }
//    fclose(dataCabang);
//    int x = 0;
//    dataCabang = fopen("DAT/dataCab.dat", "wb");
//    //LOOPING PEMBUATAN ID CABANG SESUAI INPUTAN USER
//    for (int i = idterakhir+1; i <= idterakhir+n; i++) {
//        //GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
//        snprintf(cabang.id_cabang, sizeof(cabang.id_cabang), "%s%d", kodecabang, i);
//
//        gotoxy(17, 17); getteks(idReg, 10);
//        //INPUT ALAMAT CABANG
//        gotoxy(17, 22); getteks(cabang.alamat_cabang, 30);
//
//        //MENYIMPAN KE DALAM FILE
//        fwrite(&cabang, sizeof(cabang), 1, dataCabang);
//        x++;
//    }
//    fclose(dataCabang); //MENUTUP FILE SETELAH DIGUNAKAN
//}
//void insertRating(int n) {
//    int x = 0;
//    char *rat[] = {"S", "A", "B", "C", "D"};
//    char *ket[] ={"Sangat Baik", "Baik", "Standar", "Kurang", "Sangat Kurang"};
//    int bonus[5] = {500000, 300000, 100000, 20000, 0};
//    dataRating = fopen("DAT/dataRating.dat", "wb");
//    //Looping penambahan karyawan
//    for (int i = 1; i <= n; i++) {
//        strcpy(rating.kode_rating, rat[x]);
//        strcpy(rating.nama, ket[x]);
//        rating.bonus_rating = bonus[x];
//        fwrite(&rating, sizeof(rating), 1, dataRating);
//        x++;
//    }
//    fclose(dataRating);
//}
//void insertTPINJAM(int n) {
//    int max[5] = {2500000, 5000000, 7500000, 10000000};
//    int dur[5] = {90, 120, 240, 360};
//    int idterakhir = 0;
//    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "wb+");
//    while (fread(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman) == 1) {
//        sscanf(tipePinjam.id_tipePinjaman, "%*[^0-9]%d", &idterakhir);
//    }
//    fclose(data_tipePinjaman);
//
//    int x = 0;
//    data_tipePinjaman = fopen("DAT/datatipePinjaman.dat", "wb");
//    for (int i = idterakhir + 1; i <= idterakhir + n; i++) {
//        snprintf(tipePinjam.id_tipePinjaman, sizeof(tipePinjam.id_tipePinjaman), "%s%d", kodeTipePinjaman, i);
//
//        tipePinjam.max_tipePinjaman = max[x];
//        tipePinjam.durasiPinjam = dur[x];
//        fwrite(&tipePinjam, sizeof(tipePinjam), 1, data_tipePinjaman);
//        x++;
//    }
//    fclose(data_tipePinjaman);
//    cleanKiri();
//    cleanKanan();
//}

void insertClaim(char idEmp[], char tgl[]) {
    char kdClaim[] = "CA";
    int idterakhir = 0;

    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "ab+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
        sscanf(trClaim.idClaim, "%*[^0-9]%d", &idterakhir);
    }
    fclose(dataClaimAsuransi);

    dataClaimAsuransi  = fopen("DAT/TRdataClaim.dat", "ab");
    //Pencarian data dalam file menggunakan looping
    for (int i = idterakhir + 1; i <= idterakhir+1; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(trClaim.idClaim, sizeof(trClaim.idClaim), "%s%d", kdClaim, idterakhir+1); // ini untuk menggabungkan 2 variable
        strcpy(trClaim.idKrywn, idEmp);

        gotoxy(row, 5);SetColor(colorScText);
        printf("jml");
        getRp(&trClaim.jmlClaim, 5, 7, row+14, 12);
        printf("tmpt");
        gotoxy(row+10, 17); getteks(trClaim.tempatClaim, 18);
        printf("ket");
        gotoxy(row+10, 22); getteks(trClaim.keterangan, 18);
        strcpy(trClaim.tgl, tgl);
        strcpy(trClaim.status, "Pending");

        fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(dataClaimAsuransi);
}
void insertClaimNovember() {
    char kdClaim[] = "CA";
    int idterakhir = 0;
    char *nama[] = {"EMP1",
                    "EMP1",
                    "EMP1",
                    "EMP5",
                    "EMP7",
                    "EMP5",
                    "EMP6",
                    "EMP6",
                    "EMP6",
                    "EMP21",
                    "EMP21",
                    "EMP20",
                    "EMP24",
                    "EMP19",
                    "EMP24",
                    "EMP3",
                    "EMP1",
                    "EMP21",
                    "EMP5",
                    "EMP8",
                    "EMP5",
                    "EMP6",
                    "EMP6",
                    "EMP6",
                    "EMP21"
    };
    char *tgl[] = {"28-11-2023",
                   "10-11-2023",
                   "12-11-2023",
                   "02-11-2023",
                   "28-11-2023",
                   "20-11-2023",
                   "29-11-2023",
                   "20-11-2023",
                   "02-11-2023",
                   "26-11-2023",
                   "29-11-2023",
                   "03-11-2023",
                   "28-11-2023",
                   "30-11-2023",
                   "29-11-2023",
                   "15-11-2023",
                   "11-11-2023",
                   "25-11-2023",
                   "20-11-2023",
                   "23-11-2023",
                   "28-11-2023",
                   "03-11-2023",
                   "06-11-2023",
                   "12-11-2023",
                   "17-11-2023"};

    int jml[] = { 200000,
                  50000,
                  75000,
                  125000,
                  250000,
                  45000,
                  55000,
                  95000,
                  300000,
                  450000,
                  300000,
                  30000,
                  85000,
                  45000,
                  150000,
                  350000,
                  120000,
                  90000,
                  180000,
                  200000,
                  300000,
                  50000,
                  75000,
                  125000,
                  250000,
                  45000};

    char data[25][20] = {
            "RS Medika",
            "Apotek Manjur",
            "RS Citra",
            "RS Citra",
            "RS Medika",
            "Apotek Sido",
            "Apotek Manjur",
            "Apotek Sido",
            "RS Citra",
            "RS Medika",
            "RS Medika",
            "Apotek Manjur",
            "RS Citra",
            "Apotek Sido",
            "RS Medika",
            "RS Santosa",
            "Apotek Manjur",
            "RS Citra",
            "Apotek Sido",
            "RS Medika",
            "RS Medika",
            "Apotek Manjur",
            "RS Citra",
            "Apotek Sido",
            "RS Medika"
    };

    char tugas_kesehatan[][20] = {
            "Periksa Mata",
            "Obat Gatel",
            "Periksa Telinga",
            "Cek Kolesterol",
            "Periksa Gigi",
            "Obat Batuk",
            "Obat Pilek",
            "Obat Ruam",
            "MCU",
            "MCU",
            "Perawatan Gigi",
            "Obat Pusing",
            "Obat Oles Luka",
            "Obat Pilek",
            "Periksa Telinga",
            "Cek Darah",
            "Periksa Gigi",
            "Cek Kolesterol",
            "Perawatan Gigi",
            "Obat Batuk",
            "Obat Pilek",
            "Obat Ruam",
            "MCU",
            "MCU",
            "Obat Pusing"
    };



    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "wb+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trClaim, sizeof(trClaim), 1, dataClaimAsuransi) == 1) {
//        membaca bagian integer dari string id Region kemudian integer hasil pembacaan disimpan di variabel idterakhir
        sscanf(trClaim.idClaim, "%*[^0-9]%d", &idterakhir);
    }
    fclose(dataClaimAsuransi);
    int x = 0;
    dataClaimAsuransi  = fopen("DAT/TRdataClaim.dat", "wb");
    //Pencarian data dalam file menggunakan looping
    for (int i = idterakhir + 1; i <= idterakhir+15; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(trClaim.idClaim, sizeof(trClaim.idClaim), "%s%d", kdClaim, i); // ini untuk menggabungkan 2 variable
        strcpy(trClaim.idKrywn, nama[x]);
        trClaim.jmlClaim = jml[x];
        strcpy(trClaim.tempatClaim, data[x]);
        strcpy(trClaim.keterangan, tugas_kesehatan[x]);
        strcpy(trClaim.tgl, tgl[x]);
        strcpy(trClaim.status, "Pending");
        fwrite(&trClaim, sizeof(trClaim), 1, dataClaimAsuransi);
        x++;
    }
//    fclose(dataKaryawan);
    fclose(dataClaimAsuransi);
}
void insertClaimDesember() {
    char kdClaim[] = "CA";
    int idterakhir = 0;
    char *nama[] = {"EMP1",
                    "EMP1",
                    "EMP1",
                    "EMP5",
                    "EMP7",
                    "EMP5",
                    "EMP6",
                    "EMP6",
                    "EMP6",
                    "EMP21",
                    "EMP21",
                    "EMP20",
                    "EMP24",
                    "EMP19",
                    "EMP24",
                    "EMP3",
                    "EMP1",
                    "EMP21",
                    "EMP5",
                    "EMP8",
                    "EMP5",
                    "EMP6",
                    "EMP6",
                    "EMP6",
                    "EMP21"
    };
    char *tgl[] = {"02-12-2023",
                   "05-12-2023",
                   "10-12-2023",
                   "14-12-2023",
                   "18-12-2023",
                   "21-12-2023",
                   "26-12-2023",
                   "01-12-2023",
                   "04-12-2023",
                   "09-12-2023",
                   "13-12-2023",
                   "16-12-2023",
                   "22-12-2023",
                   "25-12-2023",
                   "30-12-2023",
                   "07-12-2023",
                   "11-12-2023",
                   "15-12-2023",
                   "20-12-2023",
                   "23-12-2023",
                   "28-12-2023",
                   "03-12-2023",
                   "06-12-2023",
                   "12-12-2023",
                   "17-12-2023"};

    int jml[] = { 200000,
                  50000,
                  75000,
                  125000,
                  250000,
                  45000,
                  55000,
                  95000,
                  300000,
                  450000,
                  300000,
                  30000,
                  85000,
                  45000,
                  150000,
                  350000,
                  120000,
                  90000,
                  180000,
                  200000,
                  300000,
                  50000,
                  75000,
                  125000,
                  250000,
                  45000};

    char data[25][20] = {
                    "RS Medika",
                    "Apotek Manjur",
                    "RS Citra",
                    "RS Citra",
                    "RS Medika",
                    "Apotek Sido",
                    "Apotek Manjur",
                    "Apotek Sido",
                    "RS Citra",
                    "RS Medika",
                    "RS Medika",
                    "Apotek Manjur",
                    "RS Citra",
                    "Apotek Sido",
                    "RS Medika",
                    "RS Santosa",
                    "Apotek Manjur",
                    "RS Citra",
                    "Apotek Sido",
                    "RS Medika",
                    "RS Medika",
                    "Apotek Manjur",
                    "RS Citra",
                    "Apotek Sido",
                    "RS Medika"
    };

    char tugas_kesehatan[][20] = {
            "Periksa Mata",
            "Obat Gatel",
            "Periksa Telinga",
            "Cek Kolesterol",
            "Periksa Gigi",
            "Obat Batuk",
            "Obat Pilek",
            "Obat Ruam",
            "MCU",
            "MCU",
            "Perawatan Gigi",
            "Obat Pusing",
            "Obat Oles Luka",
            "Obat Pilek",
            "Periksa Telinga",
            "Cek Darah",
            "Periksa Gigi",
            "Cek Kolesterol",
            "Perawatan Gigi",
            "Obat Batuk",
            "Obat Pilek",
            "Obat Ruam",
            "MCU",
            "MCU",
            "Obat Pusing"
    };



    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "wb+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trClaim, sizeof(trClaim), 1, dataClaimAsuransi) == 1) {
//        membaca bagian integer dari string id Region kemudian integer hasil pembacaan disimpan di variabel idterakhir
        sscanf(trClaim.idClaim, "%*[^0-9]%d", &idterakhir);
    }
    fclose(dataClaimAsuransi);
    int x = 0;
    dataClaimAsuransi  = fopen("DAT/TRdataClaim.dat", "wb");
    //Pencarian data dalam file menggunakan looping
    for (int i = idterakhir + 1; i <= idterakhir+15; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(trClaim.idClaim, sizeof(trClaim.idClaim), "%s%d", kdClaim, i); // ini untuk menggabungkan 2 variable
        strcpy(trClaim.idKrywn, nama[x]);
        trClaim.jmlClaim = jml[x];
        strcpy(trClaim.tempatClaim, data[x]);
        strcpy(trClaim.keterangan, tugas_kesehatan[x]);
        strcpy(trClaim.tgl, tgl[x]);
        strcpy(trClaim.status, "Pending");
        fwrite(&trClaim, sizeof(trClaim), 1, dataClaimAsuransi);
        x++;
    }
//    fclose(dataKaryawan);
    fclose(dataClaimAsuransi);
}

void insertCutiSeptember() {
    char kdClaim[] = "CT";
    int idterakhir = 0;

    char tanggal_pengajuan[25][11] = {"02-09-2023", "05-09-2023", "10-09-2023", "14-09-2023", "18-09-2023",
                                      "21-09-2023", "26-09-2023", "01-09-2023", "04-09-2023", "09-09-2023",
                                      "13-09-2023", "16-09-2023", "22-09-2023", "25-09-2023", "30-09-2023",
                                      "07-09-2023", "11-09-2023", "15-09-2023", "20-09-2023", "23-09-2023",
                                      "28-09-2023", "03-09-2023", "06-09-2023", "12-09-2023", "17-09-2023"};

    char tanggal_cuti[25][11] = {"04-09-2023", "07-09-2023", "12-09-2023", "16-09-2023", "20-09-2023",
                                 "23-09-2023", "28-09-2023", "03-09-2023", "06-09-2023", "11-09-2023",
                                 "15-09-2023", "18-09-2023", "24-09-2023", "27-09-2023", "02-10-2023",
                                 "09-09-2023", "13-09-2023", "17-09-2023", "22-09-2023", "25-09-2023",
                                 "30-09-2023", "05-09-2023", "08-09-2023", "14-09-2023", "19-09-2023"};

    char keterangan[25][50] = {"Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis"};

    int lama[25] = {2, 1, 2, 1, 1,
                         1, 2, 2, 3, 2,
                         2, 1, 1, 2, 2,
                         3, 1, 2, 1, 1,
                         2, 2, 2, 1, 2};

    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    datatrCuti = fopen("DAT/TRdataCuti.dat", "ab+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
//        membaca bagian integer dari string id Region kemudian integer hasil pembacaan disimpan di variabel idterakhir
        sscanf(trCuti.idCuti, "%*[^0-9]%d", &idterakhir);
    }
    fclose(datatrCuti);
    int x = 0;

    datatrCuti = fopen("DAT/TRdataCuti.dat", "ab");
    //Pencarian data dalam file menggunakan looping
    for (int i = idterakhir + 1; i <= idterakhir+25; i++) {

        snprintf(trCuti.idCuti, sizeof(trCuti.idCuti), "%s%d", "CT", i);
        snprintf(trCuti.idKaryawan, sizeof(trCuti.idKaryawan), "%s%d", "EMP", x+1);
        int hari;
        if (checkCuti(hari, trCuti.idKaryawan) == 1) {
            trCuti.jumlahHari = lama[x];
            strcpy(trCuti.ketCuti, keterangan[x]);
            strcpy(trCuti.tglPengajuan, tanggal_pengajuan[x]);
            strcpy(trCuti.sts, "Diterima");
            strcpy(trCuti.tglCuti, tanggal_cuti[x]);

            fwrite(&trCuti, sizeof (dataCuti), 1, datatrCuti);
            updateSisaCuti(trCuti.idKaryawan, hari);
        } else {
            trCuti.jumlahHari = lama[x];
            strcpy(trCuti.ketCuti, keterangan[x]);
            strcpy(trCuti.tglPengajuan, tanggal_pengajuan[x]);
            strcpy(trCuti.tglCuti, tanggal_cuti[x]);
            strcpy(trCuti.sts, "Ditolak");

            fwrite(&trCuti, sizeof (dataCuti), 1, datatrCuti);
        }
        x++;
    }
    fclose(datatrCuti);
}
void findCutitoUpd() {
    int found;
    found = 0;
    char idCab[10];

    retype:
    gotoxy(row + 24, 15); getteks(idCab, 6);

    //Membuka file asli dengan mode rb
    datatrCuti = fopen("DAT/TRdataCuti.dat", "rb");
    datatrCutiTemp = fopen("TEMP/TRdataCutiTemp.dat", "wb");
    //Pencarian data dalam file menggunakan loopung
    while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
        strcpy(trCuti.sts, "Diterima");
        strcpy(trCuti.idCuti, trCuti.idCuti);
        strcpy(trCuti.idKaryawan, trCuti.idKaryawan);
        strcpy(trCuti.tglCuti, trCuti.tglCuti);
        strcpy(trCuti.tglPengajuan, trCuti.tglPengajuan);
        trCuti.jumlahHari = trCuti.jumlahHari;
        strcpy(trCuti.ketCuti, trCuti.ketCuti);

        fwrite(&trCuti, sizeof(trCuti), 1, datatrCutiTemp);
       /* while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
            fwrite(&trCuti, sizeof(trCuti), 1, datatrCutiTemp);
        }*/
    }


    //Menutup file asli dan file temporary setelah digunakan
    fclose(datatrCuti);
    fclose(datatrCutiTemp);
}
void updateDataCuti() {
    //Memanggil prosedur pencarian id kota
    findCutitoUpd();
    //Membuka file asli dengan mode rb
    datatrCuti = fopen("DAT/TRdataCuti.dat", "wb");
    datatrCutiTemp = fopen("TEMP/TRdataCutiTemp.dat", "rb");

    //Proses menyalin kembali semua data dari file temporary ke file asli
    while (fread(&trCuti, sizeof(trCuti), 1, datatrCutiTemp)==1) {
        fwrite(&trCuti, sizeof(trCuti), 1, datatrCuti);
    }

    //Menutup file asli dan file temporary setelah digunakan
    fclose(datatrCuti);
    fclose(datatrCutiTemp);
}
void insertCutiOktober() {
    char kdClaim[] = "CT";
    int idterakhir = 0;

    char tanggal_pengajuan[25][11] = {"02-10-2023", "05-10-2023", "10-10-2023", "14-10-2023", "18-10-2023",
                                      "21-10-2023", "26-10-2023", "01-10-2023", "04-10-2023", "09-10-2023",
                                      "13-10-2023", "16-10-2023", "22-10-2023", "25-10-2023", "30-10-2023",
                                      "07-10-2023", "11-10-2023", "15-10-2023", "20-10-2023", "23-10-2023",
                                      "28-10-2023", "03-10-2023", "06-10-2023", "12-10-2023", "17-10-2023"};

    char tanggal_cuti[25][11] = {"04-10-2023", "07-10-2023", "12-10-2023", "16-10-2023", "20-10-2023",
                                 "23-10-2023", "28-10-2023", "03-10-2023", "06-10-2023", "11-10-2023",
                                 "15-10-2023", "18-10-2023", "24-10-2023", "27-10-2023", "01-11-2023",
                                 "09-10-2023", "13-10-2023", "17-10-2023", "22-10-2023", "25-10-2023",
                                 "30-10-2023", "05-10-2023", "08-10-2023", "14-10-2023", "19-10-2023"};

    char keterangan[25][50] = {"Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Pribadi", "Liburan Keluarga", "Acara Spesial", "Keperluan Medis"};

    int lama[25] = {2, 1, 1, 2, 2,
                    2, 2, 2, 3, 2,
                    1, 1, 2, 1, 1,
                    1, 2, 1, 1, 2,
                    2, 2, 2, 1, 1};

    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    datatrCuti = fopen("DAT/TRdataCuti.dat", "ab+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
//        membaca bagian integer dari string id Region kemudian integer hasil pembacaan disimpan di variabel idterakhir
        sscanf(trCuti.idCuti, "%*[^0-9]%d", &idterakhir);
    }
    fclose(datatrCuti);
    int x = 0;

    datatrCuti = fopen("DAT/TRdataCuti.dat", "ab");
    //Pencarian data dalam file menggunakan looping
    for (int i = idterakhir + 1; i <= idterakhir+15; i++) {

        snprintf(trCuti.idCuti, sizeof(trCuti.idCuti), "%s%d", "CT", i);
        snprintf(trCuti.idKaryawan, sizeof(trCuti.idKaryawan), "%s%d", "EMP", x+1);
        int hari;
        if (checkCuti(hari, trCuti.idKaryawan) == 1) {
            trCuti.jumlahHari = lama[x];
            strcpy(trCuti.ketCuti, keterangan[x]);
            strcpy(trCuti.tglPengajuan, tanggal_pengajuan[x]);
            strcpy(trCuti.sts, "Diterima");
            strcpy(trCuti.tglCuti, tanggal_cuti[x]);

            fwrite(&trCuti, sizeof (dataCuti), 1, datatrCuti);
            updateSisaCuti(trCuti.idKaryawan, hari);
        } else {
            trCuti.jumlahHari = lama[x];
            strcpy(trCuti.ketCuti, keterangan[x]);
            strcpy(trCuti.tglPengajuan, tanggal_pengajuan[x]);
            strcpy(trCuti.tglCuti, tanggal_cuti[x]);
            strcpy(trCuti.sts, "Ditolak");

            fwrite(&trCuti, sizeof (dataCuti), 1, datatrCuti);
        }
        x++;
    }
    fclose(datatrCuti);
}
void insertCutiDesember() {
    char kdClaim[] = "CT";
    int idterakhir = 0;

    char tanggal_pengajuan[25][11] = {"02-12-2023", "05-12-2023", "10-12-2023", "14-12-2023", "18-12-2023",
                                      "21-12-2023", "26-12-2023", "01-12-2023", "04-12-2023", "09-12-2023",
                                      "13-12-2023", "16-12-2023", "22-12-2023", "25-12-2023", "30-12-2023",
                                      "07-12-2023", "11-12-2023", "15-12-2023", "20-12-2023", "23-12-2023",
                                      "28-12-2023", "03-12-2023", "06-12-2023", "12-12-2023", "17-12-2023"};

    char tanggal_cuti[25][11] = {"04-12-2023", "07-12-2023", "12-12-2023", "16-12-2023", "20-12-2023",
                                 "23-12-2023", "28-12-2023", "03-12-2023", "06-12-2023", "11-12-2023",
                                 "15-12-2023", "18-12-2023", "24-12-2023", "27-12-2023", "02-01-2024",
                                 "09-12-2023", "13-12-2023", "17-12-2023", "22-12-2023", "25-12-2023",
                                 "30-12-2023", "05-12-2023", "08-12-2023", "14-12-2023", "19-12-2023"};

    char keterangan[25][50] = {"Liburan Singkat Desember", "Kegiatan Akhir Tahun", "Liburan Keluarga", "Acara Natal", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Akhir Tahun", "Liburan Akhir Tahun", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Akhir Tahun", "Liburan Keluarga", "Acara Natal", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Akhir Tahun", "Liburan Akhir Tahun", "Acara Spesial", "Keperluan Medis",
                               "Liburan Singkat", "Kegiatan Akhir Tahun", "Liburan Keluarga", "Acara Natal", "Keperluan Medis"};

    int lama[25] = {2, 3, 2, 2, 2,
                    2, 1, 3, 2, 2,
                    2, 1, 2, 2, 2,
                    2, 3, 3, 2, 2,
                    2, 1, 2, 2, 2};

    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    datatrCuti = fopen("DAT/TRdataCuti.dat", "ab+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trCuti, sizeof(trCuti), 1, datatrCuti) == 1) {
//        membaca bagian integer dari string id Region kemudian integer hasil pembacaan disimpan di variabel idterakhir
        sscanf(trCuti.idCuti, "%*[^0-9]%d", &idterakhir);
    }
    fclose(datatrCuti);
    int x = 0;
    datatrCuti = fopen("DAT/TRdataCuti.dat", "ab");
    //Pencarian data dalam file menggunakan looping
    for (int i = idterakhir + 1; i <= idterakhir+15; i++) {
        // GENERATE ID CABANG OTOMATIS DENGAN MENGGABUNGKAN STRING DAN INTEGER
        snprintf(trCuti.idCuti, sizeof(trCuti.idCuti), "%s%d", kdClaim, i); // ini untuk menggabungkan 2 variable
        snprintf(trCuti.idKaryawan, sizeof(trCuti.idKaryawan), "%s%d", "EMP", x+1);
        trCuti.jumlahHari = lama[x];

        updateSisaCuti(trCuti.idKaryawan, lama[x]);

        strcpy(trCuti.ketCuti, keterangan[x]);
        strcpy(trCuti.tglCuti, tanggal_cuti[x]);
        strcpy(trCuti.tglPengajuan, tanggal_pengajuan[x]);
        strcpy(trCuti.sts, "Pending");
        fwrite(&trCuti, sizeof(trCuti), 1, datatrCuti);
        x++;
    }
//    fclose(dataKaryawan);
    fclose(datatrCuti);
}

void insertPinjamNovember() {
    char *nama[] = {"EMP1",
                    "EMP1",
                    "EMP1",
                    "EMP5",
                    "EMP5",
                    "EMP5",
                    "EMP6",
                    "EMP6",
                    "EMP6",
                    "EMP21",
                    "EMP21",
                    "EMP21",
                    "EMP24",
                    "EMP24",
                    "EMP24"
    };

    char *tgl[] = {"28-11-2023",
                   "10-11-2023",
                   "12-11-2023",
                   "02-11-2023",
                   "28-11-2023",
                   "20-11-2023",
                   "29-11-2023",
                   "20-11-2023",
                   "02-11-2023",
                   "26-11-2023",
                   "29-11-2023",
                   "03-11-2023",
                   "28-11-2023",
                   "30-11-2023",
                   "29-11-2023"
    };
    int jmlPinjam[] = {1900000, 1600000, 1500000, 1100000, 2400000, 1700000, 2100000, 1200000, 2200000, 2500000, 2500000, 1400000, 2300000, 1700000, 1800000};

    char kodePeminjaman[] = {"LOAN"};
    int id_terakhir = 0;
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "wb+");
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1)
    {
        //MEMBACA BAGIAN INTEGER DARI STRING ID Peminjaman KEMUDIAN INTEGER HASIL PEMBACAAN DISIMPAN DI VARIABEL IDTERAKHIR
        sscanf(trPinjam.id_PPinjam, "%*[^0-9]%d", &id_terakhir);
    }
    int x =0;
    for (int i = id_terakhir+1; i <= id_terakhir + 15; i++)
    {
        gotoxy(row, 5);SetColor(colorScText);
        // generate id otomatis denan menggabungkan 2 variable string & integer
        snprintf(trPinjam.id_PPinjam, sizeof (trPinjam.id_PPinjam), "%s%d", kodePeminjaman, i);
        strcpy (trPinjam.id_karyawan, nama[x]); // copy id karyawan otomatis
        strcpy(trPinjam.tgl_pinjam, tgl[x]); // otomatis mengisi tanggal peminjaman
        // memasukkan nominal peminjaman karyawan
        trPinjam.jumlah_pinjam = jmlPinjam[x];
        //mencari tipePinjaman bedasarkan nominal pinjaman
        tipePinjaman(jmlPinjam[x]);
        // menghitung bunga karyawan
        trPinjam.bunga_pinjam = hitungBunga(jmlPinjam[x]);

        // kalkulasi kapan tempo karyawan
        kalkulasiTempo(tgl[x], trPinjam.id_tipePinjam); // kalkulasi tempo pembayaran.
        strcpy(trPinjam.status_pinjam, "Pending"); // otomatis mengisi pending...
        fwrite(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang);
        x++;
    }
    fclose(dataPeminjamanUang);
}
void insertPinjam(char idEmp[], char tgl[]) {
    int nominalPinjam;
    char kodePeminjaman[] = {"LOAN"};
    int id_terakhir = 0;
    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "ab+");
    while (fread(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang) == 1)
    {
        //MEMBACA BAGIAN INTEGER DARI STRING ID Peminjaman KEMUDIAN INTEGER HASIL PEMBACAAN DISIMPAN DI VARIABEL IDTERAKHIR
        sscanf(trPinjam.id_PPinjam, "%*[^0-9]%d", &id_terakhir);
    }
    for (int i = id_terakhir+1; i <= id_terakhir + 1; i++)
    {
        gotoxy(row, 5);SetColor(colorScText);
        // generate id otomatis denan menggabungkan 2 variable string & integer
        snprintf(trPinjam.id_PPinjam, sizeof (trPinjam.id_PPinjam), "%s%d", kodePeminjaman, i);
        strcpy (trPinjam.id_karyawan, idEmp); // copy id karyawan otomatis
        strcpy(trPinjam.tgl_pinjam, tgl); // otomatis mengisi tanggal peminjaman
        // memasukkan nominal peminjaman karyawan
        printf("jml");
        getRp(&trPinjam.jumlah_pinjam, 5, 8, row+14, 12);
        //mencari tipePinjaman bedasarkan nominal pinjaman
        tipePinjaman(trPinjam.jumlah_pinjam);
        // menghitung bunga karyawan
        trPinjam.bunga_pinjam = hitungBunga(trPinjam.jumlah_pinjam);
        char rp[10];
        rupiah(trPinjam.bunga_pinjam, rp);
        gotoxy(row+12, 17); printf("Rp. %s", rp);

        // kalkulasi kapan tempo karyawan
        kalkulasiTempo(tgl, trPinjam.id_tipePinjam); // kalkulasi tempo pembayaran.
        strcpy(trPinjam.status_pinjam, "Pending"); // otomatis mengisi pending...
        gotoxy(row+12, 22); printf("%s", trPinjam.tanggalTempo);
        fwrite(&trPinjam, sizeof(trPinjam), 1, dataPeminjamanUang);
    }
    fclose(dataPeminjamanUang);
}

void insertLembur(char idEmp[], char ajuan[12]) {
    char kodeLembur[] = {"LBR"};
    int id_terakhir = 0;
    int x;
    char idGJtemp[20];

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

        char tglLbr[15];
        printf("tglLbr"); fflush(stdin);
        gotoxy(row+10, 12); getDate(lembur.tggl_lembur);
        int jam;
        printf("jamLbr");
        fflush(stdin);
        gotoxy(row+10, 17); getnum(&lembur.lama_lembur, 1); fflush(stdin);
        lembur.gaji_lembur = lembur.lama_lembur*50000; // mengisi upah lembur

        strcpy(lembur.tggl_pengajuan, ajuan); // mengisi tanggal pengajuan
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

int updmr() {
    SetColor(text2);
    int lebar = 10;
    int tinggi = 20;
    for (int j = 12; j < 14+tinggi; j++) {
        for (int i = 127; i < lebar+127; i++) {
            printASCII(244, i, j);
        }
    }
    SetColor(colorScText);
    printASCII(200, 126,34);
    printASCII(201, 126,11);
    printASCII(187, 137,11);
    printASCII(188, 137,34);

    SetColor(colorMainText);
    gotoxy(126, 9);printf("UPDATE RATING");
    gotoxy(132, 14); printf("S");
    gotoxy(132, 18); printf("A");
    gotoxy(132, 22); printf("B");
    gotoxy(132, 26); printf("C");
    gotoxy(132, 30); printf("D");

    int pil = 1;
    int banyakMenu = 5;
    while (1) {
        for (int i = 1; i <= banyakMenu; i++) {
            if (i == pil) {
                SetColor(colorScText);
                printASCII(174, 137, 14 + (i - 1) * 4);
                printASCII(174, 138, 14 + (i - 1) * 4);
                printASCII(174, 139, 14 + (i - 1) * 4);
            } else {
                SetColor(colorMainText);
                gotoxy(137, 14 + (i - 1) * 4);
                printf("   ");
            }
        }

        char ch = getch();
        switch (ch) {
            case 72:  // Panah atas
                if (pil > 1) {
                    pil--;
                }
                break;
            case 80:  // Panah bawah
                if (pil < banyakMenu) {
                    pil++;
                }
                break;
            case 13:  // Tombol Enter
                cleanKiri();
                return pil;
        }
    }
}
void insertMr(char idBrc[], char tglMR[]) {
    int leftMarg  = 5;
    char idMR[] = "MR";
    int idterakhir = 0;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");

    // Membuka file dengan mode ab+ untuk mengetahui id terakhir yang telah ditambahkan
    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "ab+");
    // Membaca file untuk mendapatkan Id kota terakhir
    while (fread(&trRating, sizeof(trRating), 1, dataTrRating) == 1) {
//        membaca bagian integer dari string id Region kemudian integer hasil pembacaan disimpan di variabel idterakhir
        sscanf(trRating.idMR, "%*[^0-9]%d", &idterakhir);
    }
    //Pencarian data dalam file menggunakan looping
    int i = 1;
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(karyawan.id_cabang, idBrc) == 0 && (strcmp(karyawan.status_karyawan, "Aktif") == 0 || strcmp(karyawan.status_karyawan, "aktif") == 0) && strcmp(karyawan.id_jabatan, "JB1") == 0) {
            cleanKiri();
            SetColor(colorScText);
            gotoxy(5, 5); printf("ID Karyawan");
            gotoxy(5, 7); printf("ID Cabang");
            gotoxy(5, 9); printf("ID Jabatan");
            gotoxy(5, 11); printf("Nama Karyawan");
            gotoxy(5, 13); printf("Tanggal Lahir");
            gotoxy(5, 15); printf("Alamat");
            gotoxy(5, 17); printf("Sex");
            gotoxy(5, 19); printf("Tanggal Mulai Kerja");
            gotoxy(5, 21); printf("Jatah Cuti");
            gotoxy(5, 23); printf("Plafon Asuransi");
            gotoxy(5, 25); printf("Status");

            snprintf(trRating.idMR, sizeof(trRating.idMR), "%s%d", idMR, idterakhir + 1);

            gotoxy(leftMarg+50, 5); printf("| %-40s|", karyawan.id_karyawan);
            gotoxy(leftMarg+50, 7); printf("| %-40s|", karyawan.id_cabang);
            gotoxy(leftMarg+50, 9); printf("| %-40s|", karyawan.id_jabatan);
            gotoxy(leftMarg+50, 11); printf("| %-40s|", karyawan.nama_karyawan);
            gotoxy(leftMarg+50, 13); printf("| %-40s|", karyawan.tanggalLahir_karyawan);
            gotoxy(leftMarg+50, 15); printf("| %-40s|", karyawan.alamat_karyawan);
            gotoxy(leftMarg+50, 17); printf("| %-40s|", karyawan.gender_karyawan);
            gotoxy(leftMarg+50, 19); printf("| %-40s|", karyawan.tgglMulaiKerja_karyawan);
            gotoxy(leftMarg+50, 21); printf("| %-40d|", karyawan.jatahCuti_karyawan);
            gotoxy(leftMarg+50, 23); printf("| %-40d|", karyawan.plafonAsuransi);
            gotoxy(leftMarg+50, 25); printf("| %-40s|", karyawan.status_karyawan);

            strcpy(trRating.idKrywn, karyawan.id_karyawan);
            switch (updmr()) {
                case 1:
                    strcpy(trRating.kRating,"S");
                    break;
                case 2:
                    strcpy(trRating.kRating,"A");
                    break;
                case 3:
                    strcpy(trRating.kRating,"B");
                    break;
                case 4:
                    strcpy(trRating.kRating,"C");
                    break;
                case 5:
                    strcpy(trRating.kRating,"D");
                    break;
            }

            strcpy(trRating.tgl, tglMR);

            dataRating = fopen ("DAT/dataRating.dat", "rb");
            while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
                if (strcmp(trRating.kRating, rating.kode_rating) == 0) {
                    trRating.bonus = rating.bonus_rating;
                    break;
                }
            }
            fclose(dataRating);

            fwrite(&trRating, sizeof(trRating), 1, dataTrRating);
            idterakhir++;
            i++;
        }
    }

    fclose(dataKaryawan);
    fclose(dataTrRating);
    showMessage("ATTENTION!", "Data Berhasil Disimpan!\nSee You Next Month!");
    cleanKiri();
}
void insertGaji() {
//    createGajiBase("BRC1");
    dataGajian = fopen("DAT/TRdataGajian.dat", "ab");
    dataGajianTemp = fopen("TEMP/TRdataGajianTemp.dat", "rb");
    while (fread(&gaji, sizeof(gaji), 1, dataGajianTemp) == 1) {
        fwrite(&gaji, sizeof(gaji), 1, dataGajian);
    }
    fclose(dataGajianTemp);
    fclose(dataGajian);
}

void delgajiBulanan(int sasi, int taun) {
    int hri, bulan, thun;

    dataGajian = fopen("DAT/TRdataGajian.dat", "rb");
    dataGajianTemp = fopen("TEMP/TRdataGajianTemp.dat", "wb");
    while (fread(&gaji, sizeof(gaji), 1, dataGajian) == 1) {
        bulanTahun(gaji.tanggal, &hri, &bulan, &thun);
        if (bulan == sasi && thun == taun) {
            continue;
        } else {
            fwrite(&gaji, sizeof(gaji), 1, dataGajianTemp);
        }
    }
    fclose(dataGajianTemp);
    fclose(dataGajian);

    dataGajian = fopen("DAT/TRdataGajian.dat", "wb");
    dataGajianTemp = fopen("TEMP/TRdataGajianTemp.dat", "rb");
    while (fread(&gaji, sizeof(gaji), 1, dataGajianTemp) == 1) {
        fwrite(&gaji, sizeof(gaji), 1, dataGajian);
    }
    fclose(dataGajianTemp);
    fclose(dataGajian);
}
void delclaimBulanan(int sasi, int taun) {
    int hri, bulan, thun;

    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "rb");
    dataClaimAsuransiTemp = fopen("TEMP/TRdataClaimTemp.dat", "wb");
    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi) == 1) {
        bulanTahun(trClaim.tgl, &hri, &bulan, &thun);
        if (bulan == sasi && thun == taun) {
            continue;
        } else {
            fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransiTemp);
        }
    }
    fclose(dataClaimAsuransiTemp);
    fclose(dataClaimAsuransi);

    dataClaimAsuransi = fopen("DAT/TRdataClaim.dat", "wb");
    dataClaimAsuransiTemp = fopen("TEMP/TRdataClaimTemp.dat", "rb");
    while (fread(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransiTemp) == 1) {
        fwrite(&trClaim, sizeof(data_trClaim), 1, dataClaimAsuransi);
    }
    fclose(dataClaimAsuransiTemp);
    fclose(dataClaimAsuransi);
}
void delcutiBulanan(int sasi, int taun) {
    int hri, bulan, thun;

    datatrCuti = fopen("DAT/TRdataCuti.dat", "rb");
    datatrCutiTemp = fopen("TEMP/TRdataCutiTemp.dat", "wb");
    while (fread(&trCuti, sizeof(dataCuti), 1, datatrCuti) == 1) {
        bulanTahun(trCuti.tglPengajuan, &hri, &bulan, &thun);
        if (bulan == sasi && thun == taun) {
            continue;
        } else {
            fwrite(&trCuti, sizeof(dataCuti), 1, datatrCutiTemp);
        }
    }
    fclose(datatrCuti);
    fclose(datatrCutiTemp);

    datatrCuti = fopen("DAT/TRdataCuti.dat", "wb");
    datatrCutiTemp = fopen("TEMP/TRdataCutiTemp.dat", "rb");
    while (fread(&trCuti, sizeof(dataCuti), 1, datatrCutiTemp) == 1) {
        fwrite(&trCuti, sizeof(dataCuti), 1, datatrCuti);
    }
    fclose(datatrCuti);
    fclose(datatrCutiTemp);
}
void dellemburBulanan(int sasi, int taun) {
    int hri, bulan, thun;

    dataLembur = fopen ("DAT/TRdataLembur.dat", "rb");
    dataLemburTemp = fopen("TEMP/TRdataLemburTemp.dat", "wb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLembur) == 1) {
        bulanTahun(lembur.tggl_pengajuan, &hri, &bulan, &thun);
        if (bulan == sasi && thun == taun) {
            continue;
        } else {
            fwrite(&lembur, sizeof(data_Lembur), 1, dataLemburTemp);
        }
    }
    fclose(dataLembur);
    fclose(dataLemburTemp);

    dataLembur = fopen ("DAT/TRdataLembur.dat", "wb");
    dataLemburTemp = fopen("TEMP/TRdataLemburTemp.dat", "rb");
    while (fread(&lembur, sizeof(data_Lembur), 1, dataLemburTemp) == 1) {
        fwrite(&lembur, sizeof(data_Lembur), 1, dataLembur);
    }
    fclose(dataLembur);
    fclose(dataLemburTemp);
}
void delPinjamBulanan(int sasi, int taun) {
    int hri, bulan, thun;

    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "rb");
    dataPeminjamanUangTemp = fopen ("TEMP/TRdataPinjamanTemp.dat", "wb");
    while (fread(&trPinjam, sizeof(datatrPinjam), 1,dataPeminjamanUang) == 1) {
        bulanTahun(trPinjam.tgl_pinjam, &hri, &bulan, &thun);
        if (bulan == sasi && thun == taun) {
            continue;
        } else {
            fwrite(&trPinjam, sizeof(datatrPinjam), 1, dataPeminjamanUangTemp);
        }
    }
    fclose(dataPeminjamanUang);
    fclose(dataPeminjamanUangTemp);

    dataPeminjamanUang = fopen ("DAT/TRdataPinjaman.dat", "wb");
    dataPeminjamanUangTemp = fopen ("TEMP/TRdataPinjamanTemp.dat", "rb");
    while (fread(&trPinjam, sizeof(datatrPinjam), 1, dataPeminjamanUangTemp) == 1) {
        fwrite(&trPinjam, sizeof(datatrPinjam), 1, dataPeminjamanUang);
    }
    fclose(dataPeminjamanUang);
    fclose(dataPeminjamanUangTemp);
}
void deltrRatingBulanan(int sasi, int taun) {
    int hri, bulan, thun;

    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "rb");
    dataTrRatingTemp = fopen("TEMP/TRdataMonthlyRatingTemp.dat", "wb");
    while (fread(&trRating, sizeof(data_trRating), 1,dataTrRating) == 1) {
        bulanTahun(trRating.tgl, &hri, &bulan, &thun);
        if (bulan == sasi && thun == taun) {
            continue;
        } else {
            fwrite(&trRating, sizeof(data_trRating), 1, dataTrRatingTemp);
        }
    }
    fclose(dataTrRating);
    fclose(dataTrRatingTemp);

    dataTrRating = fopen("DAT/TRdataMonthlyRating.dat", "wb");
    dataTrRatingTemp = fopen("TEMP/TRdataMonthlyRatingTemp.dat", "rb");
    while (fread(&trRating, sizeof(data_trRating), 1,dataRatingTemp) == 1) {
        fwrite(&trRating, sizeof(data_trRating), 1, dataRating);
    }
    fclose(dataTrRating);
    fclose(dataTrRatingTemp);
}

#endif //HOLLYFPAYROLL_INSERTDATA_H
