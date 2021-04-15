
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
int main() {
  pid_t pid, sid;   	 
  pid = fork();	 
  if (pid < 0) {
	exit(EXIT_FAILURE);
  }
  if (pid > 0) {
	exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0) {
	exit(EXIT_FAILURE);
  }
  if ((chdir("/home/huda/jawab")) < 0) {
	exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

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
if(day==9&&month==4&&hours==22&&minutes==22){
    	execlp("zip","zip","-rm","Lopyu_Stevany.zip","Musyik","Pyoto","Fylm",NULL);  
	}
}
}
