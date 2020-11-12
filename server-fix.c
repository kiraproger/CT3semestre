#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#define Q_NAME "/serverqueue"

void sigacter();

int main(){
    mqd_t mq1 = mq_open(Q_NAME, O_CREAT , 0622, NULL); // rw- -w- -w-
    
    if (mq1 == -1 ){
        perror ("Failed to open");
        return 1;
        }
       
    struct mq_attr mq1_inf;
    
    mq_getattr (mq1, &mq1_inf);
    
    long maxlen = mq1_inf.mq_msgsize;
    
    char* message = (char*)malloc(maxlen);
    
    if (message == NULL){
    	printf("server fallen, invalid try to creat buf \n");
    	mq_close (mq1);
    	mq_unlink (Q_NAME);
    	return 1;
    	}
    	
    struct sigaction sa;
    
    sa.sa_handler = sigacter;
    sa.sa_flags = 0;
    
    sigaction(SIGINT, &sa, NULL);
    
    while (1){
    	ssize_t cur_len = mq_receive(mq1, message, maxlen, NULL);
    	
    	if (errno == EINTR)
    	    break;
    	    
    	    
    	if (cur_len == -1){
    	    perror("Failed to receive");
    	    break;
    	}
    	
    	ssize_t written_bytes = write(STDOUT_FILENO, message, cur_len );
    	
    	if (written_bytes != cur_len || written_bytes == -1){
    	    perror( "Failed to write");
    	    break;
	}
    	
    	printf ("\n");
    	
    	}
    	
    mq_close (mq1);
    mq_unlink (Q_NAME);
    return 1;
    }
    
void sigacter(){
}
    
    	
    
    
    
