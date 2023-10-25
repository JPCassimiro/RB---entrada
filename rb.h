#ifndef RB_H
#define RB_H
#define COUNT 5

typedef struct node *link;
struct node {
  link f; // Nó pai
  link l;
  link r;
  int item;
  int color; // cor do nó, 0 para b, 1 para r
  int id;
  int N;
};

typedef struct tree {
  link head; // raiz
  link z;    // nó externo
} * Tree;

link novoNo(int item, link l, link r);
Tree createTree();

link rotR(Tree t, link h);
link rotL(Tree t, link h);

link search(Tree h, int query);
link searchR(Tree t, link h, int query);

link insertR(Tree t, link h, link n);
link insert(Tree h, int item);

void cor(Tree a, link h);
void pai(Tree a, link h);

void recolor(Tree a, link h);

void entradaRB(Tree a, int item,link h);

void imprimeR(Tree a, link t);
void imprime(Tree a, char *s);
#endif