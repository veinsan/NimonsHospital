#include "exit.h"

// Fungsi untuk menampilkan tulisan "TERIMA"
void display_terima(void) {
    // Mengatur warna teks menggunakan ANSI_COLOR_LAVENDER
    printf(ANSI_COLOR_LAVENDER);
    // Menampilkan teks "TERIMA" dalam bentuk ASCII art
    printf("                                    ████████╗███████╗██████╗ ██╗███╗   ███╗ █████╗ \n");
    printf("                                    ╚══██╔══╝██╔════╝██╔══██╗██║████╗ ████║██╔══██╗\n");
    printf("                                       ██║   █████╗  ██████╔╝██║██╔████╔██║███████║\n");
    printf("                                       ██║   ██╔══╝  ██╔══██╗██║██║╚██╔╝██║██╔══██║\n");
    printf("                                       ██║   ███████╗██║  ██║██║██║ ╚═╝ ██║██║  ██║\n");
    printf("                                       ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝╚═╝     ╚═╝╚═╝  ╚═╝\n");
    printf(ANSI_RESET); // Mengembalikan warna ke default
    printf("\n");
}

// Fungsi untuk menampilkan tulisan "KASIH"
void display_kasih(void) {
    // Mengatur warna teks menggunakan ANSI_COLOR_LAVENDER
    printf(ANSI_COLOR_LAVENDER);
    // Menampilkan teks "KASIH" dalam bentuk ASCII art
    printf("                                          ██╗  ██╗ █████╗ ███████╗██╗██╗  ██╗\n");
    printf("                                          ██║ ██╔╝██╔══██╗██╔════╝██║██║  ██║\n");
    printf("                                          █████╔╝ ███████║███████╗██║███████║\n");
    printf("                                          ██╔═██╗ ██╔══██║╚════██║██║██╔══██║\n");
    printf("                                          ██║  ██╗██║  ██║███████║██║██║  ██║\n");
    printf("                                          ╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝╚═╝  ╚═╝\n");
    printf(ANSI_RESET); // Mengembalikan warna ke default
    printf("\n");
}

// Fungsi untuk menampilkan gambar hati (love)
void display_love(void) {
    // Mengatur warna teks menggunakan ANSI_COLOR_PINK
    printf(ANSI_COLOR_PINK);
    // Menampilkan gambar hati menggunakan karakter ASCII
    printf("                                                     ...      .....\n");
    printf("                                                  @.     @.  @.     .@\n");
    printf("                                                @         @ @         @\n");
    printf("                                               @           @           @\n");
    printf("                                               @                        @\n");
    printf("                                                @                      @\n");
    printf("                                                 @                    @\n");
    printf("                                                  @                  @\n");
    printf("                                                    @              @\n");
    printf("                                                      @          @\n");
    printf("                                                        @      @\n");
    printf("                                                          @  @\n");
    printf("                                                           @\n");
    printf(ANSI_RESET); // Mengembalikan warna ke default
    printf("\n");
}

// Fungsi untuk menampilkan tulisan "SAMPai JUMPA"
void display_sampai_jumpa(void) {
    // Mengatur warna teks menggunakan ANSI_COLOR_LAVENDER
    printf(ANSI_COLOR_LAVENDER);
    // Menampilkan teks "SAMPai JUMPA" dalam bentuk ASCII art
    printf("             ███████╗ █████╗ ███╗   ███╗██████╗  █████╗ ██╗         ██  ██    ██╗███╗   ███╗██████╗  █████╗ \n");
    printf("             ██╔════╝██╔══██╗████╗ ████║██╔══██╗██╔══██╗██║         ██║ ██║   ██║████╗ ████║██╔══██╗██╔══██╗\n");
    printf("             ███████╗███████║██╔████╔██║██████╔╝███████║██║         ██║ ██║   ██║██╔████╔██║██████╔╝███████║\n");
    printf("             ╚════██║██╔══██║██║╚██╔╝██║██╔═══╝ ██╔══██║██║   ██╗   ██║ ██║   ██║██║╚██╔╝██║██╔═══╝ ██╔══██║\n");
    printf("             ███████║██║  ██║██║ ╚═╝ ██║██║     ██║  ██║██║   ╚█████╔╝  ╚██████╔╝██║ ╚═╝ ██║██║     ██║  ██║\n");
    printf("             ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝╚═╝    ╚════╝   ╚═════╝  ╚═╝     ╚═╝╚═╝     ╚═╝  ╚═╝\n");
    printf(ANSI_RESET); // Mengembalikan warna ke default
}

// Fungsi untuk keluar dari program dengan menampilkan pesan-pesan tersebut
void exit_program(void) {
    display_terima(); // Menampilkan "TERIMA"
    display_kasih(); // Menampilkan "KASIH"
    display_love(); // Menampilkan gambar hati (love)
    display_sampai_jumpa(); // Menampilkan "SAMPai JUMPA"
    exit(0); // Keluar dari program
}