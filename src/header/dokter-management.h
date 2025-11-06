#ifndef DOKTER_MANAGEMENT_H
#define DOKTER_MANAGEMENT_H

#include "data.h"
#include "set.h"

void tambahDokter(User dokterList[], int *currentDokterCount, Set *usernameSet);
void assignRuangan(User dokterList[], int currentDokterCount, Ruangan ruanganList[], int jumlahRuanganTotal, int denahBaris, int denahKolom);

#endif