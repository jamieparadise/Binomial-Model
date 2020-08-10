#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    

    std::vector<std::vector<double>> StockPrices {{100,0,0},{110,90,0},{120,100,80}};
    // the stock prices is going to be stored in a vector
    //                S_uu=120
    //        S_u=110
    //  S=100         S_ud=100
    //        S_d=90
    //                S_dd=80
    // and a vector to hold the call prices
    double T{2}; // total time after the two steps
    for(int i=0;i<=2;i++){
        std::cout << "The stock prices at time " << i*T/2 << " years:" <<std::endl;
        for (int j=0;j<=i;j++){
            std::cout << StockPrices[i][j] <<std::endl;
        }
    }
    std::vector<std::vector<double>> CallPrices (3,std::vector<double>(3));
    double X {100}; //strike price of call
    std::cout << "All of the calls i am looking at have a strike price of " << X <<std::endl;
    std::cout << "We can find the values of the calls for the final stock prices at time "<< T/2 <<":" << std::endl; 
    for (int i=0;i<=2;i++){
        CallPrices[2][i] = std::max(StockPrices[2][i]-X,0.0);
        std::cout << CallPrices[2][i] <<std::endl;
    }
    //  call values
    //               C_uu=20
    //      C_u=?
    //  C=?          C_ud=0
    //      C_d=?
    //               C_dd=0
    std::cout << "===================== " <<std::endl;
    std::cout << "Hedging (r = 0%) " <<std::endl;
    std::cout << "===================== " <<std::endl;
    std::cout << "If the stock goes up to " << StockPrices[1][0] <<  " at time t = "<< T/2 << " years and we want to hedge with a portfolio of S_u * delta_u - C_u in the next step" << std::endl;
    double delta_u {( CallPrices[2][0]- CallPrices[2][1])/(StockPrices[2][0]-StockPrices[2][1])};
    std::cout << "By having a portfolio of " << delta_u << " * S_u - C_u we are hedged again moves in the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta_u*StockPrices[2][0] - CallPrices[2][0] <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta_u*StockPrices[2][1] - CallPrices[2][1] <<std::endl;
    std::cout << "Therefore the portfolio "<< delta_u << " * S_u - C_u is worth "<< delta_u*StockPrices[2][1] - CallPrices[2][1] <<" to at time t= "<< T/2 <<std::endl;
    CallPrices[1][0] = delta_u * StockPrices[1][0] - delta_u*StockPrices[2][1] + CallPrices[2][1];
    std::cout << "So C_u = "<< CallPrices[1][0] <<std::endl;
    std::cout << "Instead, if the stock goes down to " << StockPrices[1][1] <<  " at time t = "<< T/2 << " years and we want to hedge with a portfolio of S_d * delta_d - C_d in the next step" << std::endl;
    double delta_d {( CallPrices[2][1]- CallPrices[2][2])/(StockPrices[2][1]-StockPrices[2][2])};
    std::cout << "By having a portfolio of " << delta_d << " * S_d - C_d we are hedged again moves in the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta_d*StockPrices[2][1] - CallPrices[2][1] <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta_d*StockPrices[2][2] - CallPrices[2][2] <<std::endl;
    std::cout << "Therefore the portfolio "<< delta_d << " * S_d - C_d is worth "<< delta_d*StockPrices[2][2] - CallPrices[2][2] <<" to at time t= "<< T/2 <<std::endl;   
    CallPrices[1][1] = delta_d * StockPrices[1][1] - delta_d*StockPrices[2][2] + CallPrices[2][2];
    std::cout << "So C_d = "<< CallPrices[1][1] <<std::endl;    
    std::cout << "Finally we need to find the price of C at time t=0." <<std::endl;
    double delta{(CallPrices[1][0]- CallPrices[1][1])/(StockPrices[1][0]-StockPrices[1][1])};
    std::cout << "By having a portfolio of " << delta << " * S - C we are hedged again moves in the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta*StockPrices[1][0] - CallPrices[1][0] <<std::endl; 
    std::cout << "If the stock goes down the portfolio is worth " << delta*StockPrices[1][1] - CallPrices[1][1] <<std::endl;
    std::cout << "Therefore the portfolio "<< delta << " * S - C is worth "<< delta*StockPrices[1][1] - CallPrices[1][1] <<" to at time t= "<< 0 <<std::endl;
    CallPrices[0][0] = delta * StockPrices[0][0] - delta*StockPrices[1][0] + CallPrices[1][0];
    std::cout << "So C = "<< CallPrices[0][0] <<std::endl; 
    std::cout << "===================== " <<std::endl;
    std::cout << "Hedging " <<std::endl;
    std::cout << "===================== " <<std::endl;
    
    double R{0.05}; // riskfree return over one year
    double r{log(1+R)};//0.04879... continuously compounded riskfree rate
    double discount_factor {exp(-r*T/2)};
    std::cout << "If the interest rate is " << r <<std::endl;
    std::cout << "If the stock goes up to " << StockPrices[1][0] <<  " at time t = "<< T/2 << " years and we want to hedge with a portfolio of S_u * delta_u - C_u in the next step" << std::endl;
    std::cout << "By having a portfolio of " << delta_u << " * S_u - C_u we are hedged again moves in the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta_u*StockPrices[2][0] - CallPrices[2][0] <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta_u*StockPrices[2][1] - CallPrices[2][1] <<std::endl;
    std::cout << "Therefore the portfolio "<< delta_u << " * S_u - C_u is worth "<< discount_factor*(delta_u*StockPrices[2][1] - CallPrices[2][1]) <<" to at time t= "<< T/2 <<std::endl;
    CallPrices[1][0] = delta_u*StockPrices[1][0] - discount_factor*(delta_u*StockPrices[2][1] - CallPrices[2][1]);// discount_factor
    std::cout << "So C_u = "<< CallPrices[1][0] <<std::endl;
    std::cout << "Instead, if the stock goes down to " << StockPrices[1][1] <<  " at time t = "<< T/2 << " years and we want to hedge with a portfolio of S_d * delta_d - C_d in the next step" << std::endl;
    std::cout << "By having a portfolio of " << delta_d << " * S_d - C_d we are hedged again moves in the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta_d*StockPrices[2][1] - CallPrices[2][1] <<std::endl;
    std::cout << "If the stock goes down the portfolio is worth " << delta_d*StockPrices[2][2] - CallPrices[2][2] <<std::endl;
    std::cout << "Therefore the portfolio "<< delta_d << " * S_d - C_d is worth "<< discount_factor*(delta_d*StockPrices[2][2] - CallPrices[2][2]) <<" to at time t= "<< T/2 <<std::endl;   
    CallPrices[1][1] = discount_factor*(delta_d * StockPrices[1][1] - delta_d*StockPrices[2][2] + CallPrices[2][2]);
    std::cout << "So C_d = "<< CallPrices[1][1] <<std::endl;    
    std::cout << "Finally we need to find the price of C at time t=0." <<std::endl;
    delta = (CallPrices[1][0]- CallPrices[1][1])/(StockPrices[1][0]-StockPrices[1][1]);
    std::cout << "By having a portfolio of " << delta << " * S - C we are hedged again moves in the stock price." << std::endl;
    std::cout << "If the stock goes up the portfolio is worth " << delta*StockPrices[1][0] - CallPrices[1][0] <<std::endl; 
    std::cout << "If the stock goes down the portfolio is worth " << delta*StockPrices[1][1] - CallPrices[1][1] <<std::endl;
    std::cout << "Therefore the portfolio "<< delta << " * S - C is worth "<< discount_factor*(delta*StockPrices[1][1] - CallPrices[1][1]) <<" to at time t= "<< 0 <<std::endl;
    CallPrices[0][0] = delta*StockPrices[0][0]- discount_factor*(delta*StockPrices[1][1] - CallPrices[1][1]);
    std::cout << "So C = "<< CallPrices[0][0] <<std::endl; 
    std::cout << "===================== " <<std::endl;
    std::cout << "Replication " <<std::endl;
    std::cout << "===================== " <<std::endl;
    double A_0{100};
    double A_n{A_0*exp(r*T)}; //A_0*(r+1)};
    std::cout << "A call option can be replicated by a portfolio of x stock and y bonds/cash." <<std::endl;
    std::vector<double> BondPrices {StockPrices[0][0],StockPrices[0][0]*exp(r*T/2),StockPrices[0][0]*exp(r*T)};
    std::cout << "C = xS + yA" <<std::endl;
    std::cout << "Where A is bonds/cash worth " << BondPrices[0] << " initially, "<< BondPrices[1] << " after " << T/2 << " years and " << BondPrices[2] << " after " << T << " years"<<std::endl;

    std::cout << "If the stock goes up in the first step:" << std::endl; 
    std::cout << "C_u(t) = xS_u(t) + yA(t)"<< " where t="<<T/2<< " or " << T <<std::endl;
    std::cout << "C_uu = xS_uu + yA("<<T<<")"<<std::endl;
    double y_u{(CallPrices[2][0] - delta_u * StockPrices[2][0])/BondPrices[2]};
    std::cout << CallPrices[2][0]  << " = " << delta_u << " * "  << StockPrices[2][0] << " + y * " << BondPrices[2] <<std::endl;
    std::cout << "y = " << y_u << std::endl;
    std::cout << "The call C_u(t) is replicated by a portfolio of stocks and bonds/cash between t="<<T/2<< " and " << T << std::endl;
    std::cout << "C_u(t) = "<<  delta_u << " S_u(t) "  <<  " + "<< y_u << " A(t)"<<std::endl;
    std::cout << "Therefore: "<<std::endl;
    std::cout << "C_u("<<T/2<<") = "<<  delta_u << " S_u("<<T/2<<") "  <<  " + "<< y_u << " A("<<T/2<<")"<<std::endl;
    std::cout << "C_u("<<T/2<<") = "<<  delta_u << " * " <<  StockPrices[1][0] <<  " + " << y_u << " * "<<  BondPrices[1] << " = "<< delta_u * StockPrices[1][0] + y_u * BondPrices[1] <<std::endl;
    
    std::cout << "\nInstead, if the stock goes down in the first step:" << std::endl; 
    std::cout << "C_d(t) = xS_d(t) + yA(t)"<< " where t="<<T/2<< " or " << T <<std::endl;
    std::cout << "C_du = xS_du + yA("<<T<<")"<<std::endl;
    std::cout << CallPrices[2][1]  << " = " << delta_d << " * "  << StockPrices[2][1] << " + y * " << BondPrices[2] <<std::endl;
    double y_d{(CallPrices[2][1] - delta_d * StockPrices[2][1])/BondPrices[2]};
    std::cout << "y = " << y_d << std::endl;
    std::cout << "The call C_d(t) is replicated by a portfolio of stocks and bonds/cash between t="<<T/2<< " and " << T << std::endl;
    std::cout << "C_d(t) = "<<  delta_d << " S_d(t) "  <<  " + "<< y_d << " A(T)"<<std::endl;
    std::cout << "Therefore: "<<std::endl;
    std::cout << "C_d("<<T/2<<") = "<<  delta_d << " S("<<T/2<<") "  <<  " + "<< y_d << " A("<<T/2<<")"<<std::endl;
    std::cout << "C_d("<<T/2<<") = "<<  delta_d << " * " <<  StockPrices[1][0] <<  " + " << y_d << " * "<<  BondPrices[1] << " = "<< delta_d * StockPrices[1][0] + y_d * BondPrices[1] <<std::endl;
    
    std::cout << "\nFinally, between t=0 and "<< T/2 <<" the call can be replicated by a portfolio of x stock and y bonds/cash, C(t) = xS(t) + yA(t)"<< " where t="<<0<< " or " << T/2 <<std::endl;
    std::cout << "C_u = xS_u + yA("<<T/2<<")"<<std::endl;
    std::cout << CallPrices[1][0]  << " = " << delta << " * "  << StockPrices[1][0] << " + y * " << BondPrices[1] <<std::endl;
    double y{(CallPrices[1][0] - delta * StockPrices[1][0])/(BondPrices[1])};
    std::cout << "y = " << y << std::endl;    
    std::cout << "The call C(t) is replicated by a portfolio of stocks and bonds/cash between t="<<0<< " and " << T/2 << std::endl;
    std::cout << "C(t) = "<<  delta << " S(t) "  <<  " + "<< y << " A(t)"<<std::endl;
    std::cout << "Therefore: "<<std::endl;
    std::cout << "C("<<0<<") = "<<  delta << " S("<<0<<") "  <<  " + "<< y << " A("<<0<<")"<<std::endl;
    std::cout << "C("<<0<<") = "<<  delta << " * " <<  StockPrices[0][0] <<  " + " << y << " * "<<  BondPrices[0] << " = "<< delta * StockPrices[0][0] + y * BondPrices[0] <<std::endl;
    std::cout << "===================== " <<std::endl;
    std::cout << "Risk neutral pricing" <<std::endl;
    std::cout << "===================== " <<std::endl;
    std::cout << "The value of the call can be calculated with risk neutral pricing." <<std::endl;
    std::cout <<  "The value of the call is the discounted expected value of the future payoff under the risk-neutral random walk" <<std::endl;
    std::cout << "If the stock goes up in the first step:" << std::endl; 
    std::cout << "The value of the call at t="<<T/2<< ", C_u("<<T/2<<")= (p * C_uu("<<T<<") + (1 - p) * C_ud("<<T<<"))*exp(-(r*"<<T/2<<"))" <<std::endl;
    std::cout << "Where p is the risk neutral probably of the stock going up." <<std::endl;
    double p_u{(StockPrices[1][0]*exp(r*T*0.5)-StockPrices[2][1])/(StockPrices[2][0]-StockPrices[2][1]) };//((1+r)*S_0-S_d)/(S_u-S_d)};
    std::cout << "p = "<< p_u << std::endl;
    std::cout << "The value of C_u(T/2) = ("<< p_u <<  " * C_uu(T) + "<<  (1 - p_u) << "* C_d(T))*exp(-(r*T/2))." <<std::endl;
    std::cout << "The value of C_u("<<T/2<< ") = "<< (p_u * CallPrices[2][0] +  (1 - p_u)* CallPrices[2][1] )*discount_factor <<std::endl;
    std::cout << "\nInstead, if the stock goes down in the first step:" << std::endl; 
    std::cout << "The value of the call at t="<<T/2<< ", C_d("<<T/2<<")= (p * C_du("<<T<<") + (1 - p) * C_dd("<<T<<"))*exp(-(r*"<<T/2<<"))" <<std::endl;
    std::cout << "Where p is the risk neutral probably of the stock going up." <<std::endl;
    double p_d{(StockPrices[1][1]*exp(r*T*0.5)-StockPrices[2][2])/(StockPrices[2][1]-StockPrices[2][2]) };
    std::cout << "p = "<< p_d << std::endl;
    std::cout << "The value of C_d(T/2) = ("<< p_d <<  " * C_du(T) + "<<  (1 - p_d) << "* C_dd(T))*exp(-(r*T/2))." <<std::endl;
    std::cout << "The value of C_d("<<T/2<< ") = "<< (p_d * CallPrices[2][1] +  (1 - p_d)* CallPrices[2][2] )*discount_factor <<std::endl; 
    std::cout << "\nFinally, the value of the call at t="<<0<< ", C"<<0<<")= (p * C_u("<<T/2<<") + (1 - p) * C_d("<<T/2<<"))*exp(-(r*"<<T/2<<"))" <<std::endl;
    std::cout << "Where p is the risk neutral probably of the stock going up." <<std::endl;
    double p{(StockPrices[0][0]*exp(r*T*0.5)-StockPrices[1][1])/(StockPrices[1][0]-StockPrices[1][1]) };
    std::cout << "p = "<< p << std::endl;
    std::cout << "The value of C(0) = ("<< p <<  " * C_u(T/2) + "<<  (1 - p) << "* C_d(T/2))*exp(-(r*T/2))." <<std::endl;
    std::cout << "The value of C("<<0<< ") = "<< (p * CallPrices[1][0] +  (1 - p)* CallPrices[1][1] )*discount_factor <<std::endl;
    return 0;
}

