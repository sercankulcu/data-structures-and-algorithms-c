/* Parantez denetimi: acan parantezler yigina konur, kapanan gelince
 * ustteki acanla eslesmesi denetlenir; sonda yigin bos olmalidir.
 * Ornekler: bir dengeli dizgi ve uc hata turu (yanlis eslesme, fazla
 * kapanan, kapanmamis acan).
 * Slayt: "Parantez Denetimi Adim Adim". */
#include <stdio.h>
#include <stdbool.h>  /* sunumda yok: bool */

#define MAX 100       /* sunumda yok */

/* sunumda yok: eslesir (ders notundaki gibi) */
bool eslesir(char acan, char kapanan) {
  return (acan == '(' && kapanan == ')') ||
         (acan == '[' && kapanan == ']') ||
         (acan == '{' && kapanan == '}');
}

bool dengeli(const char *e) {
  char y[MAX];  int top = -1;
  for (; *e; e++) {
    if (*e=='(' || *e=='[' || *e=='{')
      y[++top] = *e;
    else if (*e==')' || *e==']' || *e=='}') {
      if (top < 0 || !eslesir(y[top], *e))
        return false;  /* fazla/yanlış */
      top--;
    }
  }
  return top == -1;       /* açık kalmadı mı */
}

int main(void)
{
    const char *dizgiler[] = { "{a*(b+c)-[d]}", "[(a+b]*c)", "(a+b))", "((a+b)" };
    int i;

    for (i = 0; i < 4; i++)
        printf("%-14s %s\n", dizgiler[i], dengeli(dizgiler[i]) ? "dengeli" : "dengesiz");
    return 0;
}

/* Beklenen cikti:
 * {a*(b+c)-[d]}  dengeli
 * [(a+b]*c)      dengesiz
 * (a+b))         dengesiz
 * ((a+b)         dengesiz
 */
