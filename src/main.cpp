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
double energy_edeption(double, double, TRandom*);


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
    
    
    get_configuration_data(&par);
    
    //par.push_back(en);
    //par.push_back(mo);

    TRandom rndm;
    rndm.SetSeed(0); // random seed number sets by this comand
    
    const double m_elec = 0.000511; // GeV/c^2
    const double energy_edep_cal_med = 0.3; // GeV
    const double energy_edep_cal_sigma = 0.005; // GeV


    TFile* output = new TFile("Energy_momentum_ratio_data.root", "RECREATE");

    TH2D* hist_true_ratio_energy_momentum_elecposi = 
        new TH2D("True_ratio_energy_momentum_for_elecposi", "E/p for e^{#pm}", 
        1000, 0., 2.,
        100, 0., 50);
    TH2D* hist_smear_ratio_energy_momentum_elecposi = 
        new TH2D("Smear_ratio_energy_momentum_for_elecposi","E/p for e^{#pm}", 
        1000, 0., 2.,
        1000, 0., 50);
    TH2D* hist_smear_ratio_energy_momentum_charged_p = 
        new TH2D("Smear_ratio_energy_momentum_for_charged_p",
        "E/p charged particles", 
        1000, 0., 2.,
        1000, 0., 50);

    for (int i = 0; i < n_events; i++){
        double momentum = rndm.Uniform(50.);

        double e_elecposi = TMath::Sqrt(momentum * momentum + m_elec * m_elec);

        hist_true_ratio_energy_momentum_elecposi->Fill(e_elecposi/momentum,
                                                       momentum);
        hist_smear_ratio_energy_momentum_elecposi->
            Fill(smearE(e_elecposi, par[0], &rndm)/
                 smearP(momentum, par[1], &rndm), 
                 smearP(momentum, par[1], &rndm));
        hist_smear_ratio_energy_momentum_charged_p->
            Fill(energy_edeption(energy_edep_cal_med, energy_edep_cal_sigma,
                                 &rndm)/
                 smearP(momentum, par[1], &rndm), 
                 smearP(momentum, par[1], &rndm));

    }

    hist_true_ratio_energy_momentum_elecposi->Write();
    hist_smear_ratio_energy_momentum_elecposi->Write();
    hist_smear_ratio_energy_momentum_charged_p->Write();

    output->Close();
    
    delete output;

    return 0;
}
