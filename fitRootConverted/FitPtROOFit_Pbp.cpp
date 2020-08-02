#include "RooGlobalFunc.h"
#include "RooFitResult.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"
#include "RooAbsReal.h"
#include "RooCBShape.h"
#include "RooAddPdf.h"
#include "RooNLLVar.h"
#include "RooPlot.h"
#include "RooHistPdf.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1D.h"
#include "TH1F.h"
#include "string.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace RooFit ;

void FitPtROOFit(Double_t ggYield, Double_t &nPsiCoh, Double_t &nPsiICoh, Double_t &fracFDcoh, Double_t &fracFDic, Double_t &fI, Double_t &fFD, Int_t z, Int_t y, Int_t s, Double_t &N_coh){


//
// Fits Pt distribution of data to samples of MC events

  Double_t PtCut = gPtMax;
  if(s==kSystPtCut0) PtCut=gPtMaxSyst0;
  else if(s==kSystPtCut1) PtCut = gPtMaxSyst1;
  else if(s==kSystPtCut2) PtCut = gPtMaxSyst2;
  else if(s==kSystPtCut3) PtCut = gPtMaxSyst3;
  else if(s==kSystPtCut4) PtCut = gPtMaxSyst4;

  Int_t nPtBins = gPtBins;
  Double_t PtbinShift = 0.;
  if(s==kSystPtBins12) nPtBins = gPtBins12;
  else if(s==kSystPtBins25) nPtBins = gPtBins25;
  else if(s==kSystPtBins50) nPtBins = gPtBins50;
  else if(s==kSystPtBinShift) PtbinShift = 0.02;

  // Observables
  // here you have to set the limits for the variables
  //RooRealVar m("m","di-lepton mass",2.8,3.4) ;
 // RooRealVar jRecM("jRecM", "di-muon mass", 2.8,3.4);//NEW
  //RooRealVar y("y","di-lepton rapidity",-3.6,-2.6) ;
 // RooRealVar jRecY("jRecY", "di-muon rapidity", -3.6,-2.6);//NEW
  Float_t ptMax = 1.0;
 // RooRealVar pt("pt","di-lepton pt",0.0,ptMax) ;
  RooRealVar jRecPt("JRecPt", "di-muon pt", 0.+PtbinShift,ptMax+PtbinShift);//NEW
  RooRealVar jRecPt2("JRecPt","di-muon pt",0.+PtbinShift,1.0+PtbinShift) ;



  // Create data sets
  ofstream outputfile;
  outputfile.open("PtData.txt");
  TFile* filePtYM = new TFile(Form("result_val_data_%s_%s.root",zdcType[z].Data(),systCheck[s].Data()));
 // TTree* treePtYM = filePtYM->Get("jRecTree");
 // TLeaf *l_jRecPt = treePtYM->GetLeaf("jRecPt");
  TH1D* hPt = (TH1D*) filePtYM->Get(Form("hPtYbin%i",y));
  /*for(int i=0; i<treePtYM->GetEntries();i++){
  l_jRecPt->GetBranch()->GetEntry(i);
  double Peet = l_jRecPt->GetValue();
  outputfile << Peet << endl;
  }*/
  int i=1;
  do{
	int bin = hPt->GetBinContent(i);
	for(int j=0; j<bin; j++){
		double Peet = (i-1)*(1.0/((Double_t)nPtBins)) + 0.001 + PtbinShift;
		outputfile << Peet << endl;
	}
	i++;
  }while(i<nPtBins+1);
  outputfile.close();
  cout << "working..." << endl;
  //RooDataSet* dataPtYM = new RooDataSet("dataPtYM", "dataPtYM",treePtYM, RooArgSet(jRecPt,jRecY,jRecM));
  //RooDataSet* data = dataPtYM->reduce(RooArgSet(jRecPt));
  //RooDataSet* data = new RooDataSet("data", "data", treePtYM, RooArgSet(jRecPt));
  RooDataSet* data = RooDataSet::read("PtData.txt",RooArgList(jRecPt)) ;

//  RooDataSet* dataPtYM2 = new RooDataSet("dataPtYM2", "dataPtYM",treePtYM, RooArgSet(jRecPt2,jRecY,jRecM));
//  RooDataSet* data2 = dataPtYM2->reduce(RooArgSet(jRecPt2));

 // TFile* ggfile = new TFile(Form("result_sl_gg_mm_low_%s_%s.root",zdcType[z].Data(),systCheck[s].Data()));
/*  TTree* ggtree = ggfile->Get("jRecTree");
  TLeaf *l_ggjRecPt = ggtree->GetLeaf("jRecPt");
  RooDataSet* ggPtYM = new RooDataSet("ggPtYM", "ggPtYM",ggtree, RooArgSet(jRecPt,jRecY,jRecM));
  RooDataSet* gg = ggPtYM->reduce(RooArgSet(jRecPt));
*/
  TFile* cohfile = new TFile(Form("result_val_sl_jpsi_coh_%s_%s.root",zdcType[z].Data(),systCheck[s].Data()));
 // TTree* cohtree = cohfile->Get("jRecTree");
 // TLeaf *l_cohjRecPt = cohtree->GetLeaf("jRecPt");
 // RooDataSet* cohPtYM = new RooDataSet("cohPtYM", "cohPtYM",cohtree, RooArgSet(jRecPt,jRecY,jRecM));
 // RooDataSet* coh = cohPtYM->reduce(RooArgSet(jRecPt));
 //  RooDataSet* coh = new RooDataSet("coh",cohtree,RooArgSet(jRecPt));

  TFile* icfile = new TFile(Form("result_val_sl_jpsi_incoh_%s_%s.root",zdcType[z].Data(),systCheck[s].Data()));
 /* TTree* ictree = icfile->Get("jRecTree");
  TLeaf *l_icjRecPt = ictree->GetLeaf("jRecPt");
  RooDataSet* icPtYM = new RooDataSet("icPtYM", "icPtYM",ictree, RooArgSet(jRecPt,jRecY,jRecM));
  RooDataSet* ic = icPtYM->reduce(RooArgSet(jRecPt));
*/
  TFile* p2scohfile = new TFile(Form("result_val_sl_psi2s_coh_jpsipipi_%s_%s.root",zdcType[z].Data(),systCheck[s].Data()));
/*  TTree* p2stree = p2sfile->Get("jRecTree");
  TLeaf *l_p2sjRecPt = p2stree->GetLeaf("jRecPt");
  RooDataSet* p2sPtYM = new RooDataSet("p2sPtYM", "p2sPtYM",p2stree, RooArgSet(jRecPt,jRecY,jRecM));
  RooDataSet* p2s = p2sPtYM->reduce(RooArgSet(jRecPt));
*/
  TFile* p2sicfile = new TFile(Form("result_val_sl_psi2s_incoh_jpsipipi_%s_%s.root",zdcType[z].Data(),systCheck[s].Data()));
 /*
  RooDataSet* dataPtYM = RooDataSet::read("pTyM_data.txt",RooArgList(pt,y,m)) ;
  RooDataSet* data = dataPtYM->reduce(RooArgSet(pt));

  RooDataSet* dataPtYM2 = RooDataSet::read("pTyM_data.txt",RooArgList(pt2,y,m)) ;
  RooDataSet* data2 = dataPtYM2->reduce(RooArgSet(pt2));

  RooDataSet* ggPtYM = RooDataSet::read("pTyM_lhc12a8a_NOpT.txt",RooArgList(pt,y,m)) ;
  RooDataSet* gg = ggPtYM->reduce(RooArgSet(pt));
  RooDataSet* cohPtYM = RooDataSet::read("pTyM_lhc12a8b_NOpT.txt",RooArgList(pt,y,m)) ;
  RooDataSet* coh = cohPtYM->reduce(RooArgSet(pt));
  RooDataSet* icPtYM = RooDataSet::read("pTyM_lhc12a8c_NOpT.txt",RooArgList(pt,y,m)) ;
  RooDataSet* ic = icPtYM->reduce(RooArgSet(pt));
  // Here you chose the Transverse or Longitudinal file for FD
  RooDataSet* p2sPtYM = RooDataSet::read("pTyM_psi2S_T_NOpT.txt",RooArgList(pt,y,m)) ;
  // RooDataSet* p2sPtYM = RooDataSet::read("pTyM_psi2S_L_NOpT.txt",RooArgList(pt,y,m)) ;
  RooDataSet* p2s = p2sPtYM->reduce(RooArgSet(pt));
*/
  // Create histograms and fill them
  Int_t nBin = nPtBins;  // here you chose the binning!
  Int_t nBin2 = nPtBins; //250

  TH1F *dataH2 = new TH1F("dataH2","dataH2",nBin,0.+PtbinShift,ptMax+PtbinShift);  //35.-0.,1.4


  //TH1F *dataH = new TH1F("dataH","dataH",nBin,0.0,ptMax);
  TH1F *dataH = (TH1F*) hPt;


 // TH1F *ggH = (TH1F*) ggfile->Get(Form("hPtYbin%i",y));
  TH1F *ggH = (TH1F*) filePtYM->Get(Form("hSBPtYbin%i",y));
  Double_t fracGGbelow = (ggH->Integral(0,(Int_t)nPtBins*PtCut))/(ggH->Integral());
  cout << "fracGGbelow = " << fracGGbelow << endl;
 // TH1F *cohH = new TH1F("cohH","cohH",nBin,0.0,ptMax);
  TH1F *cohH = (TH1F*) cohfile->Get(Form("hPtYbin%i",y));
  cohH->Draw();
 // TH1F *icH = new TH1F("icH","icH",nBin,0.0,ptMax);
  TH1F *icH = (TH1F*) icfile->Get(Form("hPtYbin%i",y));
  TH1F *p2scohH = (TH1F*) p2scohfile->Get(Form("hPtYbin%i",y));
  TH1F *p2sicH = (TH1F*) p2sicfile->Get(Form("hPtYbin%i",y));
  //TH1F *p2sH = new TH1F("p2sH","p2sH",nBin,0.0,ptMax);


  // Create the templete PDFs needed for the model
  Int_t order = 0; // order of the interpolation between bins. Zero is no interpolation
  // define PDF from histograms
  RooHistPdf ggPdf("ggPdf","ggPdf",jRecPt,RooDataHist("ggDH","ggDH",RooArgList(jRecPt),ggH),order);
  RooHistPdf cohPdf("cohPdf","cohPdf",jRecPt,RooDataHist("cohDH","cohDH",RooArgList(jRecPt),cohH),order);
  RooHistPdf icPdf("icPdf","icPdf",jRecPt,RooDataHist("icDH","icDH",RooArgList(jRecPt),icH),order);
  RooHistPdf p2scohPdf("p2scohPdf","p2scohPdf",jRecPt,RooDataHist("p2scohDH","p2scohDH",RooArgList(jRecPt),p2scohH),order);
  RooHistPdf p2sicPdf("p2sicPdf","p2sicPdf",jRecPt,RooDataHist("p2sicDH","p2sicDH",RooArgList(jRecPt),p2sicH),order);
  // Define parameters for PDFs
  // if there is only one number, the parameter is fixed.
  // if there are 3 numbers, the first is where the fit starts the search
  // and the other two are the upper and lower bounds for the parameter

  Double_t nGG = ggYield/fracGGbelow; //number of gg from fit to mass peak in pT<Pt cut / frac of gg in template which are in pT<Pt cut
  Int_t nCoh  = 1000;
  Int_t nICoh = 10;
  //STARLIGHT ratio for pT<Pt cut * number of coh in template for pT<Pt cut / frac of p2s in template which are in pT<Pt cut
 // Double_t nPsiCoh = 600;
  //Double_t nPsiICoh = 6;
  //Double_t nPsi = 10.823; // No polarisation
 // Double_t nPsi = 9.108; // Transverse polarisation
 // Double_t nPsi = 15.842; // Longitudinal polarisation

  RooRealVar ggN("ggN","number of gg",nGG); // fixed by fit to mass peak
  RooRealVar cohN("cohN","number of coh",nCoh,0,100000); // free
  RooRealVar icN("icN","number of ic",nICoh,0,10000); //free
  RooRealVar p2scohN("p2scohN","number of coh p2s",nPsiCoh); // fixed to STARLIGHT ratio
  RooRealVar p2sicN("p2sicN","number of incoh p2s",nPsiICoh);

  cout << "working2... " << endl;


  // Create the model as the sum of the four templates
 // RooAddPdf sum("sum","extended summ of gg, coh, ic and p2s",RooArgList(ggPdf,cohPdf,icPdf,p2sPdf),
//		RooArgList(ggN,cohN,icN,p2sN));
    RooAddPdf sum("sum","extended sum of all", RooArgList(cohPdf,icPdf,ggPdf,p2scohPdf,p2sicPdf), RooArgList(cohN,icN,ggN,p2scohN,p2sicN));

  cout << "working3..." << endl;

  // perform fit
  RooFitResult* r = sum.fitTo(*data,Extended(kTRUE),Save());


  cout << "working4..." << endl;

  // plot
  RooPlot* frame = jRecPt.frame(Bins(nBin),Title("jRecPt spectrum")) ;
  data->plotOn(frame);
  sum.plotOn(frame,LineColor(kBlack), Range(0.,1.0) ) ;
  sum.paramOn(frame,data);
  sum.plotOn(frame,Components(ggPdf), LineColor(kGreen), Range(0,1.0)    );
  sum.plotOn(frame,Components(icPdf), LineColor(kRed), Range(0,1.0) );
  sum.plotOn(frame,Components(cohPdf), LineColor(kBlue), Range(0,1.0)  );
  sum.plotOn(frame,Components(p2scohPdf), LineColor(kCyan), Range(0,1.0)  );
  sum.plotOn(frame,Components(p2sicPdf), LineColor(kMagenta), Range(0,1.0) );
  sum.paramOn(frame,data);
  frame->Draw();



  // get fractions of PDF in jRecPt range [0,Pt cut]
  jRecPt.setRange("signal",0,PtCut);
  RooAbsReal* cohI = cohPdf.createIntegral(jRecPt,NormSet(jRecPt),Range("signal")) ;
  RooAbsReal* icI = icPdf.createIntegral(jRecPt,NormSet(jRecPt),Range("signal")) ;
  RooAbsReal* p2scohI = p2scohPdf.createIntegral(jRecPt,NormSet(jRecPt),Range("signal")) ;
  RooAbsReal* p2sicI = p2sicPdf.createIntegral(jRecPt,NormSet(jRecPt),Range("signal")) ;
  RooAbsReal* ggI = ggPdf.createIntegral(jRecPt,NormSet(jRecPt),Range("signal")) ;
  RooAbsReal* sI = sum.createIntegral(jRecPt,NormSet(jRecPt),Range("signal")) ;

 //Calculate chi^2
  Double_t total = sum.expectedEvents(jRecPt);
  cout << total << endl;
  Double_t chi2=0;
  for(Int_t i=0; i<nPtBins; i++){
	jRecPt.setRange("bin",i*(1.0/((Double_t)nPtBins))+PtbinShift,(i+1)*(1.0/((Double_t)nPtBins))+PtbinShift);
        RooAbsReal* binI = sum.createIntegral(jRecPt,NormSet(jRecPt),Range("bin"));
	Double_t fBin = binI->getVal();
	Double_t sumPoint = fBin * total;
	cout << sumPoint << " ";
	Double_t dataPoint = dataH->GetBinContent(i+1);
	cout << dataPoint << endl;
	Double_t sqDiff = (sumPoint - dataPoint)*(sumPoint-dataPoint);
	cout << sqDiff << endl;
	Double_t sqError = sumPoint;
	Double_t chiBin = sqDiff/sqError;
	cout << chiBin << endl;
	chi2+=chiBin;
  }
  cout << "chi^2 = " << chi2 << endl;
  cout << "chi^2/dof = " << chi2/((Double_t)nPtBins) << endl;

Double_t fCoh  = cohI->getVal();
Double_t fICoh = icI->getVal();
Double_t fPsiCoh  = p2scohI->getVal();
Double_t fPsiICoh = p2sicI->getVal();
Double_t fGG   = ggI->getVal();


cout << "For jRectPt<Pt cut GeV/c" << endl;
cout << "Number of gg integrated under Pt cut: " << ggN.getValV() * fGG << " +/- " << ggN.getError() * fGG << endl;
cout << "Number of coh feed-down integrated under Pt cut: " << p2scohN.getValV() * fPsiCoh << " +/- " << p2scohN.getError() * fPsiCoh << endl;
cout << "Number of incoh feed-down integrated under Pt cut: " << p2sicN.getValV() * fPsiICoh << " +/- " << p2sicN.getError() * fPsiICoh << endl;
cout << "Number of incoherent integrated under Pt cut: " << icN.getValV() * fICoh << " +/- " << icN.getError() * fICoh << endl;
cout << "Number of coherent integrated under Pt cut: " << cohN.getValV() * fCoh << " +/- " << cohN.getError() * fCoh << endl;
N_coh = cohN.getValV() * fCoh; //Number of coherent J/psi according to fit
Double_t N_cohError = cohN.getError() * fCoh; //Error on coh J/psi according to fit
Double_t N_I = icN.getValV() * fICoh; //Number of incoherent J/psi below Pt cut
Double_t N_IError = icN.getError() * fICoh; //Error on inc J/psi below Pt cut
Double_t N_cohFD = p2scohN.getValV() * fPsiCoh; //Number of coh FD below Pt cut
Double_t N_cohFDError = p2scohN.getError() * fPsiCoh; //Error on coh FD < Pt cut
Double_t N_icFD = p2sicN.getValV() * fPsiICoh; //Number of ic FD below Pt cut
Double_t N_icFDError = p2sicN.getError() * fPsiICoh; //Error on ic FD below Pt cut

//When cross sections and efficiencies are given for pt<Pt cut:
//cout << "fFDcoh = " << p2scohN.getValV() * fPsiCoh/(cohN.getValV() * fCoh) << endl;
//cout << "fFDincoh = " << p2sicN.getValV() * fPsiICoh/(cohN.getValV() * fCoh) << endl;
//When cross sections and effeciences are given for all pt:
 fracFDcoh = p2scohN.getValV()/cohN.getValV();
 fracFDic = p2sicN.getValV()/icN.getValV();

 cout << "fFDcoh = " << fracFDcoh << ";  Target: 0.105" << endl;
 cout << "fFDincoh = " << fracFDic << ";  Target: 0.0993" << endl;

cout << "****************************** " << endl;
cout << "Fractions of the templates under Pt=Pt cut GeV/c" << endl;
cout << "Coherent fraction " << fCoh << endl;
cout << "Incoherent fraction " << fICoh << endl;
cout << "Coherent Feed-down fraction " << fPsiCoh << endl;
cout << "Incoherent Feed-down fraction " << fPsiICoh << endl;
cout << "Gamma+Gamma fraction " << fGG << endl;

fI = (icN.getValV() * fICoh) / (cohN.getValV() * fCoh);
fFD = ((p2scohN.getValV() * fPsiCoh) + (p2sicN.getValV() * fPsiICoh)) / (cohN.getValV() * fCoh);

  TFile* fFit = new TFile(Form("fit_v3_%s_%s_%i_%s.root",anaType[0].Data(),zdcType[z].Data(),y,systCheck[s].Data()),"recreate");
  frame->Write();
  TH1D* hN_coh = new TH1D("hN_coh","N_coh",1,0,1);
  hN_coh->SetBinContent(1,N_coh);
  hN_coh->SetBinError(1,N_cohError);
  hN_coh->Write();
  hN_coh->Delete();
  TH1D* hN_I = new TH1D("hN_I","N_I",1,0,1);
  hN_I->SetBinContent(1,N_I);
  hN_I->SetBinError(1,N_IError);
  hN_I->Write();
  hN_I->Delete();
  TH1D* hN_cohFD = new TH1D("hN_cohFD","N_cohFD",1,0,1);
  hN_cohFD->SetBinContent(1,N_cohFD);
  hN_cohFD->SetBinError(1,N_cohFDError);
  hN_cohFD->Write();
  hN_cohFD->Delete();
  TH1D* hN_icFD = new TH1D("hN_icFD","N_icFD",1,0,1);
  hN_icFD->SetBinContent(1,N_icFD);
  hN_icFD->SetBinError(1,N_icFDError);
  hN_icFD->Write();
  hN_icFD->Delete();


  fFit->Close();

  filePtYM->Close();
 // ggfile->Close();
  cohfile->Close();
  icfile->Close();
  p2scohfile->Close();
  p2sicfile->Close();



}
