#include "denah.h" 

// Fungsi untuk menampilkan denah rumah sakit berdasarkan jumlah ruangan, baris dan kolom
void lihatDenah(int jumlahRuangIgnored, int barisDenahAktual, int kolomDenahAktual) {
    if (barisDenahAktual <= 0 || kolomDenahAktual <= 0) {
        printf("Dimensi denah tidak valid untuk ditampilkan.\n");
        return;
    }

    // Menampilkan nomor kolom di bagian atas denah
    printf("      ");
    for (int j = 0; j < kolomDenahAktual; j++) {
        printf("%d     ", j + 1);
    }
    printf("\n");

    // Menampilkan garis pemisah setelah nomor kolom
    printf("   +");
    for (int j = 0; j < kolomDenahAktual; j++) {
        printf("-----+");
    }
    printf("\n");

    // Menampilkan baris dan kolom denah
    for (int i = 0; i < barisDenahAktual; i++) {
        printf(" %c |", 'A' + i); // Menampilkan baris denah (A, B, C, dst)
        for (int j = 0; j < kolomDenahAktual; j++) {
            printf(" %c%d  |", 'A' + i, j + 1); // Menampilkan kolom denah (A1, A2, B1, dst)
        }
        printf("\n");

        // Menampilkan garis pemisah setelah setiap baris
        printf("   +");
        for (int j = 0; j < kolomDenahAktual; j++) {
            printf("-----+");
        }
        printf("\n");
    }
}

// Fungsi untuk menampilkan detail ruangan berdasarkan indeks dan informasi ruangan
void lihatRuangan(int indeks, const Ruangan ruanganListFromParam[], int denahKolomAktual) {
    if (denahKolomAktual <= 0) {
        printf("Informasi kolom denah tidak valid untuk menampilkan detail ruangan.\n");
        return;
    }
    if (ruanganListFromParam == NULL || indeks < 0 || indeks >= (MAX_BARIS * MAX_KOLOM)) { 
        printf("Indeks ruangan tidak valid atau denah belum diinisialisasi.\n");
        return;
    }

    const Ruangan *r = &ruanganListFromParam[indeks]; 

    char kodeRuangStr[6]; 
    snprintf(kodeRuangStr, sizeof(kodeRuangStr), "%c%d", 'A' + (indeks / denahKolomAktual), (indeks % denahKolomAktual) + 1);

    // Menampilkan detail ruangan (kode ruangan, kapasitas, dokter, pasien)
    printf("\n--- Detail Ruangan %s ---\n", kodeRuangStr);
    printf("Kapasitas  : %d\n", r->kapasitas);
    printf("Dokter     : %s\n", strlen(r->dokter) > 0 ? r->dokter : "-"); 
    printf("Pasien di dalam ruangan:\n");
    if (r->jumlahPasien == 0) {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        for (int i = 0; i < r->jumlahPasien; i++) {
            if (r->pasien[i][0] != '\0') {
                printf("  %d. %s\n", i + 1, r->pasien[i]);
            }
        }
    }
    printf("------------------------------\n");
}

// Fungsi untuk mengubah ukuran denah (menambah/mengurangi baris dan kolom)
boolean ubahDenah(int *ptrJumlahRuangTotal, Ruangan **ptrToRuanganListGlobal, int barisBaru, int kolomBaru, int *ptrDenahBarisMain, int *ptrDenahKolomMain) {
    if (barisBaru <= 0 || kolomBaru <= 0 || barisBaru > MAX_BARIS || kolomBaru > MAX_KOLOM) {
        printf("Ukuran denah baru tidak valid!\n");
        return FALSE;
    }

    int jumlahRuangBaru = barisBaru * kolomBaru;
    int jumlahRuangLama = *ptrJumlahRuangTotal;
    int kolomLama = *ptrDenahKolomMain;

    // Memastikan bahwa ruangan yang akan dihapus tidak memiliki dokter bertugas
    if (jumlahRuangBaru < jumlahRuangLama && *ptrToRuanganListGlobal != NULL) {
        for (int i = jumlahRuangBaru; i < jumlahRuangLama; i++) { 
            if (strlen((*ptrToRuanganListGlobal)[i].dokter) > 0) {
                char kodeRuangHilang[15]; 
                snprintf(kodeRuangHilang, sizeof(kodeRuangHilang), "%c%d", 'A' + (i / kolomLama), (i % kolomLama) + 1);
                printf("Tidak dapat mengubah ukuran denah. Ruangan %s masih ditempati oleh Dr. %s. Silakan pindahkan dokter terlebih dahulu.\n", 
                       kodeRuangHilang, (*ptrToRuanganListGlobal)[i].dokter);
                return FALSE;
            }
        }
    }

    // Mengalokasikan ulang (realloc) memori untuk list ruangan
    Ruangan *ruanganListBaru = (Ruangan*) realloc(*ptrToRuanganListGlobal, sizeof(Ruangan) * jumlahRuangBaru);
    if (ruanganListBaru == NULL && jumlahRuangBaru > 0) { 
        printf("Gagal mengubah ukuran denah (realloc gagal)!\n");
        return FALSE;
    }
    
    *ptrToRuanganListGlobal = ruanganListBaru;

    // Menginisialisasi ruangan tambahan jika jumlah ruang bertambah
    if (jumlahRuangBaru > jumlahRuangLama) {
        for (int i = jumlahRuangLama; i < jumlahRuangBaru; i++) {
            if (*ptrToRuanganListGlobal != NULL) { 
                (*ptrToRuanganListGlobal)[i].kapasitas = MAX_PASIEN_RUANGAN; 
                (*ptrToRuanganListGlobal)[i].dokter[0] = '\0';
                (*ptrToRuanganListGlobal)[i].jumlahPasien = 0;
                for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
                    (*ptrToRuanganListGlobal)[i].pasien[j][0] = '\0';
                }
            }
        }
    }

    // Memperbarui jumlah ruang dan ukuran denah
    *ptrJumlahRuangTotal = jumlahRuangBaru;
    *ptrDenahBarisMain = barisBaru;
    *ptrDenahKolomMain = kolomBaru;

    printf("Denah rumah sakit berhasil diubah menjadi %d baris dan %d kolom.\n", barisBaru, kolomBaru);
    return TRUE;
}

// Fungsi untuk memindahkan dokter dari satu ruangan ke ruangan lain
boolean pindahDokter(const char *kodeRuanganAsal, const char *kodeRuanganTujuan, 
                     Ruangan ruanganListFromParam[], 
                     int denahBarisAktual, int denahKolomAktual) {
    if (kodeRuanganAsal == NULL || kodeRuanganTujuan == NULL || strlen(kodeRuanganAsal) < 2 || strlen(kodeRuanganTujuan) < 2) {
         printf("Format kode ruangan asal atau tujuan tidak valid.\n"); return FALSE;
    }

    // Menghitung indeks baris dan kolom dari kode ruangan asal dan tujuan
    int asalBarisIdx = kodeRuanganAsal[0] - 'A';
    int asalKolomAngka = atoi(&kodeRuanganAsal[1]);
    int asalKolomIdx = asalKolomAngka - 1;
    
    int tujuanBarisIdx = kodeRuanganTujuan[0] - 'A';
    int tujuanKolomAngka = atoi(&kodeRuanganTujuan[1]);
    int tujuanKolomIdx = tujuanKolomAngka - 1;

    // Memastikan kode ruangan dalam batas denah
    if (!(asalBarisIdx >= 0 && asalBarisIdx < denahBarisAktual && asalKolomAngka >= 1 && asalKolomAngka <= denahKolomAktual) ||
        !(tujuanBarisIdx >= 0 && tujuanBarisIdx < denahBarisAktual && tujuanKolomAngka >= 1 && tujuanKolomAngka <= denahKolomAktual)) {
        printf("Kode ruangan di luar batas denah.\n");
        return FALSE;
    }

    // Menghitung indeks ruangan asal dan tujuan
    int asalIdx = asalBarisIdx * denahKolomAktual + asalKolomIdx;
    int tujuanIdx = tujuanBarisIdx * denahKolomAktual + tujuanKolomIdx;

    // Memastikan bahwa ruangan asal dan tujuan valid
    if (ruanganListFromParam == NULL || asalIdx < 0 || asalIdx >= (denahBarisAktual * denahKolomAktual) || 
        tujuanIdx < 0 || tujuanIdx >= (denahBarisAktual * denahKolomAktual)) {
        printf("Indeks ruangan tidak valid atau denah belum diinisialisasi!\n");
        return FALSE;
    }
    
    // Memastikan ruangan asal memiliki dokter yang bertugas
    if (strlen(ruanganListFromParam[asalIdx].dokter) == 0) {
        printf("Pemindahan gagal. Ruangan %s kosong.\n", kodeRuanganAsal);
        return FALSE;
    }

    // Menyimpan nama dokter yang akan dipindahkan
    char namaDokterYangPindah[MAX_USERNAME_LEN];
    strncpy(namaDokterYangPindah, ruanganListFromParam[asalIdx].dokter, MAX_USERNAME_LEN - 1);
    namaDokterYangPindah[MAX_USERNAME_LEN - 1] = '\0';

    // Memastikan ruangan tujuan kosong
    if (strlen(ruanganListFromParam[tujuanIdx].dokter) > 0) {
        if (strcmp(ruanganListFromParam[tujuanIdx].dokter, namaDokterYangPindah) == 0) {
            printf("Dokter %s sudah berada di ruangan %s. Tidak ada pemindahan.\n", namaDokterYangPindah, kodeRuanganTujuan);
            return TRUE; 
        }
        printf("Pemindahan gagal. Ruangan %s sudah ditempati.\n", kodeRuanganTujuan);
        return FALSE;
    }
    
    // Memindahkan dokter ke ruangan tujuan
    ruanganListFromParam[asalIdx].dokter[0] = '\0'; 
    strncpy(ruanganListFromParam[tujuanIdx].dokter, namaDokterYangPindah, MAX_USERNAME_LEN - 1);
    ruanganListFromParam[tujuanIdx].dokter[MAX_USERNAME_LEN - 1] = '\0';

    printf("Dr. %s berhasil dipindahkan dari ruangan %s ke ruangan %s.\n", namaDokterYangPindah, kodeRuanganAsal, kodeRuanganTujuan);
    return TRUE;
}