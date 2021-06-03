#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <queue>

template <class T>
class BST {
   public:
      BST() : root_(0) {}
      ~BST() { destroy_(root_); }
      int Size() const { return size_(root_); }
      int Height() const { return height_(root_); }
      void Search(const T& k) const { printnode_(search_(root_, k)); }
      void Min() const { printnode_(min_(root_)); }
      void Max() const { printnode_(max_(root_)); }
      void Predecessor(const T& k) const
         { printnode_(predecessor_(root_, 0, k)); }
      void Successor(const T& k) const 
         { printnode_(successor_(root_, 0, k)); }
      void Insert(const T& k) { insert_(root_, k); }
      void Remove(const T& k) { remove_(root_, k); }
      void Defoliate() { defoliate_(root_); }
      void preOrder() const { preorder_(root_); }
      void inOrder() const { inorder_(root_); } 
      void postOrder() const { postorder_(root_); }
      void levelOrder() const { levelorder_(root_); }
      void Serialize(std::ostream& ostr) { serialize_(ostr, root_); }
      void Deserialize(std::istream& istr) { deserialize_(istr, root_); }
      void Report() const;
   protected:
      struct Node;
      Node* root_;
      void destroy_(Node*);
      int size_(const Node*) const;
      int height_(const Node*) const;
      Node* search_(Node*, const T&) const;
      const Node* min_(const Node*) const;
      const Node* max_(const Node*) const;
      const Node* predecessor_(Node*, Node*, const T&) const;
      const Node* successor_(Node*, Node*, const T&) const;
      void insert_(Node*&, const T&);
      void remove_(Node*&, const T&);
      void defoliate_(Node*&);
      void preorder_(const Node*) const;
      void inorder_(const Node*) const;
      void postorder_(const Node*) const;
      void levelorder_(const Node*) const;
      void printnode_(const Node*) const;
      void serialize_(std::ostream& ostr, const Node*) const;
      void deserialize_(std::istream& istr, Node*&);
};

template <class T>
struct BST<T>::Node {
   Node(const T& k) : key(k), left(0), right(0) {}
   T key;
   Node* left;
   Node* right;
   virtual void print() const
   {
      std::cout << std::setw(10) << this << ':';
      std::cout << std::setw(20) << key;
      std::cout << std::setw(10) << left;
      std::cout << std::setw(10) << right << std::endl;
   }
};

template <class T>
void BST<T>::Report() const
{
   std::cout << "pre-order traversal" << std::endl;
   preOrder();
   std::cout << "in-order traversal" << std::endl;
   inOrder();
   std::cout << "post-order traversal" << std::endl;
   postOrder();
   std::cout << "level-order traversal" << std::endl;
   levelOrder();
   std::cout << "size = " << Size() << std::endl;
   std::cout << "height = " << Height() << std::endl;
   Min();
   Max();
}

template <class T>
void BST<T>::destroy_(Node* p)
{
   if (!p) return;
   destroy_(p->left);
   destroy_(p->right);
   delete p;
}

template <class T>
int BST<T>::size_(const Node* p) const
{
   if (!p) return 0;
   return 1 + size_(p->left) + size_(p->right);
}

template <class T>
int BST<T>::height_(const Node* p) const
{
   if (!p) return -1;
   return 1 + std::max(height_(p->left), height_(p->right));
}

template <class T>
typename BST<T>::Node* BST<T>::search_(Node* p, const T& k) const
{
   if (!p) return p;

   if (k < p->key)
      p = search_(p->left, k);
   else if (k > p->key)
      p = search_(p->right, k);
     
   return p;
}

template <class T>
const typename BST<T>::Node* BST<T>::min_(const Node* p) const
{
   return p->left ? min_(p->left) : p;
}

template <class T>
const typename BST<T>::Node* BST<T>::max_(const Node* p) const
{
   return p->right ? max_(p->right) : p;
}

template <class T>
const typename BST<T>::Node* 
BST<T>::predecessor_(Node* node, Node* prec, const T& k) const 
{
   if (!node) return prec;

   if (k > node->key)
      return predecessor_(node->right, node, k);
   else if (k < node->key)
      return predecessor_(node->left, prec, k);
   else
      if (node->left)
         return max_(node->left);
      else
         return prec;
}

template <class T>
const typename BST<T>::Node* 
BST<T>::successor_(Node* node, Node* succ, const T& k) const
{
   if (!node) return succ;

   if (k > node->key)
      return successor_(node->right, succ, k);
   else if (k < node->key)
      return successor_(node->left, node, k);
   else
      if (node->right)
         return min_(node->right);
      else
         return succ;
}

template <class T>
void BST<T>::insert_(Node*& p, const T& k)
{
   if (!p) {
      p = new Node(k);
      return;
   }

   if (k < p->key)
      insert_(p->left, k);
   else if (k > p->key)
      insert_(p->right, k);
   else  // no duplicate keys
      return;
}

template <class T>
void BST<T>::remove_(Node*& p, const T& k)
{
   if (!p) return;

   if (k < p->key)
      remove_(p->left, k);
   else if (k > p->key)
      remove_(p->right, k);
   else {
      if (!p->left) {
         Node* leaf = p->right;
         delete p;
         p = leaf;
         return;
      }
      else if (!p->right) {
         Node* leaf = p->left;
         delete p;
         p = leaf;
         return;
      }
      p->key = max_(p->left)->key;
      remove_(p->left, p->key);
   }
}

template <class T>
void BST<T>::defoliate_(Node*& p)
{
   if (!p) return;

   if (!p->left && !p->right) {
      delete p;
      p = 0;
      return;
   }
   defoliate_(p->left);
   defoliate_(p->right);
}

template <class T>
void BST<T>::preorder_(const Node* p) const
{
   if (!p) return;
   printnode_(p);
   preorder_(p->left);
   preorder_(p->right);
}

template <class T>
void BST<T>::inorder_(const Node* p) const
{
   if (!p) return;
   inorder_(p->left);
   Predecessor(p->key);
   printnode_(p);
   Successor(p->key);
   std::cout << std::endl;
   inorder_(p->right);
}

template <class T>
void BST<T>::postorder_(const Node* p) const
{
   if (!p) return;
   postorder_(p->left);
   postorder_(p->right);
   printnode_(p);
}

template <class T>
void BST<T>::levelorder_(const Node* p) const
{
   if (!p) return;
   std::queue<const Node*> q;
   q.push(p);
   while (!q.empty()) {
      const Node* node = q.front();
      printnode_(node);
      q.pop();
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);
   }
}

template <class T>
void BST<T>::printnode_(const Node* p) const
{
   if (!p) {
      std::cout << std::setw(10) << p << std::endl;
      return;
   }
   p->print();
}

template <class T>
void BST<T>::serialize_(std::ostream& ostr, const Node* p) const
{
   if (!p) {
      ostr << ' ' << '\035';  // ascii group separator
      return;
   }
   ostr << ' ' << p->key;
   serialize_(ostr, p->left);
   serialize_(ostr, p->right);
}

template <class T>
void BST<T>::deserialize_(std::istream& istr, Node*& p)
{
   std::string keystr;
   istr >> keystr;
   if (keystr == "\035" || istr.eof()) return;
   std::istringstream isstr(keystr);
   T key;
   isstr >> key;
   p = new Node(key);
   deserialize_(istr, p->left);
   deserialize_(istr, p->right);
}

#endif
