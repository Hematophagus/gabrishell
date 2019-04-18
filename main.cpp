#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(){
	char buffer[255];
	pid_t pid;

	while(true){
		cout << "INTERPERTADOR DE COMANDOS FODA ";
		cin >> buffer;
		if(!strcasecmp(buffer, "pwd")){
			pid = fork();
			if(pid == -1){
				perror("Nao Consegui Criar o Processo Filho, malz :/\n");
				exit(EXIT_FAILURE);
			}
			else if(pid == 0){
				if(getcwd(buffer, (sizeof(buffer))) != NULL)
					cout << buffer << "\n";
				else
					cout << "Deu Ruim ó\n";
				_exit(EXIT_SUCCESS);
			}
			else{
				int status;
				(void)waitpid(pid, &status, 0);
			}
			return EXIT_SUCCESS;
		}
	}
	return 0;
}


