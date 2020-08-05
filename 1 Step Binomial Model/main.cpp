#include <cmath>
#include <iostream>


int main()
{
	double S_0 { 100}; // stock value at time 0
    double S_u { 109};//stock value if price goes down
    double S_d { 95}; //stock value if price goes up
    double X {100}; //strike price of call
    double C_u { std::max(S_u-X,0.0)};
    double C_d { std::max(S_d-X,0.0)};
    std::cout << "If the stock goes up to " << S_u <<  " the call will be worth " << C_u << std::endl;
    std::cout << "If the stock goes up to " << S_d << " the call will be worth " << C_d << std::endl;
    double delta {(C_u-C_d)/(S_u-S_d)};
    std::cout << "By having a portfolio of " << delta << " * S - C we are hedged again the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta*S_u - C_u <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta*S_d - C_d <<std::endl;
    std::cout << "The portfolio "<< delta << " * S - C is worth "<< delta*S_d - C_d <<" to begin with." <<std::endl;
    std::cout << "Therefore "<< delta << " * " << S_0 << " - C = "<< delta*S_d - C_d << std::endl;
    std::cout << "So C = "<<  delta*S_0 -delta*S_u + C_u <<std::endl;
    std::cout << "======================" <<std::endl;
    double T {1};
    double r{0.03};
    double discount_factor {exp(-log(1+r)*T)};//1/(1+r)};
    std::cout << "If the risk-free rate was greater than zero." <<std::endl;
    std::cout << "If the interest rate is " << r << " and the stock movement is " << T << " years in the future. "<<std::endl;
    std::cout << "By having a portfolio of " << delta << " * S - C we are hedged again the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta*S_u - C_u <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta*S_d - C_d <<std::endl;
    double C{delta*S_0 - discount_factor*(delta*S_d - C_d)};
    std::cout << "The portfolio "<< delta << " * S - C is worth "<<  discount_factor*(delta*S_d - C_d) <<" to begin with." <<std::endl;
    std::cout << "Therefore "<< delta << " * " << S_0 << " - C = "<<  discount_factor*(delta*S_d - C_d) << std::endl;
    std::cout << "So C = "<<  C <<std::endl;
    
    


    std::cout << "===================== " <<std::endl;
    std::cout << "Replication " <<std::endl;
    std::cout << "===================== " <<std::endl;
    double A_0{100};
    double A_n{A_0*(r+1)};
    std::cout << "A call option can be replicated by a portfolio of x stock and y bonds/cash." <<std::endl;
    std::cout << "C(T) = xS(T) + yA(T)" <<std::endl;
    std::cout << "Where A(T) are bonds/cash worth " << A_0 << " initially and "<< A_n << " after " << T << " years. "<<std::endl;
    std::cout << "If the price stock rises:" <<std::endl;
    std::cout << "C_u(T) = xS_u(T) + yA(T)"<<std::endl;
    std::cout << C_u  << " = " << delta << " * "  << S_u << " + y * " << A_n <<std::endl;
    double y{(C_u - delta * S_u)/(A_n)};
    std::cout << "y = " << y << std::endl;
    std::cout << "The call is replicated by a portfolio of stocks and bonds/cash"<< std::endl;
    std::cout << "C(T) = "<<  delta << " S(T) "  <<  " + "<< y << " A(T)"<<std::endl;
    std::cout << "===================== " <<std::endl;
    std::cout << "Risk neutral pricing" <<std::endl;
    std::cout << "===================== " <<std::endl;
    std::cout << "The value of the call can be calculated with risk neutral pricing." <<std::endl;
    std::cout <<  "The value of the call is the present value of the expectation under the risk-neutral random walk" <<std::endl;
    std::cout << "The value of the call at initally C(0) = (p * C_u(T) +  (1 - p) * C_d(T))*exp(-(r*T)) ." <<std::endl;
    std::cout << "Where p is the risk neutral probably of the stock going up." <<std::endl;
    double U {(S_u/S_0)-1};
    double D {(S_d/S_0)-1};
    double p {((1+r)*S_0-S_d)/(S_u-S_d)};
    std::cout << "p = "<< p << std::endl;
    std::cout << "The value of C(0) = "<< p <<  " * (C_u(T) + "<<  (1 - p) << "* C_d(T))*exp(-(r*T))." <<std::endl;
    std::cout << "The value of C(0) = "<< (p * C_u +  (1 - p)* C_d )*discount_factor <<std::endl;
    return 0;
}
