# Laporan Penjelasan dan Penyelesaian Soal

## Soal 1
### e. Membuat Progam yang berjalan secara otomatis
Membuat suatu proses daemon yang dapat mengecek waktu
```c
  while (1) {
	int hours, minutes, seconds, day, month, year;
	time_t now;
	time(&now);
	struct tm *local = localtime(&now);
	hours = local->tm_hour;
	minutes = local->tm_min;
	day = local->tm_mday;
	month = local->tm_mon + 1;
	seconds=local->tm_sec;
```
Variabel hours, minutes, days, months, seconds menyimpan waktu sekarang dan bisa digunakan untuk mengetahui kapan program harus berjalan. Proses daemon akan mengecek setiap detik.<br> <br>
### b. Mendownload file dari google drive
```c
 if(day==9&&month==4&&hours==16&&minutes==22&&seconds<20){
	int child_id;
	for(int i=0;i<3;i++){
  	child_id = fork();
  	if (child_id == 0){
	if(i==0)
	{
	char link[80]={"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download"};
	execlp("wget","wget","--no-check-certificate",link,"-q","-O","Musik_for_Stevany.zip", NULL );
	}
if(i==1)
	{
	char link[80]={"https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"};
	execlp("wget","wget","--no-check-certificate",link,"-q","-O","Film_for_Stevany.zip", NULL );
	}
if(i==2)
	{   	 
	char link[80]={"https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
	execlp("wget","wget","--no-check-certificate",link,"-q","-O","Foto_for_Stevany.zip",NULL);
	}   	 
	}
	}
	sleep(21);
}
```
Ketika waktu sekarang adalah Jum 09 Apr 16:22:00, program akan mendownload file-file zip dari google drive. Program lalu diberi jeda 20 detik agar memastikan download telah selesai sebelum lanjut ke perintah selanjutnya.Menggunakan ```fork()``` yang berada di dalam ```for``` loop. <br><br>
### c. Mengextract isi dari zip
```c
if(day==9 && month==4 && hours==16 && minutes==22 && seconds==25){
int child_id;
for(int i=0;i<3;i++){
  child_id = fork();
  if (child_id == 0){
if(i==0)
	execlp("unzip","unzip","Foto_for_Stevany.zip",NULL);
if(i==1)
	execlp("unzip","unzip","Film_for_Stevany.zip",NULL);
if(i==2)	 
	execlp("unzip","unzip","Musik_for_Stevany.zip",NULL);       	 
    	}
	}
sleep(5);
}
```
Pada detik ke 25, file-file yang telah didownload akan di unzip. Akan terdapat folder-folder MUSIK, FOTO, dan FILM.<br><br>
### a. Membuat folder Musyik, Fylm, dan Pyoto
```c
if(day==9 && month==4 && hours==16 && minutes==22 && seconds==31){
int child_id;
for(int i=0;i<3;i++){
  child_id = fork();
  if (child_id == 0){
if(i==0)
	execlp("mkdir","mkdir","Musyik",NULL);
if(i==1)
	execlp("mkdir","mkdir","Fylm",NULL);
if(i==2)   	 
	execlp("mkdir","mkdir","Pyoto",NULL);
        	}
	}
	sleep(3);
}
```
Membuat folder-folder Musyik,Fylm,Pyoto yang nantinya untuk menyimpan isi dari MUSIK,FILM, dan FOTO.<br><br>
### d. Memindahkan ke folder yang telah dibuat
```c
if(day==9 && month==4 && hours==16 && minutes==22 && seconds==35){
int child_id;
for(int i=0;i<3;i++){
  child_id = fork();
  if (child_id == 0){
if(i==0)
	execlp("cp","cp","-a","MUSIK/.","Musyik/",NULL);
if(i==1)
	execlp("cp","cp","-a","FILM/.","Fylm/",NULL);
if(i==2)
	execlp("cp","cp","-a","FOTO/.","Pyoto/",NULL);	 
        	}
	}
	sleep(3);
}
if(day==9 && month==4 && hours==16 && minutes==22 && seconds==39){
int child_id;
for(int i=0;i<3;i++){
  child_id = fork();
  if (child_id == 0){
if(i==0)
	execlp("rm","rm","-r","MUSIK",NULL);
if(i==1)
	execlp("rm","rm","-r","FILM",NULL);
if(i==2)   	 
	execlp("rm","rm","-r","FOTO",NULL);   	 
        	}
	}
	sleep(3);
}
```
Mengcopy isi dari MUSIK, FILM, dan FOTO, ke Musyik, Fylm, dan Pyoto. Setelah itu folder MUSIK, FILM, dan FOTO dihapus.<br><br>
### f. Semua folder di zip pada jam 22:22:00
```c
if(day==9&&month==4&&hours==22&&minutes==22){
    	execlp("zip","zip","-rm","Lopyu_Stevany.zip","Musyik","Pyoto","Fylm",NULL);  
	}
}
```
Ketika waktu sekarang adalah Jum 09 Apr 22:22:00, Folder Musyik, Pyoto, dan Fylm akan di zip ke Lopyu_Stevany.zip. ```-rm``` akan menghapus folder-folder tersebut sehingga yang tersisa hanya file zipnya. Pada bagian ini tidak dilakukan ```fork()``` sehingga ketika berjalan juga akan memberhentikan proses daemon.<br><br>
Beberapa kendala yang didapat saat membuat program ini adalah :
1. Kesalahan penempatan ```fork()``` dalam ```while``` loop sehingga program melakukan ```fork()``` terus menerus.
2. Terlalu banyak melalukan wget sehingga google drive sering mengembalikan 403 Forbidden.

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
