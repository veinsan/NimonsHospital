#include "daftar-checkup.h"

// Fungsi untuk membersihkan buffer input setelah menggunakan scanf
static void clearInputBufferDC_ULTRAFINAL() {
    int c;
    // Membaca dan membuang karakter yang tersisa di buffer input hingga newline atau EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi untuk menginisialisasi antrean dokter (dokterQueues) berdasarkan jumlah dokter yang ada
void initializeDokterQueues(User semuaDokterInit[], int jumlahTotalDokterInit) {
    for (int i = 0; i < jumlahTotalDokterInit; i++) {
        dokterQueues[i].dokter = &semuaDokterInit[i]; // Menetapkan dokter ke antrean
        dokterQueues[i].head = NULL; // Menetapkan kepala antrean ke NULL (belum ada pasien)
        dokterQueues[i].tail = NULL; // Menetapkan ekor antrean ke NULL (belum ada pasien)
        dokterQueues[i].jumlah_antrian = 0; // Menetapkan jumlah antrian ke 0
    }
    // Menginisialisasi sisa antrean dokter jika jumlah dokter lebih sedikit dari kapasitas
    for (int i = jumlahTotalDokterInit; i < MAX_JUMLAH_USER; i++) { 
        dokterQueues[i].dokter = NULL; // Tidak ada dokter yang ditetapkan
        dokterQueues[i].head = NULL;
        dokterQueues[i].tail = NULL;
        dokterQueues[i].jumlah_antrian = 0;
    }
}

// Fungsi untuk mendaftarkan pasien untuk check-up dengan dokter yang tersedia
void daftarCheckUp(User paraDokter[], int jumlahDokterAktif, 
                   User semuaPasien[], int jumlahPasienSekarang) {
    
    // Mengecek apakah pasien sudah login dan memiliki peran sebagai "Pasien"
    if (!isLoggedIn || strcmp(currentUser.role, "Pasien") != 0) { 
        printf("Perintah DAFTAR_CHECKUP hanya untuk Pasien yang sudah login!\n");
        return;
    }

    boolean sudahAdaDiAntrian = FALSE;
    // Mengecek apakah pasien sudah terdaftar dalam antrian check-up
    for(int i = 0; i < jumlahDokterAktif; ++i) { 
        if (dokterQueues[i].dokter == NULL) continue; // Skip jika dokter tidak ada
        AntrianNode* cekNode = dokterQueues[i].head;
        while(cekNode != NULL) {
            // Jika pasien sudah terdaftar, set sudahAdaDiAntrian menjadi TRUE
            if(strcmp(cekNode->pasien_data.username, currentUser.username) == 0) {
                sudahAdaDiAntrian = TRUE;
                break;
            }
            cekNode = cekNode->next;
        }
        if(sudahAdaDiAntrian) break; // Keluar dari loop jika sudah terdaftar
    }
    
    // Jika pasien sudah ada dalam antrian, tampilkan pesan dan hentikan eksekusi
    if(sudahAdaDiAntrian){
        printf("\nAnda sudah terdaftar dalam antrian check-up!\n");
        printf("Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
        return;
    }

    // Menyimpan data check-up pasien
    CheckUpData dataMedisInputLokal; 
    printf("\nSilakan masukkan data check-up Anda:\n");

    // Meminta input suhu tubuh pasien
    do {
        printf("Suhu Tubuh (Celcius): ");
        if (scanf("%f", &dataMedisInputLokal.suhu_tubuh) != 1) { 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input suhu tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi suhu tubuh dalam rentang yang wajar
        if (dataMedisInputLokal.suhu_tubuh < 35.0 || dataMedisInputLokal.suhu_tubuh > 42.0) {
            printf("Suhu tubuh invalid (35°C-42°C)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.suhu_tubuh < 35.0 || dataMedisInputLokal.suhu_tubuh > 42.0);

    // Meminta input tekanan darah pasien
    do {
        printf("Tekanan Darah (sistol/diastol, contoh 120 80): ");
        if (scanf("%d %d", &dataMedisInputLokal.tekanan_darah_sistol, &dataMedisInputLokal.tekanan_darah_diastol) != 2) { 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input tekanan darah tidak valid! Harap masukkan dua angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi tekanan darah dalam rentang yang wajar
        if (dataMedisInputLokal.tekanan_darah_sistol < 90 || dataMedisInputLokal.tekanan_darah_sistol > 180 ||
            dataMedisInputLokal.tekanan_darah_diastol < 60 || dataMedisInputLokal.tekanan_darah_diastol > 120) {
            printf("Tekanan darah invalid (Sistol 90-180, Diastol 60-120)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.tekanan_darah_sistol < 90 || dataMedisInputLokal.tekanan_darah_sistol > 180 ||
            dataMedisInputLokal.tekanan_darah_diastol < 60 || dataMedisInputLokal.tekanan_darah_diastol > 120);

    // Meminta input detak jantung pasien
    do {
        printf("Detak Jantung (bpm): ");
        if (scanf("%d", &dataMedisInputLokal.detak_jantung)!=1){ 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input detak jantung tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi detak jantung dalam rentang yang wajar
        if (dataMedisInputLokal.detak_jantung < 50 || dataMedisInputLokal.detak_jantung > 220) {
            printf("Detak jantung invalid (50-220 bpm)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.detak_jantung < 50 || dataMedisInputLokal.detak_jantung > 220);

    // Meminta input saturasi oksigen pasien
    do {
        printf("Saturasi Oksigen (%%): ");
        if (scanf("%f", &dataMedisInputLokal.saturasi_oksigen)!=1){ 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input saturasi oksigen tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi saturasi oksigen dalam rentang yang wajar
        if (dataMedisInputLokal.saturasi_oksigen < 90.0 || dataMedisInputLokal.saturasi_oksigen > 100.0) {
            printf("Saturasi oksigen invalid (90-100%%)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.saturasi_oksigen < 90.0 || dataMedisInputLokal.saturasi_oksigen > 100.0);

    // Meminta input kadar gula darah pasien
    do {
        printf("Kadar Gula Darah (mg/dL): ");
        if (scanf("%f", &dataMedisInputLokal.kadar_gula)!=1){ 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input kadar gula tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi kadar gula darah dalam rentang yang wajar
        if (dataMedisInputLokal.kadar_gula < 50 || dataMedisInputLokal.kadar_gula > 250) {
            printf("Kadar gula darah invalid (50-250 mg/dL)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.kadar_gula < 50 || dataMedisInputLokal.kadar_gula > 250);

    // Meminta input berat badan pasien
    do {
        printf("Berat Badan (kg): ");
        if (scanf("%f", &dataMedisInputLokal.berat_badan)!=1){ 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input berat badan tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi berat badan dalam rentang yang wajar
        if (dataMedisInputLokal.berat_badan <= 0.0 || dataMedisInputLokal.berat_badan > 200) {
            printf("Berat badan invalid (>0, max 200kg)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.berat_badan <= 0.0 || dataMedisInputLokal.berat_badan > 200);

    // Meminta input tinggi badan pasien
    do {
        printf("Tinggi Badan (cm): ");
        if (scanf("%f", &dataMedisInputLokal.tinggi_badan)!=1){ 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input tinggi badan tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi tinggi badan dalam rentang yang wajar
        if (dataMedisInputLokal.tinggi_badan <= 50.0 || dataMedisInputLokal.tinggi_badan > 220) {
            printf("Tinggi badan invalid (50-220 cm)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.tinggi_badan <= 50.0 || dataMedisInputLokal.tinggi_badan > 220);

    // Meminta input kadar kolesterol pasien
    do {
        printf("Kadar Kolestrol (mg/dL): ");
        if (scanf("%f", &dataMedisInputLokal.kadar_kolesterol)!=1){ 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input kolesterol tidak valid! Harap masukkan angka.\n"); 
            return;
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi kadar kolesterol dalam rentang yang wajar
        if (dataMedisInputLokal.kadar_kolesterol < 100 || dataMedisInputLokal.kadar_kolesterol > 300) {
            printf("Kadar kolesterol invalid (100-300 mg/dL)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.kadar_kolesterol < 100 || dataMedisInputLokal.kadar_kolesterol > 300);

    // Meminta input trombosit pasien
    do {
        printf("Trombosit (ribu/µL): ");
        if (scanf("%d", &dataMedisInputLokal.trombosit) != 1) { 
            clearInputBufferDC_ULTRAFINAL(); 
            printf("Input trombosit tidak valid! Harap masukkan angka.\n"); 
            return; 
        }
        clearInputBufferDC_ULTRAFINAL();
        // Memvalidasi trombosit dalam rentang yang wajar
        if (dataMedisInputLokal.trombosit < 150000 || dataMedisInputLokal.trombosit > 450000) { 
            printf("Trombosit invalid (150000-450000 per uL)! Masukkan lagi.\n");
        }
    } while (dataMedisInputLokal.trombosit < 150000 || dataMedisInputLokal.trombosit > 450000);

    // Menampilkan daftar dokter yang tersedia untuk pasien
    printf("\nBerikut adalah daftar dokter yang tersedia (yang memiliki ruangan):\n");

    User* dokterYangBisaDipilih[MAX_JUMLAH_USER];
    int indeksAsliDokter[MAX_JUMLAH_USER];     
    int countDokterBisaDipilih = 0;

    // Menyaring dokter yang memiliki ruangan dan memasukkannya ke dalam daftar
    for (int i = 0; i < jumlahDokterAktif; i++) { 
        if (paraDokter[i].kodeRuangan[0] != '\0') { 
            if (countDokterBisaDipilih < MAX_JUMLAH_USER) { 
                dokterYangBisaDipilih[countDokterBisaDipilih] = &paraDokter[i];
                indeksAsliDokter[countDokterBisaDipilih] = i; 
                countDokterBisaDipilih++;
            }
        }
    }

    // Mengecek apakah ada dokter yang tersedia
    if (countDokterBisaDipilih == 0) {
        printf("Mohon maaf, tidak ada dokter yang praktek di ruangan saat ini.\n");
        return;
    }

    // Menampilkan daftar dokter yang dapat dipilih beserta informasi mereka
    for (int i = 0; i < countDokterBisaDipilih; i++) {
        AntrianDokter* antrianDokterIni = NULL;
        for(int k=0; k < jumlahDokterAktif; ++k) { 
             if(dokterQueues[k].dokter != NULL && dokterQueues[k].dokter->id == dokterYangBisaDipilih[i]->id) {
                antrianDokterIni = &dokterQueues[k];
                break;
            }
        }
        int jumlahAntrianSkrg = (antrianDokterIni != NULL) ? antrianDokterIni->jumlah_antrian : 0;

        printf("%d. Dr. %s - Ruangan %s (Antrian: %d orang) - Aura: %d\n",
               i + 1, 
               dokterYangBisaDipilih[i]->username,
               dokterYangBisaDipilih[i]->kodeRuangan, 
               jumlahAntrianSkrg,
               dokterYangBisaDipilih[i]->aura); 
    }

    // Meminta pengguna untuk memilih dokter dari daftar
    int pilihanUserNomor; 
    printf("Pilih dokter (1-%d): ", countDokterBisaDipilih);
    if (scanf("%d", &pilihanUserNomor) != 1) { clearInputBufferDC_ULTRAFINAL(); printf("Pilihan dokter tidak valid! Masukkan angka.\n"); return;}
    clearInputBufferDC_ULTRAFINAL(); 

    // Mengecek apakah pilihan dokter valid
    if (pilihanUserNomor < 1 || pilihanUserNomor > countDokterBisaDipilih) {
        printf("Pilihan dokter tidak tersedia!\n");
        return;
    }
    int idxAsliDokterYgDipilih = indeksAsliDokter[pilihanUserNomor - 1];

    // Membuat node baru untuk antrian pasien
    AntrianNode* newNode = (AntrianNode*)malloc(sizeof(AntrianNode));
    if (newNode == NULL) {
        printf("Error Kritis: Gagal alokasi memori untuk membuat antrian baru.\n");
        return; 
    } 

    newNode->pasien_data = currentUser; 
    newNode->data_medis = dataMedisInputLokal; 
    newNode->status = 0; 
    newNode->next = NULL; 

    AntrianDokter *selectedQueue = NULL;
    for(int i=0; i < jumlahDokterAktif; ++i) { 
         if(dokterQueues[i].dokter != NULL && dokterQueues[i].dokter->id == paraDokter[idxAsliDokterYgDipilih].id) {
            selectedQueue = &dokterQueues[i];
            break;
        }
    }
    if (selectedQueue == NULL || selectedQueue->dokter == NULL) { 
        printf("Error Internal: Gagal menemukan antrian untuk dokter yang dipilih.\n");
        free(newNode); 
        return;
    }

    // Menambahkan node baru ke antrean dokter yang dipilih
    if (selectedQueue->head == NULL) { 
        selectedQueue->head = newNode;
        selectedQueue->tail = newNode;
    } else { 
        selectedQueue->tail->next = newNode;
        selectedQueue->tail = newNode;
    }
    selectedQueue->jumlah_antrian++;

    // Memperbarui data pasien
    strncpy(currentUser.dokterPerawat, selectedQueue->dokter->username, MAX_USERNAME_LEN -1);
    currentUser.dokterPerawat[MAX_USERNAME_LEN-1] = '\0';
    
    currentUser.suhuTubuh = dataMedisInputLokal.suhu_tubuh;
    currentUser.tekananDarahSistolik = dataMedisInputLokal.tekanan_darah_sistol;
    currentUser.tekananDarahDiastolik = dataMedisInputLokal.tekanan_darah_diastol;
    currentUser.detakJantung = dataMedisInputLokal.detak_jantung;
    currentUser.saturasiOksigen = dataMedisInputLokal.saturasi_oksigen;
    currentUser.kadarGulaDarah = (int)dataMedisInputLokal.kadar_gula;
    currentUser.beratBadan = dataMedisInputLokal.berat_badan;
    currentUser.tinggiBadan = (int)dataMedisInputLokal.tinggi_badan;
    currentUser.kadarKolesterol = (int)dataMedisInputLokal.kadar_kolesterol;
    currentUser.trombosit = dataMedisInputLokal.trombosit; 
    
    // Memperbarui data pasien di global list
    for(int i=0; i < jumlahPasienSekarang; ++i){ 
        if(semuaPasien[i].id == currentUser.id){ 
            strncpy(semuaPasien[i].dokterPerawat, selectedQueue->dokter->username, MAX_USERNAME_LEN -1);
            semuaPasien[i].dokterPerawat[MAX_USERNAME_LEN-1] = '\0';
            
            semuaPasien[i].suhuTubuh = dataMedisInputLokal.suhu_tubuh;
            semuaPasien[i].tekananDarahSistolik = dataMedisInputLokal.tekanan_darah_sistol;
            semuaPasien[i].tekananDarahDiastolik = dataMedisInputLokal.tekanan_darah_diastol;
            semuaPasien[i].detakJantung = dataMedisInputLokal.detak_jantung;
            semuaPasien[i].saturasiOksigen = dataMedisInputLokal.saturasi_oksigen;
            semuaPasien[i].kadarGulaDarah = (int)dataMedisInputLokal.kadar_gula;
            semuaPasien[i].beratBadan = dataMedisInputLokal.berat_badan;
            semuaPasien[i].tinggiBadan = (int)dataMedisInputLokal.tinggi_badan;
            semuaPasien[i].kadarKolesterol = (int)dataMedisInputLokal.kadar_kolesterol;
            semuaPasien[i].trombosit = dataMedisInputLokal.trombosit;
            break;
        }
    }

    // Menampilkan konfirmasi bahwa pasien telah berhasil didaftarkan
    printf("\nPendaftaran check-up berhasil!\n");
    printf("Anda terdaftar pada antrian Dr. %s di ruangan %s.\n", 
           selectedQueue->dokter->username, 
           selectedQueue->dokter->kodeRuangan); 
    printf("Posisi antrian Anda: %d dari %d\n", selectedQueue->jumlah_antrian, selectedQueue->jumlah_antrian);
}