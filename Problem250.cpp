#include <iostream>
#include <vector>

unsigned int powmod(unsigned int base, unsigned int exponent, unsigned int modulo)
{
  unsigned int result = 1;
  while (exponent > 0)
  {
    if (exponent & 1)
      result = (result * (unsigned long long)base) % modulo;

    base = (base * (unsigned long long)base) % modulo;
    exponent >>= 1;
  }
  return result;
}

int main()
{
  unsigned int limit  = 250250;
  unsigned int modulo = 250;

  std::cin >> limit >> modulo;

  std::vector<unsigned int> residues;
  for (unsigned int i = 0; i <= limit; i++)
    residues.push_back(powmod(i, i, modulo));

  const auto SixteenDigits = 10000000000000000ULL;

  std::vector<unsigned long long> current(modulo + 1, 0);

  current[0] = 1;

  auto last = current;

  for (unsigned int i = 1; i <= limit; i++)
  {
    for (unsigned int j = 0; j < modulo; j++)
    {
      if (last[j] == 0) 
        continue;      

      auto newResidue = residues[i] + j;
      
      if (newResidue >= modulo) 
        newResidue -= modulo;

      current[newResidue] += last[j];
      current[newResidue] %= SixteenDigits;
    }
    last = current;
  }

  auto result = current[0];
  
  if (result == 0)
    result = SixteenDigits;
  result--;

  std::cout << result << std::endl;
  return 0;
}
