#include "env.h"
#include "TPad.h"
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TLatex.h"
TH1F* hPt;
TH1F* h1c;
TH1F* h1i;
TH1F* hfc;
TH1F* hfi;
TH1F* hgl;
TH1F* hun;
TF1* fgu;

double ffsum(double *x, double *par){
  Double_t pt=x[0];
  Double_t n1c=par[0];
  Double_t n1i=par[1];
  Double_t ngl=par[2];
  Double_t fd =par[3];
  Double_t nun=par[4];
  Double_t sum=0;
  sum+=hgl->GetBinContent(hgl->FindFixBin(pt))*ngl;
  sum+=h1c->GetBinContent(h1c->FindFixBin(pt))*n1c;
  sum+=h1i->GetBinContent(h1i->FindFixBin(pt))*n1i;
  // sum+=hfc->GetBinContent(hfc->FindFixBin(pt))*n1c*fd;
  sum+=hfi->GetBinContent(hfi->FindFixBin(pt))*n1i*fd;
  sum+=hun->GetBinContent(hun->FindFixBin(pt))*nun;
  return sum;
}

void fitPt( const char* AnalysisName, const int selectionFlag, Double_t rSigma2s1s = 0.150 ){
  SetStyle();
  gStyle->SetLineScalePS(2);
  // TFile* feff = new TFile(Form("efficiency%s.root", suffix.Contains("15") ? "15" : (suffix.Contains("18") ? "18" : "")));
  // TH1D* hEff1cM = (TH1D*) feff->Get(Form("h1cEffM%i",iy));
  // TH1D* hEfffcM = (TH1D*) feff->Get(Form("hfcEffM%i",iy));
  double brfd = 0.614;
  // double eff1c_m = hEff1cM->GetBinContent(im+1);
  // double efffd_m = hEfffcM->GetBinContent(im+1);
  double fd = 0.1;





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
  hPt->Draw("PE");


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

  // hPt->Rebin(2);
  // h1c->Rebin(2);
  // h1i->Rebin(2);
  // // hfc->Rebin(2);
  // hfi->Rebin(2);
  // hgl->Rebin(2);


  hPt->Sumw2();





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

  h1c->Scale(1./h1c->Integral(1,h1c->GetNbinsX()));
  h1i->Scale(1./h1i->Integral(1,h1i->GetNbinsX()));
  // hfc->Scale(1./hfc->Integral(1,hfc->GetNbinsX()));
  hfi->Scale(1./hfi->Integral(1,hfi->GetNbinsX()));
  hgl->Scale(1./hgl->Integral(1,hgl->GetNbinsX()));
  hun->Scale(1./hun->Integral(1,hun->GetNbinsX()));

  h1c->SetLineColor(kBlue);
  h1i->SetLineColor(kRed);
  // hfc->SetLineColor(kCyan);
  hfi->SetLineColor(kYellow+1);
  hgl->SetLineColor(kGreen);
  hun->SetLineColor(kMagenta);

  h1c->SetMarkerColor(kBlue);
  h1i->SetMarkerColor(kRed);
  // hfc->SetMarkerColor(kCyan);
  hfi->SetMarkerColor(kYellow+1);
  hgl->SetMarkerColor(kGreen);
  hun->SetMarkerColor(kMagenta);

  h1c->SetLineWidth(2);
  h1i->SetLineWidth(2);
  // hfc->SetLineWidth(2);
  hfi->SetLineWidth(2);
  hgl->SetLineWidth(2);
  hun->SetLineWidth(2);

  // // Get expected number of gg events from invariant mass fit (with pt cut)
  // TFile* ffitM = new TFile("fitM.root");
  // TH1D* hM = (TH1D*) ffitM->Get(Form("%s_%i_0_4",suffix.Data(),iy));
  // TF1* fBG = (TF1*) hM->GetListOfFunctions()->FindObject("fBG");
  // Double_t n_val = fBG->Integral(gMMin[im]+0.001,gMMax[im]-0.001,1e-5)/hM->GetBinWidth(1);
  // Double_t n_err = fBG->GetParError(0)/fBG->GetParameter(0)*n_val;
  // if (debug==2) n_val+=n_err;
  // if (debug==3) n_val-=n_err;
  // printf("nbg=%f\n",n_val);
  // // Estimate fraction of gg events below pt cut
  // Double_t ngl = n_val/hgl->Integral(1,hgl->FindFixBin(gPtMax[0]))*hgl->Integral(1,hgl->GetNbinsX());

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



  // TF1* fsum = new TF1("fsum",ffsum,0,4,5);
  TF1* fsum = new TF1("fsum",ffsum,0,1.6,5);
  // fsum->SetNpx(nBinsX);
  fsum->SetNpx(1000);
  fsum->SetParameter(0,10);
  fsum->SetParLimits(0,0,100);
  fsum->SetParameter(1,1000);
  fsum->FixParameter(2,ngl);
  fsum->FixParameter(3,fd);
  fsum->SetParameter(4,10);
  // hPt->Fit(fsum,debug?"":"Q");
  // hPt->Fit(fsum,"LQ");
  hPt->Fit(fsum,"LRM");

  Double_t n1c     = fsum->GetParameter(0);
  Double_t n1i     = fsum->GetParameter(1);
  Double_t nun     = fsum->GetParameter(4);
  Double_t n1c_err = fsum->GetParError(0);
  Double_t n1i_err = fsum->GetParError(1);

  Double_t chi2ndf = fsum->GetChisquare()/fsum->GetNDF();
  printf("chi2/ndf=%.2f\n",chi2ndf);
  printf("chi2    =%.2f\n",fsum->GetChisquare());
  printf("ndf     =%.2d\n",fsum->GetNDF());
  h1c->Scale(n1c);
  h1i->Scale(n1i);
  // hfc->Scale(n1c*fd);
  hfi->Scale(n1i*fd);
  hgl->Scale(ngl);
  hun->Scale(nun);

//  hPt->SetTitle(Form("%s, %.1f < y <%.1f, %.2f < M (GeV/#it{c}^{2}) < %.2f, fd=%.2f\n",suffix.Data(),gYMin[iy],gYMax[iy],gMMin[im],gMMax[im],fd));
  hPt->SetTitle("");
  hPt->GetYaxis()->SetTitle(Form("Counts per %.0f MeV/#it{c}",1000*hPt->GetBinWidth(1)));
  hPt->GetXaxis()->SetTitle("Dimuon #it{p}_{T} (GeV/#it{c})");

//   TFile* fout = new TFile("fitPt.root","update");
//   h1c->Write(Form("h1c_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
//   h1i->Write(Form("h1i_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
//   hfc->Write(Form("hfc_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
//   hfi->Write(Form("hfi_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
//   hgl->Write(Form("hgl_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
//   hun->Write(Form("hun_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
//   hPt->Write(Form("hPt_%s_%i_%i_%.0f_%s",suffix.Data(),iy,im,rSigma2s1s*1000,debug>1 ? Form("%i",debug) : ""),TObject::kOverwrite);
// //  fsum->Write(Form("fitPt_%s_%i_%i_%i",suffix.Data(),iy,im,ipt),TObject::kOverwrite);
//   fout->Close();

  // if (!debug) return;

  TCanvas* c = new TCanvas("c","c",285*3,750);
  c->SetRightMargin(0.01);
  c->SetLeftMargin(0.12);
  c->SetTopMargin(0.01);
  c->SetBottomMargin(0.11);

  hPt->SetLineColor(kBlack);
  hPt->SetMarkerStyle(kFullCircle);
  hPt->SetMarkerSize(0.8);
  fsum->SetLineColor(kBlack);
//
  Bool_t log=1;
  if (log) {
    // gPad->SetLogy();
    hPt->GetXaxis()->SetRangeUser(0,1.7);
    hPt->SetMaximum(hPt->GetBinContent(hPt->GetMaximumBin())*1.2);
    hPt->SetMinimum(0.);
  } else {
    gPad->SetLeftMargin(0.14);
    hPt->GetXaxis()->SetRangeUser(0,1.5);
    hPt->GetYaxis()->SetTitleOffset(1.7);
    hPt->SetMaximum(hPt->GetBinContent(hPt->GetMaximumBin())*1.2);
    hPt->SetMinimum(0.);
  }
  hPt->GetXaxis()->SetTitleOffset(1.17);
  hPt->GetXaxis()->SetTitleSize(0.046);
  hPt->GetYaxis()->SetTitleSize(0.0468);

  hPt->GetListOfFunctions()->Clear();
  hPt->SetMaximum(hPt->GetMaximum()*1.3);
  hPt->Draw("e0");
  h1c->Scale(1./n1c);
  h1i->Scale(1./n1i);
  // hfc->Scale(1./n1c/fd);
  hfi->Scale(1./n1i/fd);
  hgl->Scale(1./ngl);
  hun->Scale(1./nun);
  fsum->DrawClone("same");
  h1c->Scale(n1c);
  h1i->Scale(n1i);
  // hfc->Scale(n1c*fd);
  hfi->Scale(n1i*fd);
  hgl->Scale(ngl);
  hun->Scale(nun);

  Double_t int1c = h1c->Integral(1,h1c->FindFixBin(0.999999));
  Double_t int1i = h1i->Integral(1,h1c->FindFixBin(0.999999));
  Double_t intfc = 0.0;
  // Double_t intfc = hfc->Integral(1,h1c->FindFixBin(0.999999));
  Double_t intfi = hfi->Integral(1,h1c->FindFixBin(0.999999));
  Double_t intun = hun->Integral(1,h1c->FindFixBin(0.999999));
  Double_t all = int1i+intfc+intfi+intun+int1c;
  Double_t ratio = (int1i+intfc+intfi+intun)/int1c;
  Double_t fI = (int1i+intun)/int1c;
  Double_t fD = (intfc+intfi)/int1c;
  printf("%f\n",int1c);
  printf("%f\n",int1i);
  printf("%f\n",intfc);
  printf("%f\n",intfi);
  printf("%f\n",intun);
  printf("%f\n",all);
  printf("fI = %f\n",fI);
  printf("fD = %f\n",fD);
  printf("%f\n",ratio);


  Double_t err1c = 0;
  Double_t err1i = 0;
  Double_t errun = 0;
  Double_t errfI = 0;
  // Double_t int1c = fCohJpsiToMuC  ->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.999999), err1c, "" );
  // Double_t int1i = fIncohJpsiToMuC->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.999999), err1i, "" );
  // Double_t intun = fHighPtTailC   ->IntegralAndError( 1, fCohJpsiToMuC->GetXaxis()->FindBin(0.999999), errun, "" );
  Double_t f_I   = (int1c + intun ) / int1i;

  // err1c += int1c * (fsum->GetParError(0) / fsum->GetParameter(0));
  // err1i += int1i * (fsum->GetParError(1) / fsum->GetParameter(1));
  // errun += intun * (fsum->GetParError(4) / fsum->GetParameter(4));
  err1c += fsum->GetParError(0);
  err1i += fsum->GetParError(1);
  errun += fsum->GetParError(4);

  if ( int1c < 0.0001 ) {
    err1c = 0;
    int1c = 0;
  }


  // errfI          = err1c + err1i + errun;
  Double_t RatioErrfIOverfI        = 0;
  Double_t RatioErr1cOver1c        = 0;
  Double_t RatioErrIncohOverIncoh  = 0;
  RatioErr1cOver1c                 = err1i / int1i;
  RatioErrIncohOverIncoh           = ( err1c + errun ) / ( int1c + intun );
  RatioErrfIOverfI                 = RatioErrIncohOverIncoh + RatioErr1cOver1c;
  errfI                            = RatioErrfIOverfI * f_I;
  // errfI          = (RatioErrfIOverfI + (FitPtDistr->GetParError(0) / FitPtDistr->GetParameter(0)) + (FitPtDistr->GetParError(1) / FitPtDistr->GetParameter(1)) + (FitPtDistr->GetParError(3) / FitPtDistr->GetParameter(3))) * f_I;
  // cout << "err1c = " << err1c;
  // cout << "err1i = " << err1i;
  // cout << "errun = " << errun;
  // cout << "errfI = " << errfI;
  printf("err1c = %f\n",err1c);
  printf("err1i = %f\n",err1i);
  printf("errun = %f\n",errun);
  printf("errfI = %f\n",errfI);




  hgl->SetLineColor(kGreen+2);
  // hfc->SetLineColor(kOrange-6);

  h1c->Draw("hist same");
  h1i->Draw("hist same");
  // hfc->Draw("hist same");
  hfi->Draw("hist same");
  hgl->Draw("hist same");
  hun->Draw("hist same");

  // Double_t lumi = suffix.Contains("15") ? 216 : (suffix.Contains("18") ? 538 : 754);
  Double_t lumi = 11.92;

  TLatex* latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.045);
  latex->SetTextAlign(22);
  latex->DrawLatex(0.56,0.95,Form("ALICE, Pb#minusp #sqrt{#it{s}_{NN}} = 8.16 TeV"));
  latex->DrawLatex(0.45,0.86,Form("f_{c} = #frac{%.3f + %.3f}{%.3f} = %.3f #pm %.3f", int1c, intun, int1i, f_I, errfI));
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
    TLegend* l = new TLegend(0.45,0.47,0.98,0.77);
//    TLegend* l = new TLegend(0.55,0.50,0.98,0.84);
    l->SetMargin(0.1);
    l->AddEntry(hPt,"ALICE data","p");
    l->AddEntry(fsum,Form("Fit: #chi^{2}/NDF=%.1f\n",chi2ndf),"l");
    l->AddEntry(h1c,Form("Coherent J/#psi: %.0f #pm %.0f",n1c,n1c_err));
    l->AddEntry(h1i,Form("Incoherent J/#psi: %.0f #pm %.0f",n1i,n1i_err));
    l->AddEntry(hun,Form("Incoherent dissocitive J/#psi: %.0f",nun),"l");
    // l->AddEntry(hfc,"Coherent #psi' feeddown");
    l->AddEntry(hfi,"Incoherent #psi' feeddown");
    l->AddEntry(hgl,Form("Continuum #gamma#gamma #rightarrow #mu#mu: %.0f",ngl));
    l->Draw();
  }  else {
    TLegend* l = new TLegend(0.47,0.48,0.985,0.78);
    l->SetMargin(0.09);
    l->AddEntry(hPt,"ALICE data","p");
    l->AddEntry(h1c,"Coherent J/#psi");
    l->AddEntry(h1i,"Incoherent J/#psi");
    l->AddEntry(hun,"Incoherent J/#psi with nucleon dissociation");
    // l->AddEntry(hfc,"Coherent J/#psi from #psi' decay");
    l->AddEntry(hfi,"Incoherent J/#psi from #psi' decay");
    l->AddEntry(hgl,"Continuum #gamma#gamma #rightarrow #mu#mu");
    l->AddEntry(fsum,"Sum");
    l->Draw();
  }


  gPad->SaveAs(Form("pngResults/fitPtEvgeny_%d.png", selectionFlag),  "RECREATE");


//  TLatex* latex = new TLatex();
//  latex->SetNDC();
//  latex->DrawLatex(0.1,0.2,);
//  gPad->Print(Form("fitPt_%s_%i_%i.png",suffix.Data(),iy,log));
  // gPad->Print(Form("pt%i.pdf",iy));
}
