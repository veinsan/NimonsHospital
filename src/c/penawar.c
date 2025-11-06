#include "minum-obat.h"

// Fungsi untuk menangani proses menelan obat dan mengembalikannya ke inventory
void minumPenawar(StackObat *perut, ListObat *inventory) {
    // Mengecek apakah stack perut kosong (belum ada obat yang dimakan)
    if (stackKosong(*perut)) {
        printf("\nPerut kosong!! Belum ada obat yang dimakan.\n");
        return; // Jika perut kosong, keluar dari fungsi
    }

    // Mengecek apakah inventory penuh dan tidak bisa menyimpan obat lagi
    if (inventory->size >= MAX_OBAT) {
        printf("\nInventory penuh! Tidak bisa menyimpan obat kembali.\n");
        return; // Jika inventory penuh, keluar dari fungsi
    }

    char obatDikeluarkan[MAX_NAMA_OBAT];  // Menyimpan nama obat yang akan dikeluarkan

    // Mengeluarkan obat dari stack perut dan menyimpannya dalam obatDikeluarkan
    popObat(perut, obatDikeluarkan);

    // Menyimpan obat yang dikeluarkan ke dalam inventory
    strcpy(inventory->data[inventory->size], obatDikeluarkan);
    inventory->size++;  // Menambahkan ukuran inventory setelah obat disimpan

    // Menampilkan pesan bahwa obat telah dikeluarkan dan dikembalikan ke inventory
    printf("\nUwekkk!!! %s keluar dan kembali ke inventory\n", obatDikeluarkan);
}