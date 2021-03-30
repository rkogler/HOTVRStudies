#include <iostream>
#include <memory>
// include general UHH2 classes
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/TopJetIds.h"
// include everything from the HOTVR Studies
#include "UHH2/HOTVRStudies/include/Matching.h"
#include "UHH2/HOTVRStudies/include/Clustering.h"
#include "UHH2/HOTVRStudies/include/TopTagger.h"
#include "UHH2/HOTVRStudies/include/TopTagPerformanceHists.h"
#include "UHH2/HOTVRStudies/include/HOTVRJetsHists.h"
#include "UHH2/HOTVRStudies/include/VRJetsHists.h"
#include "UHH2/HOTVRStudies/include/SoftClusterHists.h"
#include "UHH2/HOTVRStudies/include/Makefiles.h"
// include from HOTVR for the performance hists
#include "UHH2/HOTVR/include/HOTVRIds.h"
// include from fastjet
#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/HOTVRinfo.hh"
#include "fastjet/contrib/HOTVR.hh"

using namespace std;
using namespace uhh2;
using namespace fastjet;
using namespace contrib;

/** AnalysisModule for HOTVR Studies.
*
* This is the central class which calls other AnalysisModules, Hists or Selection classes.
* This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
*/

class HOTVRStudiesModule: public AnalysisModule {
public:

  explicit HOTVRStudiesModule(Context & ctx);
  virtual bool process(Event & event) override;

private:
//initialize hist classes
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_fpt;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_fpt_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_fpt_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_fpt_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_fpt_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_fpt_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mass;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mass_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mass_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mass_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mass_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mass_1000;

  std::unique_ptr<HOTVRJetsHists> hist_matched_jets;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_200;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_400;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_600;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_800;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_1000;

  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_Nsub3;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_Nsub3_200;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_Nsub3_400;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_Nsub3_600;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_Nsub3_800;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_Nsub3_1000;
  //
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_fpt;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_fpt_200;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_fpt_400;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_fpt_600;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_fpt_800;
  // std::unique_ptr<HOTVRJetsHists> hist_matched_jets_fpt_1000;

  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_200;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_400;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_600;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_800;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_1000;

  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_tau32;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_tau32_200;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_tau32_400;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_tau32_600;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_tau32_800;
  std::unique_ptr<HOTVRJetsHists> hist_tagged_jets_tau32_1000;

  // std::unique_ptr<SoftClusterHists> hist_rejected_subjets;
  // std::unique_ptr<SoftClusterHists> hist_rejected_subjets_200;
  // std::unique_ptr<SoftClusterHists> hist_rejected_subjets_400;
  // std::unique_ptr<SoftClusterHists> hist_rejected_subjets_600;
  // std::unique_ptr<SoftClusterHists> hist_rejected_subjets_800;
  // std::unique_ptr<SoftClusterHists> hist_rejected_subjets_1000;
  //
  // std::unique_ptr<SoftClusterHists> hist_rejected_cluster;
  // std::unique_ptr<SoftClusterHists> hist_rejected_cluster_200;
  // std::unique_ptr<SoftClusterHists> hist_rejected_cluster_400;
  // std::unique_ptr<SoftClusterHists> hist_rejected_cluster_600;
  // std::unique_ptr<SoftClusterHists> hist_rejected_cluster_800;
  // std::unique_ptr<SoftClusterHists> hist_rejected_cluster_1000;
  //
  // std::unique_ptr<SoftClusterHists> hist_soft_cluster;
  // std::unique_ptr<SoftClusterHists> hist_soft_cluster_200;
  // std::unique_ptr<SoftClusterHists> hist_soft_cluster_400;
  // std::unique_ptr<SoftClusterHists> hist_soft_cluster_600;
  // std::unique_ptr<SoftClusterHists> hist_soft_cluster_800;
  // std::unique_ptr<SoftClusterHists> hist_soft_cluster_1000;

   std::unique_ptr<VRJetsHists> hist_vr_jets;
  // std::unique_ptr<VRJetsHists> hist_hotvr_jet_constituents;
  // std::unique_ptr<VRJetsHists> hist_hotvr_jet_constituents_200;
  // std::unique_ptr<VRJetsHists> hist_hotvr_jet_constituents_400;
  // std::unique_ptr<VRJetsHists> hist_hotvr_jet_constituents_600;
  // std::unique_ptr<VRJetsHists> hist_hotvr_jet_constituents_800;
  // std::unique_ptr<VRJetsHists> hist_hotvr_jet_constituents_1000;
  //
  // std::unique_ptr<VRJetsHists> hist_vr_jets_ISD;
  // std::unique_ptr<VRJetsHists> hist_vr_jets_ISD_200;
  // std::unique_ptr<VRJetsHists> hist_vr_jets_ISD_400;
  // std::unique_ptr<VRJetsHists> hist_vr_jets_ISD_600;
  // std::unique_ptr<VRJetsHists> hist_vr_jets_ISD_800;
  // std::unique_ptr<VRJetsHists> hist_vr_jets_ISD_1000;

// initialize event handle
  Event::Handle<vector<TopJet>> h_matched_jets;
  Event::Handle<vector<TopJet>> h_matched_parton_jets;
  Event::Handle<vector<pair<TopJet, TopJet>>> h_matched_pairs; //contains pair of matched jets
    // denominator for the ROC curves first: ttbar, second:qcd

// for performance study
  std::unique_ptr<AnalysisModule> cl_topjet_hotvr;
  std::unique_ptr<Selection> sel_ntop_hotvr;
  std::unique_ptr<Selection> sel_toptag_hotvr, sel_toptag_softdrop;

  // --- Scans --- //
  std::unique_ptr<Hists> hist_hotvr_pre, hist_softdrop_pre;
  std::vector<std::unique_ptr<Selection>> sel_hotvr, sel_softdrop;
  std::vector<std::unique_ptr<Hists>> hist_hotvr, hist_softdrop;
  int n_points = 100;

// initialize classes
  string m_clustering;
  Matching* matching;
  Clustering* clustering;
  TopTagger* toptagger;

// for the csv files for ML studies
  string m_csvfile_ttbar;
  string m_csvfile_qcd;
  Makefiles* makefiles;

// initialize vectors of jets
// ... containing pseudojets
  vector<fastjet::PseudoJet> pseudojets;
  vector<fastjet::PseudoJet> hotvr_jets;
  vector<vector<fastjet::PseudoJet>> hotvr_jets_constituents;
  vector<fastjet::PseudoJet> vr_jets;
  vector<vector<fastjet::PseudoJet>> vr_jets_constituents;
  vector<fastjet::PseudoJet> vr_jets_SD;
  vector<fastjet::PseudoJet> vr_jets_ISD;
  vector<fastjet::PseudoJet> parton_pseudojets;
  vector<fastjet::PseudoJet> parton_jets;
// ... containing UHH2(top)jets (in order to save the tau32 values)
  vector<TopJet> _top_hotvr_jets;
  vector<TopJet> _top_vr_jets;
  vector<TopJet> _top_parton_jets;

  vector<Jet> _rejected_subjets; // rejected subjets with ptsub
  vector<TopJet> _rejected_cluster; // rejected cluster (jets without subjets)
  vector<TopJet> _soft_cluster; // soft cluster rejected via softdrop / massjump condition

  string dataset_version;

  bool isTTbar;
  bool is_mc, is_qcd;

  int nevent=0;
};

/*
 ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
 ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

HOTVRStudiesModule::HOTVRStudiesModule(Context & ctx){
  cout << "Starting HOTVRStudiesModule!" << endl;
// get info from xml
  m_clustering = ctx.get("Clustering");
  m_csvfile_ttbar = ctx.get("csvfile_ttbar");
  m_csvfile_qcd = ctx.get("csvfile_qcd");
// check for the dataset version (ttbar or QCD)
  dataset_version = ctx.get("dataset_version");
  isTTbar = dataset_version.find("ttbar") == 0;
  is_mc = ctx.get("dataset_type") == "MC";
  is_qcd = (dataset_version.find("QCD") == 0);

//declare event handle
  h_matched_jets = ctx.get_handle<vector<TopJet>>("matched_jets");
  h_matched_parton_jets = ctx.get_handle<vector<TopJet>>("matched_parton_jets");
  h_matched_pairs = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs");

// Set up Hists classes:
  hist_hotvr_jets.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets", is_qcd));
  hist_hotvr_jets_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_200", is_qcd));
  hist_hotvr_jets_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_400", is_qcd));
  hist_hotvr_jets_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_600", is_qcd));
  hist_hotvr_jets_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_800", is_qcd));
  hist_hotvr_jets_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_1000", is_qcd));

  hist_hotvr_jets_Nsub3.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3", is_qcd));
  hist_hotvr_jets_Nsub3_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_200", is_qcd));
  hist_hotvr_jets_Nsub3_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_400", is_qcd));
  hist_hotvr_jets_Nsub3_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_600", is_qcd));
  hist_hotvr_jets_Nsub3_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_800", is_qcd));
  hist_hotvr_jets_Nsub3_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_1000", is_qcd));

  hist_hotvr_jets_fpt.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_fpt", is_qcd));
  hist_hotvr_jets_fpt_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_fpt_200", is_qcd));
  hist_hotvr_jets_fpt_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_fpt_400", is_qcd));
  hist_hotvr_jets_fpt_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_fpt_600", is_qcd));
  hist_hotvr_jets_fpt_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_fpt_800", is_qcd));
  hist_hotvr_jets_fpt_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_fpt_1000", is_qcd));

  hist_hotvr_jets_mass.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mass", is_qcd));
  hist_hotvr_jets_mass_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mass_200", is_qcd));
  hist_hotvr_jets_mass_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mass_400", is_qcd));
  hist_hotvr_jets_mass_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mass_600", is_qcd));
  hist_hotvr_jets_mass_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mass_800", is_qcd));
  hist_hotvr_jets_mass_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mass_1000", is_qcd));

  hist_matched_jets.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets", is_qcd));
  hist_matched_jets_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_200", is_qcd));
  hist_matched_jets_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_400", is_qcd));
  hist_matched_jets_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_600", is_qcd));
  hist_matched_jets_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_800", is_qcd));
  hist_matched_jets_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_1000", is_qcd));

  // hist_matched_jets_Nsub3.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_Nsub3", is_qcd));
  // hist_matched_jets_Nsub3_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_Nsub3_200", is_qcd));
  // hist_matched_jets_Nsub3_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_Nsub3_400", is_qcd));
  // hist_matched_jets_Nsub3_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_Nsub3_600", is_qcd));
  // hist_matched_jets_Nsub3_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_Nsub3_800", is_qcd));
  // hist_matched_jets_Nsub3_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_Nsub3_1000", is_qcd));
  //
  // hist_matched_jets_fpt.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_fpt", is_qcd));
  // hist_matched_jets_fpt_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_fpt_200", is_qcd));
  // hist_matched_jets_fpt_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_fpt_400", is_qcd));
  // hist_matched_jets_fpt_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_fpt_600", is_qcd));
  // hist_matched_jets_fpt_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_fpt_800", is_qcd));
  // hist_matched_jets_fpt_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_fpt_1000", is_qcd));

  hist_tagged_jets.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets", is_qcd));
  hist_tagged_jets_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_200", is_qcd));
  hist_tagged_jets_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_400", is_qcd));
  hist_tagged_jets_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_600", is_qcd));
  hist_tagged_jets_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_800", is_qcd));
  hist_tagged_jets_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_1000", is_qcd));

  hist_tagged_jets_tau32.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_tau32", is_qcd));
  hist_tagged_jets_tau32_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_tau32_200", is_qcd));
  hist_tagged_jets_tau32_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_tau32_400", is_qcd));
  hist_tagged_jets_tau32_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_tau32_600", is_qcd));
  hist_tagged_jets_tau32_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_tau32_800", is_qcd));
  hist_tagged_jets_tau32_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_tagged_jets_tau32_1000", is_qcd));


  // hist_rejected_subjets.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_subjets"));
  // hist_rejected_subjets_200.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_subjets_200"));
  // hist_rejected_subjets_400.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_subjets_400"));
  // hist_rejected_subjets_600.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_subjets_600"));
  // hist_rejected_subjets_800.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_subjets_800"));
  // hist_rejected_subjets_1000.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_subjets_1000"));
  //
  // hist_rejected_cluster.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_cluster"));
  // hist_rejected_cluster_200.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_cluster_200"));
  // hist_rejected_cluster_400.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_cluster_400"));
  // hist_rejected_cluster_600.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_cluster_600"));
  // hist_rejected_cluster_800.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_cluster_800"));
  // hist_rejected_cluster_1000.reset(new SoftClusterHists(ctx, "SoftClusterHists_rejected_cluster_1000"));
  //
  // hist_soft_cluster.reset(new SoftClusterHists(ctx, "SoftClusterHists_soft_cluster"));
  // hist_soft_cluster_200.reset(new SoftClusterHists(ctx, "SoftClusterHists_soft_cluster_200"));
  // hist_soft_cluster_400.reset(new SoftClusterHists(ctx, "SoftClusterHists_soft_cluster_400"));
  // hist_soft_cluster_600.reset(new SoftClusterHists(ctx, "SoftClusterHists_soft_cluster_600"));
  // hist_soft_cluster_800.reset(new SoftClusterHists(ctx, "SoftClusterHists_soft_cluster_800"));
  // hist_soft_cluster_1000.reset(new SoftClusterHists(ctx, "SoftClusterHists_soft_cluster_1000"));

   hist_vr_jets.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets", is_qcd));
  // hist_hotvr_jet_constituents.reset(new VRJetsHists(ctx, "VRJetsHists_hotvr_jets", is_qcd));
  // hist_hotvr_jet_constituents_200.reset(new VRJetsHists(ctx, "VRJetsHists_hotvr_jets_200", is_qcd));
  // hist_hotvr_jet_constituents_400.reset(new VRJetsHists(ctx, "VRJetsHists_hotvr_jets_400", is_qcd));
  // hist_hotvr_jet_constituents_600.reset(new VRJetsHists(ctx, "VRJetsHists_hotvr_jets_600", is_qcd));
  // hist_hotvr_jet_constituents_800.reset(new VRJetsHists(ctx, "VRJetsHists_hotvr_jets_800", is_qcd));
  // hist_hotvr_jet_constituents_1000.reset(new VRJetsHists(ctx, "VRJetsHists_hotvr_jets_1000", is_qcd));
  //
  // hist_vr_jets_ISD.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets_ISD", is_qcd));
  // hist_vr_jets_ISD_200.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets_ISD_200", is_qcd));
  // hist_vr_jets_ISD_400.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets_ISD_400", is_qcd));
  // hist_vr_jets_ISD_600.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets_ISD_600", is_qcd));
  // hist_vr_jets_ISD_800.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets_ISD_800", is_qcd));
  // hist_vr_jets_ISD_1000.reset(new VRJetsHists(ctx, "VRJetsHists_vr_jets_ISD_1000", is_qcd));

//for ROC curves
  double top_pt_min = 0.0;
  double top_eta_max = 100000;
  TopJetId id_topjet =  PtEtaCut(top_pt_min, top_eta_max);
  TopJetId id_hotvr = AndId<TopJet>(id_topjet, Tau32Groomed(0.56));  // definition of hotvr id

  for (int i = 0; i < n_points; ++i) //loop over working points and create hists
  {
    std::unique_ptr<Selection> sel;
    std::unique_ptr<Hists> hist;
    TopJetId id;
    double tau32 = 1 - (i * 1./n_points);
    // - HOTVR - //
    id = AndId<TopJet>(id_topjet, Tau32Groomed(tau32)); // define id on specific tau
    sel.reset(new NTopJetSelection(1, -1, id, h_matched_jets)); // selection on specific tau
    sel_hotvr.push_back(std::move(sel)); // fill vector with selection bool

    hist.reset(new TopTagPerformanceHists(ctx, "HOTVR_Performance_" + to_string(i), is_qcd,  id, h_matched_pairs)); // reserve hist for sp. tau
    hist_hotvr.push_back(std::move(hist)); // fill vector with hists
  }

  hist_hotvr_pre.reset(new TopTagPerformanceHists(ctx, "HOTVR_Pre", is_qcd, id_topjet, h_matched_pairs)); // reserve preselection hist
}
/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/
bool HOTVRStudiesModule::process(Event & event) {
// here define genparticles and read from event
  auto genparticles = event.genparticles;

//MATCHING -> class to filter the stable particles from the genparticles and create a pseudojet from them
  matching = new Matching();
  matching->set_stable_particles(genparticles);
  pseudojets = matching->get_stableParticles();
  matching->set_partons(genparticles);
  parton_pseudojets = matching->get_partons();

//CLUSTERING -> clusters jets depending on the algorithm that is chosen
  clustering = new Clustering(m_clustering);
  clustering->cluster_jets(pseudojets); // cluster the pseudojets, possible modes defined in hotvr.config: "HOTVR, HOTVR_SD, VR"
  hotvr_jets = clustering->get_hotvr_jets();
  hotvr_jets_constituents = clustering->get_hotvr_jet_constituents();
  // get the rejected subjets
  _rejected_subjets = clustering->get_rejected_subjets();
  _rejected_cluster = clustering->get_rejected_cluster();
  _soft_cluster = clustering->get_soft_cluster();
  // fill hists with the number of rejected subjets and clusters
  // hist_rejected_subjets->fill_n_rejected_subjets(event, _rejected_subjets);
  // hist_rejected_cluster->fill_n_cluster(event, _rejected_cluster);
  // hist_soft_cluster->fill_n_cluster(event, _soft_cluster);
  // fill hists for rejected subjets (rejected with ptsub in the HOTVR plugin)
  // for (size_t k = 0; k < _rejected_subjets.size(); k++) {
  //   hist_rejected_subjets->fill_rejected_subjets(event, _rejected_subjets[k]);
  //   if(_rejected_subjets[k].pt()>200 && _rejected_subjets[k].pt()<400)  hist_rejected_subjets_200->fill_rejected_subjets(event, _rejected_subjets[k]);
  //   if(_rejected_subjets[k].pt()>400 && _rejected_subjets[k].pt()<600)  hist_rejected_subjets_400->fill_rejected_subjets(event, _rejected_subjets[k]);
  //   if(_rejected_subjets[k].pt()>600 && _rejected_subjets[k].pt()<800)  hist_rejected_subjets_600->fill_rejected_subjets(event, _rejected_subjets[k]);
  //   if(_rejected_subjets[k].pt()>800 && _rejected_subjets[k].pt()<1000)  hist_rejected_subjets_800->fill_rejected_subjets(event, _rejected_subjets[k]);
  //   if(_rejected_subjets[k].pt()>1000 && _rejected_subjets[k].pt()<1200)  hist_rejected_subjets_1000->fill_rejected_subjets(event, _rejected_subjets[k]);
  // }
  // fill hists for rejected cluster (jets with no subjets)
  // for (size_t k = 0; k < _rejected_cluster.size(); k++) {
  //   hist_rejected_cluster->fill_cluster(event, _rejected_cluster[k]);
  //   if(_rejected_cluster[k].pt()>200 && _rejected_cluster[k].pt()<400)  hist_rejected_cluster_200->fill_cluster(event, _rejected_cluster[k]);
  //   if(_rejected_cluster[k].pt()>400 && _rejected_cluster[k].pt()<600)  hist_rejected_cluster_400->fill_cluster(event, _rejected_cluster[k]);
  //   if(_rejected_cluster[k].pt()>600 && _rejected_cluster[k].pt()<800)  hist_rejected_cluster_600->fill_cluster(event, _rejected_cluster[k]);
  //   if(_rejected_cluster[k].pt()>800 && _rejected_cluster[k].pt()<1000)  hist_rejected_cluster_800->fill_cluster(event, _rejected_cluster[k]);
  //   if(_rejected_cluster[k].pt()>1000 && _rejected_cluster[k].pt()<1200)  hist_rejected_cluster_1000->fill_cluster(event, _rejected_cluster[k]);
  // }
  // // fill hists for soft cluster (jets rejected with the NOVETO case in the HOTVR plugin)
  // for (size_t k = 0; k < _soft_cluster.size(); k++) {
  //   hist_soft_cluster->fill_cluster(event, _soft_cluster[k]);
  //   if(_soft_cluster[k].pt()>200 && _soft_cluster[k].pt()<400)  hist_soft_cluster_200->fill_cluster(event, _soft_cluster[k]);
  //   if(_soft_cluster[k].pt()>400 && _soft_cluster[k].pt()<600)  hist_soft_cluster_400->fill_cluster(event, _soft_cluster[k]);
  //   if(_soft_cluster[k].pt()>600 && _soft_cluster[k].pt()<800)  hist_soft_cluster_600->fill_cluster(event, _soft_cluster[k]);
  //   if(_soft_cluster[k].pt()>800 && _soft_cluster[k].pt()<1000)  hist_soft_cluster_800->fill_cluster(event, _soft_cluster[k]);
  //   if(_soft_cluster[k].pt()>1000 && _soft_cluster[k].pt()<1200)  hist_soft_cluster_1000->fill_cluster(event, _soft_cluster[k]);
  // }

  // get the VR clustered jets
  vr_jets = clustering->get_vr_jets();
  vr_jets_constituents = clustering->get_vr_jet_constituents(); // vector<vector<PseudoJet>>
  vr_jets_SD = clustering->get_vr_jets_SD();
  vr_jets_ISD = clustering->get_vr_jets_ISD();
  // cluster and get the clustered parton jets (AK10 jets)
  clustering->cluster_parton_jets(parton_pseudojets, isTTbar);
  parton_jets = clustering->get_parton_jets();
  //get the topjets from the Clustering
  _top_hotvr_jets=clustering->get_top_hotvr_jets();
  _top_parton_jets=clustering->get_top_parton_jets();

// ---------------------------begin---ML files-------------------------------------------
// part to create files for machine learning studies (produce files
//... that contain the vr jet constituents)
  std::vector<fastjet::PseudoJet> matched_vr_jets;
  matching->run_matching(vr_jets, vr_jets_constituents, parton_jets); // match the clustered jets to parton level jets
  matched_vr_jets = matching->get_matched_pseudojets();
  vector<pair<PseudoJet, vector<PseudoJet>>> matched_vr_jets_and_constituents = matching->get_matched_jets_and_constituents();
  for (size_t j = 0; j < matched_vr_jets_and_constituents.size(); j++) { // loop over jets to fill hists
    auto jet = matched_vr_jets_and_constituents[j].first;
    auto jet_constituents = matched_vr_jets_and_constituents[j].second;
    hist_vr_jets->fill_pseudojet(event, jet);
    hist_vr_jets->fill_pseudojet_constituents(jet_constituents);
  }
  //class that makes the .csv file containing infos about jet constituents
  makefiles = new Makefiles(m_csvfile_ttbar, m_csvfile_qcd, matched_vr_jets_and_constituents, is_qcd);
//... that contain the hotvr jet constituents)
  matching->run_matching(hotvr_jets, hotvr_jets_constituents, parton_jets); // match the clustered jets to parton level jets
  vector<pair<PseudoJet, vector<PseudoJet>>> matched_hotvr_jets_and_constituents = matching->get_matched_jets_and_constituents();
  for (size_t j = 0; j < matched_hotvr_jets_and_constituents.size(); j++) { // loop over jets to fill hists
    auto jet = matched_hotvr_jets_and_constituents[j].first;
    auto jet_constituents = matched_hotvr_jets_and_constituents[j].second;
  //  hist_vr_jets->fill_pseudojet(event, jet);
  //  hist_vr_jets->fill_pseudojet_constituents(jet_constituents);
  }
  //class that makes the .csv file containing infos about jet constituents
  makefiles = new Makefiles(m_csvfile_ttbar, m_csvfile_qcd, matched_hotvr_jets_and_constituents, is_qcd);
// --------------------------end--ML files--------------------------------------------

// fill hists with infos about the jet constituents
  // for (size_t j = 0; j < hotvr_jets.size(); j++) {
  //   hist_hotvr_jet_constituents->fill_pseudojet(event, hotvr_jets[j]);
  //   hist_hotvr_jet_constituents->fill_pseudojet_constituents(hotvr_jets_constituents[j]);
  //   if(hotvr_jets[j].pt()>200 && hotvr_jets[j].pt()<400)  hist_hotvr_jet_constituents_200->fill_pseudojet_constituents(hotvr_jets_constituents[j]);
  //   if(hotvr_jets[j].pt()>400 && hotvr_jets[j].pt()<600)  hist_hotvr_jet_constituents_400->fill_pseudojet_constituents(hotvr_jets_constituents[j]);
  //   if(hotvr_jets[j].pt()>600 && hotvr_jets[j].pt()<800)  hist_hotvr_jet_constituents_600->fill_pseudojet_constituents(hotvr_jets_constituents[j]);
  //   if(hotvr_jets[j].pt()>800 && hotvr_jets[j].pt()<1000)  hist_hotvr_jet_constituents_800->fill_pseudojet_constituents(hotvr_jets_constituents[j]);
  //   if(hotvr_jets[j].pt()>1000 && hotvr_jets[j].pt()<1200)  hist_hotvr_jet_constituents_1000->fill_pseudojet_constituents(hotvr_jets_constituents[j]);
  // }

//fill hists with hotvr jets and corresponding rejected subjets
  hist_hotvr_jets->fill_n_jets(event, _top_hotvr_jets);
  for(uint j=0; j<_top_hotvr_jets.size(); ++j){ // loop over hotvr jets
    hist_hotvr_jets->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>200 && _top_hotvr_jets[j].pt()<400)  hist_hotvr_jets_200->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>400 && _top_hotvr_jets[j].pt()<600)  hist_hotvr_jets_400->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>600 && _top_hotvr_jets[j].pt()<800)  hist_hotvr_jets_600->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>800 && _top_hotvr_jets[j].pt()<1000)  hist_hotvr_jets_800->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>1000 && _top_hotvr_jets[j].pt()<1200)  hist_hotvr_jets_1000->fill_topjet(event, _top_hotvr_jets[j]);
// fill hists after Nsub3 cut
if (_top_hotvr_jets[j].subjets().size()>2) {
    hist_hotvr_jets_Nsub3->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>200 && _top_hotvr_jets[j].pt()<400)  hist_hotvr_jets_Nsub3_200->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>400 && _top_hotvr_jets[j].pt()<600)  hist_hotvr_jets_Nsub3_400->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>600 && _top_hotvr_jets[j].pt()<800)  hist_hotvr_jets_Nsub3_600->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>800 && _top_hotvr_jets[j].pt()<1000)  hist_hotvr_jets_Nsub3_800->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>1000 && _top_hotvr_jets[j].pt()<1200)  hist_hotvr_jets_Nsub3_1000->fill_topjet(event, _top_hotvr_jets[j]);
  }
// fill hists after fpt cut
  if (_top_hotvr_jets[j].subjets().size()>2 && _top_hotvr_jets[j].hotvr_fpt1()<0.8) {
    hist_hotvr_jets_fpt->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>200 && _top_hotvr_jets[j].pt()<400)  hist_hotvr_jets_fpt_200->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>400 && _top_hotvr_jets[j].pt()<600)  hist_hotvr_jets_fpt_400->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>600 && _top_hotvr_jets[j].pt()<800)  hist_hotvr_jets_fpt_600->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>800 && _top_hotvr_jets[j].pt()<1000)  hist_hotvr_jets_fpt_800->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>1000 && _top_hotvr_jets[j].pt()<1200)  hist_hotvr_jets_fpt_1000->fill_topjet(event, _top_hotvr_jets[j]);
  }
// fill hist after mass cut
  if (_top_hotvr_jets[j].subjets().size()>2 && 140<_top_hotvr_jets[j].v4().M() && _top_hotvr_jets[j].v4().M()<220) {
    hist_hotvr_jets_mass->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>200 && _top_hotvr_jets[j].pt()<400)  hist_hotvr_jets_mass_200->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>400 && _top_hotvr_jets[j].pt()<600)  hist_hotvr_jets_mass_400->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>600 && _top_hotvr_jets[j].pt()<800)  hist_hotvr_jets_mass_600->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>800 && _top_hotvr_jets[j].pt()<1000)  hist_hotvr_jets_mass_800->fill_topjet(event, _top_hotvr_jets[j]);
    if(_top_hotvr_jets[j].pt()>1000 && _top_hotvr_jets[j].pt()<1200)  hist_hotvr_jets_mass_1000->fill_topjet(event, _top_hotvr_jets[j]);
  }
} // end loop over hotvr jets

// Hists for VR ISD jets
    // for(uint j=0; j<vr_jets_ISD.size(); ++j){
    //   PseudoJet jet = vr_jets_ISD[j];
    //   hist_vr_jets_ISD->fill_pseudojet(event, jet);
    //   if(jet.pt()>200 && jet.pt()<400)  hist_vr_jets_ISD_200->fill_pseudojet(event, jet);
    //   if(jet.pt()>400 && jet.pt()<600)  hist_vr_jets_ISD_400->fill_pseudojet(event, jet);
    //   if(jet.pt()>600 && jet.pt()<800)  hist_vr_jets_ISD_600->fill_pseudojet(event, jet);
    //   if(jet.pt()>800 && jet.pt()<1000)  hist_vr_jets_ISD_800->fill_pseudojet(event, jet);
    //   if(jet.pt()>1000 && jet.pt()<1200)  hist_vr_jets_ISD_1000->fill_pseudojet(event, jet);
    // }
// ------MATCHING--------
//run_matching: loop over the parton jets and match them to the hotvr jets
  vector<TopJet> matched_jets;
  vector<TopJet> matched_parton_jets;
  matching->run_matching(_top_hotvr_jets, _top_parton_jets);
  matched_jets = matching->get_matched_jets();
  matched_parton_jets = matching->get_matched_parton_jets();
  vector<pair<TopJet, TopJet>> matched_pair = matching->get_matched_pairs();

//TopTagger for matched hotvr jets
  toptagger = new TopTagger();
  vector<TopJet> matched_jets_tagged;
  vector<pair<TopJet, TopJet>> matched_pair_tagged;
  for(uint j=0; j<matched_pair.size(); ++j){ // loop over matched jets
    TopJet parton_jet=matched_pair[j].second;
    TopJet matched_jet=matched_pair[j].first;

    //fill hists with matched jets
    hist_matched_jets->fill_topjet(event, matched_jet);
    if(parton_jet.pt()>200 && parton_jet.pt()<400)  hist_matched_jets_200->fill_topjet(event, matched_jet);
    if(parton_jet.pt()>400 && parton_jet.pt()<600)  hist_matched_jets_400->fill_topjet(event, matched_jet);
    if(parton_jet.pt()>600 && parton_jet.pt()<800)  hist_matched_jets_600->fill_topjet(event, matched_jet);
    if(parton_jet.pt()>800 && parton_jet.pt()<1000)  hist_matched_jets_800->fill_topjet(event, matched_jet);
    if(parton_jet.pt()>1000 && parton_jet.pt()<1200)  hist_matched_jets_1000->fill_topjet(event, matched_jet);

    // if(matched_jet.subjets().size()>2){
    // hist_matched_jets_Nsub3->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>200 && parton_jet.pt()<400)  hist_matched_jets_Nsub3_200->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>400 && parton_jet.pt()<600)  hist_matched_jets_Nsub3_400->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>600 && parton_jet.pt()<800)  hist_matched_jets_Nsub3_600->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>800 && parton_jet.pt()<1000)  hist_matched_jets_Nsub3_800->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>1000 && parton_jet.pt()<1200)  hist_matched_jets_Nsub3_1000->fill_topjet(event, matched_jet);
    // }
    //
    // if(matched_jet.hotvr_fpt1()<0.8){
    // hist_matched_jets_fpt->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>200 && parton_jet.pt()<400)  hist_matched_jets_fpt_200->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>400 && parton_jet.pt()<600)  hist_matched_jets_fpt_400->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>600 && parton_jet.pt()<800)  hist_matched_jets_fpt_600->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>800 && parton_jet.pt()<1000)  hist_matched_jets_fpt_800->fill_topjet(event, matched_jet);
    // if(parton_jet.pt()>1000 && parton_jet.pt()<1200)  hist_matched_jets_fpt_1000->fill_topjet(event, matched_jet);
    // }
// --------apply Top Tag-----------------
    if(toptagger->Is_tagged("sd", matched_jets[j])){
      matched_jets_tagged.push_back(matched_jet);
      matched_pair_tagged.push_back(matched_pair[j]);
      // fill hists with tagged jets
      double tau32 = matched_jet.tau3_groomed()/matched_jet.tau2_groomed();
      hist_tagged_jets->fill_topjet(event, matched_jet);
      if(tau32<0.4){hist_tagged_jets_tau32->fill_topjet(event, matched_jet);}

      if(parton_jet.pt()>200 && parton_jet.pt()<400){
        hist_tagged_jets_200->fill_topjet(event, matched_jet);
        if(tau32<0.4){hist_tagged_jets_tau32_200->fill_topjet(event, matched_jet);}
        }

      if(parton_jet.pt()>400 && parton_jet.pt()<600){
        hist_tagged_jets_400->fill_topjet(event, matched_jet);
        if(tau32<0.4){hist_tagged_jets_tau32_400->fill_topjet(event, matched_jet);}
      }

      if(parton_jet.pt()>600 && parton_jet.pt()<800){
        hist_tagged_jets_600->fill_topjet(event, matched_jet);
        if(tau32<0.4){hist_tagged_jets_tau32_600->fill_topjet(event, matched_jet);}
      }

      if(parton_jet.pt()>800 && parton_jet.pt()<1000){
        hist_tagged_jets_800->fill_topjet(event, matched_jet);
        if(tau32<0.4){hist_tagged_jets_tau32_800->fill_topjet(event, matched_jet);}
      }

      if(parton_jet.pt()>1000 && parton_jet.pt()<1200){
        hist_tagged_jets_1000->fill_topjet(event, matched_jet);
        if(tau32<0.4){hist_tagged_jets_tau32_800->fill_topjet(event, matched_jet);}
      }

  } // end if top tag
  } // end loop over matched jets

//set the event handle
  //these jets are the matched TopJets
  event.set(h_matched_parton_jets, matched_parton_jets);
  event.set(h_matched_jets, matched_jets);

//for ROC curves
  //set the event handle for the denominator
  event.set(h_matched_pairs, matched_pair);
  hist_hotvr_pre->fill(event);   // fill hists before tau selection (all parton jets)
  //set the event handle for the numerator
  event.set(h_matched_pairs, matched_pair_tagged);
  for (int i = 0; i < n_points; ++i){ //loop over working points
    if (sel_hotvr.at(i)->passes(event)){
      hist_hotvr.at(i)->fill(event); //fill hist if at least one jet of the event passes the sel
    }
  }

// decide whether or not to keep the current event in the output:
  return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the HOTVRStudiesModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(HOTVRStudiesModule)
