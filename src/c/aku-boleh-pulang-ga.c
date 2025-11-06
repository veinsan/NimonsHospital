#include "aku-boleh-pulang-ga.h"

// Fungsi untuk menukar dua entri dalam daftar ObatPenyakit (digunakan untuk pengurutan)
static void swapObatPenyakitEntri(ObatPenyakit *a, ObatPenyakit *b) {
    ObatPenyakit temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi untuk menampilkan sisa nyawa ("nyawa") pasien
void sisanyawanimon(int nyawaDiberikan) {
    printf("Sisa nyawa Anda: ");
    // Menampilkan "O" untuk nyawa yang tersisa, dan "X" untuk nyawa yang habis
    for (int k = 0; k < 3; k++) {
        printf("%s", (k < nyawaDiberikan) ? ANSI_BOLD ANSI_COLOR_YELLOW "[O]" ANSI_RESET : ANSI_BOLD "[X]" ANSI_RESET); 
    }
    printf(" (%d nyawa)\n", nyawaDiberikan);
}

// Fungsi untuk memproses status pasien (apakah selesai atau "ded" [mati])
static void prosesPasienSelesaiAtauDed(
    const char* usernamePasien,
    User* dataPasienDiCurrentUser,      
    boolean apakahPasienDed,            
    User pasienListGlobal[],            
    int* jumlahPasienGlobalPtr,         
    Set* usernameSetGlobal,             
    StackObat* perutUntukDikosongkan,
    ListObat* inventoryUntukDikosongkan) {

    // Menghapus pasien dari antrian dokter jika ada
    for (int i = 0; i < jumlahDokter; i++) { 
        AntrianDokter* q = &dokterQueues[i];
        if (q->head == NULL || q->dokter == NULL) continue; 

        AntrianNode* current = q->head;
        AntrianNode* prev = NULL;
        while (current != NULL) {
            if (strcmp(current->pasien_data.username, usernamePasien) == 0) {
                // Jika ditemukan, hapus dari antrian dan bebasakan memori
                if (prev == NULL) { q->head = current->next; } 
                else { prev->next = current->next; }
                if (q->tail == current) { q->tail = prev; }
                
                AntrianNode* tempNode = current;
                current = current->next; 
                free(tempNode); 
                q->jumlah_antrian--;
                break; 
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Jika pasien "ded", hapus data pasien dari sistem
    if (apakahPasienDed) {
        int idxPasienDihapus = -1;
        // Cari indeks pasien dalam daftar global
        for (int i = 0; i < *jumlahPasienGlobalPtr; i++) {
            if (strcmp(pasienListGlobal[i].username, usernamePasien) == 0) {
                idxPasienDihapus = i;
                break;
            }
        }
        // Hapus pasien dari daftar global jika ditemukan
        if (idxPasienDihapus != -1) {
            for (int i = idxPasienDihapus; i < (*jumlahPasienGlobalPtr) - 1; i++) {
                pasienListGlobal[i] = pasienListGlobal[i+1];
            }
            (*jumlahPasienGlobalPtr)--; 
            hapusSet(usernameSetGlobal, usernamePasien); 
            printf("Informasi pasien %s telah dihapus permanen dari sistem.\n", usernamePasien);
        }
        // Hapus data pasien jika pasien yang sedang login adalah yang sama
        if (dataPasienDiCurrentUser != NULL && strcmp(dataPasienDiCurrentUser->username, usernamePasien) == 0) {
            dataPasienDiCurrentUser->username[0] = '\0';
            dataPasienDiCurrentUser->password[0] = '\0'; 
            dataPasienDiCurrentUser->role[0] = '\0';
            dataPasienDiCurrentUser->nyawa = 0;
            dataPasienDiCurrentUser->namaPenyakit[0] = '\0';
            dataPasienDiCurrentUser->dokterPerawat[0] = '\0';
        }
    } else { 
        // Jika bukan "ded", hapus penyakit dan dokter dari data pasien
        if (dataPasienDiCurrentUser != NULL && strcmp(dataPasienDiCurrentUser->username, usernamePasien) == 0) {
            dataPasienDiCurrentUser->namaPenyakit[0] = '\0';
            dataPasienDiCurrentUser->dokterPerawat[0] = '\0'; 
        }
    }

    // Reset perut (stack) dan inventory jika diperlukan
    if (perutUntukDikosongkan != NULL) perutUntukDikosongkan->top = -1; 
    if (inventoryUntukDikosongkan != NULL) inventoryUntukDikosongkan->size = 0; 
}

// Fungsi untuk memeriksa status pasien sebelum membolehkan mereka pulang (untuk "pulang")
void akubolehpulanggaDok(
    User* userLoggedInInstance, StackObat* perutPasien, ListObat* inventoryPasien,
    User pasienListGlobal[], int* jumlahPasienGlobalPtr, Set* usernameSetGlobal,
    int* statusLoginGlobalPtr, User dokterListGlobal[], int dokterCountGlobal) {

    // Memastikan hanya pasien yang sudah login yang dapat mengakses fungsi ini
    if (!(*statusLoginGlobalPtr) || strcmp(userLoggedInInstance->role, "Pasien") != 0) {
        printf("Perintah ini hanya dapat diakses oleh Pasien yang sudah login.\n");
        return;
    }

    // Memastikan pasien sudah didiagnosis
    if (userLoggedInInstance == NULL || strlen(userLoggedInInstance->namaPenyakit) == 0) {
        printf("\nKamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    printf("\nDokter sedang memeriksa keadaanmu...\n");

    // Jika pasien memiliki obat yang belum diminum, minta mereka untuk meminumnya terlebih dahulu
    if (inventoryPasien->size > 0) {
        printf("\nMasih ada obat di inventory (%d obat) yang belum kamu habiskan, minum semuanya dulu yukk!\n", inventoryPasien->size);
        return;
    }

    // Mencari ID penyakit pasien berdasarkan diagnosis
    int idPenyakitPasien = -1;
    for (int i = 0; i < jumlahPenyakit; i++) { 
        if (strcmp(userLoggedInInstance->namaPenyakit, penyakitList[i].namaPenyakit) == 0) {
            idPenyakitPasien = penyakitList[i].idPenyakit;
            break;
        }
    }

    if (idPenyakitPasien == -1) {
        printf("\nPenyakit '%s' yang terdiagnosis tidak dikenali dalam sistem resep. Hubungi admin.\n", userLoggedInInstance->namaPenyakit);
        return;
    }

    // Membuat daftar resep obat untuk pasien berdasarkan penyakit yang terdiagnosis
    ObatPenyakit resepMentahDinamis[MAX_OBAT]; 
    int countResepMentah = 0;
    for (int i = 0; i < jumlahObatPenyakit; i++) { 
        if (obatPenyakitList[i].idPenyakit == idPenyakitPasien) {
            if (countResepMentah < MAX_OBAT) { 
                resepMentahDinamis[countResepMentah++] = obatPenyakitList[i];
            } else {
                break; 
            }
        }
    }
    
    // Jika tidak ada obat yang diperlukan dan perut kosong, biarkan pasien pulang
    if (countResepMentah == 0 && perutPasien->top == -1) {
         printf("\nSelamat! Kamu tidak memerlukan pengobatan khusus untuk '%s' atau sudah sembuh. Silahkan pulang dan jaga kesehatan!\n", userLoggedInInstance->namaPenyakit);
         prosesPasienSelesaiAtauDed(userLoggedInInstance->username, userLoggedInInstance, FALSE, pasienListGlobal, jumlahPasienGlobalPtr, usernameSetGlobal, perutPasien, inventoryPasien);
         
         if (strlen(userLoggedInInstance->dokterPerawat) > 0) {
            for (int i = 0; i < dokterCountGlobal; i++) {
                if (strcmp(dokterListGlobal[i].username, userLoggedInInstance->dokterPerawat) == 0) {
                    dokterListGlobal[i].aura++;
                    printf("Dokter %s mendapatkan +1 Aura! (Total: %d)\n", dokterListGlobal[i].username, dokterListGlobal[i].aura);
                    break;
                }
            }
         }
         return;
    }
    
    // Urutkan resep (daftar obat) berdasarkan urutan minum yang diinginkan
    for (int i = 0; i < countResepMentah - 1; i++) {
        for (int j = 0; j < countResepMentah - i - 1; j++) {
            if (resepMentahDinamis[j].urutanMinum > resepMentahDinamis[j + 1].urutanMinum) {
                swapObatPenyakitEntri(&resepMentahDinamis[j], &resepMentahDinamis[j + 1]);
            }
        }
    }

    // Menyusun nama obat yang benar berdasarkan daftar resep
    char resepBenar_NamaObat[MAX_OBAT][MAX_NAMA_OBAT_LEN];
    int jumlahObatDiResepBenar = countResepMentah;
    for (int i = 0; i < jumlahObatDiResepBenar; i++) {
        int idObatCari = resepMentahDinamis[i].idObat;
        int ketemuObatDiList = 0;
        for (int k = 0; k < jumlahObat; k++) { 
            if (obatList[k].idObat == idObatCari) {
                strncpy(resepBenar_NamaObat[i], obatList[k].namaObat, MAX_NAMA_OBAT_LEN - 1);
                resepBenar_NamaObat[i][MAX_NAMA_OBAT_LEN - 1] = '\0';
                ketemuObatDiList = 1;
                break;
            }
        }
        if (!ketemuObatDiList) strcpy(resepBenar_NamaObat[i], "ObatTidakDikenal"); 
    }

    // Bandingkan obat yang diminum pasien dengan resep yang seharusnya
    int jumlahObatYangDiminum = perutPasien->top + 1;
    boolean apakahSalahMinum = FALSE;

    if (jumlahObatYangDiminum != jumlahObatDiResepBenar) {
        apakahSalahMinum = TRUE;
        if (jumlahObatDiResepBenar == 0 && jumlahObatYangDiminum > 0) {
            printf("Kamu seharusnya tidak minum obat apapun untuk penyakit ini!\n");
        }
    } else if (jumlahObatDiResepBenar == 0 && jumlahObatYangDiminum == 0) {
        apakahSalahMinum = FALSE; 
    }
    else {
        for (int i = 0; i < jumlahObatDiResepBenar; i++) {
            if (strcmp(perutPasien->data[i], resepBenar_NamaObat[i]) != 0) {
                apakahSalahMinum = TRUE;
                break;
            }
        }
    }

    // Tangani jika pasien salah minum obat
    if (apakahSalahMinum) {
        printf("\nMaaf, tapi kamu masih belum bisa pulang!\n");
        if (jumlahObatDiResepBenar > 0) {
            printf("Urutan peminuman obat yang diharapkan untuk %s:\n", userLoggedInInstance->namaPenyakit);
            for (int i = 0; i < jumlahObatDiResepBenar; i++) {
                printf("%s%s", resepBenar_NamaObat[i], (i == jumlahObatDiResepBenar - 1) ? "" : " -> ");
            }
            printf("\n");
        } else {
            printf("Seharusnya kamu tidak minum obat apapun.\n");
        }

        // Tampilkan urutan obat yang diminum pasien dan kurangi nyawa jika salah
        printf("\nUrutan obat yang kamu minum:\n");
        if (jumlahObatYangDiminum == 0) printf("(Perut kosong)\n");
        else {
            for (int i = 0; i < jumlahObatYangDiminum; i++) {
                printf("%s%s", perutPasien->data[i], (i == jumlahObatYangDiminum - 1) ? "" : " -> ");
            }
        }
        printf("\n\n");

        if (userLoggedInInstance->nyawa > 0) userLoggedInInstance->nyawa--; 
        for(int i=0; i < *jumlahPasienGlobalPtr; ++i){ 
            if(pasienListGlobal[i].id == userLoggedInInstance->id){
                pasienListGlobal[i].nyawa = userLoggedInInstance->nyawa;
                break;
            }
        }
        sisanyawanimon(userLoggedInInstance->nyawa);

        // Jika nyawa habis, tandai pasien sebagai "ded" (mati)
        if (userLoggedInInstance->nyawa <= 0) {
            printf("Kondisi pasien menjadi fatal, kamu dinyatakan \"ded\"!\n");
            prosesPasienSelesaiAtauDed(userLoggedInInstance->username, userLoggedInInstance, TRUE, pasienListGlobal, jumlahPasienGlobalPtr, usernameSetGlobal, perutPasien, inventoryPasien);
            *statusLoginGlobalPtr = 0; 
        } else {
            printf("Silahkan gunakan PENAWAR atau konsultasi lagi!\n");
        }
    } else {
        // Jika pasien sudah minum obat dengan benar, mereka dapat pulang
        printf("\nSelamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");
        
        // Tambah aura dokter jika pasien sembuh
        if (strlen(userLoggedInInstance->dokterPerawat) > 0) {
            for (int i = 0; i < dokterCountGlobal; i++) {
                if (strcmp(dokterListGlobal[i].username, userLoggedInInstance->dokterPerawat) == 0) {
                    dokterListGlobal[i].aura++;
                    printf("Dokter %s mendapatkan +1 Aura! (Total Aura: %d)\n", dokterListGlobal[i].username, dokterListGlobal[i].aura);
                    break;
                }
            }
        }
        
        // Proses penyelesaian pasien dan kembali ke menu utama
        prosesPasienSelesaiAtauDed(userLoggedInInstance->username, userLoggedInInstance, FALSE, pasienListGlobal, jumlahPasienGlobalPtr, usernameSetGlobal, perutPasien, inventoryPasien);
        printf("# Pasien %s kembali ke menu utama dan meninggalkan ruangan.\n", userLoggedInInstance->username);
    }
}