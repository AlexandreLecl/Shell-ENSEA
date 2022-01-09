#include "fonction.h"

int count[3];

int main(void){
	char buf[BUFSIZE];
	char output[BUFSIZE];
	int size;
	int i;
	char arg[NUM_ARG][BUFSIZE];
	FILE* fichier;
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
		while (i<NUM_ARG){
			// on réinitialise les arguments non utilisés
			strcpy(arg[i],"");
			i++;
		}
		if(strncmp(arg[0],"exit\n",5)==0 || size==0){
			//EOF pour ctrl D
				write(1,"Bye bye\n",8);
				break;
				//il est important de mettre cette boucle en premier car sinon on rentre dans la boucle suivante

		}else if(strncmp(arg[0],"fortune",7)==0){
			if(strncmp(arg[1],">",1)==0){
				// On inscrit la sortie de la fonction dans un fichier
				fichier=fopen(arg[2],"w+");
				fprintf(fichier,"Today is what happened to yesterday.\n");
				fclose(fichier);
				sprintf(output,"enseash %% ");
			}else if(strncmp(arg[1],"|",1)==0){
				//gestion de la redirection de type pipe
				if(strncmp(arg[2],"wc",2)==0){
					clock_gettime(CLOCK_REALTIME,&start);
					fichier=fopen("fortune.txt","w+");
					if(fichier==NULL){
						write(1,"Erreur impossible d'ouvrir ce fichier\n",38);
						exit(1);
					}
					fprintf(fichier,"Today is what happened to yesterday.\n");
					fclose(fichier);
					fichier=fopen("fortune.txt","r");
					if(fichier==NULL){
						write(1,"Erreur impossible d'ouvrir ce fichier\n",38);
						exit(1);
					}
					wc(fichier);
					fclose(fichier);
					clock_gettime(CLOCK_REALTIME,&stop);
					sprintf(output,"enseash [exit: %d %d %d | %ld ns] %% ",count[0],count[1],count[2],stop.tv_nsec - start.tv_nsec);
				}
			}else{
				write(1,"Today is what happened to yesterday.\n",38);
				sprintf(output,"enseash %% ");
			}
			
		}else if(strncmp(arg[0],"wc",2)==0){
			// wc compte les nombres de lignes, de mots et de caractères
			if(strncmp(arg[1],"<",1)==0){
				clock_gettime(CLOCK_REALTIME,&start);
				fichier=fopen(arg[2],"r");
				if(fichier==NULL){
					write(1,"Erreur impossible d'ouvrir ce fichier\n",38);
					exit(1);
				}
				wc(fichier);
				fclose(fichier);
				clock_gettime(CLOCK_REALTIME,&stop);
				sprintf(output,"enseash [exit: %d %d %d | %ld ns] %% ",count[0],count[1],count[2],stop.tv_nsec - start.tv_nsec);
			}else{
				write(1,"Error missing arguments.\n",25);
				sprintf(output,"enseash %% ");
			}
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
void wc(FILE* fichier){
	int num_line=1;
	int num_word=1;
	int num_carac=0;
	int current_carac=0;
	while(current_carac != EOF){
		current_carac=fgetc(fichier);
		num_carac++;
		if(current_carac==' '){
			num_word++;
		}else if(current_carac=='\n'){
			num_word++;
			num_line++;
		}
	}
	count[0]= num_line;
	count[1]= num_word;
	count[2]= num_carac;
}







