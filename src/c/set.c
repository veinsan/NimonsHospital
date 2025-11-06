#include "set.h"

// Inisialisasi set dengan mengatur ukurannya menjadi 0
void buatSet(Set *s) {
    s->size = 0; // Set ukuran menjadi 0 untuk menandakan set kosong
}

// Mengubah string menjadi huruf kecil dan menyimpannya di string tujuan
void ubahKeHurufKecil(char *dest, const char *src) {
    int i = 0;
    // Iterasi melalui setiap karakter dalam string sumber
    while (src[i] != '\0' && i < (MAX_USERNAME_LEN - 1)) {
        // Jika karakter adalah huruf besar, ubah menjadi huruf kecil
        dest[i] = (src[i] >= 'A' && src[i] <= 'Z') ? src[i] + ('a' - 'A') : src[i];
        i++;
    }
    dest[i] = '\0'; // Tambahkan karakter null di akhir string tujuan
}

// Mencari elemen dalam set (perbandingan tidak sensitif huruf besar-kecil)
int searchSet(Set s, const char *input) {
    // String sementara untuk menyimpan versi huruf kecil dari input
    char tempInputLower[MAX_USERNAME_LEN];
    ubahKeHurufKecil(tempInputLower, input); // Mengubah input menjadi huruf kecil

    // Iterasi melalui elemen set untuk memeriksa apakah input ada
    for (int i = 0; i < s.size; i++) {
        // Jika ditemukan kecocokan, kembalikan 1 (benar)
        if (strcmp(tempInputLower, s.elements[i]) == 0) {
            return 1;
        }
    }
    return 0; // Kembalikan 0 (salah) jika tidak ada kecocokan
}

// Menyisipkan elemen baru ke dalam set jika belum ada
void insertSet(Set *s, const char *input) {
    // Memeriksa apakah set sudah penuh
    if (s->size >= MAX_JUMLAH_USER) {
        printf("Set penuh! Elemen '%s' tidak bisa ditambahkan.\n", input);
        return; // Kembali jika set sudah penuh
    }

    // Jika elemen belum ada dalam set, tambahkan elemen baru
    if (!searchSet(*s, input)) {
        ubahKeHurufKecil(s->elements[s->size], input); // Ubah menjadi huruf kecil dan simpan dalam set
        s->size++; // Tambahkan ukuran set
    }
}

// Menghapus elemen dari set jika ditemukan
void hapusSet(Set *s, const char *input) {
    // Memeriksa kondisi input atau set yang tidak valid
    if (s == NULL || input == NULL || s->size == 0) {
        return; // Keluar jika kondisi tidak valid
    }

    // Mengubah input menjadi huruf kecil untuk perbandingan yang tidak sensitif huruf besar-kecil
    char inputLower[MAX_USERNAME_LEN];
    ubahKeHurufKecil(inputLower, input);

    int foundidx = -1; // Indeks untuk menyimpan posisi elemen yang akan dihapus

    // Mencari elemen dalam set
    for (int i = 0; i < s->size; i++) {
        if (strcmp(s->elements[i], inputLower) == 0) {
            foundidx = i; // Jika ditemukan, simpan indeksnya
            break; // Keluar dari loop setelah elemen ditemukan
        }
    }

    // Jika elemen ditemukan, hapus elemen tersebut
    if (foundidx != -1) {
        // Geser semua elemen setelah elemen yang ditemukan ke kiri
        for (int i = foundidx; i < s->size - 1; i++) {
            strcpy(s->elements[i], s->elements[i + 1]);
        }
        s->size--; // Kurangi ukuran set

        // Bersihkan elemen terakhir (opsional tetapi membantu untuk menghindari data yang tidak sengaja)
        if (s->size >= 0 && s->size < MAX_JUMLAH_USER) {
            s->elements[s->size][0] = '\0'; // Tambahkan karakter null di elemen terakhir
        }
    }
}