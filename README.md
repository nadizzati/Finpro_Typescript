# README - Pemantauan Polusi Laut

## Deskripsi Program
Program ini dirancang untuk memantau dan mengelola data polusi laut di beberapa lokasi. Program ini menerima input dari pengguna terkait konsentrasi polusi di beberapa lokasi laut dan menghitung indeks polusi laut (IPL) untuk setiap lokasi. Berdasarkan IPL yang dihitung, program menampilkan status bahaya polusi di lokasi tersebut dan memungkinkan pengguna untuk mengurutkan data berdasarkan kriteria yang ditentukan.

## Struktur Data
### 1. `SeaLocation`
Struktur data ini digunakan untuk menyimpan informasi tentang lokasi laut dan konsentrasi polusi. Setiap `SeaLocation` menyimpan data seperti:
- Nama lokasi
- Konsentrasi plastik, logam berat, minyak, B3, dan pH
- Indeks untuk masing-masing polusi
- Total Indeks Polusi Laut (IPL)
- Tingkat bahaya berdasarkan IPL
- Jumlah jenis polusi yang terdeteksi

### 2. `DangerLevel`
Enumerasi ini digunakan untuk mengkategorikan tingkat bahaya polusi berdasarkan IPL:
- `AMAN`: Polusi rendah
- `SEDANG`: Polusi sedang
- `TINGGI`: Polusi tinggi
- `SANGAT_TINGGI`: Polusi sangat tinggi

## Fungsi Utama

1. **`inputData()`**:
   - Fungsi ini menerima input nama lokasi dan jenis polusi (Plastik, Logam Berat, Minyak, B3, dan pH) untuk masing-masing lokasi laut.
   
2. **`calculateIndex()`**:
   - Menghitung indeks untuk setiap jenis polusi dengan membandingkan nilai input dengan standar baku mutu.
   - Menghitung total IPL berdasarkan indeks-indeks tersebut dan menentukan tingkat bahaya berdasarkan IPL.

3. **`displayStatus()`**:
   - Menampilkan data status polusi setiap lokasi laut beserta nilai indeks dan IPL yang telah dihitung.

4. **`sortLocations()`**:
   - Mengurutkan lokasi laut berdasarkan kriteria yang dipilih pengguna (misalnya IPL tertinggi, konsentrasi plastik tertinggi, dll).

5. **`showDanger()`**:
   - Menampilkan panduan tentang status bahaya berdasarkan IPL (AMAN, SEDANG, TINGGI, SANGAT TINGGI).

## Pembagian Tugas
### 1. Nadia (Input Data)
Fungsi `inputData()` bertanggung jawab untuk:
- Menginput nama lokasi laut dan jenis polusi yang ada di lokasi tersebut.
- Menangani menu loop untuk memilih jenis polusi (Plastik, Logam Berat, Minyak, B3, dan pH).
- Melakukan validasi input untuk setiap jenis polusi agar hanya menerima data yang valid (angka non-negatif untuk konsentrasi polusi dan nilai pH antara 0 dan 14).

### 2. Eugenia (Kalkulasi Indeks)
Fungsi `calculateIndex()` bertanggung jawab untuk:
- Menghitung indeks polusi untuk masing-masing parameter (Plastik, Logam Berat, Minyak, B3, dan pH) dengan membandingkan nilai yang diinputkan dengan nilai baku mutu lingkungan (standar konsentrasi maksimum).
- Menghitung Indeks Polusi Laut (IPL) total dengan mengambil rata-rata indeks-indeks polusi yang ada.
- Menentukan tingkat bahaya berdasarkan IPL (AMAN, SEDANG, TINGGI, SANGAT TINGGI).

### 3. Azel (Display Status)
Fungsi `displayStatus()` dan `printLine()` bertanggung jawab untuk:
- Menampilkan status lokasi laut beserta parameter polusinya (Plastik, Logam Berat, Minyak, B3, dan pH).
- Menampilkan IPL dan status bahaya untuk setiap lokasi.
- Menampilkan garis pemisah antar lokasi agar tampilan lebih jelas dan terorganisir.

### 4. Mila (Main Program & Ringkasan)
Fungsi `main()`, `showDanger()`, `sortLocations()`, dan `displayAllLocations()` bertanggung jawab untuk:
- Alur utama program yang mengatur input, kalkulasi, dan tampilan hasil.
- Menyediakan menu bagi pengguna untuk memilih bagaimana data akan diurutkan berdasarkan berbagai kriteria (IPL tertinggi, konsentrasi plastik, logam berat, minyak, B3, penyimpangan pH).
- Menampilkan status bahaya polusi dan lokasi dengan polusi berat (Tinggi/Sangat Tinggi).
- Mengatur struktur data `SeaLocation` dan enumerasi `DangerLevel`.

## Contoh Penggunaan
1. **Menambah Data Lokasi**
   - Masukkan jumlah lokasi laut yang ingin dimasukkan.
   - Input nama lokasi dan jenis polusi yang ada di lokasi tersebut.

2. **Pengurutan Data**
   - Pilih kriteria untuk mengurutkan data: IPL tertinggi, konsentrasi plastik tertinggi, atau kriteria lainnya.

3. **Tampilkan Status Polusi**
   - Setelah memasukkan data dan memilih kriteria pengurutan, status polusi untuk setiap lokasi akan ditampilkan, termasuk informasi bahaya berdasarkan IPL.