#include "BinomTreeCall.h"

BinomTreeCall::BinomTreeCall(int N, double S, double X, double R,double T, double sigma):
    N{N},S{S},X{X},r{log(1+R)},T{T},dt{T/N},sigma{sigma}
{
    StockPriceTree.resize(N+1, std::vector<double>(N+1));
    CallPriceTree.resize(N+1, std::vector<double>(N+1));
    u=exp((r-sigma*sigma/2)*dt + sigma*sqrt(dt)); // the amount the stock goes up 
    d=exp((r-sigma*sigma/2)*dt - sigma*sqrt(dt));;                  // or down at each step
    p = (exp(r*dt)-d)/(u-d); //risk neutral prob of stock going up
    calc_StockTree();
    calc_CallTree();
}

void BinomTreeCall::calc_StockTree(){
    for(int i=0;i<=N;i++){
        for(int j=0;j<=i;j++){
            StockPriceTree[i][j]=S*pow(u,j)*pow(d,i-j);
            }
    }
}

void BinomTreeCall::print_StockTree(){
    for(int i=0;i<=N;i++){
        std::cout << "The stock prices at step " << i <<": " << std::endl;
        for(int j=i;j>=0;j--){
            std::cout  << StockPriceTree[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
}
void BinomTreeCall::calc_CallTree(){
    for(int i=0;i<=N;i++){
        //the prices of the calls are calculated at expiry using the asset prices at the end final time step
        CallPriceTree[N][i]=std::max(StockPriceTree[N][i]-X,0.0);
    }
// These call prices are used to calculate the prices of the calls back down the tree.                                                                                                                
// Using risk neutral pricing, the price of the call is the discounted expected value of the future payoff.            
// So the price of the call at time t can be found by looking at the value of the two calls at t+1,                   
// that are above and below it in the tree, and multiplying the those values by their risk neutral probability,       
// then summing them and multiplying by the discount factor C(T) = (p * C_u(T+1) + (1-p) * C_d(T+1)) * e ^ (-r*t)        
//                                                                                                                      
//     p     C_u(T+1)
//          /
//      C(T)
//          \
//     1-p   C_d(T+1)
//                                                                                                            
     
    for(int i=N-1;i>=0;i--)
    {
        for(int j=0;j<=i;j++)
        {
            CallPriceTree[i][j] = exp(-r*dt)*( p*CallPriceTree[i+1][j+1] + (1-p)*CallPriceTree[i+1][j]);
        }
    }
}

void BinomTreeCall::print_CallTree(){
    for(int i=N;i>=0;i--)
    {
        std::cout << "The call prices at step " << i <<": " << std::endl;
        for(int j=i;j>=0;j--)
        {
            std::cout << CallPriceTree[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
}

double BinomTreeCall::calc_call_price(int new_N)
{
    N=new_N;
    dt=T/N;
    StockPriceTree.resize(N+1, std::vector<double>(N+1));
    CallPriceTree.resize(N+1, std::vector<double>(N+1));
    u=exp((r-sigma*sigma/2)*dt + sigma*sqrt(dt)); // the amount the stock goes up 
    d=exp((r-sigma*sigma/2)*dt - sigma*sqrt(dt));;                  // or down at each step               
    p = (exp(r*dt)-d)/(u-d); //risk neutral prob of stock going up
    calc_StockTree();
    calc_CallTree();
    return CallPriceTree[0][0];
}

double BinomTreeCall::return_call_price(){
    return CallPriceTree[0][0];
}

BinomTreeCall::~BinomTreeCall()
{
}

