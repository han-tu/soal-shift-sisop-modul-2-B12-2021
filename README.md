# Laporan Penjelasan dan Penyelesaian Soal

## Soal 1

## Soal 2

## Soal 3

### a. Membuat direktori dengan format nama sesuai timestamp [YYYY-mm-dd_HH:ii:ss] tiap 40 detik

Pembuatan format nama akan menggunakan library time.h

```c
        now = time(0) ;
        t = *localtime(&now) ;
        strftime(buff, sizeof(buff), "%Y-%m-%d_%X", &t) ;
```
variabel buff akan menyimpan format nama yang diinginkan dengan tipe data string (char*).

Setelah melakukan ```fork()``` child process akan kembali di-fork agar dapat melakukan execv di sub child nya dan melanjutkan program di child processnya.
sub child process akan melakukan command ```mkdir``` dengan nama sesuai isi variabel ```buff```. Lalu di eksekusi dengan perintah execv.
```c
        if (child_id == 0) {
            // int status ;
            if (fork() == 0) {
                char* arg[] = {"mkdir", "-p", buff, NULL} ;
                execv("/bin/mkdir", arg) ;
            }
        }
```
Lalu diakhir loop while program akan menunggu selama 40 detik menggunakan code berikut :

```c
        time_t first = time(0), second ;
        while (difftime(second, first) != 40) {
            second = time(0) ;
        }
```

dimana tipe data time_t berasal dari library time.h .

### b. Mengunduh 10 gambar tiap 5 detik, lalu memberi nama berdasarkan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar persegi berukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix.

Process ini dilakukan pada parent process yang dihasilkan dari fork utama. Hal pertama yang dilakukan adalah program menjalankan ```sleep(1)``` untuk menuggu child process satu tingkat dibawahnya selesai membuat folder.


