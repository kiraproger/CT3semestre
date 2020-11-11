#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void sigacter();

int main(){
    mqd_t mq1 = mq_open("/serverqueue", O_CREAT , 0622, NULL); // rw- -w- -w-
    
    if (mq1 == -1 ){
        perror ("Failed to open");
        exit (1);
        }
       
    struct mq_attr mq1_inf;
    
    mq_getattr (mq1, &mq1_inf);
    
    long maxlen = mq1_inf.mq_msgsize;
    
    char* message = (char*)calloc (maxlen, sizeof(char));
    
    if (message == NULL){
    	printf("server fallen, invalid try to creat buf \n");
    	mq_unlink ("/serverqueue");
    	exit (1);
    	}
    	
    struct sigaction sa;
    
    sa.sa_handler = sigacter;
    sa.sa_flags = 0;
    
    sigaction(SIGTERM, &sa, NULL);
    
    while (1){
    	size_t cur_len = mq_receive(mq1, message, maxlen, NULL);
    	if (cur_len == -1){
    	    mq_unlink ("/serverqueue");
    	    perror("Failed to receive");
    	    exit (1);
    	    }
    	
    	ssize_t written_bytes = write( 1, message, cur_len );
    	
    	if (written_bytes != cur_len){
    		perror( "Failed to write");
    		mq_unlink ("/serverqueue");
    		exit(1);}
    	
    	
    	
    	printf ("\n");
    	
    	}
    	
    return 0;
    }
    
   void sigacter()
{
	mq_unlink ("/serverqueue");
	exit(1);
}
	  
    
    
    	
    
    
    
