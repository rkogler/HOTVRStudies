#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"

#include <iostream>

#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/HOTVR.hh"

#include "TH1F.h"
#include "TH2F.h"

/**  Class to fill general hists for the HOTVR Studies e.g. mass or pt of the jets.
 *
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class HOTVRStudiesHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    HOTVRStudiesHists(uhh2::Context & ctx, const std::string & dirname, bool is_qcd);

    virtual void fill(const uhh2::Event & ev) override;
    void fill_matched(const uhh2::Event & ev);
    void fill_AK4(const Event & event);
    void fill_HOTVR(const uhh2::Event & ev);
    void fill_HOTVR_tagged(const uhh2::Event & ev);

    void fill_VR(const uhh2::Event & ev);
    void fill_SD(const uhh2::Event & ev);
    void fill_ISD(const uhh2::Event & ev);
    virtual ~HOTVRStudiesHists();

 private:
    bool b_is_qcd;
    TH1F *processed_events_ttbar, *processed_events_qcd;

    TH1F *hist_matched_jets_pt, *hist_matched_jets_mass,  *hist_matched_jets_eta, *hist_matched_jets_phi, *hist_matched_jets_energy; // Definition of hists for generel studies
    TH1F *hist_matched_parton_jets_pt, *hist_matched_parton_jets_mass,  *hist_matched_parton_jets_eta, *hist_matched_parton_jets_phi, *hist_matched_parton_jets_energy; // Definition of hists for generel studies
    TH1F *hist_parton_jets_pt, *hist_parton_jets_mass,  *hist_parton_jets_eta, *hist_parton_jets_phi, *hist_parton_jets_energy; // Definition of hists for generel studies
    TH1F *hist_tagged_jets_pt, *hist_tagged_jets_mass,  *hist_tagged_jets_eta, *hist_tagged_jets_phi, *hist_tagged_jets_energy; // Definition of hists for generel studies

    // TH1F *hist_matched_jets_notag_pt, *hist_matched_jets_notag_mass,  *hist_matched_jets_notag_eta, *hist_matched_jets_notag_phi, *hist_matched_jets_notag_energy; // Definition of hists for generel studies
    // TH1F *hist_matched_jets_notag_max_distance, *hist_matched_jets_notag_mmin, *hist_matched_jets_notag_fpt1, *hist_matched_jets_notag_nsubjets;
    // TH1F *hist_matched_parton_jets_notag_pt, *hist_matched_parton_jets_notag_mass,  *hist_matched_parton_jets_notag_eta, *hist_matched_parton_jets_notag_phi, *hist_matched_parton_jets_notag_energy; // Definition of hists for generel studies

    TH1F *hist_jets_pt, *hist_jets_mass, *hist_jets_mass_region, *hist_jets_eta, *hist_jets_phi, *hist_jets_energy; // Definition of hists for generel studies
    TH1F *hist_jets_mass_00, *hist_jets_mass_200, *hist_jets_mass_400, *hist_jets_mass_600, *hist_jets_mass_800;
    TH1F *hist_jets_mass_lowpT_N2,  *hist_jets_mass_lowpT_N3,   *hist_jets_mass_highpT_N2, *hist_jets_mass_highpT_N3; // masses of subjets in different pt regions
    TH1F *hist_jets_fpt_lowpT_N2,  *hist_jets_fpt_lowpT_N3,   *hist_jets_fpt_highpT_N2, *hist_jets_fpt_highpT_N3; // fractional leading subjet transverse momentum
    TH1F *hist_jets_mmin_lowpT, *hist_jets_mmin_highpT;

    TH1F *hist_noMJ_pt, *hist_noMJ_mass, *hist_noMJ_mass_region, *hist_noMJ_eta, *hist_noMJ_phi, *hist_noMJ_energy; // Definition of hists for generel studies
    TH1F *hist_noMJ_mass_00, *hist_noMJ_mass_200, *hist_noMJ_mass_400, *hist_noMJ_mass_600, *hist_noMJ_mass_800;

    TH1F *hist_SD_pt, *hist_SD_mass, *hist_SD_mass_region, *hist_SD_eta, *hist_SD_phi, *hist_SD_energy; // Definition of hists for generel studies
    TH1F *hist_SD_mass_00, *hist_SD_mass_200, *hist_SD_mass_400, *hist_SD_mass_600, *hist_SD_mass_800;
    TH1F *hist_SD_mass_lowpT_N2,  *hist_SD_mass_lowpT_N3,   *hist_SD_mass_highpT_N2, *hist_SD_mass_highpT_N3; // masses of subjets in different pt regions
    TH1F *hist_SD_fpt_lowpT_N2,  *hist_SD_fpt_lowpT_N3,   *hist_SD_fpt_highpT_N2, *hist_SD_fpt_highpT_N3; // fractional leading subjet transverse momentum
    TH1F *hist_SD_mmin_lowpT, *hist_SD_mmin_highpT;

    TH1F *hist_ISD_pt;
    TH1F *hist_ISD_mass_00, *hist_ISD_mass_200, *hist_ISD_mass_400, *hist_ISD_mass_600, *hist_ISD_mass_800;
    TH1F *hist_ISD_nsubjets_00, *hist_ISD_nsubjets_200, *hist_ISD_nsubjets_400, *hist_ISD_nsubjets_600, *hist_ISD_nsubjets_800;


 protected:
//pseudojets right after clustering
    uhh2::Event::Handle<std::vector<fastjet::PseudoJet>> h_HOTVRjets;
    uhh2::Event::Handle<std::vector<fastjet::PseudoJet>> h_VR_jets;
    uhh2::Event::Handle<std::vector<fastjet::PseudoJet>> h_VR_jets_SD;
    uhh2::Event::Handle<std::vector<fastjet::PseudoJet>> h_VR_jets_ISD;
    uhh2::Event::Handle<std::vector<fastjet::PseudoJet>> h_parton_jets;
// TopJets for efficiency analysis
    uhh2::Event::Handle<std::vector<TopJet>> h_top_hotvr_jets;
    uhh2::Event::Handle<std::vector<TopJet>> h_HOTVRjets_tagged;
    uhh2::Event::Handle<std::vector<TopJet>> h_top_parton_jets;
    uhh2::Event::Handle<std::vector<TopJet>> h_matched_jets;
    uhh2::Event::Handle<std::vector<std::pair<TopJet, TopJet>>> h_matched_pairs;
    // uhh2::Event::Handle<std::vector<std::pair<TopJet, TopJet>>> h_matched_pairs_notag;

};
