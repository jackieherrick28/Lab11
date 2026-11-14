/**************************************************************************************************************************************
* Filename: Lab11.c
* Class: CPE 2600 121
* Description: A program in the starter repository (mandel) has been provided that features a command line interface which allows 
*              adjustment of various parameters and will then generate a Mandelbrot set visualization and save it to a jpeg file. 
* Author: Jackie Herrick
* Date: 11/14/26
*
* gcc Lab11.c -o Lab11 -lm
* ffmpeg -i mandel%d.jpg mandel.mpg 
**************************************************************************************************************************************/#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <getopt.h>
#include <math.h>

#define FRAMES 50 // 50 frame as defined in Lab document
double s = 1;
int main(int argc, char *argv[])
{
    int max_process = 1; //default number of processors is 1
    int active = 0; //tracks the processor being used
    int frame = 0; // Keeps track of what frame we are on.

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
                char scale[32];

                snprintf(output, sizeof(output), "frame%03d.jpg", frame);

                double scale_value = 4.0 * pow(0.9, frame);

                snprintf(scale, sizeof(scale),  "%f", scale_value);

                execl("./mandel", "mandel",  "-x", "-0.75",  "-y", "0.10",  "-s", scale,   "-o", output, (char *)NULL);

                perror("execl");
                exit(1);
            }
            //increments active and frame
            active++;
            frame++; 
            s++;
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