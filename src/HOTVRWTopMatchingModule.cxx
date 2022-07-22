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
#include "UHH2/HOTVRStudies/include/HOTVRWtopHists.h"
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
std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets;
std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_200;
std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_400;
std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_600;
std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_800;
std::unique_ptr<HOTVRJetsHists> hist_hotvr_jets_1000;

std::unique_ptr<HOTVRWtopHists> hist_W_parton_jets;
std::unique_ptr<HOTVRWtopHists> hist_W_parton_jets_200;
std::unique_ptr<HOTVRWtopHists> hist_W_parton_jets_400;
std::unique_ptr<HOTVRWtopHists> hist_W_parton_jets_600;
std::unique_ptr<HOTVRWtopHists> hist_W_parton_jets_800;
std::unique_ptr<HOTVRWtopHists> hist_W_parton_jets_1000;

std::unique_ptr<HOTVRJetsHists> hist_top_parton_jets;
std::unique_ptr<HOTVRJetsHists> hist_top_parton_jets_200;
std::unique_ptr<HOTVRJetsHists> hist_top_parton_jets_400;
std::unique_ptr<HOTVRJetsHists> hist_top_parton_jets_600;
std::unique_ptr<HOTVRJetsHists> hist_top_parton_jets_800;
std::unique_ptr<HOTVRJetsHists> hist_top_parton_jets_1000;

  std::unique_ptr<HOTVRWtopHists> hist_matched_jets;
  std::unique_ptr<HOTVRWtopHists> hist_matched_jets_200;
  std::unique_ptr<HOTVRWtopHists> hist_matched_jets_400;
  std::unique_ptr<HOTVRWtopHists> hist_matched_jets_600;
  std::unique_ptr<HOTVRWtopHists> hist_matched_jets_800;
  std::unique_ptr<HOTVRWtopHists> hist_matched_jets_1000;

// initialize event handle
  Event::Handle<vector<TopJet>> h_HOTVR_jets;
  Event::Handle<vector<TopJet>> h_parton_jets;
  Event::Handle<vector<TopJet>> h_W_parton_jets;

  Event::Handle<vector<TopJet>> h_matched_jets;
  Event::Handle<vector<TopJet>> h_matched_parton_jets;
  Event::Handle<vector<pair<TopJet, TopJet>>> h_matched_pairs; //contains pair of matched jets
    // denominator for the ROC curves first: ttbar, second:qcd

// initialize classes
  string m_clustering;
  Matching* matching;
  Clustering* clustering;
  TopTagger* toptagger;

// initialize vectors of jets
// ... containing pseudojets
  vector<fastjet::PseudoJet> pseudojets;
  vector<fastjet::PseudoJet> hotvr_jets;
  vector<fastjet::PseudoJet> parton_pseudojets;
  vector<fastjet::PseudoJet> W_parton_pseudojets;
  vector<fastjet::PseudoJet> parton_jets;
  vector<fastjet::PseudoJet> W_parton_jets;

  vector<TopJet> _top_hotvr_jets;
  vector<TopJet> _top_parton_jets;
  vector<TopJet> _top_parton_jets_W;

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
  if(debug){std::cout << "Got info from config file" << '\n';}

  h_HOTVR_jets = ctx.get_handle<vector<TopJet>>("HOTVR_jets");
  h_parton_jets = ctx.get_handle<vector<TopJet>>("parton_jets");
  h_W_parton_jets = ctx.get_handle<vector<TopJet>>("W_parton_jets");

//declare event handle
  h_matched_jets = ctx.get_handle<vector<TopJet>>("matched_jets");
  h_matched_parton_jets = ctx.get_handle<vector<TopJet>>("matched_parton_jets");
  h_matched_pairs = ctx.get_handle<vector<pair<TopJet, TopJet>>>("matched_pairs");

  if(debug){std::cout << "Set handle" << '\n';}

  if (isTTbar) {
    if(debug){std::cout << "HOTVRClusteringModule: Event is ttbar!" << '\n';}
    const std::string ttbar_gen_label("ttbargen");
    ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, true));
    h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");
  }
// Set up Hists classes:
hist_hotvr_jets.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets", is_qcd));
hist_hotvr_jets_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_200", is_qcd));
hist_hotvr_jets_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_400", is_qcd));
hist_hotvr_jets_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_600", is_qcd));
hist_hotvr_jets_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_800", is_qcd));
hist_hotvr_jets_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_hotvr_jets_1000", is_qcd));

hist_W_parton_jets.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_W_parton_jets", is_qcd));
hist_W_parton_jets_200.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_W_parton_jets_200", is_qcd));
hist_W_parton_jets_400.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_W_parton_jets_400", is_qcd));
hist_W_parton_jets_600.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_W_parton_jets_600", is_qcd));
hist_W_parton_jets_800.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_W_parton_jets_800", is_qcd));
hist_W_parton_jets_1000.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_W_parton_jets_1000", is_qcd));

hist_top_parton_jets.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_top_parton_jets", is_qcd));
hist_top_parton_jets_200.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_top_parton_jets_200", is_qcd));
hist_top_parton_jets_400.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_top_parton_jets_400", is_qcd));
hist_top_parton_jets_600.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_top_parton_jets_600", is_qcd));
hist_top_parton_jets_800.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_top_parton_jets_800", is_qcd));
hist_top_parton_jets_1000.reset(new HOTVRJetsHists(ctx, "HOTVRJetsHists_top_parton_jets_1000", is_qcd));

  hist_matched_jets.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_matched_jets", is_qcd));
  hist_matched_jets_200.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_matched_jets_200", is_qcd));
  hist_matched_jets_400.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_matched_jets_400", is_qcd));
  hist_matched_jets_600.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_matched_jets_600", is_qcd));
  hist_matched_jets_800.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_matched_jets_800", is_qcd));
  hist_matched_jets_1000.reset(new HOTVRWtopHists(ctx, "HOTVRWtopHists_matched_jets_1000", is_qcd));
  if(debug){std::cout << "End Module Constructor" << '\n';}
}
/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/
bool HOTVRWTopMatchingModule::process(Event & event) {
  if(debug){std::cout << "Begin process...!!" << '\n';}

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
    if (debug) {std::cout << "New Matching class" << '\n';}

    matching->set_stable_particles(genparticles); // Input for HOTVR jet clustering
    pseudojets = matching->get_stableParticles();
    if (debug) {std::cout << "Get stable particles" << '\n';}

    matching->set_partons(genparticles); // Input for top parton jet clustering
    matching->set_W_partons(genparticles); // INput for W parton jets

    parton_pseudojets = matching->get_partons();
    W_parton_pseudojets = matching->get_W_partons();
    if (debug) {std::cout << "Set and get partons" << '\n';}
  //   if (debug)
  //   {std::cout << "parton_pseudojets size " << parton_pseudojets.size() << '\n';
  // std::cout << "W_parton_pseudojets size " << W_parton_pseudojets.size() << '\n';
  // for (size_t i = 0; i < 5 ; i++) {
  //  std::cout << "parton_pseudojets jets pt " << parton_pseudojets[i].pt() << '\n';
  // }
  // for (size_t i = 0; i < 5 ; i++) {
  //  std::cout << "W_parton_pseudojets pt " << W_parton_pseudojets[i].pt() << '\n';
  // }
  // }
    // -----CLUSTERING -----
    clustering = new Clustering(m_clustering);
   clustering->cluster_jets(pseudojets); // cluster the pseudojets, possible modes defined in hotvr.config: "HOTVR, HOTVR_SD, VR"
   hotvr_jets = clustering->get_hotvr_jets();
   _top_hotvr_jets=clustering->get_top_hotvr_jets();
   if (debug) {std::cout << "Cluster HOTVR jets " << '\n';}

   for (size_t i = 0; i < _top_hotvr_jets.size(); i++) {
     TopJet jet = _top_hotvr_jets[i];
     hist_hotvr_jets->fill_topjet(event, jet);
     if(jet.pt()>200 &&jet.pt()<400)  hist_hotvr_jets_200->fill_topjet(event, jet);
     if(jet.pt()>400 &&jet.pt()<600)  hist_hotvr_jets_400->fill_topjet(event, jet);
     if(jet.pt()>600 &&jet.pt()<800)  hist_hotvr_jets_600->fill_topjet(event, jet);
     if(jet.pt()>800 &&jet.pt()<1000)  hist_hotvr_jets_800->fill_topjet(event, jet);
     if(jet.pt()>1000 &&jet.pt()<1200)  hist_hotvr_jets_1000->fill_topjet(event, jet);
   }
   // // cluster W GENJETS
   clustering->cluster_W_parton_jets(W_parton_pseudojets);
   W_parton_jets = clustering->get_W_parton_jets();
   _top_parton_jets_W = clustering->get_top_W_parton_jets();
   if (debug) {std::cout << "Cluster W jets " << '\n';}

   clustering->cluster_parton_jets(parton_pseudojets, isTTbar);
   parton_jets = clustering->get_parton_jets();
   _top_parton_jets = clustering->get_top_parton_jets();
   if (debug) {std::cout << "Cluster top jets " << '\n';}

   // match top genjets to W and plot distance
   matching->run_matching(_top_parton_jets_W, _top_parton_jets);
   vector<pair<TopJet, TopJet>> matched_W_top_pair = matching->get_matched_pairs();
  if (debug) {std::cout << "Match W top jets " << matched_W_top_pair.size() << '\n';}

  for(uint i=0; i<matched_W_top_pair.size(); ++i){ // loop over matched W jets
    TopJet top_parton_jet=matched_W_top_pair[i].second;
    TopJet jet=matched_W_top_pair[i].first;
   //for (size_t i = 0; i < _top_parton_jets_W.size(); i++) {
     hist_W_parton_jets->fill_topjet(event, jet, top_parton_jet);   // kleinsten Abstand W und top genjet plotten
     if(jet.pt()>200 &&jet.pt()<400)  hist_W_parton_jets_200->fill_topjet(event, jet, top_parton_jet);
     if(jet.pt()>400 &&jet.pt()<600)  hist_W_parton_jets_400->fill_topjet(event, jet, top_parton_jet);
     if(jet.pt()>600 &&jet.pt()<800)  hist_W_parton_jets_600->fill_topjet(event, jet, top_parton_jet);
     if(jet.pt()>800 &&jet.pt()<1000)  hist_W_parton_jets_800->fill_topjet(event, jet, top_parton_jet);
     if(jet.pt()>1000 &&jet.pt()<1200)  hist_W_parton_jets_1000->fill_topjet(event, jet, top_parton_jet);
   }
   for (size_t i = 0; i < _top_parton_jets.size(); i++) {
     TopJet jet = _top_parton_jets[i];
     hist_top_parton_jets->fill_topjet(event, jet);
     if(jet.pt()>200 &&jet.pt()<400)  hist_top_parton_jets_200->fill_topjet(event, jet);
     if(jet.pt()>400 &&jet.pt()<600)  hist_top_parton_jets_400->fill_topjet(event, jet);
     if(jet.pt()>600 &&jet.pt()<800)  hist_top_parton_jets_600->fill_topjet(event, jet);
     if(jet.pt()>800 &&jet.pt()<1000)  hist_top_parton_jets_800->fill_topjet(event, jet);
     if(jet.pt()>1000 &&jet.pt()<1200)  hist_top_parton_jets_1000->fill_topjet(event, jet);
   }

//// // ------MATCHING zum top--------

// matching->run_matching_W_top(_top_hotvr_jets, _top_parton_jets, _top_parton_jets_W); // TODO does this work? TODO wenn W dicht, dann zum W matchen, sonst top
//  matched_jets = matching->get_matched_jets();
//  matched_parton_jets = matching->get_matched_parton_jets();
//  vector<pair<TopJet, TopJet>> matched_pair_HOTVR_top = matching->get_matched_pairs();
// if (debug) {std::cout << "Match jets " << '\n';}
//
// for(uint j=0; j<matched_pair_HOTVR_top.size(); ++j){ // loop over matched jets
//   TopJet parton_jet=matched_pair_HOTVR_top[j].second;
//   TopJet matched_jet=matched_pair_HOTVR_top[j].first;
//
//   //fill hists with matched jets
//   hist_matched_jets->fill_topjet(event, matched_jet, parton_jet);
//   if(parton_jet.pt()>200 && parton_jet.pt()<400)  hist_matched_jets_200->fill_topjet(event, matched_jet, parton_jet);
//   if(parton_jet.pt()>400 && parton_jet.pt()<600)  hist_matched_jets_400->fill_topjet(event, matched_jet, parton_jet);
//   if(parton_jet.pt()>600 && parton_jet.pt()<800)  hist_matched_jets_600->fill_topjet(event, matched_jet, parton_jet);
//   if(parton_jet.pt()>800 && parton_jet.pt()<1000)  hist_matched_jets_800->fill_topjet(event, matched_jet, parton_jet);
//   if(parton_jet.pt()>1000 && parton_jet.pt()<1200)  hist_matched_jets_1000->fill_topjet(event, matched_jet, parton_jet);
// }
// // ------MATCHING zum W--------
// //run_matching: loop over the parton jets and match them to the hotvr jets
   vector<TopJet> matched_jets;
   vector<TopJet> matched_parton_jets;
//   //run matching reco to W genjet
   matching->run_matching_W_top(_top_hotvr_jets, _top_parton_jets, _top_parton_jets_W); // TODO does this work? TODO wenn W dicht, dann zum W matchen, sonst top
    matched_jets = matching->get_matched_jets();
    matched_parton_jets = matching->get_matched_parton_jets();
    vector<pair<TopJet, TopJet>> matched_pair = matching->get_matched_pairs();
   if (debug) {std::cout << "Match jets " << '\n';}

   for(uint j=0; j<matched_pair.size(); ++j){ // loop over matched jets
     TopJet parton_jet=matched_pair[j].second;
     TopJet matched_jet=matched_pair[j].first;

     //fill hists with matched jets
     hist_matched_jets->fill_topjet(event, matched_jet, parton_jet);
     if(parton_jet.pt()>200 && parton_jet.pt()<400)  hist_matched_jets_200->fill_topjet(event, matched_jet, parton_jet);
     if(parton_jet.pt()>400 && parton_jet.pt()<600)  hist_matched_jets_400->fill_topjet(event, matched_jet, parton_jet);
     if(parton_jet.pt()>600 && parton_jet.pt()<800)  hist_matched_jets_600->fill_topjet(event, matched_jet, parton_jet);
     if(parton_jet.pt()>800 && parton_jet.pt()<1000)  hist_matched_jets_800->fill_topjet(event, matched_jet, parton_jet);
     if(parton_jet.pt()>1000 && parton_jet.pt()<1200)  hist_matched_jets_1000->fill_topjet(event, matched_jet, parton_jet);
   }


// // delete clustering infos
 clustering->Reset();
// decide whether or not to keep the current event in the output:
  return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the HOTVRWTopMatchingModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(HOTVRWTopMatchingModule)
