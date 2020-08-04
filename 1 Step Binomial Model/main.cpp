#include <cmath>
#include <iostream>


int main()
{
	double S_0 { 100}; // stock value at time 0
    double S_u { 110};//stock value if price goes down
    double S_d { 90}; //stock value if price goes up
    double X {100}; //strike price of call
    double C_u { std::max(S_u-X,0.0)};
    double C_d { std::max(S_d-X,0.0)};
    std::cout << "If the stock goes up to " << S_u <<  " the call will be worth " << C_u << std::endl;
    std::cout << "If the stock goes up to " << S_d << " the call will be worth " << C_d << std::endl;
    double delta {(C_u-C_d)/(S_u-S_d)};
    std::cout << "By having a portfolio of " << delta << " * S - C we are hedged again the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta*S_u - C_u <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta*S_d - C_d <<std::endl;
    std::cout << "The portfolio "<< delta << " * S - C is worth "<< delta*S_0 - C_d <<" to begin with." <<std::endl;
    std::cout << "Therefore "<< delta << " * " <<S_0 << " - C = "<< delta*S_d - C_d << std::endl;
    std::cout << "So C = "<<  delta*S_0 -delta*S_u + C_u <<std::endl;
    double T {1};
    double r{0.05};
    std::cout << "If the risk-free rate was great than zero then the call would be worth the present value  of this. " <<std::endl;
    std::cout << "If the interest rate is " << r << " and the stock movement is " << T << " years in the future. "<<std::endl;
    std::cout << "Then C =" << std::exp(-r*T)*(delta*S_0 -delta*S_u + C_u ) <<  std::endl;
    std::cout << "Replication " <<std::endl;
    std::cout << "===================== " <<std::endl;
    double A_0{100}
    double A_n{105}
    std::cout << "A call option can be replicated by a portfolio of x stock and y bonds/cash." <<std::endl;
    std::cout << "C(T) = xS(T) + yA(T)"<<std::endl;
    std::cout << "C(T) = " delta "S(T) + yA(T)"<<std::endl;
    double y{}
    return 0;
}
