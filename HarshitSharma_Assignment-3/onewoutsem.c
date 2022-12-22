#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int philo[5] = {0,1,2,3,4};
int kaantein[5] = {0,0,0,0,0};
int leftfork;
int rightfork;
int busy = 1;
int vella = 0;
int n[5];
pthread_t dhaage[5];

void thinking(int ph)
{
  printf("Philosopher %d is thinking\n",ph);
}
void eating(int ph)
{
  printf("Philosopher %d is eating\n",ph);
  sleep(1);
}

void*think(void*n)
{
  int ph =* (int*)n;
  thinking(ph);
  if(kaantein[ph]==vella && kaantein[(ph+1)%5]==vella)
  {
    kaantein[ph] = kaantein[ph%5] = busy;
    eating(ph);
  }
  kaantein[ph] = kaantein[ph%5] = vella;
  
}

void loop()
{
  int i = 0;
  while(1)
    {
      pthread_create(&dhaage[i%5], NULL, think, &philo[i%5]);
      pthread_create(&dhaage[(i+2)%5], NULL, think, &philo[(i+2)%5]);
      pthread_join(dhaage[i%5], NULL);
      pthread_join(dhaage[(i+2)%5], NULL);
      i++;
    }
}

int main()
{
  loop();
  
}
