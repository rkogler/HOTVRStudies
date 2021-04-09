#include <iostream>
#include <memory>
// include general UHH2 classes
#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/common/include/TTbarGen.h"
// include everything from the HOTVR Studies
#include "UHH2/HOTVRStudies/include/Matching.h"
#include "UHH2/HOTVRStudies/include/Clustering.h"
#include "UHH2/HOTVRStudies/include/JetDisplayHists.h"
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

class JetDisplayModule: public AnalysisModule {
public:

  explicit JetDisplayModule(Context & ctx);
  virtual bool process(Event & event) override;

private:
//initialize hist classes
std::unique_ptr<JetDisplayHists> hist_jet_display;

std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

// initialize event handle
Event::Handle<vector<PseudoJet>> h_parts;

Event::Handle<vector<PseudoJet>> h_jets;
Event::Handle<vector<PseudoJet>> h_rejected_cluster;
Event::Handle<vector<PseudoJet>> h_soft_cluster;
Event::Handle<vector<PseudoJet>> h_rejected_subjets;

// Event::Handle<vector<vector<PseudoJet>>> h_jets;
// Event::Handle<vector<vector<PseudoJet>>> h_rejected_cluster;
// Event::Handle<vector<vector<PseudoJet>>> h_soft_cluster;
// Event::Handle<vector<vector<PseudoJet>>> h_rejected_subjets;

Event::Handle<vector<vector<PseudoJet>>> h_jet0_subjets;
Event::Handle<vector<vector<PseudoJet>>> h_jet1_subjets;
Event::Handle<vector<vector<PseudoJet>>> h_jet2_subjets;
Event::Handle<vector<vector<PseudoJet>>> h_jet3_subjets;

// initialize classes
  string m_clustering;
  Matching* matching;
  Clustering* clustering;

// initialize vectors of jets containing pseudojets with constituents
  vector<fastjet::PseudoJet> parts;

  vector<fastjet::PseudoJet> hotvr_jets;
  vector<fastjet::PseudoJet> rejected_cluster;
  vector<fastjet::PseudoJet> soft_cluster;
  vector<fastjet::PseudoJet> rejected_subjets;

  // vector<vector<fastjet::PseudoJet>> hotvr_jets;
  // vector<vector<fastjet::PseudoJet>> rejected_cluster;
  // vector<vector<fastjet::PseudoJet>> soft_cluster;
  // vector<vector<fastjet::PseudoJet>> rejected_subjets;

  vector<vector<fastjet::PseudoJet>> jet0_subjets;
  vector<vector<fastjet::PseudoJet>> jet1_subjets;
  vector<vector<fastjet::PseudoJet>> jet2_subjets;
  vector<vector<fastjet::PseudoJet>> jet3_subjets;

  string dataset_version;

  bool isTTbar;
  bool is_mc, is_qcd;

  int nevent=0;
  uint _event_max;
};

/*
 ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
 ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

JetDisplayModule::JetDisplayModule(Context & ctx){
  cout << "Starting JetDisplayModule!" << endl;
// get info from xml
  m_clustering = ctx.get("Clustering");
// check for the dataset version (ttbar or QCD)
  dataset_version = ctx.get("dataset_version");
  isTTbar = dataset_version.find("ttbar") == 0;
  is_mc = ctx.get("dataset_type") == "MC";
  is_qcd = (dataset_version.find("QCD") == 0);

  h_parts = ctx.get_handle<vector<PseudoJet>>("parts");

  h_jets = ctx.get_handle<vector<PseudoJet>>("jets");
  h_rejected_cluster = ctx.get_handle<vector<PseudoJet>>("rejected_cluster");
  h_soft_cluster = ctx.get_handle<vector<PseudoJet>>("soft_cluster");
  h_rejected_subjets = ctx.get_handle<vector<PseudoJet>>("rejected_subjets");

  // h_jets = ctx.get_handle<vector<vector<PseudoJet>>>("jets");
  // h_rejected_cluster = ctx.get_handle<vector<vector<PseudoJet>>>("rejected_cluster");
  // h_soft_cluster = ctx.get_handle<vector<vector<PseudoJet>>>("soft_cluster");
  // h_rejected_subjets = ctx.get_handle<vector<vector<PseudoJet>>>("rejected_subjets");

  h_jet0_subjets = ctx.get_handle<vector<vector<PseudoJet>>>("jet0_subjets");
  h_jet1_subjets = ctx.get_handle<vector<vector<PseudoJet>>>("jet1_subjets");
  h_jet2_subjets = ctx.get_handle<vector<vector<PseudoJet>>>("jet2_subjets");
  h_jet3_subjets = ctx.get_handle<vector<vector<PseudoJet>>>("jet3_subjets");

  const std::string ttbar_gen_label("ttbargen");
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  hist_jet_display.reset( new JetDisplayHists(ctx, "JetDisplay_event01")); //TODO add for more events or find elegant solution

  //for(unsigned int i=0;i<_event_max;i++){
    //TString hname = string::Format("JetDisplay_event%d",i);
    //hist_jet_display.reset( new JetDisplayHists(ctx, JetDisplay_event01));
    //hname = TString::Format("JetDisplay_akt_event%d",i);
    //hist_jet_display_akt.reset( new JetDisplayHists(hname));
    //hname = TString::Format("JetDisplay_ca_event%d",i);
    //hist_jet_display_ca.reset( new JetDisplayHists(hname));
    //hname = TString::Format("JetDisplay_highpT_event%d",i);
    //hist_jet_display_highpT.reset( new JetDisplayHists(hname));
    //hname = TString::Format("JetDisplay_highpT_akt_event%d",i);
    //hist_jet_display_highpT_akt.reset( new JetDisplayHists(hname));
    //hname = TString::Format("JetDisplay_highpT_ca_event%d",i);
    //hist_jet_display_highpT_ca.reset( new JetDisplayHists(hname));
  //  cout<<"Initializing "<<(double)i*100./(double)_event_max<<"%"<<std::endl;
  //}
  clustering = new Clustering(m_clustering);
  matching = new Matching();
}
/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/
bool JetDisplayModule::process(Event & event) {
// here define genparticles and read from event
  auto genparticles = event.genparticles;

  if(isTTbar){
  ttgenprod->process(event);
  }

//MATCHING -> class to filter the stable particles from the genparticles and create a pseudojet from them
  matching->set_stable_particles(genparticles);
  parts = matching->get_stableParticles();

//CLUSTERING -> clusters jets depending on the algorithm that is chosen
  clustering->cluster_jets(parts); // cluster the pseudojets, possible modes defined in hotvr.config: "HOTVR, HOTVR_SD, VR"

  hotvr_jets = clustering->get_hotvr_jets();
  // get the rejected subjets
  rejected_subjets = clustering->get_rejected_subjets();
  rejected_cluster = clustering->get_rejected_cluster();
  soft_cluster = clustering->get_soft_cluster();
  // hotvr_jets = clustering->get_hotvr_jet_constituents();
  // // get the rejected subjets
  // rejected_subjets = clustering->get_rejected_subjets_constituents();
  // rejected_cluster = clustering->get_rejected_cluster_constituents();
  // soft_cluster = clustering->get_soft_cluster_constituents();

  jet0_subjets = clustering->get_jet0_subjets_constituents();
  jet1_subjets = clustering->get_jet1_subjets_constituents();
  jet2_subjets = clustering->get_jet2_subjets_constituents();
  jet3_subjets = clustering->get_jet3_subjets_constituents();

  event.set(h_jets, hotvr_jets);
  event.set(h_parts, parts);
  event.set(h_rejected_cluster, rejected_cluster);
  event.set(h_soft_cluster, soft_cluster);
  event.set(h_rejected_subjets, rejected_subjets);

  event.set(h_jet0_subjets, jet0_subjets);
  event.set(h_jet1_subjets, jet1_subjets);
  event.set(h_jet2_subjets, jet2_subjets);
  event.set(h_jet3_subjets, jet3_subjets);

  if(isTTbar){ //TODO selection on events (pt, toptagging)
    hist_jet_display->fill(event); //TODO add for further events or find elegant solution
  }
  // delete clustering infos
  clustering->Reset();
// decide whether or not to keep the current event in the output:
  return true;
}

// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the JetDisplayModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(JetDisplayModule)
