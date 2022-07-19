#include <vector>
#include "TRandom.h"
#include "TMath.h"

double smearE(double etrue, std::vector<double> par, TRandom* rndm){
    
    double sigma;
    sigma = etrue * TMath::Sqrt(par[0] * par[0] / (etrue * etrue) +
                                par[1] * par[1] / etrue + 
                                par[2] * par[2]);
    
    double esmear = rndm->Gaus(etrue, sigma);

    return esmear;
}