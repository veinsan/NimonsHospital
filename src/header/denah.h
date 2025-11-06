#ifndef DENAH_H
#define DENAH_H
#include "data.h"

void lihatDenah(int jumlahRuangIgnored, int barisDenahAktual, int kolomDenahAktual);
void lihatRuangan(int indeks, const Ruangan ruanganListFromParam[], int denahKolomAktual); 
boolean ubahDenah(int *ptrJumlahRuangTotal, Ruangan **ptrToRuanganListGlobal, int barisBaru, int kolomBaru, int *ptrDenahBarisMain, int *ptrDenahKolomMain);
boolean pindahDokter(const char *kodeRuanganAsal, const char *kodeRuanganTujuan, Ruangan ruanganListFromParam[], int denahBarisAktual, int denahKolomAktual);
boolean bacaKonfigurasiDenah(const char *filename, Ruangan **ptrToRuanganListGlobal, int *ptrBarisHasil, int *ptrKolomHasil, int *ptrJumlahRuangHasil);

#endif