#include <pthread.h> 
#include <stdio.h>
#include <errno.h>

void* count(void* arg)  
{
    *(int*)arg = *(int*)arg + 2;
} 

int main(){
    int numbers[10];
    pthread_t threads[10];
    for (int i = 0; i < 10; ++i)
        numbers[i] = i + 1;
        
    for (int i = 0; i < 10; ++i){
        errno = pthread_create (threads + i, NULL, count, numbers + i);
        if (errno != 0){
            perror("Failed to create pthread");
            return 1;}}
            
    for (int i = 0; i < 10; ++i)
        pthread_join(threads[i], NULL);
        
    int summ = 0;
    
    for (int i = 0; i < 10; ++i)
        summ = summ + numbers[i];
      
    printf("%i\n", summ);
    
    return 0;
}
        
        
        
        
        
    
	

        

