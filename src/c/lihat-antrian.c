#include "lihat-antrian.h"

// Fungsi untuk menampilkan antrian pasien di ruangan tertentu
void lihatantrian(Ruangan ruanganListDilempar[], int jumlahRuanganDilempar, int barisUntukDenah, int kolomUntukDenah, int dokterCountDilempar) { 
    // Memastikan pengguna sudah login
    if (!isLoggedIn) { 
        printf("Harap melakukan login terlebih dahulu.\n");
        return;
    }

    // Memastikan hanya Manager yang dapat mengakses fitur ini
    if (strcmp(currentUser.role, "Manager") != 0){ 
        printf("Perintah LIHAT_ANTRIAN hanya dapat diakses oleh Manager.\n"); 
        return;
    }

    // Menampilkan denah ruangan
    lihatDenah(jumlahRuanganDilempar, barisUntukDenah, kolomUntukDenah); 
    printf("\n"); 

    boolean adaRuanganDitampilkan = FALSE; // Menandakan apakah ada ruangan yang ditampilkan

    // Iterasi untuk menampilkan informasi setiap ruangan
    for (int i = 0; i < jumlahRuanganDilempar; i++) { 
        const Ruangan* r = &ruanganListDilempar[i]; 

        // Jika ruangan tidak ada dokter yang bertugas, lewati ruangan ini
        if (strlen(r->dokter) == 0) continue; 
        
        adaRuanganDitampilkan = TRUE; // Tandai ada ruangan yang ditampilkan

        // Menentukan kode baris dan nomor kolom ruangan berdasarkan indeks
        char kodeBaris = 'A' + (i / kolomUntukDenah); 
        int nomorKolom = (i % kolomUntukDenah) + 1;   

        // Menampilkan informasi tentang ruangan
        printf("============ Ruangan %c%d ============\n", kodeBaris, nomorKolom);
        printf("Kapasitas  : %d\n", r->kapasitas);
        printf("Dokter     : Dr. %s\n", r->dokter); 

        // Menampilkan daftar pasien yang berada di dalam ruangan
        printf("Pasien di dalam ruangan:\n");
        if (r->jumlahPasien == 0) {
            printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
        } else {
            for (int j = 0; j < r->jumlahPasien; j++) {
                printf("  %d. %s\n", j + 1, r->pasien[j]);
            }
        }

        // Menampilkan pasien yang ada di antrian luar ruangan
        printf("Pasien di antrian:\n");
        AntrianDokter* dq = NULL;
        // Mencari antrian dokter berdasarkan nama dokter di ruangan
        for (int j = 0; j < jumlahDokter; j++) { 
            if (dokterQueues[j].dokter != NULL && 
                strcmp(dokterQueues[j].dokter->username, r->dokter) == 0) { 
                dq = &dokterQueues[j]; // Menyimpan referensi antrian dokter
                break;
            }
        }

        // Jika antrian dokter ada dan terdapat pasien dalam antrian
        if (dq != NULL && dq->head != NULL) {
            AntrianNode* node = dq->head;
            int nomor = 1;
            // Menampilkan semua pasien dalam antrian
            while (node != NULL) {
                printf("  %d. %s\n", nomor, node->pasien_data.username);
                node = node->next; // Melanjutkan ke pasien berikutnya
                nomor++;
            }
        } else {
            // Jika tidak ada pasien dalam antrian
            printf("  Tidak ada pasien di antrian saat ini.\n");
        }
        printf("\n"); 
    }

    // Jika tidak ada ruangan yang ditampilkan (tidak ada dokter atau antrian)
    if (!adaRuanganDitampilkan) {
        printf("Saat ini tidak ada ruangan yang memiliki dokter bertugas atau tidak ada antrian.\n");
    }
}