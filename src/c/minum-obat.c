#include "minum-obat.h"

// Fungsi untuk menginisialisasi stack obat
void buatStackObat(StackObat *s) {
    s->top = -1; // Menandakan stack kosong
}

// Fungsi untuk memeriksa apakah stack obat kosong
int stackKosong(StackObat s) {
    return s.top == -1; // Mengembalikan true jika stack kosong
}

// Fungsi untuk memeriksa apakah stack obat penuh
int stackPenuh(StackObat s) {
    return s.top == MAX_OBAT - 1; // Mengembalikan true jika stack penuh
}

// Fungsi untuk menambahkan obat ke dalam stack
void pushObat(StackObat *s, const char *obat) {
    if (!stackPenuh(*s)) { // Pastikan stack tidak penuh
        s->top++; // Naikkan top stack
        // Salin nama obat ke dalam stack, pastikan tidak melebihi kapasitas
        strncpy(s->data[s->top], obat, MAX_NAMA_OBAT_LEN - 1);
        s->data[s->top][MAX_NAMA_OBAT_LEN - 1] = '\0'; // Tambahkan null terminator
    }
}

// Fungsi untuk mengeluarkan obat dari stack
void popObat(StackObat *s, char *obatDihapus) {
    if (!stackKosong(*s)) { // Pastikan stack tidak kosong
        // Salin nama obat yang dikeluarkan ke obatDihapus
        strncpy(obatDihapus, s->data[s->top], MAX_NAMA_OBAT_LEN - 1);
        obatDihapus[MAX_NAMA_OBAT_LEN - 1] = '\0'; // Tambahkan null terminator
        s->top--; // Turunkan top stack
    } else {
        obatDihapus[0] = '\0'; // Jika stack kosong, set obatDihapus ke string kosong
    }
}

// Fungsi untuk menginisialisasi list obat
void buatListObat(ListObat *l) {
    l->size = 0; // Set ukuran list obat ke 0
}

// Fungsi untuk menghapus obat pada list obat berdasarkan index
void hapusObat(ListObat *l, int index) {
    if (index < 0 || index >= l->size) { // Pastikan index valid
        return; // Jika tidak valid, keluar dari fungsi
    }

    // Geser semua obat setelah index yang dihapus ke kiri
    for (int i = index; i < l->size - 1; i++) {
        strncpy(l->data[i], l->data[i + 1], MAX_NAMA_OBAT_LEN - 1);
        l->data[i][MAX_NAMA_OBAT_LEN - 1] = '\0'; // Pastikan null terminator
    }
    l->size--; // Kurangi ukuran list obat
}

// Fungsi untuk menampilkan daftar obat dalam inventory
void tampilkanListObat(ListObat l) {
    printf("\n============ DAFTAR OBAT (Inventory) ============\n");
    if (l.size == 0) {
        printf("Inventory kosong.\n"); // Jika inventory kosong, beri pesan
        return;
    }
    // Menampilkan semua obat dalam inventory
    for (int i = 0; i < l.size; i++) {
        printf("%d. %s\n", i + 1, l.data[i]);
    }
}

void tambahObat(ListObat *inventory, const char *obat) {
    if (inventory->size < MAX_OBAT) {  // Pastikan kapasitas inventory tidak terlampaui
        strncpy(inventory->data[inventory->size], obat, MAX_NAMA_OBAT_LEN - 1);
        inventory->data[inventory->size][MAX_NAMA_OBAT_LEN - 1] = '\0'; // Pastikan null terminator
        inventory->size++;  // Tingkatkan ukuran inventory
        printf("Obat '%s' berhasil ditambahkan ke inventory!\n", obat);
    } else {
        printf("Inventory obat penuh! Tidak bisa menambah obat '%s'.\n", obat);
    }
}

// Fungsi untuk mengonsumsi obat
void minumObat(User *pasien, StackObat *perut, ListObat *inventory) {
    if (inventory->size == 0) {
        printf("\nInventory obat kosong! Tidak ada obat yang bisa diminum.\n");
        return; // Jika inventory kosong, keluar dari fungsi
    }

    tampilkanListObat(*inventory); // Menampilkan daftar obat yang tersedia

    int pilihan;
    printf("\nPilih obat untuk diminum (nomor): ");
    if (scanf("%d", &pilihan) != 1) { // Validasi input untuk pilihan obat
        printf("\nInput tidak valid! Masukkan nomor obat.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Membersihkan input buffer
        return;
    }

    if (pilihan < 1 || pilihan > inventory->size) { // Cek apakah pilihan valid
        printf("\nPilihan nomor tidak tersedia!\n");
        return;
    }

    // Menambahkan obat yang dipilih ke dalam stack perut
    pushObat(perut, inventory->data[pilihan - 1]);
    printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", inventory->data[pilihan - 1]);
    
    // Menghapus obat yang telah diminum dari inventory
    hapusObat(inventory, pilihan - 1);

    // Menampilkan sisa inventory setelah obat diminum
    if (inventory->size > 0) {
        tampilkanListObat(*inventory);
    } else {
        printf("\nInventory sekarang kosong.\n"); // Jika inventory kosong setelah obat diminum
    }
}