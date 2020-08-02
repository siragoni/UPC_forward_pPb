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



void ReadHistoCounter(){

  // TFile* fileList = new TFile("AnalysisResultsNewLHC16s_correlations_14062020.root");  //Used file: for LHC16s proper trigger
  TFile* fileList = new TFile("AnalysisResultsNewLHC16s_OnlyMainCMUP.root");  //Used file: for LHC16s proper trigger
  // TFile* fileList = new TFile("AnalysisResultsNewLHC16r_OnlyMainCMUP.root");  //Used file: for LHC16s proper trigger
  // TFile* fileList = new TFile("AnalysisResultsNewLHC16r_OnlyMainCMUP_Run1.root");  //Used file: for LHC16s proper trigger
  // TFile* fileList = new TFile("AnalysisResultsNewLHC16r_correlations_14062020.root");  //Used file: for LHC16s proper trigger
  TDirectory* dir = fileList->GetDirectory("MyTask");
  TList* listings;
  dir->GetObject("MyOutputContainer", listings);
  TH1F* fCounterH   = (TH1F*)listings->FindObject("fCounterH");
  Double_t counters[300];
  for ( Int_t i = 0; i < fCounterH->GetNbinsX(); i++ ) {
    counters[i] = fCounterH->GetBinContent(i+1);
    if ( (i == 90) || (i == 91) ) {
      cout << "Counter[" << i << "] = " << (counters[i]/1000.0) << endl;
    } else {
      cout << "Counter[" << i << "] = " << counters[i] << endl;
    }
  }
}
