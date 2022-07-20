#include <iostream>
#include <vector>
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "TRandom.h"
#include "TMath.h"
#include "Pythia8/Pythia.h"


void initialization_pythia(Pythia8::Pythia*, TRandom*);
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


    TRandom rndm;
    rndm.SetSeed(0); // random seed number sets by this comand
    
    
    Pythia8::Pythia pythia;
    initialization_pythia(&pythia, &rndm);


    std::vector<std::vector<double>> par;
    
    
    get_configuration_data(&par);
    
    //const double m_elec = 0.000511; // GeV/c^2
    const double energy_edep_cal_med = 0.3; // GeV
    const double energy_edep_cal_sigma = 0.005; // GeV

    const int idElectron     =  11;
    const int idMu           =  13;
    const int idPi           =  211;
    const int idK            =  321;
    const int idProton       =  2212;
    


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
        if (!pythia.next()) continue;
        
        for (int i = 0; i < pythia.event.size(); ++i){
            if (fabs(pythia.event[i].eta()) > 2.){
	            continue;
            }
            if (fabs(pythia.event[i].id()) == idElectron){
                double energy_el   = pythia.event[i].e();
                double px_el       = pythia.event[i].px();
                double py_el       = pythia.event[i].py();
                double pz_el       = pythia.event[i].pz();

                double p_el = TMath::Sqrt(px_el * px_el + 
                                          py_el * py_el + 
                                          pz_el * pz_el);
                hist_true_ratio_energy_momentum_elecposi
                    ->Fill(energy_el/p_el, p_el);
                hist_smear_ratio_energy_momentum_elecposi->
                    Fill(smearE(energy_el, par[0], &rndm)/
                                smearP(p_el, par[1], &rndm), 
                                smearP(p_el, par[1], &rndm));
                
            }

            if (fabs(pythia.event[i].id()) == idMu  ||
                fabs(pythia.event[i].id()) == idPi  ||
                fabs(pythia.event[i].id()) == idK   ||
                fabs(pythia.event[i].id()) == idProton){
                double energy_h = energy_edeption(energy_edep_cal_med, 
                                                  energy_edep_cal_sigma,
                                                  &rndm);
                double px_h       = pythia.event[i].px();
                double py_h       = pythia.event[i].py();
                double pz_h       = pythia.event[i].pz();
                
                double p_h = TMath::Sqrt(px_h * px_h + 
                                         py_h * py_h + 
                                         pz_h * pz_h);
                hist_smear_ratio_energy_momentum_charged_p->
                    Fill(energy_h/smearP(p_h, par[1], &rndm), 
                         smearP(p_h, par[1], &rndm));         
            }
         }

        // double momentum = rndm.Uniform(50.);

        // double e_elecposi = TMath::Sqrt(momentum * momentum + m_elec * m_elec);

        // hist_true_ratio_energy_momentum_elecposi->Fill(e_elecposi/momentum,
        //                                                momentum);
        // hist_smear_ratio_energy_momentum_elecposi->
        //     Fill(smearE(e_elecposi, par[0], &rndm)/
        //          smearP(momentum, par[1], &rndm), 
        //          smearP(momentum, par[1], &rndm));
        // hist_smear_ratio_energy_momentum_charged_p->
        //     Fill(energy_edeption(energy_edep_cal_med, energy_edep_cal_sigma,
        //                          &rndm)/
        //          smearP(momentum, par[1], &rndm), 
        //          smearP(momentum, par[1], &rndm));

    }

    hist_true_ratio_energy_momentum_elecposi->Write();
    hist_smear_ratio_energy_momentum_elecposi->Write();
    hist_smear_ratio_energy_momentum_charged_p->Write();

    output->Close();
    
    delete output;

    return 0;
}
