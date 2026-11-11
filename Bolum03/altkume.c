/* Alt kume uretimi (en sade geri izleme): her oge icin once "al", sonra
 * "alma" karari; 2^n alt kume. Slayt: "Alt Kume Uretimi Adim Adim".
 * Ornek: {a, b, c}. */
#include <stdio.h>  /* sunumda yok */

void altkume(char *s, int n, int i,
             int sec[]) {
  int j;
  if (i == n) {                  /* karar bitti */
    printf("{");
    for (j = 0; j < n; j++)
      if (sec[j]) printf("%c", s[j]);
    printf("}\n");
    return;
  }
  sec[i] = 1; altkume(s, n, i + 1, sec);
  sec[i] = 0; altkume(s, n, i + 1, sec);
}

int main(void) {  /* sunumda yok */
  char s[] = "abc";
  int sec[3];
  altkume(s, 3, 0, sec);
  return 0;
}

/* Beklenen cikti:
 * {abc}
 * {ab}
 * {ac}
 * {a}
 * {bc}
 * {b}
 * {c}
 * {}
 */
