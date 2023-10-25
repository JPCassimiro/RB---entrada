#include "rb.h"
#include <stdio.h>

int main(void) {
  Tree t = createTree();
  entradaRB(t,55,t->head);
  entradaRB(t,77,t->head);
  entradaRB(t,44,t->head);
  //entradaRB(t,66,t->head);
  imprime(t,"arvore");
  return 0;
}