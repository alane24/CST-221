//Audrey Lane CST 221
// This program is to show deadlocks entering and exiting from sleep. 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

pthread_t tid[5];
pthread_mutex_t lock;
int counter;
int thread_id [5];
int shared_data = 20;
FILE * file;

void* test(){
	pthread_mutex_lock(&lock);
	counter += 1;
	printf("Process %d accessed counter %d \n", getpid(), counter);
	sleep(3);
	printf("Process %d closing.\n", counter);
	pthread_mutex_unlock(&lock);
	return NULL;
}

void* processFunction (){
	char message [100];
	strcpy(message, "Process %d accessed the shared resource, num: %d \n");
	printf(message, getpid(), shared_data);
	sleep((int)0.2);
	fprintf(file, message, getpid(), shared_data);
	pthread_mutex_unlock(&lock);
	return NULL;
}

void* testLock(){
	clock_t start_clock = clock();
	char message [100];
	counter += 1;
	thread_id[counter] = counter;
	while (!pthread_mutex_trylock(&lock))
{
		if ((clock() - start_clock) > 2)
		{
			strcpy(message, "Resource %d is now starved going to sleep.\n");
			printf(message, getpid());
			fprintf(file, message, getpid());
			sleep(2);
			strcpy(message, "Resource %d has woken from sleep. \n");
			printf(message, getpid());
			fprintf(file, message, getpid());
			start_clock = clock();
		}
	}

	processFunction();
	
}

void* test_call_one (){
	int i = 0;
	int y = 0;
	file = fopen("dl.txt" , "w"); //creates txt of output
	pthread_mutex_init(&lock, NULL);
	
	while (i < 5) {
		pthread_create(&(tid[i]), NULL, &testLock, NULL);
		i++;
	}
	while (y < 5) {
		pthread_join(tid[y], NULL);
		y++;
	}
	
	pthread_mutex_destroy(&lock);
	
}

void* thread_function (){

	clock_t start_clock = clock();
	char message [100];
	printf("Counter increment: %d\n", ++counter);
	fprintf(file, "Counter increment: %d\n", ++counter);
	while (!pthread_mutex_trylock(&lock))
	{
	
		if((clock() - start_clock) > 2)
		{
			strcpy(message, "Resource %d now starved going to sleep.\n");
			printf(message, getpid());
			fprintf(file, message, getpid());
			printf("counter increment inside: %d\n", ++counter);
			fprintf(file, "Counter increment: %d\n", ++counter);
			sleep(2);
			strcpy(message, "Resource %d has woken from sleep. \n");
			printf(message, getpid());
			fprintf(file, message, getpid());
			
			start_clock = clock();
	}
}	
	strcpy(message, "Process %d accessed the shared resource, num: %d \n");
	printf(message, getpid(), shared_data);
	sleep((int)0.2);

	fprintf(file, message, getpid(), shared_data);
	pthread_mutex_unlock(&lock);
	printf("Counter increment: %d\n", ++counter);
	fprintf(file, "Counter increment: %d\n", counter);
}

void* access_resource (){
	pthread_t thread;
	pthread_create(&thread, NULL, thread_function(), NULL);
}
void* test_call_two (){
	file = fopen("DLOutput.txt", "w"); //creates txt of output
	pthread_mutex_init(&lock, NULL);
	fork();
	fork();
	access_resource();
}
int main (void){
	test_call_one();
	test_call_two();
	return 0;
}
	
