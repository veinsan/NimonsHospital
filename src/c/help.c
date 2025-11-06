#include "help.h"

// Fungsi utama untuk menampilkan menu bantuan berdasarkan status login
void help() {
    printf("\n=========== HELP ===========\n\n");

    // Jika pengguna belum login
    if (!isLoggedIn) {
        // Menampilkan pesan bahwa pengguna belum login
        printf("Kamu belum login sebagai role apapun. Silahkan login terlebih dahulu.\n\n");
        printf("1. LOGIN: Masuk ke dalam akun yang sudah terdaftar\n");
        printf("2. REGISTER: Membuat akun baru\n");
    } else {
        // Jika sudah login, tampilkan menu sesuai role pengguna
        tampilkanMenuHelp(currentUser.role);
    }

    printf("\nFootnote:\n");
    printf("1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("2. Jangan lupa untuk memasukkan input yang valid\n");
}

// Fungsi untuk membuat linked list dari fitur yang tersedia
FiturHelp* createLinkedList(const char *features[], int featureCount) {
    FiturHelp *head = NULL;  // Menyimpan pointer ke node pertama
    FiturHelp *tail = NULL;  // Menyimpan pointer ke node terakhir

    // Membuat linked list untuk setiap fitur yang ada
    for (int i = 0; i < featureCount; i++) {
        FiturHelp *newNode = (FiturHelp*)malloc(sizeof(FiturHelp));  // Alokasi memori untuk node baru
        strcpy(newNode->feature, features[i]);  // Menyalin nama fitur ke node baru
        newNode->next = NULL;  // Node berikutnya adalah NULL pada awalnya

        if (head == NULL) {
            // Jika linked list kosong, node baru jadi head dan tail
            head = tail = newNode;
        } else {
            // Menambah node baru ke akhir linked list
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;  // Mengembalikan head dari linked list
}

// Fungsi untuk menampilkan linked list dalam halaman
void displayLinkedList(FiturHelp *head) {
    const int itemsPerPage = 4;  // Menentukan jumlah item yang ditampilkan per halaman
    int totalItems = 0;  // Variabel untuk menghitung total item dalam linked list
    FiturHelp *temp = head;

    // Menghitung total item dalam linked list
    while (temp != NULL) {
        totalItems++;
        temp = temp->next;
    }

    // Menghitung total halaman yang diperlukan
    int totalPages = (totalItems + itemsPerPage - 1) / itemsPerPage;
    int currentPage = 0;  // Menyimpan halaman saat ini
    char input[10];

    do {
        #ifdef _WIN32
        system("cls");  // Membersihkan layar di Windows
        #else
        system("clear");  // Membersihkan layar di sistem lain (Unix-based)
        #endif

        // Menampilkan halaman dan informasi
        printf("=========== MENU (Page %d of %d) ===========\n\n", currentPage + 1, totalPages);

        FiturHelp *current = head;
        int nomor = 1 + currentPage * itemsPerPage;

        // Menampilkan fitur dari linked list sesuai halaman
        for (int i = 0; i < currentPage * itemsPerPage && current != NULL; i++) {
            current = current->next;
        }

        // Menampilkan fitur dalam halaman saat ini
        for (int i = 0; i < itemsPerPage && current != NULL; i++) {
            printf("%d. %s\n", nomor++, current->feature);
            current = current->next;
        }

        // Menampilkan navigasi untuk berpindah halaman
        printf("\n[n] Next page | [p] Previous page | [q] Quit help\n");
        printf(">>> ");
        scanf("%s", input);  // Menerima input untuk navigasi halaman

        // Menangani input untuk navigasi halaman
        if (strcmp(input, "n") == 0 && currentPage < totalPages - 1) {
            currentPage++;  // Pindah ke halaman berikutnya
        } else if (strcmp(input, "p") == 0 && currentPage > 0) {
            currentPage--;  // Pindah ke halaman sebelumnya
        } else if (strcmp(input, "q") != 0 && strcmp(input, "n") != 0 && strcmp(input, "p") != 0) {
            // Menangani input yang tidak valid
            printf("Perintah tidak dikenal. Gunakan 'n', 'p', atau 'q'.\n");
            getchar();  // Mengkonsumsi karakter ekstra yang mungkin tertinggal
        }

    } while (strcmp(input, "q") != 0);  // Mengulang hingga pengguna memilih untuk keluar
}

// Fungsi untuk menghapus linked list setelah digunakan
void deleteLinkedList(FiturHelp *head) {
    FiturHelp *current = head;
    while (current != NULL) {
        FiturHelp *toDelete = current;
        current = current->next;
        free(toDelete);  // Menghapus node dari memori
    }
}

// Fungsi untuk menampilkan menu bantuan berdasarkan role pengguna
void tampilkanMenuHelp(const char *role) {
    // Daftar fitur yang tersedia untuk masing-masing role

    // Fitur untuk Manager
    const char *managerFeatures[] = {
        "LOGOUT: Keluar dari akun yang sedang digunakan",
        "LUPA_PASSWORD: Membuat password baru",
        "LIHAT_DENAH: Lihat ruangan di RS serta detailnya",
        "LIHAT_USER: Melihat semua pengguna (Dokter/Pasien)",
        "LIHAT_PASIEN: Melihat data semua pasien",
        "LIHAT_DOKTER: Melihat data semua dokter",
        "CARI_USER: Mencari data spesifik",
        "CARI_PASIEN: Mencari data pasien spesifik",
        "CARI_DOKTER: Mencari data dokter spesifik",
        "TAMBAH_DOKTER: Mendaftarkan dokter baru ke sistem",
        "ASSIGN_DOKTER: Menempatkan dokter ke dalam ruangan tertentu",
        "LIHAT_SEMUA_ANTRIAN: Melihat denah dan antrian ruangan",
        "LIHAT_FINANSIAL: Melihat kondisi keuangan rumah sakit",
        "UBAH_DENAH: Mengubah ukuran denah rumah sakit",
        "PINDAH_DOKTER: Memindahkan dokter antar ruangan"
    };

    // Fitur untuk Dokter
    const char *doctorFeatures[] = {
        "LOGOUT: Keluar dari akun yang sedang digunakan",
        "LUPA_PASSWORD: Membuat password baru",
        "LIHAT_DENAH: Lihat ruangan di RS serta detailnya",
        "DIAGNOSIS: Melakukan diagnosis penyakit",
        "NGOBATIN: Memberikan obat kepada pasien",
        "LIHAT_RUANGAN: Melihat detail ruangan",
        "LIHAT_DOMPET: Melihat jumlah Banarich"
    };

    // Fitur untuk Pasien
    const char *patientFeatures[] = {
        "LOGOUT: Keluar dari akun yang sedang digunakan",
        "LUPA_PASSWORD: Membuat password baru",
        "LIHAT_DENAH: Lihat ruangan di RS serta detailnya",
        "DAFTAR_CHECKUP: Mendaftar untuk pemeriksaan dokter",
        "ANTRIAN: Melihat status antrian",
        "PULANGDOK: Minta izin untuk pulang",
        "MINUM_OBAT: Mengonsumsi obat dari inventory",
        "PENAWAR: Mengeluarkan obat terakhir dari perut",
        "LIHAT_RUANGAN: Melihat detail ruangan",
        "LIHAT_DOMPET: Melihat jumlah Banarich",
        "GACHA_GAMING: Gunakan mesin gacha untuk Banarich",
        "SKIP_ANTRIAN: Potong antrian ke depan",
        "CANCEL_ANTRIAN: Batalkan antrian"
    };

    FiturHelp *head = NULL;

    // Memilih fitur berdasarkan role pengguna
    if (strcmp(role, "Manager") == 0) {
        printf("Halo Manager %s. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", currentUser.username);
        head = createLinkedList(managerFeatures, sizeof(managerFeatures) / sizeof(managerFeatures[0]));
    } else if (strcmp(role, "Dokter") == 0) {
        printf("Halo Dokter %s. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", currentUser.username);
        head = createLinkedList(doctorFeatures, sizeof(doctorFeatures) / sizeof(doctorFeatures[0]));
    } else if (strcmp(role, "Pasien") == 0) {
        printf("Selamat datang, %s. Berikut adalah hal-hal yang dapat kamu lakukan sekarang:\n\n", currentUser.username);
        head = createLinkedList(patientFeatures, sizeof(patientFeatures) / sizeof(patientFeatures[0]));
    }

    // Menampilkan daftar fitur
    if (head != NULL) {
        displayLinkedList(head);  // Menampilkan linked list
        deleteLinkedList(head);   // Menghapus linked list setelah digunakan
    }
}