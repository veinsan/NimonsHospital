#include "aku-boleh-pulang-ga.h"
#include "antrian-saya.h"
#include "cari-user.h"
#include "daftar-checkup.h"
#include "data.h" 
#include "denah.h"
#include "diagnosis.h"
#include "dokter-management.h"
#include "exit.h"
#include "help.h"
#include "lihat-antrian.h"
#include "lihat-user.h"
#include "mainin-antrian.h" // Bonus B06
#include "minum-obat.h"
#include "ngobatin.h"
#include "set.h"
#include "user-management.h"

// Fungsi untuk membersihkan buffer input setelah scanf untuk menghindari karakter tersisa
static void clearInputBuffer() {
    int c;
    // Membaca dan mengabaikan karakter hingga menemui newline atau EOF
    while ((c = getchar()) != '\n' && c != EOF);
}
// --- Fungsi Inisialisasi Denah ---
void inisialisasiDenah(int *jumlahRuangHasil, int* barisHasil, int* kolomHasil, int argc, char *argv[]) {
    *barisHasil = 4; 
    *kolomHasil = 4; 

    if (argc > 2) { 
        int argBaris = atoi(argv[1]);
        int argKolom = atoi(argv[2]);
        if (argBaris > 0 && argKolom > 0 && argBaris <= MAX_BARIS && argKolom <= MAX_KOLOM) {
            *barisHasil = argBaris;
            *kolomHasil = argKolom;
        } else {
            printf("Dimensi denah dari argumen (%s x %s) tidak valid (max %dx%d). Menggunakan default %dx%d.\n",
                   argv[1], argv[2], MAX_BARIS, MAX_KOLOM, *barisHasil, *kolomHasil);
        }
    }

    *jumlahRuangHasil = (*barisHasil) * (*kolomHasil);
    ruanganList = (Ruangan*) malloc(sizeof(Ruangan) * (*jumlahRuangHasil));
    if (ruanganList == NULL) {
        printf("Gawat! Gagal alokasi memori untuk denah! Program berhenti.\n");
        exit(1); 
    }
    
    for (int i = 0; i < *jumlahRuangHasil; i++) {
        ruanganList[i].kapasitas = MAX_PASIEN_RUANGAN; 
        ruanganList[i].dokter[0] = '\0';
        ruanganList[i].jumlahPasien = 0;
        for (int j = 0; j < MAX_PASIEN_RUANGAN; j++) {
            ruanganList[i].pasien[j][0] = '\0';
        }
    }
}

// --- Fungsi untuk Enable ANSI Colors (Bonus Kreativitas) ---
void enable_ansi_colors(void) {
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
    }
    #endif
}

// --- Fungsi-fungsi display welcome message (ASCII Art - Bonus Kreativitas) ---
void display_welcome_title(void) {
    printf(ANSI_COLOR_YELLOW);
    printf("\n\n\n          ██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
    printf("          ██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
    printf("          ██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗  \n");
    printf("          ██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝  \n");
    printf("          ╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
    printf("           ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
    printf(ANSI_RESET);
    printf("\n");
}

void display_to_title(void) {
    printf(ANSI_COLOR_YELLOW);
    printf("                                ████████╗ ██████╗ \n");
    printf("                                ╚══██╔══╝██╔═══██╗\n");
    printf("                                   ██║   ██║   ██║\n");
    printf("                                   ██║   ██║   ██║\n");
    printf("                                   ██║   ╚██████╔╝\n");
    printf("                                   ╚═╝    ╚═════╝ \n");
    printf(ANSI_RESET);
    printf("\n");
}

void display_rs_nimons_title(void) {
    printf(ANSI_COLOR_BLUE);
    printf("        ██████╗ ███████╗  ███╗   ██╗██╗███╗   ███╗ ██████╗ ███╗   ██╗███████╗\n");
    printf("        ██╔══██╗██╔════╝  ████╗  ██║██║████╗ ████║██╔═══██╗████╗  ██║██╔════╝\n");
    printf("        ██████╔╝███████╗  ██╔██╗ ██║██║██╔████╔██║██║   ██║██╔██╗ ██║███████╗\n");
    printf("        ██╔══██╗╚════██║  ██║╚██╗██║██║██║╚██╔╝██║██║   ██║██║╚██╗██║╚════██║\n");
    printf("        ██║  ██║███████║  ██║ ╚████║██║██║ ╚═╝ ██║╚██████╔╝██║ ╚████║███████║\n");
    printf("        ╚═╝  ╚═╝╚══════╝  ╚═╝  ╚═══╝╚═╝╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝\n");
    printf(ANSI_RESET);
    printf("\n");
    };

void display_menu_login(void) {
    printf("                     ╔════════════════════════════════════════════╗\n");
    printf("                     ║                    MENU                    ║\n");
    printf("                     ╠════════════════════════════════════════════╣\n");
    printf("                     ║                   %sLOGIN%s                    ║\n", ANSI_BOLD, ANSI_RESET);
    printf("                     ║                  %sREGISTER%s                  ║\n", ANSI_BOLD, ANSI_RESET);
    printf("                     ╚════════════════════════════════════════════╝\n");
}

// --- Fungsi Helper untuk Dequeue Pasien ---
static AntrianNode* dequeuePasien(AntrianDokter *queue) {
    if (queue == NULL || queue->head == NULL) {
        return NULL; 
    }
    AntrianNode *nodeDihapus = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL) {
        queue->tail = NULL; 
    }
    queue->jumlah_antrian--;
    nodeDihapus->next = NULL; 
    return nodeDihapus; 
}

// =================== FUNGSI UTAMA ===================
int main(int argc, char *argv[]) {
    display_welcome_title();
    display_to_title();
    display_rs_nimons_title();
    
    int currentDokterCount = jumlahDokter; // Dari data.c (via extern di data.h)
    int currentPasienCount = jumlahPasien; // Dari data.c (via extern di data.h)
    
    int jumlahRuangTotalMain; 
    int denahBarisMain, denahKolomMain;

    inisialisasiDenah(&jumlahRuangTotalMain, &denahBarisMain, &denahKolomMain, argc, argv);
    printf("RS NIMONS beroperasi dengan denah %d x %d.\n", denahBarisMain, denahKolomMain);

    buatSet(&usernameSet); // usernameSet global
    insertSet(&usernameSet, manager.username); 
    for (int i = 0; i < currentDokterCount; i++) insertSet(&usernameSet, dokterList[i].username); 
    for (int i = 0; i < currentPasienCount; i++) insertSet(&usernameSet, pasienList[i].username); 
    
    initializeDokterQueues(dokterList, currentDokterCount); // dokterQueues global

    StackObat perutPasien;    
    ListObat inventoryPasien; 
    buatStackObat(&perutPasien);     
    buatListObat(&inventoryPasien);  
    
    display_menu_login(); 

    char command[50];
    char arg1[MAX_USERNAME_LEN]; // Buffer untuk argumen tambahan

    printf("\nMasukkan perintah:\n");

    while (1) {
        printf("\n>>> ");
        if (scanf(" %49[^\n]", command) != 1) { // Max 49 char + null, spasi di depan skip whitespace
            int c_clear; while ((c_clear = getchar()) != '\n' && c_clear != EOF);
            if (c_clear == EOF) {printf("Mencapai akhir input. Keluar...\n"); break;}
            printf("Perintah tidak valid atau terlalu panjang. Ketik HELP.\n");
            continue;
        }
        int c_clear; while ((c_clear = getchar()) != '\n' && c_clear != EOF); // Clear sisa newline

        // --- Proses Dispatch Command ---
        if (strcmp(command, "LOGIN") == 0) {
            login(&manager, dokterList, currentDokterCount, pasienList, currentPasienCount);
        } 
        else if (strcmp(command, "REGISTER") == 0) {
            registerPasien(pasienList, &currentPasienCount, &usernameSet);
        } 
        else if (strcmp(command, "LOGOUT") == 0) {
            logout();
        } 
        else if (strcmp(command, "LUPA_PASSWORD") == 0) {
            lupaPassword(&manager, dokterList, currentDokterCount, pasienList, currentPasienCount);
        } 
        else if (strcmp(command, "HELP") == 0) {
            help();
        } 
        else if (strcmp(command, "LIHAT_USER") == 0){
            lihatsemuaUser(manager, dokterList, currentDokterCount, pasienList, currentPasienCount);
        }
        else if (strcmp(command, "LIHAT_PASIEN") == 0){
            lihatPasien(pasienList, currentPasienCount);
        }
        else if (strcmp(command, "LIHAT_DOKTER") == 0){
            lihatDokter(dokterList, currentDokterCount);
        }
        else if (strcmp(command, "CARI_USER") == 0){
            cariUser(&manager, dokterList, currentDokterCount, pasienList, currentPasienCount);
        }
        else if (strcmp(command, "CARI_DOKTER") == 0){
            cariDokter(dokterList, currentDokterCount);
        }
        else if (strcmp(command, "CARI_PASIEN") == 0){
            cariPasien(pasienList, currentPasienCount); 
        }
        else if (strcmp(command, "TAMBAH_DOKTER") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Manager") == 0) {
                int dokterCountSebelum = currentDokterCount;
                tambahDokter(dokterList, &currentDokterCount, &usernameSet); 
                if (currentDokterCount > dokterCountSebelum && (currentDokterCount - 1) < MAX_JUMLAH_USER) {
                    int newDokterIndex = currentDokterCount - 1; 
                    if (dokterQueues[newDokterIndex].dokter == NULL) { // Hanya inisialisasi jika belum ada dokter di slot itu
                        dokterQueues[newDokterIndex].dokter = &dokterList[newDokterIndex];
                        dokterQueues[newDokterIndex].head = NULL;
                        dokterQueues[newDokterIndex].tail = NULL;
                        dokterQueues[newDokterIndex].jumlah_antrian = 0;
                        // printf("Antrian untuk Dokter %s telah diinisialisasi.\n", dokterList[newDokterIndex].username); // Opsional
                    }
                }
            } else {
                printf("Perintah ini hanya untuk Manager.\n");
            }
        } 
        else if (strcmp(command, "ASSIGN_DOKTER") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Manager") == 0) {
                assignRuangan(dokterList, currentDokterCount, ruanganList, jumlahRuangTotalMain, denahBarisMain, denahKolomMain);
            } else {
                printf("Perintah ini hanya untuk Manager.\n");
            }
        }
        else if (strcmp(command, "LIHAT_ANTRIAN") == 0) { 
             if (isLoggedIn && strcmp(currentUser.role, "Manager") == 0) {
                lihatantrian(ruanganList, jumlahRuangTotalMain, denahBarisMain, denahKolomMain, currentDokterCount);
             } else {
                printf("Perintah ini hanya untuk Manager.\n");
             }
        }
        else if (strcmp(command, "DIAGNOSIS") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Dokter") == 0){
                AntrianDokter* antrianDrIni = NULL;
                for (int i = 0; i < currentDokterCount; i++){ 
                    if (dokterQueues[i].dokter != NULL && strcmp(dokterQueues[i].dokter->username, currentUser.username) == 0) {
                        antrianDrIni = &dokterQueues[i];
                        break;
                    }
                }
                if (antrianDrIni != NULL && antrianDrIni->head != NULL){
                    AntrianNode* pasienNodeSaatIni = antrianDrIni->head;
                    if (strlen(pasienNodeSaatIni->dokterdiagnosasesi) > 0 &&
                        strcmp(pasienNodeSaatIni->dokterdiagnosasesi, currentUser.username) == 0) {
                        printf("Anda sudah mendiagnosis pasien %s pada sesi ini.\nPenyakit: %s\nSilakan lakukan NGOBATIN jika perlu.\n",
                               pasienNodeSaatIni->pasien_data.username,
                               strlen(pasienNodeSaatIni->pasien_data.namaPenyakit) > 0 ? pasienNodeSaatIni->pasien_data.namaPenyakit : "Belum terdiagnosis jelas / Tidak ada");
                    } else {
                        diagnosisPasien(&pasienNodeSaatIni->pasien_data); 
                        strcpy(pasienNodeSaatIni->dokterdiagnosasesi, currentUser.username);
                        if (strlen(pasienNodeSaatIni->pasien_data.namaPenyakit) == 0) {
                            AntrianNode* nodedihapus = antrianDrIni->head; 
                            antrianDrIni->head = antrianDrIni->head->next; 
                            if (antrianDrIni->head == NULL) { 
                                antrianDrIni->tail = NULL;    
                            }
                            antrianDrIni->jumlah_antrian--;   
                            free(nodedihapus); 
                        }
                    }
                } else {
                    printf("Tidak ada pasien untuk diperiksa!\n");
                }
            } else {
                printf("Perintah ini hanya untuk Dokter.\n");
            }
        } 
        else if (strcmp(command, "NGOBATIN") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Dokter") == 0) {
                AntrianDokter* antrianDrIni = NULL;
                for (int i = 0; i < currentDokterCount; i++){
                    if (dokterQueues[i].dokter != NULL && strcmp(dokterQueues[i].dokter->username, currentUser.username) == 0){
                        antrianDrIni = &dokterQueues[i];
                        break;
                    }
                }
                if (antrianDrIni != NULL && antrianDrIni->head != NULL){
                    ngobatinPasien(&(antrianDrIni->head->pasien_data)); 
                    printf("Pasien %s selesai diberi resep obat.\n", antrianDrIni->head->pasien_data.username);
                    AntrianNode *pasienSelesaiNode = dequeuePasien(antrianDrIni);
                    if (pasienSelesaiNode != NULL) {
                        free(pasienSelesaiNode);
                    }
                } else {
                    printf("Tidak ada pasien untuk diobati!\n");
                }
            } else {
                printf("Perintah ini hanya untuk Dokter.\n");
            }
        } 
        else if (strcmp(command, "TAMBAH_OBAT") == 0) { // Command untuk menambah obat ke inventory
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                char namaObat[MAX_NAMA_OBAT_LEN];
                printf("Masukkan nama obat yang ingin ditambahkan: ");
                if (scanf("%s", namaObat) == 1) {
                    tambahObat(&inventoryPasien, namaObat);  // Menambah obat ke inventory
                } else {
                    printf("Input obat gagal.\n");
                }
                clearInputBuffer(); // Pastikan buffer dibersihkan
            } else {
                printf("Perintah ini hanya untuk Pasien yang sudah login.\n");
            }
        } 
        else if (strcmp(command, "LIHAT_OBAT") == 0) { // Command untuk melihat inventory obat
            tampilkanListObat(inventoryPasien); // Menampilkan daftar obat dalam inventory
        }
        else if (strcmp(command, "MINUM_OBAT") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                minumObat(&currentUser, &perutPasien, &inventoryPasien);
            } else {
                printf("Perintah ini hanya untuk Pasien.\n");
            }
        } 
        else if (strcmp(command, "PENAWAR") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                minumPenawar(&perutPasien, &inventoryPasien);
                sisanyawanimon(currentUser.nyawa); 
            } else {
                printf("Perintah ini hanya untuk Pasien.\n");
            }
        } 
        else if (strcmp(command, "PULANGDOK") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                akubolehpulanggaDok(&currentUser, &perutPasien, &inventoryPasien, pasienList, &currentPasienCount, &usernameSet, &isLoggedIn, dokterList, currentDokterCount);
            } else {
                 printf("Perintah ini hanya untuk Pasien.\n");
            }
        }
        else if (strcmp(command, "DAFTAR_CHECKUP") == 0) {
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                // Panggil dengan dokterList, currentDokterCount (dari main), 
                // pasienList (global), dan currentPasienCount (dari main)
                daftarCheckUp(dokterList, currentDokterCount, pasienList, currentPasienCount);
            } else {
                printf("Perintah ini hanya untuk Pasien.\n");
            }
        }
        else if (strcmp(command, "ANTRIAN") == 0) { 
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                antrianSaya(currentDokterCount); 
            } else {
                printf("Perintah ini hanya untuk Pasien.\n");
            }
        }
        else if (strcmp(command, "LIHAT_DENAH") == 0) {
            if (isLoggedIn) { // Sesuai spek S01 (STI), bisa diakses Manager, Dokter, Pasien
                lihatDenah(jumlahRuangTotalMain, denahBarisMain, denahKolomMain); }
            else {
                printf("Anda harus login untuk melihat denah.\n");
            }
        } 
        else if (strncmp(command, "LIHAT_RUANGAN ", 14) == 0) { 
            if (isLoggedIn) {
                char kodeRuang[4]; 
                if (sscanf(command + 14, " %3s", kodeRuang) == 1) { 
                    // Validasi format kodeRuang (misal A1, C5, bukan A12 atau X1)
                    if ((kodeRuang[0] >= 'A' && kodeRuang[0] < 'A' + denahBarisMain) &&
                        (kodeRuang[1] >= '1' && kodeRuang[1] < '1' + denahKolomMain) &&
                        kodeRuang[2] == '\0') { 

                        int barisIdx = kodeRuang[0] - 'A';
                        int kolomIdx = kodeRuang[1] - '1'; // Konversi '1' jadi 0, '2' jadi 1, dst.
                        int indexRuangan = barisIdx * denahKolomMain + kolomIdx;

                        if (indexRuangan >= 0 && indexRuangan < jumlahRuangTotalMain) {
                            lihatRuangan(indexRuangan, ruanganList, denahKolomMain);
                        } else {
                            printf("Kode ruangan tidak valid (di luar batas indeks)!\n");
                        }
                    } else {
                        printf("Format kode ruangan salah atau di luar batas denah! (Contoh: A1, B%d, dll.)\n", denahKolomMain);
                    }
                } 
            } else {
                printf("Harus login untuk melihat ruangan!\n");
            }
        }
        else if (strncmp(command, "UBAH_DENAH ", 11) == 0) { 
            if (isLoggedIn && strcmp(currentUser.role, "Manager") == 0) {
                int br, kl;
                if (sscanf(command + 11, "%d %d", &br, &kl) == 2) { 
                    // PERBAIKAN CARA PANGGIL:
                    // Parameter pertama: alamat jumlahRuangTotalMain
                    // Parameter kedua: alamat dari pointer ruanganList (GLOBAL)
                    // Parameter ketiga & keempat: barisBaru (br) & kolomBaru (kl) dari input
                    // Parameter kelima & keenam: alamat denahBarisMain & denahKolomMain
                    if (ubahDenah(&jumlahRuangTotalMain, &ruanganList, br, kl, &denahBarisMain, &denahKolomMain)) {
                        // Tidak perlu printf sukses lagi di sini, karena sudah ada di dalam ubahDenah
                    } else {
                        // ubahDenah sudah nge-print pesan errornya sendiri
                    }
                } else {
                    printf("Format command salah. Contoh: UBAH_DENAH <baris> <kolom>\n");
                }
            } else {
                printf("Perintah UBAH_DENAH hanya untuk Manager.\n");
            }
        }
        else if (strncmp(command, "PINDAH_DOKTER ", 14) == 0) { // Perhatikan spasi
            if (isLoggedIn && strcmp(currentUser.role, "Manager") == 0) {
                char asal[4], tujuan[4];
                // Ambil argumen dari sisa command string
                // Format: PINDAH_DOKTER <asal> <tujuan> (misal: PINDAH_DOKTER A1 C3)
                if (sscanf(command + 14, "%3s %3s", asal, tujuan) == 2) { // command + 14 untuk skip "PINDAH_DOKTER "
                                                                         // %3s untuk baca kode ruangan (misal A1, B2)
                    pindahDokter(asal, tujuan, ruanganList, denahBarisMain, denahKolomMain);} 
                else {
                    printf("Format command salah. Contoh: PINDAH_DOKTER <asal> <tujuan>\n");
                }
            } else {
                printf("Perintah PINDAH_DOKTER hanya untuk Manager.\n");
            }
        }
        else if (strcmp(command, "SKIP_ANTRIAN") == 0) { // Bonus B06
            if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                printf("Masukkan nama dokter yang antriannya ingin Anda skip: ");
                // MAX_USERNAME_LEN-1 karena arg1 adalah char[MAX_USERNAME_LEN]
                if (scanf("%19s", arg1) == 1) { 
                    skipAntrian(arg1); 
                    int c_skp; while ((c_skp = getchar()) != '\n' && c_skp != EOF); 
                } else {
                     printf("Input nama dokter gagal.\n");
                     int c_skp; while ((c_skp = getchar()) != '\n' && c_skp != EOF);
                }
            } else {
                printf("Perintah ini khusus untuk Pasien yang sudah login.\n");
            }
        }
        else if (strcmp(command, "CANCEL_ANTRIAN") == 0) { // Bonus B06
             if (isLoggedIn && strcmp(currentUser.role, "Pasien") == 0) {
                printf("Masukkan nama dokter yang antriannya ingin Anda batalkan: ");
                if (scanf("%19s", arg1) == 1) {
                    cancelAntrian(arg1);
                    int c_cnl; while ((c_cnl = getchar()) != '\n' && c_cnl != EOF);
                } else {
                    printf("Input nama dokter gagal.\n");
                    int c_cnl; while ((c_cnl = getchar()) != '\n' && c_cnl != EOF);
                }
            } else {
                printf("Perintah ini khusus untuk Pasien yang sudah login.\n");
            }
        }
        else if (strcmp(command, "EXIT") == 0) {
            exit_program(); // exit_program akan memanggil exit(0)
            break; 
        } 
        else {
            printf("Command '%s' tidak dikenal. Ketik HELP untuk bantuan.\n", command);
        }
    }
    
    if (ruanganList != NULL) {
        free(ruanganList); 
        ruanganList = NULL;
    }

    return 0;
}