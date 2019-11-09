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

//_____________________________________________________________________________
/* - Computes the efficiency of the MC on a
 * - run-by-run basis.
 * -
 */
void fitEfficiencyMC(){

  // TFile* fileList = new TFile("../MyUPC-MonteCarlo/AnalysisResults.root");
  // TFile* fileList = new TFile("AnalysisResultsMC06062019.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-06-16-LHC18qr/kCohJpsiToMu/AnalysisResults.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-10-30/kCohJpsiToMu/AnalysisResults.root");
  // TFile* fileList = new TFile("MCtrainResults/2019-11-09/kCohJpsiToMu/AnalysisResults.root");
  TFile* fileList = new TFile("AnalysisResultsMCcohJPsiALLaods.root");
  // TFile* fileList = new TFile("AnalysisResultsMCcohJPsi09112019.root");
  TDirectory* dir = fileList->GetDirectory("MyTask");
  TList* listings;
  dir->GetObject("MyOutputContainer", listings);
  /* - We now do the same as before to ascertain if the TList was there and
   * - to try to retrieve the plots. Result:
   *   listings->ls()
   *     OBJ: TList	  MyOutputContainer	          Doubly linked list          : 0
   *     OBJ: TH1F	  fNumberMuonsH	              fNumberMuonsH               : 0 at: 0x5a145f0
   *     OBJ: TH1F	  fCounterH	                  fCounterH                   : 0 at: 0x5a3b570
   *     OBJ: TH1F	  fEtaMuonH	                  fEtaMuonH                   : 0 at: 0x5a3ba80
   *     OBJ: TH1F	  fRAbsMuonH	                fRAbsMuonH                  : 0 at: 0x5a3c0c0
   *     OBJ: TH1F	  fInvariantMassDistributionH	fInvariantMassDistributionH : 0 at: 0x5a3c720
   */
  // TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunH");
  // TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fMCEfficiencyPerRunH");
  TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunRestrictedRapidityH");
  TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fMCEfficiencyPerRunRestrictedRapidityH");
  // TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunRestrictedRapidity36to31H");
  // TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fMCEfficiencyPerRunRestrictedRapidity36to31H");
  fEfficiencyPerRunH  ->Sumw2();
  fMCEfficiencyPerRunH->Sumw2();

  TH1F* RealEfficiency = (TH1F*) fEfficiencyPerRunH->Clone("RealEfficiency");
  TH1F* MCEfficiency = (TH1F*) fMCEfficiencyPerRunH->Clone("MCEfficiency");
  // RealEfficiency->Divide(fMCEfficiencyPerRunH);
  // RealEfficiency->Draw("ep");

  Double_t ComputedEfficiency[200];
  Double_t ValueEfficiency[200];
  Double_t ValueEfficiency2[200];
  Double_t Error1[200];
  Double_t Error2[200];
  for ( Int_t i = 0; i < 200; i++ ) ComputedEfficiency[i] = 0;
  for ( Int_t i = 0; i < 200; i++ ) ValueEfficiency[i] = 0;
  for ( Int_t i = 0; i < 200; i++ ) ValueEfficiency2[i] = 0;

  Int_t counter = 0;
  cout << "fEfficiencyPerRunH : " << endl;
  for ( Int_t iLoop = 1; iLoop <= RealEfficiency->GetNbinsX(); iLoop++ ) {
    TString label          = RealEfficiency->GetXaxis()->GetBinLabel(iLoop);
    if ( atoi( label.Data() ) == 266615) continue;
    ValueEfficiency[iLoop] = RealEfficiency->GetBinContent(iLoop);
    if ( ValueEfficiency[iLoop] != 0 ) {
      Error1[iLoop]          = RealEfficiency->GetBinError(iLoop) / ValueEfficiency[iLoop];
    } else {
      Error1[iLoop]          = 0;
    }
    // ValueEfficiency[iLoop] = fEfficiencyPerRunH->GetXaxis()->GetBinContent(iLoop);
    counter++;
    cout << atoi( label.Data() ) << endl;
    for ( Int_t iLoop2 = 1; iLoop2 <= MCEfficiency->GetNbinsX(); iLoop2++ ) {
      TString label2 = MCEfficiency->GetXaxis()->GetBinLabel(iLoop2);
      // if ( atoi(label2.Data()) == atoi(label.Data()) ) {
      if ( atoi( MCEfficiency->GetXaxis()->GetBinLabel(iLoop2) ) == atoi( RealEfficiency->GetXaxis()->GetBinLabel(iLoop) ) ) {
        cout << atoi( MCEfficiency->GetXaxis()->GetBinLabel(iLoop2) ) << endl;
        cout << atoi( RealEfficiency->GetXaxis()->GetBinLabel(iLoop) ) << endl;
        cout << "OK : " << counter << endl;
        // if ( ValueEfficiency != 0 && fMCEfficiencyPerRunH->GetXaxis()->GetBinContent(iLoop2) != 0 ) {
        if ( ValueEfficiency[iLoop] != 0 && MCEfficiency->GetBinContent(iLoop2) != 0 ) {
          // ComputedEfficiency[iLoop] = (Double_t)ValueEfficiency[iLoop]; // / (Double_t)MCEfficiency->GetBinContent(iLoop2);
          ValueEfficiency2[iLoop] = MCEfficiency->GetBinContent(iLoop2);
          Error2[iLoop]           = MCEfficiency->GetBinError(iLoop2) / ValueEfficiency2[iLoop];
          ComputedEfficiency[iLoop] = (Double_t)ValueEfficiency[iLoop] / (Double_t)ValueEfficiency2[iLoop];
          // ComputedEfficiency[iLoop] = ValueEfficiency[iLoop] / fMCEfficiencyPerRunH->GetXaxis()->GetBinContent(iLoop2);
        } else {
          ComputedEfficiency[iLoop] = 0;
        }
      } else {
         continue;
      }
      // cout << label2.Data() << endl;
      // counter++;
    }
  }
  cout << "counter = " << counter << endl;

  for ( Int_t i = 0; i < 200 ; i++ ) {
    cout << "Run " << i << " = " << ComputedEfficiency[i] << endl;
  }

  for ( Int_t i = 0; i < 200 ; i++ ) {
    cout << "Run tr1 " << i << " = " << ValueEfficiency[i] << endl;
    cout << "Run tr2 " << i << " = " << ValueEfficiency2[i] << endl;
  }


  // counter = 0;
  // cout << "fMCEfficiencyPerRunH : " << endl;
  // for ( Int_t iLoop = 1; iLoop <= fMCEfficiencyPerRunH->GetNbinsX(); iLoop++ ) {
  //   TString label = fMCEfficiencyPerRunH->GetXaxis()->GetBinLabel(iLoop);
  //   cout << label.Data() << endl;
  //   // counter++;
  // }
  // cout << "counter = " << counter << endl;
  TCanvas* EffCanvas = new TCanvas("EffCanvas","EffCanvas",900,800);
  TH1F* Eff = new TH1F( "eff" , "eff", 200, -0.5, 199.5 );
  for ( Int_t i = 0; i < 200; i++) {
    Eff->Fill( i, ComputedEfficiency[i] );
    Eff->SetBinError( i+1 , (Error1[i] + Error2[i]) * ComputedEfficiency[i]);
  }
  Eff->Draw("ep");



  TFile f("pngResults/efficiency.root", "recreate");
  // RealEfficiency->Write();
  f.Close();
}
