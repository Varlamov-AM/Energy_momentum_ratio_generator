#include "TRandom.h"
#include "TMath.h"
#include "TF1.h"


double energy_edeption(double energy_edep_med,
                       double energy_edep_sigma,
                       TRandom* rndm){

    double edep_energy = 
        rndm->Landau(energy_edep_med, energy_edep_sigma);

    return edep_energy;
}