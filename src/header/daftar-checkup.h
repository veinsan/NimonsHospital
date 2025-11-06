#ifndef DAFTAR_CHECKUP_H
#define DAFTAR_CHECKUP_H

#include "data.h"     

void initializeDokterQueues(User semuaDokter[], int jumlahTotalDokter);
void daftarCheckUp(User paraDokter[], int jumlahParaDokter, User semuaPasien[], int jumlahPasienSekarang); 

#endif