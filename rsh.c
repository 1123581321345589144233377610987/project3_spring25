#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// TODO
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
	for(unsigned int i =0;i<N;i++){
		if(!strcmp(allowed[i],cmd)){
			return 1;
		}
	}
	return 0;
}

int findCMD(char* command){
    int i = 0;
    while(allowed[i]){
        if(!strcmp(command, allowed[i])){
            return i;
        }
        i++;
    }
    return -1;
}

int main() {

    // TODO
    // Add variables as needed

    char line[256];

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	char* arrline[21];
	for(unsigned int i=0;i<21;i++){
		arrline[i]=NULL;
	}

	char* token = strtok(line, " ");

   // loop through the string to extract all other tokens
   unsigned int idx=0;
   while( token != NULL ) {
      arrline[idx]=token; 
      token = strtok(NULL, " ");
	  idx++;
   }
   char* command=arrline[0];

	// TODO
	// Add code to spawn processes for the first 9 commands
	// And add code to execute cd, exit, help commands
	// Use the example provided in myspawn.c
	int index;
	pid_t pid;
	int status;
	posix_spawnattr_t attr;
	posix_spawnattr_init(&attr);
	index = findCMD(command);
	int numargs=-1;
	for(unsigned int i=0;i<21;i++){
		if(arrline[i]==NULL){
			break;
		}
		numargs++;
	}

        switch(index){
			//cp
            case 0: 
				if (posix_spawnp(&pid, "cp", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
			//touch
            case 1: 
				if (posix_spawnp(&pid, "touch", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
			//mkdir
            case 2:  
				if (posix_spawnp(&pid, "mkdir", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
            
				//ls
			case 3: 
				if (posix_spawnp(&pid, "ls", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
            
			//pwd
			case 4: 
				if (posix_spawnp(&pid, "pwd", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
            
			//cat
			case 5: 
				if (posix_spawnp(&pid, "cat", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
            
			//grep
				case 6: 
				if (posix_spawnp(&pid, "grep", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}	
				break;
            
			//chmod
			case 7: 
				if (posix_spawnp(&pid, "chmod", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
            
			//diff
			case 8: 
				if (posix_spawnp(&pid, "diff", NULL, &attr, arrline, environ) != 0) {
					perror("spawn failed");
					exit(EXIT_FAILURE);
				}
				break;
            
			//cd
			case 9: 
				if(numargs>1){
					printf("-rsh: cd: too many arguments\n");
					break;
				}
				chdir(arrline[1]);
				break;
			
			//exit
			case 10: return 0;
			
			//help
			case 11: 
				printf("The allowed commands are:\n");
				for(unsigned int i=0;i<N;i++){
					printf("%u: %s\n", i+1, allowed[i]);
				}
				break;
			default: printf("NOT ALLOWED!\n");
        }
		// Wait for the spawned process to terminate
		if(index<9){
			if (waitpid(pid, &status, 0) == -1) {
				perror("waitpid failed");
			}
		
		
			// Destroy spawn attributes
			posix_spawnattr_destroy(&attr);
		}
    }
	return EXIT_SUCCESS;
}
