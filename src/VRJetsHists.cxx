#include "UHH2/HOTVRStudies/include/VRJetsHists.h"

using namespace std;
using namespace uhh2;
using namespace fastjet;
using namespace contrib;

VRJetsHists::VRJetsHists(Context & ctx, const string & dirname, bool is_qcd):
Hists(ctx, dirname),
b_is_qcd(is_qcd)
{
// book all histograms here
// processed events
processed_events_ttbar = book<TH1F>("processed_events_ttbar", "processed events ttbar", 1,0,1);
processed_events_qcd = book<TH1F>("processed_events_qcd", "processed events qcd", 1,0,1);
// general hists
hist_pt = book<TH1F>("p_{T}", "p_{T} [GeV]", 200, 0, 2000);
hist_mass = book<TH1F>("mass", "mass [GeV]", 300, 0, 300);
hist_eta = book<TH1F>("eta", "#eta", 100, -6, 6);
hist_phi = book<TH1F>("phi", "#phi", 40, -4, 4);
hist_energy = book<TH1F>("energy", "energy [GeV]", 100, 0, 2200);
hist_nconstituents = book<TH1F>("nconstituents", "nconstituents", 200, -0.5, 199.5);
hist_mass_constituents = book<TH1F>("mass constituents", "mass constituents [GeV]", 100, 0, 1);
hist_mass_sum_constituents = book<TH1F>("mass sum constituents", "mass sum constituents [GeV]", 300, 0, 300);

// N-subjettiness
hist_tau1 = book<TH1F>("tau1", "tau1", 100, 0, 1);
hist_tau2 = book<TH1F>("tau2", "tau2", 100, 0, 1);
hist_tau3 = book<TH1F>("tau3", "tau3", 100, 0, 1);
hist_tau21 = book<TH1F>("tau21", "tau21", 100, 0, 1);
hist_tau32 = book<TH1F>("tau32", "tau32", 100, 0, 1);
}

void VRJetsHists::fill(const Event & event){}

void VRJetsHists::fill_pseudojet(const fastjet::PseudoJet & jet){
  if (b_is_qcd) {processed_events_qcd->Fill(0);}
  else{processed_events_ttbar->Fill(0);}

    hist_pt->Fill(jet.pt());
    hist_mass->Fill(jet.m());
    hist_eta->Fill(jet.eta());
    hist_phi->Fill(jet.phi());
    hist_energy->Fill(jet.E());

    double R = 1.5;
    double b = 1.0;
    // calculate Nsubjettiness
    Nsubjettiness nSub1(1, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    Nsubjettiness nSub2(2, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    Nsubjettiness nSub3(3, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    double tau1 = nSub1(jet);
    double tau2 = nSub2(jet);
    double tau3 = nSub3(jet);

    hist_tau1->Fill(tau1);
    hist_tau2->Fill(tau2);
    hist_tau3->Fill(tau3);
    hist_tau21->Fill(tau2/tau1);
    hist_tau32->Fill(tau3/tau2);
}

void VRJetsHists::fill_pseudojet_constituents(const std::vector<fastjet::PseudoJet> & jets){
  if (b_is_qcd) {processed_events_qcd->Fill(0);}
  else{processed_events_ttbar->Fill(0);}
  double mass = 0;
  double mass2 = 0;
  double px = 0;
  double py = 0;
  double pz = 0;
  double Energy = 0;
  for (size_t i = 0; i < jets.size(); i++) {
    auto jet = jets[i];
    hist_mass_constituents->Fill(jet.m());
    px += jet.four_mom()[0];
    py += jet.four_mom()[1];
    pz += jet.four_mom()[2];
    Energy += jet.four_mom()[3];
  }
  mass2=(std::pow(Energy, 2) - std::pow(px ,2) - std::pow(py,2) - std::pow(pz,2));
    if(mass2>0){mass = sqrt(abs(mass2));};
    hist_nconstituents->Fill(jets.size());
    hist_mass_sum_constituents->Fill(mass);
}

VRJetsHists::~VRJetsHists(){}
