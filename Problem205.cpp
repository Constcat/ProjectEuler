#include <iostream>
#include <iomanip>
#include <vector>

void roll(unsigned int dices, unsigned int sides, std::vector<unsigned int>& count, unsigned int sum = 0)
{
  if (dices == 0)
  {
    count[sum]++;
    return;
  }

  for (unsigned int i = 1; i <= sides; i++)
    roll(dices - 1, sides, count, sum + i);
}

int main()
{
  unsigned int dicesPeter, sidesPeter;
  std::cin >> dicesPeter >> sidesPeter;
  unsigned int dicesColin, sidesColin;
  std::cin >> dicesColin >> sidesColin; 

  unsigned int maxTotal = std::max(dicesPeter * sidesPeter, dicesColin * sidesColin);

  std::vector<unsigned int> colin(maxTotal + 1, 0);
  roll(dicesPeter, sidesPeter, colin);
  unsigned int sumColin = 0; 
  for (auto x : colin)
    sumColin += x;

  std::vector<unsigned int> peter(maxTotal + 1, 0);
  roll(dicesColin, sidesColin, peter);
  unsigned int sumPeter = 0; 
  for (auto x : peter)
    sumPeter += x;

  double winPeter = 0;
  for (unsigned int sum = 1; sum <= maxTotal; sum++)
  {
    unsigned int numWins = 0;
    for (unsigned int j = 1; j < sum; j++)
      numWins += colin[j];

    double beats = numWins / double(sumColin);
    winPeter += beats * peter[sum] / sumPeter;
  }

  std::cout << std::fixed << std::setprecision(7) << winPeter << std::endl;
  return 0;
}
