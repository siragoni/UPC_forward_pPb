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
/* - Computes the Photon Flux.
 * -
 */
void PhotonFlux(){

  Double_t  RapidityValues[] = { 2.45, 2.55, 2.65, 2.75, 2.85, 2.95,
                                 3.05, 3.15, 3.25, 3.35, 3.45,
                                 3.55, 3.65, 3.75, 3.85, 3.95, 4.05 };

  Double_t  PhotonFlux[]     = { 3.3078E+01, 3.0390E+01, 2.7768E+01, 2.5213E+01, 2.2759E+01,
                                 2.0368E+01, 1.8123E+01, 1.5930E+01, 1.3938E+01, 1.1976E+01,
                                 1.0275E+01, 8.6080E+00, 7.1948E+00, 5.8509E+00, 4.7321E+00,
                                 3.7158E+00, 2.8827E+00 };

  TH1F*     PhotonFluxH      = new TH1F( "PhotonFluxH" , "PhotonFluxH", 17, 2.4, 4.1 );
  for ( Int_t i = 0; i < 17; i++) {
    PhotonFluxH->SetBinContent( i+1, PhotonFlux[i] );
    PhotonFluxH->SetBinError(   i+1, 0.1             );
  }
  TCanvas* PhotonFluxCanvas = new TCanvas("PhotonFluxCanvas","PhotonFluxCanvas",900,800);
  PhotonFluxH->SetLineColor(kBlue);
  PhotonFluxH->SetLineStyle(kSolid);
  PhotonFluxH->SetLineWidth(3);
  PhotonFluxH->SetMarkerStyle(kFullCircle);
  PhotonFluxH->SetMarkerColor(kBlue);
  PhotonFluxH->SetMarkerSize(1);
  PhotonFluxH->Draw("ep");

  // TCanvas* PhotonFluxFitCanvas = new TCanvas( "PhotonFluxFitCanvas","PhotonFluxFitCanvas",900,800);
  TF1*     PhotonFluxFit       = new TF1(     "PhotonFluxFit", "pol3", 2.35, 4.15 );
  PhotonFluxFit->FixParameter( 0, 101.902   );
  PhotonFluxFit->FixParameter( 1, -21.17    );
  PhotonFluxFit->FixParameter( 2,  -5.9056  );
  PhotonFluxFit->FixParameter( 3,   1.25871 );
  PhotonFluxFit->SetLineColor(kMagenta);
  PhotonFluxFit->SetLineStyle(kSolid);
  PhotonFluxFit->SetLineWidth(3);
  PhotonFluxFit->SetMarkerStyle(kFullCircle);
  PhotonFluxFit->SetMarkerColor(kMagenta);
  PhotonFluxFit->SetMarkerSize(1);
  PhotonFluxFit->Draw("same");


  Double_t PhotonFluxRapidity[40] = {0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0};

  PhotonFluxRapidity[0] = ( PhotonFluxFit->Integral(2.6001,3.5999) ) / 1.00; // Full          restricted range
  PhotonFluxRapidity[1] = ( PhotonFluxFit->Integral(2.6001,3.0999) ) / 0.50; // Most  forward restricted bin
  PhotonFluxRapidity[2] = ( PhotonFluxFit->Integral(3.0999,3.5999) ) / 0.50; // Least forward restricted bin
  PhotonFluxRapidity[3] = ( PhotonFluxFit->Integral(2.5001,3.9999) ) / 1.50; // Full          Guillermo  range
  PhotonFluxRapidity[4] = ( PhotonFluxFit->Integral(2.5001,2.9999) ) / 0.50; // Most  forward Guillermo  bin
  PhotonFluxRapidity[5] = ( PhotonFluxFit->Integral(3.0001,3.4999) ) / 0.50; // Central       Guillermo  bin
  PhotonFluxRapidity[6] = ( PhotonFluxFit->Integral(3.4999,3.9999) ) / 0.50; // Least forward Guillermo  bin

  PhotonFluxRapidity[7]  = ( PhotonFluxFit->Integral(2.5001,3.2499) ) / 0.75; // Forward  half Guillermo  bin
  PhotonFluxRapidity[8]  = ( PhotonFluxFit->Integral(3.2499,3.9999) ) / 0.75; // LeastFWD half Guillermo  bin

  PhotonFluxRapidity[9]  = ( PhotonFluxFit->Integral(2.5001,2.9999) ) / 0.50; // LeastFWD half Guillermo  bin
  PhotonFluxRapidity[10] = ( PhotonFluxFit->Integral(3.0001,3.4999) ) / 0.50; // LeastFWD half Guillermo  bin
  PhotonFluxRapidity[11] = ( PhotonFluxFit->Integral(3.5001,3.9999) ) / 0.50; // LeastFWD half Guillermo  bin

  PhotonFluxRapidity[12] = ( PhotonFluxFit->Integral(2.5001,2.8749) ) / 0.375;
  PhotonFluxRapidity[13] = ( PhotonFluxFit->Integral(2.8751,3.2499) ) / 0.375;
  PhotonFluxRapidity[14] = ( PhotonFluxFit->Integral(3.2501,3.6249) ) / 0.375;
  PhotonFluxRapidity[15] = ( PhotonFluxFit->Integral(3.6251,3.9999) ) / 0.375;

  PhotonFluxRapidity[16] = ( PhotonFluxFit->Integral(2.5001,2.7999) ) / 0.3;
  PhotonFluxRapidity[17] = ( PhotonFluxFit->Integral(2.8001,3.0999) ) / 0.3;
  PhotonFluxRapidity[18] = ( PhotonFluxFit->Integral(3.1001,3.3999) ) / 0.3;
  PhotonFluxRapidity[19] = ( PhotonFluxFit->Integral(3.4001,3.6999) ) / 0.3;
  PhotonFluxRapidity[20] = ( PhotonFluxFit->Integral(3.7001,3.9999) ) / 0.3;


  for( Int_t iLoop = 0; iLoop < 40; iLoop++) {
    cout << "PhotonFluxRapidity[" << iLoop << "]  =  " << PhotonFluxRapidity[iLoop] << endl;
  }

}
