#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t forks[5]; //five forks so five semaphores
int n[5];
pthread_t philo[5]; //every philosopher with one thread

void*eat(void*n)
{
  int ph =* (int*)n; //just a counter fpr philosopher and forks
  int hi = (ph+1)%5;
  printf("Philosopher %d is thinking \n",ph);
  sleep(1);
  if(ph%2==0)
  {
    sem_wait(&forks[ph]);
    sem_wait(&forks[hi]);
  }
  else if(ph%2!=0)
  {
    sem_wait(&forks[hi]);
    sem_wait(&forks[ph]);
  }
  printf("philosopher %d eats\n",ph);
  sleep(2);
  printf("philosopher %d finished eating\n",ph);
  sem_post(&forks[hi]);
  sem_post(&forks[ph]);
}

int main() {
  for(int i = 0;i<5;i++)
    {
      n[i] = i;
      sem_init(&forks[i],0,1);
    }
  for (int i = 0; i<5 ;i++)
    {
        pthread_create(&philo[i],NULL,eat,(void*)&n[i]);
    }
  for (int i =0; i<5;i++)
    {
      pthread_join(philo[i],NULL);
    }
  
}