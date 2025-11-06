#include "cari-user.h"

static void clearInputBufferCariUser() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void printHeaderUserTable() {
    printf("ID   | Username   | Role     | Penyakit\n");
    printf("--------------------------------------------------\n");
}

static void printUserDetail(User user) {
    printf("%-4d | %-10s | %-8s | %s\n",
           user.id,
           user.username,
           user.role,
           (strcmp(user.role, "Pasien") == 0 && strlen(user.namaPenyakit) > 0) ? user.namaPenyakit : "-");
}

static void printHeaderDokterTable(){
    printf("\nID   | Username   | Aura\n");
    printf("--------------------------\n");
}

static void printDokterDetail(User dokter){
    printf("%-4d | %-10s | %d\n", dokter.id, dokter.username, dokter.aura);
}

static void printHeaderPasienTable() {
    printf("\nID   | Username   | Penyakit            | Nyawa | Dokter Perawat\n");
    printf("---------------------------------------------------------------------\n");
}

static void printPasienDetail(User pasien) {
    printf("%-4d | %-10s | %-19s | %-5d | %s\n",
           pasien.id, pasien.username,
           strlen(pasien.namaPenyakit) > 0 ? pasien.namaPenyakit : "-",
           pasien.nyawa,
           strlen(pasien.dokterPerawat) > 0 ? pasien.dokterPerawat : "-");
}

int binarySearchByID(User sortedList[], int size, int id) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sortedList[mid].id == id) return mid;
        if (sortedList[mid].id < id) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int sequentialSearchByName(User list[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].username, name) == 0) {
            return i;
        }
    }
    return -1;
}

void cariUser(User *managerData, User dokterListGlobal[], int dokterCountGlobal, User pasienListGlobal[], int pasienCountGlobal) {
    if (strcmp(currentUser.role, "Manager") != 0) {
        printf("Perintah CARI_USER hanya bisa digunakan oleh Manager.\n");
        return;
    }

    int pilihan;
    printf("Cari berdasarkan?\n1. ID\n2. Nama\n");
    printf(">>> Pilihan: ");
    if (scanf("%d", &pilihan) != 1) {
        printf("Input pilihan tidak valid. Masukkan angka (1 atau 2).\n");
        clearInputBufferCariUser(); 
        return;
    }
    clearInputBufferCariUser(); 

    int ditemukan = 0;
    char namaInput[MAX_USERNAME_LEN + 2];

    if (pilihan == 1) {
        int idInput;
        printf("\n>>> Masukkan nomor ID user: ");
        if (scanf("%d", &idInput) != 1) {
            printf("Input ID tidak valid. Masukkan angka.\n");
            clearInputBufferCariUser();
            return;
        }
        clearInputBufferCariUser();
        printf("\nMenampilkan pengguna dengan nomor ID %d...\n", idInput); 

        if (managerData->id == idInput) {
            printHeaderUserTable();
            printUserDetail(*managerData);
            ditemukan = 1;
        }

        if (!ditemukan) {
            int index = binarySearchByID(dokterListGlobal, dokterCountGlobal, idInput);
            if (index != -1) {
                printHeaderUserTable();
                printUserDetail(dokterListGlobal[index]);
                ditemukan = 1;
            }
        }

        if (!ditemukan && pasienCountGlobal > 0) {
            User tempPasienList[MAX_JUMLAH_USER]; 
            for(int i=0; i < pasienCountGlobal; i++) tempPasienList[i] = pasienListGlobal[i];
            sortUsers(tempPasienList, pasienCountGlobal, SORT_BY_ID, ASC); 
            
            int index = binarySearchByID(tempPasienList, pasienCountGlobal, idInput);
            if (index != -1) {
                printHeaderUserTable();
                printUserDetail(tempPasienList[index]); 
                ditemukan = 1;
            }
        }
    } else if (pilihan == 2) {
        printf("\n>>> Masukkan nama user: ");
        if (scanf("%19s", namaInput) != 1) { 
             printf("Input nama gagal.\n");
             clearInputBufferCariUser(); return;
        }
        if (strlen(namaInput) >= MAX_USERNAME_LEN) {
            printf("Nama user terlalu panjang! Maksimum %d karakter.\n", MAX_USERNAME_LEN - 1);
            clearInputBufferCariUser(); 
            return;
        }
        clearInputBufferCariUser();
        
        int userDitemukanDiCetak = 0; 
        if (strcmp(managerData->username, namaInput) == 0) {
            if(!userDitemukanDiCetak) {printf("\nMenampilkan pengguna dengan nama %s...\n", namaInput); printHeaderUserTable(); userDitemukanDiCetak = 1;}
            printUserDetail(*managerData);
            ditemukan = 1;
        }

        if (!ditemukan) { 
            int index = sequentialSearchByName(dokterListGlobal, dokterCountGlobal, namaInput);
            if (index != -1) {
                if(!userDitemukanDiCetak) {printf("\nMenampilkan pengguna dengan nama %s...\n", namaInput); printHeaderUserTable(); userDitemukanDiCetak = 1;}
                printUserDetail(dokterListGlobal[index]);
                ditemukan = 1;
            }
        }

        if (!ditemukan) {
            int index = sequentialSearchByName(pasienListGlobal, pasienCountGlobal, namaInput);
            if (index != -1) {
                if(!userDitemukanDiCetak) {printf("\nMenampilkan pengguna dengan nama %s...\n", namaInput); printHeaderUserTable(); userDitemukanDiCetak = 1;}
                printUserDetail(pasienListGlobal[index]);
                ditemukan = 1;
            }
        }
    } else {
        printf("Pilihan tidak valid!\n");
        return;
    }

    if (!ditemukan) {
        if (pilihan == 1) {
             printf("\nTidak ditemukan pengguna dengan ID tersebut.\n");
        } else if (pilihan == 2) {
             printf("\nTidak ditemukan pengguna dengan nama %s!\n", namaInput); 
        }
    }
}

void cariDokter(User dokterListGlobal[], int dokterCountGlobal){
    if (strcmp(currentUser.role, "Manager") != 0) {
        printf("Perintah CARI_DOKTER hanya untuk Manager.\n"); return;
    }
    if (dokterCountGlobal == 0) {
        printf("Belum ada dokter terdaftar.\n"); return;
    }
    int pilihan;
    char namaInput[MAX_USERNAME_LEN+2];

    printf("Cari dokter berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
    if (scanf("%d", &pilihan) != 1) { printf("Input pilihan tidak valid.\n"); clearInputBufferCariUser(); return; }
    clearInputBufferCariUser();

    int foundIndex = -1;
    if (pilihan == 1) {
        int idInput;
        printf("\n>>> Masukkan ID dokter: ");
        if (scanf("%d", &idInput) != 1) { printf("Input ID tidak valid.\n"); clearInputBufferCariUser(); return; }
        clearInputBufferCariUser();
        printf("\nMenampilkan dokter dengan ID %d...\n", idInput); 
        foundIndex = binarySearchByID(dokterListGlobal, dokterCountGlobal, idInput);
    } else if (pilihan == 2) {
        printf("\n>>> Masukkan nama dokter: ");
        if (scanf("%19s", namaInput) != 1) { printf("Input nama gagal.\n"); clearInputBufferCariUser(); return; }
        if (strlen(namaInput) >= MAX_USERNAME_LEN) { printf("Nama dokter terlalu panjang!\n"); clearInputBufferCariUser(); return; }
        clearInputBufferCariUser();
        printf("\nMenampilkan dokter dengan nama %s...\n", namaInput);
        foundIndex = sequentialSearchByName(dokterListGlobal, dokterCountGlobal, namaInput);
    } else {
        printf("Pilihan tidak valid!\n"); return;
    }

    if (foundIndex != -1) {
        printHeaderDokterTable(); printDokterDetail(dokterListGlobal[foundIndex]);
    } else {
        if (pilihan == 1) {
            printf("\nTidak ditemukan dokter dengan ID tersebut.\n");
        } else if (pilihan == 2) {
            printf("\nTidak ditemukan dokter dengan nama %s.\n", namaInput);
        }
    }
}

void cariPasien(User pasienListGlobal[], int pasienCountGlobal) {
    if (strcmp(currentUser.role, "Manager") != 0) {
        printf("Perintah CARI_PASIEN hanya untuk Manager.\n"); return;
    }
    if (pasienCountGlobal == 0) {
        printf("Belum ada pasien terdaftar.\n"); return;
    }
    
    int pilihan;
    char namaInput[MAX_USERNAME_LEN+2];
    char penyakitInput[MAX_NAMA_PENYAKIT_LEN + 2];

    printf("Cari pasien berdasarkan?\n1. ID\n2. Nama\n3. Penyakit\n>>> Pilihan: ");
    if (scanf("%d", &pilihan) != 1) { printf("Input pilihan tidak valid.\n"); clearInputBufferCariUser(); return; }
    clearInputBufferCariUser(); 
    
    int ditemukan = 0;
    if (pilihan == 1) {
        int idInput;
        printf("\n>>> Masukkan ID pasien: ");
        if (scanf("%d", &idInput) != 1) { printf("Input ID tidak valid.\n"); clearInputBufferCariUser(); return; }
        clearInputBufferCariUser();
        
        if (pasienCountGlobal > 0) {
            User tempPasienList[MAX_JUMLAH_USER];
            for(int i=0; i < pasienCountGlobal; i++) tempPasienList[i] = pasienListGlobal[i];
            sortUsers(tempPasienList, pasienCountGlobal, SORT_BY_ID, ASC);
            int index = binarySearchByID(tempPasienList, pasienCountGlobal, idInput);
            if (index != -1) {
                printf("\nMenampilkan pasien dengan ID %d...\n", idInput);
                printHeaderPasienTable(); printPasienDetail(tempPasienList[index]);
                ditemukan = 1;
            }
        }
    } else if (pilihan == 2) {
        printf("\n>>> Masukkan nama pasien: ");
        if (scanf("%19s", namaInput) != 1) { printf("Input nama gagal.\n"); clearInputBufferCariUser(); return; }
        if (strlen(namaInput) >= MAX_USERNAME_LEN) { printf("Nama pasien terlalu panjang!\n"); clearInputBufferCariUser(); return; }
        clearInputBufferCariUser();

        int index = sequentialSearchByName(pasienListGlobal, pasienCountGlobal, namaInput);
        if (index != -1) {
            printf("\nMenampilkan pasien dengan nama %s...\n", namaInput);
            printHeaderPasienTable(); printPasienDetail(pasienListGlobal[index]);
            ditemukan = 1;
        }
    } else if (pilihan == 3) {
        printf("\n>>> Masukkan nama penyakit: ");
        if (scanf(" %29[^\n]", penyakitInput) != 1) {
            printf("Input nama penyakit gagal.\n");
            clearInputBufferCariUser(); 
            return;
        }
        clearInputBufferCariUser(); 

        User hasilPencarian[MAX_JUMLAH_USER]; 
        int jumlahHasil = 0;
        for (int i = 0; i < pasienCountGlobal; i++) {
            if (strcmp(pasienListGlobal[i].namaPenyakit, penyakitInput) == 0) {
                if (jumlahHasil < MAX_JUMLAH_USER) { 
                    hasilPencarian[jumlahHasil++] = pasienListGlobal[i];
                } else {
                    break; 
                }
            }
        }

        if (jumlahHasil > 0) {
            ditemukan = 1;
            SortMethod method; SortOrder order; int methodInput, orderInput;
            printf("Urutkan berdasarkan?\n1. ID\n2. Nama\n>>> Pilihan: ");
            if (scanf("%d", &methodInput) != 1) { clearInputBufferCariUser(); return; }
            clearInputBufferCariUser();
            method = (methodInput == 2) ? SORT_BY_NAME : SORT_BY_ID;
            
            printf("\nUrutan sort %s?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>>> Pilihan: ", (method == SORT_BY_ID ? "ID" : "nama"));
            if (scanf("%d", &orderInput) != 1) { clearInputBufferCariUser(); return; }
            clearInputBufferCariUser();
            order = (orderInput == 2) ? DESC : ASC;
            
            sortUsers(hasilPencarian, jumlahHasil, method, order);
            
            printf("\nMenampilkan pasien dengan penyakit %s dengan %s terurut %s...\n",
                   penyakitInput,
                   (method == SORT_BY_ID ? "ID" : "nama"),
                   (order == ASC ? "ascending" : "descending"));

            printf("ID   | Nama       | Penyakit\n"); 
            printf("------------------------------\n");
            for (int i = 0; i < jumlahHasil; i++) {
                 printf("%-4d | %-10s | %s\n", 
                           hasilPencarian[i].id, 
                           hasilPencarian[i].username, 
                           hasilPencarian[i].namaPenyakit);
            }
        }
    } else {
        printf("Pilihan tidak valid!\n"); return;
    }

    if (!ditemukan) {
        if (pilihan == 1) {
            printf("\nTidak ditemukan pasien dengan ID tersebut.\n");
        } else if (pilihan == 2) {
            printf("\nTidak ditemukan pasien dengan nama %s.\n", namaInput);
        } else if (pilihan == 3) {
            printf("\nTidak ditemukan pasien dengan penyakit %s.\n", penyakitInput);
        }
    }
}