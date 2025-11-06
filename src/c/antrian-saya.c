#include "antrian-saya.h"

// Fungsi untuk menampilkan status antrian pasien
void antrianSaya(int dokterCount) {
    // Memastikan bahwa hanya pasien yang sudah login yang bisa mengakses fitur ini
    if (!isLoggedIn || strcmp(currentUser.role, "Pasien") != 0) {
        printf("Khusus Pasien yang sudah Login!\n");
        return;  // Jika bukan pasien yang login, keluar dari fungsi
    }

    int found = 0;  // Variabel untuk menandai apakah pasien ditemukan dalam antrian

    // Iterasi untuk mencari dokter yang memiliki antrian
    for (int i = 0; i < MAX_JUMLAH_USER; i++) {
        // Melewati antrian yang kosong atau tidak memiliki dokter
        if (dokterQueues[i].dokter == NULL || dokterQueues[i].jumlah_antrian == 0) {
            continue;
        }

        // Menelusuri antrian pasien untuk mencari apakah pasien yang sedang login terdaftar
        AntrianNode* current = dokterQueues[i].head;
        int posisi = 1; // Menyimpan posisi pasien dalam antrian
        while (current != NULL) {
            // Jika pasien yang sedang login ditemukan dalam antrian
            if (strcmp(current->pasien_data.username, currentUser.username) == 0) {
                // Menampilkan status antrian pasien
                printf("\nStatus antrian Anda:\n");
                printf("Dokter: Dr. %s\n", dokterQueues[i].dokter->username);
                printf("Ruangan: %s\n", dokterQueues[i].dokter->kodeRuangan);
                printf("Posisi antrian: %d dari %d\n", posisi, dokterQueues[i].jumlah_antrian);
                found = 1; // Tandai bahwa pasien ditemukan
                break;
            }
            current = current->next; // Melanjutkan ke pasien berikutnya dalam antrian
            posisi++; // Menambah posisi dalam antrian
        }
        if (found) {
            break;  // Jika pasien ditemukan, keluar dari loop
        }
    }

    // Jika pasien tidak ditemukan dalam antrian
    if (!found) {
        printf("\nAnda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
    }
}