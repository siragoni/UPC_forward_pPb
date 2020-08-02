#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
using namespace RooFit;
TH1F* hPt;
TH1F* h1c;
TH1F* h1i;
TH1F* hfc;
TH1F* hfi;
TH1F* hgl;
TH1F* hun;
TF1* fgu;




void FitPtROOFit( const char* AnalysisName, const int selectionFlag, Double_t rSigma2s1s = 0.150 )
{
  // ---------------------------------------------------
  // I m p o r t i n g   R O O T   h i s t o g r a m s
  // ===================================================
  // I m p o r t   T H 1   i n t o   a   R o o D a t a H i s t
  // ---------------------------------------------------------
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
  TList* listings;
  dir->GetObject("MyOutputContainer", listings);
  TList* listingsMC[8];
  for(Int_t iDirectory = 0; iDirectory < 8; iDirectory++) {
    if (iDirectory == 1 || iDirectory == 2) continue;
    dirMC[iDirectory]->GetObject("MyOutputContainer", listingsMC[iDirectory]);
  }
  h1c = (TH1F*)listingsMC[0]->FindObject("fTemplatePtDistributionH");
  // fCohPsi2sToMu       = (TH1F*)listingsMC[1]->FindObject("fTemplatePtDistributionH");
  // fCohPsi2sToMuPi     = (TH1F*)listingsMC[2]->FindObject("fTemplatePtDistributionH");
  h1i = (TH1F*)listingsMC[3]->FindObject("fTemplatePtDistributionH");
  hfi = (TH1F*)listingsMC[4]->FindObject("fTemplatePtDistributionH");
  // fIncohPsi2sToMuPi   = (TH1F*)listingsMC[5]->FindObject("fTemplatePtDistributionH");
  hgl = (TH1F*)listingsMC[6]->FindObject("fTemplatePtDistributionH");
  // fTwoGammaToMuHigh   = (TH1F*)listingsMC[7]->FindObject("fTemplatePtDistributionH");

  if      ( selectionFlag == 0 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionH");
  // else if ( selectionFlag == 1 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCzeroZNAzeroH");
  // else if ( selectionFlag == 2 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCzeroZNAanyH");
  // else if ( selectionFlag == 3 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCanyZNAzeroH");
  // else if ( selectionFlag == 4 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZNCanyZNAanyH");
  else if ( selectionFlag == 1 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNAH");
  else if ( selectionFlag == 2 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNAbinsH_0");
  else if ( selectionFlag == 3 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNAbinsH_1");
  else if ( selectionFlag == 4 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCH");
  else if ( selectionFlag == 5 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCbinsH_0");
  else if ( selectionFlag == 6 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCbinsH_1");
  // Run 2 settings
  else if ( selectionFlag == 7 ) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCH");
  else if ( selectionFlag == 8 ) {
    hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_0");
    hPt->Add( (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_1") );
  }
  else if ( selectionFlag == 9 ) {
    hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_2");
    hPt->Add( (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_3") );
  }
  else if ( selectionFlag == 10) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCthreebinsH_0");
  else if ( selectionFlag == 11) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCthreebinsH_1");
  else if ( selectionFlag == 12) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCthreebinsH_2");
  else if ( selectionFlag == 13) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_0");
  else if ( selectionFlag == 14) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_1");
  else if ( selectionFlag == 15) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_2");
  else if ( selectionFlag == 16) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfourbinsH_3");
  else if ( selectionFlag == 17) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_0");
  else if ( selectionFlag == 18) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_1");
  else if ( selectionFlag == 19) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_2");
  else if ( selectionFlag == 20) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_3");
  else if ( selectionFlag == 21) hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionZeroZNCfivebinsH_4");
  else                           hPt = (TH1F*)listings->FindObject("fDimuonPtDistributionH");
  // hPt->Rebin(5);
  // hPt->Rebin(2);
  // hPt->Rebin(2);
  // hPt->Draw("PE");


  hPt->Rebin(5);
  h1c->Rebin(5);
  h1i->Rebin(5);
  // hfc->Rebin(5);
  hfi->Rebin(5);
  hgl->Rebin(5);

  hPt->Rebin(2);
  h1c->Rebin(2);
  h1i->Rebin(2);
  // hfc->Rebin(2);
  hfi->Rebin(2);
  hgl->Rebin(2);

  hPt->Rebin(2);
  h1c->Rebin(2);
  h1i->Rebin(2);
  // hfc->Rebin(2);
  hfi->Rebin(2);
  hgl->Rebin(2);








  Int_t nBinsX = hPt->GetNbinsX();

  TF1* fun = new TF1("fun","[0]*x*(1+[1]/[2]*x*x)^(-[2])",0,20);
  fun->SetParameter(0,1);
  //  fun->SetParameter(1,debug==4 ? 1.25 : 1.);
  //  fun->SetParameter(2,debug==4 ? 6.1 : 1.);
  // fun->SetParameter(1,debug==4 ? 1.6 : 1.79);
  // fun->SetParameter(2,debug==4 ? 3.58 : 3.58);
  fun->SetParameter(1, 1.79);
  fun->SetParameter(2, 3.58);
  fun->SetNpx(nBinsX);
  // hun = (TH1D*) fun->GetHistogram()->Clone("hun");
  hun = (TH1F*) fun->GetHistogram()->Clone("hun");
  for (Int_t ibin=1;ibin<=hun->GetNbinsX();ibin++) hun->SetBinError(ibin,0);




  // Declare observable x
  RooRealVar pT("pT", "pT", 0, 20);
  // Create a binned dataset that imports contents of TH1 and associates its contents to observable 'x'
  RooDataHist rPt("rPt", "rPt", pT, Import(*hPt));
  RooDataHist r1c("r1c", "r1c", pT, Import(*h1c));
  RooDataHist r1i("r1i", "r1i", pT, Import(*h1i));
  RooDataHist rfi("rfi", "rfi", pT, Import(*hfi));
  RooDataHist rgl("rgl", "rgl", pT, Import(*hgl));
  RooDataHist run("run", "run", pT, Import(*hun));
  // P l o t   a n d   f i t   a   R o o D a t a H i s t
  // ---------------------------------------------------
  // Make plot of binned dataset showing Poisson error bars (RooFit default)
  // RooPlot *frame = pT.frame(Title("Dimuon pT distribution"));
  RooPlot *frame = pT.frame(0.0, 1.6);
  rPt.plotOn(frame);
  // // Fit a Gaussian p.d.f to the data
  // RooRealVar mean("mean", "mean", 0, -10, 10);
  // RooRealVar sigma("sigma", "sigma", 3, 0.1, 10);
  // RooGaussian gauss("gauss", "gauss", x, mean, sigma);
  // gauss.fitTo(dh);
  // gauss.plotOn(frame);






  RooHistPdf pdf1c("pdf1c", "pdf1c", pT, r1c, 0);
  RooHistPdf pdf1i("pdf1i", "pdf1i", pT, r1i, 0);
  RooHistPdf pdffi("pdffi", "pdffi", pT, rfi, 0);
  RooHistPdf pdfgl("pdfgl", "pdfgl", pT, rgl, 0);
  RooHistPdf pdfun("pdfun", "pdfun", pT, run, 0);








  Double_t ngl = 0.0;
  // WITHOUT ZDC
  if        ( selectionFlag == 0 ) {
    // FitPtDistr->SetParameter(1, 700);
    ngl = 40;
  } else if ( selectionFlag == 1 ) {
    // FitPtDistr->SetParameter(1, 550);
    ngl = 40;
  } else if ( selectionFlag == 2 ) {
    // FitPtDistr->SetParameter(1, 260);
    ngl = 15;
  } else if ( selectionFlag == 3 ) {
    // FitPtDistr->SetParameter(1, 290);
    ngl = 22;
  } else if ( selectionFlag == 4 ) {
    // FitPtDistr->SetParameter(1, 635);
    ngl = 40;
  } else if ( selectionFlag == 5 ) {
    // FitPtDistr->SetParameter(1, 290);
    ngl = 15;
  } else if ( selectionFlag == 6 ) {
    // FitPtDistr->SetParameter(1, 350);
    ngl = 25;
  } else if ( selectionFlag == 7 ) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 820);
    ngl = 56;
  } else if ( selectionFlag == 8 ) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 325);
    ngl = 25;
  } else if ( selectionFlag == 9 ) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 550);
    ngl = 34;
  } else if ( selectionFlag == 10) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 100);
    ngl = 12;
  } else if ( selectionFlag == 11) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 512);
    ngl = 29;
  } else if ( selectionFlag == 12) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 265);
    ngl = 19;
  } else if ( selectionFlag == 13) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 45);
    ngl =  6;
  } else if ( selectionFlag == 14) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 281);
    ngl = 19;
  } else if ( selectionFlag == 15) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 402);
    ngl = 21;
  } else if ( selectionFlag == 16) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 147);
    ngl = 14;
  } else if ( selectionFlag == 17) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 25);
    ngl =  3;
  } else if ( selectionFlag == 18) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 139);
    ngl = 14;
  } else if ( selectionFlag == 19) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 336);
    ngl = 17;
  } else if ( selectionFlag == 20) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 292);
    ngl = 15;
  } else if ( selectionFlag == 21) { // Run 2 settings
    // FitPtDistr->SetParameter(1, 84);
    ngl = 11;
  }




  RooRealVar ggN     ( "ggN",    "number of gg",        ngl); // fixed by fit to mass peak
  // RooRealVar cohN    ( "cohN",   "number of coh",       10,  0, 20 ); // free
  RooRealVar cohN    ( "cohN",   "number of coh",       7 ); // free
  RooRealVar icN     ( "icN",    "number of ic",        200, 0, 500); //free
  // RooRealVar p2scohN ( "p2scohN","number of coh p2s",   nPsiCoh); // fixed to STARLIGHT ratio
  RooRealVar p2sicN  ( "p2sicN", "number of incoh p2s", 24,  20, 28);
  RooRealVar dissoc  ( "dissoc", "number of dissoc",    30,  0, 100 );
  RooAddPdf  sum     ( "sum",    "extended sum of all",
                       RooArgList(pdf1i, pdf1c, pdffi,    pdfgl, pdfun),
                       RooArgList(icN,   cohN,  p2sicN,   ggN,   dissoc)
                       );




  RooFitResult* r = sum.fitTo(rPt,Extended(kTRUE),Save());




  sum.plotOn (frame,LineColor(kBlack), Range(0.,1.0) ) ;
  // sum.paramOn(frame);
  // sum.paramOn(frame,rPt);
  sum.plotOn (frame,Components(pdf1c), LineColor(kGreen),   Range(0,1.6)    );
  sum.plotOn (frame,Components(pdf1i), LineColor(kRed),     Range(0,1.6) );
  sum.plotOn (frame,Components(pdffi), LineColor(kBlue),    Range(0,1.6)  );
  sum.plotOn (frame,Components(pdfgl), LineColor(kCyan),    Range(0,1.6)  );
  sum.plotOn (frame,Components(pdfun), LineColor(kMagenta), Range(0,1.6) );
  // sum.paramOn(frame,rPt);
  frame->Draw();



  // new TCanvas("rf201_composite", "rf201_composite", 600, 600);
  // gPad->SetLeftMargin(0.15);
  // xframe->GetYaxis()->SetTitleOffset(1.4);
  // xframe->Draw();




  // get fractions of PDF in jRecPt range [0,Pt cut]
  pT.setRange("signal",0.0,1.0);
  RooAbsReal* cohI   = pdf1c.createIntegral(pT,NormSet(pT),Range("signal")) ;
  RooAbsReal* icI    = pdf1i.createIntegral(pT,NormSet(pT),Range("signal")) ;
  // RooAbsReal* p2scohI = p2scohPdf.createIntegral(pT,NormSet(pT),Range("signal")) ;
  RooAbsReal* p2sicI = pdffi.createIntegral(pT,NormSet(pT),Range("signal")) ;
  RooAbsReal* ggI    = pdfgl.createIntegral(pT,NormSet(pT),Range("signal")) ;
  RooAbsReal* funI   = pdfun.createIntegral(pT,NormSet(pT),Range("signal")) ;
  RooAbsReal* sI     = sum.createIntegral  (pT,NormSet(pT),Range("signal")) ;





  //Calculate chi^2
  Double_t total = sum.expectedEvents(pT);
  cout << "total = " << total << endl;
  Double_t chi2 = 0;
  for( Int_t i = 0; i < nBinsX; i++){
   	pT.setRange( "bin", i*(1.0/((Double_t)nBinsX)), (i+1)*(1.0/((Double_t)nBinsX)) );
    RooAbsReal* binI   = sum.createIntegral( pT, NormSet(pT), Range("bin") );
   	Double_t fBin      = binI->getVal();
   	Double_t sumPoint  = fBin * total;
   	cout << "sumPoint" << sumPoint << " ";
   	Double_t dataPoint = hPt->GetBinContent(i+1);
   	cout <<  dataPoint << endl;
   	Double_t sqDiff    = (sumPoint - dataPoint)*(sumPoint-dataPoint);
   	cout <<  sqDiff    << endl;
   	Double_t sqError   = sumPoint;
   	Double_t chiBin    = sqDiff/sqError;
   	cout <<  chiBin    << endl;
   	chi2+=chiBin;
  }

  cout << "chi^2 =     " << chi2 << endl;
  cout << "chi^2/dof = " << chi2/((Double_t)nBinsX) << endl;

  Double_t fCoh     = cohI   ->getVal();
  Double_t fICoh    = icI    ->getVal();
  // Double_t fPsiCoh  = p2scohI->getVal();
  Double_t fPsiICoh = p2sicI ->getVal();
  Double_t fGG      = ggI    ->getVal();
  Double_t fdisso   = funI   ->getVal();


 cout << "For jRectPt<Pt cut GeV/c" << endl;
 cout << "Number of gg integrated under Pt cut: "              << ggN.getValV()    * fGG      << " +/- " << ggN.getError()    * fGG      << endl;
 // cout << "Number of coh feed-down integrated under Pt cut: " << p2scohN.getValV() * fPsiCoh << " +/- " << p2scohN.getError() * fPsiCoh << endl;
 cout << "Number of incoh feed-down integrated under Pt cut: " << p2sicN.getValV() * fPsiICoh << " +/- " << p2sicN.getError() * fPsiICoh << endl;
 cout << "Number of incoherent integrated under Pt cut: "      << icN.getValV()    * fICoh    << " +/- " << icN.getError()    * fICoh    << endl;
 cout << "Number of coherent integrated under Pt cut: "        << cohN.getValV()   * fCoh     << " +/- " << cohN.getError()   * fCoh     << endl;
 Double_t N_coh2      = cohN.getValV()    * fCoh; //Number of coherent J/psi according to fit
 Double_t N_cohError  = cohN.getError()   * fCoh; //Error on coh J/psi according to fit
 Double_t N_I         = icN.getValV()     * fICoh; //Number of incoherent J/psi below Pt cut
 Double_t N_IError    = icN.getError()    * fICoh; //Error on inc J/psi below Pt cut
 // Double_t N_cohFD = p2scohN.getValV() * fPsiCoh; //Number of coh FD below Pt cut
 // Double_t N_cohFDError = p2scohN.getError() * fPsiCoh; //Error on coh FD < Pt cut
 Double_t N_icFD      = p2sicN.getValV()  * fPsiICoh; //Number of ic FD below Pt cut
 Double_t N_icFDError = p2sicN.getError() * fPsiICoh; //Error on ic FD below Pt cut
 Double_t N_diss      = dissoc.getValV()  * fdisso; //Number of ic FD below Pt cut
 Double_t N_dissError = dissoc.getError() * fdisso; //Error on ic FD below Pt cut

 //When cross sections and efficiencies are given for pt<Pt cut:
 //cout << "fFDcoh = " << p2scohN.getValV() * fPsiCoh/(cohN.getValV() * fCoh) << endl;
 //cout << "fFDincoh = " << p2sicN.getValV() * fPsiICoh/(cohN.getValV() * fCoh) << endl;
 //When cross sections and effeciences are given for all pt:
 // fracFDcoh = p2scohN.getValV()/cohN.getValV();
 //  fracFDic = p2sicN.getValV()/icN.getValV();
 //
 //  cout << "fFDcoh = " << fracFDcoh << ";  Target: 0.105" << endl;
 //  cout << "fFDincoh = " << fracFDic << ";  Target: 0.0993" << endl;

 cout << "****************************** " << endl;
 cout << "Fractions of the templates under Pt=Pt cut GeV/c" << endl;
 cout << "Coherent fraction " << fCoh << endl;
 cout << "Incoherent fraction " << fICoh << endl;
 // cout << "Coherent Feed-down fraction " << fPsiCoh << endl;
 cout << "Incoherent Feed-down fraction " << fPsiICoh << endl;
 cout << "Gamma+Gamma fraction " << fGG << endl;

 Double_t f_I   =  (N_coh2     + N_diss     ) / (N_I);
 Double_t ErrfI = sqrt((N_cohError + N_dissError)*(N_cohError + N_dissError) / ((N_coh2 + N_diss)*(N_coh2 + N_diss)) + (N_IError*N_IError)/(N_I*N_I) )*f_I;
 // fFD = ((p2scohN.getValV() * fPsiCoh) + (p2sicN.getValV() * fPsiICoh)) / (cohN.getValV() * fCoh);








 Double_t lumi = 11.92;

 TLatex* latex = new TLatex();
 latex->SetNDC();
 latex->SetTextSize(0.045);
 latex->SetTextAlign(22);
 latex->DrawLatex(0.56,0.95,Form("ALICE, Pb#minusp #sqrt{#it{s}_{NN}} = 8.16 TeV"));
 latex->DrawLatex(0.45,0.86,Form("f_{c} = #frac{%.3f + %.3f}{%.3f} = %.3f #pm %.3f", N_coh2, N_diss, N_I, f_I, ErrfI));
 if ( selectionFlag == 7 ) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-4.000,  -2.500));
 if ( selectionFlag == 8 ) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-4.000,  -3.250));
 if ( selectionFlag == 9 ) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.250,  -2.500));
 if ( selectionFlag == 10) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-4.000,  -3.500));
 if ( selectionFlag == 11) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.500,  -3.000));
 if ( selectionFlag == 12) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.000,  -2.500));
 if ( selectionFlag == 13) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-4.000,  -3.625));
 if ( selectionFlag == 14) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.625,  -3.250));
 if ( selectionFlag == 15) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.250,  -2.875));
 if ( selectionFlag == 16) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-2.875,  -2.500));
 if ( selectionFlag == 17) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-4.000,  -3.700));
 if ( selectionFlag == 18) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.700,  -3.400));
 if ( selectionFlag == 19) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.400,  -3.100));
 if ( selectionFlag == 20) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-3.100,  -2.800));
 if ( selectionFlag == 21) latex->DrawLatex(0.80,0.20,Form("%.3f < y < %.3f",-2.800,  -2.500));
 latex->SetTextSize(0.033);
 latex->SetTextAlign(12);
 // latex->DrawLatex(0.48,0.89,Form("UPC, L_{#lower[-0.3]{int}} = %.0f #pm %.0f #mub^{-1}",lumi,lumi*0.05));
 // latex->DrawLatex(0.48,0.85,Form("#minus%.2f < #it{y} < #minus%.2f",-gYMin[iy],-gYMax[iy]));
 // latex->DrawLatex(0.48,0.81,Form("%.2f < #it{m}_{#mu#mu} < %.2f GeV/#it{c}^{2}",gMMin[im],gMMax[im]));

 if (0) {
//    TLegend* l = new TLegend(0.45,0.47,0.98,0.77);
// //    TLegend* l = new TLegend(0.55,0.50,0.98,0.84);
//    l->SetMargin(0.1);
//    l->AddEntry(hPt,"ALICE data","p");
//    l->AddEntry(fsum,Form("Fit: #chi^{2}/NDF=%.1f\n",chi2ndf),"l");
//    l->AddEntry(h1c,Form("Coherent J/#psi: %.0f #pm %.0f",n1c,n1c_err));
//    l->AddEntry(h1i,Form("Incoherent J/#psi: %.0f #pm %.0f",n1i,n1i_err));
//    l->AddEntry(hun,Form("Incoherent dissocitive J/#psi: %.0f",nun),"l");
//    // l->AddEntry(hfc,"Coherent #psi' feeddown");
//    l->AddEntry(hfi,"Incoherent #psi' feeddown");
//    l->AddEntry(hgl,Form("Continuum #gamma#gamma #rightarrow #mu#mu: %.0f",ngl));
//    l->Draw();
 }  else {
   // TLegend* l = new TLegend(0.47,0.48,0.985,0.78);
   // l->SetMargin(0.09);
   // l->AddEntry(hPt,"ALICE data","p");
   // l->AddEntry(pdf1c,"Coherent J/#psi");
   // l->AddEntry(pdf1i,"Incoherent J/#psi");
   // l->AddEntry(pdfun,"Incoherent J/#psi with nucleon dissociation");
   // // l->AddEntry(hfc,"Coherent J/#psi from #psi' decay");
   // l->AddEntry(pdffi,"Incoherent J/#psi from #psi' decay");
   // l->AddEntry(pdfgl,"Continuum #gamma#gamma #rightarrow #mu#mu");
   // l->AddEntry(sum,"Sum");
   // l->Draw();
 }





 for (int i=0; i<frame->numItems(); i++) {
   TString obj_name=frame->nameOf(i); if (obj_name=="") continue;
   cout << Form("%d. '%s'\n",i,obj_name.Data());
 }



 TString names[] = {
   "h_rPt",
   "sum_Norm[pT]_Range[0.000000_1.000000]",
   "sum_Norm[pT]_Comp[pdf1c]_Range[0.000000_1.600000]",
   "sum_Norm[pT]_Comp[pdf1i]_Range[0.000000_1.600000]",
   "sum_Norm[pT]_Comp[pdffi]_Range[0.000000_1.600000]",
   "sum_Norm[pT]_Comp[pdfgl]_Range[0.000000_1.600000]",
   "sum_Norm[pT]_Comp[pdfun]_Range[0.000000_1.600000]",
   ""
 };

 TString signs[] = {
   "ALICE data",
   "Total fit",
   "#gamma+Pb",
   "Exclusive",
   "#gamma#gamma",
   "Non-exclusive"
 };


 TLegend* l = new TLegend(0.47,0.48,0.985,0.78);
 l->SetMargin(0.09);
 Int_t i=-1;
 while ( names[++i] != "" ) {
   TObject *obj = frame->findObject(names[i].Data());
   if (!obj) {
     Warning("fitBi4",Form("Can't find item = %s in the frame2!\n",names[i].Data()));
     continue;
   }
   l->AddEntry(obj,signs[i],"l");
 }
 l->Draw();









 gPad->SaveAs(Form("pngResults/fitPtROOFit_%d.png", selectionFlag),  "RECREATE");

}
