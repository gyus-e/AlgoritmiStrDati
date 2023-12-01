#ifndef ALBERI_H_
#define ALBERI_H_

typedef int TIPO;

struct Tree {
    TIPO key;
    struct Tree * left;
    struct Tree * right;
};

struct Tree * NewNode (TIPO k)
{
    struct Tree * nuovo = malloc (sizeof(struct Tree));
    nuovo->key=k;
    nuovo->left=NULL;
    nuovo->right=NULL;
    return nuovo;
}

#endif