#include "Shop.h"

Shop::Shop() : upgradeLevel{0, 0, 0}, upgradeCost{300, 300, 300}
{

}

Shop::~Shop()
{

}

void Shop::upgrade(int upgradeType)
{
    upgradeLevel[upgradeType] += 1;
    sound.Engine()->play2D("media/keching.wav");
    upgradeCost[upgradeType] = 300 + upgradeLevel[upgradeType] * 200;
}

int Shop::getUpgradeLevel(int upgradeType)
{
    return upgradeLevel[upgradeType];
}

int Shop::getUpgradeCost(int upgradeType)
{
    return upgradeCost[upgradeType];
}