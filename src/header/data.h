#ifndef DATA_H
#define DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD   "\x1b[1m"
#define ANSI_COLOR_PINK         "\x1b[38;2;255;105;180m"
#define ANSI_COLOR_LAVENDER    "\x1b[38;2;186;85;211m"
#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_ROLE_LEN 10
#define MAX_NAMA_PENYAKIT_LEN 30
#define MAX_NAMA_OBAT_LEN 30
#define MAX_PASIEN_RUANGAN 3
#define MAX_ANTRIAN_PASIEN 5
#define MAX_JUMLAH_USER 110
#define MAX_BARIS 5
#define MAX_KOLOM 5
#define MAX_OBAT 10
#define MAX_NAMA_OBAT 50
#define KAPASITAS_MAKSIMUM_DOKTER_DI_ARRAY 10

#define TRUE 1
#define FALSE 0
typedef int boolean;

typedef struct {
    int id;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char role[MAX_ROLE_LEN];
    char namaPenyakit[MAX_NAMA_PENYAKIT_LEN];
    float suhuTubuh;
    int tekananDarahSistolik;
    int tekananDarahDiastolik;
    int detakJantung;
    float saturasiOksigen;
    int kadarGulaDarah;
    float beratBadan;
    float tinggiBadan;
    int kadarKolesterol;
    int trombosit;
    int nyawa;
    char dokterPerawat[MAX_USERNAME_LEN];
    int aura;
    char kodeRuangan[4];
} User;

typedef struct {
    int id;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    float suhu_tubuh;
    int tekanan_darah_sistol;
    int tekanan_darah_diastol;
    int detak_jantung;
    float saturasi_oksigen;
    float kadar_gula;
    float berat_badan;
    float tinggi_badan;
    float kadar_kolesterol;
    int trombosit; 
} CheckUpData;

typedef struct AntrianNode {
    User pasien_data;
    CheckUpData data_medis;
    int status;
    char dokterdiagnosasesi[MAX_USERNAME_LEN];
    struct AntrianNode *next;
} AntrianNode;

typedef struct {
    User* dokter;
    AntrianNode *head;
    AntrianNode *tail;
    int jumlah_antrian;
} AntrianDokter;

typedef struct {
    int idObat;
    char namaObat[MAX_NAMA_OBAT_LEN];
} Obat;

typedef struct {
    Obat obat[10];
    int jumlahObat;
} ListObatPasien;

typedef struct {
    char data[MAX_OBAT][MAX_NAMA_OBAT];
    int top;
} StackObat;

typedef struct {
    char data[MAX_OBAT][MAX_NAMA_OBAT];
    int size;
} ListObat;

typedef struct {
    char namaPenyakit[50];
    ListObatPasien daftarObat;
} MapPenyakitMauPulang;

typedef struct {
    int idPenyakit;
    char namaPenyakit[MAX_NAMA_PENYAKIT_LEN];
    float suhuTubuhMin, suhuTubuhMax;
    int tekananDarahSistolikMin, tekananDarahSistolikMax;
    int tekananDarahDiastolikMin, tekananDarahDiastolikMax;
    int detakJantungMin, detakJantungMax;
    int saturasiOksigenMin, saturasiOksigenMax;
    int kadarGulaDarahMin, kadarGulaDarahMax;
    float beratBadanMin, beratBadanMax;
    int tinggiBadanMin, tinggiBadanMax;
    int kadarKolesterolMin, kadarKolesterolMax;
    int trombositMin, trombositMax;
} Penyakit;

typedef struct {
    int idObat;
    int idPenyakit;
    int urutanMinum;
} ObatPenyakit;

typedef struct {
    char elements[MAX_JUMLAH_USER][MAX_USERNAME_LEN];
    int size;
} Set;

typedef struct FiturHelp {
    char feature[100];
    struct FiturHelp *next;
} FiturHelp;

typedef struct {
    int kapasitas;
    char dokter[MAX_USERNAME_LEN];
    char pasien[MAX_PASIEN_RUANGAN][MAX_USERNAME_LEN];
    int jumlahPasien;
} Ruangan;

typedef struct Antrian {
    User pasien;
    int status;
    struct Antrian *next;
} Antrian;

typedef enum { SORT_BY_ID = 1, SORT_BY_NAME = 2, SORT_BY_AURA = 3 } SortMethod;
typedef enum { ASC = 1, DESC = 2 } SortOrder;

extern User currentUser;
extern int isLoggedIn;
extern int idpenggunasebelum;
extern User manager;
extern User dokterList[];
extern User pasienList[];

extern Penyakit penyakitList[];
extern Obat obatList[];
extern ObatPenyakit obatPenyakitList[];

extern Ruangan *ruanganList;
extern AntrianDokter dokterQueues[MAX_JUMLAH_USER];

extern Set usernameSet;

extern int jumlahDokter;
extern int jumlahPasien;
extern int jumlahAntrianDokter;
extern int jumlahObat;
extern int jumlahPenyakit;
extern int jumlahObatPenyakit;

#endif