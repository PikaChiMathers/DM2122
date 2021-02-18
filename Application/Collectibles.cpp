#include "Collectibles.h"

Collectibles::Collectibles()
{
    data = 0;
}

void Collectibles::tookCollectible(bool got)
{
    if (got == true)
    {
        data++;
    }
}

int Collectibles::getCollectbleAmt()
{
    return data;
}
