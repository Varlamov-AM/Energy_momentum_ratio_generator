#include <iostream>
#include <vector>
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "TRandom.h"
#include "TMath.h"


void get_configuration_data(std::vector<std::vector<double>>*);
double smearP(double, std::vector<double>, TRandom*);
double smearE(double, std::vector<double>, TRandom*);

int main(int argc, char* argv[]){

    int n_events = 0;

    if (argc > 1){
        n_events = atoi(argv[1]);
    } else {
        std::cout << 
        "Don't find numbers of events to generate in input!" <<
        std::endl;
        return 1;
    }
    
    std::cout << "N events to generate: " << n_events << std::endl;

    std::vector<std::vector<double>> par;
    std::vector<double> en = {0.018, 0.033, 0.011};
    std::vector<double> mo = {0.008, 0.002};
    
    
    get_configuration_data(&par);
    
    //par.push_back(en);
    //par.push_back(mo);

    TRandom rndm;
    rndm.SetSeed(0); // random seed number sets by this comand
    
    const double m_elec = 0.000511; // GeV/c^2

    TFile* output = new TFile("Energy_momentum_ratio_data.root", "RECREATE");

    TH2D* hist_true_ratio_energy_momentum = 
        new TH2D("True_ratio_energy_momentum", "e^{-} p value", 
        1000, 0.3, 2.,
        100, 0., 50);
    TH2D* hist_smear_ratio_energy_momentum = 
        new TH2D("Smear_ratio_energy_momentum", "e^{-} p value", 
        1000, 0.3, 2.,
        1000, 0., 50);

    for (int i = 0; i < n_events; i++){
        double momentum = rndm.Uniform(50.);
        
        // double phi      = rndm.Uniform(TMath::TwoPi());
        // double theta    = rndm.Uniform(TMath::Pi());

        // double px = momentum * TMath::Cos(phi) * TMath::Sin(theta);
        // double py = momentum * TMath::Sin(phi) * TMath::Sin(theta);
        // double pz = momentum * TMath::Cos(theta);

        // TLorentzVector fmommetum(px, py, pz, e);

        double e = TMath::Sqrt(momentum * momentum + m_elec * m_elec);

        hist_true_ratio_energy_momentum->Fill(e/momentum, momentum);
        hist_smear_ratio_energy_momentum->
            Fill(smearE(e, par[0], &rndm)/smearP(momentum, par[1], &rndm), 
                 smearP(momentum, par[1], &rndm));

    }

    hist_true_ratio_energy_momentum->Write();
    hist_smear_ratio_energy_momentum->Write();

    output->Close();
    
    delete output;

    return 0;
}
