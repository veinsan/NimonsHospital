#ifndef MINUM_OBAT_H
#define MINUM_OBAT_H

#include "data.h"

void buatStackObat(StackObat *s);
void tambahObat(ListObat *inventory, const char *obat);
int stackKosong(StackObat s);
int stackPenuh(StackObat s); 
void pushObat(StackObat *s, const char *obat);
void popObat(StackObat *s, char *obatDihapus); 
void buatListObat(ListObat *l);
void hapusObat(ListObat *l, int index);
void tampilkanListObat(ListObat l);
void minumObat(User *pasien, StackObat *perut, ListObat *inventory);
void minumPenawar(StackObat *perut, ListObat *inventory);

#endif