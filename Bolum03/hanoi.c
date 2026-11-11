/* Hanoi kuleleri: n - 1 diski araya, en buyugu hedefe, n - 1 diski hedefe.
 * 2^n - 1 hamle. Slayt: "Hanoi n = 3 Adim Adim". */
#include <stdio.h>  /* sunumda yok */

void hanoi(int n, char *kaynak, char *ara,
           char *hedef) {
  if (n == 1)
    printf("%s -> %s\n", kaynak, hedef);
  else {
    hanoi(n - 1, kaynak, hedef, ara);
    printf("%s -> %s\n", kaynak, hedef);
    hanoi(n - 1, ara, kaynak, hedef);
  }
}

int main(void) {  /* sunumda yok */
  /* main: */ hanoi(3, "A", "B", "C");
  return 0;
}

/* Beklenen cikti:
 * A -> C
 * A -> B
 * C -> B
 * A -> C
 * B -> A
 * B -> C
 * A -> C
 */
