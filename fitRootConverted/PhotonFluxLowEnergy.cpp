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

  Double_t  PhotonFlux[]     = { 1.8360E+02, 1.8672E+02, 1.8985E+02, 1.9297E+02, 1.9610E+02,
                                 1.9922E+02, 2.0234E+02, 2.0547E+02, 2.0859E+02, 2.1172E+02,
                                 2.1484E+02, 2.1797E+02, 2.2109E+02, 2.2422E+02, 2.2734E+02,
                                 2.3046E+02, 2.3359E+02 };

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
  TF1*     PhotonFluxFit       = new TF1(     "PhotonFluxFit", "pol1", 2.35, 4.15 );
  PhotonFluxFit->FixParameter( 0, 107.051   );
  PhotonFluxFit->FixParameter( 1, 31.2439    );
  PhotonFluxFit->SetLineColor(kMagenta);
  PhotonFluxFit->SetLineStyle(kSolid);
  PhotonFluxFit->SetLineWidth(3);
  PhotonFluxFit->SetMarkerStyle(kFullCircle);
  PhotonFluxFit->SetMarkerColor(kMagenta);
  PhotonFluxFit->SetMarkerSize(1);
  PhotonFluxFit->Draw("same");


  Double_t PhotonFluxRapidity[9] = {0,0,0,0,0,0,0,0,0};

  PhotonFluxRapidity[0] = ( PhotonFluxFit->Integral(2.6001,3.5999) ) / 1.00; // Full          restricted range
  PhotonFluxRapidity[1] = ( PhotonFluxFit->Integral(2.6001,3.0999) ) / 0.50; // Most  forward restricted bin
  PhotonFluxRapidity[2] = ( PhotonFluxFit->Integral(3.0999,3.5999) ) / 0.50; // Least forward restricted bin
  PhotonFluxRapidity[3] = ( PhotonFluxFit->Integral(2.5001,3.9999) ) / 1.50; // Full          Guillermo  range
  PhotonFluxRapidity[4] = ( PhotonFluxFit->Integral(2.5001,2.9999) ) / 0.50; // Most  forward Guillermo  bin
  PhotonFluxRapidity[5] = ( PhotonFluxFit->Integral(3.0001,3.4999) ) / 0.50; // Central       Guillermo  bin
  PhotonFluxRapidity[6] = ( PhotonFluxFit->Integral(3.4999,3.9999) ) / 0.50; // Least forward Guillermo  bin
  PhotonFluxRapidity[7] = ( PhotonFluxFit->Integral(2.5001,3.2499) ) / 0.75; // Forward  half Guillermo  bin
  PhotonFluxRapidity[8] = ( PhotonFluxFit->Integral(3.2499,3.9999) ) / 0.75; // LeastFWD half Guillermo  bin

  for( Int_t iLoop = 0; iLoop < 9; iLoop++) {
    cout << "PhotonFluxRapidity[" << iLoop << "]  =  " << PhotonFluxRapidity[iLoop] << endl;
  }

}
