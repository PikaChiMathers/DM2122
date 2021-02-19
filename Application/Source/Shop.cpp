#include "Shop.h"

Shop::Shop() : upgradeLevel{0, 0, 0}
{

}

Shop::~Shop()
{

}

void Shop::upgrade(int upgradeType)
{
    upgradeLevel[upgradeType] += 1;
}

int Shop::getUpgradeLevel(int upgradeType)
{
    return upgradeLevel[upgradeType];
}