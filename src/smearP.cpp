#include <vector>
#include "TRandom.h"
#include "TMath.h"

double smearP(double ptrue, std::vector<double> par, TRandom* rndm){
    
    double sigma;
    sigma = ptrue * TMath::Sqrt(par[0] * par[0] + 
                                par[1] * par[1] * ptrue * ptrue);
    
    double psmear = rndm->Gaus(ptrue, sigma);

    return psmear;
}