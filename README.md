cat << 'EOF' > README.md
# 🏥 Nimons Hospital  
**Tugas Besar IF1210 – Algoritma dan Pemrograman 1 ITB 2025**  

Nimons Hospital adalah sistem manajemen rumah sakit berbasis terminal yang dibuat menggunakan bahasa C.  
Proyek ini mensimulasikan kegiatan utama dalam rumah sakit seperti login multi-role, manajemen pasien dan dokter, sistem antrian, diagnosa penyakit, hingga pengelolaan obat dan ruangan.  

---

## 🧩 Fitur Utama (F01–F18)
| Kode | Fitur | Deskripsi Singkat |
|------|-------|------------------|
| F01 | **Login** | Autentikasi Manager, Dokter, dan Pasien. |
| F02 | **Register** | Registrasi akun pasien baru dengan validasi username huruf saja. |
| F03 | **Lihat User** | Menampilkan daftar semua user, dokter, atau pasien dengan opsi sorting. |
| F04 | **Cari User** | Mencari pengguna berdasarkan ID atau nama. |
| F05 | **Tambah Dokter** | Menambahkan dokter baru (khusus Manager). |
| F06 | **Assign Ruangan** | Menempatkan dokter ke ruangan tertentu. |
| F07 | **Lihat Denah** | Menampilkan layout rumah sakit dalam bentuk grid interaktif. |
| F08 | **Ubah Denah** | Mengatur ukuran atau isi denah ruangan. |
| F09 | **Daftar Checkup** | Pasien mendaftar ke antrian dokter. |
| F10 | **Lihat Antrian** | Menampilkan daftar pasien di tiap dokter. |
| F11 | **Mainin Antrian** | Dokter dapat skip atau cancel antrian (bonus feature). |
| F12 | **Diagnosis** | Dokter mendiagnosa pasien berdasarkan parameter kesehatan. |
| F13 | **Ngobatin** | Menentukan obat yang harus diminum pasien sesuai penyakit. |
| F14 | **Minum Obat** | Simulasi pasien meminum obat menggunakan stack. |
| F15 | **Penawar** | Mengeluarkan obat dari perut dan mengembalikannya ke inventory. |
| F16 | **Aku Boleh Pulang Ga?** | Mengecek apakah pasien sudah sembuh berdasarkan kondisi tubuh. |
| F17 | **Help** | Menampilkan daftar perintah sesuai role pengguna. |
| F18 | **Exit** | Menyimpan perubahan dan keluar dari sistem. |

---

## ⚙️ Struktur Folder
```bash
nimons-hospital/
├── src/
│ ├── main.c
│ ├── makefile
│ ├── [18 modul .c]
│ └── [17 header .h]
│
└── data/
├── dokter.txt
├── pasien.txt
├── penyakit.txt
└── obat.txt

```


---

## 🧠 Konsep dan Implementasi
- **Bahasa:** C  
- **Paradigma:** Modular + ADT  
- **Struktur Data:** Queue, Stack, Map, Set, Linked List  
- **Sorting:** Bubble & Selection Sort  
- **Searching:** Binary Search & Sequential Search  
- **Konsep Tambahan:**  
  - Run-Length Encoding (RLE) untuk fitur *Lupa Password*  
  - Bonus fitur antrian (skip & cancel)  
  - Penawar obat (mengeluarkan dari stack perut ke inventory)

---

## 🧪 Cara Menjalankan
Jalankan perintah berikut di terminal:

```bash
git clone https://github.com/veinsan/GelapNyawang.git
```

Atau, untuk rebuild pakai:

```bash
make clean
make run
```

---

## 👥 Tim Pengembang
| Nama | NIM | Fakultas |
|------|------|-----------|
| Naomi Azzahra | 18224017 | Sistem dan Teknologi Informasi |
| Muthia Ariesta Anggraeni | 18224045 | Sistem dan Teknologi Informasi |
| Nathan Pasha Athallah | 18224053 | Sistem dan Teknologi Informasi |
| Riantama Putra | 18224061 | Sistem dan Teknologi Informasi |
| Stephanie Mae | 18224117 | Sistem dan Teknologi Informasi |

---

## 🧾 Catatan
- Proyek ini dibuat sebagai bagian dari mata kuliah **IF1210 – Algoritma dan Pemrograman 1**.  
- Dibangun dengan semangat ngoding sampai pagi dan kopi dingin. ☕  
- Semua fitur diuji di lingkungan Linux (GCC 13) dan Windows (MinGW).

---

## 🪪 Lisensi
Proyek ini bersifat open source untuk tujuan pembelajaran.  
Silakan fork dan pelajari strukturnya, tapi tetap cantumkan kredit ke **Tim Nimons Hospital – ITB 2025**.
