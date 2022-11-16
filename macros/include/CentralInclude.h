#include <iostream>
#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TArray.h>
#include <TPad.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>

using namespace std;

// style function
void SetStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(0);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetLegendBorderSize(0);
}
