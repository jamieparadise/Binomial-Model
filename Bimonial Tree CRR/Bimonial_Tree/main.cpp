#include <iostream>
#include <vector>
#include <cmath>

double binom_tree_call_price(int N, double S, double X, double r,double T, double sigma) {
    double time_step{T/N}; //size of each time step
    // CRR method
    double u{exp(sigma*sqrt(time_step))}; // the amount the stock goes up 
    double d{1/u};                      // or down at each step
    double p{(exp(r*time_step)-d)/(u-d)}; // the risk neutral probability of the stock moving up at each step

    std::vector<std::vector<double>> StockPriceTree(N+1,std::vector<double>(N+1));
    
    for(int i=0;i<=N;i++){
        for(int j=0;j<=i;j++){
            StockPriceTree[i][j]=S*pow(u,j)*pow(d,i-j);
            }
        std::cout << std::endl;
    }
    
    for(int i=0;i<=N;i++){
        std::cout << "The stock prices at step " << i <<": " << std::endl;
        for(int j=i;j>=0;j--){
            std::cout  << StockPriceTree[i][j] << std::endl;
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
            CallPriceTree[i][j] = exp(-r*time_step)*( p*CallPriceTree[i+1][j+1] + (1-p)*CallPriceTree[i+1][j]);
        }
    }
    
    for(int i=N;i>=0;i--)
    {
        std::cout << "The call prices at step " << i <<": " << std::endl;
        for(int j=i;j>=0;j--)
        {
            std::cout << CallPriceTree[i][j] << std::endl;
        }
        std::cout << std::endl;
    }
    return CallPriceTree[0][0];
}

int main(int argc, char **argv)
{
    double S { 100};  //  spot price  
    double X  {100};  // strike price
    double R{0.05}; //riskfree return over one year
    double r{log(1+R)};//0.04879... continuously compounded riskfree rate
    double T {2};    // time until expiry
    double sigma {0.1};  //volatility
    int N{2}; // number of time steps
    double call_price {binom_tree_call_price(N,S,X,r,T,sigma)};
    std::cout << "The call price with N="<<N<< ", S="<<S<<", X="<<X<<", r="<<r<<", T="<<T<<", sigma="<<sigma<<": "<< call_price << std::endl;

	return 0;
}