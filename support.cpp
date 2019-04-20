#include "headers.h"

using namespace std;


int numParameters(char *buffer){
	int i = 1;
	char *p = strstr(buffer, " ");
	while(p != NULL){
		p = strstr(&p[1], " ");
		i++;	
	}

	return i;
}

void pop(){
	putp(exit_attribute_mode);
}

void push(int cor){
	putp(enter_bold_mode);
	putp(tparm(set_a_foreground, cor));
}

char **split(char *buffer){
	int i = 0, num = numParameters(buffer)+1;
	char *p = strtok(buffer, " "), **argv = new char*[num];
	while(p != NULL){

		argv[i] = new char[255];
		strcpy(argv[i], p);		 
		
		i++;			

		p = strtok(NULL, " ");
	}
	return argv;
}

char **splitPipe(char *string, const char *sep){
	char *temp = new char[strlen(string)];
	char **splited = new char*[2];
	char *newS = NULL;
	int i = 0;

	strcpy(temp, string);
	
	newS = strtok(temp, sep);
	while(newS != NULL){
		splited[i] = newS;
		newS = strtok(NULL, sep);
		i++;
	}	

	return splited;
}


