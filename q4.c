#include "fonction.h"

int main(void){
	char buf[BUFSIZE];
	char output[BUFSIZE];
	int size;
	write(1,"Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n",59);
	sprintf(output,"enseash %% ");
	while(1){
		write(1,output,strlen(output));
		size=read(1,buf,BUFSIZE);
		if(strncmp(buf,"exit\n",5)==0 || size==0){
			//EOF pour ctrl D
					write(1,"Bye bye\n",8);
					break;
					//il est important de mettre cette boucle en première car sinon on rentre dans la boucle suivante
		}else if(strncmp(buf,"fortune\n",8)==0){
			write(1,"Today is what happened to yesterday.\n",38);
			sprintf(output,"enseash %% ");
		}else if(strncmp(buf,"givme42\n",8)==0){
			int out=givme42();
			sprintf(output,"enseash [exit: %d ] %% ",out);
			//L'entier out est convertit en char puis on l'affiche dans le write au début du while
		}else{
			write(1,"Error unknown function.\n",25);
			sprintf(output,"enseash %% ");
		}
	}
	return 1;
}

int givme42(void){
	return 42;
}

int add(int n,int m){
	return n+m;
}
