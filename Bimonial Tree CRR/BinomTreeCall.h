#ifndef BINOMTREECALL_H
#define BINOMTREECALL_H
#include <vector>
#include <cmath>
#include <iostream>
class BinomTreeCall
{
private:
    double S;  //  spot price  
    double X;  // strike price
    double R; //riskfree return over one year
    double r;// continuously compounded riskfree rate
    double T;    // time until expiry
    double sigma;  //volatility
    int N; // the number of steps in the binomial tree
    double dt;// the size of each time step
    double u; // the amount the stock goes up 
    double d; // or down at each step
    double p;
    std::vector<std::vector<double>> StockPriceTree;
    std::vector<std::vector<double>> CallPriceTree;
public:
    BinomTreeCall(int N, double S, double X, double R,double T, double sigma);
    void calc_StockTree();
    void print_StockTree();
    void calc_CallTree();
    void print_CallTree();
    double return_call_price();
    double calc_call_price(int new_N);
    ~BinomTreeCall();

};

#endif // BINOMTREECALL_H
