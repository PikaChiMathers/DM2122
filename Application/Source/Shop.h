#pragma once

class Shop
{
private:
    int upgradeLevel[3];

public:
    Shop();
    ~Shop();

    void upgrade(int upgradeType);

    int getUpgradeLevel(int upgradeType);
};