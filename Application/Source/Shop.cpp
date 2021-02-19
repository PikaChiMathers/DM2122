#include "Shop.h"

Shop::Shop() : upgradeLevel()
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