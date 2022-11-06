/*#include <time.h>
#include <stdlib.h>

srand(time(NULL));   // Initialization, should only be called once.
int r = rand();

int main() {
  sleep(3);
  printf("%d", r);
  return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>

int randint(int smallest, int biggest) {
  //time_t t;
  return rand() % (biggest-smallest) + smallest;
}

int main () {
   int i, n;
   time_t t;
   
   n = 5;
   srand((unsigned) time(&t));
   
   for( i = 0 ; i < n ; i++ ) {
      printf("%d\n", randint(5, 16));
   }
   /* Intializes random number generator */

   /* Print 5 random numbers from 0 to 49 */
   
   return(0);
}

