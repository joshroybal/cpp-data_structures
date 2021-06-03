#ifndef AVL_HPP
#define AVL_HPP

#include "bst.hpp"

template <class T>
class AVL : public BST<T>
{
   public:
      void Insert(const T&);
      void Remove(const T&);
      void Deserialize(std::istream& istr);
   private:
      struct Node;
      int height_(Node*) const;
      int bal_(Node*) const;
      Node* insert_(Node*, const T&);
      Node* remove_(Node*, const T&);
      Node* rl_(Node*);
      Node* rr_(Node*);
      Node* adjust_(Node*);
      Node* deserialize_(std::istream& istr, Node*);
};

template <class T>
struct AVL<T>::Node : public BST<T>::Node {
   Node(const T& k) : BST<T>::Node(k), h(0), b(0) {}
   int h;
   int b;
   void print() const
   {
      std::cout << std::setw(10) << this << ':';
      std::cout << std::setw(20) << BST<T>::Node::key;
      std::cout << std::setw(3) << h;
      std::cout << std::setw(3) << b;
      std::cout << std::setw(10) << BST<T>::Node::left;
      std::cout << std::setw(10) << BST<T>::Node::right << std::endl;
   }
};

template <class T>
void AVL<T>::Insert(const T& k)
{
   BST<T>::root_ = insert_(static_cast<AVL<T>::Node*>(BST<T>::root_), k);
}

template <class T>
void AVL<T>::Remove(const T& k)
{
   BST<T>::root_ = remove_(static_cast<AVL<T>::Node*>(BST<T>::root_), k);
}

template <class T>
void AVL<T>::Deserialize(std::istream& istr)
{
   BST<T>::root_ = deserialize_(istr, 
         static_cast<AVL<T>::Node*>(BST<T>::root_));
}

template <class T>
int AVL<T>::height_(Node* node) const
{
   return node ? node->h : -1;
}

template <class T>
int AVL<T>::bal_(Node* node) const
{
   return node ? height_(static_cast<AVL<T>::Node*>(node->left)) 
      - height_(static_cast<AVL<T>::Node*>(node->right)) : 0;
}

template <class T>
typename AVL<T>::Node* AVL<T>::insert_(Node* node, const T& k)
{
   if (!node) return new Node(k);

   if (k < node->key)
      node->left = insert_(static_cast<AVL<T>::Node*>(node->left), k);
   else if (k > node->key)
      node->right = insert_(static_cast<AVL<T>::Node*>(node->right), k);
   else
      return node;

   node = adjust_(node);

   if (node->b > 1) {
      int lb = bal_(static_cast<AVL<T>::Node*>(node->left));
      if (lb > 0)             // left left
         return rr_(node);
      else if (lb < 0) {      // left right
         node->left = rl_(static_cast<AVL<T>::Node*>(node->left));
         return rr_(node);
      }
   }
   else if (node->b < -1) {
      int rb = bal_(static_cast<AVL<T>::Node*>(node->right));
      if (rb < 0)          // right right
         return rl_(node);
      else if (rb > 0) {   // right left
         node->right = rr_(static_cast<AVL<T>::Node*>(node->right));
         return rl_(node);
      }
   }
   
   return node;
}

template <class T>
typename AVL<T>::Node* AVL<T>::remove_(Node* node, const T& k)
{
   if (!node) return node;

   if (k < node->key)
      node->left = remove_(static_cast<AVL<T>::Node*>(node->left), k);
   else if (k > node->key)
      node->right = remove_(static_cast<AVL<T>::Node*>(node->right), k);
   else {
      if (!node->left) {
         Node* leaf = static_cast<AVL<T>::Node*>(node->right);
         delete node;
         return leaf;
      }
      else if (!node->right) {
         Node* leaf = static_cast<AVL<T>::Node*>(node->left);
         delete node;
         return leaf;
      }
      node->key = BST<T>::max_(node->left)->key;
      node->left = remove_(static_cast<AVL<T>::Node*>(node->left), node->key);
   }

   node = adjust_(node);

   if (node->b > 1) {
      int lb = bal_(static_cast<AVL<T>::Node*>(node->left));
      if (lb > 0)             // left left
         return rr_(node);
      else if (lb < 0) {      // left right
         node->left = rl_(static_cast<AVL<T>::Node*>(node->left));
         return rr_(node);
      }
   }
   else if (node->b < -1) {
      int rb = bal_(static_cast<AVL<T>::Node*>(node->right));
      if (rb < 0)          // right right
         return rl_(node);
      else if (rb > 0) {   // right left
         node->right = rr_(static_cast<AVL<T>::Node*>(node->right));
         return rl_(node);
      }
   }
   
   return node;   
}

template <class T>
typename AVL<T>::Node* AVL<T>::rl_(Node* node)
{
   Node* right = static_cast<AVL<T>::Node*>(node->right);
   Node* left = static_cast<AVL<T>::Node*>(right->left);

   right->left = node;
   node->right = left;

   // order matters - adjust node before right
   node = adjust_(node);
   right = adjust_(right);
   
   return right;
}

template <class T>
typename AVL<T>::Node* AVL<T>::rr_(Node* node)
{
   Node* left = static_cast<AVL<T>::Node*>(node->left);
   Node* right = static_cast<AVL<T>::Node*>(left->right);

   left->right = node;
   node->left = right;

   // order matters - adjust node before left
   node = adjust_(node);
   left = adjust_(left);

   return left;
}

template <class T>
typename AVL<T>::Node* AVL<T>::adjust_(Node* node)
{
   if (!node) return node;
   node->h = 1 + std::max(height_(static_cast<AVL<T>::Node*>(node->left)), 
         height_(static_cast<AVL<T>::Node*>(node->right)));
   node->b = bal_(node);
   return node;
}

template <class T>
typename AVL<T>::Node* AVL<T>::deserialize_(std::istream& istr, Node* node)
{
   std::string keystr;
   istr >> keystr;
   if (keystr == "\035" || istr.eof()) return 0;
   std::istringstream isstr(keystr);
   T key;
   isstr >> key;
   node = new Node(key);
   node->left = deserialize_(istr, static_cast<AVL<T>::Node*>(node->left));
   node->right = deserialize_(istr, static_cast<AVL<T>::Node*>(node->right));
   return adjust_(node);
}

#endif
