#ifndef LIHAT_USER_H 
#define LIHAT_USER_H

#include "data.h"

void lihatsemuaUser(User manager, User dokterList[], int dokterCount, User pasienList[], int pasienCount);
void lihatDokter(User dokterList[], int dokterCount);
void lihatPasien(User pasienList[], int pasienCount);
void swapUsers(User *a, User *b);
void sortUsers(User arr[], int n, SortMethod method, SortOrder order);

#endif