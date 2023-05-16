#include <bits/stdc++.h>

using namespace std;

// algorithm for part A
double partA(double *data, int size)
{
    if(size<=1) return 0;

    double maximum[size]; // stores the maximum value from i to n
    maximum[size-1]=data[size-1];

    // preparing maximum array
    for(int ii=size-2; ii>0; ii--) 
        if(data[ii]>maximum[ii+1]) 
            maximum[ii]=data[ii];

    
    double profit=0, minimum=data[0]; // stores the net profit and minimum value so far

    if(maximum[1] - minimum >profit) 
        profit = maximum[1] - minimum;


    // checking which buy would return maximum profit
    for(int ii=0; ii<size-1; ii++)
    {
        if(data[ii]<minimum) 
            minimum = data[ii];

        if(maximum[ii+1] - minimum >profit) 
            profit = maximum[ii+1] - minimum;
    }

    return profit;
}


// algoritm for part B
double partB(double *data, int size)
{
    if(size<=1) return 0;

    bool bought=false; // true when we currently own a stock and false otherwise

    double current, profit=0; // stores the purchase value of current stock, and the net profit respectively

    // Purchasing at local minima and selling at local maxima
    for(int ii=0; ii<size-1; ii++)
    {
        if(bought)
        {
            if(data[ii]>current)
            {
                profit+=(data[ii]-current);
                bought = false;
            }
        }

        if(!bought)
        {
            if(data[ii+1]>data[ii])
            {
                bought = true;

                current = data[ii];
            }
        }
    }

    if(bought) 
        return profit + data[size-1] - current;

    return profit;
}


// algorithm for part C
double partC(double *data, int size, double x)
{
    if(size<=1) return 0;

    x/=100; // x* value will be the transaction fee now

    vector <pair<int, int>> increasingSpree; // stored the indices of monotonous increases in prices
    // basically, storing pair of local minima and maximas

    bool flag=false;
    // preparing the increasingSpree vector
    for(int ii=0; ii<size-1; ii++)
    {
        if(!flag)
        {
            if(data[ii]<data[ii+1])
            {
                increasingSpree.push_back({ii, -1});
                flag = true;
            }
        }
        else
        {
            if(data[ii]>data[ii+1])
            {
                increasingSpree.back().second = ii;
                flag = false;
            }
        }
    }

    if(flag) 
        increasingSpree.back().second = size-1;

    // Problems :
    // can't take the same stance of buying rises as in part b

    // because the x% fee might negate the profit earned

    // or holding at local maxima while there's a decline might reduce the number of transactions
    // resulting in higher net profit than immediately selling at a decline

    // the above case has to be considered only when the decrerasing spree doesn't cross the previous buyinh price

    bool bought = false; // true when we currently own a stock and false otherwise
    double current, profit=0; // stores the purchase value of current stock, and the net profit respectively

    /*
        My Algorithm and way to tackle the above problems which
        can't be solved using part B strategy

        Greedy with a few optimisations:

            -If the buy price of next pair of minima-maxima is lower than current,
             if we have to sell, we will sell right then and not hold.

            -Else, We'll find the next pair which has higher selling price than present one
             We'll do a rough comparison of which way we are better off
    */

    for(int ii=0; ii<increasingSpree.size()-1; ii++)
    {
        // buying the stock
        if(!bought)
        {
            current = data[increasingSpree[ii].first];
            bought = true;
        }

        // if the present buying price is less than current holding, we'll ditch the holding and assume we never bought it
        else if(current > data[increasingSpree[ii].first] ) 
            current = data[increasingSpree[ii].first];

        // the change net profit if we buy and sell in the present minima-maxima pair
        double delta = data[increasingSpree[ii].second] - current -x*(data[increasingSpree[ii].second] + current);
        
        if(delta<0) continue; // don't sell if change will be negative


        // the change in net profit will always be positive from here on...


        // if next day buying price is lesser, we'll have to buy at that price for obvious reasons
        // as our delta is positive, we'll encash it before moving on to the next step
        if(data[increasingSpree[ii+1].first] < current)
        {
            bought=false;
            profit+=delta;
        }
        
        // while looking into future days' data, we'll keep looking until we find a higher selling price because why would we sell for lower ("_")

        int next = 1; // variable to find how many days into the future we have to see

        double lost_delta=0; // the profit we might be losing in the middle while we keep holding the share to find a higher selling price

        // calculating the next variable and finding profit lost in the process
        while(ii+next < increasingSpree.size())
        {
            if(data[increasingSpree[ii].second] < data[increasingSpree[ii+next].second])
                break;

            double potBuy = data[increasingSpree[ii+next].first];
            double potSell = data[increasingSpree[ii+next].second];

            if(potSell - potBuy -x*(potBuy+potSell) > 0) 
                lost_delta+=(potSell - potBuy -x*(potBuy+potSell));

            next++;
        }

        if(next==size)
        {
            profit+=delta;
            bought = false;
            continue;
        }

        double potBuy = data[increasingSpree[ii+next].first];
        double potSell = data[increasingSpree[ii+next].second];
        double potential_delta = potSell - current -x*(potSell+current);

        // comparing the weights of selling at present price or selling at a higher price in future

        // if the future buy price is less than current buy price, no need to hold it till future, trivially
        if(potBuy<current || potential_delta < lost_delta)
        {
            profit+=delta;
            bought = false;
            continue;
        }
        
        // now that we removed all the negatives of holding, we can safely sell our held share at a higher price in the future
        profit+=potential_delta;
        bought=false;

        ii+=(next); // moving on to the future day

    }

    // terminating the algorithm after seeing off the last iteration
    if(bought) 
        return max(profit, profit + (1-x)*data[increasingSpree.back().second] - (1+x)*current); // if selling on last iteration is profitable or not

    // if buying as well selling on the last iteration is profitable or not
    return max(profit, profit + (1-x)*data[increasingSpree.back().second] - (1+x)*data[increasingSpree.back().first]);

    
}

int main()
{
    int size;
    cin>>size;

    double data[size], x;
    cin>>x;
    for(int ii=0; ii<size; ii++) cin>>data[ii];

    cout<<"1 transaction                 : $"<<partA(data, size)<<endl;
    cout<<"multiple transactions         : $"<<partB(data, size)<<endl;
    cout<<"transactions with "<<x<<"% fee     : $"<<partC(data, size, x)<<endl;

}