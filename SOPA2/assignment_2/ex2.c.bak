#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define N_FILOSOFOS 5
#define PMI PTHREAD_MUTEX_INITIALIZER

typedef struct {
  int hashi_esquerda;
  int hashi_direita;
  int id_relativo;
} filosofo;

pthread_mutex_t hashis[] = {PMI, PMI, PMI, PMI, PMI};
char nomes[][32] = {"Aristóteles", "Platão", "Sócrates", "Pitágoras", "Demócrito"};

int randint(int smallest, int biggest) {
  //time_t t;
  return rand() % (biggest-smallest) + smallest;
}

void *thread_filosofo(void *args){
  filosofo *actual_args = args;
  printf("%s -> id %d ", nomes[(int)actual_args->id_relativo], pthread_self());
  pthread_mutex_lock(&hashis[0]);
  printf("%d %d\n", hashis[0], randint(5, 16));
  pthread_mutex_unlock(&hashis[0]);
  //printf("%d ", actual_args->hashi_esquerda);
  //printf("%d ", actual_args->hashi_direita);
  //printf("%d\n", actual_args->id_relativo);

}


//pthread_mutex_t hashis[N_FILOSOFOS];


int main() {
  //for (int i=0; i<N_FILOSOFOS; i++) {hashis[i] = PTHREAD_MUTEX_INITIALIZER;}
  time_t t;
  srand((unsigned) time(&t));
  
  for (int i=0; i<N_FILOSOFOS; i++) printf("%d, ", hashis[i]);
  pthread_mutex_t *ptr = hashis;
  /*printf("%s", nomes[2]);
  printf("%d\n", ptr);
  printf("%d\n", &hashis[1]);
  printf("%d\n", &hashis[2]);
  printf("%d\n", &hashis[3]);
  printf("%d\n", &hashis[4]);*/
  int hashi_esquerda, hashi_direita, id_relativo;
  pthread_t filosofos[N_FILOSOFOS];
  for (int i=0; i<N_FILOSOFOS; i++) {
    filosofo *args = malloc(sizeof *args);
    /*hashi_esquerda = i%5;
    hashi_direita = (i+1)%5;
    id_relativo = i;*/
    /*args->hashi_esquerda = (int) hashi_esquerda;
    args->hashi_direita = (int) hashi_direita;
    args->id_relativo = (int) id_relativo;*/
    
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

