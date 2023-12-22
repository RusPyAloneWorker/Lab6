#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>


int main() {
    char command[200];
    char* args[60];
    
    while (1) {
        printf("Введите команду: ");
        fgets(command, sizeof(command), stdin);
        
        // Удаление символа новой строки из команды
        command[strcspn(command, "\n")] = 0;
        
        // Разделение команды на аргументы
        char* command_word = strtok(command, " ");
        int i = 0;
        
        while (command_word != NULL) {
            args[i++] = command_word;
            // strtok хранит поинтер последнего токена/слова и проходится по command
            command_word = strtok(NULL, " "); 
        }
        
        args[i] = NULL;
       
      	execute_command(args);	
    }
    
    return 0;
}

void execute_command(char* args[]) {
	int pid = fork();
	if (pid < 0) {
		fprintf(stderr, "Ошибка при создании процесса.\n");
		return 1;
	} 
	else if (pid == 0) {
		// Код дочернего процесса
		execvp(args[0], args);
		int result = execvp(args[0], args);
        int error = errno;
		if (result == -1) {
			fprintf(stderr, "Error code: %d\n", error);
			exit(error);
		}
            
		exit(1); // Выходим из дочернего процесса
	} 
	else {
    	wait(NULL); // Родитель ждет выполнение дочернего процесса
	}
}
