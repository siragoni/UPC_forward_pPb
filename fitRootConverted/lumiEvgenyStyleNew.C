#include "TChain.h"
#include "TH1D.h"
#include "AliTriggerClass.h"
#include "TFile.h"
#include "TH2D.h"
// #include "../task/runlist.txt"
#include "TCanvas.h"
#include "TLegend.h"

// Int_t nRuns     = 38;
Int_t nRuns     = 77;
Int_t runList[] = {
  267131, 267130, 267110, 267109, 267077, 267072, 267070, 267067, 267063, 267062,
  267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
  266940, 266915, 266912, 266886, 266885, 266883, 266882, 266880, 266878, 266857,
  266807, 266805, 266800, 266776, 266775, 266708, 266706, 266703, 266702, 266676,
  266674, 266669, 266668, 266665, 266659, 266658, 266657, 266630, 266621, 266618,
  266615, 266614, 266613, 266595, 266593, 266591, 266588, 266587, 266584, 266549,
  266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, 266518, 266516,
  266514, 266487, 266480, 266479, 266472, 266441, 266439 };
// Int_t runList[]  = {
//   267131, 267130, 267110, 267109, 267077, 267072, 267070, 267067, 267063, 267062,
//   267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
//   266940, 266915, 266912, 266886, 266885, 266883, 266882, 266880, 266878, 266857,
//   /*266807, 266805, 266800, 266776, 266775, 266708, 266706, 266703, 266702, 266676,
//   266674, 266669, 266668, 266665, 266659, 266658, 266657, 266630, 266621, 266618,
//   266614, 266613, 266595, 266593, 266591, 266588, 266587, 266584, 266549,
//   266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, 266518,*/ 266516,
//   266514, 266487, 266480, 266479, 266472, 266441, 266439 };



// void lumiEvgenyStyle(TString className = "CMUL7-B-NOPF-MUFAST"){
// void lumiEvgenyStyle(TString className = "CMUP11-B-NOPF-MUFAST"){
void lumiEvgenyStyle(TString className = "CMUP23-B-NOPF-MUFAST"){
//void lumiEvgenyStyle(TString className = "CCUP9-B-NOPF-CENTNOTRD"){
  TH1D* hTrigRecorded = new TH1D("hTrigRecorded","",nRuns,0,nRuns);
  TH1D* hTrigAnalysed = new TH1D("hTrigAnalysed","",nRuns,0,nRuns);
  TH1D* hLumiRecorded = new TH1D("hLumiRecorded","",nRuns,0,nRuns);
  TH1D* hLumiAnalysed = new TH1D("hLumiAnalysed","",nRuns,0,nRuns);
  Int_t run;
  TObjArray* classes = new TObjArray();
  ULong64_t class_l0b[100];
  ULong64_t class_l2a[100];
  Double_t  class_lumi[100];
  Double_t mu = 0;
  TChain* t = new TChain("trending");
  t->AddFile("trending.root");
  // t->AddFile("trending_fixed.root");
  // t->AddFile("trending2018.root");
  t->SetBranchAddress("mu",&mu);
  t->SetBranchAddress("run",&run);
  t->SetBranchAddress("classes",&classes);
  t->SetBranchAddress("class_lumi",&class_lumi);
  t->SetBranchAddress("class_l2a",&class_l2a);
  t->SetBranchAddress("class_l0b",&class_l0b);
  t->BuildIndex("run");

  AliTriggerClass* cl     = 0x0;
  AliTriggerClass* clRef  = 0x0;
  AliTriggerClass* clLT   = 0x0;
  // TFile* f = new TFile("AnalysisResultsNewLHC16s_correlations_noLPT.root");
  // TFile* f = new TFile("AnalysisResultsNewLHC16s_correlations_noPDCA.root");
  // TFile* f = new TFile("AnalysisResultsNewLHC16s_correlations_13062020.root");
  TFile* f = new TFile("AnalysisResultsNewLHC16s_OnlyMainCMUP.root");
  // TFile* f = new TFile("AnalysisResultsNewLHC16s_correlations_14062020.root");
  // TFile* f = new TFile("AnalysisResultsNewLHC16s_04052020.root");
  TList* list = (TList*) f->Get("MyTask/MyOutputContainer"); // provide your list here
  TH2F* h2 = (TH2F*) list->FindObject("fTriggersVsRunH");


  for (Int_t i=0;i<nRuns;i++){
    Int_t r = runList[i];
    if ( r == 266615 ) continue;






    // if ( r == 267110 || r == 266885 || r == 266882 || r == 266857 || r == 266775 || r == 266706 || r == 266703 || r == 266702 || r == 266668 || r == 266658 || r == 266657 || r == 266614 || r == 266613 || r == 266591 || r == 266588 || r == 266587 || r == 266584 || r == 266518 || r == 266516 || r == 266514 || r == 266472 || r == 266441  ) continue;


    char* srun = Form("%i",r);
    t->GetEntryWithIndex(r);
    printf("%i ",run);
    className = "CMUP23-B-NOPF-MUFAST";
    // className = "CMUP22-B-NOPF-ALLNOTRD";
    // if (run<=245542) className = "CMUP10-B-NOPF-MUFAST";
    // AliTriggerClass* cl     = (AliTriggerClass*) classes->FindObject(className.Data());
    // AliTriggerClass* clRef  = (AliTriggerClass*) classes->FindObject("C0V0M-B-NOPF-CENTNOTRD");
    // AliTriggerClass* clLT   = (AliTriggerClass*) classes->FindObject("CMUL7-B-NOPF-MUFAST");
    cl     = (AliTriggerClass*) classes->FindObject(className.Data());
    // clRef  = (AliTriggerClass*) classes->FindObject("C0V0M-B-NOPF-CENTNOTRD");
    clRef  = (AliTriggerClass*) classes->FindObject("C0TVX-B-NOPF-CENTNOTRD");
    clLT   = (AliTriggerClass*) classes->FindObject("CMUL7-B-NOPF-MUFAST");
    Int_t icl        = classes->IndexOf(cl);
    Int_t iclassRef  = classes->IndexOf(clRef);
    Int_t iclassLT   = classes->IndexOf(clLT);
    Double_t l0bRef = class_l0b[iclassRef];
    Double_t l0bLT  = class_l0b[iclassLT];
    Double_t l2aLT  = class_l2a[iclassLT];
    Double_t l2a    = class_l2a[icl];
    Double_t lumi   = class_lumi[iclassLT];
    Double_t eff = 0.82;
    // if (295585 <=run && run<= 295589) eff = 0.536;
    // if (295612 <=run && run<= 295615) eff = 0.532;
    // if (295665 <=run && run<= 296198) eff = 0.518;
    // if (296241 <=run && run<= 297595) eff = 0.514;
    // Double_t sigma = 7.66*eff;
    // Double_t sigma = 1.715*eff;
    Double_t sigma = 2.092*eff;
    // if (295671 <=run && run<= 295715) l0bRef/=0.135;
    // if (295717 <=run && run<= 295720) l0bRef/=0.135;

    Double_t lumiSeen = l0bRef/sigma*mu/(1-exp(-mu));
    Double_t lt = l2aLT/l0bLT;
    Double_t lumiMy = lumiSeen*lt/1000000.;
    cout << "LumiMy = " << lumiMy << endl;
    cout << "l2a = " << l2a << endl;
    printf("%f %f %f\n",lumiMy,lumi,lumiMy/lumi);
   // if (!cl) continue;
   // Int_t iclass = classes->IndexOf(cl);
   // if (iclass<0) continue;
   // Double_t l0b = class_l0b[iclass];
   // Double_t l2a = class_l2a[iclass];
//
//    Double_t lumiMy = l0bRef/4.*l2a/l0b;
////    if ((run>=295671 && run<=295715) || (run>=295717 && run<=295720)) class_lumi[iclass]/=0.135;
//    Double_t lumi = class_lumi[iclass];
//    printf("%f\n",lumiMy/1000000./lumi);
    hTrigRecorded->Fill(srun,l2a);
    hLumiRecorded->Fill(srun,lumiMy);


//     TFile* f = new TFile("AnalysisResultsLHC18qr15o30082019.root");
//     TList* list = (TList*) f->Get("MyTask/MyOutputContainer"); // provide your list here
//     // TH2D* fTriggersVsRun = (TH2D*) list->FindObject("fTriggersVsRun");
//     // TH2F* fTriggersVsRun = (TH2F*) list->FindObject("fTriggersVsRunH");
//
//
//     // TFile* f = new TFile(Form("../data18/AnalysisResults.%i.root",r));
// //    TFile* f = new TFile(Form("../data18/AnalysisResults.%i.root",r));
// //    TFile* f = new TFile(Form("/eos/user/e/ekryshen/trees/pb2018/mup/task/merged/AnalysisResults.000%i.root",r));
//     // TList* list = (TList*) f->Get("UpcTree/histos");
//     TH2F* h2 = (TH2F*) list->FindObject("fTriggersVsRunH");
//     Int_t nTrigAnalysed =  h2->GetBinContent(run<=245542 ? 5 : 3,h2->GetYaxis()->FindFixBin(run+0.5));
//     hTrigAnalysed->Fill(srun,nTrigAnalysed);
// //    printf("l2a=%0.f nTrigAnalysed=%i\n",l2a,nTrigAnalysed);
//     hLumiAnalysed->Fill(srun,lumi>1e-10 ? Double_t(nTrigAnalysed)/l2a*lumiMy : 0);



    Int_t class_bin = 2;
    // Int_t class_bin = 4;
    // check for consistency with fTriggersVsRun contents
    // if (className.Contains("CMUP10-B-NOPF-MUFAST")) class_bin = 4;
    // if (className.Contains("CMUP11-B-NOPF-MUFAST")) class_bin = 1;
    Int_t run_bin       = h2->GetYaxis()->FindFixBin(run+0.5);
    cout << "bin = " << h2->GetYaxis()->FindBin(run+0.5) << endl;
    Int_t nTrigAnalysed = h2->GetBinContent(class_bin,h2->GetYaxis()->FindFixBin(run+0.5));
    cout << "run = " << run << " , run_bin = " << run_bin <<  ", nTrigAnalysed = " << nTrigAnalysed << endl;
    Int_t nTrigRecorded = l2a;
    // Double_t lumiAnalysed = nTrigRecorded>=1 ? Double_t(nTrigAnalysed)/nTrigRecorded*lumiRecorded : 0;
    // hTrigRecorded->Fill(srun,l2a);
    // hTrigAnalysed->Fill(srun,nTrigAnalysed);
    // hLumiRecorded->Fill(srun,lumiRecorded/1000000.); // b -> ub
    // hLumiAnalysed->Fill(srun,lumiAnalysed/1000000.); // b -> ub
    // Int_t nTrigAnalysed =  h2->GetBinContent(run<=245542 ? 5 : 3,h2->GetYaxis()->FindFixBin(run+0.5));
    hTrigAnalysed->Fill(srun,nTrigAnalysed);
//    printf("l2a=%0.f nTrigAnalysed=%i\n",l2a,nTrigAnalysed);
    hLumiAnalysed->Fill(srun,lumi>1e-10 ? Double_t(nTrigAnalysed)/l2a*lumiMy : 0);

  }
  new TCanvas;
  hTrigRecorded->SetLineColor(kBlue);
  hTrigAnalysed->SetLineColor(kRed);
  hTrigRecorded->Draw("hist");
  hTrigAnalysed->Draw("hist same");

  new TCanvas;
  hLumiRecorded->SetLineColor(kBlue);
  hLumiAnalysed->SetLineColor(kRed);
  hLumiRecorded->Draw("hist");
  hLumiAnalysed->Draw("hist same");

  TLegend* l = new TLegend(0.5,0.7,0.9,0.9);
  l->AddEntry(hLumiRecorded,Form("Recorded = %.3f /mb",hLumiRecorded->Integral()));
  l->AddEntry(hLumiAnalysed,Form("Analysed = %.3f /mb",hLumiAnalysed->Integral()));
  l->Draw();

  printf("%f\n",hLumiAnalysed->Integral());
  TFile* f2 = new TFile("lumi16s.root","recreate");
  hLumiRecorded->Write();
  hLumiAnalysed->Write();
  f2->Close();

  for( Int_t iBins = 1; iBins < hLumiAnalysed->GetNbinsX(); iBins++) {

    // else if ( fRunNum == 246809 ) { fLumiPerRun = 2.47068;  }

    cout << "else if ( fRunNum == "  << hLumiAnalysed->GetXaxis()->GetBinLabel(iBins);
    cout << " ) { fLumiPerRun = " << hLumiAnalysed->GetBinContent(iBins) << "; }" << endl;
  }

}
