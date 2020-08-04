#include <iostream>
#include <vector>
#include <cmath>



int main(int argc, char **argv)
{
    double S { 100};  //  price of underlying spot
    double X  {95};  // strike price
    double r {0.06};   // risk-free rate 
    double T {1};    // time until expiry
    double sigma {0.2};  //volatility
    
    int N{3}; // number of time steps
    double time_step{T/N}; //size of each time step
    //This one is CRR method
    double u{exp(sigma*sqrt(time_step))}; // the amount the stock goes up 
    double d{1/u};                      // or down at each step
    double p{(exp(r*time_step)-d)/(u-d)}; // the probability of the stock moving up at each step

    std::vector<std::vector<double>> StockPriceTree(N+1,std::vector<double>(N+1));
    std::cout << "The stock prices: " << std::endl;
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=i;j++)
        {
            StockPriceTree[i][j]=S*pow(u,j)*pow(d,i-j);
            std::cout <<i << " " << j << " " << StockPriceTree[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
    
    
    //next the tree of the call prices is created
    std::vector<std::vector<double>> CallPriceTree(N+1,std::vector<double>(N+1));
    for(int i=0;i<=N;i++)
    {
        //the prices of the calls are calculated at expiry using the asset prices at the end final time step
        CallPriceTree[N][i]=std::max(StockPriceTree[N][i]-X,0.0);
    }
    //these call prices are used to calculate the prices of the calls back down the tree
    for(int i=N-1;i>=0;i--){
        for(int j=0;j<=i;j++){
            CallPriceTree[i][j] = exp(-r*time_step)*( p*CallPriceTree[i+1][j+1] + (1-p)*CallPriceTree[i+1][j]);
        }
        
    }
    
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=i;j++)
        {
            std::cout << i << " " << j << " " << StockPriceTree[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
	return 0;
}
