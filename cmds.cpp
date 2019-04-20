#include "headers.h"

using namespace std;

void cd(char *buffer){
	if(strstr(buffer, "\"") != NULL){
		push(1);
		perror("Evite por aspas no caminho");
		pop();
	}
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



void pipemode(char *buffer){

	int status, fd[2];
	char **cmd = splitPipe(buffer, "|");	
	cout << cmd[0];
	char *cmdPath = new char[50];
	pid_t pid;
	
	if(!pipe(fd)){
		pid = fork();
		if(pid > 0){
			char **cmd1 = split(cmd[0]);
			strcpy(cmdPath, "/bin/");
			strcat(cmdPath, cmd1[0]);

			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);

			if(execv(cmdPath, cmd1)){
				push(1);
				perror("[Erro] no pipe: processo pai");
				pop();
			}
			int np = numParameters(cmd[1]);
			for(int i = 0; i < np; i++)
				delete []cmd1[i];
			delete []cmd1;			 
		}else if(!pid){
			char **cmd2 = split(cmd[1]);
			strcpy(cmdPath, "/bin/");
			strcat(cmdPath, cmd2[0]);
			
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			
			if(execv(cmdPath, cmd2)){
				push(1);
				perror("Erro no pipe: processo filho");
				pop();
			}
			wait(&status);
			int np = numParameters(cmd[1]);			

			for(int i = 0; i < np; i++)
				delete []cmd2[i];
			delete []cmd2;
		}	
		

	}			
	delete []cmdPath;
	delete []cmd[0];
	delete []cmd[1];
	delete []cmd;
	
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
