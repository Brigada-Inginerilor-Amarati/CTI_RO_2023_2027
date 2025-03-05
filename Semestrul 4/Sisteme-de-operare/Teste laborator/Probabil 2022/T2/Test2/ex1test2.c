#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFSIZE 4096
int main(int argc, char * argv[])
{
	int pfd1[2];
	int pfd2[2];
	pid_t child;
	if(argc!=2)
	{
		dup2(1,2);
		printf("Eroare la numarul de argumente\n Usage %s intrare.fis\n",argv[1]);
		exit(1);
	}

	if(pipe(pfd1)<0)
	{
		printf("Eroare la crearea pipe-ului\n");
		exit(2);
	}
	if(pipe(pfd2)<0)
	{
		printf("Eroare la crearea pipe-ului\n");
		exit(2);
	}

	if((child=fork())<0)
	{
		printf("Eroare la creerea procesului\n");
		exit(3);
	}
	else
		if(child==0)
		{
			close(pfd1[1]);
			close(pfd2[0]);
			dup2(pfd2[1],1);
			dup2(pfd1[0],0);

			execlp("grep","grep","[A-Z]",NULL);

			printf("Eroare la executarea execlp in fiu\n");
			close(pfd1[0]);
			close(pfd2[1]);
			exit(6);

		}
		else
		{	close(pfd1[0]);
			close(pfd2[1]);
			char *buff=malloc(sizeof(char)*BUFSIZE);

			int fd;
			if((fd=open(argv[1],O_RDONLY))<0)
			{
				printf("Eroare la deschiderea fisierului\n");
				exit(4);
			}

			int n;

			while((n=read(fd,buff,BUFSIZE)))
			{
				if(write(pfd1[1],buff,n)<0)
				{
					printf("Eroare la scrierea in pipe\n");
					exit(6);
				}
			}
			close(pfd1[1]);
			pid_t wpid;
			int info;
			wpid=wait(&info);
			if(WIFEXITED(info))
				printf("Procesul fiu cu PID-ul <%d> s-a incheiat cu codul <%d>\n",wpid,WEXITSTATUS(info));
			else
				printf("Child ended abnormally\n");

			dup2(pfd2[0],0);
			execlp("wc","wc","-l",NULL);
			printf("Eroare la execlp in tata\n");
			close(pfd2[0]);
			exit(8);
			free(buff);
		}

	return 0;
}