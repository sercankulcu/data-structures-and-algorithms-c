/* malloc ile calisma aninda boyutu belli olan dizi: NULL denetimi, dizi
 * gibi kullanim, free ve sarkan isaretciyi NULL yapmak.
 * Slayt: "malloc ile Dizi". */
#include <stdio.h>
#include <stdlib.h>

int main(void) {  /* sunumda yok */
  int n, i, *a;
  /* sunumda: scanf("%d", &n); klavye girdisi yok, n sabit verildi */
  n = 5;
  a = malloc(n * sizeof *a);   /* n int */
  if (a == NULL) {
    fprintf(stderr, "Yetersiz bellek\n");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < n; i++)
    a[i] = i * i;              /* dizi gibi */
  for (i = 0; i < n; i++)      /* sunumda yok: icerigi yaz */
    printf("%d ", a[i]);
  printf("\n");                /* sunumda yok */
  free(a);                     /* geri ver */
  a = NULL;          /* sarkan işaretçi olmasın */
  printf("a = %s\n", a == NULL ? "NULL" : "?");  /* sunumda yok */
  return 0;
}

/* Beklenen cikti:
 * 0 1 4 9 16
 * a = NULL
 */
