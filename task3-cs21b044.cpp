#include <bits/stdc++.h>

using namespace std;

//candle
struct candle
{
    int open, close, low, high;
};

// hammer
bool isHammer(candle prices)
{
    int realBodySize = max(prices.open, prices.close) - min(prices.open, prices.close);

    int shadowSize = min(prices.open, prices.close) - prices.low;

    if(shadow < 2*realBodySize) return 0;

    return 1;
}

// Bulling Englufing

bool bullishEngulfing(candle pricePast, candle pricePresent)
{
    if(pricePast.open < pricePast.close || pricePresent.open > pricePresent.close ) return 0;

    if(pricePast.close >= pricePresent.open && pricePast.open <=pricePresent.close) return 1;

    return 0;
}

// Bearish Engulfing

bool bearishEngulfing(candle pricePast, candle pricePresent)
{
    if(pricePast.open > pricePast.close || pricePresent.open < pricePresent.close ) return 0;

    if(pricePast.close <= pricePresent.open && pricePast.open >=pricePresent.close) return 1;

    return 0;
}

int main()
{
    vector<candle> prices;

    for(int day=0; day<prices.size(); day++)
    {
        if(isHammer(prices[day])) cout<<"Hammer on day "<<day+1<<endl; // checks for hammer on day i
    }

    for(int day=1; day<prices.size(); day++)
    {
        if(bullishEngulfing(prices[day-1], prices[day])) cout<<"Bulling Engulfing on day "<<day+1<<endl; // checks if day i-1 and i make a bulllish engulfing
    }

    for(int day=1; day<prices.size(); day++)
    {
        if(bearishEngulfing(prices[day-1], prices[day])) cout<<"Bearish Engulfing on day "<<day+1<<endl; // checks if day i-1 and i make a bearish engulfing
    }

    return 0;
}