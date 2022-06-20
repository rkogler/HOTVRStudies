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
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/common/include/PrintingModules.h"

// include everything from the HOTVR Studies
#include "UHH2/HOTVRStudies/include/Matching.h"
#include "UHH2/HOTVRStudies/include/Clustering.h"
#include "UHH2/HOTVRStudies/include/TopTagger.h"
#include "UHH2/HOTVRStudies/include/TopTagPerformanceHists.h"
#include "UHH2/HOTVRStudies/include/HOTVRJetsHists.h"
#include "UHH2/HOTVRStudies/include/VRJetsHists.h"
#include "UHH2/HOTVRStudies/include/SoftClusterHists.h"
#include "UHH2/HOTVRStudies/include/Makefiles.h"
#include "UHH2/HOTVRStudies/include/EfficiencyHists.h"
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

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mGr130;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mGr130_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mGr130_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mGr130_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mGr130_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mGr130_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mSm130;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mSm130_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mSm130_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mSm130_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mSm130_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_mSm130_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub3_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq2;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq2_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq2_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq2_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq2_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq2_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq3;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq3_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq3_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq3_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq3_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsubeq3_1000;

  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub4;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub4_200;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub4_400;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub4_600;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub4_800;
  std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_Nsub4_1000;

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

  std::unique_ptr<HOTVRJetsHists> hist_njets_matched;

// initialize event handle
  Event::Handle<vector<TopJet>> h_HOTVR_jets;
  Event::Handle<vector<TopJet>> h_parton_jets;

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
  //----EfficiencyHists----
  std::unique_ptr<EfficiencyHists> hist_eff_hotvr;

// initialize classes
  string m_clustering;
  Matching* matching;
  Clustering* clustering;
  TopTagger* toptagger;

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

  vector<Jet> _rejected_subjets; // rejected subjets with ptsub
  vector<TopJet> _rejected_cluster; // rejected cluster (jets without subjets)
  vector<TopJet> _soft_cluster; // soft cluster rejected via softdrop / massjump condition

  string dataset_version;

  bool isTTbar;
  bool is_mc, is_qcd;

  int nevent=0;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

  Event::Handle<TTbarGen> h_ttbargen;
  bool debug = false;
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
  if(debug){cout << "HOTVRStudiesModule: Debugging mode :) " << '\n';}
// get info from xml
  m_clustering = ctx.get("Clustering");
// check for the dataset version (ttbar or QCD)
  dataset_version = ctx.get("dataset_version");
  isTTbar = dataset_version.find("ttbar") == 0;
  is_mc = ctx.get("dataset_type") == "MC";
  is_qcd = (dataset_version.find("QCD") == 0);

  h_HOTVR_jets = ctx.get_handle<vector<TopJet>>("HOTVR_jets");
  h_parton_jets = ctx.get_handle<vector<TopJet>>("parton_jets");

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

  hist_hotvr_jets_mGr130.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mGr130", is_qcd));
  hist_hotvr_jets_mGr130_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mGr130_200", is_qcd));
  hist_hotvr_jets_mGr130_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mGr130_400", is_qcd));
  hist_hotvr_jets_mGr130_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mGr130_600", is_qcd));
  hist_hotvr_jets_mGr130_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mGr130_800", is_qcd));
  hist_hotvr_jets_mGr130_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mGr130_1000", is_qcd));

  hist_hotvr_jets_mSm130.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mSm130", is_qcd));
  hist_hotvr_jets_mSm130_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mSm130_200", is_qcd));
  hist_hotvr_jets_mSm130_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mSm130_400", is_qcd));
  hist_hotvr_jets_mSm130_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mSm130_600", is_qcd));
  hist_hotvr_jets_mSm130_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mSm130_800", is_qcd));
  hist_hotvr_jets_mSm130_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_mSm130_1000", is_qcd));

  hist_hotvr_jets_Nsub3.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3", is_qcd));
  hist_hotvr_jets_Nsub3_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_200", is_qcd));
  hist_hotvr_jets_Nsub3_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_400", is_qcd));
  hist_hotvr_jets_Nsub3_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_600", is_qcd));
  hist_hotvr_jets_Nsub3_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_800", is_qcd));
  hist_hotvr_jets_Nsub3_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub3_1000", is_qcd));

  hist_hotvr_jets_Nsubeq2.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq2", is_qcd));
  hist_hotvr_jets_Nsubeq2_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq2_200", is_qcd));
  hist_hotvr_jets_Nsubeq2_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq2_400", is_qcd));
  hist_hotvr_jets_Nsubeq2_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq2_600", is_qcd));
  hist_hotvr_jets_Nsubeq2_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq2_800", is_qcd));
  hist_hotvr_jets_Nsubeq2_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq2_1000", is_qcd));

  hist_hotvr_jets_Nsubeq3.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq3", is_qcd));
  hist_hotvr_jets_Nsubeq3_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq3_200", is_qcd));
  hist_hotvr_jets_Nsubeq3_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq3_400", is_qcd));
  hist_hotvr_jets_Nsubeq3_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq3_600", is_qcd));
  hist_hotvr_jets_Nsubeq3_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq3_800", is_qcd));
  hist_hotvr_jets_Nsubeq3_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsubeq3_1000", is_qcd));

  hist_hotvr_jets_Nsub4.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub4", is_qcd));
  hist_hotvr_jets_Nsub4_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub4_200", is_qcd));
  hist_hotvr_jets_Nsub4_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub4_400", is_qcd));
  hist_hotvr_jets_Nsub4_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub4_600", is_qcd));
  hist_hotvr_jets_Nsub4_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub4_800", is_qcd));
  hist_hotvr_jets_Nsub4_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_Nsub4_1000", is_qcd));

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

  hist_njets_matched.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_njets_matched", is_qcd));

//for ROC curves
  double top_pt_min = 0.0;
  double top_eta_max = 100000;
  TopJetId id_topjet =  PtEtaCut(top_pt_min, top_eta_max);
  TopJetId id_hotvr = AndId<TopJet>(id_topjet, Tau32Groomed(0.47));  // definition of hotvr id (HOTVR SD WP 0.47)

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

  //efficiency hists -> give hotvr id
  hist_eff_hotvr.reset(new EfficiencyHists(ctx, "HOTVR_Eff", is_qcd, id_hotvr, h_matched_pairs));

}
/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/
bool HOTVRStudiesModule::process(Event & event) {
  if(debug){std::cout << "Begin process..." << '\n';}

  //get the topjets from the Clustering Module
  vector<TopJet> _top_hotvr_jets = event.get(h_HOTVR_jets);
  vector<TopJet> _top_parton_jets = event.get(h_parton_jets);

//fill hists with hotvr jets and corresponding rejected subjets
  hist_hotvr_jets->fill_n_jets(event, _top_hotvr_jets);
  for(uint j=0; j<_top_hotvr_jets.size(); ++j){ // loop over hotvr jets
    //std::cout << "Jet pt "<<jet.pt() << '\n';
    TopJet jet = _top_hotvr_jets[j];
    hist_hotvr_jets->fill_topjet(event, jet);
    if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_200->fill_topjet(event, jet);
    if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_400->fill_topjet(event, jet);
    if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_600->fill_topjet(event, jet);
    if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_800->fill_topjet(event, jet);
    if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_1000->fill_topjet(event, jet);
    // fill hists for m > 130 GeV and m < 130 GeV
    if (jet.v4().M()>130) {
      hist_hotvr_jets_mGr130->fill_topjet(event, jet);
      if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_mGr130_200->fill_topjet(event, jet);
      if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_mGr130_400->fill_topjet(event, jet);
      if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_mGr130_600->fill_topjet(event, jet);
      if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_mGr130_800->fill_topjet(event, jet);
      if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_mGr130_1000->fill_topjet(event, jet);
    }
    if (jet.v4().M()<130) {
      hist_hotvr_jets_mSm130->fill_topjet(event, jet);
      if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_mSm130_200->fill_topjet(event, jet);
      if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_mSm130_400->fill_topjet(event, jet);
      if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_mSm130_600->fill_topjet(event, jet);
      if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_mSm130_800->fill_topjet(event, jet);
      if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_mSm130_1000->fill_topjet(event, jet);
    }

// fill hists after Nsub3 cut
if (jet.subjets().size()>2) {
    hist_hotvr_jets_Nsub3->fill_topjet(event, jet);
    if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_Nsub3_200->fill_topjet(event, jet);
    if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_Nsub3_400->fill_topjet(event, jet);
    if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_Nsub3_600->fill_topjet(event, jet);
    if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_Nsub3_800->fill_topjet(event, jet);
    if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_Nsub3_1000->fill_topjet(event, jet);
  }
  // fill hists for jets with == 2 subjets
  if (jet.subjets().size()==2) {
      hist_hotvr_jets_Nsubeq2->fill_topjet(event, jet);
      if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_Nsubeq2_200->fill_topjet(event, jet);
      if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_Nsubeq2_400->fill_topjet(event, jet);
      if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_Nsubeq2_600->fill_topjet(event, jet);
      if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_Nsubeq2_800->fill_topjet(event, jet);
      if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_Nsubeq2_1000->fill_topjet(event, jet);
    }
    // fill hists after Nsub3 cut
    if (jet.subjets().size()==3) {
        hist_hotvr_jets_Nsubeq3->fill_topjet(event, jet);
        if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_Nsubeq3_200->fill_topjet(event, jet);
        if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_Nsubeq3_400->fill_topjet(event, jet);
        if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_Nsubeq3_600->fill_topjet(event, jet);
        if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_Nsubeq3_800->fill_topjet(event, jet);
        if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_Nsubeq3_1000->fill_topjet(event, jet);
      }
      // fill hists after Nsub3 cut
      if (jet.subjets().size()>3) {
          hist_hotvr_jets_Nsub4->fill_topjet(event, jet);
          if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_Nsub4_200->fill_topjet(event, jet);
          if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_Nsub4_400->fill_topjet(event, jet);
          if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_Nsub4_600->fill_topjet(event, jet);
          if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_Nsub4_800->fill_topjet(event, jet);
          if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_Nsub4_1000->fill_topjet(event, jet);
        }
// fill hists after fpt cut
  if (jet.subjets().size()>2 &&jet.hotvr_fpt1()<0.8) {
    hist_hotvr_jets_fpt->fill_topjet(event, jet);
    if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_fpt_200->fill_topjet(event, jet);
    if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_fpt_400->fill_topjet(event, jet);
    if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_fpt_600->fill_topjet(event, jet);
    if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_fpt_800->fill_topjet(event, jet);
    if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_fpt_1000->fill_topjet(event, jet);
  }
// fill hist after mass cut
  if (jet.subjets().size()>2 && 140<jet.v4().M() &&jet.v4().M()<220) {
    hist_hotvr_jets_mass->fill_topjet(event, jet);
    if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_mass_200->fill_topjet(event, jet);
    if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_mass_400->fill_topjet(event, jet);
    if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_mass_600->fill_topjet(event, jet);
    if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_mass_800->fill_topjet(event, jet);
    if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_mass_1000->fill_topjet(event, jet);
  }
} // end loop over hotvr jets

// ------MATCHING--------
matching = new Matching();
//run_matching: loop over the parton jets and match them to the hotvr jets
  vector<TopJet> matched_jets;
  vector<TopJet> matched_parton_jets;
  matching->run_matching(_top_hotvr_jets, _top_parton_jets);
  matched_jets = matching->get_matched_jets();
  matched_parton_jets = matching->get_matched_parton_jets();
  vector<pair<TopJet, TopJet>> matched_pair = matching->get_matched_pairs();

  hist_njets_matched->fill_n_jets(event, matched_jets);
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

 //set the event handle  these jets are the matched TopJets
  event.set(h_matched_parton_jets, matched_parton_jets);
  event.set(h_matched_jets, matched_jets);

//for ROC curves
  //set the event handle for the denominator
  event.set(h_matched_pairs, matched_pair);
  hist_hotvr_pre->fill(event);   // fill hists before tau selection (all parton jets)
  hist_eff_hotvr->fill(event);   // fill hists for efficiency plots
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
