#include <iostream>
#include <fstream>
// #include "bst.hpp"
#include "avl.hpp"

int main()
{
   /*
   AVL<std::string> wordTree;
   std::ifstream ifstr("/home/slacker/dat/words.txt", std::ifstream::in);
   while (true) {
      std::string word;
      ifstr >> word;
      if (ifstr.eof()) break;
      wordTree.Insert(word);
   }
   ifstr.close();
   wordTree.Report();
   std::cout << "serializing tree" << std::endl;
   std::ofstream ofstr("tree.dat", std::ofstream::out);
   wordTree.Serialize(ofstr);
   ofstr.close();
   */
   AVL<std::string> wordTree;
   std::ifstream ifstr("tree.dat", std::ifstream::in);
   wordTree.Deserialize(ifstr);
   ifstr.close();
   std::cout << "size = " << wordTree.Size() << std::endl;
   std::cout << "height = " << wordTree.Height() << std::endl;
   wordTree.Min();
   wordTree.Max();
   std::string colors[] = { "red", "orange", "yellow", "green", "blue",
      "indigo", "violet" };
   for (int i = 0; i < 7; i++) wordTree.Search(colors[i]);
   for (int i = 0; i < 7; i++) wordTree.Remove(colors[i]);
   for (int i = 0; i < 7; i++) wordTree.Search(colors[i]);
   std::string colores[] = { "rojo", "anaranjado", "amarillo", "verde", "azul",
      "indigo", "violeta" };
   for (int i = 0; i < 7; i++) wordTree.Search(colores[i]);
   for (int i = 0; i < 7; i++) wordTree.Insert(colores[i]);
   for (int i = 0; i < 7; i++) wordTree.Search(colores[i]);
   return 0;
}
