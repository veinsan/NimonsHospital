#include "user-management.h"

// Fungsi untuk membersihkan buffer input setelah scanf untuk menghindari karakter tersisa
static void clearInputBuffer() {
    int c;
    // Membaca dan mengabaikan karakter hingga menemui newline atau EOF
    while ((c = getchar()) != '\n' && c != EOF);
}

void login(User *managerData, User dokterListParam[], int dokterCountParam, User pasienListParam[], int pasienCountParam) {
    if (isLoggedIn) {
        printf("Anda sudah login sebagai %s!\n", currentUser.username);
        return; // Jika sudah login, tampilkan pesan dan keluar
    }

    char usernameInput[MAX_USERNAME_LEN + 2];
    char passwordInput[MAX_PASSWORD_LEN + 2];

    // Input username
    printf("Username: ");
    if (scanf("%20s", usernameInput) != 1) { 
        printf("Input username gagal. Coba lagi.\n");
        clearInputBuffer();
        return;
    }

    if (strlen(usernameInput) >= MAX_USERNAME_LEN) {
        char nextChar = getchar(); 
        if (nextChar != '\n' && nextChar != EOF && nextChar != ' ' && nextChar != '\t') {
            printf("Username terlalu panjang!\n");
            ungetc(nextChar, stdin); 
            clearInputBuffer();
            return;
        }
        if (nextChar != EOF) ungetc(nextChar, stdin); 
    }
    clearInputBuffer();

    // Input password
    printf("Password: ");
    if (scanf("%20s", passwordInput) != 1) { 
        printf("Input password gagal. Coba lagi.\n");
        clearInputBuffer();
        return;
    }

    if (strlen(passwordInput) >= MAX_PASSWORD_LEN) {
        char nextChar = getchar();
        if (nextChar != '\n' && nextChar != EOF && nextChar != ' ' && nextChar != '\t') {
            printf("Password terlalu panjang!\n");
            ungetc(nextChar, stdin);
            clearInputBuffer();
            return;
        }
        if (nextChar != EOF) ungetc(nextChar, stdin);
    }
    clearInputBuffer();

    // Cek login untuk Manager
    if (strcmp(usernameInput, managerData->username) == 0) {
        if (strcmp(passwordInput, managerData->password) == 0) {
            currentUser = *managerData;
            isLoggedIn = 1;
            printf("Selamat datang Manager %s!\n", currentUser.username);
        } else {
            printf("Password salah untuk pengguna yang bernama %s!\n", usernameInput);
        }
        return;
    }

    // Cek login untuk Dokter
    for (int i = 0; i < dokterCountParam; i++) {
        if (strcmp(usernameInput, dokterListParam[i].username) == 0) {
            if (strcmp(passwordInput, dokterListParam[i].password) == 0) {
                currentUser = dokterListParam[i];
                isLoggedIn = 1;
                printf("Selamat pagi Dokter %s!\n", currentUser.username);
            } else {
                printf("Password salah untuk pengguna yang bernama %s!\n", usernameInput);
            }
            return;
        }
    }

    // Cek login untuk Pasien
    for (int i = 0; i < pasienCountParam; i++) {
        if (strcmp(usernameInput, pasienListParam[i].username) == 0) {
            if (strcmp(passwordInput, pasienListParam[i].password) == 0) {
                currentUser = pasienListParam[i];
                isLoggedIn = 1;
                printf("Selamat pagi %s! Ada keluhan apa ?\n", currentUser.username);
            } else {
                printf("Username atau password salah untuk pengguna yang bernama %s!\n", usernameInput);
            }
            return;
        }
    }

    // Jika username tidak ditemukan
    printf("Tidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", usernameInput);
}

void registerPasien(User listPasien[], int *jumlahPasienAktif, Set *usernameSetGlobal) {
    if (isLoggedIn) {
        printf("Anda sudah login sebagai %s. Silakan logout dulu untuk register akun baru.\n", currentUser.username);
        return;
    }

    if (*jumlahPasienAktif >= MAX_JUMLAH_USER) {
        printf("Registrasi gagal! Kapasitas penyimpanan pasien di sistem sudah penuh.\n");
        return;
    }

    char tempUsername[MAX_USERNAME_LEN + 2]; 
    char tempPassword[MAX_PASSWORD_LEN + 2];

    // Input username
    printf("Username: ");
    if (scanf("%20s", tempUsername) != 1) { 
        printf("Input username gagal.\n");
        clearInputBuffer(); 
        return;
    }
    if (strlen(tempUsername) >= MAX_USERNAME_LEN) { 
        printf("Registrasi gagal! Username terlalu panjang.\n");
        clearInputBuffer(); 
        return;
    }
    clearInputBuffer(); 

    // Validasi username hanya boleh huruf
    for (int i = 0; tempUsername[i] != '\0'; i++) {
        if (!((tempUsername[i] >= 'a' && tempUsername[i] <= 'z') || (tempUsername[i] >= 'A' && tempUsername[i] <= 'Z'))) {
            printf("Registrasi gagal! Username hanya boleh terdiri dari huruf.\n");
            return;
        }
    }

    // Input password
    printf("Password: ");
    if (scanf("%20s", tempPassword) != 1) { 
        printf("Input password gagal.\n");
        clearInputBuffer();
        return;
    }
    if (strlen(tempPassword) >= MAX_PASSWORD_LEN) {
        printf("Registrasi gagal! Password terlalu panjang (maks %d karakter).\n", MAX_PASSWORD_LEN - 1);
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    // Cek apakah username sudah ada
    if (searchSet(*usernameSetGlobal, tempUsername)) {
        printf("Registrasi gagal! Pasien dengan nama '%s' sudah terdaftar.\n", tempUsername);
        return;
    }

    idpenggunasebelum++; 
    int idxBaru = *jumlahPasienAktif; 

    listPasien[idxBaru].id = idpenggunasebelum;
    strncpy(listPasien[idxBaru].username, tempUsername, MAX_USERNAME_LEN - 1);
    listPasien[idxBaru].username[MAX_USERNAME_LEN - 1] = '\0';
    strncpy(listPasien[idxBaru].password, tempPassword, MAX_PASSWORD_LEN - 1);
    listPasien[idxBaru].password[MAX_PASSWORD_LEN - 1] = '\0';
    strcpy(listPasien[idxBaru].role, "Pasien");
    
    // Reset data pasien
    listPasien[idxBaru].namaPenyakit[0] = '\0'; 
    listPasien[idxBaru].nyawa = 3; 
    listPasien[idxBaru].dokterPerawat[0] = '\0'; 
    listPasien[idxBaru].aura = 0; 
    listPasien[idxBaru].kodeRuangan[0] = '\0';
    
    listPasien[idxBaru].suhuTubuh = 0.0f; 
    listPasien[idxBaru].tekananDarahSistolik = 0;
    listPasien[idxBaru].tekananDarahDiastolik = 0;
    listPasien[idxBaru].detakJantung = 0;
    listPasien[idxBaru].saturasiOksigen = 0.0f;
    listPasien[idxBaru].kadarGulaDarah = 0;
    listPasien[idxBaru].beratBadan = 0.0f;
    listPasien[idxBaru].tinggiBadan = 0.0f;
    listPasien[idxBaru].kadarKolesterol = 0;
    listPasien[idxBaru].trombosit = 0;

    (*jumlahPasienAktif)++;
    insertSet(usernameSetGlobal, tempUsername); 
    printf("Pasien %s berhasil ditambahkan!\n", tempUsername); 
}

void logout() {
    if (!isLoggedIn) {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout.\n");
        return;
    }
    printf("Sampai jumpa!\n");
    isLoggedIn = 0;
    memset(&currentUser, 0, sizeof(currentUser)); // Clear currentUser data
}

void generateKodeUnik(const char *username, char *outputRLE) { 
    int len = strlen(username);
    int outIdx = 0;
    if (len == 0) {
        outputRLE[0] = '\0';
        return;
    }

    for (int i = 0; i < len; ) {
        char currentChar = username[i];
        int count = 0;
        while (i + count < len && username[i + count] == currentChar) {
            count++;
        }

        if (count > 1) {
            if (count < 10) { 
                 outputRLE[outIdx++] = count + '0';
            } else {
                outputRLE[outIdx++] = '9'; 
            }
        }

        if (outIdx < (MAX_USERNAME_LEN * 2) - 1) {  // Pastikan tidak melampaui buffer
             outputRLE[outIdx++] = currentChar;
        } else {
            break;  // Stop jika buffer mendekati penuh
        }
        i += count;
    }
    outputRLE[outIdx] = '\0';
}

void lupaPassword (User *managerData, User dokterListParam[], int dokterCountParam, User pasienListParam[], int pasienCountParam) {
    char username[MAX_USERNAME_LEN + 2];
    char kodeUnikInput[MAX_USERNAME_LEN * 2 + 2]; 
    char expectedKodeUnik[MAX_USERNAME_LEN * 2 + 2]; 
    char newPassword[MAX_PASSWORD_LEN + 2];

    printf("Username: ");
    if (scanf("%20s", username) != 1) { clearInputBuffer(); return; }
    if (strlen(username) >= MAX_USERNAME_LEN) { 
        printf("Invalid. Username terlalu panjang!\n"); 
        clearInputBuffer(); 
        return; 
    }
    clearInputBuffer();

    printf("Kode Unik: ");
    if (scanf("%39s", kodeUnikInput) != 1) { clearInputBuffer(); return; }
    clearInputBuffer();

    // Generate kode unik yang diharapkan dari username yang dimasukkan
    generateKodeUnik(username, expectedKodeUnik);

    // Verifikasi kode unik
    if (strcmp(kodeUnikInput, expectedKodeUnik) != 0) {
        printf("Kode unik salah!\n");
        return;
    }

    // Proses untuk Manager
    if (strcmp(username, managerData->username) == 0) {
        printf("Halo Manager %s, silakan daftarkan ulang password anda!\n", username);
        printf("Password Baru: ");
        if (scanf("%20s", newPassword) != 1) { clearInputBuffer(); return; }
        if (strlen(newPassword) >= MAX_PASSWORD_LEN) { 
            printf("Password terlalu panjang!\n");
            clearInputBuffer(); 
            return; 
        }    
        clearInputBuffer();
        strncpy(managerData->password, newPassword, MAX_PASSWORD_LEN - 1);
        managerData->password[MAX_PASSWORD_LEN - 1] = '\0';
        printf("Password berhasil diubah!\n");
        return;
    }

    // Proses untuk Dokter
    for (int i = 0; i < dokterCountParam; i++) {
        if (strcmp(username, dokterListParam[i].username) == 0) {
            printf("Halo Dokter %s, silakan daftarkan ulang password anda!\n", username);
            printf("Password Baru: ");
            if (scanf("%20s", newPassword) != 1) { clearInputBuffer(); return; }
            if (strlen(newPassword) >= MAX_PASSWORD_LEN) { 
                printf("Password terlalu panjang!\n");
                clearInputBuffer(); 
                return; 
            }           
            clearInputBuffer();
            strncpy(dokterListParam[i].password, newPassword, MAX_PASSWORD_LEN - 1);
            dokterListParam[i].password[MAX_PASSWORD_LEN - 1] = '\0';
            printf("Password berhasil diubah!\n");
            return;
        }
    }

    // Proses untuk Pasien
    for (int i = 0; i < pasienCountParam; i++) {
        if (strcmp(username, pasienListParam[i].username) == 0) {
            printf("Halo %s, silakan daftarkan ulang password anda!\n", username); 
            printf("Password Baru: ");
            if (scanf("%20s", newPassword) != 1) { clearInputBuffer(); return; }
            if (strlen(newPassword) >= MAX_PASSWORD_LEN) { 
                printf("Password terlalu panjang!\n");
                clearInputBuffer(); 
                return; 
            }    
            clearInputBuffer();
            strncpy(pasienListParam[i].password, newPassword, MAX_PASSWORD_LEN - 1);
            pasienListParam[i].password[MAX_PASSWORD_LEN - 1] = '\0';
            printf("Password berhasil diubah!\n");
            return;
        }
    }

    printf("Username tidak terdaftar!\n");
}