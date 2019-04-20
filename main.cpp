#include "headers.h"

using namespace std;

int main(){
	char *buffer = new char[PATH_MAX];
	pid_t pid;
	int status;

	setupterm(NULL, STDOUT_FILENO, NULL);
	putp(exit_attribute_mode);
	system("clear");
	
	while(true){
		push(2);
		cout << "GABRISHELL";
		push(7);
		cout << ":" ;
		pop();

		cin.getline(buffer, PATH_MAX-1);	

		if(strstr(buffer, " | ") != NULL)
			pipemode(buffer);
		else if(!strcasecmp(buffer, "pwd"))
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
