/* Ara ekten (infix) soneke (postfix) cevirme: isleclere yigin ici (isp) ve
 * gelen (icp) oncelik verilir; yiginin dibinde '#' bekcisi durur.
 * Slaytlar: "postfix: a*(b+c)-d", "postfix: a*(b+c)*d". */
#include <stdio.h>
#include <ctype.h>    /* sunumda yok: isalnum */

#define MAX 100       /* sunumda yok */

/* sunumda yok: isp ve icp (ders notundaki gibi) */
int isp(char c) {           /* yığındaki öncelik */
  switch (c) {
    case '(': return 0;
    case '*': case '/': case '%': return 13;
    case '+': case '-': return 12;
    default: return -1;     /* '#': yığının dibi */
  }
}
int icp(char c) {           /* gelen öncelik */
  if (c == '(') return 20;
  return isp(c);
}

void postfix(const char *e, char *cikti) {
  char y[MAX] = {'#'};  int top = 0, k = 0;
  for (; *e; e++) {
    if (isalnum(*e)) cikti[k++] = *e;
    else if (*e == ')') {
      while (y[top] != '(')
        cikti[k++] = y[top--];
      top--;                /* '(' at */
    } else {
      while (isp(y[top]) >= icp(*e))
        cikti[k++] = y[top--];
      y[++top] = *e;
    }
  }
  while (top > 0) cikti[k++] = y[top--];
  cikti[k] = '\0';
}

int main(void)
{
    const char *ifadeler[] = {
        "a*(b+c)-d",
        "a*(b+c)*d",
        "a+b*c",
        "a/b-c+d*e-a*c",
        "a-b-c",
    };
    char cikti[MAX];
    int i;

    for (i = 0; i < 5; i++) {
        postfix(ifadeler[i], cikti);
        printf("%s -> %s\n", ifadeler[i], cikti);
    }
    return 0;
}

/* Beklenen cikti:
 * a*(b+c)-d -> abc+*d-
 * a*(b+c)*d -> abc+*d*
 * a+b*c -> abc*+
 * a/b-c+d*e-a*c -> ab/c-de*+ac*-
 * a-b-c -> ab-c-
 */
