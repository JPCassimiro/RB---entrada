#include "rb.h"
#include <stdio.h>
#include <stdlib.h>

int id = 0;
link novoNo(int item, link l, link r) {
  link t = malloc(sizeof(struct node));
  t->item = item;
  t->l = l;
  t->r = r;
  t->color = 1;
  t->id = id++;
  return t;
}

Tree createTree() {
  Tree t = malloc(sizeof(struct tree));
  t->z = malloc(sizeof(struct node));
  t->head = t->z;
  t->z->l = t->z;
  t->z->r = t->z;
  t->z->color = 0;
  t->head->f = NULL;
  return t;
}

link insert(Tree t, int item) {
  if (t->head == t->z) {
    t->head = novoNo(item, t->z, t->z);
    t->head->color = 0;
    return t->head; //-Arvore sem nós, raiz nova vem de novoNo
  }
  return insertR(t, t->head, novoNo(item, t->z, t->z)); //-Manda o nó da arvore para a func de entrada passando um nó novo
}

link insertR(Tree t, link h, link n) {
  if (h == t->z) {
    return n;
  }

  if (h->item >= n->item){
    h->l = insertR(t, h->l, n);
    h->l->f = h;
  }
  else{
    h->r = insertR(t, h->r, n);
    h->r->f = h;
  }
  (h->N)++;
  return h;
}

link rotR(Tree t, link h) {
  link x = h->l;
  h->l = x->r;
  x->r = h;
  return x;
}

link rotL(Tree t, link h) { 
  link x = h->r;
  h->r = x->l;
  x->l = h;
  return x;
}

link searchR(Tree t, link h, int query) {
  if (h == t->z) {
    return NULL;
  }
  if (h->item == query)
    return h;
  if (h->item >= query)
    return searchR(t, h->l, query);
  return searchR(t, h->r, query);
}

link search(Tree t, int query) { return searchR(t, t->head, query); }

void cor(Tree a,link h){
  if(h==a->z){
    return;
  }
  cor(a,h->r);
  printf("\n%d",h->color);
  cor(a,h->l);
}

void pai(Tree a,link h){
  if(h==a->z){
    return;
  }
  pai(a,h->r);
  printf("\n%d",h->f->item);
  pai(a,h->l);
}

void rebalance(Tree a, link h){
  if(h == a->z){
    return;
  }
  rebalance(a,h->r);
  rebalance(a,h->l);
  if((h->color==1)&&(h->f->color==1)){//Caso inicial, h e f são 1
    if((h->f->f->l->color == 1)&&(h->f->f->r == h->f)){//caso 1, tio 1 pai esquerda
      //pai avo e tio são recoloridos
      h->f->color = !h->f->color;
      if(h->f->f != a->head){
        h->f->f->color = !h->f->f->color;
      }
      h->f->f->l->color = !h->f->f->l->color;
    }
    else if((h->f->r == h)&&(h->f->f->l == h->f)&&(h->f->f->r->color == 0)){
      h->f->f->l = rotL(a,h->f);
      h->f->color = 0;
      h->f->f->color = 1;
      h->f->f->f->l = rotR(a,h->f->f);
    }
    else if((h->f->l == h)&&(h->f->f->l == h->f)&&(h->f->f->r->color == 0)){
      h->f->color = 0;
      if(h->f->f != a->head){
        h->f->f->color = 1;
      }
      if(h->f->f->f != NULL){
        h->f->f->f->l = rotR(a,h->f->f);
      }
    }
    else if((h->f->l == h)&&(h->f->f->r == h->f)&&(h->f->f->l->color == 0)){
      h->f->f->r = rotR(a,h->f);
      h->f->color = 0;
      if(h->f->f != a->head){
         h->f->f->color = 1;
      }
      if(h->f->f->f != NULL){
        h->f->f->f->r = rotL(a,h->f->f);
      }
    }
    else if((h->f->r==h)&&(h->f->f->r == h->f)&&(h->f->f->l->color == 0)){
      h->f->color = 0;
      if(h->f->f != a->head){
        h->f->f->color = 1;
      }
      if(h->f->f->f != NULL){
        h->f->f->f->r = rotL(a,h->f->f);
      }
    }
  }
}

int c = 0;
void imprimeR(Tree a, link t) {
  char s[255];
  if (t == a->z) {
    return;
  }
  imprimeR(a, t->r);
  printf("%d [ label = \"<f0>| <f1> %d (%d) c:%d| <f2>\"]\n",t->id, t->item, t->N, t->color);
  if (t->l != a->z) {
    printf("%d:f0->%d:f1;\n", t->id, t->l->id);
  } else {
    printf("z%d [ shape=point ];\n", c);
    printf("%d:f0->z%d;\n", t->id, c);
    c++;
  }
  if (t->r != a->z) {
    printf("%d:f2->%d:f1;\n", t->id, t->r->id);
  } else {
    printf("z%d [ shape=point ];\n", c);
    printf("%d:f2->z%d;\n", t->id, c);
    c++;
  }
  imprimeR(a, t->l);
}

void imprime(Tree a, char *s) {
  c = 0;
  printf("digraph %s {\n", s);
  printf("node [shape=record,style=rounded, height=.1]\n");
  imprimeR(a, a->head);
  printf("}\n");
}
    
void entradaRB(Tree a, int item,link h){
  insert(a,item);
  //rebalance(a,h);
}