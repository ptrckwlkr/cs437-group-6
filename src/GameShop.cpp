#include "GameShop.h"

GameShop::GameShop()
{
  int statSum;
  int stats[5];
  int price;

  for (int i = 1; i < 10; ++i)
  {
    auto set = (EquipSet)i;
    for (int j = 0; j < 6; ++j)
    {
      statSum = 6 * i + (rand() % i);
      stats[0] = 0;
      stats[1] = 0;
      stats[2] = 0;
      stats[3] = 0;
      stats[4] = 0;
      while (statSum)
      {
        int s = rand() % 5;
        stats[s]++;
        statSum--;
      }
      price = 200 * i + (rand() % (i * 10));

      auto slot = (EquipSlot)j;
      Entry item = {
              price,
              false,
              std::make_shared<Equipment>(set, slot, stats[0], stats[1], stats[2], stats[3], stats[4])
      };
      items.push_back(item);
    }
  }
}
