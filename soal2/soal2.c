#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <dirent.h>

//fungsi buang .jpg
char* cut_four (char* s)
{
  int n;
  int i;
  char* new;
  
  for (i = 0; s[i] != '\0'; i++);
  // lenght of the new string
  n = i - 4 + 1;

  if (n < 1) return NULL;

  new = (char*) malloc (n * sizeof(char));

  for (i = 0; i < n - 1; i++)
  {
    new[i] = s[i];
  }
  new[i] = '\0';

  return new;  
}

int main()
{
  if (fork() == 0)
  {
    //ngeunzip
    char *argv[] = {"unzip", "-q", "/home/zea/modul2/pets.zip", "-d", "/home/zea/modul2/petshop/"};
    execv("/bin/unzip", argv);
  }

  while((wait(NULL)) > 0);

  //ngecheck file
  DIR *dp;
  struct dirent *ep;
  char path[100] = {"/home/zea/modul2/petshop/"};

  dp = opendir(path);
  if (dp != NULL)
  {
    while ((ep = readdir (dp)))
    {
      //hidden file
      if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
        continue;

      if (fork() == 0) continue;
          
      //nyari yang folder
      if (ep->d_type & DT_DIR)
      {
        char t[50];
        strcpy(t, path);
        strcat(t, ep->d_name);
        
        if (fork() == 0)
        {
          //foldernya diremove
          char *argv[] = {"rm", "-rf", t, NULL};
          execv("/bin/rm", argv);
        }
                
        while((wait(NULL)) > 0);
        exit(EXIT_SUCCESS);
      }
      
      //motong .jpg
      char* cutted = cut_four(ep->d_name);
      char* tok;

      //ngepisahin yang hewannya banyak
      while (tok = strtok_r(cutted, "_", &cutted))
      {
        char* tok2;
        int j = 0;
        //kategori, nama, umur
        char cat[20], name[20], umur[10];
        char* temp = tok;
                
        //ngepisahin atribut hewan
        while (tok2 = strtok_r(temp, ";", &temp))
        {
          if (j == 0)
          {
            if (fork() == 0)
            {
              //bikin folder sesuai hewan
              char a[80]; strcpy(a, path); strcat(a, tok2);
              char* argmk[] = {"mkdir", "-p", a, NULL};
              execv("/bin/mkdir", argmk);
            }
            
            while((wait(NULL)) > 0);
            //simpen ke tok2
            strcpy(cat, tok2);
          }
          
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
        
        if (fork() == 0)
        {
          //kasi nama path/nama.jpg
          char t[80]; strcpy(t, path); strcat(t, cat); strcat(t, "/"); strcat(t, name); strcat(t, ".jpg");
          char u[80]; strcpy(u, path); strcat(u, ep->d_name);
          //copy karena kl ada dua hewan
          //dr source (u) ke destination (t)
          char* argcp[] = {"cp", u, t, NULL};
          execv("/bin/cp", argcp);
        }
                
        while((wait(NULL)) > 0);  

        //format keterangan
        char p[80] = "nama : ";
        strcat(p, name); strcat(p, "\numur  : "); strcat(p, umur); strcat(p, " tahun\n\n");
        //path tempatnya keterangan        
        char y[80]; strcpy(y, path); strcat(y, cat); strcat(y, "/keterangan.txt");
        //a --> bisa bikin, bisa nyambung
        FILE* src = fopen(y, "a");
        fputs(p, src);
        fclose(src);
      } 
      
      //di remove
      char b[50]; strcpy(b, path); strcat(b, ep->d_name);
      char* argrm[] = {"rm", b, NULL};
      execv("/bin/rm", argrm);
    }

    (void) closedir (dp);
  }
  
  else perror ("Couldn't open the directory");

  return 0;
}