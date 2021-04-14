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

Lakukan loop sebanyak 10x. Dimana tiap loop melakukan 
1. Fork
2. Mengambil string format timestamp seperti yang diminta
3. Mengambil path tempat menaruh hasil unduhan
4. Menghitung ukuran gambar sesuai yang diminta
5. Mengunduh 1 gambar

```c
                if (fork() == 0) {
                    continue ;
                }

                time_t new_now = time(0) ;
                struct tm new_tstruct = *localtime(&new_now) ;
                char new_buff[80] ;
                strftime(new_buff, sizeof(new_buff), "%Y-%m-%d_%X", &new_tstruct) ;
                
                char path[80] ;
                strcpy(path, buff) ;
                strcat(path, "/") ;
                strcat(path, new_buff) ;
                
                char link[80] = "https://picsum.photos/" ;
                int picsize = (((long)mktime(&t)) % 1000) + 50 ;
                char num[10] ;
                sprintf(num, "%d", picsize) ;
                strcat(link, num) ;

                char* arg[] = {"wget", "-q", "-O", path, link, NULL} ;
                execv("/bin/wget", arg) ;
```

Untuk mengambil detik Epoch Unix, digunakan fungsi ```mktime``` dari library time.h. karena return type fungsi tersebut ada ```time_t``` maka harus memberikan type cast "long" agar dapat dibaca sebagai angka.

### c. Letakkan file status.txt yang berisi "Download Success" dengan enkripsi caesar chipper shift 5. Lalu zip direktori.

Untuk membuat file status.txt, cukup menggunakan fungsi ```fopen``` dengan mode "w" agar otomatis terbuat filenya. Enkripsi String "Download Success" lalu letakkan kedalam status.txt. Lalu zip direktori tersebut dengan mode zip "-m" agar direktori yang lama terhapus setelah di-zip.

```c
            char str[30] = "Download Success", p[30] ;
            int j ;
            for (j = 0 ; j < strlen(str) ; j++) {
                if (str[j] == ' ') continue ;
                if ((str[j] >= 'a' && str[j] <= 'z' && str[j] + 5 > 'z') || (str[j] >= 'A' && str[j] <= 'Z' && str[j] + 5 > 'Z'))
                    str[j] -= 26 ;
                str[j] += 5 ;
            }
            strcpy(p, buff) ;
            strcat(p, "/") ;
            strcat(p, "status.txt") ;
            FILE* txt = fopen(p, "w") ;
            fputs(str, txt) ;
            fclose(txt) ;
            
            strcpy(p, buff) ;
            strcat(p, ".zip") ;
            char* argz[] = {"zip", p, "-q", "-m", "-r", buff, NULL} ;
            execv("/bin/zip", argz) ;
```

mode zip lainnya seperti "-q" digunakan agar output log dari command zip tidak dicetak, dan "-r" digunakan agar direktori di-zip secara rekursif.

### d. Membuat Program Bash yang dapat menterminasi semua process serta menghapus dirinya sendiri.
Akan dibahas secara bersamaan pada soal poin (e)

### e. Membuat dua mode program utama
1. Mode "-z" agar ketika program "killer" dapat menghentikan semua operasi dari proses.

Ketika argumen mode yang dimasukkan saat program utama dijalankan adalah "-z". Code berikut akan dieksekusi
```c
        if (!strcmp(argv[1], "-z")) {
            strcpy(b, "#!/bin/bash\nkillall -9 ./soal3\nrm $0\n") ;
            make_program(b) ;
        }
```

2. Mode "-x" yang menunggu semua process selesai lalu melakukan terminasi kepada semua process

Ketika argumen mode yang dimasukkan saat program utama dijalankan adalah "-z". Code berikut akan dieksekusi
```c
        else if (!strcmp(argv[1], "-x")) {
            strcpy(b, "#!/bin/bash\nkillall -15 ./soal3\nrm $0\n") ;
            make_program(b) ;
            signal(SIGTERM, custom_signal_x) ;
        }
```

fungsi ```signal``` akan merubah perilaku sinyal SIGTERM (15) menjadi menjalankan fungsi ```custom_signal_x()```

```c
void custom_signal_x(int signum) {
    mysignal = 0 ;
}
```

variabel mysignal adalah variabel yang digunakan sebagai kondisi while
```c
while(mysignal) {
```
sehingga ketika mysignal bernilai 0, program akan berhenti.

Beberapa kendala yang didapat saat membuat program ini adalah :
1. Terjadi pembuatan process yang terlalu banyak karena lupa menghentikan fork
2. Kesalahan - kesalahan syntax fungsi
3. Menemukan ide agar proses dapat berjalan secara paralel (bersama - sama) tanpa menunggu proses yang lain selesai
