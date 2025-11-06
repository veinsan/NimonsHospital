#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include "data.h"
#include "set.h"

void login(User *manager, User dokterList[], int dokterCount, User pasienList[], int pasienCount);
void registerPasien(User pasienList[], int *pasienCount, Set *usernameSet);
void logout();
void lupaPassword(User *manager, User dokterList[], int dokterCount, User pasienList[], int pasienCount);
void generateKodeUnik(const char *username, char *output);

#endif