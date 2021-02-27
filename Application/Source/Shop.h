#pragma once
#include "Sound.h"

class Shop
{
private:
    int upgradeLevel[3];
    int upgradeCost[3];

public:
    Shop();
    ~Shop();

    void upgrade(int upgradeType);

    int getUpgradeLevel(int upgradeType);
    int getUpgradeCost(int upgradeType);
    Sound sound;
};