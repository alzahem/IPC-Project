
// sender.cpp

#include <sys/shm.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "msg.h"    /* For the message struct */

// Headers added
#include <iostream>

/* The size of the shared memory chunk */
#define SHARED_MEMORY_CHUNK_SIZE 1000

/* The ids for the shared memory segment and the message queue */
int shmid, msqid;

/* The pointer to the shared memory */
void* sharedMemPtr;

/**
 * Sets up the shared memory segment and message queue
 * @param shmid - the id of the allocated shared memory 
 * @param msqid - the id of the shared memory
 */

void init(int& shmid, int& msqid, void*& sharedMemPtr)
{
	/* TODO: 
        1. Create a file called keyfile.txt containing string "Hello world" (you may do
 		    so manually or from the code).
	    2. Use ftok("keyfile.txt", 'a') in order to generate the key.
		3. Use the key in the TODO's below. Use the same key for the queue
		    and the shared memory segment. This also serves to illustrate the difference
		    between the key and the id used in message queues and shared memory. The id
		    for any System V objest (i.e. message queues, shared memory, and sempahores) 
		    is unique system-wide among all SYstem V objects. Two objects, on the other hand,
		    may have the same key.
		4. Delete all TODOs when program is fully working and beautify code. 
	 */


	// Use ftok in order to generate the key
	key_t key = ftok("keyfile.txt", 'a');

	/* TODO: Get the id of the shared memory segment. The size of the segment must be SHARED_MEMORY_CHUNK_SIZE */
	shmid = shmget(key, SHARED_MEMORY_CHUNK_SIZE, 0666|IPC_CREAT);

	/* TODO: Attach to the shared memory */
	sharedMemPtr = (char*) shmat(shmid,(void*)0, 0666);

	/* TODO: Attach to the message queue */
	msqid = msgget(key, 0666|IPC_CREAT);


	/* Store the IDs and the pointer to the shared memory region in the corresponding parameters */
	
}

/**
 * Performs the cleanup functions
 * @param sharedMemPtr - the pointer to the shared memory
 * @param shmid - the id of the shared memory segment
 * @param msqid - the id of the message queue
 */

void cleanUp(const int& shmid, const int& msqid, void* sharedMemPtr)
{
	/* TODO: Detach from shared memory */
	shmdt(sharedMemPtr);
}

/**
 * The main send function
 * @param fileName - the name of the file
 */
void send(const char* fileName)
{
	/* Open the file for reading */
	FILE* fp = fopen(fileName, "r");
	

	/* A buffer to store message we will send to the receiver. */
	message sndMsg; 
	
	/* A buffer to store message received from the receiver. */
	message rcvMsg;
	
	/* Was the file open? */
	if(!fp)
	{
		perror("fopen");
		exit(-1);
	}
	
	/* Read the whole file */
	while(!feof(fp))
	{
		/* Read at most SHARED_MEMORY_CHUNK_SIZE from the file and store them in shared memory. 
 		 * fread will return how many bytes it has actually read (since the last chunk may be less
 		 * than SHARED_MEMORY_CHUNK_SIZE).
 		 */
		if((sndMsg.size = fread(sharedMemPtr, sizeof(char), SHARED_MEMORY_CHUNK_SIZE, fp)) < 0)
		{
			perror("fread");
			exit(-1);
		}
		
			
		/* TODO: Send a message to the receiver telling him that the data is ready 
 		 * (message of type SENDER_DATA_TYPE) 
 		 */

		sndMsg.mtype = SENDER_DATA_TYPE;
		std::cout << "\nSending message to the reciever. ";

		// If the message was not sent, throw an error, else "msg sent"
		if(msgsnd(msqid, &sndMsg, sizeof(sndMsg) - sizeof(long), 0) == -1){
			perror("Error, the sender could not send the message. \n");
		} 
		else {
			std::cout << "Message successfully sent. \n\n";
		}


		/* TODO: Wait until the receiver sends us a message of type RECV_DONE_TYPE telling us 
 		 * that he finished saving the memory chunk. 
 		 */
		std::cout << "\nMessage recieved. \n";
		if(msgsnd(msqid, &sndMsg, sizeof(sndMsg), 0) == -1){
			perror("Error, reciever did not recieve the message. \n");
		}
		else {
			std::cout << "Message successfully recieved. \n\n";
		}

	

	/** TODO: once we are out of the above loop, we have finished sending the file.
 	  * Lets tell the receiver that we have nothing more to send. We will do this by
 	  * sending a message of type SENDER_DATA_TYPE with size field set to 0. 	
	  */

	sndMsg.size = 0;
	sndMsg.mtype = SENDER_DATA_TYPE;
	printf("\nThere is nothing else to send. \n");
	printf("Message Type: %ld - Size of Message: %d\n", rcvMsg.mtype, rcvMsg.size);
	printf("DEBUG: Message Struct Size %lu\n", sizeof(rcvMsg) - sizeof(long));

	if(msgsnd(msqid, &sndMsg, sizeof(sndMsg) - sizeof(long), 0) == -1)
	{
		perror("Error, message was unable to send. ");
	}
	printf("The message was successfully sent. \n");

	/* Close the file */
	fclose(fp);
	
	}
}
int main(int argc, char** argv)
{
	
	/* Check the command line arguments */
	if(argc < 2)
	{
		fprintf(stderr, "USAGE: %s <FILE NAME>\n", argv[0]);
		exit(-1);
	}
		
	/* Connect to shared memory and the message queue */
	init(shmid, msqid, sharedMemPtr);
	
	/* Send the file */
	send(argv[1]);
	
	/* Cleanup */
	cleanUp(shmid, msqid, sharedMemPtr);


	std::cout << "\n\nEND OF SENDER_CPP\n\n";

	return 0;
}
