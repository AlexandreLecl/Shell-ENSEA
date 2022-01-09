#include "fonction.h"

int main(void){
	char buf[BUFSIZE];
	int size;
	write(1,"Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n",59);
	while(1){
		write(1,"enseash % ",10);
		size=read(1,buf,BUFSIZE);
		if(strncmp(buf,"exit\n",5)==0 || size==0){
					write(1,"Bye bye\n",8);
					break;
		}else if(strncmp(buf,"fortune\n",8)==0){
			write(1,"Today is what happened to yesterday.\n",38);
		}else{
			write(1,"Error unknown function.\n",25);
		}
	}
	return 1;
}
