#include "UHH2/HOTVRStudies/include/Clustering.h"

using namespace std;
using namespace fastjet;
using namespace contrib;

//constructor
Clustering::Clustering(std::string clustering)
  {
    // constructor: initialise all variables
    ifstream myfile(clustering);
    std::string line;
    if (myfile.is_open()) {
      while ( myfile>>line )
      {
        std::string value;
        myfile>>value;
        if(line=="rho") _rho=get_value(value);
        if(line=="mu") _mu=get_value(value);
        if(line=="theta") _theta=get_value(value);
        if(line=="rmin") _min_r=get_value(value);
        if(line=="rmax") _max_r=get_value(value);
        if(line=="ptmin") _ptmin=get_value(value);
        if(line=="clustering") _clustering_algorithmus=value;
        if(line=="pt_cut") _pt_cut=get_value(value);
        if(line=="z_cut") _z_cut=get_value(value);
        if(line=="beta") _beta=get_value(value);
        if(line=="pt_threshold") _pt_threshold=get_value(value);
        if(line=="theta_SD") _theta_SD=get_value(value);
      }
      myfile.close();
    }
    else  std::cout<<"file not found"<<std::endl;
    //show_settings();

  // // parameters for HOTVR (optimized for top-tagging)
//   mu = (30.0);     // massjump threshold
//   theta = (0.7);       // massjump parameter
//   max_r = (1.5);       // maximum allowed distance R
//   min_r = (0.1);     // minimum allowed distance R
//   rho = (600);       // cone shrinking parameter
//   pt_cut = (0); // minimum pT of subjets
//   ptmin = (100.);        // minimum pT of large jets
//   // parameters for SoftDrop
//   z_cut = 0.05;
//   beta = 0.0;
//   pt_threshold = 30;
// // for ISD
//   theta_SD = 0.0;

}
// cluster all
void Clustering::cluster_jets(vector<PseudoJet> pseudojets)
{
  // cluster_HOTVR_jets(pseudojets);
  cluster_HOTVR_SD_jets(pseudojets);
  //cluster_VR_SD_jets(pseudojets);
  //cluster_VR_ISD_jets(pseudojets);
}
// HOTVR including mass jump Clustering
void Clustering::cluster_HOTVR_jets(vector<PseudoJet> pseudojets)
{
  HOTVR hotvr_plugin(_mu, _theta, _min_r, _max_r, _rho, _pt_cut, HOTVR::CALIKE); // initialize plugin
  JetDefinition jet_def(&hotvr_plugin); // set up jet definition and cluster sequence
  ClusterSequence _clust_seq(pseudojets, jet_def);
  _hotvr_jets=hotvr_plugin.get_jets(); //HOTVR Clustering
//  std::vector<PseudoJet> rejected_jets=hotvr_plugin.get_rejected_cluster(); // get the rejected clusters below the pt threshold (CLUSTER)
//  std::vector<PseudoJet> soft_jets=hotvr_plugin.get_soft_cluster(); // removed via Soft Drop Condition (NOVETO)

  for (unsigned int i = 0; i < _hotvr_jets.size(); ++i) {
    double R = 1.5;
    double b = 1.0;

// calculate Nsubjettiness
    Nsubjettiness nSub1(1, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    Nsubjettiness nSub2(2, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    Nsubjettiness nSub3(3, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    double tau1 = nSub1(_hotvr_jets[i]);
    double tau2 = nSub2(_hotvr_jets[i]);
    double tau3 = nSub3(_hotvr_jets[i]);

    //convert into TopJet
    _top_hotvr_jets.push_back(convert_jet(_hotvr_jets[i], tau1, tau2, tau3));
 }
}
// HOTVR including Soft Drop Clustering
void Clustering::cluster_HOTVR_SD_jets(vector<PseudoJet> pseudojets)
{
  HOTVR hotvr_plugin(_beta, _z_cut, _pt_threshold, _min_r, _max_r, _rho, _pt_cut, _mu, HOTVR::CALIKE); // initialize plugin
  JetDefinition jet_def(&hotvr_plugin); // set up jet definition and cluster sequence
ClusterSequence _clust_seq(pseudojets, jet_def);
  _hotvr_jets=hotvr_plugin.get_jets(); //HOTVR Clustering
  vector<PseudoJet> rejected_jets=hotvr_plugin.get_rejected_cluster(); // get the rejected clusters below the pt threshold (CLUSTER)
  vector<PseudoJet> soft_jets=hotvr_plugin.get_soft_cluster(); // removed via Soft Drop Condition (NOVETO)
  _rejected_subjets=convert_subjets(hotvr_plugin.get_rejected_subjets()); // get the rejected subjets with ptsub
  // convert rejected jets into topjets
  for (size_t j = 0; j < rejected_jets.size(); j++) {
    _rejected_cluster.push_back(convert_jet(rejected_jets[j]));
  }
  // convert soft jets into topjets
  for (size_t j = 0; j < soft_jets.size(); j++) {
    _soft_cluster.push_back(convert_jet(soft_jets[j]));
  }
  // loop over hotvr jets
  for (unsigned int i = 0; i < _hotvr_jets.size(); ++i) {
    double R = 1.5;
    double b = 1.0;
    // calculate Nsubjettiness
    Nsubjettiness nSub1(1, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    Nsubjettiness nSub2(2, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    Nsubjettiness nSub3(3, OnePass_KT_Axes(), NormalizedMeasure(b, R));
    double tau1 = nSub1(_hotvr_jets[i]);
    double tau2 = nSub2(_hotvr_jets[i]);
    double tau3 = nSub3(_hotvr_jets[i]);
    //convert into TopJet
    _top_hotvr_jets.push_back(convert_jet(_hotvr_jets[i], tau1, tau2, tau3));
  // save the jet constituents
    auto jet_constituents = _hotvr_jets[i].constituents();
    _hotvr_jet_constituents.push_back(_hotvr_jets[i].constituents());
  //  std::cout << "n constituents " << jet_constituents.size() << '\n';
//for (size_t k = 0; k < jet_constituents.size(); k++) {
//  std::cout << "mass constituents " << jet_constituents[k].m() << '\n';
//}

 }// end loop over hotvr jets
}

// Variable R plus SoftDrop
void Clustering::cluster_VR_SD_jets(vector<PseudoJet> pseudojets)
{
  VariableRPlugin VR_plugin(_rho, _min_r, _max_r, VariableRPlugin::CALIKE);
  JetDefinition jet_def_VR(&VR_plugin);
  ClusterSequence _clust_seq_VR(pseudojets, jet_def_VR);
  SoftDrop _sd(_beta, _z_cut);

  _vr_jets=sorted_by_pt(_clust_seq_VR.inclusive_jets(_pt_threshold)); //VR Clustering
  for(unsigned i=0; i<_vr_jets.size(); i++) //groom jets with SoftDrop
  {
    _vr_jet_constituents.push_back(_vr_jets[i].constituents());
    _top_vr_jets.push_back(convert_jet(_vr_jets[i]));
    _vr_jets_SD.push_back(_sd(_vr_jets[i]));
  }
}

// Variable R plus Iterative SoftDrop
void Clustering::cluster_VR_ISD_jets(vector<PseudoJet> pseudojets)
{
  VariableRPlugin VR_plugin(_rho, _min_r, _max_r, VariableRPlugin::CALIKE);
  JetDefinition jet_def_VR(&VR_plugin);
  ClusterSequence _clust_seq_VR(pseudojets, jet_def_VR);
  _vr_jets=sorted_by_pt(_clust_seq_VR.inclusive_jets(_pt_threshold)); //VR Clustering

  //double R_VR = ? how do we get the variable radius from the VR plugin? instead of min_r
  double R=1;
  int n=10; // number of layers (-1 <> infinite)
  contrib::RecursiveSoftDrop rsd(_beta, _z_cut, n, R);
  // keep addittional structure info (used below)
  rsd.set_verbose_structure(true);
  // Instead of recursing into both branches found by the previous
  // iteration, only keep recursing into the hardest one
  rsd.set_hardest_branch_only();

  for(unsigned i=0; i<_vr_jets.size(); i++) //groom jets with Iterative SoftDrop
  {
    _vr_jets_ISD.push_back(rsd(_vr_jets[i]));
  }
 }

// cluster parton jets and throw away top daughters
void Clustering::cluster_parton_jets(vector<PseudoJet> pseudojets, bool ttbar)
{
  JetDefinition jet_def(antikt_algorithm,1.0);
  vector<PseudoJet> parton_jets;
  ClusterSequence clust_seq(pseudojets, jet_def);
  parton_jets = sorted_by_pt(clust_seq.inclusive_jets(100.));

  if(!ttbar) _parton_fatjets = parton_jets; //in case of a qcd sample keep all parton jets
  else{ //in case of a ttbar sample keep only jets that contain a top
    for(unsigned i=0; i<parton_jets.size(); i++){
      bool candidate=false;
      for(unsigned j=0;j<parton_jets[i].constituents().size(); j++) if(parton_jets[i].constituents().at(j).user_index()==6) candidate=true;
      if(candidate){ _parton_fatjets.push_back(parton_jets[i]);}
    }
  }
  for (unsigned int i = 0; i < _parton_fatjets.size(); ++i) {
    //convert into TopJet
    _top_parton_jets.push_back(convert_jet(_parton_fatjets[i]));
  }
}

//converts a pseudojet into a topjet, the values for the groomed tau are set
TopJet Clustering::convert_jet(PseudoJet pseudojet, double tau1, double tau2, double tau3)
{
	LorentzVector v4(pseudojet.pt(), pseudojet.eta(), pseudojet.phi(), pseudojet.E());
	TopJet topjet;
	topjet.set_v4(v4);
  if(pseudojet.has_user_info<HOTVRinfo>()){
    HOTVRinfo hi = pseudojet.user_info<HOTVRinfo>();
    topjet.set_subjets(convert_subjets(hi.subjets()));
    topjet.set_hotvr_mmin(hi.mmin());
    topjet.set_hotvr_fpt1(hi.ptfraction(0));
    topjet.set_max_distance(hi.max_distance());
  }
	topjet.set_tau1_groomed(tau1);
	topjet.set_tau2_groomed(tau2);
	topjet.set_tau3_groomed(tau3);

	return topjet;
}
//converts a pseudojet into a topjet with subjets
TopJet Clustering::convert_jet(PseudoJet pseudojet)
{
  LorentzVector v4(pseudojet.pt(), pseudojet.eta(), pseudojet.phi(), pseudojet.E());
	TopJet topjet;
	topjet.set_v4(v4);
  if(pseudojet.has_user_info<HOTVRinfo>()){
    HOTVRinfo hi = pseudojet.user_info<HOTVRinfo>();
    topjet.set_subjets(convert_subjets(hi.subjets()));
    topjet.set_hotvr_mmin(hi.mmin());
    topjet.set_hotvr_fpt1(hi.ptfraction(0));
    topjet.set_max_distance(hi.max_distance());
  }
	return topjet;
}
//converts a vector of pseudojets into topjets
vector<Jet> Clustering::convert_subjets(vector<PseudoJet> subjets)
{
  vector<Jet> jets;
  for (size_t i = 0; i < subjets.size(); i++) {
    PseudoJet pseudojet=subjets[i];
    LorentzVector v4(pseudojet.pt(), pseudojet.eta(), pseudojet.phi(), pseudojet.E());
  	Jet jet;
  	jet.set_v4(v4);
    jets.push_back(jet);
  }
	return jets;
}
// get the value for the specific parameter from the config file
double Clustering::get_value(std::string word){
  return atof(word.c_str());
}

void Clustering::show_settings(){
  std::cout<<"-----Clustering------"<<std::endl;
  std::cout<<"Algorithmus: "<<_clustering_algorithmus<<std::endl;
  std::cout<<"Minimum Jet pT: "<<_ptmin<<"GeV"<<std::endl;
  if(_clustering_algorithmus=="hotvr" || _clustering_algorithmus=="variableR") std::cout<<"rho: "<<_rho<<"GeV"<<std::endl;
  if(_clustering_algorithmus=="hotvr" || _clustering_algorithmus=="variableR") std::cout<<"minimum radius: "<<_min_r<<std::endl;
  if(_clustering_algorithmus=="hotvr" || _clustering_algorithmus=="variableR") std::cout<<"maximum radius: "<<_max_r<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"mu: "<<_mu<<"GeV"<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"theta: "<<_theta<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"z_cut: "<<_z_cut<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"beta: "<<_beta<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"pt_threshold: "<<_pt_threshold <<"GeV"<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"pt_cut for subjets: "<<_pt_threshold <<"GeV"<<std::endl;
  if(_clustering_algorithmus=="hotvr") std::cout<<"theta for SD: "<<_theta_SD<<std::endl;

  std::cout<<"---------------------"<<std::endl;
}
