#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N_FILOSOFOS 5
#define PMI PTHREAD_MUTEX_INITIALIZER
#define TRUE 1
#define FALSE 0

typedef struct {
  int hashi_esquerda;
  int hashi_direita;
  int id_relativo;
} filosofo;

//pthread_mutex_t hashis[] = {PMI, PMI, PMI, PMI, PMI};
sem_t hashis[N_FILOSOFOS];
int pratos[N_FILOSOFOS];

char nomes[][32] = {"Aristóteles", "Platão", "Sócrates", "Pitágoras", "Demócrito"};

int randint(int smallest, int biggest) {
  //time_t t;
  return rand() % (biggest-smallest) + smallest;
}

void comer(char nome[]) {
  printf("%s está comendo.\n", nome);
  sleep(randint(1, 5));
  printf("%s acabou de comer\n", nome);
}

void mostrar_pratos(int arr[]){
  printf("Pratos: [");
  for (int i=0; i < N_FILOSOFOS; i++)  printf("%d%s", arr[i], i+1 == N_FILOSOFOS ? "]\n" : ", ");
}

void *thread_filosofo(void *args){
  filosofo *actual_args = args;
  int id = (int) actual_args -> id_relativo;
  printf("%s -> id %d sentou-se à mesa\n", nomes[id], pthread_self());
  while(TRUE) {
    sleep(randint(1, 5));
    sem_wait(&hashis[actual_args->hashi_esquerda]);
    sem_wait(&hashis[actual_args->hashi_direita]);
    comer(nomes[id]);
    pratos[id]++; mostrar_pratos(pratos);
    sem_post(&hashis[actual_args->hashi_esquerda]);
    sem_post(&hashis[actual_args->hashi_direita]);
  }
  //pthread_mutex_lock(&hashis[0]);
  //printf("%d %d\n", hashis[0], randint(5, 16));
  //pthread_mutex_unlock(&hashis[0]);
}

int main() {
  time_t t;
  srand((unsigned) time(&t));
  
  //for (int i=0; i<N_FILOSOFOS; i++) printf("%d, ", hashis[i]);
  for (int i=0; i<N_FILOSOFOS; i++) pratos[i] = 0;
  for(int i=0; i<N_FILOSOFOS; i++) sem_init(&hashis[i],0,1);
  //pthread_mutex_t *ptr = hashis;

  int hashi_esquerda, hashi_direita, id_relativo;
  pthread_t filosofos[N_FILOSOFOS];
  for (int i=0; i<N_FILOSOFOS; i++) {
    filosofo *args = malloc(sizeof *args);
    
    args->hashi_esquerda = i%N_FILOSOFOS;
    args->hashi_direita = (i+1)%N_FILOSOFOS;
    args->id_relativo = i;

    if (pthread_create(&filosofos[i], NULL, thread_filosofo, args)) {
      free(args);
    }
  }

  for (int i=0; i < N_FILOSOFOS; i++) pthread_join(filosofos[i], NULL);

  printf("\nTeste final\n");
  return 0;
}

