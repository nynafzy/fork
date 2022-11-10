#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void sigint_handler(int sig)
{
	printf("Ctrl + C Error! Don't Press\n");
}


int getNumber() {
	int number;


	printf("Insert a number : ");


	scanf("%d", &number);

	return number;
}


int checkEven(int number) {
	int n, i, flag = 0, status = 0;
	n = number;

	for (i = 2; i <= n / 2; ++i)	{

		if(n % i ==0) {
		  flag = 1;

		  break;
		}
	}

	if(n == 1) {
		status = 0;
	}
	else {
		if(flag == 0)
		  status = 1;
		else
		  status = 2;
	}

	return status;
}


int main(void)	{

	printf("\n=[Hi,Let me guess is it Odd or Even numbers]=\n");

	int fd[2];
	pipe(fd);
	pid_t pid = fork();



	void sigint_handler(int sig);


	if(signal(SIGINT, sigint_handler) == SIG_ERR) {
		perror("signal");
		exit(1);
	}


	if(pid > 0) {

	  close(fd[1]);

	  int sNumber;
	  read(fd[0], &sNumber, sizeof(sNumber));
	  close(fd[0]);

	  printf("Processing numbers..\n");
	  wait(NULL);
	  int status = checkEven(sNumber);

	  if(status == 0)
		printf("Invalid number !\n\n");
	  else if(status == 1)
		printf("%d is an Odd Number.\n\n", sNumber);
	  else if(status == 2)
		printf("%d is an Even Number.\n\n", sNumber);

	}


	if(pid == 0) {

	  close(fd[0]);


	  int number = getNumber();
	  write(fd[1], &number, sizeof(number));
	  close(fd[1]);

	  exit(EXIT_SUCCESS);
	}

	return EXIT_SUCCESS;
}
