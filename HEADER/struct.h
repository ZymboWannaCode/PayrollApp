#ifndef UIPRJ_STRUCT_H
#define UIPRJ_STRUCT_H


typedef struct {
    char id[10];
    char nama[50];
    int gaji;
} dataregion;
dataregion reg;
FILE *dataRegion;
FILE *dataRegionTemp;

// deklarasi struct data karyawan
typedef struct {
    char id_karyawan[10];
    char id_cabang[10];
    char id_jabatan[10];
    char nama_karyawan[50];
    char tanggalLahir_karyawan[15];
    char alamat_karyawan[100];
    char gender_karyawan[2];
    char tgglMulaiKerja_karyawan[15];
    int jatahCuti_karyawan;
    int plafonAsuransi;
    char status_karyawan[10];
    char password[10];
} data_karyawan;
data_karyawan karyawan;
FILE *dataKaryawan;
FILE *dataKaryawanTemp;

typedef struct {
    char kode_rating[3];
    char nama[30];
    int bonus_rating;
} data_rating;
data_rating  rating;
FILE *dataRating;
FILE *dataRatingTemp;

typedef struct
{
    char id_cabang[10];
    char id_region[10];
    char alamat_cabang[50];
} data_cabang;
data_cabang cabang;
FILE *dataCabang;
FILE *dataCabangTemp;


typedef struct {
    char id[10];
    char nama[30];
    int tunjangan;
} datajabatan;
datajabatan jabatan;
FILE *File;
FILE *Tempfile;


// deklarasi tipe pinjaman
typedef struct
{
    char id_tipePinjaman[10];
    int max_tipePinjaman;
    int durasiPinjam;
}data_TipePinjaman;
data_TipePinjaman tipePinjam;
FILE *data_tipePinjaman;
FILE *data_tipePinjaman_temp;


typedef struct {
    char id_lembur[10];
    char id_karyawan[10];
    char id_gaji[20];
    char tggl_lembur[13];
    int lama_lembur;
    int gaji_lembur;
    char tggl_pengajuan[13];
    char status_lembur[10];
} data_Lembur;
data_Lembur lembur;
FILE *dataLembur;
FILE *dataLemburTemp;

typedef struct {
    char idMR[10];
    char idKrywn[10];
    char kRating[3];
    char tgl[15];
    int bonus;
} data_trRating;
data_trRating trRating;
FILE *dataTrRating;
FILE *dataTrRatingTemp;

typedef struct {
    char idClaim[10];
    char idKrywn[10];
    char tgl[15];
    int jmlClaim;
    char tempatClaim[50];
    char keterangan[50];
    char status[10];
} data_trClaim;
data_trClaim trClaim;
data_trClaim trClaimTemp;
FILE *dataClaimAsuransi;
FILE *dataClaimAsuransiTemp;


typedef struct {
    char idCuti[10];
    char idKaryawan[10];
    char tglCuti[15];
    int jumlahHari;
    char ketCuti[50];
    char tglPengajuan[15];
    char sts[10];
} dataCuti;
dataCuti trCuti;
FILE *datatrCuti;
FILE *datatrCutiTemp;

typedef struct {
    char id_PPinjam[10];
    char id_karyawan[10];
    char tgl_pinjam[10];
    int jumlah_pinjam;
    int bunga_pinjam;
    char status_pinjam[10];
    char id_tipePinjam[10];
    char tanggalTempo[15];
} datatrPinjam;
datatrPinjam trPinjam;
FILE *dataPeminjamanUang;
FILE *dataPeminjamanUangTemp;

typedef struct {
    char idGaji[20];
    char idKrywn[10];
    char idPrating[10];
    char tanggal[15];
    int gajiPokok;
    int tJabatan;
    int bRating;
    int uLembur;
    int pajak;
    int totGaji;
    int potong;
    int gjTerima;
} dataGaji;
dataGaji gaji;
FILE *dataGajian;
FILE *dataGajianTemp;

typedef struct
{
    int hari, bulan, tahun;
} tanggal;

#endif //UIPRJ_STRUCT_H
