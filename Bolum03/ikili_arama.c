/* Yinelemeli ikili arama ve uc durumlu COMPARE makrosu. Aralik [left, right]
 * kapali uclu; her turda yari atilir. Slaytlar: "Ikili Arama Problemi",
 * "Ikili Arama: 18 Araniyor", "Ikili Arama: 25 Yok". Test dizisi nottan. */
#include <stdio.h>  /* sunumda yok */

#define COMPARE(x, y) ((x) < (y) ? -1 : (y) < (x) ? 1 : 0)

int binsearch(int list[], int aranan,
              int left, int right) {
  while (left <= right) {
    int middle = (left + right) / 2;
    switch (COMPARE(list[middle], aranan)) {
      case -1: left = middle + 1; break;
      case 0: return middle;
      case 1: right = middle - 1;
    }
  }
  return -1;
}

int main(void) {  /* sunumda yok */
  int list[] = {4, 13, 18, 19, 24, 27, 33, 36, 39, 40};
  printf("18 -> %d\n", binsearch(list, 18, 0, 9));
  printf("25 -> %d\n", binsearch(list, 25, 0, 9));
  printf("4 -> %d\n", binsearch(list, 4, 0, 9));
  printf("40 -> %d\n", binsearch(list, 40, 0, 9));
  return 0;
}

/* Beklenen cikti:
 * 18 -> 2
 * 25 -> -1
 * 4 -> 0
 * 40 -> 9
 */
