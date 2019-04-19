#include <iostream>
#include <cstring>
#include <cstdlib>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fstream>
#include <curses.h>
#include <term.h>

using namespace std;

void pwd();

void ls(char *buffer);

void cd(char *buffer);

void more(char *buffer);

void grep(char *buffer);

//void pipemode(char *buffer);

int numParameters(char *buffer){
	int i = 1;
	char *p = strstr(buffer, " ");
	while(p != NULL){
		p = strstr(&p[1], " ");
		i++;	
	}

	return i;
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

void push(int cor){
	putp(enter_bold_mode);
	putp(tparm(set_a_foreground, cor));
}

void pop(){
	putp(exit_attribute_mode);
}

int main(){
	setupterm(NULL, STDOUT_FILENO, NULL);
	putp(exit_attribute_mode);

	char *buffer = new char[PATH_MAX];
	pid_t pid;
	int status;
	
	while(true){
		clear();
		push(2);
		cout << "GABRISHELL";
		push(7);
		cout << ":" ;
		pop();

		cin.getline(buffer, PATH_MAX-1);	
		/*cout << buffer;
		if(strstr(buffer, " | ") != NULL){
			pipemode(buffer);
		} 
		*/
		if(!strcasecmp(buffer, "pwd"))
			pwd();
		else if(!strncasecmp(buffer, "cd", 2))
			cd(buffer);
		else if(!strcasecmp(buffer, "ls"))
			ls(buffer);
		else if(!strncasecmp(buffer, "more", 4)){
			more(buffer);
		}else if(!strncasecmp(buffer, "grep", 4)){
			grep(buffer);
		}
		if(!strcasecmp(buffer, "exit"))
			exit(EXIT_SUCCESS);	
	}
	return 0;
}

void pwd(){
	char *path = new char[PATH_MAX];
	
	if(getcwd(path, PATH_MAX) != NULL)
		cout << path << "\n";
	else{
		push(1);
		perror("[ERRO] Não foi possível imprimir o diretório atual");
		pop();
	}
	delete []path;
	return;
}

void cd(char *buffer){
	if(strstr(buffer, "\"") != NULL)
		perror("Evite por aspas no caminho");
	else
		chdir(&buffer[3]);
}

void ls(char *buffer){
	pid_t pid = fork();
	int status;
	char **argv = split(buffer);
	
	if(pid != 0)
		waitpid(-1, &status, 0);
	else{
		if(execv("/bin/ls", argv) < 0){
			push(1);
			perror("Impossível executar o comando");
			pop();		
		}
		_exit(EXIT_SUCCESS);	
	}
}

void more(char *buffer){
	pid_t pid = fork();
	int status;
	char **argv = split(buffer);
	
	if(pid != 0)
		waitpid(-1, &status, 0);
	else{
		if(execv("/bin/more", argv) < 0){
			push(1);
			perror("Impossível executar o comando");
			pop();		
		}
		_exit(EXIT_SUCCESS);	
	}

}

void grep(char *buffer){
	pid_t pid = fork();
	int status;
	char **argv = split(buffer);
	
	if(pid != 0)
		waitpid(-1, &status, 0);
	else{
		if(execv("/bin/grep", argv) < 0){
			push(1);
			perror("Impossível executar o comando");
			pop();		
		}
		_exit(EXIT_SUCCESS);	
	}

}

 	
