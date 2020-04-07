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



Double_t fLumiPerRun = 0;
Int_t    fRunNum     = 0;
Double_t GlobalAxE   = 0;
// Double_t fLumi       = 11919.684;


Double_t fLumi       = 7917.604;  // REDUCED run list...

//_____________________________________________________________________________
/* - There were plenty of ways to do this...
 * - However, recently the STL libraries were
 * - creating confusion on the LEGO framework
 * - (they didn't fire at all).
 * - This problem was not found on local, where
 * - things were working properly...
 * - So I am using the most barbaric C-style
 * - arrays/for...
 */
void SetLuminosityCap()
{
  fLumiPerRun = 0;
  /* - Here I am rounding up the number for 10k,
   * - so that I don't have to do tedious conversions...
   * - I am adding 1 entry to the number obtained by 40k,
   * - so that I am not missing anything...
   * -
   */
  if      ( fRunNum == 267131 ) { fLumiPerRun = 299.488; }
  else if ( fRunNum == 267130 ) { fLumiPerRun = 133.813; }
  else if ( fRunNum == 267110 ) { fLumiPerRun = 293.588; }
  else if ( fRunNum == 267109 ) { fLumiPerRun = 506.868; }
  else if ( fRunNum == 267077 ) { fLumiPerRun = 52.7582; }
  else if ( fRunNum == 267072 ) { fLumiPerRun = 108.475; }
  else if ( fRunNum == 267070 ) { fLumiPerRun = 40.3772; }
  else if ( fRunNum == 267067 ) { fLumiPerRun = 117.626; }
  else if ( fRunNum == 267063 ) { fLumiPerRun = 122.597; }
  else if ( fRunNum == 267062 ) { fLumiPerRun = 67.7758; }
  else if ( fRunNum == 267022 ) { fLumiPerRun = 95.3051; }
  else if ( fRunNum == 267020 ) { fLumiPerRun = 446.61; }
  else if ( fRunNum == 266998 ) { fLumiPerRun = 22.3174; }
  else if ( fRunNum == 266997 ) { fLumiPerRun = 22.4019; }
  else if ( fRunNum == 266994 ) { fLumiPerRun = 58.4044; }
  else if ( fRunNum == 266993 ) { fLumiPerRun = 26.0976; }
  else if ( fRunNum == 266988 ) { fLumiPerRun = 307.71; }
  else if ( fRunNum == 266944 ) { fLumiPerRun = 174.388; }
  else if ( fRunNum == 266943 ) { fLumiPerRun = 164.8; }
  else if ( fRunNum == 266942 ) { fLumiPerRun = 68.5736; }
  else if ( fRunNum == 266940 ) { fLumiPerRun = 110.686; }
  else if ( fRunNum == 266915 ) { fLumiPerRun = 58.1344; }
  else if ( fRunNum == 266912 ) { fLumiPerRun = 163.755; }
  else if ( fRunNum == 266886 ) { fLumiPerRun = 167.216; }
  else if ( fRunNum == 266885 ) { fLumiPerRun = 111.504; }
  else if ( fRunNum == 266883 ) { fLumiPerRun = 132.063; }
  else if ( fRunNum == 266882 ) { fLumiPerRun = 76.5574; }
  else if ( fRunNum == 266880 ) { fLumiPerRun = 34.1592; }
  else if ( fRunNum == 266878 ) { fLumiPerRun = 444.15; }
  else if ( fRunNum == 266857 ) { fLumiPerRun = 47.3076; }
  else if ( fRunNum == 266807 ) { fLumiPerRun = 58.4043; }
  else if ( fRunNum == 266805 ) { fLumiPerRun = 137.953; }
  else if ( fRunNum == 266800 ) { fLumiPerRun = 277.81; }
  else if ( fRunNum == 266776 ) { fLumiPerRun = 347.019; }
  else if ( fRunNum == 266775 ) { fLumiPerRun = 587.711; }
  else if ( fRunNum == 266708 ) { fLumiPerRun = 77.0559; }
  else if ( fRunNum == 266706 ) { fLumiPerRun = 255.623; }
  else if ( fRunNum == 266703 ) { fLumiPerRun = 47.0861; }
  else if ( fRunNum == 266702 ) { fLumiPerRun = 121.264; }
  else if ( fRunNum == 266676 ) { fLumiPerRun = 25.0438; }
  else if ( fRunNum == 266674 ) { fLumiPerRun = 43.2181; }
  else if ( fRunNum == 266669 ) { fLumiPerRun = 202.677; }
  else if ( fRunNum == 266668 ) { fLumiPerRun = 151.058; }
  else if ( fRunNum == 266665 ) { fLumiPerRun = 102.909; }
  else if ( fRunNum == 266659 ) { fLumiPerRun = 147.023; }
  else if ( fRunNum == 266658 ) { fLumiPerRun = 44.1322; }
  else if ( fRunNum == 266657 ) { fLumiPerRun = 451.944; }
  else if ( fRunNum == 266630 ) { fLumiPerRun = 40.7954; }
  else if ( fRunNum == 266621 ) { fLumiPerRun = 138.065; }
  else if ( fRunNum == 266618 ) { fLumiPerRun = 228.025; }
  else if ( fRunNum == 266614 ) { fLumiPerRun = 372.09; }
  else if ( fRunNum == 266613 ) { fLumiPerRun = 310.359; }
  else if ( fRunNum == 266595 ) { fLumiPerRun = 253.44; }
  else if ( fRunNum == 266593 ) { fLumiPerRun = 158.782; }
  else if ( fRunNum == 266591 ) { fLumiPerRun = 57.1858; }
  else if ( fRunNum == 266588 ) { fLumiPerRun = 60.8278; }
  else if ( fRunNum == 266587 ) { fLumiPerRun = 123.611; }
  else if ( fRunNum == 266584 ) { fLumiPerRun = 169.477; }
  else if ( fRunNum == 266549 ) { fLumiPerRun = 45.4535; }
  else if ( fRunNum == 266543 ) { fLumiPerRun = 151.764; }
  else if ( fRunNum == 266539 ) { fLumiPerRun = 139.022; }
  else if ( fRunNum == 266534 ) { fLumiPerRun = 65.8065; }
  else if ( fRunNum == 266533 ) { fLumiPerRun = 80.7648; }
  else if ( fRunNum == 266525 ) { fLumiPerRun = 67.4575; }
  else if ( fRunNum == 266523 ) { fLumiPerRun = 45.6672; }
  else if ( fRunNum == 266522 ) { fLumiPerRun = 111.334; }
  else if ( fRunNum == 266520 ) { fLumiPerRun = 59.4779; }
  else if ( fRunNum == 266518 ) { fLumiPerRun = 304.703; }
  else if ( fRunNum == 266516 ) { fLumiPerRun = 20.191; }
  else if ( fRunNum == 266514 ) { fLumiPerRun = 166.081; }
  else if ( fRunNum == 266487 ) { fLumiPerRun = 28.6638; }
  else if ( fRunNum == 266480 ) { fLumiPerRun = 738.723; }
  else if ( fRunNum == 266479 ) { fLumiPerRun = 164.735; }
  else if ( fRunNum == 266472 ) { fLumiPerRun = 86.2489; }
  else if ( fRunNum == 266441 ) { fLumiPerRun = 143.532; }
  else if ( fRunNum == 266439 ) { fLumiPerRun = 33.9646; }
  else                          { fLumiPerRun = 1.00;    }


}
//_____________________________________________________________________________
/* - Computes the efficiency of the MC on a
 * - run-by-run basis.
 * -
 */
void fitEfficiencyMC(){

  // TFile* fileList = new TFile("AnalysisResultsIncohMC_02042020.root");  //Used file: for LHC16s NO ADC multi
  TFile* fileList = new TFile("AnalysisResultsIncohMC_ADdecisions.root");  //Used file: for LHC16s ADA and ADC decisions
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
  // TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunRestrictedRapidityH");
  // TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fMCEfficiencyPerRunRestrictedRapidityH");
  // TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunRestrictedRapidity36to31H");
  // TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fMCEfficiencyPerRunRestrictedRapidity36to31H");
  TH1F* fEfficiencyPerRunH   = (TH1F*)listings->FindObject("fEfficiencyPerRunRestrictedRapidity31to26H");
  TH1F* fMCEfficiencyPerRunH = (TH1F*)listings->FindObject("fMCEfficiencyPerRunRestrictedRapidity31to26H");
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
  TString  runLabel[200];
  for ( Int_t i = 0; i < 200; i++ ) ComputedEfficiency[i] = 0;
  for ( Int_t i = 0; i < 200; i++ ) ValueEfficiency[i] = 0;
  for ( Int_t i = 0; i < 200; i++ ) ValueEfficiency2[i] = 0;

  Int_t counter = 0;
  cout << "fEfficiencyPerRunH : " << endl;
  for ( Int_t iLoop = 1; iLoop <= RealEfficiency->GetNbinsX(); iLoop++ ) {
    if ( iLoop > 77 ) break;
    // if ( iLoop > 75 ) break;
    TString label          = RealEfficiency->GetXaxis()->GetBinLabel(iLoop);
    runLabel[iLoop]        = RealEfficiency->GetXaxis()->GetBinLabel(iLoop);
    // if ( atoi( label.Data() ) == 266615) continue;
    if ( atoi( label.Data() ) >  267131) continue;
    if ( atoi( label.Data() ) == 266439) continue;




    //_______________________________
    //
    // REDUCED run list
    //
    if ( atoi( label.Data() ) == 267110) continue;
    if ( atoi( label.Data() ) == 266885) continue;
    if ( atoi( label.Data() ) == 266882) continue;
    if ( atoi( label.Data() ) == 266857) continue;
    if ( atoi( label.Data() ) == 266775) continue;
    if ( atoi( label.Data() ) == 266706) continue;
    if ( atoi( label.Data() ) == 266703) continue;
    if ( atoi( label.Data() ) == 266702) continue;
    if ( atoi( label.Data() ) == 266668) continue;
    if ( atoi( label.Data() ) == 266658) continue;
    if ( atoi( label.Data() ) == 266657) continue;
    if ( atoi( label.Data() ) == 266614) continue;
    if ( atoi( label.Data() ) == 266613) continue;
    if ( atoi( label.Data() ) == 266591) continue;
    if ( atoi( label.Data() ) == 266588) continue;
    if ( atoi( label.Data() ) == 266587) continue;
    if ( atoi( label.Data() ) == 266584) continue;
    if ( atoi( label.Data() ) == 266518) continue;
    if ( atoi( label.Data() ) == 266516) continue;
    if ( atoi( label.Data() ) == 266514) continue;
    if ( atoi( label.Data() ) == 266472) continue;
    if ( atoi( label.Data() ) == 266441) continue;
    //_______________________________




    // if ( atoi( label.Data() ) == 266807) continue;
    // if ( atoi( label.Data() ) == 266805) continue;
    // if ( atoi( label.Data() ) == 266800) continue;
    // if ( atoi( label.Data() ) == 266776) continue;
    // if ( atoi( label.Data() ) == 266775) continue;
    // if ( atoi( label.Data() ) == 266708) continue;
    // if ( atoi( label.Data() ) == 266706) continue;
    // if ( atoi( label.Data() ) == 266703) continue;
    // if ( atoi( label.Data() ) == 266702) continue;
    // if ( atoi( label.Data() ) == 266676) continue;
    // if ( atoi( label.Data() ) == 266674) continue;
    // if ( atoi( label.Data() ) == 266669) continue;
    // if ( atoi( label.Data() ) == 266668) continue;
    // if ( atoi( label.Data() ) == 266665) continue;
    // if ( atoi( label.Data() ) == 266659) continue;
    // if ( atoi( label.Data() ) == 266658) continue;
    // if ( atoi( label.Data() ) == 266657) continue;
    // if ( atoi( label.Data() ) == 266630) continue;
    // if ( atoi( label.Data() ) == 266621) continue;
    // if ( atoi( label.Data() ) == 266618) continue;
    // if ( atoi( label.Data() ) == 266614) continue;
    // if ( atoi( label.Data() ) == 266613) continue;
    // if ( atoi( label.Data() ) == 266595) continue;
    // if ( atoi( label.Data() ) == 266593) continue;
    // if ( atoi( label.Data() ) == 266591) continue;
    // if ( atoi( label.Data() ) == 266588) continue;
    // if ( atoi( label.Data() ) == 266587) continue;
    // if ( atoi( label.Data() ) == 266584) continue;
    // if ( atoi( label.Data() ) == 266549) continue;
    // if ( atoi( label.Data() ) == 266543) continue;
    // if ( atoi( label.Data() ) == 266539) continue;
    // if ( atoi( label.Data() ) == 266534) continue;
    // if ( atoi( label.Data() ) == 266533) continue;
    // if ( atoi( label.Data() ) == 266525) continue;
    // if ( atoi( label.Data() ) == 266523) continue;
    // if ( atoi( label.Data() ) == 266522) continue;
    // if ( atoi( label.Data() ) == 266520) continue;
    // if ( atoi( label.Data() ) == 266518) continue;
    ValueEfficiency[iLoop] = RealEfficiency->GetBinContent(iLoop);
    if ( ValueEfficiency[iLoop] != 0 ) {
      Error1[iLoop]          = RealEfficiency->GetBinError(iLoop) / ValueEfficiency[iLoop];
    } else {
      Error1[iLoop]          = 0;
    }
    // ValueEfficiency[iLoop] = fEfficiencyPerRunH->GetXaxis()->GetBinContent(iLoop);
    counter++;
    cout <<   atoi( label.Data() ) << endl;
    fRunNum = atoi( label.Data() );
    SetLuminosityCap();
    Double_t weight = fLumiPerRun / fLumi;
    for ( Int_t iLoop2 = 1; iLoop2 <= MCEfficiency->GetNbinsX(); iLoop2++ ) {
      if ( iLoop2 > 90 ) break;
      TString label2 = MCEfficiency->GetXaxis()->GetBinLabel(iLoop2);
      // if ( atoi(label2.Data()) == atoi(label.Data()) ) {
      if ( atoi( MCEfficiency->GetXaxis()->GetBinLabel(iLoop2) ) == atoi( RealEfficiency->GetXaxis()->GetBinLabel(iLoop) ) ) {
        cout << atoi( MCEfficiency->GetXaxis()->GetBinLabel(iLoop2) ) << endl;
        cout << atoi( RealEfficiency->GetXaxis()->GetBinLabel(iLoop) ) << endl;
        // cout << "OK : " << counter << endl;
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

    if (ComputedEfficiency[iLoop] > 0.08) cout << "BEWARE Run: " << label.Data() << endl;
    GlobalAxE += (weight * ComputedEfficiency[iLoop]);
    cout << "Global AxE   = " << GlobalAxE << endl;
    cout << "Contribution ="  << (weight * ComputedEfficiency[iLoop]) << endl;

  }
  cout << "counter = " << counter << endl;


  // for ( Int_t i = 0; i < 200 ; i++ ) {
  //   cout << "Run " << i << " = " << ComputedEfficiency[i] << endl;
  // }
  //
  // for ( Int_t i = 0; i < 200 ; i++ ) {
  //   cout << "Run tr1 " << i << " = " << ValueEfficiency[i] << endl;
  //   cout << "Run tr2 " << i << " = " << ValueEfficiency2[i] << endl;
  // }


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
  // Eff->SetStats(0);
  Eff->SetFillColor(38);
  Eff->LabelsDeflate();
  for ( Int_t i = 0; i < 76; i++) {
    // Eff->Fill( i, ComputedEfficiency[i] );
    Eff->Fill( runLabel[i].Data() , ComputedEfficiency[i] );
    Eff->SetBinError( i+1 , (Error1[i] + Error2[i]) * ComputedEfficiency[i]);
  }
  Eff->Draw("ep");

  cout << "Global AxE = " << GlobalAxE << endl;

  TFile f("pngResults/efficiency.root", "recreate");
  // RealEfficiency->Write();
  f.Close();
}
