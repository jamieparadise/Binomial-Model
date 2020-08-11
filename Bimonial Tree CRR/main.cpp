#include "BinomTreeCall.h"
#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char **argv)
{
    double S { 100};  //  spot price  
    double X  {100};  // strike price
    double R{0.05}; //riskfree return over one year
    double r{log(1+R)};//0.04879... continuously compounded riskfree rate
    double T {1};    // time until expiry
    double sigma {0.085};  //volatility
    int N{4}; // number of time steps
   // double call_price {binom_tree_call_price(N,S,X,r,T,sigma)};
    BinomTreeCall call_tree(N,S,X,R,T,sigma); 
    double price{};
    std::cout << "The call price with N="<<N<< ", S="<<S<<", X="<<X<<", r="<<r<<", T="<<T<<", sigma="<<sigma<<": "<< call_tree.return_call_price()<< std::endl;
    for(int i=500;i<=3000;i+=500){
        price = call_tree.calc_call_price(i);
        std::cout << "The call price with N="<<i<< ", S="<<S<<", X="<<X<<", r="<<r<<", T="<<T<<", sigma="<<sigma<<": " << price<<std::endl; 
    }
    std::cout << "The call seems to get about 3 decimal place accuracy with 2000-3000 steps"<< std::endl;
	return 0;
}