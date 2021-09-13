#include <iostream>

int main()
{
  unsigned int index = 124;
  std::cin >> index;

  const unsigned int MaxSteps = 22710;

  unsigned int current  = 1; 

  unsigned int numFound = 0;
  while (numFound < index)
  {
    current += 2;

    unsigned int tri1 = 1;
    unsigned int tri2 = 1;
    unsigned int tri3 = 1;

    bool isDivisor = false;
    for (unsigned int step = 0; step <= MaxSteps; step++)
    {
      unsigned int triNext = tri1 + tri2 + tri3;

      triNext %= current;

      if (triNext == 0)
      {
        isDivisor = true;
        break;
      }

      tri1 = tri2;
      tri2 = tri3;
      tri3 = triNext;

      if (tri1 == 1 && tri2 == 1 && tri3 == 1)
        break;
    }

    if (!isDivisor)
      numFound++;
  }

  std::cout << current << std::endl;
  return 0;
}
