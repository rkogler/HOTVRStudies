#include "UHH2/HOTVRStudies/include/HOTVRStudiesHists.h"

using namespace std;
using namespace uhh2;
using namespace fastjet;
using namespace contrib;

HOTVRStudiesHists::HOTVRStudiesHists(Context & ctx, const string & dirname, bool is_qcd):
Hists(ctx, dirname),
b_is_qcd(is_qcd)
{
// book all histograms here
processed_events_ttbar = book<TH1F>("processed_events_ttbar", "processed events ttbar", 1,0,1);
processed_events_qcd = book<TH1F>("processed_events_qcd", "processed events qcd", 1,0,1);

// general hists for the tagging efficiency
// the toptagged and matched particle level jets (HOTVR jets)
hist_matched_jets_pt = book<TH1F>("p_{T}_matched_jets", "HOTVR matched jets p_{T} [GeV]", 100, 0, 1800);
hist_matched_jets_mass = book<TH1F>("mass_matched_jets", "HOTVR matched jets mass [GeV]", 100, 0, 300);
hist_matched_jets_eta = book<TH1F>("eta_matched_jets", "HOTVR matched jets #eta", 100, -6, 6);
hist_matched_jets_phi = book<TH1F>("phi_matched_jets", "HOTVR matched jets #phi", 40, -4, 4);
hist_matched_jets_energy = book<TH1F>("energy_matched_jets", "HOTVR matched jets energy [GeV]", 100, 0, 2200);
// the matched parton level jets (AK4 jets)
hist_matched_parton_jets_pt = book<TH1F>("p_{T}_matched_parton_jets", "HOTVR matched parton jets p_{T} [GeV]", 100, 0, 1800);
hist_matched_parton_jets_mass = book<TH1F>("mass_matched_parton_jets", "HOTVR matched parton jets mass [GeV]", 300, 0, 300);
hist_matched_parton_jets_eta = book<TH1F>("eta_matched_parton_jets", "HOTVR matched parton jets #eta", 100, -6, 6);
hist_matched_parton_jets_phi = book<TH1F>("phi_matched_parton_jets", "HOTVR matched parton jets #phi", 40, -4, 4);
hist_matched_parton_jets_energy = book<TH1F>("energy_matched_parton_jets", "HOTVR matched parton jets energy [GeV]", 100, 0, 2200);
// the parton level jets without matching (AK4 jets)
hist_parton_jets_pt = book<TH1F>("p_{T}_parton_jets", "HOTVR parton jets p_{T} [GeV]", 100, 0, 1800);
hist_parton_jets_mass = book<TH1F>("mass_parton_jets", "HOTVR parton jets mass [GeV]", 300, 0, 300);
hist_parton_jets_eta = book<TH1F>("eta_parton_jets", "HOTVR parton jets #eta", 100, -6, 6);
hist_parton_jets_phi = book<TH1F>("phi_parton_jets", "HOTVR parton jets #phi", 40, -4, 4);
hist_parton_jets_energy = book<TH1F>("energy_parton_jets", "HOTVR parton jets energy [GeV]", 100, 0, 2200);
// the tagged hotvr jets
hist_tagged_jets_pt = book<TH1F>("p_{T}_tagged_jets", "HOTVR tagged jets p_{T} [GeV]", 100, 0, 1800);
hist_tagged_jets_mass = book<TH1F>("mass_tagged_jets", "HOTVR tagged jets mass [GeV]", 100, 0, 300);
hist_tagged_jets_eta = book<TH1F>("eta_tagged_jets", "HOTVR tagged jets #eta", 100, -6, 6);
hist_tagged_jets_phi = book<TH1F>("phi_tagged_jets", "HOTVR tagged jets #phi", 40, -4, 4);
hist_tagged_jets_energy = book<TH1F>("energy_tagged_jets", "HOTVR tagged jets energy [GeV]", 100, 0, 2200);
//NO TAG
// the toptagged and matched particle level jets (HOTVR jets)
// hist_matched_jets_notag_pt = book<TH1F>("p_{T}_matched_jets_notag", "HOTVR matched jets_notag p_{T} [GeV]", 100, 0, 1800);
// hist_matched_jets_notag_mass = book<TH1F>("mass_matched_jets_notag", "HOTVR matched jets_notag mass [GeV]", 300, 0, 300);
// hist_matched_jets_notag_eta = book<TH1F>("eta_matched_jets_notag", "HOTVR matched jets_notag #eta", 100, -6, 6);
// hist_matched_jets_notag_phi = book<TH1F>("phi_matched_jets_notag", "HOTVR matched jets_notag #phi", 40, -4, 4);
// hist_matched_jets_notag_energy = book<TH1F>("energy_matched_jets_notag", "HOTVR matched jets_notag energy [GeV]", 100, 0, 2200);
// hist_matched_jets_notag_max_distance = book<TH1F>("max_distance_matched_jets_notag", "HOTVR matched jets_notag max_distance [GeV]", 100, 0, 2);
// hist_matched_jets_notag_mmin = book<TH1F>("mmin_matched_jets_notag", "HOTVR matched jets_notag mmin [GeV]", 200, 0, 200);
// hist_matched_jets_notag_fpt1 = book<TH1F>("fpt_matched_jets_notag", "HOTVR matched jets_notag fpt", 300, 0, 1);
// hist_matched_jets_notag_nsubjets = book<TH1F>("nsubjets_matched_jets_notag", "HOTVR matched jets_notag nsubjets", 6, 0, 6);


// the matched parton level jets (AK4 jets)
// hist_matched_parton_jets_notag_pt = book<TH1F>("p_{T}_matched_parton_jets_notag", "HOTVR matched parton jets_notag p_{T} [GeV]", 100, 0, 1800);
// hist_matched_parton_jets_notag_mass = book<TH1F>("mass_matched_parton_jets_notag", "HOTVR matched parton jets_notag mass [GeV]", 300, 0, 300);
// hist_matched_parton_jets_notag_eta = book<TH1F>("eta_matched_parton_jets_notag", "HOTVR matched parton jets_notag #eta", 100, -6, 6);
// hist_matched_parton_jets_notag_phi = book<TH1F>("phi_matched_parton_jets_notag", "HOTVR matched parton jets_notag #phi", 40, -4, 4);
// hist_matched_parton_jets_notag_energy = book<TH1F>("energy_matched_parton_jets_notag", "HOTVR matched parton jets_notag energy [GeV]", 100, 0, 2200);


//GENERAL HISTS for the clustered HOTVR jets
  hist_jets_pt = book<TH1F>("p_{T}_jets", "HOTVR jets p_{T} [GeV]", 100, 0, 1800);
  hist_jets_mass = book<TH1F>("mass_jets", "HOTVR jets mass [GeV]", 100, 0, 300);
//   hist_jets_mass_00 = book<TH1F>("mass_jets_00", "HOTVR jets mass 0 [GeV]", 100, 0, 300);
//   hist_jets_mass_200 = book<TH1F>("mass_jets_200", "HOTVR jets mass 200 [GeV]", 100, 0, 300);
//   hist_jets_mass_400 = book<TH1F>("mass_jets_400", "HOTVR jets mass 400 [GeV]", 100, 0, 300);
//   hist_jets_mass_600 = book<TH1F>("mass_jets_600", "HOTVR jets mass 600 [GeV]", 100, 0, 300);
//   hist_jets_mass_800 = book<TH1F>("mass_jets_800", "HOTVR jets mass 800 [GeV]", 100, 0, 300);
//   hist_jets_mass_region = book<TH1F>("mass_jets_region", "HOTVR jets mass region [GeV]", 100, 30, 300);
  hist_jets_eta = book<TH1F>("eta_jets", "HOTVR jets #eta", 100, -6, 6);
  hist_jets_phi = book<TH1F>("phi_jets", "HOTVR jets #phi", 20, -4, 4);
  hist_jets_energy = book<TH1F>("energy_jets", "HOTVR jets energy [GeV]", 100, 0, 2200);

//   //noMJ
//     hist_noMJ_pt = book<TH1F>("p_{T}_jets_noMJ", "HOTVR noMJ jets p_{T} [GeV]", 100, 0, 1800);
//     hist_noMJ_mass = book<TH1F>("mass_jets_noMJ", "HOTVR noMJ jets mass [GeV]", 100, 0, 300);
//     hist_noMJ_mass_00 = book<TH1F>("mass_jets_noMJ_00", "HOTVR noMJ jets mass 0 [GeV]", 100, 0, 300);
//     hist_noMJ_mass_200 = book<TH1F>("mass_jets_noMJ_200", "HOTVR noMJ jets mass 200 [GeV]", 100, 0, 300);
//     hist_noMJ_mass_400 = book<TH1F>("mass_jets_noMJ_400", "HOTVR noMJ jets mass 400 [GeV]", 100, 0, 300);
//     hist_noMJ_mass_600 = book<TH1F>("mass_jets_noMJ_600", "HOTVR noMJ jets mass 600 [GeV]", 100, 0, 300);
//     hist_noMJ_mass_800 = book<TH1F>("mass_jets_noMJ_800", "HOTVR noMJ jets mass 800 [GeV]", 100, 0, 300);
// //    hist_noMJ_mass_region = book<TH1F>("mass_jets_noMJ_region", "HOTVR noMJ jets mass region [GeV]", 100, 30, 300);
//     hist_noMJ_eta = book<TH1F>("eta_jets_noMJ", "HOTVR noMJ jets #eta", 100, -6, 6);
//     hist_noMJ_phi = book<TH1F>("phi_jets_noMJ", "HOTVR noMJ jets #phi", 20, -4, 4);
//     hist_noMJ_energy = book<TH1F>("energy_jets_noMJ", "HOTVR noMJ jets energy [GeV]", 100, 0, 2200);
// //SD
//   hist_SD_pt = book<TH1F>("p_{T}_jets_SD", "HOTVR SD jets p_{T} [GeV]", 100, 0, 1800);
//   hist_SD_mass = book<TH1F>("mass_jets_SD", "HOTVR SD jets mass [GeV]", 100, 0, 300);
//   hist_SD_mass_00 = book<TH1F>("mass_jets_SD_00", "HOTVR SD jets mass 0 [GeV]", 100, 0, 300);
//   hist_SD_mass_200 = book<TH1F>("mass_jets_SD_200", "HOTVR SD jets mass 200 [GeV]", 100, 0, 300);
//   hist_SD_mass_400 = book<TH1F>("mass_jets_SD_400", "HOTVR SD jets mass 400 [GeV]", 100, 0, 300);
//   hist_SD_mass_600 = book<TH1F>("mass_jets_SD_600", "HOTVR SD jets mass 600 [GeV]", 100, 0, 300);
//   hist_SD_mass_800 = book<TH1F>("mass_jets_SD_800", "HOTVR SD jets mass 800 [GeV]", 100, 0, 300);
// //  hist_SD_mass_region = book<TH1F>("mass_jets_SD_region", "HOTVR SD jets mass region [GeV]", 100, 30, 300);
//   hist_SD_eta = book<TH1F>("eta_jets_SD", "HOTVR SD jets #eta", 100, -6, 6);
//   hist_SD_phi = book<TH1F>("phi_jets_SD", "HOTVR SD jets #phi", 20, -4, 4);
//   hist_SD_energy = book<TH1F>("energy_jets_SD", "HOTVR SD jets energy [GeV]", 100, 0, 2200);

// //SPLITTED MASS HISTS HOTVR jets
  // hist_jets_mass_lowpT_N2 = book<TH1F>("mass_lowpT_N2_jets", "HOTVR jets mass [GeV]", 120, 0, 300); //was befor 100, 0, 350
  //  hist_jets_mass_lowpT_N3 = book<TH1F>("mass_lowpT_N3_jets", "HOTVR jets mass [GeV]", 120, 0, 300);
  //  hist_jets_mass_highpT_N2 = book<TH1F>("mass_highpT_N2_jets", "HOTVR jets mass [GeV]", 120, 0, 300);
  //  hist_jets_mass_highpT_N3 = book<TH1F>("mass_highpT_N3_jets","HOTVR jets mass [GeV]", 120, 0, 300);

   // //fractional leading subjet transverse momentum
   // hist_jets_fpt_lowpT_N2 = book<TH1F>("fpt_lowpT_N2_jets", "HOTVR jets f_p_T [GeV]", 60, 0, 1); //was befor 100, 0,1
   // hist_jets_fpt_lowpT_N3 = book<TH1F>("fpt_lowpT_N3_jets", "HOTVR jets f_p_T [GeV]", 60, 0, 1);
   // hist_jets_fpt_highpT_N2 = book<TH1F>("fpt_highpT_N2_jets", "HOTVR jets f_p_T [GeV]", 60, 0, 1);
   // hist_jets_fpt_highpT_N3 = book<TH1F>("fpt_highpT_N3_jets","HOTVR jets f_p_T [GeV]", 60, 0, 1);

   //mmin
   // hist_jets_mmin_lowpT = book<TH1F>("mmin_lowpT_jets", "HOTVR jets m_{min} [GeV]", 80, 0, 140); //was befor 100, 0, 140
   // hist_jets_mmin_highpT = book<TH1F>("mmin_highpT_jets", "HOTVR jets m_{min} [GeV]", 80, 0, 140);

// //SPLITTED MASS HISTS  SD
   // hist_SD_mass_lowpT_N2 = book<TH1F>("mass_lowpT_N2_SD", "HOTVR SD jets mass [GeV]", 120, 0, 300);
   //  hist_SD_mass_lowpT_N3 = book<TH1F>("mass_lowpT_N3_SD", "HOTVR SD jets mass [GeV]", 120, 0, 300);
   //  hist_SD_mass_highpT_N2 = book<TH1F>("mass_highpT_N2_SD", "HOTVR SD jets mass [GeV]", 120, 0, 300);
   //  hist_SD_mass_highpT_N3 = book<TH1F>("mass_highpT_N3_SD","HOTVR SD jets mass [GeV]", 120, 0, 300);

    // //fractional leading subjet transverse momentum
    // hist_SD_fpt_lowpT_N2 = book<TH1F>("fpt_lowpT_N2_SD", "HOTVR SD jets f_p_T [GeV]", 60, 0, 1);
    // hist_SD_fpt_lowpT_N3 = book<TH1F>("fpt_lowpT_N3_SD", "HOTVR SD jets f_p_T [GeV]", 60, 0, 1);
    // hist_SD_fpt_highpT_N2 = book<TH1F>("fpt_highpT_N2_SD", "HOTVR SD jets f_p_T [GeV]", 60, 0, 1);
    // hist_SD_fpt_highpT_N3 = book<TH1F>("fpt_highpT_N3_SD","HOTVR SD jets f_p_T [GeV]", 60, 0, 1);

    //mmin
    //  hist_SD_mmin_lowpT = book<TH1F>("mmin_lowpT_SD", "HOTVR SD jets m_{min} [GeV]", 80, 0, 140);
    //  hist_SD_mmin_highpT = book<TH1F>("mmin_highpT_SD", "HOTVR SD jets m_{min} [GeV]", 80, 0, 140);


// initialise handle
  h_HOTVRjets = ctx.get_handle<vector<fastjet::PseudoJet>>("HOTVRjets");
  h_VR_jets = ctx.get_handle<vector<fastjet::PseudoJet>>("VRjets");
  h_VR_jets_SD = ctx.get_handle<vector<fastjet::PseudoJet>>("VRjetsSD");
  h_VR_jets_ISD = ctx.get_handle<vector<fastjet::PseudoJet>>("VRjetsISD");
  h_parton_jets = ctx.get_handle<vector<fastjet::PseudoJet>>("parton_jets");

  h_top_hotvr_jets = ctx.get_handle<vector<TopJet>>("top_hotvr_jets");
  h_HOTVRjets_tagged = ctx.get_handle<vector<TopJet>>("HOTVRjets_tagged");
  h_matched_jets = ctx.get_handle<vector<TopJet>>("matched_jets");

  h_matched_pairs = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs");
//  h_matched_pairs_notag = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs_notag");

  h_top_parton_jets = ctx.get_handle<vector<TopJet>>("top_parton_jets");

}
/*
███████ ██ ██      ██
██      ██ ██      ██
█████   ██ ██      ██
██      ██ ██      ██
██      ██ ███████ ███████
*/


void HOTVRStudiesHists::fill(const Event & event){
  if (b_is_qcd) {
  processed_events_qcd->Fill(0);
  }
  else{
  processed_events_ttbar->Fill(0);
  }

//  fill_matched(event);
//  fill_HOTVR(event);
//  fill_AK4(event);
//  fill_HOTVR_tagged(event);

  //fill_VR(event);
  //fill_SD(event);
  fill_ISD(event);
}
/*
███████ ██ ██      ██          ███████ ███████ ███████
██      ██ ██      ██          ██      ██      ██
█████   ██ ██      ██          █████   █████   █████
██      ██ ██      ██          ██      ██      ██
██      ██ ███████ ███████     ███████ ██      ██
*/

//fill general hists for tagging efficiency plots
void HOTVRStudiesHists::fill_matched(const Event & event)
{
  const auto &matched_jets = event.get(h_matched_jets);

  for(unsigned int i=0; i<matched_jets.size(); ++i){
  //  const auto &matched_jet = matched_pairs[i].first;
  //  const auto &matched_parton_jet = matched_pairs[i].second;
    const auto &matched_jet = matched_jets[i];

    hist_matched_jets_pt->Fill(matched_jet.pt());
    hist_matched_jets_mass->Fill(matched_jet.v4().M());
    hist_matched_jets_eta->Fill(matched_jet.eta());
    hist_matched_jets_phi->Fill(matched_jet.phi());
    hist_matched_jets_energy->Fill(matched_jet.v4().E());

    // hist_matched_parton_jets_pt->Fill(matched_parton_jet.pt());
    // hist_matched_parton_jets_mass->Fill(matched_parton_jet.v4().M());
    // hist_matched_parton_jets_eta->Fill(matched_parton_jet.eta());
    // hist_matched_parton_jets_phi->Fill(matched_parton_jet.phi());
    // hist_matched_parton_jets_energy->Fill(matched_parton_jet.v4().E());
  }
//  const auto &matched_pairs_notag = event.get(h_matched_pairs_notag);

  //for(unsigned int i=0; i<matched_pairs_notag.size(); ++i){
  //  const auto &matched_jet_notag = matched_pairs_notag[i].first;
  //  const auto &matched_parton_jet_notag = matched_pairs_notag[i].second;

    // hist_matched_jets_notag_pt->Fill(matched_jet_notag.pt());
    // hist_matched_jets_notag_mass->Fill(matched_jet_notag.v4().M());
    // hist_matched_jets_notag_eta->Fill(matched_jet_notag.eta());
    // hist_matched_jets_notag_phi->Fill(matched_jet_notag.phi());
    // hist_matched_jets_notag_energy->Fill(matched_jet_notag.v4().E());
    // hist_matched_jets_notag_max_distance->Fill(matched_jet_notag.max_distance());
    // hist_matched_jets_notag_mmin->Fill(matched_jet_notag.hotvr_mmin());
    // hist_matched_jets_notag_fpt1->Fill(matched_jet_notag.hotvr_fpt1());
    // hist_matched_jets_notag_nsubjets->Fill(matched_jet_notag.subjets().size());

    // hist_matched_parton_jets_notag_pt->Fill(matched_parton_jet_notag.pt());
    // hist_matched_parton_jets_notag_mass->Fill(matched_parton_jet_notag.v4().M());
    // hist_matched_parton_jets_notag_eta->Fill(matched_parton_jet_notag.eta());
    // hist_matched_parton_jets_notag_phi->Fill(matched_parton_jet_notag.phi());
    // hist_matched_parton_jets_notag_energy->Fill(matched_parton_jet_notag.v4().E());
  //}
}
void HOTVRStudiesHists::fill_AK4(const Event & event)
{
  const auto &parton_jets = event.get(h_top_parton_jets);

  for(unsigned int i=0; i<parton_jets.size(); ++i){
    hist_parton_jets_pt->Fill(parton_jets[i].pt());
    hist_parton_jets_mass->Fill(parton_jets.at(i).v4().M());
    hist_parton_jets_eta->Fill(parton_jets[i].eta());
    hist_parton_jets_phi->Fill(parton_jets[i].phi());
    hist_parton_jets_energy->Fill(parton_jets[i].v4().E());
  }
}

void HOTVRStudiesHists::fill_HOTVR_tagged(const Event & event){
  const auto &tagged_jets = event.get(h_HOTVRjets_tagged);

  for(unsigned int i=0; i<tagged_jets.size(); ++i){
    hist_tagged_jets_pt->Fill(tagged_jets[i].pt());
    hist_tagged_jets_mass->Fill(tagged_jets.at(i).v4().M());
    hist_tagged_jets_eta->Fill(tagged_jets[i].eta());
    hist_tagged_jets_phi->Fill(tagged_jets[i].phi());
    hist_tagged_jets_energy->Fill(tagged_jets[i].v4().E());
  }
}

/*
███████ ██ ██      ██          ██   ██  ██████  ████████ ██    ██ ██████
██      ██ ██      ██          ██   ██ ██    ██    ██    ██    ██ ██   ██
█████   ██ ██      ██          ███████ ██    ██    ██    ██    ██ ██████
██      ██ ██      ██          ██   ██ ██    ██    ██     ██  ██  ██   ██
██      ██ ███████ ███████     ██   ██  ██████     ██      ████   ██   ██
*/


//fill hists for clustered HOTVR jets
void HOTVRStudiesHists::fill_HOTVR(const Event & event)
{
  const auto &hotvr_jets = event.get(h_top_hotvr_jets);

  for (unsigned int i=0; i<hotvr_jets.size(); ++i){
    //// general hists
    hist_jets_pt->Fill(hotvr_jets[i].pt());
    hist_jets_mass->Fill(hotvr_jets[i].v4().M());
    hist_jets_eta->Fill(hotvr_jets[i].eta());
    hist_jets_phi->Fill(hotvr_jets[i].phi());
    hist_jets_energy->Fill(hotvr_jets[i].v4().E());

     // int nsubjets = hotvr_jets[i].user_info<HOTVRinfo>().nsubjets();
    //  double pt = hotvr_jets[i].pt();

     // vector<fastjet::PseudoJet> subjets = sorted_by_pt(hotvr_jets[i].user_info<HOTVRinfo>().subjets());
     // double ptfraction = hotvr_jets[i].user_info<HOTVRinfo>().ptfraction(0);
     // int mmin = hotvr_jets[i].user_info<HOTVRinfo>().mmin();

  //   double gptfraction = SD_hotvr_jets[i].user_info<HOTVRinfo>().ptfraction(0);
  //   int gmmin = SD_hotvr_jets[i].user_info<HOTVRinfo>().mmin();

     // if(pt < 200){
     //   hist_jets_mass_00->Fill(hotvr_jets[i].m());
     // }
     // else if(200 <= pt && pt < 400){
     //   hist_jets_mass_200->Fill(hotvr_jets[i].m());
     // }
     // else if(400 <= pt && pt < 600){
     //   hist_jets_mass_400->Fill(hotvr_jets[i].m());
     // }
     // else if(600 <= pt && pt < 800){
     //   hist_jets_mass_600->Fill(hotvr_jets[i].m());
     // }
     // else{
     //   hist_jets_mass_800->Fill(hotvr_jets[i].m());
     // }

    // hist_jets_mass_region->Fill(hotvr_jets[i].m());



// //SPLITTED MASS HISTS, fractional leading subjet transverse momentum and mmin
//      if(200 < pt && pt < 400){
//        if(nsubjets >= 2){
// 	 hist_jets_mass_lowpT_N2 ->Fill(hotvr_jets[i].m()); //jet mass
// //	 hist_jets_fpt_lowpT_N2 ->Fill(ptfraction); //ptfraction
//        }
//        if(nsubjets >= 3){
// 	 hist_jets_mass_lowpT_N3 ->Fill(hotvr_jets[i].m());
// 	// hist_jets_fpt_lowpT_N3 ->Fill(ptfraction);
// 	// hist_jets_mmin_lowpT ->Fill(mmin); //minimum pairwise mass
//        }
//      }
//      else if(600 < pt && pt < 800){
//        if(nsubjets >= 2){
// 	 hist_jets_mass_highpT_N2 ->Fill(hotvr_jets[i].m());
// 	// hist_jets_fpt_highpT_N2 ->Fill(ptfraction);
//        }
//        if(nsubjets >= 3){
// 	 hist_jets_mass_highpT_N3 ->Fill(hotvr_jets[i].m());
// //	 hist_jets_fpt_highpT_N3 ->Fill(ptfraction);
// 	// hist_jets_mmin_highpT ->Fill(mmin);
//        }
//      }
// //SD
// if(200 < pt && pt < 400){
//   if(nsubjets >= 2){
// hist_SD_mass_lowpT_N2 ->Fill(hotvr_jets_SD[i].m()); //jet mass
// //hist_SD_fpt_lowpT_N2 ->Fill(gptfraction); //ptfraction
//   }
//   if(nsubjets >= 3){
// hist_SD_mass_lowpT_N3 ->Fill(hotvr_jets_SD[i].m());
// //hist_SD_fpt_lowpT_N3 ->Fill(gptfraction);
// //hist_SD_mmin_lowpT ->Fill(gmmin); //minimum pairwise mass
//   }
// }
// else if(600 < pt && pt < 800){
//   if(nsubjets >= 2){
// hist_SD_mass_highpT_N2 ->Fill(hotvr_jets_SD[i].m());
// //hist_SD_fpt_highpT_N2 ->Fill(gptfraction);
//   }
//   if(nsubjets >= 3){
// hist_SD_mass_highpT_N3 ->Fill(hotvr_jets_SD[i].m());
// //hist_SD_fpt_highpT_N3 ->Fill(gptfraction);
// //hist_SD_mmin_highpT ->Fill(gmmin);
//   }
// }
//
  }
}

/*
███████ ██ ██      ██          ██    ██ ██████
██      ██ ██      ██          ██    ██ ██   ██
█████   ██ ██      ██          ██    ██ ██████
██      ██ ██      ██           ██  ██  ██   ██
██      ██ ███████ ███████       ████   ██   ██
*/


void HOTVRStudiesHists::fill_VR(const Event & event){
  const auto &hotvr_jets_noMJ = event.get(h_VR_jets);

  for(unsigned int i=0; i<hotvr_jets_noMJ.size(); ++i){
    double pt = hotvr_jets_noMJ[i].pt();

    hist_noMJ_pt->Fill(hotvr_jets_noMJ[i].pt());
    hist_noMJ_mass->Fill(hotvr_jets_noMJ.at(i).m());
    if(pt < 200){
      hist_noMJ_mass_00->Fill(hotvr_jets_noMJ[i].m());
    }
    else if(200 <= pt && pt < 400){
      hist_noMJ_mass_200->Fill(hotvr_jets_noMJ[i].m());
    }
    else if(400 <= pt && pt < 600){
      hist_noMJ_mass_400->Fill(hotvr_jets_noMJ[i].m());
    }
    else if(600 <= pt && pt < 800){
      hist_noMJ_mass_600->Fill(hotvr_jets_noMJ[i].m());
    }
    else{
      hist_noMJ_mass_800->Fill(hotvr_jets_noMJ[i].m());
    }
  //  hist_noMJ_mass_region->Fill(hotvr_jets_noMJ.at(i).m());
  //  hist_noMJ_eta->Fill(hotvr_jets_noMJ[i].eta());
  //  hist_noMJ_phi->Fill(hotvr_jets_noMJ[i].phi_std());
  //  hist_noMJ_energy->Fill(hotvr_jets_noMJ[i].E());
  }
}
/*
███████ ██ ██      ██          ███████ ██████
██      ██ ██      ██          ██      ██   ██
█████   ██ ██      ██          ███████ ██   ██
██      ██ ██      ██               ██ ██   ██
██      ██ ███████ ███████     ███████ ██████
*/

void HOTVRStudiesHists::fill_SD(const Event & event){
  // const auto &hotvr_jets_SD = event.get(h_VR_jets_SD);
  //
  // for(unsigned int i=0; i<hotvr_jets_SD.size(); ++i){
  //   double pt = hotvr_jets_SD[i].pt();
  //
  //   hist_SD_pt->Fill(hotvr_jets_SD[i].pt());
  //   hist_SD_mass->Fill(hotvr_jets_SD.at(i).m());
  //   if(pt < 200){
  //     hist_SD_mass_00->Fill(hotvr_jets_SD[i].m());
  //   }
  //   else if(200 <= pt && pt < 400){
  //     hist_SD_mass_200->Fill(hotvr_jets_SD[i].m());
  //   }
  //   else if(400 <= pt && pt < 600){
  //     hist_SD_mass_400->Fill(hotvr_jets_SD[i].m());
  //   }
  //   else if(600 <= pt && pt < 800){
  //     hist_SD_mass_600->Fill(hotvr_jets_SD[i].m());
  //   }
  //   else{
  //     hist_SD_mass_800->Fill(hotvr_jets_SD[i].m());
  //   }
  // //  hist_SD_mass_region->Fill(hotvr_jets_SD.at(i).m());
  // //  hist_SD_eta->Fill(hotvr_jets_SD[i].eta());
  // //  hist_SD_phi->Fill(hotvr_jets_SD[i].phi_std());
  // //  hist_SD_energy->Fill(hotvr_jets_SD[i].E());
  // }
}

void HOTVRStudiesHists::fill_ISD(const Event & event){
  // const auto &vr_jets_ISD = event.get(h_VR_jets_ISD);
  //
  // for(unsigned int i=0; i<vr_jets_ISD.size(); ++i){
  //   auto jet = vr_jets_ISD[i];
  //   double pt = jet.pt();
  //
  //   hist_ISD_pt->Fill(jet.pt());
  //   hist_ISD_mass->Fill(jet.m());
  //   if(pt < 200){
  //     hist_ISD_mass_00->Fill(jet.m());
  //   }
  //   else if(200 <= pt && pt < 400){
  //     hist_ISD_mass_200->Fill(jet.m());
  //   }
  //   else if(400 <= pt && pt < 600){
  //     hist_ISD_mass_400->Fill(jet.m());
  //   }
  //   else if(600 <= pt && pt < 800){
  //     hist_ISD_mass_600->Fill(jet.m());
  //   }
  //   else{
  //     hist_SD_mass_800->Fill(jet.m());
  //   }
  // //  hist_SD_eta->Fill(hotvr_jets_SD[i].eta());
  // //  hist_SD_phi->Fill(hotvr_jets_SD[i].phi_std());
  // //  hist_SD_energy->Fill(hotvr_jets_SD[i].E());
  // }
}

HOTVRStudiesHists::~HOTVRStudiesHists(){}
