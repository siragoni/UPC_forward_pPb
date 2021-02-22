// to run:
//   alien-token-init
//   source /tmp/gclient_env_501
//   aliroot runAnalysis.C\(opt\)


// include the header of your analysis task here! for classes already compiled by aliBuild,
// precompiled header files (with extension pcm) are available, so that you do not need to
// specify includes for those. for your own task however, you (probably) have not generated a
// pcm file, so we need to include it explicitly
#include "AliAnalysisTaskUPCforwardpPb.h"

void runAnalysis(Int_t opt)
// opt = 0; 2018 q
// opt = 1; 2018 r
{
  // set if you want to run the analysis locally (kTRUE), or on grid (kFALSE)
  // Bool_t local = kFALSE;
  // Bool_t local = kTRUE;
  // if you run on grid, specify test mode (kTRUE) or full grid model (kFALSE)
  // Bool_t gridTest = kFALSE;
  // Bool_t gridTest = kTRUE;

  /**
   * RUN ON LOCAL:
   */
  // Bool_t local    = kTRUE;
  // Bool_t gridTest = kFALSE;

  /**
   * RUN ON GRIDTEST:
   */
  // Bool_t local    = kFALSE;
  // Bool_t gridTest = kTRUE;


  /**
   * FULL GRID MOD:
   */
  Bool_t local    = kFALSE;
  Bool_t gridTest = kFALSE;


#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->ProcessLine(".include $ROOTSYS/include");
    gInterpreter->ProcessLine(".include $ALICE_ROOT/include");
#else
    gROOT->ProcessLine(".include $ROOTSYS/include");
    gROOT->ProcessLine(".include $ALICE_ROOT/include");
#endif

    // create the analysis manager
    AliAnalysisManager *mgr = new AliAnalysisManager("AnalysisTaskExample");
    AliAODInputHandler *aodH = new AliAODInputHandler();
    mgr->SetInputEventHandler(aodH);

    // compile the class and load the add task macro
    // here we have to differentiate between using the just-in-time compiler
    // from root6, or the interpreter of root5
#if !defined (__CINT__) || defined (__CLING__)
    gInterpreter->LoadMacro("AliAnalysisTaskUPCforwardpPb.cxx++g");
    AliAnalysisTaskUPCforwardpPb *task = reinterpret_cast<AliAnalysisTaskUPCforwardpPb*>(gInterpreter->ExecuteMacro("AddTaskUPCforwardpPb.C"));
#else
    gROOT->LoadMacro("AliAnalysisTaskUPCforwardpPb.cxx++g");
    gROOT->LoadMacro("AddTaskUPCforwardpPb.C");
    AliAnalysisTaskUPCforwardpPb *task = AddTaskUPCforwardpPb();
#endif


    if(!mgr->InitAnalysis()) return;
    // mgr->SetDebugLevel(2);
    // mgr->PrintStatus();
    // mgr->SetUseProgressBar(1, 25);

    if(local) {
        // if you want to run locally, we need to define some input
        TChain* chain = new TChain("aodTree");
        // add a few files to the chain (change this so that your local files are added)

        // FILE *f = fopen("list2015Full.txt","r");
        FILE *f = fopen("list.txt","r");
        // FILE *f = fopen("listLHC18qrAndLHC15o.txt","r");
        // FILE *f = fopen("listPROVA.txt","r");
        char fileadd[300];
        Int_t flaggingValue = 0;
        while(fscanf(f,"%s",fileadd)==1){
            // chain->AddFile(fileadd);
            flaggingValue = chain->Add(fileadd);
            if(flaggingValue == 0) std::cout << fileadd << std::endl;
            flaggingValue = 0;
        }


        // chain->Add("AliAOD/*");

        // chain->Add("LHC18q/0001/*");
        // chain->Add("LHC18q/0002/*");
        // chain->Add("LHC18q/0003/*");
        // chain->Add("LHC18q/0004/*");
        // chain->Add("LHC18q/0005/*");
        // chain->Add("LHC18q/0006/*");
        // chain->Add("LHC18q/0007/*");
        // chain->Add("LHC18q/0008/*");
        // chain->Add("LHC18q/0009/*");

        // start the analysis locally, reading the events from the tchain
        mgr->StartAnalysis("local", chain);
    } else {
        // if we want to run on grid, we create and configure the plugin
        AliAnalysisAlien *alienHandler = new AliAnalysisAlien();
        // also specify the include (header) paths on grid
        alienHandler->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_ROOT -I$ALICE_ROOT/include -I$ALICE_PHYSICS/include");
        // make sure your source files get copied to grid
        alienHandler->SetAdditionalLibs("AliAnalysisTaskUPCforwardpPb.cxx AliAnalysisTaskUPCforwardpPb.h");
        alienHandler->SetAnalysisSource("AliAnalysisTaskUPCforwardpPb.cxx");
        // select the aliphysics version. all other packages
        // are LOADED AUTOMATICALLY!
        alienHandler->SetAliPhysicsVersion("vAN-20181028_ROOT6-1");
        // alienHandler->SetAliPhysicsVersion("vAN-20200608_ROOT6-1");
        // set the Alien API version
        alienHandler->SetAPIVersion("V1.1x");
        // select the input data for 2018 q
      	if (opt == 0) {
          /* -
           * - OLD DATASET
           * -
           */
          // alienHandler->SetGridDataDir("/alice/data/2016/LHC16s");
      	  // alienHandler->SetDataPattern("*muon_calo_pass3/AOD191/PWGUD/UD_pPb_AOD/126_20190119-1721/*AliAOD.UPCNano.root");
          // // MC has no prefix, data has prefix 000
          // alienHandler->SetRunPrefix("000");
          // // runnumber
          // alienHandler->AddRunNumber(267110);



          // alienHandler->SetGridDataDir("/alice/data/2016/LHC16r");
      	  // alienHandler->SetDataPattern("*muon_calo_pass2/AOD191/PWGUD/UD_pPb_AOD/125_20190119-1721/*AliAOD.UPCNano.root");
          // // MC has no prefix, data has prefix 000
          // alienHandler->SetRunPrefix("000");
          // // runnumber
          // alienHandler->AddRunNumber(265746);


          /* -
           * - NEW DATASET
           * -
           * - NB: Adding each run manually...
           * -
           */
          // alienHandler->SetGridDataDir("/alice/data/2016/LHC16s");
      	  // alienHandler->SetDataPattern("*pass1_UD/PWGUD/UD_pPb_AOD/144_20191104-1006/*AliAOD.UPCNano.root");
      	  // // MC has no prefix, data has prefix 000
      	  // alienHandler->SetRunPrefix("000");

          alienHandler->SetGridDataDir("/alice/data/2016/LHC16r");
      	  alienHandler->SetDataPattern("*pass1_UD/PWGUD/UD_pPb_AOD/143_20191104-1006/*AliAOD.UPCNano.root");
      	  // MC has no prefix, data has prefix 000
      	  alienHandler->SetRunPrefix("000");






      	  // runnumber
          /* - This is the standard run list.
           * - Below I am using a reduced run list
           * - to check if the problem was due to
           * - the inefficiency of the detector maybe!!!
           */
          // Int_t listOfGoodRunNumbersLHC16s[]  = { 267131, 267130, 267110, 267109, 267077, 267072, 267070, 267067, 267063, 267062,
          //                                         267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
          //                                         266940, 266915, 266912, 266886, 266885, 266883, 266882, 266880, 266878, 266857,
          //                                         266807, 266805, 266800, 266776, 266775, 266708, 266706, 266703, 266702, 266676,
          //                                         266674, 266669, 266668, 266665, 266659, 266658, 266657, 266630, 266621, 266618,
          //                                         /*266615,*/ 266614, 266613, 266595, 266593, 266591, 266588, 266587, 266584, 266549,
          //                                         266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, 266518, 266516,
          //                                         266514, 266487, 266480, 266479, 266472, 266441, 266439 };
          Int_t listOfGoodRunNumbersLHC16s[]  = { 267131, 267130, 267110, 267109, 267077, 267072, 267070, 267067, 267063, 267062,
                                                  267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
                                                  266940, 266915, 266912, 266886, 266885, 266883, 266882, 266880, 266878, 266857,
                                                  266807, 266805, 266800, 266776, 266775, 266708, 266706, 266703, 266702, 266676,
                                                  266674, 266669, 266668, 266665, 266659, 266658, 266657, 266630, 266621, 266618,
                                                  266614, 266613, 266595, 266593, 266591, 266588, 266587, 266584, 266549,
                                                  266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, 266518, 266516,
                                                  266514, 266487, 266480, 266479, 266472, 266441, 266439 };
          // for( Int_t iRunLHC16s = 0; iRunLHC16s <  76; iRunLHC16s++){
          //   alienHandler->AddRunNumber( listOfGoodRunNumbersLHC16s[iRunLHC16s] );
          // }
          Int_t listOfGoodRunNumbersLHC16r[]  = { 265589, 265594, 265596, 265607, 265669, 265691, 265694,
                                                  265697, 265698, 265700, 265701, 265709, 265713, 265714, 265740,
                                                  265741, 265742, 265744, 265746, 265754, 265756, 265785, 265787,
                                                  265788, 265789, 265792, 265795, 265797, 265840, 266022, 266023,
                                                  266025, 266034, 266074, 266076, 266081, 266084, 266085, 266086,
                                                  266117, 266187, 266189, 266190, 266193, 266196, 266197, 266208,
                                                  266234, 266235, 266296, 266299, 266300, 266304, 266305, 266312,
                                                  266316, 266318    };
          for( Int_t iRunLHC16r = 0; iRunLHC16r <  57; iRunLHC16r++){
            // // // if ( iRunLHC16r == 51 ) continue;
            alienHandler->AddRunNumber( listOfGoodRunNumbersLHC16r[iRunLHC16r] );
          }

      	} else {
      	  cout << " not a valid option ... bye!" << endl;
      	}

        // number of files per subjob
        alienHandler->SetSplitMaxInputFileNumber(10);
        alienHandler->SetExecutable("pPbLHC16s.sh");
        // specify how many seconds your job may take
        alienHandler->SetTTL(10000);
        alienHandler->SetJDLName("pPbLHC16s.jdl");

        alienHandler->SetOutputToRunNo(kTRUE);
        alienHandler->SetKeepLogs(kTRUE);
        // merging: run with "kTRUE" and "full" for normal run
        // to merge on grid run jobs in SetRunMode("terminate")
        // to collect final results set SetMergeViaJDL(kFALSE)
        alienHandler->SetMergeViaJDL(kTRUE);

        /* - The setting to kFALSE is to download the output files
           -
         */
        // alienHandler->SetMergeViaJDL(kFALSE);
        alienHandler->SetMaxMergeStages(1);


        TString LHC16s("LHC16s");
        // define the output folders
        alienHandler->SetGridWorkingDir("pPbLHC16r_New_rejected");
        // alienHandler->SetGridOutputDir("myOutputDir");
        if (opt == 0) alienHandler->SetGridOutputDir(LHC16s.Data());



        // connect the alien plugin to the manager
        mgr->SetGridHandler(alienHandler);
        if(gridTest) {
            // speficy on how many files you want to run
            alienHandler->SetNtestFiles(1);
            // and launch the analysis
            alienHandler->SetRunMode("test");
            mgr->StartAnalysis("grid");
        } else {
            // else launch the full grid analysis

            /* - The option FULL is to send the full analysis.
               -
             */
            // alienHandler->SetRunMode("full");

            /* - This option TERMINATE is used for the merging of the files.
               -
             */
            alienHandler->SetRunMode("terminate");
            mgr->StartAnalysis("grid");
        }
    }
}

/*
Welcome my dear ALICE user! To use ALICE software from CVMFS:
 * List all packages         --> alienv q
 * List AliPhysics packages  --> alienv q | grep -i aliphysics
 * Enable a specific package --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1
 * Enable multiple packages  --> alienv enter VO_ALICE@AliPhysics::vAN-20190114_ROOT6-1,VO_ALICE@fastjet::v3.2.1_1.024-alice3-7
 */
