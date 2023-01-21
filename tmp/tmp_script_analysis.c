void tmp_script_analysis(){
  
  TFile* input = new TFile("Local_result.root", "rw");
  
  TH2D* charged = (TH2D*)input->Get("Smear_ratio_energy_momentum_for_charged_p");
  TH2D* elec = (TH2D*)input->Get("Smear_ratio_energy_momentum_for_elecposi");
  TH2D* energy_compare = (TH2D*)input->Get("Hadron_true_and_edept_energy");
  TH2D* charged_ = (TH2D*)charged->Clone();


  energy_compare->RebinX(20);
  elec->SetLineColor(kRed);
  charged->SetLineColor(kBlue);
  charged_->Add(elec);
  TH1D* slices[50];
  TH1D* slices_energy[50];
  TH1D* Landau_par_1;
  TH1D* Landau_par_2;
  Landau_par_1 = new TH1D("Landau_par_1", "Landau distribution parameter 1", 50, 0., 50.);
  Landau_par_2 = new TH1D("Landau_par_2", "Landau distribution parameter 2", 50, 0., 50.);
  TCanvas* c = new TCanvas("c", "c");
  c->Divide(5, 5);
  TCanvas* cc = new TCanvas("cc", "cc");
  cc->cd();
  energy_compare->Draw("colz");
  gStyle->SetOptStat(0);
  TCanvas* ccc = new TCanvas("ccc", "ccc");
  ccc->Divide(5, 5);
  TCanvas* cccc = new TCanvas("cccc", "cccc");

  
  TFile* outfile = new TFile("Slices.root", "RECREATE");

  for (int i = 0; i < 25; i++){
    slices[i] = (TH1D*)charged_->ProjectionX(Form("%d", i), 20*i + 1, 20*(i + 1));
    c->cd(i + 1);
    slices[i]->SetTitle(Form("p #in [%d, %d] GeV/c", i, i + 1));
    slices[i]->Draw();
    elec->ProjectionX(Form("%d_", i), 20*i + 1, 20*(i + 1))->Draw("same");
    charged->ProjectionX(Form("%d__", i), 20*i + 1, 20*(i + 1))->Draw("same");
    gStyle->SetOptStat(0);
    gPad->SetLogy();
    outfile->cd();
    slices[i]->Write();
  }

  for (int i = 0; i < 25; i++){
    slices_energy[i] = (TH1D*)energy_compare->ProjectionY(Form("%d____", i), i + 1, (i + 1));
    ccc->cd(i + 1);
    slices_energy[i]->SetAxisRange(0., 1., "X");  
    slices_energy[i]->Draw();
    TF1* func = new TF1("func", "[0]*TMath::Landau(x, [1], [2])", 0.2, 0.7);
    func->SetParameter(0, 10);
    func->SetParameter(1, 0.3);
    func->SetParameter(2, 0.01);
    func->SetParLimits(2, 0, 0.04);
    slices_energy[i]->Fit(func, "", "", 0.25, 0.6);
    Landau_par_1->SetBinContent(i + 1, func->GetParameter(1));
    Landau_par_2->SetBinContent(i + 1, func->GetParameter(2));
  }

  cccc->Divide(1, 2);
  cccc->cd(1);
  Landau_par_1->Draw();

  cccc->cd(2);
  Landau_par_2->Draw();

  c->Print("Energy_momentum_ratio.pdf");
  cc->Print("True_energy_and_energy_edeption.pdf");
  ccc->Print("Energy_distribution_slice.pdf");
  cccc->Print("Landau_distribution_parameters.pdf");


  return;
}
