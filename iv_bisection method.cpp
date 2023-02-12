#include <iostream>
#include <cmath>

using namespace std;

double bsprice(double S, double K, double r, double q, double T, double vol, char type) {
    // Black-Scholes formula
    double d1 = (log(S/K) + (r - q + 0.5*vol*vol)*T) / (vol*sqrt(T));
    double d2 = d1 - vol*sqrt(T);
    double price = 0;
    if (type == 'C') {
        price = S*exp(-q*T)*N(d1) - K*exp(-r*T)*N(d2);
    } else {
        price = K*exp(-r*T)*N(-d2) - S*exp(-q*T)*N(-d1);
    }
    return price;
}

double bsvega(double S, double K, double r, double q, double T, double vol) {
    // Black-Scholes vega
    double d1 = (log(S/K) + (r - q + 0.5*vol*vol)*T) / (vol*sqrt(T));
    double vega = S*exp(-q*T)*sqrt(T)*n(d1);
    return vega;
}

double implied_vol(double S, double K, double r, double q, double T, double price, char type) {
    // Bisection method to find implied volatility
    double a = 0.01;
    double b = 1;
    double tol = 1e-6;
    double mid = 0.5*(a+b);
    double fa = price - bsprice(S, K, r, q, T, a, type);
    double fb = price - bsprice(S, K, r, q, T, b, type);
    double fmid = price - bsprice(S, K, r, q, T, mid, type);
    while (abs(fmid) > tol) {
        if (fa*fmid < 0) {
            b = mid;
            fb = fmid;
        } else {
            a = mid;
            fa = fmid;
        }
        mid = 0.5*(a+b);
        fmid = price - bsprice(S, K, r, q, T, mid, type);
    }
    return mid;
}

int main() {
    // Example usage
    double S = 100;
    double K = 100;
    double r = 0.05;
    double q = 0.02;
    double T = 1;
    double price = 5;
    char type = 'C';
    double iv = implied_vol(S, K, r, q, T, price, type);
    cout << "Implied volatility: " << iv << endl;
    return 0;
}
