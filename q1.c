#include "fonction.h"

int main(void){
	char buf[BUFSIZE];
	write(1,"Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n",60);
	write(1,"enseash % ",10);
	read(1,buf,BUFSIZE);
	return 1;
}
