#include "fonction.h"

int main(void){
	char buf[BUFSIZE];
	char output[BUFSIZE];
	int size;
	int i;
	char arg[NUM_ARG][BUFSIZE];
	struct timespec start, stop;
	write(1,"Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n",59);
	sprintf(output,"enseash %% ");
	while(1){
		write(1,output,strlen(output));
		size=read(1,buf,BUFSIZE);
		
		char* token=strtok(buf," ");
		// on ne récupère que le début de la commande, c'est à dire le nom de la fonction appelée
		i=0;
		while (token != NULL){
			strcpy(arg[i],token);
			token=strtok(NULL," ");
			// on récupère ici tout les arguments qui suivent la commande
			i++;
		}
		
		if(strncmp(arg[0],"exit\n",5)==0 || size==0){
			//EOF pour ctrl D
					write(1,"Bye bye\n",8);
					break;
					//il est important de mettre cette boucle en premier car sinon on rentre dans la boucle suivante
		}else if(strncmp(arg[0],"fortune\n",8)==0){
			write(1,"Today is what happened to yesterday.\n",38);
			sprintf(output,"enseash %% ");
		}else if(strncmp(arg[0],"givme42\n",8)==0){
			clock_gettime(CLOCK_REALTIME,&start);
			int out=givme42();
			clock_gettime(CLOCK_REALTIME,&stop);
			sprintf(output,"enseash [exit: %d | %ld ns] %% ",out,stop.tv_nsec - start.tv_nsec);
			//L'entier out est convertit en char puis on l'affiche dans le write au début du while
		}else if(strncmp(arg[0],"add",3)==0){
			clock_gettime(CLOCK_REALTIME,&start);
			int out=add(atoi(arg[1]),atoi(arg[2]));
			clock_gettime(CLOCK_REALTIME,&stop);
			sprintf(output,"enseash [exit: %d | %ld ns] %% ",out,stop.tv_nsec - start.tv_nsec);
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
//char hostname(char s){
//	if(strncmp(s,"-i")==0)
//	return 10.10.2.245;
//}







