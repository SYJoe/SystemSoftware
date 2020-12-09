#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <network.h>
#include <alert.h>
 
#define PIN 28

int endOfSystem = 0;
int threadfinish1 = 999;
int threadfinish2 = 999;

int main()
{
    int return_thrd1;    
    int return_thrd2;
    int return_EOS;

    pthread_t thread_1; // waveDetection, transferSignalToSystem
    pthread_t thread_2; // waveSignaltoOtherSystem, alert
    pthread_t thread_3; // thread for server.blockModule
    
    pthread_create(&thread_1, NULL, detectModule, NULL);
    pthread_create(&thread_2, NULL, readToOtherSystem, NULL);
    pthread_create(&thread_3, NULL, blockModule, NULL);

    pthread_join(thread_1, (void **)&return_thrd1);
    pthread_join(thread_2, (void **)&return_thrd2);

    while(1)
    {
        if(return_thrd1 == 0 || return_thrd2 == 0)
        {
            pthread_create(&thread_1, NULL, main_buzzer, NULL);
            pthread_create(&thread_2, NULL, main_lcd, NULL);

            pthread_join(thread_1, (void **)&return_EOS);

            if(return_EOS == 119)
            {
                return 1;
            }
        }
    }
    return 0;
}