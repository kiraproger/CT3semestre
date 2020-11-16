#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <semaphore.h>

int result = 0; // to which second thread will be increment

sem_t execsem ; //to control what thread will be executed
 
void* second_thread (void* param);

int main(){

    sem_init (&execsem, 0, 1);
    pthread_t thread; //second thread id
    
    char c ; //to communicate with user
    
    printf("The count of result is executing\n");
    printf("Type 'p' to see the current result\n");
    printf("Type 's' to finish programm\n");
 
    errno = pthread_create(&thread, NULL, second_thread, NULL);
    if (errno != 0){
    	perror("Failed to create new thread");
    	sem_close (&execsem);
    	return 1;
    	}
    	
    while(1){
    	
        scanf("%c",&c);
        sem_wait(&execsem);
    
        if (c != 'p' && c != 's'){
            printf("Please type 'p' or 's'\n");
            sem_post(&execsem);
        }
        
        if(c == 'p'){
            printf("The current result is %d\n", result);
            sem_post(&execsem);
        }
        
        if(c == 's'){
    	    printf("The process is finished with result : %d\n", result);
    	    sem_close (&execsem);
    	    pthread_cancel(thread);
    	    return 0;
    	 }
    	 }
        
    
    	
   
}

void* second_thread (void* param){
    while(1){
        sem_wait(&execsem);//entrance to critical section
        ++result;
        sem_post(&execsem);
        } 
   }
        
        

