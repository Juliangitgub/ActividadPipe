#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]){
srand(time(NULL));
int fd[2];
char buf[5];
int RN;
int num;

pid_t pid;

pipe(fd);
//error 


 if (pipe(fd) == -1) {
    perror("Creating pipe");
    exit(EXIT_FAILURE);
  }

//
pid=fork();
switch(pid)
{
//
case 0://hijo
close(fd[1]);

read(fd[0],buf,5);//modificar
sscanf(buf, "%d", &num);

if(num<500){
printf("El valor es menor a 500 \n");
close(fd[0]);
}
else{
printf("El valor es mayor o igual a 500\n");
}
close(fd[0]);

break;
//
//
case -1: //error
printf("Hubo un error en la creacion del proceso");
return 1;
break;
//
// 
default://Padre
RN=rand()%(998)+1;
//printf("EL NUMERO ALEATORIO ES: %i\n",RN);
sprintf(buf,"%d",RN);
close(fd[0]);
write(fd[1],buf,5);
close(fd[1]);
break;
//
}


}

