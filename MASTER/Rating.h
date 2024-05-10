#ifndef HOLLYFPAYROLL_RATING_H
#define HOLLYFPAYROLL_RATING_H

int adaKode(char input[]) {
    int fd = 0;
    while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
        if (strcmp(input, rating.kode_rating) == 0) {
            fd = 1;
            break;
        }
    }
    if (fd == 1) {
        return 1;
    } else {
        return 0;
    }
}
void createRating(int n) {
    cleanKiri();

    dataRating = fopen("DAT/dataRating.dat", "ab+");

    for (int i = 1; i <= n; i++) {
        SetColor(colorMainText);
        gotoxy(15, 10); printf("Kode Rating");
        gotoxy(15, 12); printf("[                    ]");

        gotoxy(15, 15); printf("Keterangan");
        gotoxy(15, 17); printf("[                    ]");

        gotoxy(15, 20); printf("Bonus Rating");
        gotoxy(15, 22); printf("[ Rp.                ]");

        SetColor(colorScText);
        char kode[3];
        ulang:
        gotoxy(17, 12); getteks(kode, 1);
        fflush(stdin);
        if (adaKode(kode) == 1) {
            showMessage("ALERT!", "KODE TERSEBUT SUDAH ADA!");
            gotoxy(17, 12); printf("  ");
            goto ulang;
        } else {
            strcpy(rating.kode_rating, kode);
        }
        gotoxy(17, 17); getteks(rating.nama, 15);
        fflush(stdin);
        gotoxy(22, 22); getRp(&rating.bonus_rating, 5, 8, 22, 22);

        fwrite(&rating, sizeof(rating), 1, dataRating);
        showMessage("ATTENTION!!", "Data berhasil disimpan!");
        cleanKiri();
    }
    fclose(dataRating);
}
void readRating()
{
    char kode_rating[] = {"KODE"};
    char nama[] = {"KETERANGAN"};
    char bonus[] = {"BONUS"};
    int yTeks = 10;
    char bon[20];

    dataRating = fopen ("DAT/dataRating.dat", "rb");
    if (dataRating == NULL)
    {
        printf("Data Rating tidak ditemukan\n");
    }

    while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
        SetColor(colorScText);
        gotoxy(25, 8); printf("  %-10s  %-15s  %-20s ", kode_rating, nama, bonus);
        printTable(25, 77, 7, 35);
        rupiah(rating.bonus_rating, bon);
        gotoxy(25, yTeks); printf("  %-10s  %-15s  Rp. %-16s ", rating.kode_rating, rating.nama, bon);
        yTeks++;
    }
    fclose(dataRating);
}
void findRatingtoUpd() {
    int found;
    found = 0;
    char kode[10];

    retype:
    gotoxy(row + 26, 15); getteks(kode, 1);

    dataRating = fopen ("DAT/dataRating.dat", "rb");
    dataRatingTemp = fopen ("TEMP/dataRatingTemp.dat", "wb");

    while (found == 0 && fread(&rating, sizeof(rating), 1, dataRating) == 1) {
        if (strcmp(kode, rating.kode_rating) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
        }
    }
    if (found == 1) {
        cleanKiri();
        SetColor(colorMainText);
        gotoxy(5, 3); printf("ID Rating");
        gotoxy(5+50, 3); printf("| %-40s|", rating.kode_rating);

        gotoxy(5, 5); printf("Nama Rating");
        gotoxy(5+50, 5); printf("| %-40s|", rating.nama);

        char gjPokok[20];
        rupiah(rating.bonus_rating, gjPokok);
        gotoxy(5, 7); printf("Bonus Rating");
        gotoxy(5+50, 7); printf("| Rp. %-36s|", gjPokok);

        SetColor(colorHeadText);
        gotoxy(5, 13); printf(">>         MASUKKAN DATA YANG BARU         <<");


        SetColor(colorMainText);
        gotoxy(5, 17); printf("ID Rating");
        gotoxy(55, 17); printf("[   %-26s ]", rating.kode_rating);

        gotoxy(5, 22); printf("Nama Rating");
        gotoxy(55, 22); printf("[   %-26s ]", rating.nama);

        gotoxy(5, 27); printf("Bonus Terbaru");
        gotoxy(55, 27); printf("[ Rp.                        ]");

        SetColor(colorScText);
        int bnTemp; fflush(stdin);
        getRp(&bnTemp, 3, 8, 61, 27);

        if (doaction("UBAH DATA") == 1) {
            strcpy(rating.kode_rating, rating.kode_rating);
            strcpy(rating.nama, rating.nama);
            rating.bonus_rating = bnTemp;
            fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
                fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            } showMessage("ATTENTION!!", "Data berhasil diubah!");
        } else {
            fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
                fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            }
        }
    }
    else {
        showMessage("ALERT!", "Kode Rating tidak ditemukan");
        gotoxy(row + 26, 15); printf("  ");
        goto retype;
    }

    fclose(dataRating);
    fclose(dataRatingTemp);
}
void updateDataRating() {
    findRatingtoUpd();
    dataRating = fopen ("DAT/dataRating.dat", "wb");
    dataRatingTemp = fopen ("TEMP/dataRatingTemp.dat", "rb");

    while (fread(&rating, sizeof(rating), 1, dataRatingTemp)==1) {
        fwrite(&rating, sizeof(rating), 1, dataRating);
    }

    fclose(dataRating);
    fclose(dataRatingTemp);
}
void findRatingtoDel() {
    int found;
    found = 0;
    char kode[10];

    retype:
    gotoxy(row + 26, 15); getteks(kode, 1);

    dataRating = fopen ("DAT/dataRating.dat", "rb");
    dataRatingTemp = fopen ("TEMP/dataRatingTemp.dat", "wb");

    while (found == 0 && fread(&rating, sizeof(rating), 1, dataRating) == 1) {
        if (strcmp(kode, rating.kode_rating) == 0) {
            found = 1;
            break;
        }
        else {
            fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
        }
    }

    if (found == 1) {
        if (deleteData() == 1) {
            while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
                fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            } showMessage("ATTENTION!!", "Data berhasil dihapus!");
        } else {
            fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            while (fread(&rating, sizeof(rating), 1, dataRating) == 1) {
                fwrite(&rating, sizeof(rating), 1, dataRatingTemp);
            }
        }
    }
    else {
        showMessage("ALERT!", "Kode Rating tidak ditemukan");
        gotoxy(row + 26, 15); printf("  ");
        goto retype;
    }
    fclose(dataRating);
    fclose(dataRatingTemp);
}
void deleteDataRating() {
    findRatingtoDel();
    dataRating = fopen ("DAT/dataRating.dat", "wb");
    dataRatingTemp = fopen ("TEMP/dataRatingTemp.dat", "rb");

    while (fread(&rating, sizeof(rating), 1, dataRatingTemp)==1) {
        fwrite(&rating, sizeof(rating), 1, dataRating);
    }

    fclose(dataRating);
    fclose(dataRatingTemp);
}

#endif //HOLLYFPAYROLL_RATING_H
