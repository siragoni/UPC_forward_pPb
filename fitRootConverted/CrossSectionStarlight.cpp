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
/* - Computes the Cross section in Pb-p.
 * -
 */
void CrossSectionStarlightPbp(){

  Double_t  RapidityValues[] = { 2.45, 2.55, 2.65, 2.75, 2.85, 2.95,
                                 3.05, 3.15, 3.25, 3.35, 3.45,
                                 3.55, 3.65, 3.75, 3.85, 3.95, 4.05 };

  Double_t  CrossSection[]     = { 9.3425, 8.8670, 8.3697, 7.8506, 7.3207,
                                   6.7680, 6.2211, 5.6489, 5.1056, 4.5320,
                                   4.0166, 3.4763, 3.0015, 2.5215, 2.1067,
                                   1.7089, 1.3696 };

  TH1F*     CrossSectionH      = new TH1F( "CrossSectionH" , "CrossSectionH", 17, 2.4, 4.1 );
  for ( Int_t i = 0; i < 17; i++) {
    CrossSectionH->SetBinContent( i+1, CrossSection[i] );
    CrossSectionH->SetBinError(   i+1, 0.0001             );
  }
  TCanvas* CrossSectionCanvas = new TCanvas("CrossSectionCanvas","CrossSectionCanvas",900,800);
  CrossSectionH->SetLineColor(kBlue);
  CrossSectionH->SetLineStyle(kSolid);
  CrossSectionH->SetLineWidth(3);
  CrossSectionH->SetMarkerStyle(kFullCircle);
  CrossSectionH->SetMarkerColor(kBlue);
  CrossSectionH->SetMarkerSize(1);
  CrossSectionH->Draw("ep");

  TF1*     CrossSectionFit       = new TF1(     "CrossSectionFit", "pol3", 2.35, 4.15 );
  CrossSectionFit->FixParameter( 0, -3.03926  );
  CrossSectionFit->FixParameter( 1, 19.9132   );
  CrossSectionFit->FixParameter( 2, -8.23756  );
  CrossSectionFit->FixParameter( 3,  0.886262 );
  CrossSectionFit->SetLineColor(kMagenta);
  CrossSectionFit->SetLineStyle(kSolid);
  CrossSectionFit->SetLineWidth(3);
  CrossSectionFit->SetMarkerStyle(kFullCircle);
  CrossSectionFit->SetMarkerColor(kMagenta);
  CrossSectionFit->SetMarkerSize(1);
  CrossSectionFit->Draw("same");


  Double_t CrossSectionRapidity[40] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0};

  CrossSectionRapidity[0] = ( CrossSectionFit->Integral(2.6001,3.5999) ) / 1.00; // Full          restricted range
  CrossSectionRapidity[1] = ( CrossSectionFit->Integral(2.6001,3.0999) ) / 0.50; // Most  forward restricted bin
  CrossSectionRapidity[2] = ( CrossSectionFit->Integral(3.0999,3.5999) ) / 0.50; // Least forward restricted bin
  CrossSectionRapidity[3] = ( CrossSectionFit->Integral(2.5001,3.9999) ) / 1.50; // Full          Guillermo  range
  CrossSectionRapidity[4] = ( CrossSectionFit->Integral(2.5001,2.9999) ) / 0.50; // Most  forward Guillermo  bin
  CrossSectionRapidity[5] = ( CrossSectionFit->Integral(3.0001,3.4999) ) / 0.50; // Central       Guillermo  bin
  CrossSectionRapidity[6] = ( CrossSectionFit->Integral(3.4999,3.9999) ) / 0.50; // Least forward Guillermo  bin
  // CrossSectionRapidity[7] = ( CrossSectionFit->Integral(2.5001,3.2499) ) / 0.75; // Forward  half Guillermo  bin
  // CrossSectionRapidity[8] = ( CrossSectionFit->Integral(3.2499,3.9999) ) / 0.75; // LeastFWD half Guillermo  bin



  CrossSectionRapidity[7]  = ( CrossSectionFit->Integral(2.5001,3.2499) ) / 0.75; // Forward  half Guillermo  bin
  CrossSectionRapidity[8]  = ( CrossSectionFit->Integral(3.2499,3.9999) ) / 0.75; // LeastFWD half Guillermo  bin

  CrossSectionRapidity[9]  = ( CrossSectionFit->Integral(2.5001,2.9999) ) / 0.50; // LeastFWD half Guillermo  bin
  CrossSectionRapidity[10] = ( CrossSectionFit->Integral(3.0001,3.4999) ) / 0.50; // LeastFWD half Guillermo  bin
  CrossSectionRapidity[11] = ( CrossSectionFit->Integral(3.5001,3.9999) ) / 0.50; // LeastFWD half Guillermo  bin

  CrossSectionRapidity[12] = ( CrossSectionFit->Integral(2.5001,2.8749) ) / 0.375;
  CrossSectionRapidity[13] = ( CrossSectionFit->Integral(2.8751,3.2499) ) / 0.375;
  CrossSectionRapidity[14] = ( CrossSectionFit->Integral(3.2501,3.6249) ) / 0.375;
  CrossSectionRapidity[15] = ( CrossSectionFit->Integral(3.6251,3.9999) ) / 0.375;

  CrossSectionRapidity[16] = ( CrossSectionFit->Integral(2.5001,2.7999) ) / 0.3;
  CrossSectionRapidity[17] = ( CrossSectionFit->Integral(2.8001,3.0999) ) / 0.3;
  CrossSectionRapidity[18] = ( CrossSectionFit->Integral(3.1001,3.3999) ) / 0.3;
  CrossSectionRapidity[19] = ( CrossSectionFit->Integral(3.4001,3.6999) ) / 0.3;
  CrossSectionRapidity[20] = ( CrossSectionFit->Integral(3.7001,3.9999) ) / 0.3;

  for( Int_t iLoop = 0; iLoop < 40; iLoop++) {
    cout << "CrossSectionRapidity[" << iLoop << "]  =  " << CrossSectionRapidity[iLoop] << endl;
  }

}











//_____________________________________________________________________________
/* - Computes the Cross section in p-Pb.
 * -
 */
void CrossSectionStarlightpPb(){

  Double_t  RapidityValues[] = { 2.45, 2.55, 2.65, 2.75, 2.85, 2.95,
                                 3.05, 3.15, 3.25, 3.35, 3.45,
                                 3.55, 3.65, 3.75, 3.85, 3.95, 4.05 };

  Double_t  CrossSection[]     = { 10.4513, 10.2791, 10.1059, 9.9318, 9.7570,
                                   9.5814,  9.4052,   9.2284, 9.0512, 8.8735,
                                   8.6953,  8.5168,   8.3378, 8.1583, 7.9784,
                                   7.7979,  7.6167 };
  // Double_t  CrossSection[]     = { 8.8316,  8.6534,   8.4747, 8.2956, 8.1161,
  //                                  7.9360,  7.7553,   7.5741, 7.3921, 7.2093,
  //                                  7.0255,  6.8407,   6.6547, 6.4674, 6.2785,
  //                                  6.0879,  5.8954 };


  TH1F*     CrossSectionH      = new TH1F( "CrossSectionH" , "CrossSectionH", 17, 2.4, 4.1 );
  for ( Int_t i = 0; i < 17; i++) {
    CrossSectionH->SetBinContent( i+1, CrossSection[i] );
    CrossSectionH->SetBinError(   i+1, 0.0001             );
  }
  TCanvas* CrossSectionCanvas = new TCanvas("CrossSectionCanvas","CrossSectionCanvas",900,800);
  CrossSectionH->SetLineColor(kBlue);
  CrossSectionH->SetLineStyle(kSolid);
  CrossSectionH->SetLineWidth(3);
  CrossSectionH->SetMarkerStyle(kFullCircle);
  CrossSectionH->SetMarkerColor(kBlue);
  CrossSectionH->SetMarkerSize(1);
  CrossSectionH->Draw("ep");

  TF1*     CrossSectionFit       = new TF1(     "CrossSectionFit", "pol3", 2.35, 4.15 );
  CrossSectionFit->FixParameter( 0,  14.3685  );
  CrossSectionFit->FixParameter( 1, -1.44526  );
  CrossSectionFit->FixParameter( 2, -0.0747131  );
  CrossSectionFit->FixParameter( 3,  0.00492785  );
  CrossSectionFit->SetLineColor(kMagenta);
  CrossSectionFit->SetLineStyle(kSolid);
  CrossSectionFit->SetLineWidth(3);
  CrossSectionFit->SetMarkerStyle(kFullCircle);
  CrossSectionFit->SetMarkerColor(kMagenta);
  CrossSectionFit->SetMarkerSize(1);
  CrossSectionFit->Draw("same");


  Double_t CrossSectionRapidity[40] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0};

  CrossSectionRapidity[0] = ( CrossSectionFit->Integral(2.6001,3.5999) ) / 1.00; // Full          restricted range
  CrossSectionRapidity[1] = ( CrossSectionFit->Integral(2.6001,3.0999) ) / 0.50; // Most  forward restricted bin
  CrossSectionRapidity[2] = ( CrossSectionFit->Integral(3.0999,3.5999) ) / 0.50; // Least forward restricted bin
  CrossSectionRapidity[3] = ( CrossSectionFit->Integral(2.5001,3.9999) ) / 1.50; // Full          Guillermo  range
  CrossSectionRapidity[4] = ( CrossSectionFit->Integral(2.5001,2.9999) ) / 0.50; // Most  forward Guillermo  bin
  CrossSectionRapidity[5] = ( CrossSectionFit->Integral(3.0001,3.4999) ) / 0.50; // Central       Guillermo  bin
  CrossSectionRapidity[6] = ( CrossSectionFit->Integral(3.4999,3.9999) ) / 0.50; // Least forward Guillermo  bin
  // CrossSectionRapidity[7] = ( CrossSectionFit->Integral(2.5001,3.2499) ) / 0.75; // Forward  half Guillermo  bin
  // CrossSectionRapidity[8] = ( CrossSectionFit->Integral(3.2499,3.9999) ) / 0.75; // LeastFWD half Guillermo  bin



  CrossSectionRapidity[7]  = ( CrossSectionFit->Integral(2.5001,3.2499) ) / 0.75; // Forward  half Guillermo  bin
  CrossSectionRapidity[8]  = ( CrossSectionFit->Integral(3.2499,3.9999) ) / 0.75; // LeastFWD half Guillermo  bin

  CrossSectionRapidity[9]  = ( CrossSectionFit->Integral(2.5001,2.9999) ) / 0.50; // LeastFWD half Guillermo  bin
  CrossSectionRapidity[10] = ( CrossSectionFit->Integral(3.0001,3.4999) ) / 0.50; // LeastFWD half Guillermo  bin
  CrossSectionRapidity[11] = ( CrossSectionFit->Integral(3.5001,3.9999) ) / 0.50; // LeastFWD half Guillermo  bin

  CrossSectionRapidity[12] = ( CrossSectionFit->Integral(2.5001,2.8749) ) / 0.375;
  CrossSectionRapidity[13] = ( CrossSectionFit->Integral(2.8751,3.2499) ) / 0.375;
  CrossSectionRapidity[14] = ( CrossSectionFit->Integral(3.2501,3.6249) ) / 0.375;
  CrossSectionRapidity[15] = ( CrossSectionFit->Integral(3.6251,3.9999) ) / 0.375;

  CrossSectionRapidity[16] = ( CrossSectionFit->Integral(2.5001,2.7999) ) / 0.3;
  CrossSectionRapidity[17] = ( CrossSectionFit->Integral(2.8001,3.0999) ) / 0.3;
  CrossSectionRapidity[18] = ( CrossSectionFit->Integral(3.1001,3.3999) ) / 0.3;
  CrossSectionRapidity[19] = ( CrossSectionFit->Integral(3.4001,3.6999) ) / 0.3;
  CrossSectionRapidity[20] = ( CrossSectionFit->Integral(3.7001,3.9999) ) / 0.3;

  for( Int_t iLoop = 0; iLoop < 40; iLoop++) {
    cout << "CrossSectionRapidity[" << iLoop << "]  =  " << CrossSectionRapidity[iLoop] << endl;
  }

}
