#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
#include "TStyle.h"
using namespace std;
#include <vector>



//_____________________________________________________________________________
/* - Histograms to be used for the fit.
 * - What happens is that we will interpolate the many points together...
 * -
 */
TH1F* fCohJpsiToMu;
TH1F* fCohPsi2sToMu;
TH1F* fCohPsi2sToMuPi;
TH1F* fIncohJpsiToMu;
TH1F* fIncohPsi2sToMu;
TH1F* fIncohPsi2sToMuPi;
TH1F* fTwoGammaToMuMedium;
TH1F* fTwoGammaToMuHigh;
TH1F* fHighPtTail;
TH1F* fHighPtTailPreliminary;
//_____________________________________________________________________________
/* - Fit function for the Pt plots.
 * - I am using simple ROOT to make gaussian fits to the plot.
 */
Double_t fPtDistr(Double_t* x,Double_t* par)
{
  /* - Par 0, 1, 2:   coherent.
     - Par 3, 4, 5:   incoherent.
     - Par 6      :   gamma+gamma.
     -
   */
  Double_t val = 0;
  val += par[0]* ( fCohJpsiToMu       ->Interpolate(x[0]) );   //needed
  // val += par[1]* ( fCohPsi2sToMu      ->Interpolate(x[0]) );
  // val += par[0]* ( fCohPsi2sToMuPi    ->Interpolate(x[0]) ) * par[4];   //needed
  val += par[1]* ( fIncohJpsiToMu     ->Interpolate(x[0]) );   //needed
  // val += par[4]* ( fIncohPsi2sToMu    ->Interpolate(x[0]) );
  val += par[1]* ( fIncohPsi2sToMuPi  ->Interpolate(x[0]) ) * par[4];   //needed
  val += par[2]* ( fTwoGammaToMuMedium->Interpolate(x[0]) );   //needed
  // val += par[2]* ( fTwoGammaToMuHigh  ->Interpolate(x[0]) );   //needed
  val += par[3]* ( fHighPtTail        ->Interpolate(x[0]) );   //needed

  return val;
}
//_____________________________________________________________________________
/* - Fit function for the Pt plots.
 * - I am using simple ROOT to make gaussian fits to the plot.
 */
Double_t fPtDistrPreliminary(Double_t* x,Double_t* par)
{
  Double_t val = 0;
  val += par[0]* ( fHighPtTailPreliminary->Interpolate(x[0]) );   //needed
  return val;
}
//_____________________________________________________________________________
/* - Fit function for the ZNC plots.
 * -
 */
void fitPtDistr(const char* AnalysisName, const int selectionFlag){
  TFile* fileList = new TFile(AnalysisName);
  TDirectory* dir = fileList->GetDirectory("MyTask");
  TFile* fileMC[8];
  fileMC[0] = new TFile("MCtrainResults/2019-11-09/kCohJpsiToMu/AnalysisResults.root");
  // fileMC[1] = new TFile("MCtrainResults/2019-11-09/kCohPsi2sToMu/AnalysisResults.root");
  // fileMC[2] = new TFile("MCtrainResults/2019-11-09/kCohPsi2sToMuPi/AnalysisResults.root");
  // fileMC[3] = new TFile("MCtrainResults/2019-06-24/kIncohJpsiToMu/AnalysisResults.root");
  fileMC[3] = new TFile("AnalysisResultsLHC16s_propertrigger.root");
  fileMC[4] = new TFile("MCtrainResults/2019-11-09/kIncohPsi2sToMu/AnalysisResults.root");
  fileMC[5] = new TFile("MCtrainResults/2019-11-09/kIncohPsi2sToMuPi/AnalysisResults.root");
  fileMC[6] = new TFile("MCtrainResults/2019-11-09/kTwoGammaToMuMedium/AnalysisResults.root");
  fileMC[7] = new TFile("MCtrainResults/2019-11-09/kTwoGammaToMuLow/AnalysisResults.root");
  TDirectory* dirMC[8];
  for(Int_t iDirectory = 0; iDirectory < 8; iDirectory++) {
    if (iDirectory == 1 || iDirectory == 2) continue;
    dirMC[iDirectory] = fileMC[iDirectory]->GetDirectory("MyTask");
  }
  /* - At this level you could check if everything was okay.
   * - We do a dir->ls() to find out! We get:
   *   dir->ls();
   *   TDirectoryFile*		MyTask	MyTask
   *   KEY: TList	MyOutputContainer;1	Doubly linked list
   */
  TList* listings;
  dir->GetObject("MyOutputContainer", listings);
  TList* listingsMC[8];
  for(Int_t iDirectory = 0; iDirectory < 8; iDirectory++) {
    if (iDirectory == 1 || iDirectory == 2) continue;
    dirMC[iDirectory]->GetObject("MyOutputContainer", listingsMC[iDirectory]);
  }
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
  // fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fDimuonPtDistributionH");
  // fCohPsi2sToMu       = (TH1F*)listingsMC[1]->FindObject("fDimuonPtDistributionH");
  // fCohPsi2sToMuPi     = (TH1F*)listingsMC[2]->FindObject("fDimuonPtDistributionH");
  // fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fDimuonPtDistributionH");
  // fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fDimuonPtDistributionH");
  // fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fDimuonPtDistributionH");
  // fTwoGammaToMuMedium = (TH1F*)listingsMC[6]->FindObject("fDimuonPtDistributionH");
  // fTwoGammaToMuHigh   = (TH1F*)listingsMC[7]->FindObject("fDimuonPtDistributionH");
  fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fTemplatePtDistributionH");
  // fCohPsi2sToMu       = (TH1F*)listingsMC[1]->FindObject("fTemplatePtDistributionH");
  // fCohPsi2sToMuPi     = (TH1F*)listingsMC[2]->FindObject("fTemplatePtDistributionH");
  fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fTemplatePtDistributionH");
  fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fTemplatePtDistributionH");
  fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fTemplatePtDistributionH");
  fTwoGammaToMuMedium = (TH1F*)listingsMC[6]->FindObject("fTemplatePtDistributionH");
  fTwoGammaToMuHigh   = (TH1F*)listingsMC[7]->FindObject("fTemplatePtDistributionH");

  /* - Rebin
     -
   */
  // fCohJpsiToMu        -> Rebin(4);
  // fCohPsi2sToMu       -> Rebin(4);
  // fCohPsi2sToMuPi     -> Rebin(4);
  // fIncohJpsiToMu      -> Rebin(4);
  // fIncohPsi2sToMu     -> Rebin(4);
  // fIncohPsi2sToMuPi   -> Rebin(4);
  // fTwoGammaToMuMedium -> Rebin(4);
  // fTwoGammaToMuHigh   -> Rebin(4);
  fCohJpsiToMu        -> Rebin(5);  // -> 25 MeV bins
  // fCohPsi2sToMu       -> Rebin(5);
  // fCohPsi2sToMuPi     -> Rebin(5);
  fIncohJpsiToMu      -> Rebin(5);
  fIncohPsi2sToMu     -> Rebin(5);
  fIncohPsi2sToMuPi   -> Rebin(5);
  fTwoGammaToMuMedium -> Rebin(5);
  fTwoGammaToMuHigh   -> Rebin(5);



  fCohJpsiToMu        -> Rebin(2);  // -> 25 MeV bins
  // fCohPsi2sToMu       -> Rebin(2);
  // fCohPsi2sToMuPi     -> Rebin(2);
  fIncohJpsiToMu      -> Rebin(2);
  fIncohPsi2sToMu     -> Rebin(2);
  fIncohPsi2sToMuPi   -> Rebin(2);
  fTwoGammaToMuMedium -> Rebin(2);
  fTwoGammaToMuHigh   -> Rebin(2);



  fCohJpsiToMu        -> Rebin(2);  // -> 25 MeV bins
  // fCohPsi2sToMu       -> Rebin(2);
  // fCohPsi2sToMuPi     -> Rebin(2);
  fIncohJpsiToMu      -> Rebin(2);
  fIncohPsi2sToMu     -> Rebin(2);
  fIncohPsi2sToMuPi   -> Rebin(2);
  fTwoGammaToMuMedium -> Rebin(2);
  fTwoGammaToMuHigh   -> Rebin(2);


  /* - Firstly we normalize the histograms.
     - Remember to always Sumw2()!!
     -
   */
  fCohJpsiToMu        -> Sumw2();
  // fCohPsi2sToMu       -> Sumw2();
  // fCohPsi2sToMuPi     -> Sumw2();
  fIncohJpsiToMu      -> Sumw2();
  fIncohPsi2sToMu     -> Sumw2();
  fIncohPsi2sToMuPi   -> Sumw2();
  fTwoGammaToMuMedium -> Sumw2();
  fTwoGammaToMuHigh   -> Sumw2();
  // Double_t Integral_fCohJpsiToMu        = fCohJpsiToMu        -> Integral(0, 20);
  // Double_t Integral_fCohPsi2sToMu       = fCohPsi2sToMu       -> Integral(0, 20);
  // Double_t Integral_fCohPsi2sToMuPi     = fCohPsi2sToMuPi     -> Integral(0, 20);
  // Double_t Integral_fIncohJpsiToMu      = fIncohJpsiToMu      -> Integral(0, 20);
  // Double_t Integral_fIncohPsi2sToMu     = fIncohPsi2sToMu     -> Integral(0, 20);
  // Double_t Integral_fIncohPsi2sToMuPi   = fIncohPsi2sToMuPi   -> Integral(0, 20);
  // Double_t Integral_fTwoGammaToMuMedium = fTwoGammaToMuMedium -> Integral(0, 20);
  // Double_t Integral_fTwoGammaToMuHigh   = fTwoGammaToMuHigh   -> Integral(0, 20);
  Double_t Integral_fCohJpsiToMu        = fCohJpsiToMu        -> Integral();
  // Double_t Integral_fCohPsi2sToMu       = fCohPsi2sToMu       -> Integral();
  // Double_t Integral_fCohPsi2sToMuPi     = fCohPsi2sToMuPi     -> Integral();
  Double_t Integral_fIncohJpsiToMu      = fIncohJpsiToMu      -> Integral();
  Double_t Integral_fIncohPsi2sToMu     = fIncohPsi2sToMu     -> Integral();
  Double_t Integral_fIncohPsi2sToMuPi   = fIncohPsi2sToMuPi   -> Integral();
  Double_t Integral_fTwoGammaToMuMedium = fTwoGammaToMuMedium -> Integral();
  Double_t Integral_fTwoGammaToMuHigh   = fTwoGammaToMuHigh   -> Integral();
  fCohJpsiToMu        -> Scale( 1/Integral_fCohJpsiToMu        );
  // fCohPsi2sToMu       -> Scale( 1/Integral_fCohPsi2sToMu       );
  // fCohPsi2sToMuPi     -> Scale( 1/Integral_fCohPsi2sToMuPi     );
  fIncohJpsiToMu      -> Scale( 1/Integral_fIncohJpsiToMu      );
  fIncohPsi2sToMu     -> Scale( 1/Integral_fIncohPsi2sToMu     );
  fIncohPsi2sToMuPi   -> Scale( 1/Integral_fIncohPsi2sToMuPi   );
  fTwoGammaToMuMedium -> Scale( 1/Integral_fTwoGammaToMuMedium );
  fTwoGammaToMuHigh   -> Scale( 1/Integral_fTwoGammaToMuHigh   );

  /* - High Pt-tail, with HERA's data.
     -
   */
  TF1* fModelForHighPtTail = new TF1("fModelForHighPtTail","[0]*x*(1+[1]/[2]*x*x)^(-[2])",0,4);
  fModelForHighPtTail->SetParameter(0,1);
//  fModelForHighPtTail->SetParameter(1,debug==4 ? 1.25 : 1.);
//  fModelForHighPtTail->SetParameter(2,debug==4 ? 6.1 : 1.);
  fModelForHighPtTail->SetParameter(1, 1.6/*1.79*/);
  fModelForHighPtTail->SetParameter(2, 3.58);
  // fModelForHighPtTail->SetNpx( 4.0/0.05 );
  fModelForHighPtTail->SetNpx( 4.0/0.1 );
  fHighPtTail = (TH1F*) fModelForHighPtTail->GetHistogram()->Clone("fHighPtTail");
  for (Int_t ibin=1; ibin<=fHighPtTail->GetNbinsX(); ibin++) {
    fHighPtTail->SetBinError(ibin,0);
  }



  TH1F *fDimuonPtDistributionDataH = 0x0;
  if      ( selectionFlag == 0 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionH");
  // else if ( selectionFlag == 1 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCzeroZNAzeroH");
  // else if ( selectionFlag == 2 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCzeroZNAanyH");
  // else if ( selectionFlag == 3 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCanyZNAzeroH");
  // else if ( selectionFlag == 4 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCanyZNAanyH");
  else if ( selectionFlag == 1 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNAH");
  else if ( selectionFlag == 2 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNAbinsH_0");
  else if ( selectionFlag == 3 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNAbinsH_1");
  else if ( selectionFlag == 4 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCH");
  else if ( selectionFlag == 5 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCbinsH_0");
  else if ( selectionFlag == 6 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCbinsH_1");
  // Run 2 settings
  else if ( selectionFlag == 7 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCH");
  else if ( selectionFlag == 8 ) {
    fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_0");
    fDimuonPtDistributionDataH->Add( (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_1") );
  }
  else if ( selectionFlag == 9 ) {
    fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_2");
    fDimuonPtDistributionDataH->Add( (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_3") );
  }
  else if ( selectionFlag == 10) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCthreebinsH_0");
  else if ( selectionFlag == 11) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCthreebinsH_1");
  else if ( selectionFlag == 12) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCthreebinsH_2");
  else if ( selectionFlag == 13) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_0");
  else if ( selectionFlag == 14) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_1");
  else if ( selectionFlag == 15) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_2");
  else if ( selectionFlag == 16) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_3");
  else if ( selectionFlag == 17) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_0");
  else if ( selectionFlag == 18) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_1");
  else if ( selectionFlag == 19) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_2");
  else if ( selectionFlag == 20) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_3");
  else if ( selectionFlag == 21) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_4");
  else                           fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionH");
  fDimuonPtDistributionDataH->Rebin(5);
  fDimuonPtDistributionDataH->Rebin(2);
  fDimuonPtDistributionDataH->Rebin(2);
  fDimuonPtDistributionDataH->Draw("PE");


  /* - Preliminary fit to the unknown contribution.
   * -
   */
  TF1* fModelForHighPtTailPreliminary = new TF1("fModelForHighPtTailPreliminary","[0]*x*(1+[1]/[2]*x*x)^(-[2])",0.5,5.);
  fModelForHighPtTailPreliminary->SetParameter(0,1);
  // fModelForHighPtTailPreliminary->SetParameter(1,debug==4 ? 1.25 : 1.);
  // fModelForHighPtTailPreliminary->SetParameter(2,debug==4 ? 6.1 : 1.);
  fModelForHighPtTailPreliminary->SetParameter(1, 1.6/*1.79*/);
  fModelForHighPtTailPreliminary->SetParameter(2, 3.58);
  fModelForHighPtTailPreliminary->SetNpx( fCohJpsiToMu->GetNbinsX() );
  fHighPtTailPreliminary = (TH1F*) fModelForHighPtTailPreliminary->GetHistogram()->Clone("fHighPtTailPreliminary");
  for (Int_t ibin=1; ibin<=fHighPtTailPreliminary->GetNbinsX(); ibin++) {
    fHighPtTailPreliminary->SetBinError(ibin,0);
  }
  TCanvas* UtilityCanvas = new TCanvas("UtilityCanvas", "UtilityCanvas", 800, 900);
  TH1F* fDimuonPtDistributionDataCloneH = (TH1F*) fDimuonPtDistributionDataH->Clone("fDimuonPtDistributionDataCloneH");
  TF1* FitPtDistrPreliminary = new TF1(  "FitPtDistrPreliminary",
                                         fPtDistrPreliminary,
                                         1.25, 2.5,
                                         /*7*/1
                                         );
  FitPtDistrPreliminary->SetNpx(1000);
  fDimuonPtDistributionDataCloneH->Fit(FitPtDistrPreliminary, "","", 1.25, 2.5);
  gStyle->SetOptFit(100);
  // UtilityCanvas->SaveAs("UtilityCanvas.png");


  new TCanvas;
  TF1* FitPtDistr = new TF1(  "FitPtDistr",
                              fPtDistr,
                              0, 3,
                              /*7*/5
                              );
  FitPtDistr->SetNpx(1000);




  Double_t kFeedDownCoherent = 0.1;     // neutral element
  Double_t kError            = 0.01;
  FitPtDistr->SetParameter(4, kFeedDownCoherent);
  FitPtDistr->SetParLimits(4, FitPtDistr->GetParameter(4)*(1-kError), FitPtDistr->GetParameter(4)*(1+kError));

  // FEED-DOWN COHERENT
  // Double_t kFeedDownIncoherent = 1705;     // neutral element
  // Double_t kErrorInc           = 0.175;
  // FitPtDistr->SetParameter(5, kFeedDownIncoherent);
  // FitPtDistr->SetParLimits(5, FitPtDistr->GetParameter(5)*(1-kErrorInc), FitPtDistr->GetParameter(5)*(1+kErrorInc));

  // Gamma+Gamma Medium
  FitPtDistr->SetParameter(2, 4800);
  FitPtDistr->SetParameter(2, 6531);
  // WITH ZDC
  // if        ( selectionFlag == 0 ) {
  //   FitPtDistr->SetParameter(1, 700);
  //   FitPtDistr->SetParameter(2, 40);
  // } else if ( selectionFlag == 1 ) {
  //   FitPtDistr->SetParameter(1, 550);
  //   FitPtDistr->SetParameter(2, 40);
  // } else if ( selectionFlag == 2 ) {
  //   FitPtDistr->SetParameter(1, 260);
  //   FitPtDistr->SetParameter(2, 15);
  // } else if ( selectionFlag == 3 ) {
  //   FitPtDistr->SetParameter(1, 290);
  //   FitPtDistr->SetParameter(2, 22);
  // } else if ( selectionFlag == 4 ) {
  //   FitPtDistr->SetParameter(1, 635);
  //   FitPtDistr->SetParameter(2, 40);
  // } else if ( selectionFlag == 5 ) {
  //   FitPtDistr->SetParameter(1, 290);
  //   FitPtDistr->SetParameter(2, 15);
  // } else if ( selectionFlag == 6 ) {
  //   FitPtDistr->SetParameter(1, 350);
  //   FitPtDistr->SetParameter(2, 25);
  // } else if ( selectionFlag == 7 ) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 820);
  //   FitPtDistr->FixParameter(2, 56);
  // } else if ( selectionFlag == 8 ) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 310);
  //   FitPtDistr->FixParameter(2, 24);
  // } else if ( selectionFlag == 9 ) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 510);
  //   FitPtDistr->FixParameter(2, 33);
  // } else if ( selectionFlag == 10) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 90);
  //   FitPtDistr->FixParameter(2, 12);
  // } else if ( selectionFlag == 11) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 480);
  //   FitPtDistr->FixParameter(2, 28);
  // } else if ( selectionFlag == 12) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 250);
  //   FitPtDistr->FixParameter(2, 18);
  // } else if ( selectionFlag == 13) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 40);
  //   FitPtDistr->FixParameter(2, 6);
  // } else if ( selectionFlag == 14) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 266);
  //   FitPtDistr->FixParameter(2, 17);
  // } else if ( selectionFlag == 15) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 370);
  //   FitPtDistr->FixParameter(2, 21);
  // } else if ( selectionFlag == 16) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 141);
  //   FitPtDistr->FixParameter(2, 14);
  // } else if ( selectionFlag == 17) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 21);
  //   FitPtDistr->FixParameter(2, 3);
  // } else if ( selectionFlag == 18) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 129);
  //   FitPtDistr->FixParameter(2, 14);
  // } else if ( selectionFlag == 19) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 317);
  //   FitPtDistr->FixParameter(2, 17);
  // } else if ( selectionFlag == 20) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 273);
  //   FitPtDistr->FixParameter(2, 14);
  // } else if ( selectionFlag == 21) { // Run 2 settings
  //   FitPtDistr->SetParameter(1, 80);
  //   FitPtDistr->FixParameter(2, 11);
  // }




  // WITHOUT ZDC
  if        ( selectionFlag == 0 ) {
    FitPtDistr->SetParameter(1, 700);
    FitPtDistr->SetParameter(2, 40);
  } else if ( selectionFlag == 1 ) {
    FitPtDistr->SetParameter(1, 550);
    FitPtDistr->SetParameter(2, 40);
  } else if ( selectionFlag == 2 ) {
    FitPtDistr->SetParameter(1, 260);
    FitPtDistr->SetParameter(2, 15);
  } else if ( selectionFlag == 3 ) {
    FitPtDistr->SetParameter(1, 290);
    FitPtDistr->SetParameter(2, 22);
  } else if ( selectionFlag == 4 ) {
    FitPtDistr->SetParameter(1, 635);
    FitPtDistr->SetParameter(2, 40);
  } else if ( selectionFlag == 5 ) {
    FitPtDistr->SetParameter(1, 290);
    FitPtDistr->SetParameter(2, 15);
  } else if ( selectionFlag == 6 ) {
    FitPtDistr->SetParameter(1, 350);
    FitPtDistr->SetParameter(2, 25);
  } else if ( selectionFlag == 7 ) { // Run 2 settings
    FitPtDistr->SetParameter(1, 820);
    FitPtDistr->FixParameter(2, 56);
  } else if ( selectionFlag == 8 ) { // Run 2 settings
    FitPtDistr->SetParameter(1, 325);
    FitPtDistr->FixParameter(2, 25);
  } else if ( selectionFlag == 9 ) { // Run 2 settings
    FitPtDistr->SetParameter(1, 550);
    FitPtDistr->FixParameter(2, 34);
  } else if ( selectionFlag == 10) { // Run 2 settings
    FitPtDistr->SetParameter(1, 100);
    FitPtDistr->FixParameter(2, 12);
  } else if ( selectionFlag == 11) { // Run 2 settings
    FitPtDistr->SetParameter(1, 512);
    FitPtDistr->FixParameter(2, 29);
  } else if ( selectionFlag == 12) { // Run 2 settings
    FitPtDistr->SetParameter(1, 265);
    FitPtDistr->FixParameter(2, 19);
  } else if ( selectionFlag == 13) { // Run 2 settings
    FitPtDistr->SetParameter(1, 45);
    FitPtDistr->FixParameter(2, 6);
  } else if ( selectionFlag == 14) { // Run 2 settings
    FitPtDistr->SetParameter(1, 281);
    FitPtDistr->FixParameter(2, 19);
  } else if ( selectionFlag == 15) { // Run 2 settings
    FitPtDistr->SetParameter(1, 402);
    FitPtDistr->FixParameter(2, 21);
  } else if ( selectionFlag == 16) { // Run 2 settings
    FitPtDistr->SetParameter(1, 147);
    FitPtDistr->FixParameter(2, 14);
  } else if ( selectionFlag == 17) { // Run 2 settings
    FitPtDistr->SetParameter(1, 25);
    FitPtDistr->FixParameter(2, 3);
  } else if ( selectionFlag == 18) { // Run 2 settings
    FitPtDistr->SetParameter(1, 139);
    FitPtDistr->FixParameter(2, 14);
  } else if ( selectionFlag == 19) { // Run 2 settings
    FitPtDistr->SetParameter(1, 336);
    FitPtDistr->FixParameter(2, 17);
  } else if ( selectionFlag == 20) { // Run 2 settings
    FitPtDistr->SetParameter(1, 292);
    FitPtDistr->FixParameter(2, 15);
  } else if ( selectionFlag == 21) { // Run 2 settings
    FitPtDistr->SetParameter(1, 84);
    FitPtDistr->FixParameter(2, 11);
  }



  // FitPtDistr->SetParLimits(2, FitPtDistr->GetParameter(2)*0.95, FitPtDistr->GetParameter(2)*1.05);
  // FitPtDistr->SetParLimits(2, FitPtDistr->GetParameter(2)*0.8, FitPtDistr->GetParameter(2)*1.0);
  FitPtDistr->SetParLimits(0, 0.0, 100.0);
  if ( selectionFlag == 16) {
    FitPtDistr->SetParLimits(1, FitPtDistr->GetParameter(1)*0.8, FitPtDistr->GetParameter(1)*1.0);
  } else {
    FitPtDistr->SetParLimits(1, FitPtDistr->GetParameter(1)*0.85, FitPtDistr->GetParameter(1)*1.0);
  }

  // FitPtDistr->SetParameter(3, FitPtDistrPreliminary->GetParameter(0));
  // FitPtDistr->SetParLimits(3, FitPtDistrPreliminary->GetParameter(0)*0.9, FitPtDistrPreliminary->GetParameter(0)*1.1);
  // FitPtDistr->SetParLimits(7, 740, 745);

  fDimuonPtDistributionDataH->SetLineColor(kBlue);
  fDimuonPtDistributionDataH->SetLineStyle(kSolid);
  fDimuonPtDistributionDataH->SetLineWidth(3);
  fDimuonPtDistributionDataH->SetMarkerStyle(kFullCircle);
  fDimuonPtDistributionDataH->SetMarkerColor(kBlue);
  fDimuonPtDistributionDataH->SetMarkerSize(1);
  fDimuonPtDistributionDataH->GetXaxis()->SetTitle("p_{T} [GeV/#it{c}]");
  fDimuonPtDistributionDataH->GetYaxis()->SetTitle( Form( "Counts / (%.3f GeV/#it{c})",
                                                          fDimuonPtDistributionDataH->GetXaxis()->GetBinWidth(1)
                                                        )
                                                    );
  fDimuonPtDistributionDataH->SetTitle("");
  fDimuonPtDistributionDataH->Fit( FitPtDistr,"","", 0./*1.2*/, 3. );
  TCanvas* PtDistrCanvas = new TCanvas( "PtDistrCanvas", "PtDistrCanvas", 900, 800 );
  gPad->SetMargin(0.13,0.01,0.12,0.01);
  // gPad->SetLogy();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  /* - Beautifying is starting now.
     -
   */
  fDimuonPtDistributionDataH->GetXaxis()->SetTitleOffset(1.25);
  // fDimuonPtDistributionDataH->GetYaxis()->SetTitleOffset(1.25);
  fDimuonPtDistributionDataH->GetYaxis()->SetTitleOffset(1.45);
  fDimuonPtDistributionDataH->GetXaxis()->SetTitleSize(0.045);
  fDimuonPtDistributionDataH->GetYaxis()->SetTitleSize(0.045);
  fDimuonPtDistributionDataH->GetXaxis()->SetLabelSize(0.045);
  fDimuonPtDistributionDataH->GetYaxis()->SetLabelSize(0.045);
  fDimuonPtDistributionDataH->GetXaxis()->SetTitleFont(42);
  fDimuonPtDistributionDataH->GetYaxis()->SetTitleFont(42);
  fDimuonPtDistributionDataH->GetXaxis()->SetLabelFont(42);
  fDimuonPtDistributionDataH->GetYaxis()->SetLabelFont(42);
  // fDimuonPtDistributionDataH->GetXaxis()->SetNdivisions(408);
  // fDimuonPtDistributionDataH->GetYaxis()->SetRangeUser(10, fDimuonPtDistributionDataH->GetMaximum()*10.);
  fDimuonPtDistributionDataH->GetYaxis()->SetRangeUser(fDimuonPtDistributionDataH->GetMaximum()*0.0001, fDimuonPtDistributionDataH->GetMaximum()*1.5);
  // fDimuonPtDistributionDataH->GetXaxis()->SetRangeUser(0, 5.5);
  fDimuonPtDistributionDataH->GetXaxis()->SetRangeUser(0, 3);
  // gPad ->SetLogy();
  fDimuonPtDistributionDataH->Draw("PEsame");
  fCohJpsiToMu        -> SetLineColor(kRed);
  // fCohPsi2sToMu       -> SetLineColor(kMagenta);
  // fCohPsi2sToMuPi     -> SetLineColor(kYellow+1);
  fIncohJpsiToMu      -> SetLineColor(kCyan);
  fIncohPsi2sToMu     -> SetLineColor(kYellow);
  fIncohPsi2sToMuPi   -> SetLineColor(kBlue+2);
  fTwoGammaToMuMedium -> SetLineColor(kGreen);
  fTwoGammaToMuHigh   -> SetLineColor(kBlue+3);
  fHighPtTail         -> SetLineColor(kGreen+1);
  fCohJpsiToMu        -> SetLineWidth(3);
  // fCohPsi2sToMu       -> SetLineWidth(3);
  // fCohPsi2sToMuPi     -> SetLineWidth(3);
  fIncohJpsiToMu      -> SetLineWidth(3);
  fIncohPsi2sToMu     -> SetLineWidth(3);
  fIncohPsi2sToMuPi   -> SetLineWidth(3);
  fTwoGammaToMuMedium -> SetLineWidth(3);
  fTwoGammaToMuHigh   -> SetLineWidth(3);
  fHighPtTail         -> SetLineWidth(3);
  TH1F* fCohJpsiToMuC        = (TH1F*) fCohJpsiToMu        -> Clone("fCohJpsiToMuC");
  // TH1F* fCohPsi2sToMuC       = (TH1F*) fCohPsi2sToMu       -> Clone("fCohPsi2sToMuC");
  // TH1F* fCohPsi2sToMuPiC     = (TH1F*) fCohPsi2sToMuPi     -> Clone("fCohPsi2sToMuPiC");
  TH1F* fIncohJpsiToMuC      = (TH1F*) fIncohJpsiToMu      -> Clone("fIncohJpsiToMuC");
  TH1F* fIncohPsi2sToMuC     = (TH1F*) fIncohPsi2sToMu     -> Clone("fIncohPsi2sToMuC");
  TH1F* fIncohPsi2sToMuPiC   = (TH1F*) fIncohPsi2sToMuPi   -> Clone("fIncohPsi2sToMuPiC");
  TH1F* fTwoGammaToMuMediumC = (TH1F*) fTwoGammaToMuMedium -> Clone("fTwoGammaToMuMediumC");
  TH1F* fTwoGammaToMuHighC   = (TH1F*) fTwoGammaToMuHigh   -> Clone("fTwoGammaToMuHighC");
  TH1F* fHighPtTailC         = (TH1F*) fHighPtTail         -> Clone("fHighPtTailC");
  fCohJpsiToMuC        -> Scale( FitPtDistr->GetParameter(0) );
  // fCohPsi2sToMuC       -> Scale( FitPtDistr->GetParameter(0) * FitPtDistr->GetParameter(4) );
  // fCohPsi2sToMuPiC     -> Scale( FitPtDistr->GetParameter(0) * FitPtDistr->GetParameter(4) );
  fIncohJpsiToMuC      -> Scale( FitPtDistr->GetParameter(1) );
  fIncohPsi2sToMuC     -> Scale( FitPtDistr->GetParameter(1) * FitPtDistr->GetParameter(4) );
  fIncohPsi2sToMuPiC   -> Scale( FitPtDistr->GetParameter(1) * FitPtDistr->GetParameter(4) );
  fTwoGammaToMuMediumC -> Scale( FitPtDistr->GetParameter(2) );
  fTwoGammaToMuHighC   -> Scale( FitPtDistr->GetParameter(2) );
  fHighPtTailC         -> Scale( FitPtDistr->GetParameter(3) );
  fCohJpsiToMuC        -> Draw("HISTsame");
  // fCohPsi2sToMuC       -> Draw("same");
  // fCohPsi2sToMuPiC     -> Draw("same");
  fIncohJpsiToMuC      -> Draw("HISTsame");
  // fIncohPsi2sToMuC     -> Draw("same");
  fIncohPsi2sToMuPiC   -> Draw("HISTsame");
  fTwoGammaToMuMediumC -> Draw("HISTsame");
  // fTwoGammaToMuHighC   -> Draw("same");
  fHighPtTailC         -> Draw("Esame");
  // fCohJpsiToMu        -> Scale( FitPtDistr->GetParameter(0) );
  // fCohPsi2sToMu       -> Scale( FitPtDistr->GetParameter(1) );
  // fCohPsi2sToMuPi     -> Scale( FitPtDistr->GetParameter(2) );
  // fIncohJpsiToMu      -> Scale( FitPtDistr->GetParameter(3) );
  // fIncohPsi2sToMu     -> Scale( FitPtDistr->GetParameter(4) );
  // fIncohPsi2sToMuPi   -> Scale( FitPtDistr->GetParameter(5) );
  // fTwoGammaToMuMedium -> Scale( FitPtDistr->GetParameter(6) );
  // fTwoGammaToMuHigh   -> Scale( FitPtDistr->GetParameter(0) );
  // fCohJpsiToMu        -> Draw("same");
  // fCohPsi2sToMu       -> Draw("same");
  // fCohPsi2sToMuPi     -> Draw("same");
  // fIncohJpsiToMu      -> Draw("same");
  // fIncohPsi2sToMu     -> Draw("same");
  // fIncohPsi2sToMuPi   -> Draw("same");
  // fTwoGammaToMuMedium -> Draw("same");
  // fTwoGammaToMuHigh   -> Draw("same");







  Double_t err1c = 0;
  Double_t err1i = 0;
  Double_t errun = 0;
  Double_t errfI = 0;
  Double_t int1c = fCohJpsiToMuC  ->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.999999), err1c, "" );
  Double_t int1i = fIncohJpsiToMuC->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.999999), err1i, "" );
  Double_t intun = fHighPtTailC   ->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.999999), errun, "" );
  Double_t f_I   = (int1c + intun ) / int1i;

  // err1c *= (int1c * (FitPtDistr->GetParError(0)));
  // err1i *= (int1i * (FitPtDistr->GetParError(1)));
  // errun *= (intun * (FitPtDistr->GetParError(3)));
  err1c += int1c * (FitPtDistr->GetParError(0) / FitPtDistr->GetParameter(0));
  err1i += int1i * (FitPtDistr->GetParError(1) / FitPtDistr->GetParameter(1));
  errun += intun * (FitPtDistr->GetParError(3) / FitPtDistr->GetParameter(3));

  if ( int1c < 0.0001 ) err1c = 0;

  // errfI          = err1c + err1i + errun;
  Double_t RatioErrfIOverfI        = 0;
  Double_t RatioErr1cOver1c        = 0;
  Double_t RatioErrIncohOverIncoh  = 0;
  RatioErr1cOver1c                 = err1i / int1i;
  RatioErrIncohOverIncoh           = ( err1c + errun ) / ( int1c + intun );
  RatioErrfIOverfI                 = RatioErrIncohOverIncoh + RatioErr1cOver1c;
  errfI                            = RatioErrfIOverfI * f_I;
  // errfI          = (RatioErrfIOverfI + (FitPtDistr->GetParError(0) / FitPtDistr->GetParameter(0)) + (FitPtDistr->GetParError(1) / FitPtDistr->GetParameter(1)) + (FitPtDistr->GetParError(3) / FitPtDistr->GetParameter(3))) * f_I;
  cout << "err1c = " << err1c;
  cout << "err1i = " << err1i;
  cout << "errun = " << errun;
  cout << "errfI = " << errfI;



  TLatex* latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(42);
  latex->SetTextAlign(11);
  latex->SetNDC();
  latex->DrawLatex(0.17,0.94,"ALICE Performance, Pb-p #sqrt{s_{NN}} = 8.16 TeV");
  latex->DrawLatex(0.17,0.86,Form("f_{c} = #frac{%.3f + %.3f}{%.3f} = %.3f #pm %.3f", int1c, intun, int1i, f_I, errfI));
  latex->SetTextSize(0.045);
  // latex->DrawLatex(0.55,0.84,"UPC, #it{L} = 235 ub^{-1}");
  // latex->DrawLatex(0.55,0.84,"UPC, LHC18q+LHC18r data");
  // latex->DrawLatex(0.55,0.78,"#it{p}_{T}-integrated");
  if ( selectionFlag == 7 ) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-4.000,  -2.500));
  if ( selectionFlag == 8 ) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-4.000,  -3.250));
  if ( selectionFlag == 9 ) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.250,  -2.500));
  if ( selectionFlag == 10) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-4.000,  -3.500));
  if ( selectionFlag == 11) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.500,  -3.000));
  if ( selectionFlag == 12) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.000,  -2.500));
  if ( selectionFlag == 13) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-4.000,  -3.625));
  if ( selectionFlag == 14) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.625,  -3.250));
  if ( selectionFlag == 15) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.250,  -2.875));
  if ( selectionFlag == 16) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-2.875,  -2.500));
  if ( selectionFlag == 17) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-4.000,  -3.700));
  if ( selectionFlag == 18) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.700,  -3.400));
  if ( selectionFlag == 19) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.400,  -3.100));
  if ( selectionFlag == 20) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-3.100,  -2.800));
  if ( selectionFlag == 21) latex->DrawLatex(0.55,0.72,Form("%.3f < y < %.3f",-2.800,  -2.500));

  // latex->DrawLatex(0.55,0.78,Form("%.1f < y < %.1f",-4.0,-2.5));
  /* - Chi square computation.
     -
   */
  // latex->DrawLatex(0.55,0.68,Form( "  #tilde{#chi}^{2} = %.2f / %.2d = %.2f  ",
  //                                  FitPtDistr->GetChisquare(),
  //                                  FitPtDistr->GetNDF(),
  //                                  FitPtDistr->GetChisquare()/FitPtDistr->GetNDF()
  //                                 )
  //                                );

  TLegend* l = new TLegend(0.45,0.55,0.98,0.85);
  l->SetMargin(0.1);
  l->SetBorderSize(0);
  l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018");
  if      ( selectionFlag == 0 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018");
  else if ( selectionFlag == 1 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 0N0N");
  else if ( selectionFlag == 2 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 0NXN");
  else if ( selectionFlag == 3 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 XN0N");
  else if ( selectionFlag == 4 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 XNXN");
  else                           l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018");
  l->AddEntry(  FitPtDistr, Form( "Fit: #chi^{2}/NDF = %.2f / %.2d = %.2f  ",
                                   FitPtDistr->GetChisquare(),
                                   FitPtDistr->GetNDF(),
                                   FitPtDistr->GetChisquare()/FitPtDistr->GetNDF()
                                   )
                                  );
  l->AddEntry(  fCohJpsiToMuC,        "Coherent   J/#psi");
  l->AddEntry(  fIncohJpsiToMuC,      "Incoherent J/#psi");
  l->AddEntry(  fHighPtTailC,         "Incoherent dissociative J/#psi");
  // l->AddEntry(  fCohPsi2sToMuPiC,     "Coherent   #psi(2S) feeddown");
  l->AddEntry(  fIncohPsi2sToMuPiC,   "Incoherent #psi(2S) feeddown");
  l->AddEntry(  fTwoGammaToMuMediumC, "Continuum  #gamma#gamma #rightarrow #mu#mu");
  l->Draw();

  gPad->SaveAs("pngResults/fitPtDistr.png", "RECREATE");
  gPad->SaveAs(Form("pngResults/fitPtDistr_%d.png", selectionFlag),  "RECREATE");


}
