#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t chopsticks[5];


void *Phil(void *n)
{
	while (1) {
		int p = *(int *)n;
		int sem_value_right;

		printf("Phil %d  is thinking...\n", p);
		sleep(rand()%4+1);
		printf("Phil %d wants to eat...\n", p);

		// Force the philosopher with the ID 0 to take the right chopstick
		// Thus breaking the Circular wait condition
		if (p == 0) {
			int sem_value_left;
			// Take the right chopstick
			printf("Phil %d is trying to pick the right chopstick...\n", p);
			sem_wait(&chopsticks[(p+1)%5]);
			printf("Phil %d picks the right chopstick...\n", p);

			sem_getvalue(&chopsticks[p], &sem_value_left);
			// Check if the left chopstick is available
			if (sem_value_left == 1) {
				// Take the left chopstick!
				printf("Phil %d is trying to pick the left chopstick...\n", p);
				sem_wait(&chopsticks[p]);
				printf("Phil %d picks the left chopstick...\n", p);

				// Start eating
				printf("=====> Phil %d is eating...\n", p);
				sleep(rand()%5+5);

				// Finish eating
				printf("-------------------------------------------------------------\n");
				printf("Phil %d is putting down the chopsticks...\n", p);
				printf("-------------------------------------------------------------\n");
				// Put down the chopsticks
				sem_post(&chopsticks[(p+1)%5]);
				sem_post(&chopsticks[p]);

			// If the left chopstick is not available!
			} else {
				// If the left is not available then put down the one you hold(left)
				sem_post(&chopsticks[(p+1)%5]);
				sleep(rand()%6+2);
			}
		
		// Other philosopher with ID other tan 0
		} else {
				// Pick the left chopstick
				printf("Phil %d is trying to pick the left chopstick...\n", p);
				sem_wait(&chopsticks[p]);
				printf("Phil %d picks the left chopstick...\n", p);

				sem_getvalue(&chopsticks[(p+1)%5], &sem_value_right);
				// Check if the right chopstick is available
				if (sem_value_right == 1) {
					// Take the right chopstick!
					printf("Phil %d is trying to pick the right chopstick...\n", p);
					sem_wait(&chopsticks[(p+1)%5]);
					printf("Phil %d picks the right chopstick...\n", p);

					// Start eating
					printf("=====> Phil %d is eating...\n", p);
					sleep(rand()%5+5);

					// Finish eating
					printf("-------------------------------------------------------------\n");
					printf("Phil %d is putting down the chopsticks...\n", p);
					printf("-------------------------------------------------------------\n");
					// Put down the chopsticks
					sem_post(&chopsticks[p]);
					sem_post(&chopsticks[(p+1)%5]);

				} else {
					// If the right is not available then put down the one you hold(left)
					sem_post(&chopsticks[p]);
					sleep(rand()%6+2);
			}
		}
	}
}


int main(int argc, char const *argv[])
{
	/* code */
	int n[5];
	pthread_t T[5];
	// Initialize every semaphore variable
	for (int i = 0; i < 5; i++) {
		sem_init(&chopsticks[i], 0, 1);
	}

	// Create the five threads
	for (int i = 0; i < 5; i++) {
		n[i] = i;
		pthread_create(&T[i], NULL, Phil, (void *)&n[i]);
	}

	// Wait for every child to finish
	for (int i =  0; i < 5; i++) {
		pthread_join(T[i], NULL);
	}


	return 0;
}
