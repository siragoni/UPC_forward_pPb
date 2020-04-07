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
TH1F* fTwoGammaToMuLow;
TH1F* fTwoGammaToMuMedium;
TH1F* fHighPtTail;
TH1F* fHighPtTailPreliminary;

TH1F* fCohJpsiToMuOrig;
TH1F* fCohPsi2sToMuOrig;
TH1F* fCohPsi2sToMuPiOrig;
TH1F* fIncohJpsiToMuOrig;
TH1F* fIncohPsi2sToMuOrig;
TH1F* fIncohPsi2sToMuPiOrig;
TH1F* fTwoGammaToMuMediumOrig;
TH1F* fTwoGammaToMuLowOrig;

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
  val += par[2]* ( fTwoGammaToMuLow   ->Interpolate(x[0]) );   //needed
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
  fileMC[1] = 0x0;
  fileMC[2] = 0x0;
  fileMC[3] = new TFile("MCtrainResults/2019-11-09/kIncohJpsiToMu/AnalysisResults.root");
  fileMC[4] = new TFile("MCtrainResults/2019-11-09/kIncohPsi2sToMu/AnalysisResults.root");
  fileMC[5] = new TFile("MCtrainResults/2019-11-09/kIncohPsi2sToMuPi/AnalysisResults.root");
  fileMC[6] = new TFile("MCtrainResults/2019-11-09/kTwoGammaToMuLow/AnalysisResults.root");
  fileMC[7] = new TFile("MCtrainResults/2019-11-09/kTwoGammaToMuMedium/AnalysisResults.root");
  TDirectory* dirMC[8];
  for(Int_t iDirectory = 0; iDirectory < 8; iDirectory++) {
    if ( iDirectory == 1 || iDirectory == 2 ) continue;
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
    if ( iDirectory == 1 || iDirectory == 2 ) continue;
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
  fCohJpsiToMuOrig        = (TH1F*)listingsMC[0]->FindObject("fTemplatePtDistributionH");
  // fCohPsi2sToMuOrig       = (TH1F*)listingsMC[1]->FindObject("fTemplatePtDistributionH");
  // fCohPsi2sToMuPiOrig     = (TH1F*)listingsMC[2]->FindObject("fTemplatePtDistributionH");
  fIncohJpsiToMuOrig      = (TH1F*)listingsMC[3]->FindObject("fTemplatePtDistributionH");
  fIncohPsi2sToMuOrig     = (TH1F*)listingsMC[4]->FindObject("fTemplatePtDistributionH");
  fIncohPsi2sToMuPiOrig   = (TH1F*)listingsMC[5]->FindObject("fTemplatePtDistributionH");
  fTwoGammaToMuLowOrig    = (TH1F*)listingsMC[6]->FindObject("fTemplatePtDistributionH");
  fTwoGammaToMuMediumOrig = (TH1F*)listingsMC[7]->FindObject("fTemplatePtDistributionH");

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
  fCohJpsiToMuOrig        -> Rebin(5);  // -> 25 MeV bins
  // fCohPsi2sToMuOrig       -> Rebin(5);
  // fCohPsi2sToMuPiOrig     -> Rebin(5);
  fIncohJpsiToMuOrig      -> Rebin(5);
  fIncohPsi2sToMuOrig     -> Rebin(5);
  fIncohPsi2sToMuPiOrig   -> Rebin(5);
  fTwoGammaToMuLowOrig    -> Rebin(5);
  fTwoGammaToMuMediumOrig -> Rebin(5);





  Float_t PtBins[]    = { 0.000, 0.025, 0.050, 0.075, 0.100, 0.125, 0.150, 0.175,
                          0.200, 0.225, 0.250, 0.275, 0.350, 0.425, 0.500, 0.575,
                          0.650, 0.725,
                          0.800, 0.875, 0.950, 1.100, 1.250, 1.400, 1.600, 1.800,
                          2.000, 2.500, 3.000, 3.500, 4.000, 5.000
                        };
  Int_t   PtBinNumber = sizeof(PtBins)/sizeof(Float_t) - 1; // or just = 9
  fCohJpsiToMu        = new TH1F("fCohJpsiToMu",        "fCohJpsiToMu",        PtBinNumber, PtBins );
  // fCohPsi2sToMu       = new TH1F("fCohPsi2sToMu",       "fCohPsi2sToMu",       PtBinNumber, PtBins );
  // fCohPsi2sToMuPi     = new TH1F("fCohPsi2sToMuPi",     "fCohPsi2sToMuPi",     PtBinNumber, PtBins );
  fIncohJpsiToMu      = new TH1F("fIncohJpsiToMu",      "fIncohJpsiToMu",      PtBinNumber, PtBins );
  fIncohPsi2sToMu     = new TH1F("fIncohPsi2sToMu",     "fIncohPsi2sToMu",     PtBinNumber, PtBins );
  fIncohPsi2sToMuPi   = new TH1F("fIncohPsi2sToMuPi",   "fIncohPsi2sToMuPi",   PtBinNumber, PtBins );
  fTwoGammaToMuMedium = new TH1F("fTwoGammaToMuMedium", "fTwoGammaToMuMedium", PtBinNumber, PtBins );
  fTwoGammaToMuLow    = new TH1F("fTwoGammaToMuLow",    "fTwoGammaToMuLow",    PtBinNumber, PtBins );

  Double_t BinCenter = 0;
  for ( Int_t ibin = 1; ibin < fCohJpsiToMuOrig->GetNbinsX(); ibin++ ) {
    BinCenter = ((TAxis*)fCohJpsiToMuOrig->GetXaxis())->GetBinCenter(ibin);
    if ( BinCenter > PtBins[PtBinNumber-1] ) continue;
    cout << "BinCenter = " << BinCenter << endl;
    for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
      if ( BinCenter < PtBins[ibinVariable+1] ){
        // fCohJpsiToMu->Fill( fCohJpsiToMuOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        fCohJpsiToMu->SetBinContent(ibinVariable+1, fCohJpsiToMu->GetBinContent(ibinVariable+1) + (fCohJpsiToMuOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        break;
      }
    }
    // for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
    //   if ( BinCenter < PtBins[ibinVariable+1] ){
    //     // fCohPsi2sToMu->Fill( fCohPsi2sToMuOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
    //     fCohPsi2sToMu->SetBinContent(ibinVariable+1, fCohPsi2sToMu->GetBinContent(ibinVariable+1) + (fCohPsi2sToMuOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
    //     break;
    //   }
    // }
    // for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
    //   if ( BinCenter < PtBins[ibinVariable+1] ){
    //     // fCohPsi2sToMuPi->Fill( fCohPsi2sToMuPiOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
    //     fCohPsi2sToMuPi->SetBinContent(ibinVariable+1, fCohPsi2sToMuPi->GetBinContent(ibinVariable+1) + (fCohPsi2sToMuPiOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
    //     break;
    //   }
    // }
    for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
      if ( BinCenter < PtBins[ibinVariable+1] ){
        // fIncohJpsiToMu->Fill( fIncohJpsiToMuOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        fIncohJpsiToMu->SetBinContent(ibinVariable+1, fIncohJpsiToMu->GetBinContent(ibinVariable+1) + (fIncohJpsiToMuOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        break;
      }
    }
    for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
      if ( BinCenter < PtBins[ibinVariable+1] ){
        // fIncohPsi2sToMu->Fill( fIncohPsi2sToMuOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        fIncohPsi2sToMu->SetBinContent(ibinVariable+1, fIncohPsi2sToMu->GetBinContent(ibinVariable+1) + (fIncohPsi2sToMuOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        break;
      }
    }
    for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
      if ( BinCenter < PtBins[ibinVariable+1] ){
        // fIncohPsi2sToMuPi->Fill( fIncohPsi2sToMuPiOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        fIncohPsi2sToMuPi->SetBinContent(ibinVariable+1, fIncohPsi2sToMuPi->GetBinContent(ibinVariable+1) + (fIncohPsi2sToMuPiOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        break;
      }
    }
    for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
      if ( BinCenter < PtBins[ibinVariable+1] ){
        // fTwoGammaToMuMedium->Fill( fTwoGammaToMuMediumOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        fTwoGammaToMuMedium->SetBinContent(ibinVariable+1, fTwoGammaToMuMedium->GetBinContent(ibinVariable+1) + (fTwoGammaToMuMediumOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        break;
      }
    }
    for( Int_t ibinVariable = 0; ibinVariable < PtBinNumber-1; ibinVariable++ ) {
      if ( BinCenter < PtBins[ibinVariable+1] ){
        // fTwoGammaToMuHigh->Fill( fTwoGammaToMuHighOrig->GetBinContent(ibin), 1./(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        fTwoGammaToMuLow->SetBinContent(ibinVariable+1, fTwoGammaToMuLow->GetBinContent(ibinVariable+1) + (fTwoGammaToMuLowOrig->GetBinContent(ibin))/(PtBins[ibinVariable+1]-PtBins[ibinVariable]) );
        break;
      }
    }
  }

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
  fTwoGammaToMuLow    -> Sumw2();
  fTwoGammaToMuMedium -> Sumw2();
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
  Double_t Integral_fTwoGammaToMuLow    = fTwoGammaToMuLow   -> Integral();
  Double_t Integral_fTwoGammaToMuMedium = fTwoGammaToMuMedium -> Integral();
  fCohJpsiToMu        -> Scale( 1/Integral_fCohJpsiToMu        );
  // fCohPsi2sToMu       -> Scale( 1/Integral_fCohPsi2sToMu       );
  // fCohPsi2sToMuPi     -> Scale( 1/Integral_fCohPsi2sToMuPi     );
  fIncohJpsiToMu      -> Scale( 1/Integral_fIncohJpsiToMu      );
  fIncohPsi2sToMu     -> Scale( 1/Integral_fIncohPsi2sToMu     );
  fIncohPsi2sToMuPi   -> Scale( 1/Integral_fIncohPsi2sToMuPi   );
  fTwoGammaToMuLow    -> Scale( 1/Integral_fTwoGammaToMuLow   );
  fTwoGammaToMuMedium -> Scale( 1/Integral_fTwoGammaToMuMedium );

  /* - High Pt-tail, with HERA's data.
     -
   */
  TF1* fModelForHighPtTail = new TF1("fModelForHighPtTail","[0]*x*(1+[1]/[2]*x*x)^(-[2])",0,4);
  fModelForHighPtTail->SetParameter(0,1);
//  fModelForHighPtTail->SetParameter(1,debug==4 ? 1.25 : 1.);
//  fModelForHighPtTail->SetParameter(2,debug==4 ? 6.1 : 1.);
  fModelForHighPtTail->SetParameter(1, 1.6/*1.79*/);
  fModelForHighPtTail->SetParameter(2, 3.58);
  fModelForHighPtTail->SetNpx( fCohJpsiToMu->GetNbinsX() );
  // fHighPtTail = (TH1F*) fModelForHighPtTail->GetHistogram()->Clone("fHighPtTail");
  // for (Int_t ibin=1; ibin<=fHighPtTail->GetNbinsX(); ibin++) {
  //   fHighPtTail->SetBinError(ibin,0);
  // }
  Float_t PtBins2[]    = { 0.000, 0.025, 0.050, 0.075, 0.100, 0.125, 0.150, 0.175,
                          0.200, 0.225, 0.250, 0.275, 0.350, 0.425, 0.500, 0.575,
                          0.650, 0.725,
                          0.800, 0.875, 0.950, 1.100, 1.250, 1.400, 1.600, 1.800,
                          2.000, 2.500, 3.000, 3.500, 4.000, 5.000
                        };
  Int_t   PtBinNumber2 = sizeof(PtBins2)/sizeof(Float_t) - 1; // or just = 9
  fHighPtTail = new TH1F( "fHighPtTail", "fHighPtTail", PtBinNumber2, PtBins2 );
  for (Int_t ibin=1; ibin<=fHighPtTail->GetNbinsX(); ibin++) {
    fHighPtTail->SetBinError(ibin,0);
    fHighPtTail->SetBinContent(ibin,  fModelForHighPtTail->Integral(PtBins2[ibin-1], PtBins2[ibin])/(PtBins2[ibin]-PtBins2[ibin-1]));
  }
  Double_t Integral_fHighPtTail = fHighPtTail->Integral();
  fHighPtTail->Scale( 1/Integral_fHighPtTail );




  TH1F *fDimuonPtDistributionDataH = 0x0;
  if      ( selectionFlag == 0 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionH");
  else if ( selectionFlag == 1 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionRestrictedRapidity0N0NHv3");
  else if ( selectionFlag == 2 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3");
  else if ( selectionFlag == 3 ) fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3");
  else                           fDimuonPtDistributionDataH = (TH1F*)listings->FindObject("fDimuonPtDistributionH");
  // fDimuonPtDistributionDataH->Rebin(5);
  // if ( selectionFlag == 3 ) fDimuonPtDistributionDataH->Rebin(2);
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
                                         // 1.5, 3,
                                         1., 3,
                                         /*7*/1
                                         );
  FitPtDistrPreliminary->SetNpx(1000);
  if ( selectionFlag != 3 ) { fDimuonPtDistributionDataCloneH->Fit(FitPtDistrPreliminary, "","", 1.5, 3.); }
  else                      { fDimuonPtDistributionDataCloneH->Fit(FitPtDistrPreliminary, "","", 1. , 3.); }
  gStyle->SetOptFit(100);
  // UtilityCanvas->SaveAs("UtilityCanvas.png");


  new TCanvas;
  TF1* FitPtDistr = new TF1(  "FitPtDistr",
                              fPtDistr,
                              0, 3,
                              /*7*/5
                              );
  FitPtDistr->SetNpx(1000);




  Double_t kFeedDownCoherent = 0.05;     // neutral element
  Double_t kError            = 0.01;
  FitPtDistr->SetParameter(4, kFeedDownCoherent);
  FitPtDistr->SetParLimits(4, FitPtDistr->GetParameter(4)*(1-kError), FitPtDistr->GetParameter(4)*(1+kError));

  // FEED-DOWN COHERENT
  // Double_t kFeedDownIncoherent = 1705;     // neutral element
  // Double_t kErrorInc           = 0.175;
  // FitPtDistr->SetParameter(5, kFeedDownIncoherent);
  // FitPtDistr->SetParLimits(5, FitPtDistr->GetParameter(5)*(1-kErrorInc), FitPtDistr->GetParameter(5)*(1+kErrorInc));

  // Gamma+Gamma Medium
  // FitPtDistr->SetParameter(2, 4800);
  // FitPtDistr->SetParameter(2, 6531);
  if        ( selectionFlag == 0 ) {
    // FitPtDistr->SetParameter(2, 6531);  //2018
    // FitPtDistr->SetParameter(2, 9035);  //2018+2015 with SPD
    FitPtDistr->SetParameter(2, 115);  //2016
  } else if ( selectionFlag == 1 ) {
    // FitPtDistr->SetParameter(2, 5213);  //2018
    // FitPtDistr->SetParameter(2, 7754);  //2018+2015 with SPD
    FitPtDistr->SetParameter(2, 74);  //2016
  } else if ( selectionFlag == 2 ) {
    // FitPtDistr->SetParameter(2,  370);  //2018
    // FitPtDistr->SetParameter(2,  439);  //2018+2015 with SPD
    FitPtDistr->SetParameter(2,  39);  //2016
  } else if ( selectionFlag == 3 ) {
    // FitPtDistr->SetParameter(2,  470);  //2018
    // FitPtDistr->SetParameter(2,  543);  //2018+2015 with SPD
    FitPtDistr->SetParameter(2,  46);  //2016
  } else {
    FitPtDistr->SetParameter(2,  200);  //2016
  }

  // FitPtDistr->FixParameter(2, 0);
  FitPtDistr->SetParLimits(2, FitPtDistr->GetParameter(2)*0.95, FitPtDistr->GetParameter(2)*1.05);

  // Unknown component
  // if        ( selectionFlag == 0 ) {
  //   // FitPtDistr->SetParameter(3, 743);
  //   // FitPtDistr->SetParLimits(3, 720, 745);
  //   FitPtDistr->SetParameter(3, 580);            // 2018+2015
  //   FitPtDistr->SetParLimits(3, 550, 600);       // 2018+2015
  // } else if ( selectionFlag == 1 ) {
  //   // FitPtDistr->SetParameter(3, 125);
  //   // FitPtDistr->SetParLimits(3, 100, 150);
  //   FitPtDistr->SetParameter(3, 125);            // 2018+2015
  //   FitPtDistr->SetParLimits(3, 120, 130);       // 2018+2015
  // } else if ( selectionFlag == 2 ) {
  //   FitPtDistr->SetParameter(3, 20);
  //   FitPtDistr->SetParLimits(3, 0, 50);
  // } else if ( selectionFlag == 3 ) {
  //   // FitPtDistr->SetParameter(3, 540);
  //   // FitPtDistr->SetParLimits(3, 500, 600);
  //   FitPtDistr->SetParameter(3, 400);            // 2018+2015
  //   FitPtDistr->SetParLimits(3, 380, 420);       // 2018+2015
  // } else if ( selectionFlag == 4 ) {
  //   // FitPtDistr->SetParameter(3, 40);
  //   // FitPtDistr->SetParLimits(3, 0, 100);
  //   FitPtDistr->SetParameter(3, 25);             // 2018+2015
  //   FitPtDistr->SetParLimits(3, 0, 100);         // 2018+2015
  // }

  FitPtDistr->SetParameter(3, FitPtDistrPreliminary->GetParameter(0));
  FitPtDistr->SetParLimits(3, FitPtDistrPreliminary->GetParameter(0)*0.9, FitPtDistrPreliminary->GetParameter(0)*1.1);
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
  gPad->SetLogy();
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
  fDimuonPtDistributionDataH->GetYaxis()->SetRangeUser(fDimuonPtDistributionDataH->GetMaximum()*0.0001, fDimuonPtDistributionDataH->GetMaximum()*10.);
  fDimuonPtDistributionDataH->GetXaxis()->SetRangeUser(0, 5.5);
  // fDimuonPtDistributionDataH->GetXaxis()->SetRangeUser(0, 3);
  gPad ->SetLogy();
  fDimuonPtDistributionDataH->Draw("PEsame");
  fCohJpsiToMu        -> SetLineColor(kRed);
  // fCohPsi2sToMu       -> SetLineColor(kMagenta);
  // fCohPsi2sToMuPi     -> SetLineColor(kYellow+1);
  fIncohJpsiToMu      -> SetLineColor(kCyan);
  fIncohPsi2sToMu     -> SetLineColor(kYellow);
  fIncohPsi2sToMuPi   -> SetLineColor(kBlue+2);
  fTwoGammaToMuLow    -> SetLineColor(kGreen);
  fTwoGammaToMuMedium -> SetLineColor(kBlue+3);
  fHighPtTail         -> SetLineColor(kGreen+1);
  fCohJpsiToMu        -> SetLineWidth(3);
  // fCohPsi2sToMu       -> SetLineWidth(3);
  // fCohPsi2sToMuPi     -> SetLineWidth(3);
  fIncohJpsiToMu      -> SetLineWidth(3);
  fIncohPsi2sToMu     -> SetLineWidth(3);
  fIncohPsi2sToMuPi   -> SetLineWidth(3);
  fTwoGammaToMuMedium -> SetLineWidth(3);
  fTwoGammaToMuLow    -> SetLineWidth(3);
  fHighPtTail         -> SetLineWidth(3);
  TH1F* fCohJpsiToMuC        = (TH1F*) fCohJpsiToMu        -> Clone("fCohJpsiToMuC");
  // TH1F* fCohPsi2sToMuC       = (TH1F*) fCohPsi2sToMu       -> Clone("fCohPsi2sToMuC");
  // TH1F* fCohPsi2sToMuPiC     = (TH1F*) fCohPsi2sToMuPi     -> Clone("fCohPsi2sToMuPiC");
  TH1F* fIncohJpsiToMuC      = (TH1F*) fIncohJpsiToMu      -> Clone("fIncohJpsiToMuC");
  TH1F* fIncohPsi2sToMuC     = (TH1F*) fIncohPsi2sToMu     -> Clone("fIncohPsi2sToMuC");
  TH1F* fIncohPsi2sToMuPiC   = (TH1F*) fIncohPsi2sToMuPi   -> Clone("fIncohPsi2sToMuPiC");
  TH1F* fTwoGammaToMuLowC    = (TH1F*) fTwoGammaToMuLow    -> Clone("fTwoGammaToMuLowC");
  TH1F* fTwoGammaToMuMediumC = (TH1F*) fTwoGammaToMuMedium -> Clone("fTwoGammaToMuMediumC");
  // TH1F* fTwoGammaToMuHighC   = (TH1F*) fTwoGammaToMuHigh   -> Clone("fTwoGammaToMuHighC");
  TH1F* fHighPtTailC         = (TH1F*) fHighPtTail         -> Clone("fHighPtTailC");
  fCohJpsiToMuC        -> Scale( FitPtDistr->GetParameter(0) );
  // fCohPsi2sToMuC       -> Scale( FitPtDistr->GetParameter(0) * FitPtDistr->GetParameter(4) );
  // fCohPsi2sToMuPiC     -> Scale( FitPtDistr->GetParameter(0) * FitPtDistr->GetParameter(4) );
  fIncohJpsiToMuC      -> Scale( FitPtDistr->GetParameter(1) );
  fIncohPsi2sToMuC     -> Scale( FitPtDistr->GetParameter(1) * FitPtDistr->GetParameter(4) );
  fIncohPsi2sToMuPiC   -> Scale( FitPtDistr->GetParameter(1) * FitPtDistr->GetParameter(4) );
  fTwoGammaToMuMediumC -> Scale( FitPtDistr->GetParameter(2) );
  fTwoGammaToMuLowC    -> Scale( FitPtDistr->GetParameter(2) );
  // fTwoGammaToMuHighC   -> Scale( FitPtDistr->GetParameter(2) );
  fHighPtTailC         -> Scale( FitPtDistr->GetParameter(3) );
  fCohJpsiToMuC        -> Draw("same");
  // fCohPsi2sToMuC       -> Draw("same");
  // fCohPsi2sToMuPiC     -> Draw("same");
  fIncohJpsiToMuC      -> Draw("same");
  // fIncohPsi2sToMuC     -> Draw("same");
  fIncohPsi2sToMuPiC   -> Draw("same");
  fTwoGammaToMuLowC    -> Draw("same");
  // fTwoGammaToMuMediumC -> Draw("same");
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

  /* - COMPUTING $f_I$
   * -
   * - This snippet is for computing the
   * - $f_I$ fraction for correcting the
   * - cross sections later on.
   * - Basically the idea is that
   * -
   * - f_I = ( Incoh + Incoh_Dissociative )/ Coherent
   * -
   */
  Double_t intGG = fTwoGammaToMuLowC  ->Integral( fTwoGammaToMuLowC  ->GetXaxis()->FindBin(0.0001), fTwoGammaToMuLowC  ->GetXaxis()->FindBin(0.9999999) );
  // Double_t int1i = fIncohJpsiToMuC    ->Integral( fIncohJpsiToMuC    ->GetXaxis()->FindBin(0.0001), fIncohJpsiToMuC    ->GetXaxis()->FindBin(0.9999999) );
  // Double_t intun = fHighPtTailC       ->Integral( fHighPtTailC       ->GetXaxis()->FindBin(0.0001), fHighPtTailC       ->GetXaxis()->FindBin(0.9999999) );
  // Double_t f_I   = (0.0 + intun ) / int1i;



  // Double_t err1c = 0;
  Double_t err1i = 0;
  Double_t errun = 0;
  Double_t errfI = 0;
  // Double_t int1c = fCohJpsiToMuC  ->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.2499999), err1c, "" );
  Double_t int1i = fIncohJpsiToMuC->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.2499999), err1i, "" );
  Double_t intun = fHighPtTailC   ->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.2499999), errun, "" );
  Double_t f_I   = (intun ) / int1i;
  // errfI          = err1c + err1i + errun;
  Double_t RatioErrfIOverfI        = 0;
  Double_t RatioErrIncohOverIncoh  = 0;
  RatioErrfIOverfI          = errun/intun + err1i/int1i;
  errfI          = RatioErrfIOverfI * f_I;
  // cout << "err1c = " << err1c;
  cout << "err1i = " << err1i;
  cout << "errun = " << errun;
  cout << "errfI = " << errfI;



  // Double_t int1i_v2 = 0;
  // Double_t intun_v2 = 0;
  // for (size_t i = 1; i < fTwoGammaToMuLowC->GetXaxis()->FindBin(0.9999999); i++) {
  //   int1i_v2 += fIncohJpsiToMuC->GetBinContent(i);
  //   intun_v2 += fHighPtTailC   ->GetBinContent(i);
  // }
  // Double_t f_I_v2   = (0.0 + intun_v2 ) / int1i_v2;


  TLatex* latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(42);
  latex->SetTextAlign(11);
  latex->SetNDC();
  latex->DrawLatex(0.17,0.94,"ALICE Performance, Pb-p #sqrt{s_{NN}} = 8.18 TeV");
  latex->SetTextSize(0.045);
  // latex->DrawLatex(0.55,0.84,"UPC, #it{L} = 235 ub^{-1}");
  // latex->DrawLatex(0.55,0.84,"UPC, LHC16s data");
  latex->DrawLatex(0.17,0.86,Form("f_{I} = #frac{%.3f}{%.3f} = %.3f #pm %.6f", intun, int1i, f_I, errfI));
  // latex->DrawLatex(0.17,0.86,Form("f_{I} = #frac{%.3f + %.3f}{%.3f} = %.3f ", 0., intun, int1i, f_I));
  latex->DrawLatex(0.55,0.78,"#it{p}_{T} < 1 GeV/#it{c}");
  if      ( selectionFlag == 0 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.0,-2.5));
  else if ( selectionFlag == 1 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.6,-2.6));
  else if ( selectionFlag == 2 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.6,-3.1));
  else if ( selectionFlag == 3 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.1,-2.6));
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
  l->AddEntry(  fDimuonPtDistributionDataH, "UPC LHC16s");
  // if      ( selectionFlag == 0 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018");
  // else if ( selectionFlag == 1 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 0N0N");
  // else if ( selectionFlag == 2 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 0NXN");
  // else if ( selectionFlag == 3 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 XN0N");
  // else if ( selectionFlag == 4 ) l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018 XNXN");
  // else                           l->AddEntry(  fDimuonPtDistributionDataH, "ALICE data 2018");
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
  l->AddEntry(  fTwoGammaToMuLowC,    "Continuum  #gamma#gamma #rightarrow #mu#mu");
  l->Draw();

  gPad->SaveAs("pngResults/fitPtDistr.png", "RECREATE");
  if      ( selectionFlag == 0 ) gPad->SaveAs("pngResults/fitPtDistr4to25.png",  "RECREATE");
  else if ( selectionFlag == 1 ) gPad->SaveAs("pngResults/fitPtDistr36to26.png", "RECREATE");
  else if ( selectionFlag == 2 ) gPad->SaveAs("pngResults/fitPtDistr36to31.png", "RECREATE");
  else if ( selectionFlag == 3 ) gPad->SaveAs("pngResults/fitPtDistr31to26.png", "RECREATE");
  else                           gPad->SaveAs("pngResults/fitPtDistr.png",       "RECREATE");


}
