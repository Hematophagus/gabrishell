#include <iostream>
#include <cstring>
#include <cstdlib>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <curses.h>
#include <term.h>

using namespace std;

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

	char buffer[255];
	pid_t pid;
	int status;

	while(true){
		clear();
		push(2);
		cout << "GABRISHELL";
		push(7);
		cout << ":" ;
		pop();

		cin >> buffer;

		pid = fork();
		if(pid == -1){
			push(1);
			perror("[ERRO] Não foi possível criar um novo processo");
			pop();
		}else{
			if(pid == 0){
				if(!strcasecmp(buffer, "pwd")){	
					if(getcwd(buffer, (sizeof(buffer))) != NULL)
						cout << buffer << "\n";
					else{
						push(1);
						perror("[ERRO] Não foi imprimir o diretório atual");
						pop();
					}			
				}
				_exit(EXIT_SUCCESS);
				
			}

			if(pid > 0){
	
				(void)waitpid(pid, &status, 0);

			}

			if(!strcasecmp(buffer, "exit"))
				exit(EXIT_SUCCESS);
		
		}
	
	}
	return 0;
}


