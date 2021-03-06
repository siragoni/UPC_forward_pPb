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



//_____________________________________________________________________________
/* - Histograms to be used for the fit.
 * - What happens is that we will interpolate the many points together...
 * -
 */
TH1F*     fCohJpsiToMu;
TH1F*     fCohPsi2sToMu;
TH1F*     fCohPsi2sToMuPi;
TH1F*     fIncohJpsiToMu;
TH1F*     fIncohPsi2sToMu;
TH1F*     fIncohPsi2sToMuPi;
TH1F*     fTwoGammaToMuLow;
TH1F*     fTwoGammaToMuMedium;
TH1F*     fHighPtTail;
Double_t  ptrSelectionFlag = 0;
Double_t  CBparameters[8][5];
Double_t  helpppppp = 0;


// TH1F*   Systematics = new TH1F("Systematics", "Systematics", 1000, -0.5, 999.5);
// TH1F*       Systematics = 0x0;
// TH1F*       Errors      = 0x0;
Int_t       CounterForSystematics = 1;
TFile*      fileMC[8];
TDirectory* dirMC[8];
TList*      listingsMC[8];


/* - Functions used for the fit!!
 * -
 */
TF1* JPsiPeakFit     = new TF1( "JPsiPeakFit",    "crystalball",2.2,6);
TF1* PsiPrimePeakFit = new TF1( "PsiPrimePeakFit","crystalball",2.2,6);
TF1* GammaGammaFit   = new TF1( "GammaGammaFit",
                                "[0]*TMath::Exp(-[1]*x)*( (x > 1.5) ? 1 : 1 + [2]*(x-1.5)*(x-1.5) + [3]*(x-1.5)*(x-1.5)*(x-1.5) + [4]*(x-1.5)*(x-1.5)*(x-1.5)*(x-1.5) )",
                                1.2,8
                                );


//_____________________________________________________________________________
/* - Fit function for the Pt plots.
 * - I am using simple ROOT to make gaussian fits to the plot.
 */
Double_t fInvariantMass(Double_t* x,Double_t* par)
{
  /* - Par 0, 1, 2:   coherent.
     - Par 3, 4, 5:   incoherent.
     - Par 6      :   gamma+gamma.
     -
   */
  Double_t val = 0;
  if ( ptrSelectionFlag == 2 ) {
    val += par[0]* ( fIncohJpsiToMu     ->Interpolate(x[0]) );
    val += par[1]* ( fIncohPsi2sToMu    ->Interpolate(x[0]) );
  } else {
    val += par[0]* ( fCohJpsiToMu       ->Interpolate(x[0]) );
    val += par[1]* ( fCohPsi2sToMu      ->Interpolate(x[0]) );
  }
  // val   += par[2]* ( fTwoGammaToMuMedium->Interpolate(x[0]) );
  val   += par[2]* ( fTwoGammaToMuLow   ->Interpolate(x[0]) );

  return val;
}
//_____________________________________________________________________________
/* - Evgeny's own fit function.
 * -
 */
double fsum(double *x, double *par){
  Double_t parPsiPrime[5];
  Double_t parBkg[5];
  for( Int_t i=0 ; i<5 ; i++ ) parPsiPrime[i]=par[i+5];
  for( Int_t i=0 ; i<5 ; i++ ) parBkg[i]     =par[i+10];
  return par[15]*JPsiPeakFit->EvalPar(x,par)+par[16]*PsiPrimePeakFit->EvalPar(x,parPsiPrime)+par[17]*GammaGammaFit->EvalPar(x,parBkg);
}
//_____________________________________________________________________________
/* - Fit function for the templates of the PsiPrime.
 * -
 */
void fCrystalBallFitJPsi(TH1F* histoToBeFit)//, Double_t &bookKeeping[5])
{
  TF1* CBfit     = new TF1("CBfit","crystalball",2,15);
  // TF1* CBfit     = new TF1("CBfit","crystalball",1.8,7);
  CBfit       ->SetParameter(0,1);
  // CBfit       ->SetParameter(3,1.08);
  CBfit       ->FixParameter(3,1.08);
  CBfit       ->SetParameter(4,115);
  // CBfit       ->SetParameter(4,6);
  CBfit       ->SetParLimits(4,110,120);
  // CBfit       ->SetParLimits(4,1,12);
  // CBfit       ->SetParLimits(4,12,99999999);
  CBfit       ->SetParameter(2,0.090);
  CBfit       ->SetParameter(1,3.115);
  CBfit       ->SetParLimits(1,3.113,3.17);
  CBfit       ->SetNpx(1000);
  TCanvas*    JPsiCanvas = new TCanvas( "JPsiCanvas", "JPsiCanvas", 900, 800 );
  CBfit       ->Draw();
  histoToBeFit->Fit(CBfit, "R");
  // CBfit       ->SetParameter(0,1/CBfit->Integral(2,15));
  // bookKeeping = new Double_t[5];
  for(Int_t i = 0; i < 5; i++){
    CBparameters[0][i] = CBfit->GetParameter(i);
  }
}
//_____________________________________________________________________________
/* - Fit function for the templates of the PsiPrime.
 * -
 */
void fCrystalBallFitPsiPrime(TH1F* histoToBeFit)//, Double_t &bookKeeping[5])
{
  TF1* CBfit     = new TF1("CBfit","crystalball",2,15);
  CBfit       ->SetParameter(0,1);
  CBfit       ->SetParameter(3,1.08);
  // CBfit       ->SetParameter(4,3689197);
  // CBfit       ->SetParLimits(4,1,99999999);
  CBfit       ->SetParameter(4,20);
  CBfit       ->SetParLimits(4,1.5,100);
  CBfit       ->SetParameter(2,0.070);
  CBfit       ->SetParameter(1,3.67);
  CBfit       ->SetNpx(1000);
  TCanvas*    PsiPrimeCanvas = new TCanvas( "PsiPrimeCanvas", "PsiPrimeCanvas", 900, 800 );
  CBfit       ->Draw();
  cout << "histo integral = " << histoToBeFit->Integral() << endl << flush;
  histoToBeFit->Fit(CBfit, "R");
  cout << "CBfit integral = " << CBfit->Integral(2.1,9) << endl << flush;
  // CBfit       ->SetParameter(0,1/(CBfit->Integral(2.1,9)));
  cout << "CBfit integral / histo width = " << CBfit->Integral(2.1,9)/histoToBeFit->GetXaxis()->GetBinWidth(1) << endl << flush;
  // CBfit       ->SetParameter(0,1/CBfit->Integral(3,14));
  // bookKeeping = new Double_t[5];
  for(Int_t i = 0; i < 5; i++){
    CBparameters[1][i] = CBfit->GetParameter(i);
  }
}
//_____________________________________________________________________________
/* - Fit function for the templates of the PsiPrime.
 * -
 */
void fBkgPolFit(TH1F* histoToBeFit)//, Double_t &bookKeeping[5])
{
  TF1* PolBkg     = new TF1("PolBkg","[0]*TMath::Exp(-[1]*x)*( (x > 1.5) ? 1 : 1 + [2]*(x-1.5)*(x-1.5) + [3]*(x-1.5)*(x-1.5)*(x-1.5) + [4]*(x-1.5)*(x-1.5)*(x-1.5)*(x-1.5) )",0.9,8);
  // TF1* PolBkg     = new TF1("PolBkg","[0]*TMath::Exp(-[1]*x)*( (x > 4) ? 1 : 1 + [2]*(x-4)*(x-4) + [3]*(x-4)*(x-4)*(x-4) + [4]*(x-4)*(x-4)*(x-4)*(x-4) )",1.8,12);
  // PolBkg       ->SetParameter(0,0.025);   // best fit
  // PolBkg       ->SetParameter(3,0);       // best fit
  // PolBkg       ->SetParameter(4,0);       // best fit
  // PolBkg       ->SetParameter(2,-0.25);   // best fit
  PolBkg       ->SetParameter(0,0.025);
  PolBkg       ->SetParameter(3,0.0001);
  PolBkg       ->SetParameter(4,0.0001);
  PolBkg       ->SetParameter(2,0.0001);
  // PolBkg       ->FixParameter(2,0.000);
  PolBkg       ->SetParLimits(0,0.0001,1);
  PolBkg       ->SetParLimits(3,0.00000001,3);
  PolBkg       ->SetParLimits(4,0.00000001,2);
  PolBkg       ->SetParLimits(2,0.0000000000001,2);

  // PolBkg       ->SetParameter(0,0.07);
  // PolBkg       ->SetParameter(3,0);
  // PolBkg       ->SetParameter(4,0.25);
  // PolBkg       ->SetParameter(2,0.65);
  PolBkg       ->SetParameter(1,0.9);
  // PolBkg       ->SetParLimits(1,0.7,1);
  PolBkg       ->SetNpx(1000);
  TCanvas*      BkgCanvas = new TCanvas( "BkgCanvas", "BkgCanvas", 900, 800 );
  PolBkg       ->Draw();
  histoToBeFit ->Fit(PolBkg, "R");
  // PolBkg       ->SetParameter(0,1/PolBkg->Integral(2,8));
  // bookKeeping = new Double_t[5];
  for(Int_t i = 0; i < 5; i++){
    CBparameters[4][i] = PolBkg->GetParameter(i);
  }
}
//_____________________________________________________________________________
/* - Fit function for the ZNC plots.
 * -
 */
void fitJPsiTemplateMC(const int selectionFlag = 0, const int selectionFlag2 = 0){
  fileMC[0] = new TFile("MCtrainResults/2019-10-30/kCohJpsiToMu/AnalysisResults.root");
  fileMC[1] = 0x0;
  fileMC[2] = 0x0;
  fileMC[3] = new TFile("MCtrainResults/2019-10-30/kIncohJpsiToMu/AnalysisResults.root");
  fileMC[4] = new TFile("MCtrainResults/2019-10-30/kIncohPsi2sToMu/AnalysisResults.root");
  fileMC[5] = new TFile("MCtrainResults/2019-10-30/kIncohPsi2sToMuPi/AnalysisResults.root");
  fileMC[6] = new TFile("MCtrainResults/2019-10-30/kTwoGammaToMuLow/AnalysisResults.root");
  fileMC[7] = new TFile("MCtrainResults/2019-10-30/kTwoGammaToMuMedium/AnalysisResults.root");
  // TDirectory* dirMC[8];
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
  // TList* listingsMC[8];
  for(Int_t iDirectory = 0; iDirectory < 8; iDirectory++) {
    if ( iDirectory == 1 || iDirectory == 2 ) continue;
    dirMC[iDirectory]->GetObject("MyOutputContainer", listingsMC[iDirectory]);
  }
  if( selectionFlag == 1){
    if( selectionFlag2 == 0 ){
      fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_2"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_2"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_2"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_2"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_2"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_2"));
    } else if( selectionFlag2 == 1 ){
      fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_3");
      fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_3");
      fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_3");
      fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_3");
      fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_3");
      fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_3");
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_4"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_4"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_4"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_4"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_4"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_4"));
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
    } else {
      fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionH");
      fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionH");
      fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionH");
      fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionH");
      fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionH");
      fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionH");
    }
  } else if ( selectionFlag == 2 ){
    if( selectionFlag2 == 0 ){
      fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_0");
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_1"));
    } else if( selectionFlag2 == 1 ){
      fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_2");
      fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_2");
      fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_2");
      fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_2");
      fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_2");
      fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_2");
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_3"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_3"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_3"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_3"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_3"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_3"));
    } else if( selectionFlag2 == 2 ){
      fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_4");
      fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_4");
      fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_4");
      fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_4");
      fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_4");
      fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_4");
      fCohJpsiToMu       ->Add((TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fIncohJpsiToMu     ->Add((TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fIncohPsi2sToMu    ->Add((TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fIncohPsi2sToMuPi  ->Add((TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fTwoGammaToMuMedium->Add((TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
      fTwoGammaToMuLow   ->Add((TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionRapidityBinsH_5"));
    }
  }  else {
    fCohJpsiToMu        = (TH1F*)listingsMC[0]->FindObject("fInvariantMassDistributionH");
    fIncohJpsiToMu      = (TH1F*)listingsMC[3]->FindObject("fInvariantMassDistributionH");
    fIncohPsi2sToMu     = (TH1F*)listingsMC[4]->FindObject("fInvariantMassDistributionH");
    fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fInvariantMassDistributionH");
    fTwoGammaToMuMedium = (TH1F*)listingsMC[7]->FindObject("fInvariantMassDistributionH");
    fTwoGammaToMuLow    = (TH1F*)listingsMC[6]->FindObject("fInvariantMassDistributionH");
  }

  /* - Rebin
     -
   */
  // fCohJpsiToMu        -> Rebin(5);
  // fCohPsi2sToMu       -> Rebin(5);
  // fCohPsi2sToMuPi     -> Rebin(5);
  // fIncohJpsiToMu      -> Rebin(5);
  // fIncohPsi2sToMu     -> Rebin(5);
  // fIncohPsi2sToMuPi   -> Rebin(5);
  // fTwoGammaToMuMedium -> Rebin(5);
  // fTwoGammaToMuHigh   -> Rebin(5);
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
  fTwoGammaToMuMedium -> Rebin(5);
  fTwoGammaToMuLow    -> Sumw2();
  Double_t Integral_fCohJpsiToMu        = fCohJpsiToMu        -> Integral();
  // Double_t Integral_fCohPsi2sToMu       = fCohPsi2sToMu       -> Integral();
  // Double_t Integral_fCohPsi2sToMuPi     = fCohPsi2sToMuPi     -> Integral();
  Double_t Integral_fIncohJpsiToMu      = fIncohJpsiToMu      -> Integral();
  Double_t Integral_fIncohPsi2sToMu     = fIncohPsi2sToMu     -> Integral();
  Double_t Integral_fIncohPsi2sToMuPi   = fIncohPsi2sToMuPi   -> Integral();
  Double_t Integral_fTwoGammaToMuMedium = fTwoGammaToMuMedium -> Integral();
  Double_t Integral_fTwoGammaToMuHigh   = fTwoGammaToMuLow    -> Integral();
  fCohJpsiToMu        -> Scale( 1/Integral_fCohJpsiToMu        );
  // fCohPsi2sToMu       -> Scale( 1/Integral_fCohPsi2sToMu       );
  // fCohPsi2sToMuPi     -> Scale( 1/Integral_fCohPsi2sToMuPi     );
  fIncohJpsiToMu      -> Scale( 1/Integral_fIncohJpsiToMu      );
  fIncohPsi2sToMu     -> Scale( 1/Integral_fIncohPsi2sToMu     );
  fIncohPsi2sToMuPi   -> Scale( 1/Integral_fIncohPsi2sToMuPi   );
  fTwoGammaToMuMedium -> Scale( 1/Integral_fTwoGammaToMuMedium );
  fTwoGammaToMuLow    -> Scale( 1/Integral_fTwoGammaToMuHigh   );

  fCrystalBallFitJPsi    (fIncohJpsiToMu);//,      CBparameters[0]);
  // if( selectionFlag < 10 ){
  fCrystalBallFitPsiPrime(fIncohPsi2sToMu);//,     CBparameters[1]);
  // fCrystalBallFitJPsi    (fIncohJpsiToMu,    CBparameters[2]);
  // fCrystalBallFitPsiPrime(fIncohPsi2sToMu,   CBparameters[3]);
  fBkgPolFit             (fTwoGammaToMuLow);//, CBparameters[4]);
  // }
}
//_____________________________________________________________________________
/* - Fit function for the ZNC plots.
 * -
 */
void fitJPsiTemplate(const char* AnalysisName, const int selectionFlag, const int selectionFlag2){
  /* - There are three cases for the selectionFlag:
     - 1) = 0 ; this implies the traditional pt-integrated plot;
     - 2) = 1 ; this is instead the coherent component;
     - 3) = 2 ; this is the incoherent component;
     - 4) = 3 ; ******************* ;
     -
   */
  ptrSelectionFlag = selectionFlag;
  TFile* fileList = new TFile(AnalysisName);
  TDirectory* dir = fileList->GetDirectory("MyTask");
  TList* listings;
  dir->GetObject("MyOutputContainer", listings);

  TH1F *fInvariantMassDistributionH = 0x0;
  if      ( selectionFlag == 0 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionH");
  else if ( selectionFlag == 1 ) {
    // if      ( selectionFlag2 == 0 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsH_0");
    // else if ( selectionFlag2 == 1 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsH_1");
    if      ( selectionFlag2 == 0 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHCMUP14");
    else if ( selectionFlag2 == 1 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHCMUP16");
    else if ( selectionFlag2 == 2 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHV0ADec");
    else if ( selectionFlag2 == 3 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHV0CDec");
    else if ( selectionFlag2 == 4 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHADADec");
    else if ( selectionFlag2 == 5 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHADCDec");
    else if ( selectionFlag2 == 6 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionHV0Ccells");
    else if ( selectionFlag2 == 7 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionOneNeutronZNCH");
    else if ( selectionFlag2 == 8 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionOneNeutronZNAH");
    else if ( selectionFlag2 == 9 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionOnlyTwoTracks_RightRapidity_PtCutH");
    else if ( selectionFlag2 == 10) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionOnlyThreeTracks_RightRapidity_PtCutH");
  }
  else if ( selectionFlag == 2 ) {
    if      ( selectionFlag2 == 0 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionMoreRapidityBinsH_0");
    else if ( selectionFlag2 == 1 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionMoreRapidityBinsH_1");
    else if ( selectionFlag2 == 2 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionMoreRapidityBinsH_2");
  }
  else if ( selectionFlag == 3 ) {
    if      ( selectionFlag2 == 0 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionH");
    else if ( selectionFlag2 == 1 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsNewH_0");
    else if ( selectionFlag2 == 2 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsNewH_1");
    else if ( selectionFlag2 == 3 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionZeroZNAH");
    else if ( selectionFlag2 == 4 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsZeroZNAH_0");
    else if ( selectionFlag2 == 5 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsZeroZNAH_1");
    else if ( selectionFlag2 == 6 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionZeroZNCH");
    else if ( selectionFlag2 == 7 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsZeroZNCH0");
    else if ( selectionFlag2 == 8 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsZeroZNCH1");
    else if ( selectionFlag2 == 9 ) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionSmall0N0NH");
    else if ( selectionFlag2 == 10) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsSmall0N0NH_0");
    else if ( selectionFlag2 == 11) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityBinsSmall0N0NH_1");
    else if ( selectionFlag2 == 12) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionZeroZNCH");
    else if ( selectionFlag2 == 13) {
      fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_0");
      fInvariantMassDistributionH->Add( (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_1") );
    }
    else if ( selectionFlag2 == 14) {
      fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_2");
      fInvariantMassDistributionH->Add( (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_3") );
    }
    else if ( selectionFlag2 == 15) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityThreeBinsZeroZNCH_0");
    else if ( selectionFlag2 == 16) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityThreeBinsZeroZNCH_1");
    else if ( selectionFlag2 == 17) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityThreeBinsZeroZNCH_2");
    else if ( selectionFlag2 == 18) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_0");
    else if ( selectionFlag2 == 19) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_1");
    else if ( selectionFlag2 == 20) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_2");
    else if ( selectionFlag2 == 21) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNCH_3");
    else if ( selectionFlag2 == 22) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_0");
    else if ( selectionFlag2 == 23) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_1");
    else if ( selectionFlag2 == 24) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_2");
    else if ( selectionFlag2 == 25) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_3");
    else if ( selectionFlag2 == 26) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_4");
    else if ( selectionFlag2 == 27) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionZeroZNAH");
    else if ( selectionFlag2 == 28) {
      fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_0");
      fInvariantMassDistributionH->Add( (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_1") );
    }
    else if ( selectionFlag2 == 29) {
      fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_2");
      fInvariantMassDistributionH->Add( (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_3") );
    }
    else if ( selectionFlag2 == 30) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityThreeBinsZeroZNAH_0");
    else if ( selectionFlag2 == 31) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityThreeBinsZeroZNAH_1");
    else if ( selectionFlag2 == 32) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityThreeBinsZeroZNAH_2");
    else if ( selectionFlag2 == 33) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_0");
    else if ( selectionFlag2 == 34) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_1");
    else if ( selectionFlag2 == 35) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_2");
    else if ( selectionFlag2 == 36) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFourBinsZeroZNAH_3");
    else if ( selectionFlag2 == 37) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_0");
    else if ( selectionFlag2 == 38) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_1");
    else if ( selectionFlag2 == 39) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_2");
    else if ( selectionFlag2 == 40) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_3");
    else if ( selectionFlag2 == 41) fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_4");


  }
  else                           fInvariantMassDistributionH = (TH1F*)listings->FindObject("fInvariantMassDistributionH");
  fInvariantMassDistributionH->Rebin(5);
  fInvariantMassDistributionH->Draw("PE");

  fInvariantMassDistributionH->SetLineColor(kBlue);
  fInvariantMassDistributionH->SetLineStyle(kSolid);
  fInvariantMassDistributionH->SetLineWidth(3);
  fInvariantMassDistributionH->SetMarkerStyle(kFullCircle);
  fInvariantMassDistributionH->SetMarkerColor(kBlue);
  fInvariantMassDistributionH->SetMarkerSize(1);
  fInvariantMassDistributionH->GetXaxis()->SetTitle("M_{#mu#mu} [GeV/#it{c}^{2}]");
  fInvariantMassDistributionH->GetYaxis()->SetTitle( Form( "Counts / (%.3f GeV/#it{c})",
                                                          fInvariantMassDistributionH->GetXaxis()->GetBinWidth(1)
                                                        )
                                                    );
  fInvariantMassDistributionH->SetTitle("");


  // fitJPsiTemplateMC();
  fitJPsiTemplateMC( selectionFlag, selectionFlag2 );
  new TCanvas;


  TF1 *fFitInvMass = new TF1("fFitInvMass",fsum,1.2,8,18);
  fFitInvMass->SetNpx(1000000);
  fFitInvMass->FixParameter(0, CBparameters[0][0]);    // best
  fFitInvMass->FixParameter(3, CBparameters[0][3]);    // best
  // fFitInvMass->FixParameter(3, 1.02714e+00);    // best
  // fFitInvMass->FixParameter(4, 140);    // best
  fFitInvMass->FixParameter(4, CBparameters[0][4]);    // best
  // fFitInvMass->SetParameter(3, CBparameters[0][3]);
  // fFitInvMass->SetParLimits(3, CBparameters[0][3]*0.8, CBparameters[0][3]*1.2);
  // fFitInvMass->SetParameter(4, CBparameters[0][4]);
  // fFitInvMass->SetParLimits(4, CBparameters[0][4]*0.8, CBparameters[0][4]*1.2);
  // fFitInvMass->FixParameter(1, CBparameters[0][1]);
  // fFitInvMass->FixParameter(2, CBparameters[0][2]);
  fFitInvMass->SetParameter(1, CBparameters[0][1]);
  fFitInvMass->SetParLimits(1, CBparameters[0][1]*0.9, CBparameters[0][1]*1.1);
  fFitInvMass->SetParameter(2, CBparameters[0][2]);
  fFitInvMass->SetParLimits(2, CBparameters[0][2]*0.8, CBparameters[0][2]*1.2);
  fFitInvMass->FixParameter(0+5, CBparameters[1][0]);
  fFitInvMass->FixParameter(3+5, CBparameters[1][3]);
  fFitInvMass->FixParameter(4+5, CBparameters[1][4]);
  fFitInvMass->FixParameter(1+5, CBparameters[1][1]);
  fFitInvMass->FixParameter(2+5, fFitInvMass->GetParameter(2)*CBparameters[1][2]/CBparameters[0][2]);
  fFitInvMass->FixParameter(0+10, CBparameters[4][0]);    // best
  fFitInvMass->FixParameter(2+10, CBparameters[4][2]);    // best
  fFitInvMass->FixParameter(3+10, CBparameters[4][3]);    // best
  fFitInvMass->FixParameter(4+10, CBparameters[4][4]);    // best
  // fFitInvMass->FixParameter(2+10, 0.509393 );    // Fix to previous fit...
  // fFitInvMass->FixParameter(3+10, 0.833773 );    // Fix to previous fit...
  // fFitInvMass->FixParameter(4+10, 0.237383 );    // Fix to previous fit...
  // fFitInvMass->SetParameter(0+10, CBparameters[4][0]);    // mmmh
  // fFitInvMass->SetParameter(2+10, CBparameters[4][2]);    // mmmh
  // fFitInvMass->SetParameter(3+10, CBparameters[4][3]);    // mmmh
  // fFitInvMass->SetParameter(4+10, CBparameters[4][4]);    // mmmh
  fFitInvMass->SetParameter(1+10, CBparameters[4][1]);
  // fFitInvMass->FixParameter(1+10, CBparameters[4][1]);
  fFitInvMass->SetParLimits(1+10, CBparameters[4][1]*0.9, CBparameters[4][1]*1.1);
  // fFitInvMass->SetParameter(15, 1);
  // fFitInvMass->SetParameter(16, 1);
  // fFitInvMass->SetParameter(17, 1);
  // fFitInvMass->SetParLimits(15, 0.001, 9999999999);
  // fFitInvMass->SetParLimits(16, 0.001, 9999999999);
  // fFitInvMass->SetParLimits(17, 0.001, 9999999999);
  // if(selectionFlag == 19) {
  //   fFitInvMass->SetParameter(15, helpppppp * 2);
  // } else {
  //   fFitInvMass->SetParameter(15, 1);
  // }
  fFitInvMass->SetParameter(15, 1);
  fFitInvMass->SetParameter(16, 1);
  fFitInvMass->SetParameter(17, 1);
  // if(selectionFlag == 19) {
  //   fFitInvMass->SetParLimits(15, helpppppp * 1.2, 9999999999);
  // } else {
  //   fFitInvMass->SetParLimits(15, 0.001, 9999999999);
  // }
  fFitInvMass->SetParLimits(15, 0.001, 9999999999);
  fFitInvMass->SetParLimits(16, 0.001, 9999999999);
  fFitInvMass->SetParLimits(17, 0.001, 9999999999);
  fFitInvMass->Print();
  for(Int_t i = 0; i < 18; i++) cout << fFitInvMass->GetParameter(i) << endl << flush;


  // fInvariantMassDistributionH->Fit( fFitInvMass,"LR","", 1.4, 6. );
  fInvariantMassDistributionH->Fit( fFitInvMass,"LR","", 2.6, 3.5 );
  TCanvas* PtDistrCanvas = new TCanvas( "InvariantMassDimuonFit", "InvariantMassDimuonFit", 900, 800 );
  gPad->SetMargin(0.13,0.01,0.12,0.01);
  // gPad->SetLogy();
  gStyle->SetOptFit(0);
  gStyle->SetOptStat(0);
  gPad->SetTitle(  Form(  ";M_{#mu#mu} (GeV/c^{2});Counts / (%.0f MeV/c^{2})",
                           fInvariantMassDistributionH->GetXaxis()->GetBinWidth(1)*1000.  )  );
  /* - Beautifying is starting now.
     -
   */
  fInvariantMassDistributionH->GetXaxis()->SetTitleOffset(1.25);
  // fInvariantMassDistributionH->GetYaxis()->SetTitleOffset(1.25);
  fInvariantMassDistributionH->GetYaxis()->SetTitleOffset(1.45);
  fInvariantMassDistributionH->GetXaxis()->SetTitleSize(0.045);
  fInvariantMassDistributionH->GetYaxis()->SetTitleSize(0.045);
  fInvariantMassDistributionH->GetXaxis()->SetLabelSize(0.045);
  fInvariantMassDistributionH->GetYaxis()->SetLabelSize(0.045);
  fInvariantMassDistributionH->GetXaxis()->SetTitleFont(42);
  fInvariantMassDistributionH->GetYaxis()->SetTitleFont(42);
  fInvariantMassDistributionH->GetXaxis()->SetLabelFont(42);
  fInvariantMassDistributionH->GetYaxis()->SetLabelFont(42);
  fInvariantMassDistributionH->GetXaxis()->SetNdivisions(408);
  fInvariantMassDistributionH->GetYaxis()->SetRangeUser(0.0000000000001, fInvariantMassDistributionH->GetMaximum()*2.5);
  fInvariantMassDistributionH->GetXaxis()->SetRangeUser(1, 4);
  // gPad ->SetLogy();
  fInvariantMassDistributionH->Draw("PEsame");
  JPsiPeakFit    ->SetLineColor(kRed);
  PsiPrimePeakFit->SetLineColor(kMagenta);
  GammaGammaFit  ->SetLineColor(kGreen);
  GammaGammaFit  ->SetLineStyle(kDashed);
  JPsiPeakFit    -> SetLineWidth(3);
  PsiPrimePeakFit-> SetLineWidth(3);
  GammaGammaFit  -> SetLineWidth(3);
  JPsiPeakFit    ->SetNpx(fInvariantMassDistributionH->GetNbinsX());
  PsiPrimePeakFit->SetNpx(fInvariantMassDistributionH->GetNbinsX());
  GammaGammaFit  ->SetNpx(fInvariantMassDistributionH->GetNbinsX());
  JPsiPeakFit->FixParameter( 0, fFitInvMass->GetParameter(0)*fFitInvMass->GetParameter(15) );
  JPsiPeakFit->FixParameter( 1, fFitInvMass->GetParameter(1) );
  JPsiPeakFit->FixParameter( 2, fFitInvMass->GetParameter(2) );
  JPsiPeakFit->FixParameter( 3, fFitInvMass->GetParameter(3) );
  JPsiPeakFit->FixParameter( 4, fFitInvMass->GetParameter(4) );
  PsiPrimePeakFit->FixParameter( 0, fFitInvMass->GetParameter(5)*fFitInvMass->GetParameter(16) );
  PsiPrimePeakFit->FixParameter( 1, fFitInvMass->GetParameter(1+5) );
  PsiPrimePeakFit->FixParameter( 2, fFitInvMass->GetParameter(2+5) );
  PsiPrimePeakFit->FixParameter( 3, fFitInvMass->GetParameter(3+5) );
  PsiPrimePeakFit->FixParameter( 4, fFitInvMass->GetParameter(4+5) );
  GammaGammaFit->FixParameter( 0, fFitInvMass->GetParameter(10)*fFitInvMass->GetParameter(17) );
  GammaGammaFit->FixParameter( 1, fFitInvMass->GetParameter(1+10) );
  GammaGammaFit->FixParameter( 2, fFitInvMass->GetParameter(2+10) );
  GammaGammaFit->FixParameter( 3, fFitInvMass->GetParameter(3+10) );
  GammaGammaFit->FixParameter( 4, fFitInvMass->GetParameter(4+10) );
  JPsiPeakFit    ->Draw("SAME");
  PsiPrimePeakFit->Draw("SAME");
  GammaGammaFit  ->Draw("SAME");
  // GammaGammaFit  ->Draw("SAME");
  // JPsiPeakFit    ->SetNpx(fInvariantMassDistributionH->GetNbinsX()/5);
  // PsiPrimePeakFit->SetNpx(fInvariantMassDistributionH->GetNbinsX()/5);
  // GammaGammaFit  ->SetNpx(fInvariantMassDistributionH->GetNbinsX()/5);



  TLatex* latex = new TLatex();
  latex->SetTextSize(0.05);
  latex->SetTextFont(42);
  latex->SetTextAlign(11);
  latex->SetNDC();
  latex->DrawLatex(0.17,0.94,"ALICE Performance, Pb-p #sqrt{s_{NN}} = 8.16 TeV");
  latex->SetTextSize(0.045);
  // latex->DrawLatex(0.55,0.84,"UPC, #it{L} = 235 ub^{-1}");
  latex->DrawLatex(0.55,0.84,"UPC, LHC16s");
  // latex->DrawLatex(0.55,0.78,"#it{p}_{T} < 0.3 GeV/#it{c}");
  if     ( selectionFlag  != 2) {
  if     ( selectionFlag2 == 11 ) latex->DrawLatex(0.55,0.78,"#it{p}_{T} < 1 GeV/c");
  else                            latex->DrawLatex(0.55,0.78,"#it{p}_{T}-integrated");
  }
  // latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.0,-2.5));
  if        ( selectionFlag == 0 ) {
                               latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.0,  -2.50));
  } else if ( selectionFlag == 1 ) {
    if ( selectionFlag2 == 0 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.0,  -3.25));
    if ( selectionFlag2 == 1 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.25, -2.50));
  } else if ( selectionFlag == 2 ) {
    if ( selectionFlag2 == 0 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.0,  -3.5));
    if ( selectionFlag2 == 1 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.5,  -3.0));
    if ( selectionFlag2 == 2 ) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.0,  -2.5));
  } else if ( selectionFlag == 3 ) {
    if ( selectionFlag2 == 12) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -2.500));
    if ( selectionFlag2 == 13) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.250));
    if ( selectionFlag2 == 14) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.250,  -2.500));
    if ( selectionFlag2 == 15) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.500));
    if ( selectionFlag2 == 16) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.500,  -3.000));
    if ( selectionFlag2 == 17) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.000,  -2.500));
    if ( selectionFlag2 == 18) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.625));
    if ( selectionFlag2 == 19) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.625,  -3.250));
    if ( selectionFlag2 == 20) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.250,  -2.875));
    if ( selectionFlag2 == 21) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-2.875,  -2.500));
    if ( selectionFlag2 == 22) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.700));
    if ( selectionFlag2 == 23) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.700,  -3.400));
    if ( selectionFlag2 == 24) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.400,  -3.100));
    if ( selectionFlag2 == 25) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.100,  -2.800));
    if ( selectionFlag2 == 26) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-2.800,  -2.500));
    if ( selectionFlag2 == 27) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -2.500));
    if ( selectionFlag2 == 28) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.250));
    if ( selectionFlag2 == 29) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.250,  -2.500));
    if ( selectionFlag2 == 30) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.500));
    if ( selectionFlag2 == 31) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.500,  -3.000));
    if ( selectionFlag2 == 32) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.000,  -2.500));
    if ( selectionFlag2 == 33) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.625));
    if ( selectionFlag2 == 34) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.625,  -3.250));
    if ( selectionFlag2 == 35) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.250,  -2.875));
    if ( selectionFlag2 == 36) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-2.875,  -2.500));
    if ( selectionFlag2 == 37) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-4.000,  -3.700));
    if ( selectionFlag2 == 38) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.700,  -3.400));
    if ( selectionFlag2 == 39) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.400,  -3.100));
    if ( selectionFlag2 == 40) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-3.100,  -2.800));
    if ( selectionFlag2 == 41) latex->DrawLatex(0.55,0.72,Form("%.1f < y < %.1f",-2.800,  -2.500));
  }


  /* - This is the part where we obtain the actual number of J/Psi, PsiPrime
     - and the background. This is still Kay's original code. I will modify it.
     - Hopefully if everything goes alright, I should have been able to complete
     - it by the time you are reading this.
     -
   */
  Double_t numberOfTotalJPsi     = 0;
  Double_t numberOfTotalPsi2s    = 0;
  Double_t numberOfTotalBkg      = 0;
  Double_t numberOfTotalJPsiErr  = 0;
  Double_t numberOfTotalPsi2sErr = 0;
  Double_t numberOfTotalBkgErr   = 0;
  // if ( ptrSelectionFlag == 2 ) {
  //   numberOfTotalJPsi  = fIncohJpsiToMuC  -> Integral();
  //   numberOfTotalPsi2s = fIncohPsi2sToMuC -> Integral();
  // } else {
    // numberOfTotalJPsi  = fCohJpsiToMuFromModelH -> Integral();
    // numberOfTotalPsi2s = fCohPsi2sToMuFromModelH-> Integral();
    // numberOfTotalJPsi  = JPsiPeakFit    -> Integral(2.2,6,1.E-15);
    // numberOfTotalPsi2s = PsiPrimePeakFit-> Integral(2.2,6,1.E-15);
    numberOfTotalJPsi     = (JPsiPeakFit    -> Integral(2.2,6))/0.05;
    numberOfTotalPsi2s    = (PsiPrimePeakFit-> Integral(2.2,6))/0.05;
    Double_t JPsiRangeVar[9];
    JPsiRangeVar[0]       = (JPsiPeakFit    -> Integral(2.85,3.35))/0.05;
    JPsiRangeVar[1]       = (JPsiPeakFit    -> Integral(2.8,3.35))/0.05;
    JPsiRangeVar[2]       = (JPsiPeakFit    -> Integral(2.9,3.35))/0.05;
    JPsiRangeVar[3]       = (JPsiPeakFit    -> Integral(2.85,3.3))/0.05;
    JPsiRangeVar[4]       = (JPsiPeakFit    -> Integral(2.85,3.4))/0.05;
    numberOfTotalJPsiErr  = numberOfTotalJPsi *fFitInvMass->GetParError(15)/fFitInvMass->GetParameter(15);
    numberOfTotalPsi2sErr = numberOfTotalPsi2s*fFitInvMass->GetParError(16)/fFitInvMass->GetParameter(16);

  // }
  // numberOfTotalBkg = fTwoGammaFromModelH      -> Integral();
  // numberOfTotalBkg = GammaGammaFit-> Integral(2.2,6,1.E-15);
  numberOfTotalBkg    = (GammaGammaFit-> Integral(2.8,3.3))/0.05;
  numberOfTotalBkgErr = numberOfTotalBkg*fFitInvMass->GetParError(17)/fFitInvMass->GetParameter(17);
  latex->DrawLatex(0.55,0.66,Form("N_{J/#psi} = %.0f #pm %.0f",        numberOfTotalJPsi,  numberOfTotalJPsiErr ));//fFitInvMass->GetParameter(0) *fFitInvMass->GetParError(15)/0.05 ) );
  latex->DrawLatex(0.55,0.60,Form("N_{#psi(2S)} = %.0f #pm %.0f",      numberOfTotalPsi2s, numberOfTotalPsi2sErr));//fFitInvMass->GetParameter(5) *fFitInvMass->GetParError(16)/0.05 ) );
  latex->DrawLatex(0.55,0.54,Form("N_{#gamma#gamma} = %.0f #pm %.0f",  numberOfTotalBkg,   numberOfTotalBkgErr  ));//fFitInvMass->GetParameter(10)*fFitInvMass->GetParError(17)/0.05 ) );
  // latex->DrawLatex(0.55,0.54,Form("#sigma_{J/#psi} = %.0f #pm %.0f MeV/c^{2}", sigma.getVal()*1000,    sigma.getError()*1000));
  // latex->DrawLatex(0.55,0.48,Form("#sigma_{#psi(2S)} = %.0f MeV/c^{2} fixed",  sigma2.getVal()*1000));

  /* - This part concerns the background of the two signals.
     - Here, we extrapolate the background and compute the significance maybe?
     -
   */
  Double_t JPsiPeakBkg        = 0;
  Double_t Psi2JPsiPeakBkg    = 0;
  Double_t JPsiPeakSignal     = 0;
  Double_t Psi2JPsiPeakSignal = 0;
  JPsiPeakBkg     = GammaGammaFit->Integral(2.75,3.45);
  Psi2JPsiPeakBkg = GammaGammaFit->Integral(3.45,3.90);
  // latex->DrawLatex(0.55,0.42,Form("N_{BG J/#psi} = %.0f #pm %.0f",   JPsiPeakBkg,     JPsiPeakBkg     * fFitInvMass->GetParError(17) / numberOfTotalJPsi ));
  // latex->DrawLatex(0.55,0.36,Form("N_{BG #psi(2s)} = %.0f #pm %.0f", Psi2JPsiPeakBkg, Psi2JPsiPeakBkg * fFitInvMass->GetParError(17) / numberOfTotalPsi2s));
  latex->DrawLatex(0.55,0.18,Form("      #tilde{#chi}^{2} = %.2f / %.2d = %.2f  ",
                                     fFitInvMass->GetChisquare(),
                                     fFitInvMass->GetNDF(),
                                     fFitInvMass->GetChisquare()/fFitInvMass->GetNDF()
                                     )
                                    );



  gPad->SaveAs(Form("pngResults/InvMassSystematics_%d_%d.png", selectionFlag, selectionFlag2), "RECREATE");

  // TFile* fileSyst = new TFile("pngResults/Systematics.root", "recreate");
  // TH1F* Systematics = new TH1F("Systematics", "Systematics", 1000, -0.5, 999.5);
  // TH1F* Errors = new TH1F("Errors", "Errors", 1000, -0.5, 999.5);
  // Systematics->Fill(0);
  // Errors->Fill(0);
  // Systematics->Write(Systematics->GetName(), TObject::kOverwrite);
  // Errors->Write(Errors->GetName(), TObject::kOverwrite);
  // fileSyst->Close();


  // TFile* fileSyst = new TFile("pngResults/Systematics.root");
  // TH1F* Systematics  = (TH1F*) fileSyst->Get("Systematics");
  // TH1F* Errors       = (TH1F*) fileSyst->Get("Errors");
  // TH1F* Systematics2 = (TH1F*) Systematics->Clone("Systematics");
  // TH1F* Errors2      = (TH1F*) Errors->Clone("Errors");
  // // fileSyst->cd();
  // // fileSyst->Close();
  // TFile* fileSyst2 = new TFile("pngResults/Systematics2.root", "recreate");
  // fileSyst2->cd();
  // // Systematics->Fill( selectionFlag+selectionFlag2, numberOfTotalJPsi    );
  // // Errors     ->Fill( selectionFlag+selectionFlag2, numberOfTotalJPsiErr );
  // // Systematics->Write(Systematics->GetName(), TObject::kOverwrite);
  // // Errors     ->Write(Errors     ->GetName(), TObject::kOverwrite);
  // Systematics2->Fill( 100*selectionFlag+10*selectionFlag2, numberOfTotalJPsi    );
  // for( Int_t iLoop = 0; iLoop < 5; iLoop++ ) {
  //   Systematics2->Fill( 100*selectionFlag+10*selectionFlag2+iLoop+1, JPsiRangeVar[iLoop] );
  // }
  // Errors2     ->Fill( 100*selectionFlag+10*selectionFlag2, numberOfTotalJPsiErr );
  // Systematics2->Write(Systematics->GetName(), TObject::kOverwrite);
  // Errors2     ->Write(Errors     ->GetName(), TObject::kOverwrite);
  // // Systematics->Write();
  // // Errors     ->Write();
  // fileSyst2  ->Close();
  // fileSyst   ->Close();
  // CounterForSystematics += 1;
  //
  // // std::ofstream outfile;
  // //
  // // outfile.open("test.txt", std::ios_base::app);
  // // outfile << Form("%d %d ");


}
