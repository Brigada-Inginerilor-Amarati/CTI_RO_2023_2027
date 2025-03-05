#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#define SIZEBUF 4096

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		printf("Eroare la nr de argumente\nUsage %s fisier\n",argv[0]);
		exit(1);
	}

	int pfd1[2];

	int pfd2[2];

	if(pipe(pfd1)<0)
	{
		printf("Eroare la creerea pipe-ului\n");
		exit(2);
	}

	if(pipe(pfd2)<0)
	{
		printf("Eroare la creerea pipe-ului\n");
		exit(2);
	}

	struct stat info;

	if(lstat(argv[1],&info)<0)
	{
		printf("Eroare la lstat\n");
		exit(3);
	}

	if(!S_ISREG(info.st_mode))
	{
		printf("NU este un fisier obisnuit\n");
		exit(4);
	}

	pid_t child;

	if((child=fork())<0)
	{
		printf("Eroare la creerea procesului\n");
		exit(5);
	}
	else
		if(child==0)
		{	
			char **vect;
			vect=malloc(sizeof(char*)*20);

			for(int k=0;k<20;k++)
				vect[k]=malloc(sizeof(char)*20);
				strcpy(vect[0],"./ex2bashtest2.sh");
			close(pfd1[1]);
			close(pfd2[0]);
			char c;

			int i=1;
			
			
			while(read(pfd1[0],&c,1))
			{	
				if(c>='0' && c <= '9')
				{	
					vect[i][0]=c;
					
					i++;		
				}
			}
			vect[i]=NULL;
			
			
			
			dup2(pfd2[1],1);

			
			execvp(vect[0],vect);
			

			printf("Eroare la executia programului execlp din fiu\n");

			close(pfd1[0]);
			close(pfd2[1]);

			exit(0);

		}
		else
		{
			close(pfd1[0]);
			close(pfd2[1]);
			int fd;

			if((fd=open(argv[1],O_RDONLY))<0)
			{
				printf("Eroare la deschiderea fisierului\n");
				exit(6);
			}

			char *buf = malloc(sizeof(char)*SIZEBUF);

			int n;

			while((n=read(fd,buf,SIZEBUF)))
			{	
				if(write(pfd1[1],buf,n)<0)
				{
					printf("Eroare la scrierea in pipe parinte\n");
					exit(7);
				}

			}
			close(pfd1[1]);

			pid_t wpid;
			
			int st;

			wpid=wait(&st);

			if(WIFEXITED(st))
				printf("Procesul fiu cu PID-ul %d s-a incheiat cu codul %d\n",wpid,WEXITSTATUS(st));
			else
				printf("Child ended abnormally\n");
			
			
			char *s=malloc(sizeof(char)*100);

			while(read(pfd2[0],s,SIZEBUF))
			{
				printf("media=%s\n",s);
			}
			close(pfd2[0]);
			
			printf("Father ended succesfully\n");
			free(s);
			free(buf);
			exit(0);
		}



	return 0;
}