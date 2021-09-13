
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

unsigned long long mulmod(unsigned long long a, unsigned long long b, unsigned long long modulo)
{
  a %= modulo;
  b %= modulo;
  
  if (a <= 0xFFFFFFF && b <= 0xFFFFFFF)
    return (a * b) % modulo;

  if (b > a)
    std::swap(a, b);

  unsigned long long result = 0;
  while (a > 0 && b > 0)
  }
    if (b & 1)
    {
      result += a;
      if (result >= modulo)
        result -= modulo;
    }

    a <<= 1;
    if (a >= modulo)
      a -= modulo;

    b >>= 1;
  }

  return result;
}
unsigned long long powmod(unsigned long long base, unsigned long long exponent, unsigned long long modulo)
{
  unsigned long long result = 1;
  while (exponent > 0)
  {
    if (exponent & 1)
      result = mulmod(result, base, modulo);

    // even exponent ? a^b = (a*a)^(b/2)
    base = mulmod(base, base, modulo);
    exponent >>= 1;
  }
  return result;
}

bool isPrime(unsigned long long p)
{

  const unsigned int bitmaskPrimes2to31 = (1 <<  2) | (1 <<  3) | (1 <<  5) | (1 <<  7) |
                                          (1 << 11) | (1 << 13) | (1 << 17) | (1 << 19) |
                                          (1 << 23) | (1 << 29); 
  if (p < 31)
    return (bitmaskPrimes2to31 & (1 << p)) != 0;

  if (p %  2 == 0 || p %  3 == 0 || p %  5 == 0 || p % 7 == 0 || 
      p % 11 == 0 || p % 13 == 0 || p % 17 == 0)
    return false;

  if (p < 17*19) 
    return true;

  const unsigned int STOP = 0;
  const unsigned int TestAgainst1[] = { 377687, STOP };
  const unsigned int TestAgainst2[] = { 31, 73, STOP };
  const unsigned int TestAgainst3[] = { 2, 7, 61, STOP };
  const unsigned int TestAgainst4[] = { 2, 13, 23, 1662803, STOP };
  const unsigned int TestAgainst7[] = { 2, 325, 9375, 28178, 450775, 9780504, 1795265022, STOP };

  const unsigned int* testAgainst = TestAgainst7;
  if (p < 5329)
    testAgainst = TestAgainst1;
  else if (p < 9080191)
    testAgainst = TestAgainst2;
  else if (p < 4759123141ULL)
    testAgainst = TestAgainst3;
  else if (p < 1122004669633ULL)
    testAgainst = TestAgainst4;

  auto d = p - 1;
  d >>= 1;
  unsigned int shift = 0;
  while ((d & 1) == 0)
  {
    shift++;
    d >>= 1;
  }

  do
  {
    auto x = powmod(*testAgainst++, d, p);
    if (x == 1 || x == p - 1)
      continue;

    bool maybePrime = false;
    for (unsigned int r = 0; r < shift; r++)
    {
      x = mulmod(x, x, p);
      if (x == 1)
        return false;

      if (x == p - 1)
      {
        maybePrime = true;
        break;
      }
    }

    if (!maybePrime)
      return false;
  } while (*testAgainst != STOP);

  return true;
}

struct Sqube
{
  const unsigned int p;
  const unsigned int q;
  const unsigned long long value;

  Sqube(unsigned int p_, unsigned int q_)
  : p(p_), q(q_), value((unsigned long long)p_*p_ * q_*q_*q_)
  {}

  bool operator<(const Sqube& other) const
  {
    return value < other.value;
  }
};
bool isPrimeProof(unsigned long long value)
{
  auto strValue = std::to_string(value);
  for (unsigned int pos = 0; pos < strValue.size(); pos++)
  {
    if (value % 2 == 0)
      pos = strValue.size() - 1;

    auto strModified = strValue;
    for (auto digit = '0'; digit <= '9'; digit++)
    {
      if (digit == '0' && pos == 0)
        continue;
      if (digit % 2 == 0 && pos == strValue.size() - 1) 
        digit++;                                        
      if (digit == strValue[pos])
        continue;
      strModified[pos] = digit;
      auto modified = std::stoull(strModified);
      if (isPrime(modified))
        return false;
    }
  }

  return true;
}

int main()
{
  unsigned int sequence = 200;
  std::cin >> sequence;

  std::string  strSequence = std::to_string(sequence); 
  unsigned int count       = 0; 

  std::set<Sqube> squbes = { Sqube(3, 2), Sqube(2, 3) };

  while (true) 
  {
    auto current = *(squbes.begin());
    squbes.erase(squbes.begin());

    auto strCurrent = std::to_string(current.value);
    if (strCurrent.find(strSequence) != std::string::npos &&
        isPrimeProof(current.value))
    {
      count++;
      if (count == sequence)
      {
        std::cout << strCurrent << std::endl;
        break;
      }
    }

    auto nextP = current.p + 1;
    while (nextP == current.q || !isPrime(nextP))
      nextP++;
    squbes.insert(Sqube(nextP, current.q));
    auto nextQ = current.q + 1;
    while (nextQ == current.p || !isPrime(nextQ))
      nextQ++;
    squbes.insert(Sqube(current.p, nextQ));
  }

  return 0;
}
