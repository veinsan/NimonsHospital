#include "ngobatin.h"

// Fungsi untuk menukar posisi dua obat pada list obat penyakit
void swapObatPenyakit(ObatPenyakit *a, ObatPenyakit *b) {
    ObatPenyakit temp = *a; // Menyimpan sementara nilai a
    *a = *b; // Menyalin nilai b ke a
    *b = temp; // Menyalin nilai sementara (a) ke b
}

// Fungsi untuk mengobati pasien berdasarkan penyakit yang diderita
void ngobatinPasien(User *pasien) {
    printf("Dokter sedang mengobati pasien!\n");

    // Mengecek apakah pasien sudah didiagnosis dengan penyakit
    if (strlen(pasien->namaPenyakit) == 0) {
        printf("Pasien tidak memiliki penyakit karena belum di diagnosis!\n Gunakkan DIAGNOSIS terlebih dahulu.\n");
        return; // Jika belum didiagnosis, keluar dari fungsi
    }

    int ditemukan = -1; // Variabel untuk menyimpan idPenyakit yang ditemukan
    // Mencari penyakit pasien di dalam daftar penyakit yang ada
    for (int i = 0; i < jumlahPenyakit; i++) {
        if (strcmp(pasien->namaPenyakit, penyakitList[i].namaPenyakit) == 0) {
            ditemukan = penyakitList[i].idPenyakit; // Jika ditemukan, simpan idPenyakit
            break;
        }
    }

    // Jika penyakit ditemukan, lanjutkan untuk memberikan obat
    if (ditemukan != -1){
        printf("Pasien memiliki penyakit %s. Obat yang harus diberikan:\n", pasien->namaPenyakit);
        ObatPenyakit resepUntukPasien[MAX_OBAT];
        int countobat = 0; // Menghitung jumlah obat yang cocok untuk penyakit pasien

        // Mencari obat yang sesuai dengan penyakit pasien
        for (int j = 0; j < jumlahObatPenyakit; j++) {
            if (obatPenyakitList[j].idPenyakit == ditemukan) {
                if (countobat < MAX_OBAT) { // Memastikan jumlah obat tidak melebihi kapasitas
                    resepUntukPasien[countobat] = obatPenyakitList[j];
                    countobat++;
                }
            }
        }

        // Jika tidak ada obat yang ditemukan untuk penyakit pasien
        if (countobat == 0) {
            printf("Belum ada obat untuk penyakit %s di database.\n", pasien->namaPenyakit);
        }

        // Mengurutkan resep berdasarkan urutan minum obat
        for (int i = 0; i < countobat - 1; i++) {
            for (int j = 0; j < countobat - i - 1; j++) {
                if (resepUntukPasien[j].urutanMinum > resepUntukPasien[j + 1].urutanMinum) {
                    swapObatPenyakit(&resepUntukPasien[j], &resepUntukPasien[j + 1]); // Tukar posisi obat
                }
            }
        }

        // Menampilkan obat yang harus diberikan sesuai dengan urutan minum
        for (int i = 0; i < countobat; i++) {
            char namaObatDitemukan[MAX_NAMA_OBAT_LEN] = "Obat Tidak Dikenal";
            // Mencari nama obat berdasarkan idObat yang ada pada resep
            for (int k = 0; k < jumlahObatPenyakit; k++) {
                if (obatList[k].idObat == resepUntukPasien[i].idObat) {
                    strcpy(namaObatDitemukan, obatList[k].namaObat); // Menyimpan nama obat yang ditemukan
                    break;
                }
            }
            // Menampilkan urutan dan nama obat
            printf("%d. %s\n", resepUntukPasien[i].urutanMinum, namaObatDitemukan);
        }

    } else {
        // Jika penyakit tidak dikenali oleh sistem
        printf("Penyakit %s tidak dikenali oleh sistem.\n", pasien->namaPenyakit);
    }
}