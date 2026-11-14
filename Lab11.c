#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>

#define FRAMES 50// 50 frame as defined in Lab document

int main(int argc, char *argv[])
{
    int max_process = 1; //default number of processors is 1
    int active = 0;//tracks the processor being used
    int frame = 0;// Keeps track of what frame we are on.

    //User inputs number of processes and checks if there there is a number
    if(argc < 2)
    {
        fprintf(stderr, "Usage %s number of processes\n",argv[0]);
        return 1;
    }
    max_process = atoi(argv[1]);

    //Checks if the Processes are between 1 to 50 per Lab document
    if(max_process < 1 || max_process > FRAMES)
    {
        fprintf(stderr, "Processes must be between 1 and 50\n");
        return 1;
    }

    //Launches children while slots are avaible
    while(frame < FRAMES || active > 0)
    {
        while(frame < FRAMES && active < max_process)
        {
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("fork");
                break;
            }

            //Child Process
            if(pid == 0)
            {
                char output[64];
                snprintf(output, sizeof(output), "frame%03d.jpg", frame);
                execl("./mandel","mandel","-o",output, (char *)NULL);
                perror("execl");
                exit(1);
            }
            //increments active and frame
            active++;
            frame++; 
        }

        //Wait for child to finish
        if(active > 0)
        {
            int status;
            pid_t finish = wait(&status);

            if(finish > 0)
            {
                active--;
            }
        }

    }

    printf("Finished generating %d frames.\n", FRAMES);
    return 0;

}