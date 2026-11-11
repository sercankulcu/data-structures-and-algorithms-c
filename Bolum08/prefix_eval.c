/* Onek (prefix) ifadeyi hesaplama: ifade sagdan sola okunur; islec
 * gelince ilk alinan deger sol islenendir.
 * Slayt: "Prefix Hesaplama". */
#include <stdio.h>
#include <string.h>   /* sunumda yok: strlen */
#include <ctype.h>    /* sunumda yok: isdigit */

#define MAX 100       /* sunumda yok */

/* sunumda yok: uygula (ders notundaki gibi) */
float uygula(char islec, float op1, float op2) {
  switch (islec) {
    case '+': return op1 + op2;
    case '-': return op1 - op2;
    case '*': return op1 * op2;
    case '/': return op1 / op2;
    default:  return 0;
  }
}

float prefix_eval(const char *e) {
  float y[MAX], op1, op2;  int top = -1;
  for (int i = strlen(e) - 1; i >= 0; i--) {
    if (isdigit(e[i])) y[++top] = e[i] - '0';
    else {
      op1 = y[top--];  op2 = y[top--];
      y[++top] = uygula(e[i], op1, op2);
    }
  }
  return y[top];
}

int main(void)
{
    const char *ifadeler[] = { "-+*23*549", "-62", "*-623" };
    int i;

    for (i = 0; i < 3; i++)
        printf("prefix_eval(\"%s\") = %g\n", ifadeler[i],
               prefix_eval(ifadeler[i]));
    return 0;
}

/* Beklenen cikti:
 * prefix_eval("-+*23*549") = 17
 * prefix_eval("-62") = 4
 * prefix_eval("*-623") = 12
 */
