#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TMath.h"
#include "TF1.h"
#include "TLatex.h"
#include "TString.h"
using namespace std;
#include <math.h>
#include <vector>


//_____________________________________________________________________________
/* - Drawing function for the invariant mass distributions' retrieved valued,
   - after the fit in terms of CosTheta bins.
   -
 */
void CrossSectionpPb(){
  TCanvas *c2 = new TCanvas("c2","c2",600,400);
  TGraphErrors *MyCross;
  TGraphErrors *GuillermoCross;
  // Double_t DSigmaDy[6]   = { 0,0,0, 40.5, 34.0, 47.7 }; // low energy points from Guillermo
  Double_t DSigmaDy[6]   = { 0,0,0, 0,0,0 };
  Double_t DSigmaDyG[6]  = { 197,264,161, 40.5, 34.0, 47.7 };
  // Double_t fI            = 0.05;
  // Double_t fI            = 0.1;
  Double_t fI[6]         = { 0.147, 0.159, 0.162, 0.280, 0.369, 0.257};

  // Double_t errfICMUP6[6]      = { 0,0,0,0,0,0 };

  Double_t fD           = 0.1;
  // Double_t eJPsi[3]     = { 0.0640315, 0.0687199, 0.0598623 }; //only high-energy
  // Double_t eJPsi[6]     = { 0.0640315, 0.0687199, 0.0598623, 0.0600904, 0.0655808, 0.0555481 }; // ADA multi only on the low energy points
  Double_t eJPsi[6]     = { 0.16615, 0.178904, 0.154624, 0.179281, 0.196098, 0.165342 }; // AD decisions and proper trigger
  // Double_t eJPsi[6]     = { 0.0640315, 0.0687199, 0.0598623, 0.0600904, 0.0655808, 0.0555481 }; // ADA multi only on the low energy points
  // Double_t eJPsi[3]     = { 0.065, 0.065, 0.065 };
  // Double_t LUMI         = 7.917604;
  Double_t LUMI         = 11.919683898;
  Double_t LUMIlowenergy= 7.108161537;
  Double_t BR           = 0.05961;
  // Double_t NumOfJPsi[3] = { 197.0,  88.0, 106.0  };
  // Double_t Starlight[3] = { 17.0,  12.0, 22.8 };
  // Double_t NumOfJPsi[6] = { 197.0,  88.0, 106.0, 547.0, 281.0, 268.0  };
  Double_t NumOfJPsi[6] = { 682.0, 317.0, 365.0, 1032.0, 555.0, 480.0  };
  // Double_t NumOfJPsi[6] = { 682.0, 317.0, 365.0, 719.0, 389.0, 332.0  };
  // Double_t NumOfJPsi[6] = { 528.0, 252.0, 276.0, 719.0, 389.0, 332.0  };
  Double_t Starlight[6] = { 17.0,  12.0, 22.8, 204.0, 211.7, 196.1 }; // pure output.txt
  // Double_t Starlight[6] = { 17.5,  12.17, 22.83, 203.866, 211.715, 196.018 };

  // for( Int_t iLoop = 0; iLoop < 3; iLoop++ ){
  //     DSigmaDy[iLoop] = NumOfJPsi[iLoop]/( (1+fI+fD)*eJPsi[iLoop]*Starlight[iLoop]*BR*LUMI*0.5 );
  // }
  for( Int_t iLoop = 0; iLoop < 6; iLoop++ ){
      DSigmaDy[iLoop] = NumOfJPsi[iLoop]/( (1+fI[iLoop]+fD)*eJPsi[iLoop]*Starlight[iLoop]*BR*LUMI*0.5 );
  }

  DSigmaDy[0] *= 0.5;
  DSigmaDy[3] *= 0.5;
  DSigmaDy[3] *= (LUMI/LUMIlowenergy);
  DSigmaDy[4] *= (LUMI/LUMIlowenergy);
  DSigmaDy[5] *= (LUMI/LUMIlowenergy);

  // DSigmaDy[0] *= 1.19;
  // DSigmaDy[1] *= 1.19;
  // DSigmaDy[2] *= 1.19;


  Double_t x1Mine[6]      = { 945,   1072, 834, 42.1, 37.6, 48.3 }; // starlight values
  // Double_t x1Mine[6]      = { 954.663,   1074.82, 834.506, 42.1, 37.6, 48.3 }; // integral  values
  Double_t x1Guillermo[6] = { 942.4, 1189, 834, 41.2, 33.1, 48.2 };
  // Double_t y1Error[6]     = { TMath::Sqrt( ( 19.0* 19.0/(197.0*197.0))  )*DSigmaDy[0],
  //                             TMath::Sqrt( ( 13.0* 13.0/(88.0 *88.0))  )*DSigmaDy[1],
  //                             TMath::Sqrt( ( 11.0* 11.0/(106.0*106.0))  )*DSigmaDy[2],
  //                             1.3,
  //                             2.1,
  //                             1.5
  //                             };
  // Double_t y1Error[6]     = { TMath::Sqrt( ( 19.0* 19.0/(197.0*197.0))  )*DSigmaDy[0],
  Double_t y1Error[6]     = { TMath::Sqrt( ( 36.0* 36.0/(682.0*682.0))  )*DSigmaDy[0],
                              TMath::Sqrt( ( 24.0* 24.0/(317.0*317.0))   )*DSigmaDy[1],
                              TMath::Sqrt( ( 26.0* 26.0/(365.0*365.0))  )*DSigmaDy[2],
                              TMath::Sqrt( ( 44.0* 44.0/(1032.0*1032.0))  )*DSigmaDy[3],
                              TMath::Sqrt( ( 32.0* 32.0/(555.0*555.0))  )*DSigmaDy[4],
                              TMath::Sqrt( ( 31.0* 31.0/(480.0*480.0))  )*DSigmaDy[5],
                              };

  // Double_t x1Error[3]     = {  (3.6-2.6)/6, (4-2.5)/6, (4-2.5)/6 };
  Double_t y1ErrorG[6]    = { 12.5,
                              25.1,
                              12.9,
                              1.3,
                              2.1,
                              1.5
                              };
  Double_t x1Error[6]     = { 0,0,0,0,0,0 };

  MyCross        = new TGraphErrors(6, x1Mine,      DSigmaDy,  x1Error, y1Error);
  GuillermoCross = new TGraphErrors(6, x1Guillermo, DSigmaDyG, x1Error, y1ErrorG);

  TMultiGraph *mg = new TMultiGraph();
  MyCross->SetMarkerStyle(20);
  MyCross->SetMarkerColor(2);
  MyCross->SetLineColor(2);
  mg->Add(MyCross);
  GuillermoCross->SetMarkerStyle(20);
  GuillermoCross->SetMarkerColor(3);
  GuillermoCross->SetLineColor(3);
  mg->Add(GuillermoCross);

  MyCross       ->SetTitle("ADC multiplicity = 0");
  GuillermoCross->SetTitle("Previous analyses");


  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("W_{#gamma p}");
  mg->GetXaxis()->SetTitleOffset(1.25);
  mg->GetYaxis()->SetTitleOffset(1.25);
  mg->GetXaxis()->SetRangeUser(10, 10000);
  mg->GetYaxis()->SetRangeUser(10, 1000);
  mg->GetYaxis()->SetTitle("#sigma(#gamma p #rightarrow J/#psi p) [nb]");

  TF1* UpperBand = new TF1("UpperBand", "75.9*TMath::Power((x/90.0), 0.70)", 10, 10000);
  TF1* LowerBand = new TF1("LowerBand", "67.7*TMath::Power((x/90.0), 0.70)", 10, 10000);
  UpperBand->Draw("same");
  LowerBand->Draw("same");
  // Change the axis limits
  gPad->BuildLegend();
  // gPad->GetXaxis()->SetRangeUser(10, 10000);
  // gPad->GetYaxis()->SetRangeUser(10, 1000);
  gPad->SetGrid();
  // gPad->SetLogy();
  gPad->SetLogx();
  gPad->SetLogy();
  gPad->Modified();
  // mg->GetXaxis()->SetLimits(-1., 1.);
  // mg->SetMinimum(0.);
  // mg->SetMaximum(6000.);
  // c2->Print("pngResults/MultiGraph1Dview.png");
  // mg->Draw("a fb l3d");
  // c2->Print("pngResults/MultiGraph2Dview.png");
  // return c2;

  // cout << "0N0N : " << endl << DSigmaDy0N0N[0] << endl << DSigmaDy0N0N[1] << endl << DSigmaDy0N0N[2] << endl;
  // cout << "0NXN : " << endl << DSigmaDy0NXN[0] << endl << DSigmaDy0NXN[1] << endl << DSigmaDy0NXN[2] << endl;
  // cout << "XN0N : " << endl << DSigmaDyXN0N[0] << endl << DSigmaDyXN0N[1] << endl << DSigmaDyXN0N[2] << endl;
  // cout << "XNXN : " << endl << DSigmaDyXNXN[0] << endl << DSigmaDyXNXN[1] << endl << DSigmaDyXNXN[2] << endl;
  //
  // cout << "0N0N E: " << endl << y1Error0N0N[0] << endl << y1Error0N0N[1] << endl << y1Error0N0N[2] << endl;
  // cout << "0NXN E: " << endl << y1Error0NXN[0] << endl << y1Error0NXN[1] << endl << y1Error0NXN[2] << endl;
  // cout << "XN0N E: " << endl << y1ErrorXN0N[0] << endl << y1ErrorXN0N[1] << endl << y1ErrorXN0N[2] << endl;
  // cout << "XNXN E: " << endl << y1ErrorXNXN[0] << endl << y1ErrorXNXN[1] << endl << y1ErrorXNXN[2] << endl;

  cout << "Mine : " << endl << DSigmaDy[0] << " +/- " << y1Error[0] << endl << DSigmaDy[1] << " +/- " << y1Error[1]  << endl << DSigmaDy[2] << " +/- " << y1Error[2] << endl;
  cout << "Mine : " << endl << DSigmaDy[3] << " +/- " << y1Error[3] << endl << DSigmaDy[4] << " +/- " << y1Error[4]  << endl << DSigmaDy[5] << " +/- " << y1Error[5] << endl;


  // new TCanvas;
  // Double_t Ratio[3]  = { 0,0,0 };
  // Double_t Error[3]  = { 0,0,0 };
  // for (size_t i = 0; i < 3; i++) {
  //   Ratio[i] = DSigmaDy0NXN[i] / DSigmaDyXN0N[i];
  //   Error[i] = y1Error0NXN[i]  + y1ErrorXN0N[i];
  // }
  // TGraphErrors* RatioPlot = new TGraphErrors(3, x1, Ratio, x1Error, Error);
  // RatioPlot->Draw("APL");
  // RatioPlot->GetXaxis()->SetTitle("y");
  // RatioPlot->GetYaxis()->SetTitle("Ratio [au]");
  // // Change the axis limits
  // gPad->BuildLegend();
  // gPad->Modified();

}
