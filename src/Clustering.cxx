#include "UHH2/HOTVRStudies/include/Clustering.h"

using namespace std;
using namespace fastjet;
using namespace contrib;

//constructor
Clustering::Clustering()
{}
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
        if(line=="rho") _rho=get_value(value); // slope of effective radius
        if(line=="alpha") _alpha=get_value(value); // exponent of effective radius
        if(line=="mu") _mu=get_value(value); // MJ: mass threshold; SD: subjet mass threshold
        if(line=="theta") _theta=get_value(value); // MJ strengh
        if(line=="rmin") _min_r=get_value(value); // radius minimum
        if(line=="rmax") _max_r=get_value(value); // radius maximum

        if(line=="ptmin") _ptmin=get_value(value); // min pt for VR clustering
        if(line=="clustering") _clustering_algorithmus=value; // clustering method (CA, kt or Anti-kt)
        if(line=="pt_cut") _pt_cut=get_value(value); // min pt of subjets (HOTVR clustering)

        if(line=="z_cut") _z_cut=get_value(value); // SD parameter
        if(line=="beta") _beta=get_value(value); // SD parameter
        if(line=="pt_threshold") _pt_threshold=get_value(value); // pt clustering threshold (default = 0)
      }
      myfile.close();
    }
    else  std::cout<<"file not found"<<std::endl;
    //if(_settings_not_shown){show_settings();}

}
// cluster all
void Clustering::cluster_jets(vector<PseudoJet> pseudojets)
{
  if(_clustering_algorithmus=="HOTVR" || _clustering_algorithmus=="HOTVR_MJ"){cluster_HOTVR_jets(pseudojets);}
  else if(_clustering_algorithmus=="HOTVR_SD" || _clustering_algorithmus=="hotvr_sd"){cluster_HOTVR_SD_jets(pseudojets);}
  else if(_clustering_algorithmus=="VR" || _clustering_algorithmus=="VR_SD"){cluster_VR_SD_jets(pseudojets);}
  else if(_clustering_algorithmus=="VR_ISD"){cluster_VR_ISD_jets(pseudojets);}
  else{std::cout << "clustering mode not found" << '\n';}
}

// --------------HOTVR including mass jump Clustering--------------------------------
void Clustering::cluster_HOTVR_jets(vector<PseudoJet> pseudojets)
{
  HOTVR hotvr_plugin(_mu, _theta, _min_r, _max_r, _rho, _pt_cut, HOTVR::CALIKE); // initialize plugin
  JetDefinition jet_def(&hotvr_plugin); // set up jet definition and cluster sequence
  //ClusterSequence _clust_seq(pseudojets, jet_def);
  _clust_seq = new ClusterSequence(pseudojets, jet_def);
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
// --------------------HOTVR including Soft Drop Clustering-----------------------------
 void Clustering::cluster_HOTVR_SD_jets(vector<PseudoJet> pseudojets)
 {
  vector<PseudoJet> pseudojets_to_cluster=pseudojets;

  bool ghost = false;
  if(ghost){pseudojets_to_cluster = add_ghosts(pseudojets);}

  HOTVR hotvr_plugin(_beta, _z_cut, _pt_threshold, _min_r, _max_r, _rho, _pt_cut, _mu, HOTVR::CALIKE, _alpha); // initialize plugin
  JetDefinition jet_def(&hotvr_plugin); // set up jet definition and cluster sequence

  //ClusterSequence _clust_seq(pseudojets_to_cluster, jet_def);
  _clust_seq = new ClusterSequence(pseudojets_to_cluster, jet_def);

  _hotvr_jets=hotvr_plugin.get_jets(); //HOTVR Clustering
  // _jet0_subjets_constituents = save_constituents(_hotvr_jets[0].user_info<HOTVRinfo>().subjets());
  // _jet1_subjets_constituents = save_constituents(_hotvr_jets[1].user_info<HOTVRinfo>().subjets());
  // _jet2_subjets_constituents = save_constituents(_hotvr_jets[2].user_info<HOTVRinfo>().subjets());
  // _jet3_subjets_constituents = save_constituents(_hotvr_jets[3].user_info<HOTVRinfo>().subjets());

  _rejected_cluster=hotvr_plugin.get_rejected_cluster(); // get the rejected clusters below the pt threshold (CLUSTER)
//  _rejected_cluster_constituents = save_constituents(_rejected_cluster);

  _soft_cluster=hotvr_plugin.get_soft_cluster(); // removed via Soft Drop Condition (NOVETO)
//  _soft_cluster_constituents = save_constituents(_soft_cluster);

  _rejected_subjets=hotvr_plugin.get_rejected_subjets(); // get the rejected subjets with ptsub
//  _rejected_subjets_constituents = save_constituents(_rejected_subjets);

  // convert rejected subjets into UHH2  jets
  _top_rejected_subjets=convert_subjets(_rejected_subjets);
  // convert rejected jets into topjets
  for (size_t j = 0; j < _rejected_cluster.size(); j++) {
    _top_rejected_cluster.push_back(convert_jet(_rejected_cluster[j]));
  }
  // convert soft jets into topjets
  for (size_t j = 0; j < _soft_cluster.size(); j++) {
    _top_soft_cluster.push_back(convert_jet(_soft_cluster[j]));
  }
  for (unsigned int i = 0; i < _hotvr_jets.size(); ++i) {   // loop over hotvr jets
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
  //  _hotvr_jet_constituents.push_back(_hotvr_jets[i].constituents());
 }// end loop over hotvr jets
 }


//---------------------Variable R plus SoftDrop--------------------------------
void Clustering::cluster_VR_SD_jets(vector<PseudoJet> pseudojets)
{
  VariableRPlugin VR_plugin(_rho, _min_r, _max_r, VariableRPlugin::CALIKE);
  JetDefinition jet_def(&VR_plugin);
  //ClusterSequence _clust_seq(pseudojets, jet_def);
  _clust_seq = new ClusterSequence(pseudojets, jet_def);

  SoftDrop _sd(_beta, _z_cut);

  _vr_jets=sorted_by_pt(_clust_seq->inclusive_jets(_ptmin)); //VR Clustering
  for(unsigned i=0; i<_vr_jets.size(); i++) //groom jets with SoftDrop
  {
    _vr_jet_constituents.push_back(_vr_jets[i].constituents());
    _top_vr_jets.push_back(convert_jet(_vr_jets[i]));
  //  _vr_jets_SD.push_back(_sd(_vr_jets[i]));
  }
}

//---------------Variable R plus Iterative SoftDrop----------------------------
void Clustering::cluster_VR_ISD_jets(vector<PseudoJet> pseudojets)
{
  VariableRPlugin VR_plugin(_rho, _min_r, _max_r, VariableRPlugin::CALIKE);
  JetDefinition jet_def(&VR_plugin);
  //ClusterSequence _clust_seq(pseudojets, jet_def);
  _clust_seq = new ClusterSequence(pseudojets, jet_def);
  _vr_jets=sorted_by_pt(_clust_seq->inclusive_jets(_ptmin)); //VR Clustering

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

//-------------cluster parton jets and throw away top daughters-----------------
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

//----------converts a pseudojet into a topjet----------------------------
//----------the values for the groomed tau are set------------------------
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
//-------------converts a pseudojet into a topjet with subjets-------------
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
//-------------converts a vector of pseudojets into topjets--------------------
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
//-------get the value for the specific parameter from the config file-------
double Clustering::get_value(std::string word){
  return atof(word.c_str());
}
//-----------------------show settings---------------------------------------
void Clustering::show_settings(){
  std::cout<<"-----Clustering------"<<std::endl;
  std::cout<<"Algorithmus: "<<_clustering_algorithmus<<std::endl;

  if(_clustering_algorithmus=="hotvr" || _clustering_algorithmus=="variableR" || _clustering_algorithmus=="hotvr_sd")
  {std::cout<<"rho: "<<_rho<<"GeV"<<std::endl;
  std::cout<<"minimum radius: "<<_min_r<<std::endl;
  std::cout<<"maximum radius: "<<_max_r<<std::endl;}

  if(_clustering_algorithmus=="hotvr")
  {std::cout<<"mu: "<<_mu<<"GeV"<<std::endl;
  std::cout<<"theta: "<<_theta<<std::endl;
  std::cout<<"pt_threshold: "<<_pt_threshold <<"GeV"<<std::endl;
  std::cout<<"pt_cut for subjets: "<<_pt_cut <<"GeV"<<std::endl;}

  if(_clustering_algorithmus=="hotvr_sd")
  {std::cout<<"z_cut: "<<_z_cut<<std::endl;
  std::cout<<"beta: "<<_beta<<std::endl;
  std::cout<<"mu: "<<_mu<<"GeV"<<std::endl;}

  if(_clustering_algorithmus=="variableR")
  {std::cout<<"Minimum Jet pT: "<<_ptmin<<"GeV"<<std::endl;}

  std::cout<<"---------------------"<<std::endl;
  _settings_not_shown = false;
}

// --------------- Add Ghost GenParticles to Pseudo Jet of GenParticles ------------
vector<PseudoJet> Clustering::add_ghosts(vector<PseudoJet> gen_in){
  double pt, eta, phi, E, p;
  TLorentzVector ghost_v4;
  for(uint i=0; i < 100; ++i){
    for(uint i_=0; i_ < 100; ++i_ ){
      phi = -M_PI + (i+0.5)*(2*M_PI/100);
      eta = -M_PI + (i_+0.5)*(2*M_PI/100);
      // create random energy
      mt19937 rng( random_device{}() );
      uniform_real_distribution<> dist(0.1, 1);
      double randnr = dist(rng);
      E = randnr*0.00001;
      p = sqrt(E*E);
      pt = p/cosh(eta);
      ghost_v4.SetPtEtaPhiE(pt, eta, phi, E);
      PseudoJet ghost( ghost_v4.Px(), ghost_v4.Py(), ghost_v4.Pz(), ghost_v4.E() );
      gen_in.push_back(ghost);
    }
  }
  return gen_in;
}
//--------------helper save constituents----------------------
vector<vector<PseudoJet>> Clustering::save_constituents(vector<PseudoJet> jets_in)
{
  vector<vector<PseudoJet>> jets_constituents;
  for (size_t i = 0; i < jets_in.size(); i++) {
    jets_constituents.push_back(jets_in[i].constituents());
  }
  return jets_constituents;
}
//-----------------reset clustering sequence------------------
void Clustering::Reset()
{
  delete _clust_seq;
}
//----------------------------GETTER---------------------------
vector<PseudoJet> Clustering::get_clustered_jets(){
  if(_clustering_algorithmus=="HOTVR" || _clustering_algorithmus=="HOTVR_MJ"){return _hotvr_jets;}
  else if(_clustering_algorithmus=="HOTVR_SD" || _clustering_algorithmus=="hotvr_sd"){return _hotvr_jets;}
  else if(_clustering_algorithmus=="VR" || _clustering_algorithmus=="VR_SD"){return _vr_jets;}
  else if(_clustering_algorithmus=="VR_ISD"){return _vr_jets_ISD;}
  else{
    throw runtime_error("Clustering mode not found!");
          return _hotvr_jets;
  }
}
vector<vector<PseudoJet>> Clustering::get_clustered_jet_constituents(){
  if(_clustering_algorithmus=="HOTVR" || _clustering_algorithmus=="HOTVR_MJ"){return _hotvr_jet_constituents;}
  else if(_clustering_algorithmus=="HOTVR_SD" || _clustering_algorithmus=="hotvr_sd"){return _hotvr_jet_constituents;}
  else if(_clustering_algorithmus=="VR" || _clustering_algorithmus=="VR_SD"){return _vr_jet_constituents;}
  else{
    throw runtime_error("Clustering mode not found!");
          return _hotvr_jet_constituents;
  }
}
