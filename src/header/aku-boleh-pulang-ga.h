#ifndef AKU_BOLEH_PULANG_GA_H
#define AKU_BOLEH_PULANG_GA_H

#include "data.h"
#include "set.h"

void akubolehpulanggaDok(
    User* userLoggedInInstance,
    StackObat* perutPasien,
    ListObat* inventoryPasien,
    User pasienListGlobal[],
    int* jumlahPasienGlobalPtr,
    Set* usernameSetGlobal,
    int* statusLoginGlobalPtr,
    User dokterListGlobal[],
    int dokterCountGlobal
);

void sisanyawanimon(int nyawaDiberikan);

#endif