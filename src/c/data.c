#include "data.h"

// Definisi Variabel Global
User currentUser;  // Menyimpan data pengguna yang sedang login
int isLoggedIn = 0; // Menunjukkan status login (0 = belum login, 1 = sudah login)
int idpenggunasebelum = 100; // ID terakhir yang digunakan untuk pengguna baru

// User manager (Role: Manager)
User manager = {88, "zeru", "pass77", "Manager", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// List Dokter
User dokterList[] = {
    {10, "Neronimo", "pass1010", "Dokter", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, "A2"},
    {11, "Ciciko", "pass1111", "Dokter", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {12, "Cacako", "pass1212", "Dokter", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {13, "Kroket", "pass1313", "Dokter", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3},
    {15, "Risol", "pass1515", "Dokter", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5}
};

// List Pasien
User pasienList[] = {
    {1, "Stewart", "pass11", "Pasien", "", 36.1, 92, 77, 66, 93.7, 127, 52.4, 177, 193, 328, 3},
    {7, "Tuart", "paturrt", "Pasien", "", 36.1, 92, 77, 66, 93.7, 127, 52.4, 177, 193, 328, 3},
    {2, "Gro", "pass22", "Pasien", "COVID-19", 36.6, 126, 85, 67, 96.5, 175, 45.7, 156, 235, 212, 3},
    {3, "Kebin", "pass33", "Pasien", "", 36.4, 96, 68, 94, 92.3, 162, 64.1, 158, 240, 380, 3},
    {6, "Nikeb", "pnikeb", "Pasien", "", 36.4, 96, 68, 94, 92.3, 162, 64.1, 158, 240, 380, 3},
    {4, "Pop", "pass44", "Pasien", "Diabetes Mellitus", 36.9, 110, 85, 73, 98.7, 152, 62.8, 157, 184, 390, 3},
    {8, "Minonette", "pass88", "Pasien", "", 36.7, 93, 87, 63, 97.8, 136, 77, 172, 227, 380, 3},
    {9, "Tobo", "pass99", "Pasien", "", 36.8, 114, 74, 61, 94.6, 100, 80.6, 173, 152, 386, 3},
    {24, "Ropik", "pass240", "Pasien", "", 36.2, 103, 87, 65, 96.6, 102, 72.3, 184, 150, 292, 3},
    {5, "Opor", "oporkanajala", "Pasien", "", 36.2, 103, 87, 65, 96.6, 102, 72.3, 184, 150, 292, 3},
    {16, "Tobokan", "pass1234", "Pasien", "", 36.8, 114, 74, 61, 94.6, 100, 80.6, 173, 152, 386, 3},
    {20, "Popokan", "passpopokan", "Pasien", "", 36.9, 110, 85, 73, 98.7, 152, 62.8, 157, 184, 390, 3},
    {100, "Pendatang", "pendatangbaru", "Pasien", "", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3}
};

// Daftar Penyakit
Penyakit penyakitList[] = {
    {1, "Influenza", 36, 38.5, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {5, "Anemia", 36, 37, 90, 120, 60, 80, 60, 100, 95, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {2, "COVID-19", 36, 39, 90, 130, 60, 85, 60, 120, 90, 100, 70, 180, 45, 90, 150, 185, 150, 240, 150, 450},
    {3, "Hipertensi", 36, 37.5, 140, 180, 90, 120, 60, 100, 90, 100, 70, 140, 45, 90, 150, 185, 150, 240, 150, 450},
    {4, "Diabetes Mellitus", 36, 37.5, 90, 140, 60, 90, 60, 100, 90, 100, 126, 200, 45, 90, 150, 185, 150, 240, 150, 450}
};

// Daftar Obat
Obat obatList[] = {
    {1, "Oseltamivir"},
    {2, "Vitamin C"},
    {3, "Remdesivir"},
    {4, "Lisinopril"},
    {5, "Metformin"}
};

// Daftar Obat untuk Penyakit
ObatPenyakit obatPenyakitList[25] = {
    {1, 1, 1}, {2, 1, 2},
    {3, 2, 1},
    {4, 3, 1},
    {5, 4, 1}, {4, 4, 2}, {3, 4, 3}, {2, 4, 4},
    {3, 5, 1}, {2, 5, 2}
};

// Antrian untuk setiap dokter
AntrianDokter dokterQueues[MAX_JUMLAH_USER];

// List Ruangan (Dynamically allocated)
Ruangan *ruanganList = NULL;

// Struktur Set untuk menyimpan username yang unik
Set usernameSet;

// Menghitung jumlah dokter, pasien, penyakit, obat, dan relasi obat-penyakit
int jumlahDokter = sizeof(dokterList) / sizeof(dokterList[0]);
int jumlahPasien = sizeof(pasienList) / sizeof(pasienList[0]);
int jumlahPenyakit = sizeof(penyakitList) / sizeof(penyakitList[0]);
int jumlahObat = sizeof(obatList) / sizeof(obatList[0]);
int jumlahObatPenyakit = sizeof(obatPenyakitList) / sizeof(obatPenyakitList[0]);