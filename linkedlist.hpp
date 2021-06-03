#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <iomanip>

template <class T>
class LinkedList
{
   public:
      LinkedList() { head_ = 0; }
      ~LinkedList() { destroy_(head_); }
      void Add(const T& k) { head_ = add_(k); }
      void Reverse() { head_ = reverse_(head_, 0); }
      int Size() const { return size_(head_, 0); }
      void Print() const { print_(head_); }
      void Report() const;
   private:
      struct Node;
      Node* head_;
      void destroy_(Node*);
      Node* add_(const T&);
      Node* reverse_(Node*, Node*);
      int size_(const Node*, int) const;
      void print_(const Node*) const;
      void printnode_(const Node*) const;
};

template <class T>
struct LinkedList<T>::Node {
   Node(const T& k, Node* p=0) : key(k), next(p) {}
   T key;
   Node* next;
   void print() const
   {
      std::cout << std::setw(10) << this << ':';
      std::cout << std::setw(20) << key;
      std::cout << std::setw(10) << next << std::endl;
   }
};

template <class T>
void LinkedList<T>::Report() const
{
   Print();
   std::cout << "size = " << Size() << std::endl;
}

template <class T>
void LinkedList<T>::destroy_(Node* node)
{
   if (!node) return;
   Node* next = node->next;
   delete node;
   node = 0;
   destroy_(next);
}

template <class T>
typename LinkedList<T>::Node* LinkedList<T>::add_(const T& k)
{
   return new Node(k, head_);
}

template <class T>
typename LinkedList<T>::Node* LinkedList<T>::reverse_(Node* head, Node* prev)
{
   if (!head) return(prev);
   Node* body = head->next;
   head->next = prev;
   return reverse_(body, head);
}

template <class T>
int LinkedList<T>::size_(const Node* node, int siz) const
{
   if (!node) return siz;
   return size_(node->next, ++siz);
}

template <class T>
void LinkedList<T>::print_(const Node* node) const
{
   if (!node) return;
   printnode_(node);
   print_(node->next);
}

template <class T>
void LinkedList<T>::printnode_(const Node* node) const
{
   if (!node) {
      std::cout << std::setw(10) << node << std::endl;
      return;
   }
   node->print();
}

#endif
