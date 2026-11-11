/* Sonek (postfix) ifadeyi hesaplama, bilesen surumu: ifade parametreyle
 * gelir, yigin eval'in icinde yerel bir dizidir; kuresel degisken yoktur.
 * Slaytlar: "Bilesen Gibi Yazmak", "eval: 23*54*+9-", "eval: 42/2-33*+42*-". */
#include <stdio.h>
#include <ctype.h>    /* sunumda yok: isdigit */

#define MAX_SIZE 100  /* sunumda yok */

/* bileşen: her şey parametre/yerel */
float eval(const char *expr);
/* yığın eval'in içinde yerel dizi */

float eval(const char *expr) {
  float y[MAX_SIZE], op1, op2;  int top = -1;
  for (int n = 0; expr[n] != '\0'; n++) {
    char c = expr[n];
    if (isdigit(c)) y[++top] = c - '0';
    else {
      op2 = y[top--];  op1 = y[top--];
      switch (c) {
        case '+': y[++top] = op1 + op2; break;
        case '-': y[++top] = op1 - op2; break;
        case '*': y[++top] = op1 * op2; break;
        case '/': y[++top] = op1 / op2; break;
      }
    }
  }
  return y[top];
}

int main(void)
{
    /* main içinde: */
    float a = eval("23*54*+9-");
    float b = eval("42/2-33*+42*-");
    float c = eval("623+-382/+*");   /* sunumda yok: notun alistirma ifadesi */

    printf("eval(\"23*54*+9-\") = %g\n", a);
    printf("eval(\"42/2-33*+42*-\") = %g\n", b);
    printf("eval(\"623+-382/+*\") = %g\n", c);
    return 0;
}

/* Beklenen cikti:
 * eval("23*54*+9-") = 17
 * eval("42/2-33*+42*-") = 1
 * eval("623+-382/+*") = 7
 */
