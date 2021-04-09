#include <vector>

void jet_display_hotvr(TFile* file, TString dir, TString prefix = "", Int_t num=-1)
{ 

  gdir = dir;

  SetupGlobalStyle(); 

  //TFile* file = new TFile("RocCycle.MC.TTbarEff_gen_jetdisplay2.root", "READ");
  //TFile* file = new TFile("genevt/RocCycle.MC.TTbarEff_gen_event86.root", "READ");  
  
  // store all jets with their subjets in this vector
  std::vector< std::vector<TH2F*> > subjets;
  subjets = GetSubjets(file);
  for (int i=0; i<subjets.size(); ++i){
    CreateContours(subjets[i]);
  }

  TCanvas *c = SetupCanvas2d();

  // some colors
  std::vector< std::vector<int> > cols;
  cols = GetColours(); 

  // gray hues for rejected jets
  //int lgray = TColor::GetColor( "#e6e6e6");
  int lgray = TColor::GetColor( "#ebebeb");
  int mgray = TColor::GetColor( "#dedede");
  int dgray = TColor::GetColor( "#d7d7d7");

  // here are the rejected subjets (by the mass jump criterion)
  TH2F* subjets_rejected;
  subjets_rejected = GetSubjetsRejected(file);
  subjets_rejected->GetXaxis()->SetTitle("#phi");
  subjets_rejected->GetYaxis()->SetTitle("#eta");
  subjets_rejected->SetTitle("");
  Cosmetics2d(subjets_rejected);
  FixHistForContour(subjets_rejected);
  DrawContour(subjets_rejected, lgray);  

  // here are the rejected subjets by the ptsub criterion
  TH2F* subjets_rejected_ptsub;
  subjets_rejected_ptsub = GetSubjetsRejectedByPtsub(file);
  if (subjets_rejected_ptsub){
    Cosmetics2d(subjets_rejected_ptsub);
    FixHistForContour(subjets_rejected_ptsub);
    DrawContour(subjets_rejected_ptsub, dgray);   
  } 

  // draw subjets
  for (int i=0; i<subjets.size(); ++i){
    for (int j=0; j<subjets[i].size(); ++j){  
      FixHistForContour(subjets[i][j]);
      DrawContour(subjets[i][j], cols[i][j]);
    }
  }
  
  // draw all stable particles
  DrawStableParts(file);

  // draw top's decay partons
  DrawTopDecay(file);

  HOTVR_label_jetdisplay();

  Eventnumber_jetdisplay(num, "HOTVR");

  gPad->RedrawAxis();

  c->SaveAs("plots/softdrop2_" + prefix + dir + "_hotvr.pdf");

}
  
