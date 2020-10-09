//Audrey Lane CST221 Producer and Consumer code without the use of sychronization 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h> //sleep function
#include <errno.h>
#define MAX 100 //constant 

int produce();
void put();
void *producer();
void *consumer();
void consume();
int get();
int buffer[MAX]; //constrained by stack

int theProduct;

void *producer() {
	int p; //P is what will be produced 
	while(1) {
		p = produce();
		put(p);
		sleep(1); //sleep for 1 second
	}
}
void *consumer() {
	int p;
	while(1) {
		p = get(); 
		consume(p); //P will be consumed 
		sleep(1); //will fall asleep
	}
}
int produce() {
	return theProduct +1;
}
void consume(int p) {
	printf("Consumed: %i\n",p); //prints Consumed and the char
}
void put(int p) {
	theProduct = p;
	printf("Produced: %d\n", p); //prints Produced and the char
	return;
}
int get() {
	return theProduct; 
}
void main() {
	pthread_t threads[2];
	pthread_create(&threads[0], 0, consumer, 0); //calling process of new thread
	pthread_create(&threads[1], 0, producer, 0);
	pthread_join(threads[0], 0);
	pthread_join(threads[1], 0);
}

