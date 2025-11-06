#ifndef SET_H
#define SET_H

#include "data.h"

void buatSet(Set *s);
void ubahKeHurufKecil(char *dest, const char *src);
int searchSet(Set s, const char *input);
void insertSet(Set *s, const char *input);
void hapusSet(Set *s, const char *input);

#endif