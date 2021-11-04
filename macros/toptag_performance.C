#include "TSystem.h"
#include <vector>

#include <iostream>

#include "include/cosmetics.h"

vector<char*> get_filenames(const char* ext)
{
  const char* inDir = "/nfs/dust/cms/user/albrecha/uhh2_102X_v2/HOTVRStudiesOutput/root/HOTVR_SD_final/ptt0_mu40";
  char* dir = gSystem->ExpandPathName(inDir);
  void* dirp = gSystem->OpenDirectory(dir);
  const char* entry;
  vector<char*> filenames;
  TString str;
  while((entry = (char*)gSystem->GetDirEntry(dirp))) {
    str = entry;
    if(str.Contains(ext))
      filenames.push_back(gSystem->ConcatFileName(dir, entry));
  }
  return filenames;
}

void toptag_performance()
{
  Int_t n_ptbins = 5;
  Double_t pt_xbins[6] = {0, 200, 400, 600, 1000, 2000};
  int n_points = 100;

  TH1F* a_ttbar_hotvr = new TH1F("A_ttbar_HOTVR", "P_{T}", n_ptbins, pt_xbins);
  vector<TH1F*> b_ttbar_hotvr;
  for (int i = 0; i < n_points; ++i)
    {
      string name = "B_ttbar_HOTVR_" + to_string(i);
      b_ttbar_hotvr.push_back(new TH1F(name.c_str(), "P_{T}", n_ptbins, pt_xbins));
    }

  TH1F* a_QCD_hotvr = new TH1F("A_QCD_HOTVR", "P_{T}", n_ptbins, pt_xbins);
  vector<TH1F*> b_QCD_hotvr;
  for (int i = 0; i < n_points; ++i)
    {
      string name = "B_QCD_HOTVR_" + to_string(i);
      b_QCD_hotvr.push_back(new TH1F(name.c_str(), "P_{T}", n_ptbins, pt_xbins));
    }

  vector<char*> filenames = get_filenames(".root");
  std::cout << filenames.size() << '\n';

  for (int i = 0; i < filenames.size(); ++i) //loop over root files
    {
      TFile *f = new TFile(filenames.at(i));
      TString filename = filenames.at(i);
      std::cout << filename << '\n';

      if (filename.Contains(".ttbar")) // fill ttbar
	{
    std::cout << filename << '\n';
	  a_ttbar_hotvr->Add((TH1F*)f->Get("HOTVR_Pre/pt_gentop"));
	  for (int i = 0; i < n_points; ++i)
	    {
	      std::string name_hotvr = "HOTVR_Performance_" + to_string(i) + "/pt_top_matched";
	      b_ttbar_hotvr.at(i)->Add((TH1F*)f->Get(name_hotvr.c_str()));
	    }
	}
      if (filename.Contains(".QCD")) // fill QCD
	{
    std::cout << filename << '\n';
	  a_QCD_hotvr->Add((TH1F*)f->Get("HOTVR_Pre/pt_gen"));
	  for (int i = 0; i < n_points; ++i)
	    {
	      std::string name_hotvr = "HOTVR_Performance_" + to_string(i) + "/pt_top_mismatched";
	      b_QCD_hotvr.at(i)->Add((TH1F*)f->Get(name_hotvr.c_str()));
	    }
	}
    }

  gStyle->SetOptStat(0);

  TCanvas *c = new TCanvas("c", "c", 600, 600);

  TPad* pad = SetupPad();
  pad->Draw();
  pad->cd();
  gPad->SetTicks();
  for (int bin = 1; bin < n_ptbins+1; ++bin){

    double N_ttbar_HOTVR = a_ttbar_hotvr->GetBinContent(bin);
    double N_QCD_HOTVR = a_QCD_hotvr->GetBinContent(bin);
    TGraphErrors *HOTVR = new TGraphErrors(n_points);

    for (int i = 0; i < n_points; ++i)
      {
	       double x_hotvr = b_ttbar_hotvr.at(i)->GetBinContent(bin) / N_ttbar_HOTVR;
	       double y_hotvr = b_QCD_hotvr.at(i)->GetBinContent(bin) / N_QCD_HOTVR;
        // std::cout << "Point " <<i << ", signal: " << x_hotvr << ", bkg: "<<y_hotvr << '\n';
	       HOTVR->SetPoint(i, x_hotvr, y_hotvr);
      }

    HOTVR->SetLineWidth(2);
    HOTVR->SetLineColor(kRed);

    TGraphErrors *hotvr_wp = new TGraphErrors(1);
    hotvr_wp->SetPoint(1,HOTVR->GetX()[50], HOTVR->GetY()[50]);
    hotvr_wp->SetMarkerStyle(23); hotvr_wp->SetMarkerColor(1);

    TMultiGraph *mg = new TMultiGraph();
    mg->Add(HOTVR);
    mg->Add(hotvr_wp, "P");
    mg->Draw("AL");

    gPad->Modified(); gPad->Update(); // make sure it's really (re)drawn;
    mg->SetTitle();
    Hist_Cosmetics(mg, false);
    mg->GetXaxis()->SetTitle("#varepsilon_{S}");
    mg->GetYaxis()->SetTitle("#varepsilon_{B}");
    mg->SetMaximum(0.1);
    mg->SetMinimum(1e-4);
    mg->GetXaxis()->SetLimits(0,0.6);
    gPad->Modified(); gPad->Update(); // make sure it's really (re)drawn;


    std::string interval;
    interval = to_string((int)pt_xbins[bin-1]) + "GeV < p_{T} < " + to_string((int)pt_xbins[bin]) + "GeV";

    TLegend *leg = new TLegend(0.4,0.19,0.7,0.34);
    leg->SetFillColor(0);
    leg->SetLineColor(1);
    leg->SetBorderSize(0);
    leg->SetTextSize(.04);
    leg->SetFillStyle(0);
    leg->SetHeader(interval.c_str());
    leg->AddEntry(HOTVR, "HOTVR TopTagger", "l");
    leg->Draw();

    TLegend *leg_wp = new TLegend(0.55,0.36,0.8,0.7);
    leg_wp->SetFillColor(0);
    leg_wp->SetLineColor(1);
    leg_wp->SetBorderSize(0);
    leg_wp->SetTextSize(.03);
    leg_wp->SetFillStyle(0);
    leg_wp->AddEntry((TObject*)0, "HOTVR TopTagger:", "");
    leg_wp->AddEntry(hotvr_wp,  "WP: #tau_{3/2}<0.56", "p");
    leg_wp->Draw();


    pad->SetLogy();
    std::string name = "SD_ptt30_mu30_Performance_PtBin_" + to_string(bin) + ".eps";
    std::string rootname = "SD_ptt30_mu30_Performance_PtBin_" + to_string(bin) + ".root";
    c->Print(name.c_str());
    TFile *MyFile = new TFile(rootname.c_str(),"RECREATE");
    HOTVR->Write();
    MyFile->Close();

  }
}
