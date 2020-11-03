#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void receive_message (mqd_t mq1);
void sigacter();

int main ()
{	
	mq_unlink ("/serverqueue");// if the queue with this name exist we must delete it  
	
	struct mq_attr mq1_inf ; // The parametrs , of queue, which I want
	
	struct sigaction sa;

	sa.sa_handler = sigacter;
	sa.sa_flags = SA_RESTART;
	printf("%d", getpid());
	sigaction(SIGTERM, &sa, NULL);
	
	mq1_inf.mq_maxmsg = 10;
	mq1_inf.mq_msgsize = 128; 
	mq1_inf.mq_curmsgs = 0;

	mqd_t mq1 = mq_open ("/serverqueue", O_RDWR | O_CREAT , 0644, &mq1_inf);
	
	if(mq1 == -1)
	{
		perror("Failed to create");
 		exit(1);
	}
	
	while(1){
		mq_getattr(mq1, &mq1_inf); //we look if somebody send message

		if(mq1_inf.mq_curmsgs == 2){
			receive_message(mq1);
		}
	}

	

	
	return 0;
}

void receive_message(mqd_t mq1)
{
	char msg_len [128] ;
	char letter[128];


	int p = mq_receive(mq1, msg_len, 129, NULL);// in this message server will get message len, I use p, because errno doent always work 
	
	if ( p == -1){
		perror ("The Server was falled");
		exit(1);
	} 
	
	p = mq_receive (mq1, letter , 129, NULL); 
		
	if ( p == -1){
		perror ("The Server was falled");
		exit(1);
	} 
	
	int len = atoi (msg_len); //The len of message 

	for (int i =0; i < len; ++i) //print message
	{
		printf("%c", letter[i]);
	}
	
	printf("\n"); 
}

void sigacter()
{
	mq_unlink("/serverqueue");
	exit(1);
}
	


