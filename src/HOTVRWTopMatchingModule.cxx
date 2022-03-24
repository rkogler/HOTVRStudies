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

class HOTVRWTopMatchingModule: public AnalysisModule {
public:

  explicit HOTVRWTopMatchingModule(Context & ctx);
  virtual bool process(Event & event) override;

private:
//initialize hist classes

  std::unique_ptr<HOTVRJetsHists> hist_matched_jets;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_200;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_400;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_600;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_800;
  std::unique_ptr<HOTVRJetsHists> hist_matched_jets_1000;

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

HOTVRWTopMatchingModule::HOTVRWTopMatchingModule(Context & ctx){
  cout << "Starting HOTVRWTopMatchingModule!" << endl;
  if(debug){cout << "HOTVRWTopMatchingModule: Debugging mode :) " << '\n';}
// get info from xml
  m_clustering = ctx.get("Clustering");
// check for the dataset version (ttbar or QCD)
  dataset_version = ctx.get("dataset_version");
  isTTbar = dataset_version.find("ttbar") == 0;
  is_mc = ctx.get("dataset_type") == "MC";
  is_qcd = (dataset_version.find("QCD") == 0);

// TODO get the jets fom previous module??
  h_HOTVR_jets = ctx.get_handle<vector<TopJet>>("HOTVR_jets");
  h_parton_jets = ctx.get_handle<vector<TopJet>>("parton_jets");

//declare event handle
  h_matched_jets = ctx.get_handle<vector<TopJet>>("matched_jets");
  h_matched_parton_jets = ctx.get_handle<vector<TopJet>>("matched_parton_jets");
  h_matched_pairs = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs");

// Set up Hists classes:

  hist_matched_jets.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets", is_qcd));
  hist_matched_jets_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_200", is_qcd));
  hist_matched_jets_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_400", is_qcd));
  hist_matched_jets_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_600", is_qcd));
  hist_matched_jets_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_800", is_qcd));
  hist_matched_jets_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_matched_jets_1000", is_qcd));

}
/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/
bool HOTVRWTopMatchingModule::process(Event & event) {
  if(debug){std::cout << "Begin process..." << '\n';}

  auto genparticles = event.genparticles;

  if(isTTbar){
    if (debug) {std::cout << "Event is ttbar!" << '\n';}
    ttgenprod->process(event);
    const auto & ttbargen = event.get(h_ttbargen);
    if (!ttbargen.IsTopHadronicDecay() || !ttbargen.IsAntiTopHadronicDecay()) { // skip leptonic decays
      return false;
    }
  }
  // ------MATCHING get pseudojet collections for the clustering--------
   matching = new Matching();
   matching->set_stable_particles(genparticles);
   pseudojets = matching->get_stableParticles();

   matching->set_partons(genparticles);
   matching->set_W_partons(genparticles);

   parton_pseudojets = matching->get_partons();
   W_parton_pseudojets = matching->get_W_partons();

   // -----CLUSTERING -----
   clustering = new Clustering(m_clustering);
  clustering->cluster_jets(pseudojets); // cluster the pseudojets, possible modes defined in hotvr.config: "HOTVR, HOTVR_SD, VR"
  hotvr_jets = clustering->get_hotvr_jets();

  clustering->cluster_parton_jets(parton_pseudojets, isTTbar);
  parton_jets = clustering->get_parton_jets();

  clustering->cluster_parton_jets(W_parton_pseudojets, isTTbar);
  W_parton_jets = clustering->get_parton_jets(); // TODO does this work??

// cluster W GENJETS
// ------MATCHING--------
//run_matching: loop over the parton jets and match them to the hotvr jets
  vector<TopJet> matched_jets;
  vector<TopJet> matched_parton_jets;
  matching->run_matching(_top_hotvr_jets, _top_parton_jets);
  //run matching reco to W or top genjet
  //matching->run_matching_W_top(_top_hotvr_jets, _top_parton_jets, _top_parton_jets_W, genjets)
  matched_jets = matching->get_matched_jets();
  matched_parton_jets = matching->get_matched_parton_jets();
  vector<pair<TopJet, TopJet>> matched_pair = matching->get_matched_pairs();

  // TODO fill efficiency hists 


// decide whether or not to keep the current event in the output:
  return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the HOTVRWTopMatchingModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(HOTVRWTopMatchingModule)
