#include "dokter-management.h"
#include "set.h"

// Fungsi untuk membersihkan buffer input setelah menggunakan scanf
static void clearInputBufferDokterMgmt() {
    int c;
    // Menghapus karakter-karakter yang ada dalam buffer hingga newline atau EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fungsi untuk menambah dokter baru ke dalam sistem
void tambahDokter(User listDokter[], int *currentTotalDokter, Set *usernameSetGlobal) {
    // Mengecek apakah kapasitas maksimum dokter telah tercapai
    if (*currentTotalDokter >= KAPASITAS_MAKSIMUM_DOKTER_DI_ARRAY) {
        printf("\nKapasitas penyimpanan untuk dokter sudah penuh! (Maks: %d dokter)\n", KAPASITAS_MAKSIMUM_DOKTER_DI_ARRAY);
        printf("Tidak bisa menambah dokter baru.\n");
        return;
    }

    // Variabel untuk menyimpan username dan password sementara
    char tempUsername[MAX_USERNAME_LEN + 2]; 
    char tempPassword[MAX_PASSWORD_LEN + 2];

    // Input username dokter
    printf("Username: "); 
    if (scanf("%20s", tempUsername) != 1) { 
        printf("Input username gagal. Harap coba lagi.\n"); 
        clearInputBufferDokterMgmt(); 
        return;
    }
    if (strlen(tempUsername) >= MAX_USERNAME_LEN) { 
        printf("Username terlalu panjang! Maksimum %d karakter.\n", MAX_USERNAME_LEN - 1);
        clearInputBufferDokterMgmt(); 
        return;
    }
    clearInputBufferDokterMgmt();  // Membersihkan input buffer setelah memasukkan username

    // Input password dokter
    printf("Password: "); 
    if (scanf("%20s", tempPassword) != 1) { 
        printf("Input password gagal. Harap coba lagi.\n");
        clearInputBufferDokterMgmt();
        return;
    }
    if (strlen(tempPassword) >= MAX_PASSWORD_LEN) {
        printf("Password terlalu panjang! Maksimum %d karakter.\n", MAX_PASSWORD_LEN - 1);
        clearInputBufferDokterMgmt();
        return;
    }
    clearInputBufferDokterMgmt();  // Membersihkan input buffer setelah memasukkan password

    // Mengecek apakah username sudah ada di dalam set
    if (searchSet(*usernameSetGlobal, tempUsername)) { 
        printf("Sudah ada Dokter bernama %s!\n", tempUsername); 
        return;
    }

    // Menambahkan ID baru untuk dokter
    idpenggunasebelum++; 
    int idxBaru = *currentTotalDokter;

    // Menambahkan data dokter ke dalam array listDokter
    listDokter[idxBaru].id = idpenggunasebelum;
    strncpy(listDokter[idxBaru].username, tempUsername, MAX_USERNAME_LEN - 1);
    listDokter[idxBaru].username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(listDokter[idxBaru].password, tempPassword, MAX_PASSWORD_LEN - 1);
    listDokter[idxBaru].password[MAX_PASSWORD_LEN - 1] = '\0';
    strcpy(listDokter[idxBaru].role, "Dokter");

    // Menambahkan nilai default untuk data lainnya
    listDokter[idxBaru].namaPenyakit[0] = '\0'; 
    listDokter[idxBaru].aura = 0;  
    listDokter[idxBaru].kodeRuangan[0] = '\0';  
    listDokter[idxBaru].dokterPerawat[0] = '\0'; 
    listDokter[idxBaru].nyawa = 0; 
    listDokter[idxBaru].suhuTubuh = 0.0f; 
    listDokter[idxBaru].tekananDarahSistolik = 0;
    listDokter[idxBaru].tekananDarahDiastolik = 0;
    listDokter[idxBaru].detakJantung = 0;
    listDokter[idxBaru].saturasiOksigen = 0.0f;
    listDokter[idxBaru].kadarGulaDarah = 0;
    listDokter[idxBaru].beratBadan = 0.0f;
    listDokter[idxBaru].tinggiBadan = 0.0f;
    listDokter[idxBaru].kadarKolesterol = 0;
    listDokter[idxBaru].trombosit = 0;

    // Menambahkan username dokter ke dalam set untuk pengecekan unik
    insertSet(usernameSetGlobal, tempUsername); 
    (*currentTotalDokter)++;  // Menambahkan total dokter yang terdaftar

    // Menampilkan konfirmasi berhasil
    printf("\nDokter %s berhasil ditambahkan ke sistem!\n", tempUsername);
}

// Fungsi untuk mengassign dokter ke ruangan tertentu
void assignRuangan(User listDokter[], int currentTotalDokter, Ruangan listRuangan[], int jumlahRuangGlobal, int denahBarisGlobal, int denahKolomGlobal) {
    // Variabel untuk menyimpan username dokter dan kode ruangan yang akan dipilih
    char usernameDokter[MAX_USERNAME_LEN + 2];
    char kodeRuangInput[4]; 

    // Input username dokter yang akan diassign ke ruangan
    printf("Username: "); 
    if (scanf("%20s", usernameDokter) != 1) { return; }
    if (strlen(usernameDokter) >= MAX_USERNAME_LEN) { return; }
    clearInputBufferDokterMgmt();

    // Input kode ruangan yang akan diassign
    printf("Ruangan: "); 
    if (scanf("%3s", kodeRuangInput) != 1) { return; }
    clearInputBufferDokterMgmt();

    // Mencari dokter berdasarkan username yang diberikan
    int idxDokterDitemukan = -1;
    for (int i = 0; i < currentTotalDokter; i++) {
        if (strcmp(listDokter[i].username, usernameDokter) == 0) {
            idxDokterDitemukan = i;
            break;
        }
    }
    if (idxDokterDitemukan == -1) {
        printf("\nDokter dengan username '%s' tidak ditemukan!\n", usernameDokter);
        return;
    }

    // Memvalidasi format kode ruangan
    if (!((kodeRuangInput[0] >= 'A' && kodeRuangInput[0] < 'A' + denahBarisGlobal) &&
          (kodeRuangInput[1] >= '1' && kodeRuangInput[1] < '1' + denahKolomGlobal) &&
           kodeRuangInput[2] == '\0')) { 
        printf("\nFormat kode ruangan '%s' salah atau di luar batas denah (A-%c, 1-%d)!\n", 
            kodeRuangInput, 'A' + denahBarisGlobal - 1, denahKolomGlobal);
        return;
    }

    // Menghitung indeks ruangan berdasarkan kode ruangan yang diberikan
    int barisRuangIdx = kodeRuangInput[0] - 'A';
    int kolomRuangIdx = kodeRuangInput[1] - '1'; 
    int idxRuanganTarget = barisRuangIdx * denahKolomGlobal + kolomRuangIdx;

    // Memastikan indeks ruangan target valid
    if (idxRuanganTarget < 0 || idxRuanganTarget >= jumlahRuangGlobal) {
        printf("\nKode ruangan '%s' menghasilkan indeks di luar batas yang valid!\n", kodeRuangInput);
        return;
    }

    // Memeriksa apakah dokter sudah memiliki ruangan dan apakah ruangan sudah ditempati
    boolean dokterSudahPunyaRuangan = (strlen(listDokter[idxDokterDitemukan].kodeRuangan) > 0);
    boolean ruanganTargetSudahDitempati = (strlen(listRuangan[idxRuanganTarget].dokter) > 0);
    char* namaDokterDiTarget = listRuangan[idxRuanganTarget].dokter;
    char* kodeRuanganDokterSaatIni = listDokter[idxDokterDitemukan].kodeRuangan;

    // Kasus ketika dokter sudah memiliki ruangan dan ruangan target sudah ditempati
    if (dokterSudahPunyaRuangan && ruanganTargetSudahDitempati) {
        if (strcmp(namaDokterDiTarget, usernameDokter) != 0) {
            printf("\nDokter %s sudah menempati ruangan %s!\n", usernameDokter, kodeRuanganDokterSaatIni);
            printf("Ruangan %s juga sudah ditempati dokter %s!\n", kodeRuangInput, namaDokterDiTarget);
        } else {
             printf("\nError: Dokter %s sudah di ruangan %s, namun juga tercatat punya ruangan %s.\n", usernameDokter, kodeRuangInput, kodeRuanganDokterSaatIni);
        }
        return;
    }
    else if (dokterSudahPunyaRuangan) { 
        printf("\nDokter %s sudah diassign ke ruangan %s!\n", 
               usernameDokter, kodeRuanganDokterSaatIni);
        return;
    }
    else if (ruanganTargetSudahDitempati) {
        printf("\nDokter %s sudah menempati ruangan %s!\n", 
               namaDokterDiTarget, kodeRuangInput); 
        printf("Silakan cari ruangan lain untuk dokter %s.\n", usernameDokter);
        return;
    }
    else { 
        // Assign dokter ke ruangan target yang valid
        strncpy(listDokter[idxDokterDitemukan].kodeRuangan, kodeRuangInput, 3);
        listDokter[idxDokterDitemukan].kodeRuangan[3] = '\0'; 
        
        strncpy(listRuangan[idxRuanganTarget].dokter, usernameDokter, MAX_USERNAME_LEN - 1);
        listRuangan[idxRuanganTarget].dokter[MAX_USERNAME_LEN - 1] = '\0';

        printf("\nDokter %s berhasil diassign ke ruangan %s!\n", usernameDokter, kodeRuangInput);
    }
}