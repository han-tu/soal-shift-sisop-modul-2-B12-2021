# Laporan Penjelasan dan Penyelesaian Soal

## Soal 1
### e. Membuat Program yang berjalan secara otomatis
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
Variabel hours, minutes, days, months, dan seconds menyimpan waktu sekarang dan bisa digunakan untuk mengetahui kapan program harus berjalan. Proses daemon akan mengecek setiap detik.<br> <br>
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
Membuat folder-folder Musyik, Fylm, Pyoto yang nantinya untuk menyimpan isi dari MUSIK, FILM, dan FOTO.<br><br>
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
isi folder setelah 16:22:00
![](https://i.imgur.com/BqQrqYu.png)

isi folder setelah 22:22:00
![](https://i.imgur.com/dPzaq1l.png)

isi dari ``lopyu_stevany.zip``
![ket](https://i.imgur.com/o2GJly5.png)

Beberapa kendala yang didapat saat membuat program ini adalah :
1. Kesalahan penempatan ```fork()``` dalam ```while``` loop sehingga program melakukan ```fork()``` terus menerus.
2. Terlalu banyak melalukan wget sehingga google drive sering mengembalikan 403 Forbidden.

## Soal 2

### a. Mengextract zip, membedakan file dan folder, dan menghapus folder

Mengextract zip menggunakan ``unzip``
```
  if (fork() == 0)
  {
    char *argv[] = {"unzip", "-q", "/home/zea/modul2/pets.zip", "-d", "/home/zea/modul2/petshop/"};
    execv("/bin/unzip", argv);
  }

  while((wait(NULL)) > 0);
```
-q agar tidak memberikan output informasi yang sedang dikerjakan program\
/home/zea/modul2/pets.zip adalah path yang akan diextract\
-d /home/zea/modul2/petshop/ path tujuan hasil mengextract zip

Membedakan file dan folder dan menghapus folder menggunakan library ``dirent.h``
```
  DIR *dp;
  struct dirent *ep;
  char path[100] = {"/home/zea/modul2/petshop/"};

  dp = opendir(path);
  if (dp != NULL)
  {
    while ((ep = readdir (dp)))
    {
      if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
        continue;

      if (fork() == 0) continue;
          
      if (ep->d_type & DT_DIR)
      {
        char t[50];
        strcpy(t, path);
        strcat(t, ep->d_name);
        
        if (fork() == 0)
        {
          char *argv[] = {"rm", "-rf", t, NULL};
          execv("/bin/rm", argv);
        }
                
        while((wait(NULL)) > 0);
        exit(EXIT_SUCCESS);
      }
```
Jika file adalah folder ``if (ep->d_type & DT_DIR)`` maka akan diremove menggunakan ``-rm``
```
        if (fork() == 0)
        {
          char *argv[] = {"rm", "-rf", t, NULL};
          execv("/bin/rm", argv);
        }
                
        while((wait(NULL)) > 0);
        exit(EXIT_SUCCESS);
      }
```

### b. Membuat folder untuk setiap jenis peliharaan

Pertama tama kita memotong .jpg dari nama file
```
char* cut_dot_jpg (char* str)
{
  int leng;
  char* new_str;
  
  int i;
  for (i = 0; str[i] != '\0'; i++);
  
  leng = i - 3;

  if (leng < 1) 
    return NULL;

  new_str = (char*) malloc (leng * sizeof(char));

  for (i = 0; i < leng - 1; i++){
    new_str[i] = str[i];
  }
  new_str[i] = '\0';
  return new_str;  
}

      char* cutted = cut_four(ep->d_name);
      char* tok;
```
Lalu memisahkan atribut hewan yang dipisahkan dengan ``_`` dan ``;``
```
      while (tok = strtok_r(cutted, "_", &cutted))
      {
        char* tok2;
        int j = 0;
        char cat[20], name[20], umur[10];
        char* temp = tok;
                
        while (tok2 = strtok_r(temp, ";", &temp))
        {
```
Membuat folder sesuai kategori hewan dengan ``mkdir``
```
          if (j == 0)
          {
            if (fork() == 0)
            {
              char a[80]; strcpy(a, path); strcat(a, tok2);
              char* argmk[] = {"mkdir", "-p", a, NULL};
              execv("/bin/mkdir", argmk);
            }
            
            while((wait(NULL)) > 0);
            strcpy(cat, tok2);
          }
```
Sisa atribut disimpan di array yang sesuai
```
          if (j == 1)
          {
            strcpy(name, tok2);
          }
                    
          
          if (j == 2)
          {
            strcpy(umur, tok2);
          }
          
          j++;
        }
```

### c. Memindahkan foto ke folder sesuai kategori dan rename

Memindah dan merename file menggunakan ``cp``
```
        if (fork() == 0)
        {
          char t[80]; strcpy(t, path); strcat(t, cat); strcat(t, "/"); strcat(t, name); strcat(t, ".jpg");
          char u[80]; strcpy(u, path); strcat(u, ep->d_name);
          char* argcp[] = {"cp", u, t, NULL};
          execv("/bin/cp", argcp);
        }
                
        while((wait(NULL)) > 0); 
```
Menggunakan cp karena kalau satu file terdapat 2 hewan, maka file akan dicopy 2 kali ke kategori yang sesuai
(soal d)\
u adalah source path\
t adalah destination path sekaligus memberi nama_hewan.jpg dibelakangnya

### e. File keterangan.txt

keterangan.txt berisi nama dan umur semua peliharaan di satu folder
```
        char p[80] = "nama : ";
        strcat(p, name); strcat(p, "\numur  : "); strcat(p, umur); strcat(p, " tahun\n\n");      
        char y[80]; strcpy(y, path); strcat(y, cat); strcat(y, "/keterangan.txt");
        FILE* src = fopen(y, "a");
        fputs(p, src);
        fclose(src);
      } 
```
p adalah format dari keterangan.txt\
y adalah path dari keterangan

Setelah itu, file akan diremove menggunakan ``rm``
```
      char b[50]; strcpy(b, path); strcat(b, ep->d_name);
      char* argrm[] = {"rm", b, NULL};
      execv("/bin/rm", argrm);
    }

    (void) closedir (dp);
  }
  
  else perror ("Couldn't open the directory");

  return 0;
}
```
Maka isi dari folder petshop akan tampak seperti berikut:
![petshop](https://i.imgur.com/dS51fv3.png)

Sebagai contoh, isi dari folder cat adalah:
![foldercat](https://i.imgur.com/K8daTD8.png)

Keterangan.txt di folder cat:
![ket](https://i.imgur.com/7ypDPhL.png)

Kendala yang ditemukan pada soal ini:
1. Membuat program dapat membedakan file dan folder
2. Membuat folder tanpa kita periksa satu satu
3. Lupa melakukan fork sebelum exec
4. Mengambil atribut dari hewan

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
