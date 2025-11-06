#include "diagnosis.h"

// Fungsi untuk mendiagnosis pasien berdasarkan gejala yang dimilikinya
void diagnosisPasien(User *pasien) {
    // Iterasi melalui semua penyakit yang terdaftar
    for (int i = 0; i < jumlahPenyakit; i++) {
        // Mengecek apakah kondisi pasien sesuai dengan rentang nilai yang ditentukan untuk penyakit tertentu
        if (pasien->suhuTubuh >= penyakitList[i].suhuTubuhMin && pasien->suhuTubuh <= penyakitList[i].suhuTubuhMax &&
            pasien->tekananDarahSistolik >= penyakitList[i].tekananDarahSistolikMin && pasien->tekananDarahSistolik <= penyakitList[i].tekananDarahSistolikMax &&
            pasien->tekananDarahDiastolik >= penyakitList[i].tekananDarahDiastolikMin && pasien->tekananDarahDiastolik <= penyakitList[i].tekananDarahDiastolikMax &&
            pasien->detakJantung >= penyakitList[i].detakJantungMin && pasien->detakJantung <= penyakitList[i].detakJantungMax && 
            pasien->kadarGulaDarah >= penyakitList[i].kadarGulaDarahMin && pasien->kadarGulaDarah <= penyakitList[i].kadarGulaDarahMax &&
            pasien->kadarKolesterol >= penyakitList[i].kadarKolesterolMin && pasien->kadarKolesterol <= penyakitList[i].kadarKolesterolMax &&
            pasien->saturasiOksigen >= penyakitList[i].saturasiOksigenMin && pasien->saturasiOksigen <= penyakitList[i].saturasiOksigenMax &&
            pasien->trombosit >= penyakitList[i].trombositMin && pasien->trombosit <= penyakitList[i].trombositMax) {

            // Jika semua gejala pasien sesuai dengan rentang nilai penyakit ini, maka pasien terdiagnosis penyakit ini
            printf("%s terdiagnosa penyakit %s!\n", pasien->username, penyakitList[i].namaPenyakit);
            strcpy(pasien->namaPenyakit, penyakitList[i].namaPenyakit);  // Menyimpan nama penyakit yang didiagnosis pada pasien
            return;  // Menghentikan proses jika penyakit sudah terdeteksi
        }
    }

    // Jika tidak ada penyakit yang cocok dengan kondisi pasien
    printf("%s tidak terdiagnosis penyakit apapun!\n", pasien->username);
    pasien->namaPenyakit[0] = '\0'; // Set namaPenyakit ke string kosong
}