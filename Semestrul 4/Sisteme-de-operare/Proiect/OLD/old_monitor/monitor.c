#include "monitor.h"

#define MAX_ID_LEN 16
#define MAX_USERNAME_LEN 32
#define MAX_CLUETEXT_LEN 128


typedef struct Coordonata{
    float latitude;
    float longitude;
}Coordonata_T;


typedef struct Treasure{
    char id[MAX_ID_LEN];
    char userName[MAX_ID_LEN];
    Coordonata_T GPSCoordinate;
    char clueText[MAX_CLUETEXT_LEN];
    int value;
}Treasure_T;


void handle_sigterm(int signum){
  if (signum == SIGUSR1) {
    is_running = 1;
  }
  
  /* char message[BUFFER_SIZE];

    // clear current line
    write(STDOUT_FILENO, "\r", 1);

    snprintf(message, sizeof(message), "Received signal %d. Shutting down...\n", signum);

    write(STDOUT_FILENO, message, strlen(message));

    // set the flag to 0
    is_running = 0;*/
}

/*static void setup_sigchld_handler(){
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = SIG_IGN; // ignore child process termination
    sa.sa_flags = SA_NOCLDWAIT; // do not create zombie processes
    sigaction(SIGCHLD, &sa, NULL); // set the signal handler
    }*/

void setup_signal_handlers() {
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    //catch shutdown signal
    sa.sa_handler = handle_sigterm;
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGUSR1, &sa, NULL);
    
    //sigaction(SIGTERM, &sa, NULL);  // catch termination signal
    //sigaction(SIGINT, &sa, NULL);   // catch interrupt signal
    //sigaction(SIGHUP, &sa, NULL);   // catch hangup signal

    // prevent zombie processes

    //setup_sigchld_handler();
}

void list_hunts() {
    DIR *dir = opendir("treasure_hunts");
    if (!dir) {
        write(2, "eroare deschidere director", 26);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path[BUFFER_SIZE];
            snprintf(path, sizeof(path), "treasure_hunts/%s/treasure.bin", entry->d_name);

            struct stat st;
            if (stat(path, &st) == 0) {
                int count = st.st_size / sizeof(struct Treasure);
                printf("Hunt: %s | Treaures: %d\n", entry->d_name, count);
            }
        }
    }

    closedir(dir);
}

void process_command() {
    char buffer[BUFFER_SIZE];

    int fd = open("monitor_command.txt", O_RDONLY);
    if (fd < 0) {
        perror("Nu pot citi fișierul de comandă");
        return;
    }

    ssize_t len = read(fd, buffer, sizeof(buffer) - 1);
    close(fd);

    if (len < 0) {
        perror("Eroare la citire");
        return;
    }

    buffer[len] = '\0';

    if (strcmp(buffer, "stop") == 0) {
      write(1, "Monitor stop command, exit in 5s\n", 33);
      usleep(3000000);
      exit(0);
    } else if (strcmp(buffer, "list_hunts") == 0) {
        list_hunts();
    } else if (strncmp(buffer, "list_treasures ", 15) == 0) {
      char hunt_id[10];
      sscanf(buffer, "list_treasures %s", hunt_id);
      
      pid_t pid = fork();
      if (pid == 0) {
 	  execl(TREASURE_MANAGER_EXEC, TREASURE_MANAGER_EXEC, "--list", hunt_id, NULL);
	  write(2, "eroare execl", 12);
	  exit(1);
      } else {
	  waitpid(pid, NULL, 0);
      }
    } else if (strncmp(buffer, "view_treasure ", 14) == 0) {
        char hunt_id[10], treasure_id[10];
        if (sscanf(buffer + 14, "%s %s", hunt_id, treasure_id) == 2) {
	   pid_t pid = fork();
           if (pid == 0) {
	       execl(TREASURE_MANAGER_EXEC, TREASURE_MANAGER_EXEC, "--view", hunt_id, treasure_id, NULL);
	       write(2, "eroare execl", 12);
	       exit(1);
	   } else {
	       waitpid(pid, NULL, 0);
	   }
	    } else {
	  write(1, "invalid format", 14);
	}
    } else {
      write(1, "Monitor comanda invalida\n", 25);
    }
}