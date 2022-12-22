#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


#define n  5
int think  = 2;
int hungry = 1;
int eat = 0;
int leftfork ;
int rightfork;
int bowls[2];
int state[5];
int phil[5] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t philo[5];
sem_t katora;

void test(int phnum)
{
	if (state[phnum] == 1 && state[(phnum + 4) % n] != 0 && state[(phnum + 1) % n] != 0) {
		state[phnum] = 0;
		sleep(2);
		printf("Philosopher %d is Eating\n", phnum + 1);
		sem_post(&philo[phnum]);
	}
}

void take_fork(int phnum)
{
	sem_wait(&mutex);
	state[phnum] = 1;
	test(phnum);
	sem_post(&mutex);
	sem_wait(&philo[phnum]);
	sleep(1);
}

void put_fork(int phnum)
{

	sem_wait(&mutex);
	state[phnum] = 2;
	printf("Philosopher %d is thinking\n", phnum + 1);
	test((phnum + 4) % n);
	test((phnum + 1) % n);

	sem_post(&mutex);
}

void* philosopher(void* num)
{

	while (1) {
		int* i = num;
		sleep(1);
		take_fork(*i);
    sem_wait(&katora);
		sleep(0);
    sem_post(&katora);
		put_fork(*i);
	}
}

void initialisation()
{
    sem_init(&katora,0,2);
    for (int i = 0; i < n; i++)
		sem_init(&philo[i], 0, 0);
}

void creatandjoin()
{
  pthread_t thread_id[n];
  for (int i = 0; i < n; i++) {


		pthread_create(&thread_id[i], NULL,
					philosopher, &phil[i]);

		printf("Philosopher %d is thinking\n", i + 1);
	}

  for (int i = 0; i < n; i++){

		pthread_join(thread_id[i], NULL);
    }
}

int main()
{
	int i;
	sem_init(&mutex, 0, 1);
	initialisation();
  creatandjoin();	
}

