#include <iostream>
#include <sstream>
#include <fstream>
#include "random.hpp"
#include "linkedlist.hpp"
#include "bst.hpp"
#include "avl.hpp"

std::string readRecord(std::ifstream&, int);

int main(int argc, char* argv[])
{
   if (argc < 2) {
      std::cerr << "Usage: " << argv[0] << " n" << std::endl;
      return 1;
   }

   std::istringstream nsstr(argv[1]);
   int n;
   nsstr >> n;
   Random rnd;

   std::cout << "integer tests" << std::endl;

   LinkedList<int>* noList = new LinkedList<int>;
   for (int i = 0; i < n; i++) noList->Add(rnd.integer());
   std::cout << "linked list" << std::endl;
   noList->Report();
   noList->Reverse();
   std::cout << "linked list reversed" << std::endl;
   noList->Report();
   delete noList;

   BST<int>* noTree = new BST<int>;
   for (int i = 0; i < n; i++) noTree->Insert(rnd.integer());
   std::cout << "binary search tree" << std::endl;
   noTree->Report();
   delete noTree;

   AVL<int>* avlTree = new AVL<int>;
   for (int i = 0; i < n; i++) avlTree->Insert(i);
   std::cout << "AVL balanced binary search tree" << std::endl;
   avlTree->Report();
   delete avlTree;

   std::cout << "string tests" << std::endl;
   LinkedList<std::string>* wordList = new LinkedList<std::string>();
   std::ifstream ifstr("words.dat", std::ifstream::in | std::ifstream::binary);
   for (int i = 0; i < n; i++) {
      int recno = rnd.integer(113783, 1);
      wordList->Add(readRecord(ifstr, recno));
   }
   ifstr.close();
   std::cout << "linked list" << std::endl;
   wordList->Report();
   std::cout << "reversing list" << std::endl;
   wordList->Reverse();
   wordList->Report();
   delete wordList;

   std::cout << "binary search tree" << std::endl;
   BST<std::string>* wordTree = new BST<std::string>();
   ifstr.open("words.dat", std::ifstream::in | std::ifstream::binary);
   for (int i = 0; i < n; i++) {
      int recno = rnd.integer(113783, 1);
      wordTree->Insert(readRecord(ifstr, recno));
   }
   ifstr.close();
   wordTree->Report();
   delete wordTree;

   std::cout << "AVL balanced binary search tree" << std::endl;
   AVL<std::string>* strTree = new AVL<std::string>();
   ifstr.open("words.dat", std::ifstream::in | std::ifstream::binary);
   for (int i = 0; i < n; i++) {
      int recno = rnd.integer(113783, 1);
      strTree->Insert(readRecord(ifstr, recno));
   }
   ifstr.close();
   strTree->Report();
   std::cout << "serialzing tree" << std::endl;
   std::ostringstream osstr;
   strTree->Serialize(osstr);
   std::cout << "defoliating tree" << std::endl;
   strTree->Defoliate();
   strTree->Report();
   delete strTree;   

   std::cout << "deserializing tree" << std::endl;
   std::istringstream isstr(osstr.str());
   osstr.clear();
   osstr.str(std::string());
   wordTree = new BST<std::string>();
   wordTree->Deserialize(isstr);
   isstr.clear();
   isstr.str(std::string());
   wordTree->Report();
   delete wordTree;

   return 0;
}

std::string readRecord(std::ifstream& ifstr, int idx)
{
   int pos = (idx - 1) * 18;
   ifstr.seekg(pos);
   char buf[19];
   buf[18] = '\0';
   ifstr.read(buf, 18);
   return buf;
}
