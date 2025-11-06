#include "mainin-antrian.h"

// Fungsi untuk memajukan posisi pasien di antrian dokter
void skipAntrian(const char* dokterUsername) {
    // Memeriksa apakah pengguna sudah login
    if (!isLoggedIn) {
        printf("Harap login terlebih dahulu!\n");
        return;
    }
    
    // Mencari dokter berdasarkan username
    for (int i = 0; i < jumlahDokter; i++) {
        // Jika dokter ditemukan dalam antrian
        if (strcmp(dokterQueues[i].dokter->username, dokterUsername) == 0) {
            AntrianNode* pasien = dokterQueues[i].head;
            AntrianNode* prev = NULL;
            int position = 1;

            // Menelusuri antrian pasien untuk menemukan posisi pasien yang sedang login
            while (pasien != NULL) {
                if (strcmp(pasien->pasien_data.username, currentUser.username) == 0) {
                    // Jika pasien sudah di posisi paling depan
                    if (position == 1) {
                        printf("Anda sudah berada di posisi paling depan antrian!\n");
                        return;
                    }
                    
                    // Jika pasien tidak di posisi pertama, pindahkan pasien ke depan antrian
                    if (prev != NULL) {
                        prev->next = pasien->next; // Menghubungkan pasien sebelumnya ke pasien berikutnya
                    }

                    if (dokterQueues[i].tail == pasien && prev != NULL) {
                        dokterQueues[i].tail = prev; // Memperbarui tail jika pasien terakhir
                    }
                    
                    pasien->next = dokterQueues[i].head; // Menyisipkan pasien di depan antrian
                    dokterQueues[i].head = pasien;
                    if (dokterQueues[i].jumlah_antrian == 1) { 
                        dokterQueues[i].tail = dokterQueues[i].head; // Jika hanya ada satu pasien
                    }

                    printf("Anda berhasil maju ke depan antrian Dr. %s!\n", dokterQueues[i].dokter->username);
                    return;
                }
                prev = pasien; // Menyimpan pasien sebelumnya
                pasien = pasien->next; // Melanjutkan ke pasien berikutnya
                position++; // Menambah posisi antrian
            }
            printf("Skip antrian gagal! Anda tidak sedang terdaftar dalam antrian Dr. %s.\n", dokterUsername);
            return;
        }
    }
    printf("Dokter %s tidak ditemukan.\n", dokterUsername); // Jika dokter tidak ditemukan
}

// Fungsi untuk membatalkan antrian pasien
void cancelAntrian(const char* dokterUsername) {
    // Memeriksa apakah pengguna sudah login
    if (!isLoggedIn) {
        printf("Harap login terlebih dahulu!\n");
        return;
    }

    // Mencari dokter berdasarkan username
    for (int i = 0; i < jumlahDokter; i++) {
        // Jika dokter ditemukan dalam antrian
        if (strcmp(dokterQueues[i].dokter->username, dokterUsername) == 0) {
            AntrianNode* pasien = dokterQueues[i].head;
            AntrianNode* prev = NULL;

            // Menelusuri antrian pasien untuk menemukan pasien yang sedang login
            while (pasien != NULL) {
                if (strcmp(pasien->pasien_data.username, currentUser.username) == 0) {
                    // Jika pasien berada di posisi pertama, update head antrian
                    if (prev == NULL) {
                        dokterQueues[i].head = pasien->next;
                    } else {
                        prev->next = pasien->next; // Menghubungkan pasien sebelumnya ke pasien berikutnya
                    }

                    // Jika pasien adalah pasien terakhir dalam antrian, update tail
                    if (dokterQueues[i].tail == pasien) {
                        dokterQueues[i].tail = prev;
                    }

                    // Menghapus node pasien dari antrian dan mengurangi jumlah antrian
                    free(pasien);
                    dokterQueues[i].jumlah_antrian--;

                    // Jika antrian kosong, set head dan tail ke NULL
                    if (dokterQueues[i].head == NULL) {
                        dokterQueues[i].tail = NULL;
                    }

                    printf("Anda berhasil keluar dari antrian Dr. %s di ruangan %s!\n", dokterQueues[i].dokter->username, dokterQueues[i].dokter->kodeRuangan);
                    return;
                }
                prev = pasien; // Menyimpan pasien sebelumnya
                pasien = pasien->next; // Melanjutkan ke pasien berikutnya
            }
            printf("Pembatalan antrian gagal! Anda tidak sedang terdaftar dalam antrian manapun.\n");
            return;
        }
    }
    printf("Dokter %s tidak ditemukan.\n", dokterUsername); // Jika dokter tidak ditemukan
}