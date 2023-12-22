#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(int argc[] , char *argv[])
{
    int pid1, pid2;
    pid1 = fork();
    if (pid1 < 0) {
        fprintf(stderr, "\nОшибка при создании первого дочернего процесса.\n");
        return 1;
    }
    else if (pid1 == 0) {
    	printf("\nДочерний процесс : %d", getpid()); 
    	print_time();
    }
    else {
    	pid2 = fork();
    	if (pid1 < 0) {
        	fprintf(stderr, "\nОшибка при создании первого дочернего процесса.\n");
        	return 1;
        }
    	else if (pid2 == 0) {
    		printf("\nДочерний процесс : %d", getpid()); 
    		print_time();
    	}
    	else {
    		printf("\nРодительский процесс : %d", getpid()); 
    		print_time();
    		
    		wait(NULL);
            wait(NULL);
          
        	system("ps -x");
        	char str[100];
			sprintf(str, "ps -fC 1.exe");	
        	system(str);
        }
    }
}

void print_time() {
	struct timespec ts;
    long msec;
    int err = clock_gettime(CLOCK_REALTIME, &ts);
    if (err) {
        perror("clock_gettime");
        return 1;
    }

    // round nanoseconds to milliseconds
    if (ts.tv_nsec >= 999500000) {
        ts.tv_sec++;
        msec = 0;
    } else {
        msec = (ts.tv_nsec + 500000) / 1000000;
    }

    struct tm* ptm = localtime(&ts.tv_sec);
    if (ptm == NULL) {
        perror("localtime");
        return 1;
    }

    char time_str[sizeof("1900-01-01 23:59:59")];
    time_str[strftime(time_str, sizeof(time_str),
            "%H:%M:%S", ptm)] = '\0';

    printf("\n%s:%03li\n", time_str, msec);
}
