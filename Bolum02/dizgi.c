/* C dizgisi: '\0' ile biten char dizisi. strlen ile sizeof farki, guvenli
 * kopya icin snprintf, icerik karsilastirmasi icin strcmp.
 * Slayt: "Dizgi = char Dizisi". */
#include <stdio.h>
#include <string.h>

int main(void) {  /* sunumda yok */
  char s[] = "dog";      /* 4 bayt: d o g \0 */
  char t[10];
  char *p = "dog";       /* salt okunur sabit */

  printf("strlen(s) = %zu\n", strlen(s));   /* 3 : \0'a kadar */
  printf("sizeof s = %zu\n", sizeof s);     /* 4 : dizinin boyutu */

  strcpy(t, s);                 /* t yeterince büyük mü? */
  printf("t = %s\n", t);
  snprintf(t, sizeof t, "%s!", s);   /* güvenli */
  printf("t = %s\n", t);
  if (strcmp(s, "dog") == 0)         /* == değil! */
    printf("s ile \"dog\" ayni icerik\n");
  printf("p = %s\n", p);
  return 0;
}

/* Beklenen cikti:
 * strlen(s) = 3
 * sizeof s = 4
 * t = dog
 * t = dog!
 * s ile "dog" ayni icerik
 * p = dog
 */
