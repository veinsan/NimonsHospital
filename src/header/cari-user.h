#ifndef CARI_USER_H
#define CARI_USER_H

#include "data.h"
#include "lihat-user.h"

int binarySearchByID(User sortedList[], int size, int id);
int sequentialSearchByName(User list[], int count, const char *name); // Pencarian case-sensitive

void cariUser(User *manager, User dokterList[], int dokterCount, User pasienList[], int pasienCount);
void cariDokter(User dokterList[], int dokterCount);
void cariPasien(User pasienList[], int pasienCount);

#endif