#ifndef HOLLYFPAYROLL_KARYAWAN_H
#define HOLLYFPAYROLL_KARYAWAN_H

void checkPass(int *pass, char pw[], char pw2[]) {
    *pass = 0;
    if (strcmp(pw, pw2) == 0) {
        *pass = 1;
    }
}
int checkCabang(char idCab[]) {
    dataCabang = fopen("DAT/dataCab.dat", "rb");
    int found = 0;
    while (fread(&cabang, sizeof(cabang), 1, dataCabang) == 1) {
        if (strcmp(idCab, cabang.id_cabang) == 0) {
            found = 1;
            break;
        }
    }
    if (found==1) {
        fclose(dataCabang);
        return 1;
    } else {
        fclose(dataCabang);
        return 0;
    }
}
int checkJabatan(char idJab[]) {
    File = fopen("DAT/dataJab.dat", "rb");
    int found = 0;
    while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
        if (strcmp(idJab, jabatan.id) == 0) {
            found = 1;
            break;
        }
    }
    if (found==1) {
        fclose(File);
        return 1;
    } else {
        fclose(File);
        return 0;
    }
}
char* cariNamaJabatan(char idJab[]) {
    File = fopen("DAT/dataJab.dat", "rb");
    int found = 0;
    while (fread(&jabatan, sizeof(jabatan), 1, File) == 1) {
        if (strcmp(idJab, jabatan.id) == 0) {
            found = 1;
            break;
        }
    }
    fclose(File);
    if (found==1) {
        return jabatan.nama;
    } else {
        return "-";
    }
}

void create_karyawan(int n)
{
    cleanKiri();
    char kodekaryawan[] = {"EMP"};
    int idterakhir = 0;
    int leftMarg = 5;

    dataKaryawan = fopen("DAT/dataEmp.dat", "ab+");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        sscanf(karyawan.id_karyawan, "%*[^0-9]%d", &idterakhir);
    }
    for (int i = idterakhir+1; i <= idterakhir+n; i++) {
        snprintf(karyawan.id_karyawan, sizeof(karyawan.id_karyawan), "%s%d", kodekaryawan, i); // ini untuk menggabungkan 2 variable

        SetColor(colorHeadText);
        gotoxy(leftMarg, 3); printf(">>         MASUKKAN DATA YANG BARU         <<");

        SetColor(colorMainText);
        gotoxy(leftMarg, 5); printf("ID Karyawan");
        gotoxy(leftMarg+50, 5); printf("| %-40s|", karyawan.id_karyawan);

        gotoxy(leftMarg, 8); printf("ID Cabang");
        gotoxy(leftMarg+50, 8); printf("| %-40s|", " ");

        gotoxy(leftMarg, 11); printf("ID Jabatan");
        gotoxy(leftMarg+50, 11); printf("| %-40s|", " ");

        gotoxy(leftMarg, 14); printf("Nama Karyawan");
        gotoxy(leftMarg+50, 14); printf("| %-40s|", " ");

        gotoxy(leftMarg, 17); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(leftMarg+50, 17); printf("| %-40s|", " ");

        gotoxy(leftMarg, 20); printf("Alamat");
        gotoxy(leftMarg+50, 20); printf("| %-40s|", " ");

        gotoxy(leftMarg, 23); printf("Sex");
        gotoxy(leftMarg+50, 23); printf("| %-40s|", " ");

        gotoxy(leftMarg, 26); printf("Tanggal Kerja DD-MM-YYYY");
        gotoxy(leftMarg+50, 26); printf("| %-40s|", " ");

        gotoxy(leftMarg, 29); printf("Jatah Cuti");
        gotoxy(leftMarg+50, 29); printf("| %-40s|", "12");

        gotoxy(leftMarg, 32); printf("Plafon Asuransi");
        gotoxy(leftMarg+50, 32); printf("| Rp. %-36s|", "5.000.000");

        gotoxy(leftMarg, 35); printf("Status");
        gotoxy(leftMarg+50, 35); printf("| %-40s|", "Aktif");

        gotoxy(leftMarg, 38); printf("Password Akun");
        gotoxy(leftMarg+50, 38); printf("| %-40s|", " ");

        SetColor(colorScText);
        char cab[10];
        ulang:
        gotoxy(57, 8); getteks(cab,6); // INPUT ID CABANG
        if (checkCabang(cab) == 1) {
            strcpy(karyawan.id_cabang, cab);
        } else {
            showMessage("ALERT", "ID Cabang Tidak Ada");
            gotoxy(57, 8); printf("       ");
            goto ulang;
        }

        char idjab[10];
        jab:
        gotoxy(57, 11); getteks(idjab,6); // INPUT ID JABATAN
        if (checkJabatan(idjab) == 1) {
            strcpy(karyawan.id_jabatan, idjab);
        } else {
            showMessage("ALERT", "ID Jabatan Tidak Ada");
            gotoxy(57, 11); printf("       ");
            goto jab;
        }

        gotoxy( 57, 14); getteks(karyawan.nama_karyawan, 50); // INPUT NAMA KARYAWAN

        gotoxy( 57, 17); getDate(karyawan.tanggalLahir_karyawan); // INPUT TGL LAHIR KARYAAWAN

        gotoxy( 57, 20); getteks(karyawan.alamat_karyawan, 50); // INPUT ALAMAT KARYAWAN

        gotoxy( 57, 23); getteks(karyawan.gender_karyawan, 1); // INPUT GENDER KARYAWAN

        gotoxy( 57, 26); getDate(karyawan.tgglMulaiKerja_karyawan); // INPUT TGL MULAI KERJA

        karyawan.jatahCuti_karyawan = 12; // INPUT JATAH CUTI KARYAWAN

        karyawan.plafonAsuransi = 5000000; // INPUT NOMINAL PLAFON ASURANSI

        strcpy(karyawan.status_karyawan, "Aktif");

        char passwd[10];
        char passwd2[10];
        pass:
        gotoxy( 57, 38); getpass(passwd, 8); // INPUT PASSWORD AKUN KARYAWAN
        gotoxy( 57, 39); getpass(passwd2, 8);
        int check;
        checkPass(&check, passwd, passwd2);
        if(check == 1) {
            strcpy(karyawan.password, passwd);
        } else {
            showMessage("ALERT!", "Pastikan memasukkan Password yang sama!");
            gotoxy( 57, 38); printf("          ");
            gotoxy( 57, 39); printf("          ");
            goto pass;
        }
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawan);
        showMessage("ATTENTION!", "Data Berhasil Disimpan!");
        cleanKiri(); // MEMBERSIHKAN TAMPILAN LAYAR BAGIAN KIRI
    }
    fclose(dataKaryawan); //MENUTUP FILE SETELAH DIGUNAKAN
}
void readdataKarywnALL() {
    cleanKiri();
    char id[] = "ID";
    char nama[] = "NAMA";
    char cab[] = "CABANG";
    char jab[] = "JABATAN";
    char alamat[] = "ALAMAT";
    int i = 1;
    int yTeks = 4;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        printTable(3, 110, 1, 42);
        gotoxy(0, 3); SetColor(colorScText);
        gotoxy(3, 2); printf(" %-8s   %-8s   %-10s   %-28s   %-40s", id, cab, jab, nama, alamat);
        gotoxy(3, yTeks); printf(" %-8s   %-8s   %-10s   %-28s   %-40s", karyawan.id_karyawan, karyawan.id_cabang, cariNamaJabatan(karyawan.id_jabatan), karyawan.nama_karyawan, karyawan.alamat_karyawan);

        if (i % 40 == 0) {
            getch();
            cleanKiri();
            yTeks = 3;
        }
        i++;
        yTeks++;
    }
    fclose(dataKaryawan);
}
void readdataKarywnplafon() {
    cleanKiri();
    char id[] = "ID_KRYWN";
    char nama[] = "NAMA";
    char cab[] = "PLAFON";
    int i = 1;
    int yTeks = 3;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        gotoxy(0, 1); SetColor(colorThdText);
        gotoxy(3, 2); printf(" %-8s | %-8s | %-20s |", id, nama, cab);
        gotoxy(0, 3); SetColor(colorScText);
        gotoxy(3, yTeks); printf(" %-8s | %-8s | %-20d |", karyawan.id_karyawan, karyawan.nama_karyawan, karyawan.jatahCuti_karyawan);

        if (i % 40 == 0) {
            getch();
            cleanKiri();
            yTeks = 2; // PADA SAAT BERHENTI, KOORDINAT UNTUK MENAMPILKAN DATA KARYAWAN AKAN RESET KEMBALI KE AWAL
        }
        i++;
        yTeks++;
    }
    fclose(dataKaryawan);
}
void readdataKarywn1() {
    int leftMarg = 5;
    char idKrywn[10];
    system("cls");
    retype:

    gotoxy(115, 2); SetColor(colorHeadText); printf("   %-35s", "W E L C O M E  M A N A J E R");
    gotoxy(115, 41); printf("%38c", ' ');
    gotoxy(127, 5);SetColor(colorMainText);
    gotoxy(124, 11); printf("Masukkan ID Karyawan");
    gotoxy(129, 15); printf("[        ]");

    readdataKarywnALL();
    frame();

    gotoxy(131, 15); getteks(idKrywn, 6);
    cleanKiri();

    int i = 1;
    int found = 0;

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");

    gotoxy(0, 3); SetColor(colorScText);
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idKrywn, karyawan.id_karyawan) == 0) {
            found = 1;
            break;
        }
        i++;
    }
    if (found == 1) {
        gotoxy(leftMarg, 5); printf("ID Karyawan");
        gotoxy(leftMarg+50, 5); printf("| %-40s|", karyawan.id_karyawan);

        gotoxy(leftMarg, 7); printf("Cabang");
        gotoxy(leftMarg+50, 7); printf("| %-40s|", karyawan.id_cabang);

        gotoxy(leftMarg, 9); printf("Jabatan");
        gotoxy(leftMarg+50, 9); printf("| %-40s|", cariNamaJabatan(karyawan.id_jabatan));

        gotoxy(leftMarg, 11); printf("Nama Karyawan");
        gotoxy(leftMarg+50, 11); printf("| %-40s|", karyawan.nama_karyawan);

        gotoxy(leftMarg, 13); printf("Tanggal Lahir");
        gotoxy(leftMarg+50, 13); printf("| %-40s|", karyawan.tanggalLahir_karyawan);

        gotoxy(leftMarg, 15); printf("Alamat");
        gotoxy(leftMarg+50, 15); printf("| %-40s|", karyawan.alamat_karyawan);

        gotoxy(leftMarg, 17); printf("Sex");
        gotoxy(leftMarg+50, 17); printf("| %-40s|", karyawan.gender_karyawan);

        gotoxy(leftMarg, 19); printf("Tanggal Mulai Kerja");
        gotoxy(leftMarg+50, 19); printf("| %-40s|", karyawan.tgglMulaiKerja_karyawan);

        gotoxy(leftMarg, 21); printf("Jatah Cuti");
        gotoxy(leftMarg+50, 21); printf("| %-40d|", karyawan.jatahCuti_karyawan);

        gotoxy(leftMarg, 23); printf("Plafon Asuransi");
        gotoxy(leftMarg+50, 23); printf("| %-40d|", karyawan.plafonAsuransi);

        gotoxy(leftMarg, 25); printf("Status");
        gotoxy(leftMarg+50, 25); printf("| %-40s|", karyawan.status_karyawan);

        gotoxy(leftMarg, 27); printf("Password Akun");
        gotoxy(leftMarg+50, 27); printf("| %-40s|", karyawan.password);
    } else {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(131, 15); printf("       ");
        goto retype;
    }
    gotoxy(123, 30); printf("Press ENTER to back...");

    fclose(dataKaryawan);
    getch();
}
void cariNamaKaryawan(char idEmp[], char *namaDia) {
    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0) {
            strcpy(namaDia, karyawan.nama_karyawan);
            break;
        }
    }
    fclose(dataKaryawan);
}

void findEmptoUpd() {
    int found;
    found = 0;
    char No[10];
    int leftMarg = 5;

    retype:
    gotoxy(row+17, 15); getteks(No, 6);

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "wb");

    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(No, karyawan.id_karyawan) == 0) {
            found = 1;
            break;
        } else {
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
        }
    }
    if (found == 1) {
        cleanKiri();
        SetColor(colorMainText);
        gotoxy(leftMarg, 2); printf("ID Karyawan");
        gotoxy(leftMarg+50, 2); printf("| %-40s|", karyawan.id_karyawan);

        gotoxy(leftMarg, 3); printf("ID Cabang");
        gotoxy(leftMarg+50, 3); printf("| %-40s|", karyawan.id_cabang);

        gotoxy(leftMarg, 4); printf("ID Jabatan");
        gotoxy(leftMarg+50, 4); printf("| %-40s|", karyawan.id_jabatan);

        gotoxy(leftMarg, 5); printf("Nama Karyawan");
        gotoxy(leftMarg+50, 5); printf("| %-40s|", karyawan.nama_karyawan);

        gotoxy(leftMarg, 6); printf("Tanggal Lahir");
        gotoxy(leftMarg+50, 6); printf("| %-40s|", karyawan.tanggalLahir_karyawan);

        gotoxy(leftMarg, 7); printf("Alamat");
        gotoxy(leftMarg+50, 7); printf("| %-40s|", karyawan.alamat_karyawan);

        gotoxy(leftMarg, 8); printf("Sex");
        gotoxy(leftMarg+50, 8); printf("| %-40s|", karyawan.gender_karyawan);

        gotoxy(leftMarg, 9); printf("Tanggal Mulai Kerja");
        gotoxy(leftMarg+50, 9); printf("| %-40s|", karyawan.tgglMulaiKerja_karyawan);

        gotoxy(leftMarg, 10); printf("Jatah Cuti");
        gotoxy(leftMarg+50, 10); printf("| %-40d|", karyawan.jatahCuti_karyawan);

        gotoxy(leftMarg, 11); printf("Plafon Asuransi");
        gotoxy(leftMarg+50, 11); printf("| Rp. %-36d|", karyawan.plafonAsuransi);

        gotoxy(leftMarg, 12); printf("Status");
        gotoxy(leftMarg+50, 12); printf("| %-40s|", karyawan.status_karyawan);

        gotoxy(leftMarg, 13); printf("Password Akun");
        gotoxy(leftMarg+50, 13); printf("| %-40s|", karyawan.password);

        // MENAMPILKAN TEKS UNTUK INPUT
        SetColor(colorHeadText);
        gotoxy(leftMarg, 16); printf(">>         MASUKKAN DATA YANG BARU         <<");

        SetColor(colorMainText);
        gotoxy(leftMarg, 18); printf("ID Karyawan");
        gotoxy(leftMarg+50, 18); printf("| %-40s|", karyawan.id_karyawan);

        gotoxy(leftMarg, 20); printf("ID Cabang");
        gotoxy(leftMarg+50, 20); printf("| %-40s|", " ");

        gotoxy(leftMarg, 22); printf("ID Jabatan");
        gotoxy(leftMarg+50, 22); printf("| %-40s|", " ");

        gotoxy(leftMarg, 24); printf("Nama Karyawan");
        gotoxy(leftMarg+50, 24); printf("| %-40s|", " ");

        gotoxy(leftMarg, 26); printf("Tanggal Lahir DD-MM-YYYY");
        gotoxy(leftMarg+50, 26); printf("| %-40s|", " ");

        gotoxy(leftMarg, 28); printf("Alamat");
        gotoxy(leftMarg+50, 28); printf("| %-40s|", " ");

        gotoxy(leftMarg, 30); printf("Sex");
        gotoxy(leftMarg+50, 30); printf("| %-40s|", " ");

        gotoxy(leftMarg, 32); printf("Tanggal Kerja DD-MM-YYYY");
        gotoxy(leftMarg+50, 32); printf("| %-40s|", " ");

        gotoxy(leftMarg, 34); printf("Jatah Cuti");
        gotoxy(leftMarg+50, 34); printf("| %-40s|", " ");

        gotoxy(leftMarg, 36); printf("Plafon Asuransi");
        gotoxy(leftMarg+50, 36); printf("| Rp. %-36s|", " ");

        gotoxy(leftMarg, 38); printf("Status");
        gotoxy(leftMarg+50, 38); printf("| %-40s|", " ");

        gotoxy(leftMarg, 40); printf("Password Akun");
        gotoxy(leftMarg+50, 40); printf("| %-40s|", " ");

        SetColor(colorScText);
        char cab[10];
        ulang:
        gotoxy(57, 20); getteks(cab,6); // INPUT ID CABANG
        if (checkCabang(cab) != 1) {
            showMessage("ALERT", "ID Cabang Tidak Ada");
            gotoxy(57, 20); printf("        ");
            goto ulang;
        }

        char idjab[10];
        jab:
        gotoxy(57, 22); getteks(idjab,6); // INPUT ID JABATAN
        if (checkJabatan(idjab) != 1) {
            showMessage("ALERT", "ID Jabatan Tidak Ada");
            gotoxy(57, 22); printf("        ");
            goto jab;
        }

        char namTemp[30];
        gotoxy(57, 24); getteks(namTemp, 35); // INPUT NAMA KARYAWAN

        char tglLhrTemp[15];
        gotoxy(57, 26); getDate(tglLhrTemp); // INPUT TGL LAHIR KARYAAWAN

        char alamatTemp[40];
        gotoxy(57, 28); getteks(alamatTemp, 30); // INPUT ALAMAT KARYAWAN

        char sexTemp[3];
        gotoxy(57, 30); getteks(sexTemp, 1); // INPUT GENDER KARYAWAN

        char tglKerjaTemp[15];
        gotoxy(57, 32); getDate(tglKerjaTemp); // INPUT TGL MULAI KERJA

        int cutitemp;
        gotoxy(57, 34); getnum(&cutitemp, 2); // INPUT JATAH CUTI KARYAWAN

        int plfontemp;
        getRp(&plfontemp, 5, 8, 61, 36); // INPUT NOMINAL PLAFON ASURANSI

        char ststemp[10];
        gotoxy(57, 38); getteks(ststemp, 10); // INPUT STATUS KARYAWAN

        char passwd[10];
        char passwd2[10];
        pass:
        gotoxy(57, 40); getpass(passwd, 8); // INPUT PASSWORD AKUN KARYAWAN
        gotoxy( 57, 41); getpass(passwd2, 8);
        int check;
        checkPass(&check, passwd, passwd2);
        if(check != 1) {
            showMessage("ALERT!", "Pastikan memasukkan Password yang sama!");
            gotoxy(57, 40); printf("          ");
            gotoxy(57, 41); printf("          ");
            goto pass;
        }
        if (doaction("UBAH DATA") == 1) {
            strcpy(karyawan.id_karyawan, No);
            strcpy(karyawan.id_cabang, cab);
            strcpy(karyawan.id_jabatan, idjab);
            strcpy(karyawan.nama_karyawan, namTemp);
            strcpy(karyawan.tanggalLahir_karyawan, tglLhrTemp);
            strcpy(karyawan.alamat_karyawan, alamatTemp);
            strcpy(karyawan.gender_karyawan, sexTemp);
            strcpy(karyawan.tgglMulaiKerja_karyawan, tglKerjaTemp);
            karyawan.jatahCuti_karyawan = cutitemp;
            karyawan.plafonAsuransi = plfontemp;
            strcpy(karyawan.status_karyawan, ststemp);
            strcpy(karyawan.password, passwd);
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
            while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
                fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
            while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
                fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
            }
        }
    } else {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(row + 17, 15); printf("       ");
        goto retype;
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}
void updatedataKarywn() {
    findEmptoUpd();

    dataKaryawan = fopen("DAT/dataEmp.dat", "wb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "rb");

    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp)==1) {
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawan);
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}


void findEmptoDel() {
    int found;
    found = 0;
    char No[10];
    int leftMarg = 5;

    retype:
    gotoxy(row+17, 15); getteks(No, 6);

    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "wb");

    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        //Jika data ditemukan maka nilai variabel found menjadi true atau 1
        if (strcmp(No, karyawan.id_karyawan) == 0) {
            cleanKiri();
            char namaJab[20];
            SetColor(colorMainText);
            gotoxy(leftMarg, 5); printf("ID Karyawan");
            gotoxy(leftMarg+50, 5); printf("| %-40s|", karyawan.id_karyawan);

            gotoxy(leftMarg, 7); printf("Cabang");
            gotoxy(leftMarg+50, 7); printf("| %-40s|", karyawan.id_cabang);

            gotoxy(leftMarg, 9); printf("Jabatan");
            gotoxy(leftMarg+50, 9); printf("| %-40s|", cariNamaJabatan(karyawan.id_jabatan));

            gotoxy(leftMarg, 11); printf("Nama Karyawan");
            gotoxy(leftMarg+50, 11); printf("| %-40s|", karyawan.nama_karyawan);

            gotoxy(leftMarg, 13); printf("Tanggal Lahir");
            gotoxy(leftMarg+50, 13); printf("| %-40s|", karyawan.tanggalLahir_karyawan);

            gotoxy(leftMarg, 15); printf("Alamat");
            gotoxy(leftMarg+50, 15); printf("| %-40s|", karyawan.alamat_karyawan);

            gotoxy(leftMarg, 17); printf("Sex");
            gotoxy(leftMarg+50, 17); printf("| %-40s|", karyawan.gender_karyawan);

            gotoxy(leftMarg, 19); printf("Tanggal Mulai Kerja");
            gotoxy(leftMarg+50, 19); printf("| %-40s|", karyawan.tgglMulaiKerja_karyawan);

            gotoxy(leftMarg, 21); printf("Jatah Cuti");
            gotoxy(leftMarg+50, 21); printf("| %-40d|", karyawan.jatahCuti_karyawan);

            gotoxy(leftMarg, 23); printf("Plafon Asuransi");
            gotoxy(leftMarg+50, 23); printf("| %-40d|", karyawan.plafonAsuransi);

            gotoxy(leftMarg, 25); printf("Status");
            gotoxy(leftMarg+50, 25); printf("| %-40s|", karyawan.status_karyawan);

            gotoxy(leftMarg, 27); printf("Password Akun");
            gotoxy(leftMarg+50, 27); printf("| %-40s|", karyawan.password);
            getch();
            if (deleteData() == 1) {
                found = 1;
                showMessage("ATTENTION!!", "Data berhasil dihapus!");
                continue;
            } else {
                found = 1;
                fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
            }
        }
        else {
            fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp);
        }
    }
    if (found == 0) {
        showMessage("ALERT!", "ID Karyawan tidak ditemukan");
        gotoxy(row + 17, 15); printf("       ");
        goto retype;
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}
void deletedataKarywn() {
    findEmptoDel();

    dataKaryawan = fopen("DAT/dataEmp.dat", "wb");
    dataKaryawanTemp = fopen("TEMP/dataEmpTemp.dat", "rb");

    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawanTemp)==1) {
        fwrite(&karyawan, sizeof(karyawan), 1, dataKaryawan);
    }
    fclose(dataKaryawan);
    fclose(dataKaryawanTemp);
}

void cariDataKarywn(char idEmp[], char* namaDia, char* jabatan, char* namaReg, char* cabang) {
    dataKaryawan = fopen("DAT/dataEmp.dat", "rb");
    while (fread(&karyawan, sizeof(karyawan), 1, dataKaryawan) == 1) {
        if (strcmp(idEmp, karyawan.id_karyawan) == 0) {
            break;
        }
    }
    strcpy(namaDia, karyawan.nama_karyawan);
    strcpy(jabatan, cariNamaJabatan(karyawan.id_jabatan));
    carinamaCabReg(karyawan.id_cabang, namaReg);
    carinamaCab(karyawan.id_cabang, cabang);
    fclose(dataKaryawan);
}

#endif //HOLLYFPAYROLL_KARYAWAN_H
