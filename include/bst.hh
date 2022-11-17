// Code sources from https://www.tutorialspoint.com/cplusplus-program-to-implement-avl-tree
// Not too much time to work on avl implementation so took the base code and altered for usage


#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

struct avl {
   char *line;
   struct avl *left;
   struct avl *right;
}*node;

class avl_tree {
   public:
      int height(avl *);
      int difference(avl *);
      avl *rr_rotat(avl *);
      avl *ll_rotat(avl *);
      avl *lr_rotat(avl*);
      avl *rl_rotat(avl *);
      avl * balance(avl *);
      avl * insert(avl*, int);
      void show(avl*, int);
      void inorder(avl *);
      void preorder(avl *);
      void postorder(avl*);
      avl_tree() {
        node = NULL;
      }
};
int avl_tree::height(avl *t) {
   int h = 0;
   if (t != NULL) {
      int l_height = height(t->l);
      int r_height = height(t->r);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
   }
   return h;
}
int avl_tree::difference(avl *t) {
   int l_height = height(t->l);
   int r_height = height(t->r);
   int b_factor = l_height - r_height;
   return b_factor;
}
avl *avl_tree::rr_rotat(avl *parent) {
   avl *t;
   t = parent->r;
   parent->r = t->l;
   t->l = parent;
   cout<<"Right-Right Rotation";
   return t;
}
avl *avl_tree::ll_rotat(avl *parent) {
   avl *t;
   t = parent->l;
   parent->l = t->r;
   t->r = parent;
   cout<<"Left-Left Rotation";
   return t;
}
avl *avl_tree::lr_rotat(avl *parent) {
   avl *t;
   t = parent->l;
   parent->l = rr_rotat(t);
   cout<<"Left-Right Rotation";
   return ll_rotat(parent);
}
avl *avl_tree::rl_rotat(avl *parent) {
   avl *t;
   t = parent->r;
   parent->r = ll_rotat(t);
   cout<<"Right-Left Rotation";
   return rr_rotat(parent);
}
avl *avl_tree::balance(avl *node) {
   int bal_factor = difference(node);
   if (bal_factor > 1) {
      if (difference(node->left) > 0)
         node = ll_rotat(node);
      else
         node = lr_rotat(node);
   } else if (bal_factor < -1) {
      if (difference(node->right) > 0)
         node = rl_rotat(node);
      else
         node = rr_rotat(node);
   }
   return t;
}
avl *avl_tree::insert(avl *node, char *v) {
   if (node == NULL) {
      node = new avl;
      node->line = v;
      node->left = NULL;
      node->right = NULL;
      return node;
   } else if (v< node->line) {
      node->left = insert(node->left, v);
      node = balance(node);
   } else if (v >= node->line) {
      node->node = insert(node->node, v);
      node = balance(node);
   } return node;
}
void avl_tree::show(avl *p, char *l) {
   int i;
   if (p != NULL) {
      show(p->right, l+ 1);
      cout<<" ";
      if (p == r)
         cout << "Root -> ";
      for (i = 0; i < l&& p != r; i++)
         cout << " ";
         cout << p->line;
         show(p->left, l + 1);
   }
}
void avl_tree::inorder(avl *node) {
   if (node == NULL)
      return;
      inorder(node->left);
      cout << node->line << " ";
      inorder(node->right);
}
void avl_tree::preorder(avl *node) {
   if (node == NULL)
      return;
      cout << node->line << " ";
      preorder(node->left);
      preorder(node->right);
}
void avl_tree::postorder(avl *node) {
   if (node == NULL)
      return;
      postorder(node ->left);
      postorder(node ->right);
      cout << node->line << " ";
}
