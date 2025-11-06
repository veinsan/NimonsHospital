#include "lihat-user.h" 

// Fungsi untuk memeriksa apakah pengguna yang sedang login adalah Manager
static boolean isCurrentUserAManager() { 
    return isLoggedIn && strcmp(currentUser.role, "Manager") == 0; // Memeriksa jika role pengguna adalah "Manager"
}

// Fungsi untuk menukar posisi dua pengguna dalam array
void swapUsers(User *a, User *b) {
    User temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi untuk mengurutkan array pengguna berdasarkan kriteria tertentu dan urutan tertentu
void sortUsers(User arr[], int n, SortMethod method, SortOrder order) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            boolean harusSwap = FALSE;

            // Menentukan kondisi swap berdasarkan metode dan urutan yang dipilih
            if (order == ASC) {
                if (method == SORT_BY_ID) {
                    if (arr[j].id > arr[j+1].id) harusSwap = TRUE;
                } else if (method == SORT_BY_NAME) {
                    if (strcasecmp(arr[j].username, arr[j+1].username) > 0) harusSwap = TRUE;
                } else if (method == SORT_BY_AURA) {
                    if (arr[j].aura > arr[j+1].aura) harusSwap = TRUE;
                }
            } else {
                if (method == SORT_BY_ID) {
                    if (arr[j].id < arr[j+1].id) harusSwap = TRUE;
                } else if (method == SORT_BY_NAME) {
                    if (strcasecmp(arr[j].username, arr[j+1].username) < 0) harusSwap = TRUE;
                } else if (method == SORT_BY_AURA) {
                    if (arr[j].aura < arr[j+1].aura) harusSwap = TRUE;
                }
            }

            // Jika kondisi swap terpenuhi, tukar posisi dua pengguna
            if (harusSwap) {
                swapUsers(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Fungsi untuk meminta kriteria pengurutan dari pengguna
static boolean mintaKriteriaSort(SortMethod *method, SortOrder *order, boolean bisaSortByAura) {
    int methodInput, orderInput;
    *method = 0;

    // Menanyakan berdasarkan apa urutkan pengguna
    printf("Urutkan berdasarkan?\n1. ID\n2. Nama\n");
    if (bisaSortByAura) {
        printf("3. Aura\n"); // Jika bisa urutkan berdasarkan aura, tampilkan pilihan ke-3
    }
    printf(">>> Pilihan: ");
    
    if (scanf("%d", &methodInput) != 1 || (methodInput < 1 || (bisaSortByAura && methodInput > 2))) {
        printf("Pilihan invalid!\n");
        return FALSE;  // Menandakan input tidak valid
    }

    // Menetapkan metode pengurutan berdasarkan input
    if (methodInput == 2) {
        *method = SORT_BY_NAME;
    } else {
        *method = SORT_BY_ID;
    }

    // Menanyakan urutan pengurutan
    printf("\nUrutan sort?\n1. ASC (A-Z / Terkecil)\n2. DESC (Z-A / Terbesar)\n>>> Pilihan: ");
    
    if (scanf("%d", &orderInput) != 1 || (orderInput != 1 && orderInput != 2)) {
        printf("Pilihan invalid!\n");
        return FALSE;  // Menandakan input tidak valid
    }

    *order = (orderInput == 2) ? DESC : ASC; // Menentukan urutan pengurutan (ASC atau DESC)
    return TRUE;  // Menandakan input valid
}

// Fungsi untuk menampilkan semua pengguna (Manager, Dokter, Pasien)
void lihatsemuaUser(User managerData, User dokterListGlobal[], int dokterCountGlobal, User pasienListGlobal[], int pasienCountGlobal) {
    // Memastikan hanya Manager yang bisa mengakses fitur ini
    if (!isCurrentUserAManager()) {
        printf("Fitur ini hanya untuk Manager.\n");
        return;
    }

    SortMethod method;
    SortOrder order;

    // Meminta kriteria untuk mengurutkan data pengguna
    if (!mintaKriteriaSort(&method, &order, FALSE)) {
        return;  // Jika input tidak valid, keluar dari fungsi
    }

    // Menghitung total jumlah pengguna (Manager, Dokter, dan Pasien)
    int totalUser = 1 + dokterCountGlobal + pasienCountGlobal;

    // Memeriksa apakah jumlah pengguna melebihi kapasitas yang tersedia
    if (totalUser > MAX_JUMLAH_USER) {
        printf("Jumlah pengguna (%d) melebihi kapasitas array sementara (%d).\n", totalUser, MAX_JUMLAH_USER);
        return;
    }

    User semuaUserListTemp[MAX_JUMLAH_USER];

    semuaUserListTemp[0] = managerData;
    // Menyalin data dokter dan pasien ke dalam array sementara
    for (int i = 0; i < dokterCountGlobal; i++) {
        semuaUserListTemp[i + 1] = dokterListGlobal[i];
    }
    for (int i = 0; i < pasienCountGlobal; i++) {
        semuaUserListTemp[i + 1 + dokterCountGlobal] = pasienListGlobal[i];
    }

    // Mengurutkan pengguna berdasarkan kriteria yang telah ditentukan
    sortUsers(semuaUserListTemp, totalUser, method, order);

    // Menampilkan daftar pengguna yang telah diurutkan
    printf("\nMenampilkan semua pengguna dengan %s terurut %s...\n",
           (method == SORT_BY_NAME ? "nama" : "ID"),
           (order == DESC ? "descending" : "ascending"));

    // Menampilkan header tabel
    printf("ID   | Nama       | Role     | Penyakit\n");
    printf("---------------------------------------------\n");

    // Menampilkan data setiap pengguna
    for (int i = 0; i < totalUser; i++) {
        printf("%-4d | %-10s | %-8s | %s\n",
               semuaUserListTemp[i].id,
               semuaUserListTemp[i].username,
               semuaUserListTemp[i].role,
               (strcmp(semuaUserListTemp[i].role, "Pasien") == 0 && strlen(semuaUserListTemp[i].namaPenyakit) > 0)
               ? semuaUserListTemp[i].namaPenyakit : "-");
    }
}

// Fungsi untuk menampilkan daftar pasien yang terdaftar
void lihatPasien(User pasienListGlobal[], int pasienCountGlobal) {
    // Memastikan hanya Manager yang bisa mengakses fitur ini
    if (!isCurrentUserAManager()) {
        printf("Fitur ini hanya untuk Manager.\n");
        return;
    }

    // Memeriksa apakah ada pasien yang terdaftar
    if (pasienCountGlobal == 0) {
        printf("Tidak ada pasien terdaftar.\n");
        return;
    }

    SortMethod method;
    SortOrder order;
    mintaKriteriaSort(&method, &order, FALSE);

    if (pasienCountGlobal > MAX_JUMLAH_USER) {
        return;
    }

    User tempPasienList[MAX_JUMLAH_USER]; 
    for (int i = 0; i < pasienCountGlobal; i++) {
        tempPasienList[i] = pasienListGlobal[i];
    }

    // Mengurutkan pasien berdasarkan kriteria yang telah ditentukan
    sortUsers(tempPasienList, pasienCountGlobal, method, order);
    
    // Menampilkan header dan data pasien yang telah diurutkan
    printf("\nMenampilkan pasien dengan %s terurut %s...\n",
           (method == SORT_BY_NAME ? "nama" : "ID"),
           (order == DESC ? "descending" : "ascending"));

    printf("ID   | Nama       | Penyakit\n");
    printf("--------------------------------\n");

    for (int i = 0; i < pasienCountGlobal; i++) {
        printf("%-4d | %-10s | %s\n",
               tempPasienList[i].id,
               tempPasienList[i].username,
               (strlen(tempPasienList[i].namaPenyakit) > 0) ? tempPasienList[i].namaPenyakit : "-");
    }
}

// Fungsi untuk menampilkan daftar dokter yang terdaftar
void lihatDokter(User dokterListGlobal[], int dokterCountGlobal) {
    // Memastikan hanya Manager yang bisa mengakses fitur ini
    if (!isCurrentUserAManager()) {
        printf("Fitur ini hanya untuk Manager.\n");
        return;
    }

    // Memeriksa apakah ada dokter yang terdaftar
    if (dokterCountGlobal == 0) {
        printf("Tidak ada dokter terdaftar.\n");
        return;
    }

    SortMethod method;
    SortOrder order;
    mintaKriteriaSort(&method, &order, TRUE);

    if (dokterCountGlobal > MAX_JUMLAH_USER) {
        return;
    }

    User tempDokterList[MAX_JUMLAH_USER];
    for (int i = 0; i < dokterCountGlobal; i++) {
        tempDokterList[i] = dokterListGlobal[i];
    }

    // Mengurutkan dokter berdasarkan kriteria yang telah ditentukan
    sortUsers(tempDokterList, dokterCountGlobal, method, order);
    
    // Menampilkan header dan data dokter yang telah diurutkan
    printf("\nMenampilkan dokter dengan %s terurut %s...\n",
           (method == SORT_BY_AURA) ? "aura" : ((method == SORT_BY_NAME) ? "nama" : "ID"),
           (order == DESC) ? "descending" : "ascending");

    printf("ID   | Nama       | Aura\n");
    printf("------------------------\n");

    for (int i = 0; i < dokterCountGlobal; i++) {
        printf("%-4d | %-10s | %d\n", tempDokterList[i].id, tempDokterList[i].username, tempDokterList[i].aura);
    }
}