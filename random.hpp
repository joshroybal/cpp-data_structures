#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <climits>

class Random
{ // instances represent random number generators
   public:
      Random(unsigned long=0);
      void reset_seed(unsigned long=0);
      int integer(unsigned long=ULONG_MAX, unsigned long=1);
      double real();
   private:
      unsigned long _seed;
      void randomize();
      // INVARIANT: 0 <= _seed < ULONG_MAX
};

#endif
