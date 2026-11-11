/* Sonek (postfix) ifadeyi hesaplama, kuresel surum: token_al ifadeyi
 * belirtec belirtec okur, eval kuresel expr ve kuresel yigit ile calisir.
 * Slaytlar: "token_al", "eval Yordami", "Bilesen Gibi Yazmak" (kuresel surum). */
#include <stdio.h>
#include <stdlib.h>   /* sunumda yok: exit */

#define MAX_SIZE 100  /* sunumda yok */

typedef enum { sol_paran, sag_paran, arti, eksi,
    carpma, bolme, mod, eos, operand } oncelik;

oncelik token_al(const char *expr, char *sembol, int *n) {
    *sembol = expr[(*n)++];
    switch (*sembol) {
        case '(':  return sol_paran;
        case ')':  return sag_paran;
        case '+':  return arti;
        case '-':  return eksi;
        case '/':  return bolme;
        case '*':  return carpma;
        case '%':  return mod;
        case '\0': return eos;
        default:   return operand;
    }
}

/* kuresel surum: disa bagimli */
char expr[] = "42/2-33*+42*-";
float yigit[MAX_SIZE];
float eval(void);

/* sunumda yok: kuresel yigit uzerinde yigin islemleri */
void yigit_ekle(int *top, float x)
{
    if (*top >= MAX_SIZE - 1) {
        fprintf(stderr, "Yigit dolu\n");
        exit(EXIT_FAILURE);
    }
    yigit[++*top] = x;
}

float yigit_al(int *top)
{
    if (*top == -1) {
        fprintf(stderr, "Yigit bos\n");
        exit(EXIT_FAILURE);
    }
    return yigit[(*top)--];
}

/* sunumda yok: islem (ders notundaki gibi) */
float islem(oncelik token, float op1, float op2) {
    switch (token) {
        case arti:   return op1 + op2;
        case eksi:   return op1 - op2;
        case carpma: return op1 * op2;
        case bolme:  return op1 / op2;
        case mod:    return (int)op1 % (int)op2;
        default:     return 0;   /* işleç değil: buraya gelinmez */
    }
}

float eval(void) {
    char sembol;  oncelik token;
    float op1, op2;
    int n = 0, top = -1;
    token = token_al(expr, &sembol, &n);
    while (token != eos) {
        if (token == operand)
            yigit_ekle(&top, sembol - '0');
        else {
            op2 = yigit_al(&top);   /* önce sağ işlenen */
            op1 = yigit_al(&top);
            yigit_ekle(&top, islem(token, op1, op2));
        }
        token = token_al(expr, &sembol, &n);
    }
    return yigit_al(&top);   /* kalan tek öğe sonuç */
}

int main(void)
{
    const char *deneme = "(7%3)";
    char sembol;
    int n = 0;
    oncelik t;

    /* token_al: "(7%3)" ifadesinin belirtecleri */
    printf("token_al(\"%s\"):", deneme);
    do {
        t = token_al(deneme, &sembol, &n);
        printf(" %d", (int)t);
    } while (t != eos);
    printf("\n");

    printf("eval() ile %s = %g\n", expr, eval());
    return 0;
}

/* Beklenen cikti:
 * token_al("(7%3)"): 0 8 6 8 1 7
 * eval() ile 42/2-33*+42*- = 1
 */
