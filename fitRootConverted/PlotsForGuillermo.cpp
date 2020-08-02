#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
using namespace std;
#include <math.h>
#include <vector>


#include "TH2.h"



void PlotsForGuillermo(){

  TFile* fileListStd    = new TFile("AnalysisResultsNewLHC16s_standard_01072020.root");
  TFile* fileListNoPDCA = new TFile("AnalysisResultsNewLHC16s_noPDCA_01072020.root");
  TFile* fileListNoLPT  = new TFile("AnalysisResultsNewLHC16s_noLPT_01072020.root");
  // TFile* fileListStd    = new TFile("AnalysisResultsNewLHC16r_std_01072020.root");
  // TFile* fileListNoPDCA = new TFile("AnalysisResultsNewLHC16r_nopdca_01072020.root");
  // TFile* fileListNoLPT  = new TFile("AnalysisResultsNewLHC16r_nolpt_01072020.root");
  TDirectory* dirStd    = fileListStd   ->GetDirectory("MyTask");
  TDirectory* dirNoPDCA = fileListNoPDCA->GetDirectory("MyTask");
  TDirectory* dirNoLPT  = fileListNoLPT ->GetDirectory("MyTask");
  TList* listingsStd;
  TList* listingsNoPDCA;
  TList* listingsNoLPT;
  dirStd   ->GetObject("MyOutputContainer", listingsStd    );
  dirNoPDCA->GetObject("MyOutputContainer", listingsNoPDCA );
  dirNoLPT ->GetObject("MyOutputContainer", listingsNoLPT  );
  TH1F* StdH      = (TH1F*)listingsStd   ->FindObject("fInvariantMassDistributionZeroZNAH");
  TH1F* NoPDCAH   = (TH1F*)listingsNoPDCA->FindObject("fInvariantMassDistributionZeroZNAH");
  TH1F* NoLPTH    = (TH1F*)listingsNoLPT ->FindObject("fInvariantMassDistributionZeroZNAH");
  TH1F* StdHv2    = new TH1F("StdHv2",    "StdHv2",    500, 0, 5);
  TH1F* NoPDCAHv2 = new TH1F("NoPDCAHv2", "NoPDCAHv2", 500, 0, 5);
  TH1F* NoLPTHv2  = new TH1F("NoLPTHv2",  "NoLPTHv2",  500, 0, 5);
  for ( Int_t i = 0; i < StdHv2->GetNbinsX(); i++ ) {
    StdHv2   ->SetBinContent( i, StdH   ->GetBinContent(i) );
    StdHv2   ->SetBinError  ( i, StdH   ->GetBinError  (i) );
    NoPDCAHv2->SetBinContent( i, NoPDCAH->GetBinContent(i) );
    NoPDCAHv2->SetBinError  ( i, NoPDCAH->GetBinError  (i) );
    NoLPTHv2 ->SetBinContent( i, NoLPTH ->GetBinContent(i) );
    NoLPTHv2 ->SetBinError  ( i, NoLPTH ->GetBinError  (i) );
  }
  StdHv2   ->Rebin(5);
  NoPDCAHv2->Rebin(5);
  NoLPTHv2 ->Rebin(5);

  StdHv2   ->SetLineWidth(2);
  NoPDCAHv2->SetLineWidth(2);
  NoLPTHv2 ->SetLineWidth(2);
  StdHv2   ->SetLineColor(kBlue);
  NoPDCAHv2->SetLineColor(kRed);
  NoLPTHv2 ->SetLineColor(kMagenta);
  new TCanvas;

  NoPDCAHv2->Draw();
  NoLPTHv2 ->Draw("same");
  StdHv2   ->Draw("same");


  TFile* f = new TFile("LHC16s.root", "recreate");
  // TFile* f = new TFile("LHC16r.root", "recreate");
  NoPDCAHv2->Write();
  NoLPTHv2 ->Write();
  StdHv2   ->Write();
  f->Close();

}
