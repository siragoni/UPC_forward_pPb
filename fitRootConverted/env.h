#ifndef env_h
#define env_h 1
#include "TStyle.h"
#include "TTree.h"
#include "TBits.h"
#include "TObjString.h"
#include "TClonesArray.h"
#include "TMath.h"
#define NTRIGGERS 5

TString zdcType[] = {"total" ,"0N0N","0NXN","XN0N","XNXN","all"};
enum                {kTotal=0, kNZdcTypes};
//enum                {kTotal=0, k0N0N, k0NXN, kXN0N, kXNXN,kNZdcTypes};
TString anaType[] = {"data" ,"data_mup11", "sl_jpsi_coh","sl_jpsi_incoh","sl_psi2s_coh","sl_psi2s_incoh","sl_psi2s_coh_jpsipipi",   "sl_psi2s_jpsipipi","sl_gg_low","sl_gg_high","all"};
enum                {kData=0, kNanaTypes};
//enum                {kData=0,  kDataMUP11, kSlJpsiCoh,   kSlJpsiIncoh,   kSlPsi2sCoh,   kSlPsi2sIncoh,    kSlPsi2sCohJpsiPiPi, kSlPsi2sIncohJpsiPiPi,   kSlGgLow,   kSlGgHigh, kNanaTypes};
TString systCheck[] = {"default" ,"syst_pt_cut_1","syst_pt_cut_2","syst_pt_cut_3","syst_pt_cut_4","syst_m_cut_1","syst_m_cut_2","syst_m_cut_3","syst_m_cut_4","all"};
enum                  {kDefaultSys=0, kNSystChecks};
//enum                  {kDefault=0,    kSystPtCut1,    kSystPtCut2,    kSystPtCut3,    kSystPtCut4,    kSystMCut1,    kSystMCut2,    kSystMCut3,    kSystMCut4, kNSystChecks};
//
////kSystLumi,
////kSystMuonTrackingEfficiency,
////kSystMuonTriggerEfficiency,
////kBranchingRatio
//
//Float_t gMmin = 2.8;
//Float_t gMmax = 3.4;
//Float_t gPtMin = 0;
//Float_t gPtMax = 0.3;
//
//Float_t gPtMin = 0;
//Float_t gPtMaxSyst1 = 0.3;
//Float_t gPtMaxSyst2 = 0.3;
//Float_t gPtMaxSyst3 = 0.3;
//Float_t gPtMaxSyst4 = 0.3;
//
//Float_t gMminSyst1 = 2.90;
//Float_t gMmaxSyst1 = 3.30;
//
//Float_t gMminSyst2 = 2.85;
//Float_t gMmaxSyst2 = 3.35;
//
//Float_t gMminSyst3 = 2.75;
//Float_t gMmaxSyst3 = 3.45;
//
//Float_t gMminSyst4 = 2.95;
//Float_t gMmaxSyst4 = 3.25;
//
//const Int_t nContinuumBins = 5; 
//Float_t gContinuumMmin[nContinuumBins] = { 4, 5, 6,  8, 10};
//Float_t gContinuumMmax[nContinuumBins] = { 5, 6, 8, 10, 12};
//Float_t gContinuumPtMin = 0;
//Float_t gContinuumPtMax = 0.3;
//
const Int_t nYBins = 10;
Float_t gYMin[nYBins] = {-4.0, -4.00, -3.75, -3.50, -3.25, -3.00, -2.75, -4.0, -3.5, -3.0};
Float_t gYMax[nYBins] = {-2.5, -3.75, -3.50, -3.25, -3.00, -2.75, -2.50, -3.5, -3.0, -2.5};
const Int_t nPtBins = 7;
const Int_t nPtBinsJpsi = 7;
Float_t gPtMin[nPtBins] = {   0,   0,   0,     0,    0,      0,     0};
Float_t gPtMax[nPtBins] = {0.25, 4.0, 0.2, 0.225, 0.25,  0.275,  0.30};
const Int_t nMBins = 10;
const Int_t nMBinsJpsi = 8;
Float_t gMMin[nMBins] = {2.85, 0.00, 2.80, 2.85, 2.90, 2.85, 2.85, 2.85, 2.20, 4.00};
Float_t gMMax[nMBins] = {3.35, 6.00, 3.35, 3.35, 3.35, 3.30, 3.35, 3.40, 2.70, 4.50};
//
//Float_t gZNA0Nmax =  90;
//Float_t gZNC0Nmax = 111;

Int_t col[12] = {kBlack,kBlue,kRed,kMagenta,kGreen+2,kYellow+2,kBlue+2,kRed+2,kMagenta+2,kGray,kBlue+1,kRed+1};

Float_t mMu = 0.1056583715;
Double_t pi = TMath::Pi();

Int_t fEventInFile;
UInt_t fPeriod;
UInt_t fOrbit;
UShort_t fBC;
UInt_t fL0inputs;
UInt_t fL1inputs;
Int_t fRunNumber; 
Int_t fNofTracklets;
Float_t fV0AMult[32];
Float_t fV0CMult[32];
Float_t fV0ATime[32];
Float_t fV0CTime[32];
Bool_t fBBFlag[64];
Bool_t fBGFlag[64];
UInt_t fBBAFlags;
UInt_t fBBCFlags;
UInt_t fBGAFlags;
UInt_t fBGCFlags;
Bool_t fBBTriggerV0A[32];
Bool_t fBGTriggerV0A[32];
Bool_t fBBTriggerV0C[32];
Bool_t fBGTriggerV0C[32];
Char_t fV0ADecision;
Char_t fV0CDecision;
Float_t fMTotV0A;
Float_t fMTotV0C;
Float_t fADATime;
Float_t fADCTime;
Char_t fADADecision;
Char_t fADCDecision;
Float_t fMTotADA;
Float_t fMTotADC;
UShort_t fTriggerChargeADA;
UShort_t fTriggerChargeADC;
Float_t fZNATDC[4];
Float_t fZNCTDC[4];
Float_t fZNAenergy;
Float_t fZNCenergy;
Float_t fZPAenergy;
Float_t fZPCenergy;
Float_t fZEM1energy;
Float_t fZEM2energy;
Float_t fZNAtower0;
Float_t fZNCtower0;
Float_t fZPAtower0;
Float_t fZPCtower0;
Float_t fVtxX;
Float_t fVtxY;
Float_t fVtxZ;
Bool_t fVtxTPC;
Int_t fNofITSClusters[6];

TObjString* fChunkFileName = new TObjString();
TObjString* fClassesFired = new TObjString();
TBits* fIR1 = new TBits();
TBits* fIR2 = new TBits();
TBits* fFOmap = new TBits();
TBits* fFiredChipMap = new TBits();
TClonesArray* fMcParticles = new TClonesArray("AliUpcParticle");
TClonesArray* fMuons = new TClonesArray("AliUpcParticle");


void SetBranches(TTree* fTree){
  fTree->SetBranchAddress("fClassesFired",&fClassesFired);
  fTree->SetBranchAddress("fMcParticles",&fMcParticles);
  fTree->SetBranchAddress("fMuons",&fMuons);
  fTree->SetBranchAddress("fChunkFileName",&fChunkFileName);
  fTree->SetBranchAddress("fEventInFile",&fEventInFile);
  fTree->SetBranchAddress("fPeriod",&fPeriod);
  fTree->SetBranchAddress("fOrbit",&fOrbit);
  fTree->SetBranchAddress("fBC",&fBC);
  fTree->SetBranchAddress("fRunNumber",&fRunNumber);
  fTree->SetBranchAddress("fNofTracklets",&fNofTracklets);
  fTree->SetBranchAddress("fV0AMult",&fV0AMult);
  fTree->SetBranchAddress("fV0CMult",&fV0CMult);
  fTree->SetBranchAddress("fV0ATime",&fV0ATime);
  fTree->SetBranchAddress("fV0CTime",&fV0CTime);
  fTree->SetBranchAddress("fBBFlag",&fBBFlag);
  fTree->SetBranchAddress("fBGFlag",&fBGFlag);
  fTree->SetBranchAddress("fBBAFlags",&fBBAFlags);
  fTree->SetBranchAddress("fBBCFlags",&fBBCFlags);
  fTree->SetBranchAddress("fBGAFlags",&fBGAFlags);
  fTree->SetBranchAddress("fBGCFlags",&fBGCFlags);
  fTree->SetBranchAddress("fBBTriggerV0A",&fBBTriggerV0A);
  fTree->SetBranchAddress("fBGTriggerV0A",&fBGTriggerV0A);
  fTree->SetBranchAddress("fBBTriggerV0C",&fBBTriggerV0C);
  fTree->SetBranchAddress("fBGTriggerV0C",&fBGTriggerV0C);
  fTree->SetBranchAddress("fV0ADecision",&fV0ADecision);
  fTree->SetBranchAddress("fV0CDecision",&fV0CDecision);
  fTree->SetBranchAddress("fMTotV0A",&fMTotV0A);
  fTree->SetBranchAddress("fMTotV0C",&fMTotV0C);
  fTree->SetBranchAddress("fADATime",&fADATime);
  fTree->SetBranchAddress("fADCTime",&fADCTime);
  fTree->SetBranchAddress("fADADecision",&fADADecision);
  fTree->SetBranchAddress("fADCDecision",&fADCDecision);
  fTree->SetBranchAddress("fMTotADA",&fMTotADA);
  fTree->SetBranchAddress("fMTotADC",&fMTotADC);
  fTree->SetBranchAddress("fTriggerChargeADA",&fTriggerChargeADA);
  fTree->SetBranchAddress("fTriggerChargeADC",&fTriggerChargeADC);
  fTree->SetBranchAddress("fZPAenergy",&fZPAenergy);
  fTree->SetBranchAddress("fZPCenergy",&fZPCenergy);
  fTree->SetBranchAddress("fZNAenergy",&fZNAenergy);
  fTree->SetBranchAddress("fZNCenergy",&fZNCenergy);
  fTree->SetBranchAddress("fZEM1energy",&fZEM1energy);
  fTree->SetBranchAddress("fZEM2energy",&fZEM2energy);
  fTree->SetBranchAddress("fZNAtower0",&fZNAtower0);
  fTree->SetBranchAddress("fZNCtower0",&fZNCtower0);
  fTree->SetBranchAddress("fZPAtower0",&fZPAtower0);
  fTree->SetBranchAddress("fZPCtower0",&fZPCtower0);
  fTree->SetBranchAddress("fZNATDC",&fZNATDC);
  fTree->SetBranchAddress("fZNCTDC",&fZNCTDC);
  fTree->SetBranchAddress("fVtxX",&fVtxX);
  fTree->SetBranchAddress("fVtxY",&fVtxY);
  fTree->SetBranchAddress("fVtxZ",&fVtxZ);
  fTree->SetBranchAddress("fVtxTPC",&fVtxTPC);
  fTree->SetBranchAddress("fNofITSClusters",&fNofITSClusters);
  fTree->SetBranchAddress("fIR1",&fIR1);
  fTree->SetBranchAddress("fIR2",&fIR2);
  fTree->SetBranchAddress("fL0inputs",&fL0inputs);
  fTree->SetBranchAddress("fL1inputs",&fL1inputs);
  fTree->SetBranchAddress("fFOmap",&fFOmap);
  fTree->SetBranchAddress("fFiredChipMap",&fFiredChipMap);
}

Bool_t IsEventSelected(Bool_t isMc=0){
  if (fRunNumber==244918) return 0; // no UPC triggers
  if (fRunNumber==296376) return 0; // bad AD
  if (fRunNumber==297623) return 0; // bad pileup
  if (fRunNumber==297624) return 0; // bad pileup
  if (fRunNumber==296977) return 0; // bad ZDC
  Bool_t cmup10 = fClassesFired->String().Contains("CMUP10-B");
  Bool_t cmup11 = fClassesFired->String().Contains("CMUP11-B");
  Bool_t cmup13 = fClassesFired->String().Contains("CMUP13-B");
  Bool_t mul = fL0inputs & 1<<20;
  if (!isMc) if (!cmup10 && !cmup11) return 0;
  if (fV0CDecision!=0 && fV0CDecision!=1) return 0;
  if (fBBAFlags!=0) return 0;
  if (fBBCFlags>=3) return 0;
  if (fBGAFlags!=0) return 0;
  if (fBGCFlags!=0) return 0;
  return 1;
}

void SetStyle(){
  gStyle->SetLineScalePS(2);
  gStyle->SetOptStat(0);
  gStyle->SetLegendBorderSize(0);
  gStyle->SetTitleOffset(1.25,"XYZ");
  gStyle->SetTitleSize(0.04,"XYZ");
  gStyle->SetLabelSize(0.04,"XYZ");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetTextSize(0.04);
  gStyle->SetTextFont(42);
}

void zdc(){
  Bool_t calibrated = 0;
  if (fRunNumber<=245068) calibrated = 1;
  if (295585<=fRunNumber && fRunNumber<=295725) calibrated = 1;
  if (fRunNumber==296509) calibrated = 1;
  if (296690<=fRunNumber && fRunNumber<=296694) calibrated = 1;
  if (297219<=fRunNumber && fRunNumber<=297221) calibrated = 1;
  if (fRunNumber==297415) calibrated = 1;

  Bool_t zna_fired = 0;
  Bool_t znc_fired = 0;
  for (Int_t i=0;i<4;i++) if (fZNATDC[i]<2 && fZNATDC[i]>-2) zna_fired = 1;
  for (Int_t i=0;i<4;i++) if (fZNCTDC[i]<2 && fZNCTDC[i]>-2) znc_fired = 1;

  Float_t fZNAtower0c = fZNAtower0;
  Float_t fZNCtower0c = fZNCtower0;

  if (!calibrated) {
    if (fRunNumber<=246994) { fZNAtower0c = fZNAtower0*2500./250.; fZNCtower0c = fZNCtower0*2500./250.;}
    if (fRunNumber>246994)  { fZNAtower0c = fZNAtower0*2500./190.; fZNCtower0c = fZNCtower0*2500./190.;}
  }

//  if (mRc<3.35 && mRc>2.85 && ptRc<0.25 && yRc<-2.5 && yRc>-4){
//    hZNA->Fill(fZNAtower0c);
//    hZNC->Fill(fZNCtower0c);
//    hZNAvsZNC->Fill(fZNAtower0c,fZNCtower0c);
//    hV0Ccells->Fill(fBBCFlags);
//  }
  
//  if (!mc) {
//    if (fZNAtower0<120 && fZNCtower0<120) hRcYMPtZN[0]->Fill(yRc,mRc,ptRc);
//    if (fZNAtower0<120 && fZNCtower0>120) hRcYMPtZN[1]->Fill(yRc,mRc,ptRc);
//    if (fZNAtower0>120 && fZNCtower0<120) hRcYMPtZN[2]->Fill(yRc,mRc,ptRc);
//    if (fZNAtower0>120 && fZNCtower0>120) hRcYMPtZN[3]->Fill(yRc,mRc,ptRc);
//  }

//  hZNAvsRun->Fill(Form("%i",fRunNumber),fZNAtower0,1);
//  hZNCvsRun->Fill(Form("%i",fRunNumber),fZNCtower0,1);

}
#endif
