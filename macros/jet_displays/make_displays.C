#include "style.C"
#include "jet_display_helpers.C"
#include "jet_display_hotvr.C"
#include "jet_display_akt.C"


void make_displays()
{
    gROOT->SetBatch(true);

    TString prefix = "test_highpt_12_05_";

    // 50 events for high and low pt:
    //TFile* file = new TFile("JetDisplayCycle.MC.TTbarEff_gen_tight_selection_subjets.root", "READ");

    // high resolution, high pt
    TFile* file = new TFile("/nfs/dust/cms/user/albrecha/uhh2_102X_v2/CMSSW_10_2_17/src/UHH2/HOTVRStudies/macros/jet_displays/root_files/uhh2.AnalysisModuleRunner.MC.ttbar_pythia8_flat_nnpdf23.root", "READ");
    // TFile* file = new TFile("JetDisplayCycle.MC.TTbarEff_gen_softdrop.root", "READ");
    // high resolution, low pt
    //TFile* file = new TFile("JetDisplayCycle.MC.TTbarEff_gen_tight_selection_highres2.root", "READ");

  	// loop over directories in file and plot jets for each directory
  	// (each holds one event)
  	file->cd();

  	std::vector<TString> dirs;

  	TKey *key;
  	TIter nextkey( gDirectory->GetListOfKeys() );
  	while ( (key = (TKey*)nextkey())) {

      TObject *obj = key->ReadObj();
      if ( obj->IsA()->InheritsFrom( TDirectory::Class() ) ) {
        TString name = obj->GetName();
        cout << "dirname = " << name << endl;
        if (name.Contains("JetDisplay")) dirs.push_back(name);
      }
    }

    // before plotting: delete ROOT's random number generator
    gRandom = NULL;
	  for (Int_t i=0; i<dirs.size(); ++i){
        cout << "-------dirname = " << dirs[i] << endl;

      UInt_t ievent = GetEventNumber(dirs[i]);
      //if (ievent!=0) continue;
      NewEvent(ievent);
		  Int_t num = ievent+2;
      if (dirs[i].Contains("_akt_")) jet_display_akt(file, dirs[i], prefix, num);
		  else if (dirs[i].Contains("_ca_")) jet_display_akt(file, dirs[i], prefix, num);
		  else jet_display_hotvr(file, dirs[i], prefix, num);
        cout << "-------dirname = " << dirs[i] << " ----finished---" << endl;

	  }

}
