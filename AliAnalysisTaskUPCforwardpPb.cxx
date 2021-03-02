/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// c++ headers
#include <iostream>
#include <fstream>
// #include <vector>
// #include <algorithm>


// root headers
#include <TMath.h>
#include "TH1I.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH1.h"
#include <TFile.h>
#include <TF2.h>
#include <TF1.h>
#include <TRandom.h>
#include <TGraph.h>
#include <TLegend.h>
#include <TGraphErrors.h>
#include <TPad.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TTree.h>
#include <TGraph2D.h>
#include <TStopwatch.h>
#include <TMatrixDSym.h>
#include <TFitResult.h>
#include <TLatex.h>
#include "TClonesArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TParticle.h"
#include "TObjString.h"
#include "TList.h"
#include "TChain.h"


// aliroot headers
#include "AliAnalysisTask.h"
#include "AliAnalysisManager.h"
#include "AliAODEvent.h"
#include "AliAODInputHandler.h"
#include "AliMuonTrackCuts.h"
#include "AliAODVertex.h"         // My addition, to use Eugeny Krishen's format

#include <bitset>


// my headers
#include "AliAnalysisTaskUPCforwardpPb.h"



class AliAnalysisTaskUPCforwardpPb;    // your analysis class

using namespace std;            // std namespace: so you can do things like 'cout'
typedef std::bitset<32> IntBits;

ClassImp(AliAnalysisTaskUPCforwardpPb) // classimp: necessary for root

//_____________________________________________________________________________
AliAnalysisTaskUPCforwardpPb::AliAnalysisTaskUPCforwardpPb()
    : AliAnalysisTaskSE(),
      fAOD(0),
      fOutputList(0),
      fNumberMuonsH(0),
      fCounterH(0),
      fEtaMuonH(0),
      fEtaDimuonH(0),
      fRAbsMuonH(0),
      fInvariantMassDistributionH(0),
      fInvariantMassDistributionLikeSignMuonsH(0),
      fInvariantMassDistributionRapidityBinsNewH{0,0},
      fInvariantMassDistributionHCMUP3(0),
      fInvariantMassDistributionHCMUP8(0),
      fInvariantMassDistributionHCMUP14(0),
      fInvariantMassDistributionHCMUP15(0),
      fInvariantMassDistributionHCMUP16(0),
      fInvariantMassDistributionHCMUP17(0),
      fInvariantMassDistributionHCMUP18(0),
      fInvariantMassDistributionHCMUP19(0),
      fInvariantMassDistributionHCMUP20(0),
      fInvariantMassDistributionHCMUP21(0),
      fInvariantMassDistributionHCMUP22(0),
      fInvariantMassDistributionHCMUP23(0),
      fInvariantMassDistributionHV0ADec(0),
      fInvariantMassDistributionHV0CDec(0),
      fInvariantMassDistributionHADADec(0),
      fInvariantMassDistributionHADCDec(0),
      fInvariantMassDistributionHV0Ccells(0),
      fInvariantMassDistributionRapidityBinsH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBinsH{ 0, 0, 0 },
      fInvariantMassDistribution0N0NH(0),
      fInvariantMassDistributionRapidityBins0N0NH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBins0N0NH{ 0, 0, 0 },
      fInvariantMassDistributionZeroZNCH(0),
      fInvariantMassDistributionRapidityBinsZeroZNCH{ 0, 0 },
      fInvariantMassDistributionRapidityThreeBinsZeroZNCH{ 0, 0, 0 },
      fInvariantMassDistributionRapidityFourBinsZeroZNCH{ 0, 0, 0, 0 },
      fInvariantMassDistributionRapidityFiveBinsZeroZNCH{ 0, 0, 0, 0, 0 },
      fInvariantMassDistributionZeroZNAH(0),
      fInvariantMassDistributionRapidityBinsZeroZNAH{ 0, 0 },
      fInvariantMassDistributionRapidityThreeBinsZeroZNAH{ 0, 0, 0 },
      fInvariantMassDistributionRapidityFourBinsZeroZNAH{ 0, 0, 0, 0 },
      fInvariantMassDistributionRapidityFiveBinsZeroZNAH{ 0, 0, 0, 0, 0 },
      fInvariantMassDistributionZeroZNCenergyH(0),
      fInvariantMassDistributionRapidityBinsZeroZNCenergyH{ 0, 0 },
      fInvariantMassDistributionZeroZNAenergyH(0),
      fInvariantMassDistributionRapidityBinsZeroZNAenergyH{ 0, 0 },
      fInvariantMassDistributionSmall0N0NH(0),
      fInvariantMassDistributionRapidityBinsSmall0N0NH{ 0, 0 },
      fInvariantMassDistributionOneNeutronZNCH(0),
      fInvariantMassDistributionOneNeutronZNAH(0),
      fDimuonPtDistributionOneNeutronZNCH(0),
      fDimuonPtDistributionOneNeutronZNAH(0),
      fEntriesAgainstRunNumberH(0),
      fEntriesAgainstRunNumberProperlyH(0),
      fRunNumberTriggerCMUP11ClassH(0),
      fRunNumberTriggerCMUP11ClassProperlyH(0),
      fRunNumberTriggerCMUP26ClassH(0),
      fRunNumberTriggerCMUP26ClassProperlyH(0),
      fRunNumberTriggerCMUP6ClassH(0),
      fRunNumberTriggerCMUP6ClassProperlyH(0),
      fRunNumberTriggerCMUP10ClassH(0),
      fRunNumberTriggerCMUP10ClassProperlyH(0),
      fRunNumberTriggerCMUP13ClassH(0),
      fRunNumberTriggerCMUP13ClassProperlyH(0),
      fTriggersVsRunH(0),
      fInvariantMassDistributionCoherentH(0),
      fInvariantMassDistributionCoherentRapidityBinsH{ 0, 0, 0, 0, 0, 0 },
      fInvariantMassDistributionCoherentShiftMinusTwoH(0),
      fInvariantMassDistributionCoherentShiftMinusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusTwoH(0),
      fInvariantMassDistributionIncoherentH(0),
      fInvariantMassDistributionIncoherentShiftMinusTwoH(0),
      fInvariantMassDistributionIncoherentShiftMinusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusTwoH(0),
      fDimuonPtDistributionH(0),
      fDimuonPtDistributionRestrictedRapidity0N0NH(0),
      fDimuonPtDistributionRestrictedRapidity0N0N36to31H(0),
      fDimuonPtDistributionRestrictedRapidity0N0N31to26H(0),
      fDimuonPtDistributionRestrictedRapidity0N0NHv3(0),
      fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3(0),
      fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3(0),
      fPtSidebandZeroZNCH(0),
      fPtSidebandZeroZNAH(0),
      fPtSidebandZeroZNARapidityH{0,0,0},
      fPtSidebandZeroZNCRapidityH{0,0,0},
      fPtSidebandZeroZNCRapidityAndMassH{0,0,0,0,0,0, 0,0,0,0,0,0},
      fPtSidebandZeroZNARapidityAndMassH{0,0,0,0,0,0, 0,0,0,0,0,0},
      fDimuonPtDistributionZeroZNAH(0),
      fDimuonPtDistributionZeroZNAbinsH{0,0},
      fDimuonPtDistributionZeroZNAfourbinsH{0,0,0,0},
      fDimuonPtDistributionZeroZNAthreebinsH{0,0,0},
      fDimuonPtDistributionZeroZNAfivebinsH{0,0,0,0,0},
      fDimuonPtDistributionZeroZNCH(0),
      fDimuonPtDistributionZeroZNCbinsH{0,0},
      fDimuonPtDistributionZeroZNCthreebinsH{0,0,0},
      fDimuonPtDistributionZeroZNCfourbinsH{0,0,0,0},
      fDimuonPtDistributionZeroZNCfivebinsH{0,0,0,0,0},
      fInvariantMassDistributionExtendedH(0),
      fInvariantMassDistributionCoherentExtendedH(0),
      fInvariantMassDistributionIncoherentExtendedH(0),
      fZNCEnergyAgainstEntriesH(0),
      fZNAEnergyAgainstEntriesH(0),
      fZNCEnergyBeforeTimingSelectionH(0),
      fZNAEnergyBeforeTimingSelectionH(0),
      fZNCEnergyAgainstEntriesExtendedH(0),
      fZNAEnergyAgainstEntriesExtendedH(0),
      fZNCEnergyAgainstEntriesExtendedHv2(0),
      fZNAEnergyAgainstEntriesExtendedHv2(0),
      fZNCEnergyBeforeTimingSelectionExtendedH(0),
      fZNAEnergyBeforeTimingSelectionExtendedH(0),
      fMuonTrackCuts(0x0),
      fRunNum(0),
      fTracklets(0),
      fL0inputs(0),
      fL1inputs(0),
      fZem1Energy(0),
      fZem2Energy(0),
      fZNCEnergy(0),
      fZNAEnergy(0),
      fZPCEnergy(0),
      fZPAEnergy(0),
      fZNATime(0),
      fZNCTime(0),
      fV0ADecision(-10),
      fV0CDecision(-10),
      fADADecision(-10),
      fADCDecision(-10),
      fIR1Map(0),
      fIR2Map(0),
      fZNATDC{0, 0, 0, 0},
      fZNCTDC{0, 0, 0, 0},
      fZPATDC{0, 0, 0, 0},
      fZPCTDC{0, 0, 0, 0},
      fV0Hits{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      fV0TotalNCells(0),
      fVZEROhitsH(0),
      fVZEROhitsWithVZEROCcutH(0),
      fVZEROhitsMoreThanFiveVZEROCcellsH(0),
      fVZEROCNumberOfHitsSameEventH(0),
      fVZEROANumberOfHitsSameEventH(0),
      fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH(0),
      fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH(0),
      fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH(0),
      fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH(0),
      fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH(0),
      fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH(0),
      fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH(0),
      fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH(0),
      fVZEROhitsInnerRingsH(0),
      fVZEROhitsOuterRingH(0),
      fEventTaggedVZEROCH(0),
      fEventNotTaggedVZEROCH(0),
      fIdentityOfVZEROCH(0),
      fIROneH(0),
      fIRTwoH(0),
      fDimuonPtDistributionOuterRingH(0),
      fDimuonPtDistributionAtLeastOneMuonOuterRingH(0),
      fDimuonPtDistributionSecondRingH(0),
      fDimuonPtDistributionCorrelationVZEROH(0),
      fDimuonPtDistributionNullIROneH(0),
      fDimuonPtDistributionNullIRTwoH(0),
      fDimuonPtDistributionNegativeIROneH(0),
      fDimuonPtDistributionNegativeIRTwoH(0),
      fDimuonPtDistributionPositiveIROneH(0),
      fDimuonPtDistributionPositiveIRTwoH(0),
      fInvariantMassDistributionZeroZNC37to37H{0,0},
      fInvariantMassDistributionZeroZNA37to37H{0,0},
      fDimuonPtDistributionZeroZNCbins27to37H{0,0},
      fDimuonPtDistributionZeroZNAbins27to37H{0,0},
      fRapidityShapeH(0),
      fRapidityShapeAtDCAH(0),
      fRapidityShapeADAdecH(0),
      fRapidityShapeADAdecAtDCAH(0),
      fRapidityShapeADCdecH(0),
      fRapidityShapeADCdecAtDCAH(0),
      fRapidityShapeADdecH(0),
      fRapidityShapeADdecAtDCAH(0),
      fZNCEnergyAfterTimingVsADAMultiH(0),
      fZNCEnergyAfterTimingVsADCMultiH(0),
      fZNCEnergyAfterTimingVsADMultiH(0),
      fZNCEnergyBeforeTimingVsADAMultiH(0),
      fZNCEnergyBeforeTimingVsADCMultiH(0),
      fZNCEnergyBeforeTimingVsADMultiH(0),
      fZNAEnergyAfterTimingVsADAMultiH(0),
      fZNAEnergyAfterTimingVsADCMultiH(0),
      fZNAEnergyAfterTimingVsADMultiH(0),
      fZNAEnergyBeforeTimingVsADAMultiH(0),
      fZNAEnergyBeforeTimingVsADCMultiH(0),
      fZNAEnergyBeforeTimingVsADMultiH(0),
      fPhiSameSignZeroTrkH(0),
      fPhiSameSignOneTrkH(0),
      fPhiSameSignTwoTrkH(0),
      fPtSameSignZeroTrkH(0),
      fPtSameSignOneTrkH(0),
      fPtSameSignTwoTrkH(0),
      fRapSameSignZeroTrkH(0),
      fRapSameSignOneTrkH(0),
      fRapSameSignTwoTrkH(0),
      fMassSameSignZeroTrkH(0),
      fMassSameSignOneTrkH(0),
      fMassSameSignTwoTrkH(0),
      fDimuonPtDistributionRejectedZNAflagH(0),
      fDimuonPtDistributionRejectedZNCflagH(0),
      fDimuonPtDistributionGammaGammaZNAH(0),
      fDimuonPtDistributionGammaGammaZNCH(0)
{
    // default constructor, don't allocate memory here!
    // this is used by root for IO purposes, it needs to remain empty
}

//_____________________________________________________________________________
AliAnalysisTaskUPCforwardpPb::AliAnalysisTaskUPCforwardpPb(const char* name)
    : AliAnalysisTaskSE(name),
      fAOD(0),
      fOutputList(0),
      fNumberMuonsH(0),
      fCounterH(0),
      fEtaMuonH(0),
      fEtaDimuonH(0),
      fRAbsMuonH(0),
      fInvariantMassDistributionH(0),
      fInvariantMassDistributionLikeSignMuonsH(0),
      fInvariantMassDistributionRapidityBinsNewH{0,0},
      fInvariantMassDistributionHCMUP3(0),
      fInvariantMassDistributionHCMUP8(0),
      fInvariantMassDistributionHCMUP14(0),
      fInvariantMassDistributionHCMUP15(0),
      fInvariantMassDistributionHCMUP16(0),
      fInvariantMassDistributionHCMUP17(0),
      fInvariantMassDistributionHCMUP18(0),
      fInvariantMassDistributionHCMUP19(0),
      fInvariantMassDistributionHCMUP20(0),
      fInvariantMassDistributionHCMUP21(0),
      fInvariantMassDistributionHCMUP22(0),
      fInvariantMassDistributionHCMUP23(0),
      fInvariantMassDistributionHV0ADec(0),
      fInvariantMassDistributionHV0CDec(0),
      fInvariantMassDistributionHADADec(0),
      fInvariantMassDistributionHADCDec(0),
      fInvariantMassDistributionHV0Ccells(0),
      fInvariantMassDistributionRapidityBinsH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBinsH{ 0, 0, 0 },
      fInvariantMassDistribution0N0NH(0),
      fInvariantMassDistributionRapidityBins0N0NH{ 0, 0 },
      fInvariantMassDistributionMoreRapidityBins0N0NH{ 0, 0, 0 },
      fInvariantMassDistributionZeroZNCH(0),
      fInvariantMassDistributionRapidityBinsZeroZNCH{ 0, 0 },
      fInvariantMassDistributionRapidityFourBinsZeroZNCH{ 0, 0, 0, 0 },
      fInvariantMassDistributionRapidityThreeBinsZeroZNCH{ 0, 0, 0 },
      fInvariantMassDistributionRapidityFiveBinsZeroZNCH{ 0, 0, 0, 0, 0 },
      fInvariantMassDistributionZeroZNAH(0),
      fInvariantMassDistributionRapidityBinsZeroZNAH{ 0, 0 },
      fInvariantMassDistributionRapidityFourBinsZeroZNAH{ 0, 0, 0, 0 },
      fInvariantMassDistributionRapidityThreeBinsZeroZNAH{ 0, 0, 0 },
      fInvariantMassDistributionRapidityFiveBinsZeroZNAH{ 0, 0, 0, 0, 0 },
      fInvariantMassDistributionZeroZNCenergyH(0),
      fInvariantMassDistributionRapidityBinsZeroZNCenergyH{ 0, 0 },
      fInvariantMassDistributionZeroZNAenergyH(0),
      fInvariantMassDistributionRapidityBinsZeroZNAenergyH{ 0, 0 },
      fInvariantMassDistributionSmall0N0NH(0),
      fInvariantMassDistributionRapidityBinsSmall0N0NH{ 0, 0 },
      fInvariantMassDistributionOneNeutronZNCH(0),
      fInvariantMassDistributionOneNeutronZNAH(0),
      fDimuonPtDistributionOneNeutronZNCH(0),
      fDimuonPtDistributionOneNeutronZNAH(0),
      fEntriesAgainstRunNumberH(0),
      fEntriesAgainstRunNumberProperlyH(0),
      fRunNumberTriggerCMUP11ClassH(0),
      fRunNumberTriggerCMUP11ClassProperlyH(0),
      fRunNumberTriggerCMUP26ClassH(0),
      fRunNumberTriggerCMUP26ClassProperlyH(0),
      fRunNumberTriggerCMUP6ClassH(0),
      fRunNumberTriggerCMUP6ClassProperlyH(0),
      fRunNumberTriggerCMUP10ClassH(0),
      fRunNumberTriggerCMUP10ClassProperlyH(0),
      fRunNumberTriggerCMUP13ClassH(0),
      fRunNumberTriggerCMUP13ClassProperlyH(0),
      fTriggersVsRunH(0),
      fInvariantMassDistributionCoherentH(0),
      fInvariantMassDistributionCoherentRapidityBinsH{ 0, 0, 0, 0, 0, 0 },
      fInvariantMassDistributionCoherentShiftMinusTwoH(0),
      fInvariantMassDistributionCoherentShiftMinusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusOneH(0),
      fInvariantMassDistributionCoherentShiftPlusTwoH(0),
      fInvariantMassDistributionIncoherentH(0),
      fInvariantMassDistributionIncoherentShiftMinusTwoH(0),
      fInvariantMassDistributionIncoherentShiftMinusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusOneH(0),
      fInvariantMassDistributionIncoherentShiftPlusTwoH(0),
      fDimuonPtDistributionH(0),
      fDimuonPtDistributionRestrictedRapidity0N0NH(0),
      fDimuonPtDistributionRestrictedRapidity0N0N36to31H(0),
      fDimuonPtDistributionRestrictedRapidity0N0N31to26H(0),
      fDimuonPtDistributionRestrictedRapidity0N0NHv3(0),
      fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3(0),
      fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3(0),
      fPtSidebandZeroZNCH(0),
      fPtSidebandZeroZNAH(0),
      fPtSidebandZeroZNARapidityH{0,0,0},
      fPtSidebandZeroZNCRapidityH{0,0,0},
      fPtSidebandZeroZNCRapidityAndMassH{0,0,0,0,0,0, 0,0,0,0,0,0},
      fPtSidebandZeroZNARapidityAndMassH{0,0,0,0,0,0, 0,0,0,0,0,0},
      fDimuonPtDistributionZeroZNAH(0),
      fDimuonPtDistributionZeroZNAbinsH{0,0},
      fDimuonPtDistributionZeroZNAfourbinsH{0,0,0,0},
      fDimuonPtDistributionZeroZNAthreebinsH{0,0,0},
      fDimuonPtDistributionZeroZNAfivebinsH{0,0,0,0,0},
      fDimuonPtDistributionZeroZNCH(0),
      fDimuonPtDistributionZeroZNCbinsH{0,0},
      fDimuonPtDistributionZeroZNCthreebinsH{0,0,0},
      fDimuonPtDistributionZeroZNCfourbinsH{0,0,0,0},
      fDimuonPtDistributionZeroZNCfivebinsH{0,0,0,0,0},
      fInvariantMassDistributionExtendedH(0),
      fInvariantMassDistributionCoherentExtendedH(0),
      fInvariantMassDistributionIncoherentExtendedH(0),
      fZNCEnergyAgainstEntriesH(0),
      fZNAEnergyAgainstEntriesH(0),
      fZNCEnergyBeforeTimingSelectionH(0),
      fZNAEnergyBeforeTimingSelectionH(0),
      fZNCEnergyAgainstEntriesExtendedH(0),
      fZNAEnergyAgainstEntriesExtendedH(0),
      fZNCEnergyAgainstEntriesExtendedHv2(0),
      fZNAEnergyAgainstEntriesExtendedHv2(0),
      fZNCEnergyBeforeTimingSelectionExtendedH(0),
      fZNAEnergyBeforeTimingSelectionExtendedH(0),
      fMuonTrackCuts(0x0),
      fRunNum(0),
      fTracklets(0),
      fL0inputs(0),
      fL1inputs(0),
      fZem1Energy(0),
      fZem2Energy(0),
      fZNCEnergy(0),
      fZNAEnergy(0),
      fZPCEnergy(0),
      fZPAEnergy(0),
      fZNATime(0),
      fZNCTime(0),
      fV0ADecision(-10),
      fV0CDecision(-10),
      fADADecision(-10),
      fADCDecision(-10),
      fIR1Map(0),
      fIR2Map(0),
      fZNATDC{0, 0, 0, 0},
      fZNCTDC{0, 0, 0, 0},
      fZPATDC{0, 0, 0, 0},
      fZPCTDC{0, 0, 0, 0},
      fV0Hits{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
      fV0TotalNCells(0),
      fVZEROhitsH(0),
      fVZEROhitsWithVZEROCcutH(0),
      fVZEROhitsMoreThanFiveVZEROCcellsH(0),
      fVZEROCNumberOfHitsSameEventH(0),
      fVZEROANumberOfHitsSameEventH(0),
      fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH(0),
      fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH(0),
      fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH(0),
      fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH(0),
      fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH(0),
      fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH(0),
      fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH(0),
      fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH(0),
      fVZEROhitsInnerRingsH(0),
      fVZEROhitsOuterRingH(0),
      fEventTaggedVZEROCH(0),
      fEventNotTaggedVZEROCH(0),
      fIdentityOfVZEROCH(0),
      fIROneH(0),
      fIRTwoH(0),
      fDimuonPtDistributionOuterRingH(0),
      fDimuonPtDistributionAtLeastOneMuonOuterRingH(0),
      fDimuonPtDistributionSecondRingH(0),
      fDimuonPtDistributionCorrelationVZEROH(0),
      fDimuonPtDistributionNullIROneH(0),
      fDimuonPtDistributionNullIRTwoH(0),
      fDimuonPtDistributionNegativeIROneH(0),
      fDimuonPtDistributionNegativeIRTwoH(0),
      fDimuonPtDistributionPositiveIROneH(0),
      fDimuonPtDistributionPositiveIRTwoH(0),
      fInvariantMassDistributionZeroZNC37to37H{0,0},
      fInvariantMassDistributionZeroZNA37to37H{0,0},
      fDimuonPtDistributionZeroZNCbins27to37H{0,0},
      fDimuonPtDistributionZeroZNAbins27to37H{0,0},
      fRapidityShapeH(0),
      fRapidityShapeAtDCAH(0),
      fRapidityShapeADAdecH(0),
      fRapidityShapeADAdecAtDCAH(0),
      fRapidityShapeADCdecH(0),
      fRapidityShapeADCdecAtDCAH(0),
      fRapidityShapeADdecH(0),
      fRapidityShapeADdecAtDCAH(0),
      fZNCEnergyAfterTimingVsADAMultiH(0),
      fZNCEnergyAfterTimingVsADCMultiH(0),
      fZNCEnergyAfterTimingVsADMultiH(0),
      fZNCEnergyBeforeTimingVsADAMultiH(0),
      fZNCEnergyBeforeTimingVsADCMultiH(0),
      fZNCEnergyBeforeTimingVsADMultiH(0),
      fZNAEnergyAfterTimingVsADAMultiH(0),
      fZNAEnergyAfterTimingVsADCMultiH(0),
      fZNAEnergyAfterTimingVsADMultiH(0),
      fZNAEnergyBeforeTimingVsADAMultiH(0),
      fZNAEnergyBeforeTimingVsADCMultiH(0),
      fZNAEnergyBeforeTimingVsADMultiH(0),
      fPhiSameSignZeroTrkH(0),
      fPhiSameSignOneTrkH(0),
      fPhiSameSignTwoTrkH(0),
      fPtSameSignZeroTrkH(0),
      fPtSameSignOneTrkH(0),
      fPtSameSignTwoTrkH(0),
      fRapSameSignZeroTrkH(0),
      fRapSameSignOneTrkH(0),
      fRapSameSignTwoTrkH(0),
      fMassSameSignZeroTrkH(0),
      fMassSameSignOneTrkH(0),
      fMassSameSignTwoTrkH(0),
      fDimuonPtDistributionRejectedZNAflagH(0),
      fDimuonPtDistributionRejectedZNCflagH(0),
      fDimuonPtDistributionGammaGammaZNAH(0),
      fDimuonPtDistributionGammaGammaZNCH(0)

{

    // constructor
    DefineInput(0, TChain::Class());    // define the input of the analysis: in this case we take a 'chain' of events
                                        // this chain is created by the analysis manager, so no need to worry about it,
                                        // it does its work automatically
    DefineOutput(1, TList::Class());    // define the ouptut of the analysis: in this case it's a list of histograms
                                        // you can add more output objects by calling DefineOutput(2, classname::Class())
                                        // if you add more output objects, make sure to call PostData for all of them, and to
                                        // make changes to your AddTask macro!
}
//_____________________________________________________________________________
AliAnalysisTaskUPCforwardpPb::~AliAnalysisTaskUPCforwardpPb()
{
    // destructor
    if(fOutputList)    {delete fOutputList;}     	// at the end of your task, it is deleted
    if(fMuonTrackCuts) {delete fMuonTrackCuts;}   // from memory by calling this function
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::UserCreateOutputObjects()
{
  // create output objects
  //
  // this function is called ONCE at the start of your analysis (RUNTIME)
  // here you ceate the histograms that you want to use
  //
  // the histograms are in this case added to a tlist, this list is in the end saved
  // to an output file
  //

  //muon track cuts
  fMuonTrackCuts = new AliMuonTrackCuts("StdMuonCuts", "StdMuonCuts");
  fMuonTrackCuts->SetFilterMask(    AliMuonTrackCuts::kMuEta     |
                                    AliMuonTrackCuts::kMuThetaAbs|
                                    AliMuonTrackCuts::kMuPdca    |
                                    AliMuonTrackCuts::kMuMatchLpt
                                  );
  fMuonTrackCuts->SetAllowDefaultParams(kTRUE);
  fMuonTrackCuts->Print("mask");



  fOutputList = new TList();          // this is a list which will contain all
                                      // of your histograms at the end of the
                                      // analysis, the contents of this list
                                      // are written to the output file

  fOutputList->SetOwner(kTRUE);       // memory management: the list is owner
                                      // of all objects it contains and will
                                      // delete them if requested

  //_______________________________
  // - Adding histograms
  fNumberMuonsH = new TH1F("fNumberMuonsH", "fNumberMuonsH", 12, -0.5, 11.5);
  fOutputList->Add(fNumberMuonsH);    // don't forget to add it to the list!

  fCounterH = new TH1F("fCounterH", "fCounterH", 200, -0.5, 199.5);
  fOutputList->Add(fCounterH);

  fEtaMuonH = new TH1F("fEtaMuonH", "fEtaMuonH", 160, -1, -5);
  fOutputList->Add(fEtaMuonH);

  fEtaDimuonH = new TH1F("fEtaDimuonH", "fEtaDimuonH", 160, -1, -5);
  fOutputList->Add(fEtaDimuonH);

  fRAbsMuonH = new TH1F("fRAbsMuonH", "fRAbsMuonH", 100, 0, 100);
  fOutputList->Add(fRAbsMuonH);

  fInvariantMassDistributionH = new TH1F("fInvariantMassDistributionH", "fInvariantMassDistributionH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionH);

  fInvariantMassDistributionLikeSignMuonsH = new TH1F("fInvariantMassDistributionLikeSignMuonsH", "fInvariantMassDistributionLikeSignMuonsH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionLikeSignMuonsH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsNewH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsNewH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsNewH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsNewH[iRapidity]);
  }

  fInvariantMassDistributionHCMUP3 = new TH1F("fInvariantMassDistributionHCMUP3", "fInvariantMassDistributionHCMUP3", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP3);

  fInvariantMassDistributionHCMUP8 = new TH1F("fInvariantMassDistributionHCMUP8", "fInvariantMassDistributionHCMUP8", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP8);

  fInvariantMassDistributionHCMUP14 = new TH1F("fInvariantMassDistributionHCMUP14", "fInvariantMassDistributionHCMUP14", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP14);

  fInvariantMassDistributionHCMUP15 = new TH1F("fInvariantMassDistributionHCMUP15", "fInvariantMassDistributionHCMUP15", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP15);

  fInvariantMassDistributionHCMUP16 = new TH1F("fInvariantMassDistributionHCMUP16", "fInvariantMassDistributionHCMUP16", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP16);

  fInvariantMassDistributionHCMUP17 = new TH1F("fInvariantMassDistributionHCMUP17", "fInvariantMassDistributionHCMUP17", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP17);

  fInvariantMassDistributionHCMUP18 = new TH1F("fInvariantMassDistributionHCMUP18", "fInvariantMassDistributionHCMUP18", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP18);

  fInvariantMassDistributionHCMUP19 = new TH1F("fInvariantMassDistributionHCMUP19", "fInvariantMassDistributionHCMUP19", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP19);

  fInvariantMassDistributionHCMUP20 = new TH1F("fInvariantMassDistributionHCMUP20", "fInvariantMassDistributionHCMUP20", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP20);

  fInvariantMassDistributionHCMUP21 = new TH1F("fInvariantMassDistributionHCMUP21", "fInvariantMassDistributionHCMUP21", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP21);

  fInvariantMassDistributionHCMUP22 = new TH1F("fInvariantMassDistributionHCMUP22", "fInvariantMassDistributionHCMUP22", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP22);

  fInvariantMassDistributionHCMUP23 = new TH1F("fInvariantMassDistributionHCMUP23", "fInvariantMassDistributionHCMUP23", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHCMUP23);

  fInvariantMassDistributionHV0ADec = new TH1F("fInvariantMassDistributionHV0ADec", "fInvariantMassDistributionHV0ADec", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHV0ADec);

  fInvariantMassDistributionHV0CDec = new TH1F("fInvariantMassDistributionHV0CDec", "fInvariantMassDistributionHV0CDec", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHV0CDec);

  fInvariantMassDistributionHV0Ccells = new TH1F("fInvariantMassDistributionHV0Ccells", "fInvariantMassDistributionHV0Ccells", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHV0Ccells);

  fInvariantMassDistributionHADADec = new TH1F("fInvariantMassDistributionHADADec", "fInvariantMassDistributionHADADec", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHADADec);

  fInvariantMassDistributionHADCDec = new TH1F("fInvariantMassDistributionHADCDec", "fInvariantMassDistributionHADCDec", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionHADCDec);



  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fInvariantMassDistributionMoreRapidityBinsH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionMoreRapidityBinsH_%d", iRapidity),
                        Form("fInvariantMassDistributionMoreRapidityBinsH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionMoreRapidityBinsH[iRapidity]);
  }

  fInvariantMassDistribution0N0NH = new TH1F("fInvariantMassDistribution0N0NH", "fInvariantMassDistribution0N0NH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistribution0N0NH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBins0N0NH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBins0N0NH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBins0N0NH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBins0N0NH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fInvariantMassDistributionMoreRapidityBins0N0NH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionMoreRapidityBins0N0NH_%d", iRapidity),
                        Form("fInvariantMassDistributionMoreRapidityBins0N0NH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionMoreRapidityBins0N0NH[iRapidity]);
  }

  fInvariantMassDistributionOneNeutronZNAH = new TH1F("fInvariantMassDistributionOneNeutronZNAH", "fInvariantMassDistributionOneNeutronZNAH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionOneNeutronZNAH);

  fInvariantMassDistributionOneNeutronZNCH = new TH1F("fInvariantMassDistributionOneNeutronZNCH", "fInvariantMassDistributionOneNeutronZNCH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionOneNeutronZNCH);

  fDimuonPtDistributionOneNeutronZNAH = new TH1F("fDimuonPtDistributionOneNeutronZNAH", "fDimuonPtDistributionOneNeutronZNAH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionOneNeutronZNAH);

  fDimuonPtDistributionOneNeutronZNCH = new TH1F("fDimuonPtDistributionOneNeutronZNCH", "fDimuonPtDistributionOneNeutronZNCH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionOneNeutronZNCH);

  fInvariantMassDistributionZeroZNAH = new TH1F("fInvariantMassDistributionZeroZNAH", "fInvariantMassDistributionZeroZNAH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionZeroZNAH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsZeroZNAH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsZeroZNAH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsZeroZNAH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsZeroZNAH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fInvariantMassDistributionRapidityThreeBinsZeroZNAH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityThreeBinsZeroZNAH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityThreeBinsZeroZNAH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityThreeBinsZeroZNAH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 4; iRapidity++ ) {
    fInvariantMassDistributionRapidityFourBinsZeroZNAH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityFourBinsZeroZNAH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityFourBinsZeroZNAH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityFourBinsZeroZNAH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 5; iRapidity++ ) {
    fInvariantMassDistributionRapidityFiveBinsZeroZNAH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityFiveBinsZeroZNAH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityFiveBinsZeroZNAH[iRapidity]);
  }

  fInvariantMassDistributionZeroZNCH = new TH1F("fInvariantMassDistributionZeroZNCH", "fInvariantMassDistributionZeroZNCH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionZeroZNCH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsZeroZNCH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsZeroZNCH%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsZeroZNCH%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsZeroZNCH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fInvariantMassDistributionRapidityThreeBinsZeroZNCH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityThreeBinsZeroZNCH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityThreeBinsZeroZNCH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityThreeBinsZeroZNCH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 4; iRapidity++ ) {
    fInvariantMassDistributionRapidityFourBinsZeroZNCH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityFourBinsZeroZNCH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityFourBinsZeroZNCH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityFourBinsZeroZNCH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 5; iRapidity++ ) {
    fInvariantMassDistributionRapidityFiveBinsZeroZNCH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityFiveBinsZeroZNCH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityFiveBinsZeroZNCH[iRapidity]);
  }

  fInvariantMassDistributionZeroZNAenergyH = new TH1F("fInvariantMassDistributionZeroZNAenergyH", "fInvariantMassDistributionZeroZNAenergyH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionZeroZNAenergyH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsZeroZNAenergyH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsZeroZNAenergyH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsZeroZNAenergyH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsZeroZNAenergyH[iRapidity]);
  }

  fInvariantMassDistributionZeroZNCenergyH = new TH1F("fInvariantMassDistributionZeroZNCenergyH", "fInvariantMassDistributionZeroZNCenergyH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionZeroZNCenergyH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsZeroZNCenergyH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsZeroZNCenergyH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsZeroZNCenergyH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsZeroZNCenergyH[iRapidity]);
  }

  fInvariantMassDistributionSmall0N0NH = new TH1F("fInvariantMassDistributionSmall0N0NH", "fInvariantMassDistributionSmall0N0NH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionSmall0N0NH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionRapidityBinsSmall0N0NH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionRapidityBinsSmall0N0NH_%d", iRapidity),
                        Form("fInvariantMassDistributionRapidityBinsSmall0N0NH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionRapidityBinsSmall0N0NH[iRapidity]);
  }


  fEntriesAgainstRunNumberH = new TH1F("fEntriesAgainstRunNumberH", "fEntriesAgainstRunNumberH", 10000, 290000, 300000);
  fOutputList->Add(fEntriesAgainstRunNumberH);

  /* - Trying to reproduce the histogram for the RunNumbers as they always
     - show it, properly labelled. Inspiration has come from the website:
     - https://root.cern.ch/doc/master/hlabels1_8C.html
     - Let us see if it works properly.
     -
   */
  fEntriesAgainstRunNumberProperlyH = new TH1F("fEntriesAgainstRunNumberProperlyH", "fEntriesAgainstRunNumberProperlyH", 10000, 290000, 300000);
  fEntriesAgainstRunNumberProperlyH->SetStats(0);
  fEntriesAgainstRunNumberProperlyH->SetFillColor(38);
  // fEntriesAgainstRunNumberProperlyH->SetCanExtend(TH1::kAllAxes);
  fEntriesAgainstRunNumberProperlyH->LabelsDeflate();
  fOutputList->Add(fEntriesAgainstRunNumberProperlyH);

  fRunNumberTriggerCMUP11ClassH = new TH1F("fRunNumberTriggerCMUP11ClassH", "fRunNumberTriggerCMUP11ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP11ClassH);

  fRunNumberTriggerCMUP11ClassProperlyH = new TH1F("fRunNumberTriggerCMUP11ClassProperlyH", "fRunNumberTriggerCMUP11ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP11ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP11ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP11ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP11ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP11ClassProperlyH);

  fRunNumberTriggerCMUP26ClassH = new TH1F("fRunNumberTriggerCMUP26ClassH", "fRunNumberTriggerCMUP26ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP26ClassH);

  fRunNumberTriggerCMUP26ClassProperlyH = new TH1F("fRunNumberTriggerCMUP26ClassProperlyH", "fRunNumberTriggerCMUP26ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP26ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP26ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP26ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP26ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP26ClassProperlyH);

  fRunNumberTriggerCMUP6ClassH = new TH1F("fRunNumberTriggerCMUP6ClassH", "fRunNumberTriggerCMUP6ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP6ClassH);

  fRunNumberTriggerCMUP6ClassProperlyH = new TH1F("fRunNumberTriggerCMUP6ClassProperlyH", "fRunNumberTriggerCMUP6ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP6ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP6ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP6ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP6ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP6ClassProperlyH);

  fRunNumberTriggerCMUP10ClassH = new TH1F("fRunNumberTriggerCMUP10ClassH", "fRunNumberTriggerCMUP10ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP10ClassH);

  fRunNumberTriggerCMUP10ClassProperlyH = new TH1F("fRunNumberTriggerCMUP10ClassProperlyH", "fRunNumberTriggerCMUP10ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP10ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP10ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP10ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP10ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP10ClassProperlyH);

  fRunNumberTriggerCMUP13ClassH = new TH1F("fRunNumberTriggerCMUP13ClassH", "fRunNumberTriggerCMUP13ClassH", 10000, 290000, 300000);
  fOutputList->Add(fRunNumberTriggerCMUP13ClassH);

  fRunNumberTriggerCMUP13ClassProperlyH = new TH1F("fRunNumberTriggerCMUP13ClassProperlyH", "fRunNumberTriggerCMUP13ClassProperlyH", 10000, 290000, 300000);
  fRunNumberTriggerCMUP13ClassProperlyH->SetStats(0);
  fRunNumberTriggerCMUP13ClassProperlyH->SetFillColor(38);
  // fRunNumberTriggerCMUP13ClassProperlyH->SetCanExtend(TH1::kAllAxes);
  fRunNumberTriggerCMUP13ClassProperlyH->LabelsDeflate();
  fOutputList->Add(fRunNumberTriggerCMUP13ClassProperlyH);

  // fTriggersVsRunH = new TH2F("fTriggersVsRunH","",5,0,5,60000,240000,300000);
  fTriggersVsRunH = new TH2F("fTriggersVsRunH","",15,0,15,60000,240000,300000);
  fOutputList->Add(fTriggersVsRunH);

  fInvariantMassDistributionCoherentH = new TH1F("fInvariantMassDistributionCoherentH", "fInvariantMassDistributionCoherentH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentH);

  for( Int_t iRapidity = 0; iRapidity < 6; iRapidity++ ) {
    fInvariantMassDistributionCoherentRapidityBinsH[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionCoherentRapidityBinsH_%d", iRapidity),
                        Form("fInvariantMassDistributionCoherentRapidityBinsH_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionCoherentRapidityBinsH[iRapidity]);
  }


  fInvariantMassDistributionCoherentShiftMinusTwoH = new TH1F("fInvariantMassDistributionCoherentShiftMinusTwoH", "fInvariantMassDistributionCoherentShiftMinusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftMinusTwoH);

  fInvariantMassDistributionCoherentShiftMinusOneH = new TH1F("fInvariantMassDistributionCoherentShiftMinusOneH", "fInvariantMassDistributionCoherentShiftMinusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftMinusOneH);

  fInvariantMassDistributionCoherentShiftPlusOneH = new TH1F("fInvariantMassDistributionCoherentShiftPlusOneH", "fInvariantMassDistributionCoherentShiftPlusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftPlusOneH);

  fInvariantMassDistributionCoherentShiftPlusTwoH = new TH1F("fInvariantMassDistributionCoherentShiftPlusTwoH", "fInvariantMassDistributionCoherentShiftPlusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionCoherentShiftPlusTwoH);

  fInvariantMassDistributionIncoherentH = new TH1F("fInvariantMassDistributionIncoherentH", "fInvariantMassDistributionIncoherentH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentH);

  fInvariantMassDistributionIncoherentShiftMinusTwoH = new TH1F("fInvariantMassDistributionIncoherentShiftMinusTwoH", "fInvariantMassDistributionIncoherentShiftMinusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftMinusTwoH);

  fInvariantMassDistributionIncoherentShiftMinusOneH = new TH1F("fInvariantMassDistributionIncoherentShiftMinusOneH", "fInvariantMassDistributionIncoherentShiftMinusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftMinusOneH);

  fInvariantMassDistributionIncoherentShiftPlusOneH = new TH1F("fInvariantMassDistributionIncoherentShiftPlusOneH", "fInvariantMassDistributionIncoherentShiftPlusOneH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftPlusOneH);

  fInvariantMassDistributionIncoherentShiftPlusTwoH = new TH1F("fInvariantMassDistributionIncoherentShiftPlusTwoH", "fInvariantMassDistributionIncoherentShiftPlusTwoH", 2000, 0, 20);
  fOutputList->Add(fInvariantMassDistributionIncoherentShiftPlusTwoH);

  fDimuonPtDistributionH = new TH1F("fDimuonPtDistributionH", "fDimuonPtDistributionH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionH);

  fDimuonPtDistributionShiftPlusOneH = new TH1F("fDimuonPtDistributionShiftPlusOneH", "fDimuonPtDistributionShiftPlusOneH", 4000, 0.02, 20.02);
  fOutputList->Add(fDimuonPtDistributionShiftPlusOneH);

  fDimuonPtDistributionRestrictedRapidity0N0NH = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0NH", "fDimuonPtDistributionRestrictedRapidity0N0NH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0NH);

  fDimuonPtDistributionRestrictedRapidity0N0N36to31H = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0N36to31H", "fDimuonPtDistributionRestrictedRapidity0N0N36to31H", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0N36to31H);

  fDimuonPtDistributionRestrictedRapidity0N0N31to26H = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0N31to26H", "fDimuonPtDistributionRestrictedRapidity0N0N31to26H", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0N31to26H);


  Float_t PtBins[]    = { 0.000, 0.025, 0.050, 0.075, 0.100, 0.125, 0.150, 0.175,
                          0.200, 0.225, 0.250, 0.275, 0.350, 0.425, 0.500, 0.575,
                          0.650, 0.725,
                          0.800, 0.875, 0.950, 1.100, 1.250, 1.400, 1.600, 1.800,
                          2.000, 2.500, 3.000, 3.500, 4.000, 5.000
                        };
  Int_t   PtBinNumber = sizeof(PtBins)/sizeof(Float_t) - 1; // or just = 9

  fDimuonPtDistributionRestrictedRapidity0N0NHv3 = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0NHv3", "fDimuonPtDistributionRestrictedRapidity0N0NHv3", PtBinNumber, PtBins);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0NHv3);

  fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3 = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3", "fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3", PtBinNumber, PtBins);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3);

  fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3 = new TH1F("fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3", "fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3", PtBinNumber, PtBins);
  fOutputList->Add(fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3);

  fDimuonPtDistributionZeroZNAH = new TH1F("fDimuonPtDistributionZeroZNAH", "fDimuonPtDistributionZeroZNAH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionZeroZNAH);

  fPtSidebandZeroZNAH = new TH1F("fPtSidebandZeroZNAH", "fPtSidebandZeroZNAH", 4000, 0, 20);
  fOutputList->Add(fPtSidebandZeroZNAH);

  fPtSidebandZeroZNCH = new TH1F("fPtSidebandZeroZNCH", "fPtSidebandZeroZNCH", 4000, 0, 20);
  fOutputList->Add(fPtSidebandZeroZNCH);


  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fDimuonPtDistributionZeroZNAbinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNAbinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNAbinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNAbinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fDimuonPtDistributionZeroZNAthreebinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNAthreebinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNAthreebinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNAthreebinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 4; iRapidity++ ) {
    fDimuonPtDistributionZeroZNAfourbinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNAfourbinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNAfourbinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNAfourbinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 5; iRapidity++ ) {
    fDimuonPtDistributionZeroZNAfivebinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNAfivebinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNAfivebinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNAfivebinsH[iRapidity]);
  }

  fDimuonPtDistributionZeroZNCH = new TH1F("fDimuonPtDistributionZeroZNCH", "fDimuonPtDistributionZeroZNCH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionZeroZNCH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fDimuonPtDistributionZeroZNCbinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNCbinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNCbinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNCbinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fDimuonPtDistributionZeroZNCthreebinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNCthreebinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNCthreebinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNCthreebinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 4; iRapidity++ ) {
    fDimuonPtDistributionZeroZNCfourbinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNCfourbinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNCfourbinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNCfourbinsH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 5; iRapidity++ ) {
    fDimuonPtDistributionZeroZNCfivebinsH[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNCfivebinsH_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNCfivebinsH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNCfivebinsH[iRapidity]);
  }

  /* - These histograms have an EXTENDED range (0,20)->(0,40)
     -
   */
  fInvariantMassDistributionExtendedH = new TH1F("fInvariantMassDistributionExtendedH", "fInvariantMassDistributionExtendedH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionExtendedH);

  fInvariantMassDistributionCoherentExtendedH = new TH1F("fInvariantMassDistributionCoherentExtendedH", "fInvariantMassDistributionCoherentExtendedH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionCoherentExtendedH);

  fInvariantMassDistributionIncoherentExtendedH = new TH1F("fInvariantMassDistributionIncoherentExtendedH", "fInvariantMassDistributionIncoherentExtendedH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionIncoherentExtendedH);

  fZNCEnergyAgainstEntriesH = new TH1F("fZNCEnergyAgainstEntriesH", "fZNCEnergyAgainstEntriesH", 20000, -10000, 40000);
  fOutputList->Add(fZNCEnergyAgainstEntriesH);

  fZNAEnergyAgainstEntriesH = new TH1F("fZNAEnergyAgainstEntriesH", "fZNAEnergyAgainstEntriesH", 20000, -10000, 40000);
  fOutputList->Add(fZNAEnergyAgainstEntriesH);

  fZNCEnergyBeforeTimingSelectionH = new TH1F("fZNCEnergyBeforeTimingSelectionH", "fZNCEnergyBeforeTimingSelectionH", 20000, -10000, 40000);
  fOutputList->Add(fZNCEnergyBeforeTimingSelectionH);

  fZNAEnergyBeforeTimingSelectionH = new TH1F("fZNAEnergyBeforeTimingSelectionH", "fZNAEnergyBeforeTimingSelectionH", 20000, -10000, 40000);
  fOutputList->Add(fZNAEnergyBeforeTimingSelectionH);

  fZNCEnergyAgainstEntriesExtendedH = new TH1F("fZNCEnergyAgainstEntriesExtendedH", "fZNCEnergyAgainstEntriesExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNCEnergyAgainstEntriesExtendedH);

  fZNAEnergyAgainstEntriesExtendedH = new TH1F("fZNAEnergyAgainstEntriesExtendedH", "fZNAEnergyAgainstEntriesExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNAEnergyAgainstEntriesExtendedH);

  fZNCEnergyAgainstEntriesExtendedHv2 = new TH1F("fZNCEnergyAgainstEntriesExtendedHv2", "fZNCEnergyAgainstEntriesExtendedHv2", 20000, -10000, 400000);
  fOutputList->Add(fZNCEnergyAgainstEntriesExtendedHv2);

  fZNAEnergyAgainstEntriesExtendedHv2 = new TH1F("fZNAEnergyAgainstEntriesExtendedHv2", "fZNAEnergyAgainstEntriesExtendedHv2", 20000, -10000, 400000);
  fOutputList->Add(fZNAEnergyAgainstEntriesExtendedHv2);

  fZNCEnergyBeforeTimingSelectionExtendedH = new TH1F("fZNCEnergyBeforeTimingSelectionExtendedH", "fZNCEnergyBeforeTimingSelectionExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNCEnergyBeforeTimingSelectionExtendedH);

  fZNAEnergyBeforeTimingSelectionExtendedH = new TH1F("fZNAEnergyBeforeTimingSelectionExtendedH", "fZNAEnergyBeforeTimingSelectionExtendedH", 20000, -10000, 400000);
  fOutputList->Add(fZNAEnergyBeforeTimingSelectionExtendedH);



  /* -
   * - VZERO plots
   */

  fVZEROhitsH = new TH1F("fVZEROhitsH", "fVZEROhitsH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROhitsH);

  fVZEROhitsWithVZEROCcutH = new TH1F("fVZEROhitsWithVZEROCcutH", "fVZEROhitsWithVZEROCcutH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROhitsWithVZEROCcutH);

  fVZEROhitsMoreThanFiveVZEROCcellsH = new TH1F("fVZEROhitsMoreThanFiveVZEROCcellsH", "fVZEROhitsMoreThanFiveVZEROCcellsH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROhitsMoreThanFiveVZEROCcellsH);

  fVZEROCNumberOfHitsSameEventH = new TH1F("fVZEROCNumberOfHitsSameEventH", "fVZEROCNumberOfHitsSameEventH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROCNumberOfHitsSameEventH);

  fVZEROANumberOfHitsSameEventH = new TH1F("fVZEROANumberOfHitsSameEventH", "fVZEROANumberOfHitsSameEventH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROANumberOfHitsSameEventH);

  fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH = new TH1F("fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH", "fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH);

  fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH = new TH1F("fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH", "fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH);

  fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH = new TH1F("fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH", "fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH);

  fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH = new TH1F("fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH", "fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH", 4000, 0, 40);
  fOutputList->Add(fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH);

  fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH = new TH1F("fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH", "fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH);

  fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH = new TH1F("fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH", "fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH);

  fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH = new TH1F("fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH", "fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH);

  fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH = new TH1F("fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH", "fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH);


  fVZEROhitsInnerRingsH = new TH1F("fVZEROhitsInnerRingsH", "fVZEROhitsInnerRingsH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROhitsInnerRingsH);

  fVZEROhitsOuterRingH = new TH1F("fVZEROhitsOuterRingH", "fVZEROhitsOuterRingH", 70, -0.5, 69.5);
  fOutputList->Add(fVZEROhitsOuterRingH);

  fEventTaggedVZEROCH = new TH1F("fEventTaggedVZEROCH", "fEventTaggedVZEROCH", 70, -0.5, 69.5);
  fOutputList->Add(fEventTaggedVZEROCH);

  fEventNotTaggedVZEROCH = new TH1F("fEventNotTaggedVZEROCH", "fEventNotTaggedVZEROCH", 70, -0.5, 69.5);
  fOutputList->Add(fEventNotTaggedVZEROCH);

  fIdentityOfVZEROCH = new TH1F("fIdentityOfVZEROCH", "fIdentityOfVZEROCH", 70, -0.5, 69.5);
  fOutputList->Add(fIdentityOfVZEROCH);

  fIROneH = new TH1F("fIROneH", "fIROneH", 200, -0.5, 199.5);
  fOutputList->Add(fIROneH);

  fIRTwoH = new TH1F("fIRTwoH", "fIRTwoH", 200, -0.5, 199.5);
  fOutputList->Add(fIRTwoH);

  fDimuonPtDistributionOuterRingH = new TH1F("fDimuonPtDistributionOuterRingH", "fDimuonPtDistributionOuterRingH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionOuterRingH);

  fDimuonPtDistributionAtLeastOneMuonOuterRingH = new TH1F("fDimuonPtDistributionAtLeastOneMuonOuterRingH", "fDimuonPtDistributionAtLeastOneMuonOuterRingH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionAtLeastOneMuonOuterRingH);

  fDimuonPtDistributionSecondRingH = new TH1F("fDimuonPtDistributionSecondRingH", "fDimuonPtDistributionSecondRingH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionSecondRingH);

  fDimuonPtDistributionCorrelationVZEROH = new TH1F("fDimuonPtDistributionCorrelationVZEROH", "fDimuonPtDistributionCorrelationVZEROH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionCorrelationVZEROH);

  fDimuonPtDistributionNullIROneH = new TH1F("fDimuonPtDistributionNullIROneH", "fDimuonPtDistributionNullIROneH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionNullIROneH);

  fDimuonPtDistributionNullIRTwoH = new TH1F("fDimuonPtDistributionNullIRTwoH", "fDimuonPtDistributionNullIRTwoH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionNullIRTwoH);

  fDimuonPtDistributionNegativeIROneH = new TH1F("fDimuonPtDistributionNegativeIROneH", "fDimuonPtDistributionNegativeIROneH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionNegativeIROneH);

  fDimuonPtDistributionNegativeIRTwoH = new TH1F("fDimuonPtDistributionNegativeIRTwoH", "fDimuonPtDistributionNegativeIRTwoH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionNegativeIRTwoH);

  fDimuonPtDistributionPositiveIROneH = new TH1F("fDimuonPtDistributionPositiveIROneH", "fDimuonPtDistributionPositiveIROneH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionPositiveIROneH);

  fDimuonPtDistributionPositiveIRTwoH = new TH1F("fDimuonPtDistributionPositiveIRTwoH", "fDimuonPtDistributionPositiveIRTwoH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionPositiveIRTwoH);

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fDimuonPtDistributionZeroZNCbins27to37H[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNCbins27to37H_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNCbins27to37H_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNCbins27to37H[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fDimuonPtDistributionZeroZNAbins27to37H[iRapidity]
            = new TH1F( Form("fDimuonPtDistributionZeroZNAbins27to37H_%d", iRapidity),
                        Form("fDimuonPtDistributionZeroZNAbins27to37H_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fDimuonPtDistributionZeroZNAbins27to37H[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionZeroZNA37to37H[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionZeroZNA37to37H_%d", iRapidity),
                        Form("fInvariantMassDistributionZeroZNA37to37H_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionZeroZNA37to37H[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 2; iRapidity++ ) {
    fInvariantMassDistributionZeroZNC37to37H[iRapidity]
            = new TH1F( Form("fInvariantMassDistributionZeroZNC37to37H_%d", iRapidity),
                        Form("fInvariantMassDistributionZeroZNC37to37H_%d", iRapidity),
                        2000, 0, 20);
    fOutputList->Add(fInvariantMassDistributionZeroZNC37to37H[iRapidity]);
  }



  // SIDEBANDS
  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fPtSidebandZeroZNCRapidityH[iRapidity]
            = new TH1F( Form("fPtSidebandZeroZNCRapidityH_%d", iRapidity),
                        Form("fPtSidebandZeroZNCRapidityH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fPtSidebandZeroZNCRapidityH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 3; iRapidity++ ) {
    fPtSidebandZeroZNARapidityH[iRapidity]
            = new TH1F( Form("fPtSidebandZeroZNARapidityH_%d", iRapidity),
                        Form("fPtSidebandZeroZNARapidityH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fPtSidebandZeroZNARapidityH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 12; iRapidity++ ) {
    fPtSidebandZeroZNARapidityAndMassH[iRapidity]
            = new TH1F( Form("fPtSidebandZeroZNARapidityAndMassH_%d", iRapidity),
                        Form("fPtSidebandZeroZNARapidityAndMassH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fPtSidebandZeroZNARapidityAndMassH[iRapidity]);
  }

  for( Int_t iRapidity = 0; iRapidity < 12; iRapidity++ ) {
    fPtSidebandZeroZNCRapidityAndMassH[iRapidity]
            = new TH1F( Form("fPtSidebandZeroZNCRapidityAndMassH_%d", iRapidity),
                        Form("fPtSidebandZeroZNCRapidityAndMassH_%d", iRapidity),
                        4000, 0, 20);
    fOutputList->Add(fPtSidebandZeroZNCRapidityAndMassH[iRapidity]);
  }


  fZNCEnergyAfterTimingVsADAMultiH = new TH2F("fZNCEnergyAfterTimingVsADAMultiH", "fZNCEnergyAfterTimingVsADAMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNCEnergyAfterTimingVsADAMultiH);

  fZNCEnergyAfterTimingVsADCMultiH = new TH2F("fZNCEnergyAfterTimingVsADCMultiH", "fZNCEnergyAfterTimingVsADCMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNCEnergyAfterTimingVsADCMultiH);

  fZNCEnergyAfterTimingVsADMultiH = new TH2F("fZNCEnergyAfterTimingVsADMultiH", "fZNCEnergyAfterTimingVsADMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNCEnergyAfterTimingVsADMultiH);

  fZNCEnergyBeforeTimingVsADAMultiH = new TH2F("fZNCEnergyBeforeTimingVsADAMultiH", "fZNCEnergyBeforeTimingVsADAMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNCEnergyBeforeTimingVsADAMultiH);

  fZNCEnergyBeforeTimingVsADCMultiH = new TH2F("fZNCEnergyBeforeTimingVsADCMultiH", "fZNCEnergyBeforeTimingVsADCMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNCEnergyBeforeTimingVsADCMultiH);

  fZNCEnergyBeforeTimingVsADMultiH = new TH2F("fZNCEnergyBeforeTimingVsADMultiH", "fZNCEnergyBeforeTimingVsADMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNCEnergyBeforeTimingVsADMultiH);




  fZNAEnergyAfterTimingVsADAMultiH = new TH2F("fZNAEnergyAfterTimingVsADAMultiH", "fZNAEnergyAfterTimingVsADAMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNAEnergyAfterTimingVsADAMultiH);

  fZNAEnergyAfterTimingVsADCMultiH = new TH2F("fZNAEnergyAfterTimingVsADCMultiH", "fZNAEnergyAfterTimingVsADCMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNAEnergyAfterTimingVsADCMultiH);

  fZNAEnergyAfterTimingVsADMultiH = new TH2F("fZNAEnergyAfterTimingVsADMultiH", "fZNAEnergyAfterTimingVsADMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNAEnergyAfterTimingVsADMultiH);

  fZNAEnergyBeforeTimingVsADAMultiH = new TH2F("fZNAEnergyBeforeTimingVsADAMultiH", "fZNAEnergyBeforeTimingVsADAMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNAEnergyBeforeTimingVsADAMultiH);

  fZNAEnergyBeforeTimingVsADCMultiH = new TH2F("fZNAEnergyBeforeTimingVsADCMultiH", "fZNAEnergyBeforeTimingVsADCMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNAEnergyBeforeTimingVsADCMultiH);

  fZNAEnergyBeforeTimingVsADMultiH = new TH2F("fZNAEnergyBeforeTimingVsADMultiH", "fZNAEnergyBeforeTimingVsADMultiH", 500, -3000, 7000, 100, -1., 99.);
  fOutputList->Add(fZNAEnergyBeforeTimingVsADMultiH);


  fRapidityShapeH = new TH1F("fRapidityShapeH", "fRapidityShapeH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeH);

  fRapidityShapeAtDCAH = new TH1F("fRapidityShapeAtDCAH", "fRapidityShapeAtDCAH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeAtDCAH);

  fRapidityShapeADAdecH = new TH1F("fRapidityShapeADAdecH", "fRapidityShapeADAdecH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeADAdecH);

  fRapidityShapeADAdecAtDCAH = new TH1F("fRapidityShapeADAdecAtDCAH", "fRapidityShapeADAdecAtDCAH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeADAdecAtDCAH);

  fRapidityShapeADCdecH = new TH1F("fRapidityShapeADCdecH", "fRapidityShapeADCdecH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeADCdecH);

  fRapidityShapeADCdecAtDCAH = new TH1F("fRapidityShapeADCdecAtDCAH", "fRapidityShapeADCdecAtDCAH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeADCdecAtDCAH);

  fRapidityShapeADdecH = new TH1F("fRapidityShapeADdecH", "fRapidityShapeADdecH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeADdecH);

  fRapidityShapeADdecAtDCAH = new TH1F("fRapidityShapeADdecAtDCAH", "fRapidityShapeADdecAtDCAH", 1000, -5., 0.);
  fOutputList->Add(fRapidityShapeADdecAtDCAH);






  // Same sign bkg
  fMassSameSignZeroTrkH = new TH1F("fMassSameSignZeroTrkH", "fMassSameSignZeroTrkH", 2000, 0, 20);
  fOutputList->Add(fMassSameSignZeroTrkH);

  fMassSameSignOneTrkH = new TH1F("fMassSameSignOneTrkH", "fMassSameSignOneTrkH", 2000, 0, 20);
  fOutputList->Add(fMassSameSignOneTrkH);

  fMassSameSignTwoTrkH = new TH1F("fMassSameSignTwoTrkH", "fMassSameSignTwoTrkH", 2000, 0, 20);
  fOutputList->Add(fMassSameSignTwoTrkH);

  fRapSameSignZeroTrkH = new TH1F("fRapSameSignZeroTrkH", "fRapSameSignZeroTrkH", 1000, -5., 0.);
  fOutputList->Add(fRapSameSignZeroTrkH);

  fRapSameSignOneTrkH = new TH1F("fRapSameSignOneTrkH", "fRapSameSignOneTrkH", 1000, -5., 0.);
  fOutputList->Add(fRapSameSignOneTrkH);

  fRapSameSignTwoTrkH = new TH1F("fRapSameSignTwoTrkH", "fRapSameSignTwoTrkH", 1000, -5., 0.);
  fOutputList->Add(fRapSameSignTwoTrkH);

  fPtSameSignZeroTrkH = new TH1F("fPtSameSignZeroTrkH", "fPtSameSignZeroTrkH", 4000, 0, 20);
  fOutputList->Add(fPtSameSignZeroTrkH);

  fPtSameSignOneTrkH = new TH1F("fPtSameSignOneTrkH", "fPtSameSignOneTrkH", 4000, 0, 20);
  fOutputList->Add(fPtSameSignOneTrkH);

  fPtSameSignTwoTrkH = new TH1F("fPtSameSignTwoTrkH", "fPtSameSignTwoTrkH", 4000, 0, 20);
  fOutputList->Add(fPtSameSignTwoTrkH);

  fPhiSameSignZeroTrkH = new TH1F("fPhiSameSignZeroTrkH", "fPhiSameSignZeroTrkH", 1000, -2., 8.);
  fOutputList->Add(fPhiSameSignZeroTrkH);

  fPhiSameSignOneTrkH = new TH1F("fPhiSameSignOneTrkH", "fPhiSameSignOneTrkH", 1000, -2., 8.);
  fOutputList->Add(fPhiSameSignOneTrkH);

  fPhiSameSignTwoTrkH = new TH1F("fPhiSameSignTwoTrkH", "fPhiSameSignTwoTrkH", 1000, -2., 8.);
  fOutputList->Add(fPhiSameSignTwoTrkH);



  fDimuonPtDistributionRejectedZNAflagH = new TH1F("fDimuonPtDistributionRejectedZNAflagH", "fDimuonPtDistributionRejectedZNAflagH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRejectedZNAflagH);

  fDimuonPtDistributionRejectedZNCflagH = new TH1F("fDimuonPtDistributionRejectedZNCflagH", "fDimuonPtDistributionRejectedZNCflagH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionRejectedZNCflagH);



  fDimuonPtDistributionGammaGammaZNAH = new TH1F("fDimuonPtDistributionGammaGammaZNAH", "fDimuonPtDistributionGammaGammaZNAH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionGammaGammaZNAH);

  fDimuonPtDistributionGammaGammaZNCH = new TH1F("fDimuonPtDistributionGammaGammaZNCH", "fDimuonPtDistributionGammaGammaZNCH", 4000, 0, 20);
  fOutputList->Add(fDimuonPtDistributionGammaGammaZNCH);

  //_______________________________
  // - End of the function
  PostData(1, fOutputList);           // postdata will notify the analysis manager of changes / updates to the
  // fOutputList object. the manager will in the end take care of writing your output to file
  // so it needs to know what's in the output
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::NotifyRun()
{
  /// Set run number for cuts
  fMuonTrackCuts->SetRun(fInputHandler);
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::UserExec(Option_t *)
{
  /* - This iSelectionCounter is used as a token. So at every passing step it is
     - increased by one. All the events are supposed to pass the first step
     - obviously, but only a few get to the end. This is effect is clearly
     - noticeable in fCounterH event with the small trial local sample.
     - Almost 160k possible events at the 0-th step, while only 2k at the 4th step.
   */
  Int_t iSelectionCounter = 0; // no selection applied yet
  fCounterH->Fill(iSelectionCounter); // entering UserExec -> counter 0
  fCounterH->Fill(90); // entering UserExec -> counter 0
  iSelectionCounter++;

  // get AOD event
  fAOD = dynamic_cast<AliAODEvent*>(InputEvent());
  if(!fAOD) {
      PostData(1, fOutputList);
      return;
  }
  fCounterH->Fill(iSelectionCounter); // AOD event found -> counter 1
  iSelectionCounter++;

  /* - Is it the right trigger?
   * -
   * - LHC16r (p-Pb @ 8 TeV):
   * - CMUP14-B-NOPF-MUFAST:   !VBA & !UBA & MSL
   * - CMUP15-B-NOPF-ALLNOTRD: !VBA & !UBA & !VC5 & !SH2 & SMB & MSL
   * -
   * -
   * -
   * - LHC16s (Pb-p @ 8 TeV):
   * - CMUP23-B-NOPF-MUFAST:   !VBA & !VGA & !UBC & !UGC & !SH2 & !VC5 & MUL
   * - CMUP22-B-NOPF-ALLNOTRD: !VBA & !VGA & !UBC & !UGC & !VC5 & !SH2 & SMB & MSL
   * -
   */
  TString trigger = fAOD->GetFiredTriggerClasses();
  if (    !(
            // trigger.Contains("CMUP3")   ||
            // trigger.Contains("CMUP8")   ||
            trigger.Contains("CMUP14-B-NOPF-MUFAST")   ||
	          // trigger.Contains("CMUP15-B-NOPF-ALLNOTRD") ||
	          trigger.Contains("CMUP23-B-NOPF-MUFAST")  // ||
            // trigger.Contains("CMUP22-B-NOPF-ALLNOTRD") ||
            // trigger.Contains("CMUP16")   ||
            // trigger.Contains("CMUP17")   ||
            // trigger.Contains("CMUP18")   ||
            // trigger.Contains("CMUP19")   ||
            // trigger.Contains("CMUP20")   ||
            // trigger.Contains("CMUP21")

            )
          )  {
                    PostData(1, fOutputList);
                    return;
  }
  fCounterH->Fill(iSelectionCounter); // right trigger found -> counter 2
  fCounterH->Fill(91); // right trigger found -> counter 2
  iSelectionCounter++;


  /* - The following lines concern the LUMI computation.
   * - What is being done is that we fill the histograms
   * - with the number of events which pass the relative
   * - trigger conditions.
   * -
   */
  // Int_t  counterForTrigger = 0;
  fRunNum    = fAOD->GetRunNumber();
  if ( trigger.Contains("CMUP14-B-NOPF-MUFAST") )  {
    fTriggersVsRunH->Fill( 0.5, fRunNum );
  }
  if ( trigger.Contains("CMUP23-B-NOPF-MUFAST") )  {
    fTriggersVsRunH->Fill( 1.5, fRunNum );
  }
  if ( trigger.Contains("CMUP15-B-NOPF-ALLNOTRD") )  {
    fTriggersVsRunH->Fill( 2.5, fRunNum );
  }
  if ( trigger.Contains("CMUP22-B-NOPF-ALLNOTRD") )  {
    fTriggersVsRunH->Fill( 3.5, fRunNum );
  }
  if ( trigger.Contains("CMUP3") )  {
    fTriggersVsRunH->Fill( 4.5, fRunNum );
  }
  if ( trigger.Contains("CMUP8") )  {
    fTriggersVsRunH->Fill( 5.5, fRunNum );
  }
  if ( trigger.Contains("CMUP16") )  {
    fTriggersVsRunH->Fill( 6.5, fRunNum );
  }
  if ( trigger.Contains("CMUP17") )  {
    fTriggersVsRunH->Fill( 7.5, fRunNum );
  }
  if ( trigger.Contains("CMUP18") )  {
    fTriggersVsRunH->Fill( 8.5, fRunNum );
  }
  if ( trigger.Contains("CMUP19") )  {
    fTriggersVsRunH->Fill( 9.5, fRunNum );
  }
  if ( trigger.Contains("CMUP20") )  {
    fTriggersVsRunH->Fill( 10.5, fRunNum );
  }
  if ( trigger.Contains("CMUP21") )  {
    fTriggersVsRunH->Fill( 11.5, fRunNum );
  }




  /* - We are now checking if there were any tracks. If there were at least one,
     - then the histogram gets filled again. If not we are returning. There
     - would be no point in going further.
   */
  Int_t nTracks(fAOD->GetNumberOfTracks());
  if(nTracks<1) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(iSelectionCounter); // At least one track -> counter 3
  iSelectionCounter++;


  //_______________________________
  // EVENT DATA EXTRACTION
  /* - Eugeny Krishen's event data extraction. I am trying to implement it.
     - The only thing I am a bit worried about is whether it should go before or
     - after the "nTracks<1" check... I will try and switch it if it sounds
     - better. These data are used for the event selection and maybe later on
     - for track selection, but I did not get to that part yet. If after all of
     - this I remember to do so, I will come back to this point and correct this
     - statement. If you find this part, please, keep in mind to check the
     - following.
   */

  /* - Event information:
     - Run Number, maybe to select the GOOD Runs and discard the others;
     - Number of Tracklets, these are in this case the SPD tracklets, so the
     - almost unit vector roughly 2 cm between two pixels of the SPD in different
     - layers.
   */
  // fRunNum    = fAOD->GetRunNumber();
  fTracklets = fAOD->GetTracklets()->GetNumberOfTracklets();

  /* - Trigger Inputs:
     - L0: ..... ;
     - L1: ..... .
   */
  fL0inputs = fAOD->GetHeader()->GetL0TriggerInputs();
  fL1inputs = fAOD->GetHeader()->GetL1TriggerInputs();

  /* - Past-future protection maps:
     - IR1: .... ;
     - IR2: .... .
   */
  fIR1Map = fAOD->GetHeader()->GetIRInt1InteractionMap();
  fIR2Map = fAOD->GetHeader()->GetIRInt2InteractionMap();

  /* - ZDC: we try to find the ZDC object data in the nano-AOD. If we cannot,
     - we return, because there would be no way to actually select the events
     - otherwise! We are here, so we could even check if there is a discrepancy
     - between good events with and without ZDC's information. Or at least, this
     - is my impression of it (filling fCounterH). ZDC information:
     - fZem1Energy:
     - fZem2Energy:
     - fZNAEnergy:
     - fZNCEnergy:
     - fZPAEnergy:
     - fZPCEnergy:
     - fZNATime:
     - fZNCTime:
     - fZNATDC[i]:
     - fZNCTDC[i]:
     - fZPATDC[i]:
     - fZPCTDC[i]:
   */
  AliAODZDC *dataZDC = dynamic_cast<AliAODZDC*>(fAOD->GetZDCData());
  if(!dataZDC) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(iSelectionCounter); // -> Counter 4
  iSelectionCounter++;

  fZem1Energy = dataZDC->GetZEM1Energy();
  fZem2Energy = dataZDC->GetZEM2Energy();

  /* - Reset Event information.
   * -
   */
  fZNAEnergy  = -8999;
  fZNCEnergy  = -8999;
  fZPAEnergy  = -8999;
  fZPCEnergy  = -8999;

  fZNAEnergy  = dataZDC->GetZNATowerEnergy()[0];
  fZNCEnergy  = dataZDC->GetZNCTowerEnergy()[0];
  fZPAEnergy  = dataZDC->GetZPATowerEnergy()[0];
  fZPCEnergy  = dataZDC->GetZPCTowerEnergy()[0];

  fZNATime    = dataZDC->GetZNATime();
  fZNCTime    = dataZDC->GetZNCTime();

  /* - Reset Event information.
   * -
   */
  for (Int_t i=0;i<4;i++) fZNATDC[i] = -999;
  for (Int_t i=0;i<4;i++) fZNCTDC[i] = -999;
  for (Int_t i=0;i<4;i++) fZPATDC[i] = -999;
  for (Int_t i=0;i<4;i++) fZPCTDC[i] = -999;

  for (Int_t i=0;i<4;i++) fZNATDC[i] = dataZDC->GetZNATDCm(i);
  for (Int_t i=0;i<4;i++) fZNCTDC[i] = dataZDC->GetZNCTDCm(i);
  for (Int_t i=0;i<4;i++) fZPATDC[i] = dataZDC->GetZPATDCm(i);
  for (Int_t i=0;i<4;i++) fZPCTDC[i] = dataZDC->GetZPCTDCm(i);

  /* - These lines are the calibration for the ZDC as provided by Evgeny Kryshen.
     -
   */
  Bool_t calibrated = 0;
  // if ( fRunNum <= 245068 ) {
  //   calibrated = 1;
  // } else if ( ( fRunNum > 245068 ) && ( fRunNum <  246995 ) ){
  //   calibrated = 0;
  // } else {
  //   calibrated = 1;
  // }

  // if ( calibrated == 0 ) {
  //   if( fRunNum <= 246994 ) {
  //     fZNAEnergy *= (2500./250.);
  //     fZNCEnergy *= (2500./250.);
  //   }
  // }

  /* - V0: we try to find the V0 object data in the nano-AOD. If we cannot,
     - we return, because there would be no way to actually select the events
     - otherwise! We are here, so we could even check if there is a discrepancy
     - between good events with and without V0's information. Or at least, this
     - is my impression of it (filling fCounterH). V0 information:
     - fV0ADecision: ..... ;
     - fV0CDecision: ..... .
     -
     -
     -
     - Plot the V0 variables to try to understand whether it is cells we are
     - talking about or boolean responses or something else altogether.
  */
  AliVVZERO *dataVZERO = dynamic_cast<AliVVZERO*>(fAOD->GetVZEROData());
  if(!dataVZERO) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(iSelectionCounter); // -> counter 5
  iSelectionCounter++;
  fCounterH->Fill(12);


  fV0ADecision = dataVZERO->GetV0ADecision();
  fCounterH->Fill(13);
  fV0CDecision = dataVZERO->GetV0CDecision();
  fCounterH->Fill(14);

  Int_t is_VZEROA_set = -9;
  Int_t is_VZEROC_set = -9;
  is_VZEROA_set = IntBits( dataVZERO->GetTriggerBits() ).test(12);
  is_VZEROC_set = IntBits( dataVZERO->GetTriggerBits() ).test(13);



  //_____________________________________
  // RUN SELECTION
  /* - NOTE: total run selection.
   * -
   */
  fCounterH->Fill(15);
  Int_t listOfGoodRunNumbersLHC16r[]  = { 265589, 265594, 265596, 265607, 265669, 265691, 265694,
                                          265697, 265698, 265700, 265701, 265709, 265713, 265714, 265740,
                                          265741, 265742, 265744, 265746, 265754, 265756, 265785, 265787,
                                          265788, 265789, 265792, 265795, 265797, 265840, 266022, 266023,
                                          266025, 266034, 266074, 266076, 266081, 266084, 266085, 266086,
                                          266117, 266187, 266189, 266190, 266193, 266196, 266197, 266208,
                                          266234, 266235, 266296, 266299, 266300, 266304, 266305, 266312,
                                          266316, 266318    };

  Int_t listOfGoodRunNumbersLHC16s[]  = { 267131, 267130, 267110, 267109, 267077, 267072, 267070, 267067, 267063, 267062,
                                          267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
                                          266940, 266915, 266912, 266886, 266885, 266883, 266882, 266880, 266878, 266857,
                                          266807, 266805, 266800, 266776, 266775, 266708, 266706, 266703, 266702, 266676,
                                          266674, 266669, 266668, 266665, 266659, 266658, 266657, 266630, 266621, 266618,
                                          /*266615,*/ 266614, 266613, 266595, 266593, 266591, 266588, 266587, 266584, 266549,
                                          266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, 266518, 266516,
                                          266514, 266487, 266480, 266479, 266472, 266441, 266439/*, 296552, 296510, 296549, 296618, 296551, 296553, 296623, 296511, 296552*/ };
  //_______________________________
  /* -
   * - REDUCED list for
   * - inefficiency AD.
   * -
   */
  // Int_t listOfGoodRunNumbersLHC16s[]  = { 267131, 267130, /*267110,*/ 267109, 267077, 267072, 267070, 267067, 267063, 267062,
  //                                         267022, 267020, 266998, 266997, 266994, 266993, 266988, 266944, 266943, 266942,
  //                                         266940, 266915, 266912, 266886, /*266885,*/ 266883, /*266882,*/ 266880, 266878, /*266857,*/
  //                                         266807, 266805, 266800, 266776, /*266775,*/ 266708, /*266706, 266703, 266702,*/ 266676,
  //                                         266674, 266669, /*266668,*/ 266665, 266659, /*266658, 266657,*/ 266630, 266621, 266618,
  //                                         /*266615,*/ /*266614, 266613,*/ 266595, 266593, /*266591, 266588, 266587, 266584,*/ 266549,
  //                                         266543, 266539, 266534, 266533, 266525, 266523, 266522, 266520, //266518, //266516,
  //                                       /*266514,*/ 266487, 266480, 266479, /*266472, 266441,*/ 266439/*, 296552, 296510, 296549, 296618, 296551, 296553, 296623, 296511, 296552*/ };

  Int_t listRunOne[] = {
    197089, 197011, 197003, 196974, 196973, 196972, 196965, 196876, 196869, 196774, 196773,
    196772, 196722, 196721, 196720, 196702, 196701, 196648, 196646, 196608, 196605, 196601,
    196568, 196566, 196564, 196563, 196535, 196528, 196477, 196475, 196474,
    197388, 197387, 197386, 197349, 197348, 197342, 197341, 197302, 197299, 197298, 197258,
    197256, 197255, 197254, 197247, 197189, 197184, 197153, 197152, 197150, 197148, 197147,
    197145, 197144, 197143, 197142, 197139, 197138, 197099, 197098, 197092, 197091, 197089
  };
  Bool_t checkIfGoodRun = kFALSE;
  for( Int_t iRunLHC16r = 0; iRunLHC16r <  57; iRunLHC16r++){
    if( fRunNum == listOfGoodRunNumbersLHC16r[iRunLHC16r] ) checkIfGoodRun = kTRUE;
  }
  // for( Int_t iRunLHC16r = 0; iRunLHC16r <  53; iRunLHC16r++){
  //   if( fRunNum == listOfGoodRunNumbersLHC16r[iRunLHC16r] ) checkIfGoodRun = kTRUE;
  // }




  for( Int_t iRunLHC16s = 0; iRunLHC16s <  76 /*86*/; iRunLHC16s++){
    if( fRunNum == listOfGoodRunNumbersLHC16s[iRunLHC16s] ) checkIfGoodRun = kTRUE;
  }

  //
  // REDUCED run list for ADC multiplicity
  // for( Int_t iRunLHC16s = 0; iRunLHC16s <  54; iRunLHC16s++){
  //   if( fRunNum == listOfGoodRunNumbersLHC16s[iRunLHC16s] ) checkIfGoodRun = kTRUE;
  // }




  // Int_t listOfGoodRunNumbersLHC16s[]  = { 267110, 266885, 266882, 266857, 266775,
  //                                         266706, 266703, 266702, 266668, 266658,
  //                                         266657, 266615, 266614, 266613, 266591,
  //                                         266588, 266587, 266584, 266518, 266516,
  //                                         266514, 266472, 266441 };
  // // REMOVED run list for ADC multiplicity
  // for( Int_t iRunLHC16s = 0; iRunLHC16s <  23; iRunLHC16s++){
  //   if( fRunNum == listOfGoodRunNumbersLHC16s[iRunLHC16s] ) checkIfGoodRun = kTRUE;
  // }


  // for( Int_t iRunLHC13 = 0; iRunLHC13 <  64 /*86*/; iRunLHC13++){
  //   if( fRunNum == listRunOne[iRunLHC13] ) checkIfGoodRun = kTRUE;
  // }
  if(checkIfGoodRun != 1) {
       PostData(1, fOutputList);
       // cout << "OPS!" << endl;
       return;
  }
  fCounterH->Fill(17);



  // END RUN SELECTION
  //_____________________________________



  /* - We have to get the number of fired V0C cells. So firstly, we get the
     - boolean information about the hit cells for all V0. This is done through
     - the GetBBFlag(i) method, where 0<i<32 stands for the V0C cells and
     - 32<i<64 for the V0A cells. Then I thought the easiest way to check
     - whether the number of fired V0C cells is above 2 is just to add up the
     - boolean numbers for 0<i<32. Let's see.
     -
     -
   */
  fV0TotalNCells = 0;
  Double_t fOuterRingCells        = 0;
  Double_t fThirdRingCells        = 0;
  Double_t fVZEROCfiredcells      = 0;
  Double_t fVZEROAfiredcells      = 0;
  Double_t fVZEROCfiredInnerCells = 0;
  for(Int_t iV0Hits = 0; iV0Hits < 64; iV0Hits++) {
        fV0Hits[iV0Hits] = dataVZERO->GetBBFlag(iV0Hits);
        // if(fV0Hits[iV0Hits] == kTRUE) {
        //       // if(iV0Hits < 32) fV0TotalNCells += fV0Hits[iV0Hits];
        //       fVZEROhitsH->Fill( iV0Hits );
        //       if(iV0Hits < 32) fV0TotalNCells += 1;
        //       if(iV0Hits < 32) {
        //         fVZEROCfiredcells += 1;
        //       } else {
        //         fVZEROAfiredcells += 1;
        //       }
        // }
        if( ((Double_t) fV0Hits[iV0Hits]) > 0.5 ) {
              // if(iV0Hits < 32) fV0TotalNCells += fV0Hits[iV0Hits];
              fVZEROhitsH->Fill( iV0Hits );
              if(iV0Hits < 32) fV0TotalNCells += 1;
              if(iV0Hits < 32) {
                fVZEROCfiredcells += 1;
                if(iV0Hits < 24) {
                  fVZEROCfiredInnerCells += 1;
                }
              } else {
                fVZEROAfiredcells += 1;
              }
              if(iV0Hits < 32 && iV0Hits > 23) fOuterRingCells += 1;
              if(iV0Hits < 24 && iV0Hits > 15) fThirdRingCells += 1;
        }
        // std::cout << "fV0Hits[iV0Hits = " << iV0Hits << ", fRunNum=" << fRunNum << "] = " << fV0Hits[iV0Hits] << endl;
        // std::cout << "fV0TotalNCells (fRunNum = " << fRunNum << ") = " << fV0TotalNCells << endl;
  }
  fCounterH->Fill(18);
  fVZEROCNumberOfHitsSameEventH->Fill( fVZEROCfiredcells );
  fVZEROANumberOfHitsSameEventH->Fill( fVZEROAfiredcells );
  for(Int_t iV0Hits = 0; iV0Hits < 64; iV0Hits++) {
        if(fV0Hits[iV0Hits] == kTRUE) {
              if( fVZEROCfiredcells < 5 ) {
                fVZEROhitsWithVZEROCcutH->Fill( iV0Hits );
              } else {
                fVZEROhitsMoreThanFiveVZEROCcellsH->Fill( iV0Hits );
              }
        }

        // cout << "Eta min channel[" << iV0Hits << "] = " << AliVVZERO::GetVZEROEtaMin(iV0Hits) << endl;
  }

  /* -
   * - Looking for coincident hits.
   * -
   */
  // Int_t TwoHitsFirstRing   = -1;
  // Int_t ThreeHitsFirstRing = -1;
  // Int_t FourHitsFirstRing  = -1;
  // Int_t FiveHitsFirstRing  = -1;
  // Int_t SixHitsFirstRing   = -1;
  // Int_t SevenHitsFirstRing = -1;
  // Int_t EightHitsFirstRing = -1;
  // for(Int_t iV0Hits = 0; iV0Hits < 8; iV0Hits++) {
  //       if(iV0Hits < 8 && fV0Hits[iV0Hits+0] == kTRUE) {
  //           if(iV0Hits < 7 && fV0Hits[iV0Hits+1] == kTRUE) {
  //               if(iV0Hits < 6 && fV0Hits[iV0Hits+2] == kTRUE) {
  //                 if(iV0Hits < 5 && fV0Hits[iV0Hits+3] == kTRUE) {
  //                     if(iV0Hits < 4 && fV0Hits[iV0Hits+4] == kTRUE) {
  //                         if(iV0Hits < 3 && fV0Hits[iV0Hits+5] == kTRUE) {
  //                             if(iV0Hits < 2 && fV0Hits[iV0Hits+6] == kTRUE) {
  //                                 if( < 1 && fV0Hits[iV0Hits+7] == kTRUE) {
  //                                   EightHitsFirstRing = 0;
  //                                   iV0Hits += 8;
  //                                 } else {
  //                                   SevenHitsFirstRing = iV0Hits;
  //                                   iV0Hits += 7;
  //                                 }
  //                             }
  //                         }
  //                     }
  //                 }
  //               }
  //           }
  //       }
  // }






  /* - AD: we try to find the AD object data in the nano-AOD. If we cannot,
     - we return, because there would be no way to actually select the events
     - otherwise! We are here, so we could even check if there is a discrepancy
     - between good events with and without AD's information. Or at least, this
     - is my impression of it (filling fCounterH). AD information:
     - fADADecision: small detector in ALICE, ADA and ADC at large distances;
     - fADCDecision: again, maybe check whether it is cells or boolean, same as V0.
  */
  // AD
  // AliVAD *dataAD = dynamic_cast<AliVAD*>(fAOD->GetADData());
  // fCounterH->Fill(19);
  // if(dataAD) {
  //       fCounterH->Fill(iSelectionCounter);
  //       iSelectionCounter++;
  //       fCounterH->Fill(20);
  //
  //       fADADecision = dataAD->GetADADecision();
  //       fADCDecision = dataAD->GetADCDecision();
  //       fCounterH->Fill(21);
  // }
  // fCounterH->Fill(22);



  AliVAD *dataAD = dynamic_cast<AliVAD*>(fAOD->GetADData());
  fCounterH->Fill(19);
  Int_t is_ADA_set = -9;
  Int_t is_ADC_set = -9;
  Double_t ADmultiplicities[16]   = { -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1 };
  Double_t ADmultiplicitiesTotal  = 0;
  Double_t ADAmultiplicitiesTotal = 0;
  Double_t ADCmultiplicitiesTotal = 0;

  Int_t ADAPastFutureBeamBeamFlags[8][21];
  Int_t ADCPastFutureBeamBeamFlags[8][21];


  Int_t ADAPastFutureBoolean = 0;
  Int_t ADCPastFutureBoolean = 0;

  if(dataAD) {
        fCounterH->Fill(iSelectionCounter); // -> counter 6
        iSelectionCounter++;
        fCounterH->Fill(20);

        fADADecision = dataAD->GetADADecision();
        fADCDecision = dataAD->GetADCDecision();
        fCounterH->Fill(21);

        is_ADA_set = IntBits( dataAD->GetTriggerBits() ).test(12);
        is_ADC_set = IntBits( dataAD->GetTriggerBits() ).test(13);
        // cout << "is_ADA_set = " << is_ADA_set << endl;
        // cout << "is_ADC_set = " << is_ADC_set << endl;
        // cout << "is_ADA_set = " << IntBits( dataAD->GetTriggerBits() ) << endl;
        // cout << "is_ADC_set = " << dataAD->GetTriggerBits() << endl;
        for( Int_t iChannel = 0; iChannel < 16; iChannel++ ){
          ADmultiplicities[iChannel] = dataAD->GetMultiplicity(iChannel);
          ADmultiplicitiesTotal     += dataAD->GetMultiplicity(iChannel);
          if ( iChannel < 8 ) {
            ADCmultiplicitiesTotal  += dataAD->GetMultiplicity(iChannel);
          } else {
            ADAmultiplicitiesTotal  += dataAD->GetMultiplicity(iChannel);
          }
        }


        for(   Int_t iChannel = 0; iChannel < 8; iChannel++ ){
          for( Int_t iClock   = 0; iClock   < 21; iClock++   ){
            ADAPastFutureBeamBeamFlags[iChannel][iClock] = 0;
            ADCPastFutureBeamBeamFlags[iChannel][iClock] = 0;
          }
        }

        for(   Int_t iChannel = 0; iChannel < 8; iChannel++ ){
          for( Int_t iClock   = 0; iClock   < 21; iClock++   ){
            ADAPastFutureBeamBeamFlags[iChannel][iClock] = dataAD->GetPFBBFlag(iChannel + 8, iClock);
            ADCPastFutureBeamBeamFlags[iChannel][iClock] = dataAD->GetPFBBFlag(iChannel, iClock);
          }
        }

        for(   Int_t iChannel = 0; iChannel < 8;  iChannel++ ){
          for( Int_t iClock   = 0; iClock   < 21; iClock++   ){
            if( dataAD->GetPFBBFlag(iChannel + 8, iClock) != 0 ) ADAPastFutureBoolean = 1;
            if( dataAD->GetPFBBFlag(iChannel, iClock)     != 0 ) ADCPastFutureBoolean = 1;
          }
        }


  }


  // END EVENT DATA EXTRACTION
  // //_______________________________
  // // EVENT SELECTION
  // /* - This is Eugeny Krishen's event selection from the talk in 14/1/2019 for
  //    - the PWG-UD (UPC oriented) meeting. The event selection requires:
  //    - CMUP11-B triggers;
  //    - Maximum 2 V0C cells fired;
  //    - Empty V0A decision;
  //    - Empty ADA decision;
  //    - Empty ADC decision;
  //    - 0 tracklets in SPD;
  //    - Exactly 2 unlike-sign muons;
  //  */
  // /* - CMUP11-B triggers: I have to check with my supervisor, but this requirement
  //    - may have already been satisfied with the requirements for the trigger info
  //  */
  // /* - Maximum 2 V0C cells fired:
  //    -
  //  */
  // /* - Empty V0A decision
  //    - Empty ADA decision
  //    - Empty ADC decision
  //  */
  if(fV0ADecision != 0) {
       PostData(1, fOutputList);
       return;
  }
  // if(fADADecision != 0) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  // if(!(fADADecision == 1 || fADADecision == 0)) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  // if(fADCDecision != 0) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  // if(fADCDecision == 1) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  if(fADADecision == 1) {
       PostData(1, fOutputList);
       return;
  }
  //
  //
  // /* - Empty V0C decision
  //  * - or at least in beam timing.
  //  */
  // if( !(fV0CDecision == 0 || fV0CDecision == 1) ) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  // /* - 0 tracklets in SPD
  //  */
  // if(fTracklets != 0) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  // /* - Maximum 2 V0C cells fired.
  //    -
  //    - Trying a more readable and immediate approach.
  //  */
  // if( fV0TotalNCells > 5 ) {
  //      PostData(1, fOutputList);
  //      return;
  // }
  //
  //
  // //_______________________________
  // /* -
  //  * - ADC multiplicity cut
  //  * -
  //  */
  // // if( ADCmultiplicitiesTotal != 0 ) {
  // //      PostData(1, fOutputList);
  // //      return;
  // // }
  //
  // //_______________________________
  // /* -
  //  * - ADA multiplicity cut
  //  * -
  //  */
  // // if( ADAmultiplicitiesTotal != 0 ) {
  // //      PostData(1, fOutputList);
  // //      return;
  // // }
  //



  /* - We are finally at the starting point. We loop over the tracks and select
     - the good muons. Later on everything should happen in this loop. Let us
     - see what the future has in hold.
     -
     - Saturday: I moved the creation of the AliAODTrack* track outside of the
     - loop as it would have been otherwise created for each single iteration.
     - This could have caused massive memory issues especially to grid. I have
     - added a second AliAODTrack* track[2] to hold the second supposed muon.
     - Now this is ready to send the information to two TLorentzVectors to
     - obtain the invariant mass of the J/Psi through the Mag() method of the
     - class. Hope for the best.
   */
  Int_t nGoodMuons = 0;
  AliAODTrack* track[2];
  track[0]         = 0x0;
  track[1]         = 0x0;
  for(Int_t iTrack(0); iTrack < nTracks; iTrack++) {
    /* - This should be another form of event selection.
       - I am basically requesting the presence of TWO good muons only.
       - Later I will be checking whether of they are likesign or unlikesign.
     */
    if(nGoodMuons > 2) {
         PostData(1, fOutputList);
         return;
    }
    // get track
    // AliAODTrack* track = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack));
    // if(!track) return;
    //
    // // is it a good muon track?
    // if(!track->IsMuonTrack()) continue;
    // if(!fMuonTrackCuts->IsSelected(track)) continue;

    track[nGoodMuons] = static_cast<AliAODTrack*>(fAOD->GetTrack(iTrack));
    if(!track[nGoodMuons]) return;

    // is it a good muon track?
    if(!track[nGoodMuons]->IsMuonTrack()) {
        // track[nGoodMuons] = 0x0;
        continue;
    }
    if(!fMuonTrackCuts->IsSelected(track[nGoodMuons])) {
        // track[nGoodMuons] = 0x0;
        continue;
    }


    /* -
     * - Compatibility with Run 1 analysis.
     * -
     */
    // if ( !( (track[nGoodMuons]->Eta() < -2.7) && (track[nGoodMuons]->Eta() > -3.7) ) ) {
    //   continue;
    // }

    // MUON SELECTION
    /* - This is Eugeny Krishen's MUON selection from the talk in 14/1/2019 for
       - the PWG-UD (UPC oriented) meeting. The event selection requires:
       - Muon trigger matching >=2 (1 GeV/c threshold);
       - (-4) < eta < (-2.5);
       - (17.5 cm) < R_{abs} < (89.5 cm);
       - p \times DCA cut;
    */

    // increase counter
    nGoodMuons++;

    // fill muon info
    // fEtaMuonH->Fill(track->Eta());
    // fRAbsMuonH->Fill(track->GetRAtAbsorberEnd());

  }
  /* - We need EXACTLY 2 good muons !!!!!
     -
   */
  if( nGoodMuons != 2 ) {
        PostData(1, fOutputList);
        return;
  }
  fCounterH->Fill(92);



  Int_t FirstMuonVZEROC  = MuonTagCellVZEROC( track[0]->Eta(), track[0]->Phi() );
  Int_t SecondMuonVZEROC = MuonTagCellVZEROC( track[1]->Eta(), track[1]->Phi() );
  fIdentityOfVZEROCH   ->Fill(FirstMuonVZEROC );
  fIdentityOfVZEROCH   ->Fill(SecondMuonVZEROC);
  fVZEROhitsInnerRingsH->Fill(fVZEROCfiredInnerCells);
  fVZEROhitsOuterRingH ->Fill(fOuterRingCells);
  if( fV0TotalNCells > 0 ){
    if ( (Double_t) fV0Hits[FirstMuonVZEROC] > 0.5 || (Double_t) fV0Hits[SecondMuonVZEROC] > 0.5 ) {
      fEventTaggedVZEROCH->Fill(fV0TotalNCells);
    } else {
      fEventNotTaggedVZEROCH->Fill(fV0TotalNCells);
    }
  }

  // Int_t TrueNumberOfActivatedVZEROC = fV0Hits[FirstMuonVZEROC] + fV0Hits[SecondMuonVZEROC];



  /* - Implementing the track cut on the unlike muons
   * -
   */
  if( (track[0]->Charge()) == (track[1]->Charge()) ) {
        TLorentzVector LikeSignMuons[2];
        TLorentzVector FakeJPsi;
        for(int indexMuon = 0; indexMuon < 2; indexMuon++) {
              LikeSignMuons[indexMuon].SetPtEtaPhiM(   track[indexMuon]->Pt(),
                                                       track[indexMuon]->Eta(),
                                                       track[indexMuon]->Phi(),
                                                       TDatabasePDG::Instance()->GetParticle(13)->Mass()
                                                     );
              FakeJPsi += LikeSignMuons[indexMuon];
        }
        fInvariantMassDistributionLikeSignMuonsH->Fill(FakeJPsi.Mag());
        fCounterH->Fill(93);
        // PostData(1, fOutputList);
        // return;




        if( fV0TotalNCells > 0 ){
          if (        (Double_t) fV0Hits[FirstMuonVZEROC] > 0.5 && (Double_t) fV0Hits[SecondMuonVZEROC] > 0.5 ) {
            fPhiSameSignTwoTrkH  ->Fill(FakeJPsi.Phi()     );
            fPtSameSignTwoTrkH   ->Fill(FakeJPsi.Pt()      );
            fRapSameSignTwoTrkH  ->Fill(FakeJPsi.Rapidity());
            fMassSameSignTwoTrkH ->Fill(FakeJPsi.Mag()     );
          } else if ( (Double_t) fV0Hits[FirstMuonVZEROC] > 0.5 || (Double_t) fV0Hits[SecondMuonVZEROC] > 0.5 ) {
            fPhiSameSignOneTrkH  ->Fill(FakeJPsi.Phi()     );
            fPtSameSignOneTrkH   ->Fill(FakeJPsi.Pt()      );
            fRapSameSignOneTrkH  ->Fill(FakeJPsi.Rapidity());
            fMassSameSignOneTrkH ->Fill(FakeJPsi.Mag()     );
          } else { // no matching
            fPhiSameSignZeroTrkH ->Fill(FakeJPsi.Phi()     );
            fPtSameSignZeroTrkH  ->Fill(FakeJPsi.Pt()      );
            fRapSameSignZeroTrkH ->Fill(FakeJPsi.Rapidity());
            fMassSameSignZeroTrkH->Fill(FakeJPsi.Mag()     );
          }
        }
        PostData(1, fOutputList);
        return;

  }
  fCounterH->Fill(94);






  TLorentzVector muons[2];
  TLorentzVector possibleJPsi;
  Double_t       chargeOfMuons[2];
  for(int indexMuon = 0; indexMuon < 2; indexMuon++) {
        muons[indexMuon].SetPtEtaPhiM(   track[indexMuon]->Pt(),
                                         track[indexMuon]->Eta(),
                                         track[indexMuon]->Phi(),
                                         TDatabasePDG::Instance()->GetParticle(13)->Mass()
                                       );
        possibleJPsi += muons[indexMuon];
        chargeOfMuons[indexMuon] = track[indexMuon]->Charge();
  }




  TLorentzVector muonsAtDCA[2];
  TLorentzVector possibleJPsiAtDCA;
  for(int indexMuonAtDCA = 0; indexMuonAtDCA < 2; indexMuonAtDCA++) {
        Double_t EnergyOfTheTrack = TMath::Sqrt(  track[indexMuonAtDCA]->PxAtDCA()*track[indexMuonAtDCA]->PxAtDCA() +
                                                  track[indexMuonAtDCA]->PyAtDCA()*track[indexMuonAtDCA]->PyAtDCA() +
                                                  track[indexMuonAtDCA]->PzAtDCA()*track[indexMuonAtDCA]->PzAtDCA() +
                                                  TDatabasePDG::Instance()->GetParticle(13)->Mass()*TDatabasePDG::Instance()->GetParticle(13)->Mass()/1000000
                                                  );
        muonsAtDCA[indexMuonAtDCA].SetPxPyPzE(   track[indexMuonAtDCA]->PxAtDCA(),
                                                 track[indexMuonAtDCA]->PyAtDCA(),
                                                 track[indexMuonAtDCA]->PzAtDCA(),
                                                 EnergyOfTheTrack
                                                 );
        possibleJPsiAtDCA += muonsAtDCA[indexMuonAtDCA];
  }








  if (  possibleJPsi.Rapidity() >  -4.0 &&
        possibleJPsi.Rapidity() <= -2.5 &&
        possibleJPsi.Mag()      >   2.8 &&
        possibleJPsi.Mag()      <   3.3
        ) {

        fRapidityShapeH     ->Fill(     possibleJPsi.Rapidity());
        fRapidityShapeAtDCAH->Fill(possibleJPsiAtDCA.Rapidity());
        if( fADADecision != 0 ){
          fRapidityShapeADAdecH     ->Fill(     possibleJPsi.Rapidity());
          fRapidityShapeADAdecAtDCAH->Fill(possibleJPsiAtDCA.Rapidity());
        }
        if( fADCDecision != 0 ){
          fRapidityShapeADCdecH     ->Fill(     possibleJPsi.Rapidity());
          fRapidityShapeADCdecAtDCAH->Fill(possibleJPsiAtDCA.Rapidity());
        }
        if( fADADecision != 0 || fADCDecision != 0 ){
          fRapidityShapeADdecH     ->Fill(     possibleJPsi.Rapidity());
          fRapidityShapeADdecAtDCAH->Fill(possibleJPsiAtDCA.Rapidity());
        }

  }



  // if ( possibleJPsi.Rapidity() < -3.7  && possibleJPsi.Rapidity() > -2.7 ) {
  //   PostData(1, fOutputList);
  //   return;
  // }











  // if( (is_VZEROC_set != 1) ) {
  //     fCounterH->Fill(160);
  //     PostData(1, fOutputList);
  //     return;
  // }
  // if( (is_VZEROA_set != 0) ) {
  //     fCounterH->Fill(161);
  //     PostData(1, fOutputList);
  //     return;
  // }
  //_______________________________
  // EVENT SELECTION
  if(fV0ADecision != 0) {
      fCounterH->Fill(95);
      fInvariantMassDistributionHV0ADec->Fill(possibleJPsi.Mag());
  }
  if(fADADecision != 0) {
      fCounterH->Fill(96);
      fInvariantMassDistributionHADADec->Fill(possibleJPsi.Mag());
  }
  if(fADCDecision != 0) {
      fCounterH->Fill(97);
      fInvariantMassDistributionHADCDec->Fill(possibleJPsi.Mag());
  }
  if( !(fV0CDecision == 0 || fV0CDecision == 1) ) {
      fCounterH->Fill(98);
      fInvariantMassDistributionHV0CDec->Fill(possibleJPsi.Mag());
  }
  if( fV0TotalNCells > 2 ) {
      fCounterH->Fill(99);
      fInvariantMassDistributionHV0Ccells->Fill(possibleJPsi.Mag());
  }
  if(   (fV0ADecision != 0)  ||
        (fADADecision != 0)  ||
        (fADCDecision != 0)  ||
        (fV0TotalNCells > 2) ||
        !(fV0CDecision == 0  || fV0CDecision == 1)
      ) {
      fCounterH->Fill(80);
      // PostData(1, fOutputList);
      // return;
  }
  //_______________________________
  if(fV0ADecision != 0 && fADADecision != 0) {
      fCounterH->Fill(110);
  }
  if(fV0ADecision != 0 && fADCDecision != 0) {
      fCounterH->Fill(111);
  }
  if(fV0ADecision != 0 && !(fV0CDecision == 0 || fV0CDecision == 1) ) {
      fCounterH->Fill(112);
  }
  if(fV0ADecision != 0 && fV0TotalNCells > 2) {
      fCounterH->Fill(113);
  }
  //_______________________________
  if(fADADecision != 0 && fADCDecision != 0) {
      fCounterH->Fill(114);
  }
  if(fADADecision != 0 && !(fV0CDecision == 0 || fV0CDecision == 1) ) {
      fCounterH->Fill(115);
  }
  if(fADADecision != 0 && fV0TotalNCells > 2) {
      fCounterH->Fill(116);
  }
  //_______________________________
  if(fADCDecision != 0 && !(fV0CDecision == 0 || fV0CDecision == 1) ) {
      fCounterH->Fill(117);
  }
  if(fADCDecision != 0 && fV0TotalNCells > 2) {
      fCounterH->Fill(118);
  }
  //_______________________________
  if(!(fV0CDecision == 0 || fV0CDecision == 1) && fV0TotalNCells > 2) {
      fCounterH->Fill(119);
  }
  //_______________________________
  Bool_t isZNAfired_2 = kFALSE;
  Bool_t isZNCfired_2 = kFALSE;
  for(Int_t iZDC = 0; iZDC < 4 ; iZDC++) {
    if ( (isZNAfired_2 == 0) && (fZNATDC[iZDC] > -2.) && (fZNATDC[iZDC] < 2.) ) {
      isZNAfired_2 = kTRUE;
    }
    if ( (isZNCfired_2 == 0) && (fZNCTDC[iZDC] > -2.) && (fZNCTDC[iZDC] < 2.) ) {
      isZNCfired_2 = kTRUE;
    }
  }
  //_______________________________
  if(fV0ADecision != 0 && isZNAfired_2 != 0) {
      fCounterH->Fill(120);
  }
  if(fV0ADecision != 0 && isZNCfired_2 != 0) {
      fCounterH->Fill(121);
  }
  //_______________________________
  if(fADADecision != 0 && isZNAfired_2 != 0) {
      fCounterH->Fill(122);
  }
  if(fADADecision != 0 && isZNCfired_2 != 0) {
      fCounterH->Fill(123);
  }
  //_______________________________
  if(fADCDecision != 0 && isZNAfired_2 != 0) {
      fCounterH->Fill(124);
  }
  if(fADCDecision != 0 && isZNCfired_2 != 0) {
      fCounterH->Fill(125);
  }
  //_______________________________
  if(!(fV0CDecision == 0 || fV0CDecision == 1) && isZNAfired_2 != 0) {
      fCounterH->Fill(126);
  }
  if(!(fV0CDecision == 0 || fV0CDecision == 1) && isZNCfired_2 != 0) {
      fCounterH->Fill(127);
  }
  //_______________________________
  if(fV0TotalNCells > 2 && isZNAfired_2 != 0) {
      fCounterH->Fill(128);
  }
  if(fV0TotalNCells > 2 && isZNCfired_2 != 0) {
      fCounterH->Fill(129);
  }
  if(is_VZEROA_set == 0) {
      fCounterH->Fill(150);
  }
  if(is_VZEROA_set == 1) {
      fCounterH->Fill(151);
  }
  if(is_VZEROC_set == 0) {
      fCounterH->Fill(152);
  }
  if(is_VZEROC_set == 1) {
      fCounterH->Fill(153);
  }
  // if( (is_VZEROC_set != 1) ) {
  //     fCounterH->Fill(160);
  //     PostData(1, fOutputList);
  //     return;
  // }
  // if( (is_VZEROA_set != 0) ) {
  //     fCounterH->Fill(161);
  //     PostData(1, fOutputList);
  //     return;
  // }



  // Event selection
  //_____________________________________


















  for(Int_t iFilling = 0; iFilling < nGoodMuons; iFilling++) {
        fEtaMuonH ->Fill(track[iFilling]->Eta());
        fRAbsMuonH->Fill(track[iFilling]->GetRAtAbsorberEnd());
  }
  // store muons
  fNumberMuonsH->Fill(nGoodMuons);
  fEntriesAgainstRunNumberH->Fill(fRunNum);
  /* - This is the last part of my try to obtain a proper RunNumbers histogram...
     -
   */
  fEntriesAgainstRunNumberProperlyH->Fill( Form("%d", fRunNum) , 1 );
  if (nGoodMuons>0) fCounterH->Fill(iSelectionCounter); // At least one good muon
  // fCounterH->Fill(94);
  iSelectionCounter++;



  /* - Finally the core!!!
   * - What will be happening is that we will instantiate TLorentzVectors to
   * - obtain the invariant mass of the dimuon system. If everything goes fine
   * - after this we should be able to obtain the peak of the J/Psi. But
   * - things never go as expected, so who knows!
   */
  // TLorentzVector muons[2];
  // TLorentzVector possibleJPsi;
  // Double_t       chargeOfMuons[2];
  // for(int indexMuon = 0; indexMuon < 2; indexMuon++) {
  //       muons[indexMuon].SetPtEtaPhiM(   track[indexMuon]->Pt(),
  //                                        track[indexMuon]->Eta(),
  //                                        track[indexMuon]->Phi(),
  //                                        TDatabasePDG::Instance()->GetParticle(13)->Mass()
  //                                      );
  //       possibleJPsi += muons[indexMuon];
  //       chargeOfMuons[indexMuon] = track[indexMuon]->Charge();
  // }
  fEtaDimuonH->Fill(possibleJPsi.Rapidity());
  fInvariantMassDistributionH->Fill(possibleJPsi.Mag());
  if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -2.60 ) {
      // fInvariantMassDistributionH->Fill(possibleJPsi.Mag());
      fInvariantMassDistributionExtendedH->Fill(possibleJPsi.Mag());
      if( possibleJPsi.Rapidity() <= -3.10 ) {
        fInvariantMassDistributionRapidityBinsNewH[0]->Fill(possibleJPsi.Mag());
      } else {
        fInvariantMassDistributionRapidityBinsNewH[1]->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP14-B-NOPF-MUFAST") )  {
        fInvariantMassDistributionHCMUP14->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP23-B-NOPF-MUFAST") )  {
        fInvariantMassDistributionHCMUP23->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP15-B-NOPF-ALLNOTRD") )  {
        fInvariantMassDistributionHCMUP15->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP22-B-NOPF-ALLNOTRD") )  {
        fInvariantMassDistributionHCMUP22->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP3") )  {
        fInvariantMassDistributionHCMUP3->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP8") )  {
        fInvariantMassDistributionHCMUP8->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP16") )  {
        fInvariantMassDistributionHCMUP16->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP17") )  {
        fInvariantMassDistributionHCMUP17->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP18") )  {
        fInvariantMassDistributionHCMUP18->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP19") )  {
        fInvariantMassDistributionHCMUP19->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP20") )  {
        fInvariantMassDistributionHCMUP20->Fill(possibleJPsi.Mag());
      }
      if ( trigger.Contains("CMUP21") )  {
        fInvariantMassDistributionHCMUP21->Fill(possibleJPsi.Mag());
      }
  }



  /* -
   * -
   * - IR timing maps
   * -
   */
  Int_t fClosestIR1         = 100;
  Int_t fClosestIR2         = 100;
  Int_t fClosestIR1truesign = 100;
  Int_t fClosestIR2truesign = 100;
  for(Int_t item=-1; item>=-90; item--) {
    Int_t bin = 90+item;
    Bool_t isFired = fIR1Map.TestBitNumber(bin);
    if(isFired) {
      fClosestIR1         = TMath::Abs(item);
      fClosestIR1truesign = item;
      break;
    }
  if(fClosestIR1         == 100)fClosestIR1         = 0;
  if(fClosestIR1truesign == 100)fClosestIR1truesign = 0;
  }
  for(Int_t item=-1; item>=-90; item--) {
    Int_t bin = 90+item;
    Bool_t isFired = fIR2Map.TestBitNumber(bin);
    if(isFired) {
      fClosestIR2 = TMath::Abs(item);
      fClosestIR2truesign = item;
      break;
    }
  }
  if(fClosestIR2         == 100)fClosestIR2         = 0;
  if(fClosestIR2truesign == 100)fClosestIR2truesign = 0;

  fIROneH->Fill(fClosestIR1);
  fIRTwoH->Fill(fClosestIR2);








  /**
   * - Pt-integrated analysis
   * - in 2 rapidity bins.
   * -
   */
  if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -3.25 ) {
    fInvariantMassDistributionRapidityBinsH[0]->Fill(possibleJPsi.Mag());
  } else if ( possibleJPsi.Rapidity() > -3.25 && possibleJPsi.Rapidity() <= -2.50 ) {
    fInvariantMassDistributionRapidityBinsH[1]->Fill(possibleJPsi.Mag());
  }

  /**
   * - Pt-integrated analysis
   * - in 3 rapidity bins.
   * -
   */
  if (        possibleJPsi.Rapidity() > -4.0  && possibleJPsi.Rapidity() <= -3.50 ) {
    fInvariantMassDistributionMoreRapidityBinsH[0]->Fill(possibleJPsi.Mag());
  } else if ( possibleJPsi.Rapidity() > -3.50 && possibleJPsi.Rapidity() <= -3.00 ) {
    fInvariantMassDistributionMoreRapidityBinsH[1]->Fill(possibleJPsi.Mag());
  } else if ( possibleJPsi.Rapidity() > -3.00 && possibleJPsi.Rapidity() <= -2.50 ) {
    fInvariantMassDistributionMoreRapidityBinsH[2]->Fill(possibleJPsi.Mag());
  }



  /* - Now we are evaluating the pt of the dimuon pair. Generally speaking,
     - if such a pt is less than 0.25 GeV/c then it fills the coherent
     - component, otherwise the incoherent component. At this point we may fill
     - even the dimuon pt distribution histogram and see if it looks like Kay's.
     -
   */
  Double_t ptOfTheDimuonPair = possibleJPsi.Pt();
  if( ptOfTheDimuonPair < 0.25) {
        fInvariantMassDistributionCoherentH->Fill(possibleJPsi.Mag());
        fInvariantMassDistributionCoherentExtendedH->Fill(possibleJPsi.Mag());
        if (        possibleJPsi.Rapidity() > -4.0  && possibleJPsi.Rapidity() <= -3.75 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[0]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.75 && possibleJPsi.Rapidity() <= -3.50 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[1]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.50 && possibleJPsi.Rapidity() <= -3.25 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[2]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.25 && possibleJPsi.Rapidity() <= -3.00 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[3]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -3.00 && possibleJPsi.Rapidity() <= -2.75 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[4]->Fill(possibleJPsi.Mag());
        } else if ( possibleJPsi.Rapidity() > -2.75 && possibleJPsi.Rapidity() <= -2.50 ) {
          fInvariantMassDistributionCoherentRapidityBinsH[5]->Fill(possibleJPsi.Mag());
        }
  } else {
        fInvariantMassDistributionIncoherentH->Fill(possibleJPsi.Mag());
        fInvariantMassDistributionIncoherentExtendedH->Fill(possibleJPsi.Mag());
  }
  // fDimuonPtDistributionH->Fill(ptOfTheDimuonPair);
  if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
    fDimuonPtDistributionH            ->Fill(ptOfTheDimuonPair);
    fDimuonPtDistributionShiftPlusOneH->Fill(ptOfTheDimuonPair);
  }

  if( ptOfTheDimuonPair < 0.200 ) {
    fInvariantMassDistributionCoherentShiftMinusTwoH->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftMinusTwoH->Fill(possibleJPsi.Mag());
  }
  if( ptOfTheDimuonPair < 0.225 ) {
    fInvariantMassDistributionCoherentShiftMinusOneH->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftMinusOneH->Fill(possibleJPsi.Mag());
  }
  if( ptOfTheDimuonPair < 0.275 ) {
    fInvariantMassDistributionCoherentShiftPlusOneH ->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftPlusOneH ->Fill(possibleJPsi.Mag());
  }
  if( ptOfTheDimuonPair < 0.300 ) {
    fInvariantMassDistributionCoherentShiftPlusTwoH ->Fill(possibleJPsi.Mag());
  } else {
    fInvariantMassDistributionIncoherentShiftPlusTwoH ->Fill(possibleJPsi.Mag());
  }




  if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -2.50 ) {
      if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
        // if( FirstMuonVZEROC > 23 && SecondMuonVZEROC > 23 ) {
        if( (Double_t) fOuterRingCells > 0.5 ) {
          fDimuonPtDistributionOuterRingH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fThirdRingCells > 0.5 ) {
          fDimuonPtDistributionAtLeastOneMuonOuterRingH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fOuterRingCells < 0.5 && (Double_t) fThirdRingCells > 0.5 ) {
          fDimuonPtDistributionSecondRingH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fOuterRingCells > 0.5 && (Double_t) fThirdRingCells > 0.5 ) {
          fDimuonPtDistributionCorrelationVZEROH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fClosestIR1 < 0.5 ) {
          fDimuonPtDistributionNullIROneH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fClosestIR2 < 0.5 ) {
          fDimuonPtDistributionNullIRTwoH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fClosestIR1truesign < 0 ) {
          fDimuonPtDistributionNegativeIROneH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fClosestIR1truesign > 0 ) {
          fDimuonPtDistributionPositiveIROneH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fClosestIR2truesign < 0 ) {
          fDimuonPtDistributionNegativeIRTwoH->Fill(ptOfTheDimuonPair);
        }
        if( (Double_t) fClosestIR2truesign > 0 ) {
          fDimuonPtDistributionPositiveIRTwoH->Fill(ptOfTheDimuonPair);
        }
      }
  }



  /* - Now this is a critical part of  the analysis. What happens next is a
     - differential analysis in terms of the energy perceived by the neutron ZDC.
     - What it means is that now we may cut on those sensible values to select
     - only those J/Psi candidates falling under a certain peak of the neutron
     - ZNC energy distribution. It will be seen that the fZNCEnergyAgainstEntriesH
     - plot will present many gaussian-like peaks. Each peak represent an
     - increasingly large number of neutrons seen by the ZNC.
     -
     - Starting from the first peak, 0n, then 1n, hopefully 2n, but anything
     - else is more like a guess. If my understanding is good enough, even the
     - 2n peak requires user input to facilitate the minimizer's job.
     -
     - So, first thing first, Guillermo Contreras has suggested the preliminary
     - cut on the ZDC time, quoting:
     - "The energy value makes sense only when the time information is not
     - -999... You can choose times |t|<5 ns to plot the energy distributions
     - in the neutron ZDC".
     -
     - This happens with the request |fZNCTime|<5 if I have understood correctly.
     - After this we can fill whatever histogram we want to.
     -
     -
     -
     - NEW: after UPC meeting 5/3/2019
     - On ZDC timing. Usually we use time information from TDCs corresponding to
     - the common PMT (reads all four ZN sectors) on both sides. Each AOD event
     - contains information on up to four consecutive timing hits from these
     - TDCs within +/-12 bcs around the trigger bunch crossing. These hits are
     - stored in fZNATDCm and fZNCTDCm arrays:
     - https://github.com/alisw/AliRoot/blob/master/STEER/AOD/AliAODZDC.h#L153
     - and can be accessed as in:
     -
     - AliAODZDC* aodZDC = aod->GetZDCData();
     - for (Int_t i=0;i<4;i++) fZNATDC[i] = aodZDC->GetZNATDCm(i);
     - for (Int_t i=0;i<4;i++) fZNCTDC[i] = aodZDC->GetZNCTDCm(i);
     -
     - These hits may come from hadronic or EMD processes in neighbouring bcs.
     - In Pb-Pb we usually have 0-2 hits within +/-12 bcs mainly due to EMD.
     - Unused timing slots in these arrays are filled with large negative value
     - (-999). In order to check if there was a timing hit in the trigger bc,
     - you have to check if at least one timing hit out of four is within +/-2
     - ns around 0.
     -
     - Regarding these getters GetZNATime() and GetZNCTime(), defined here:
     - https://github.com/alisw/AliRoot/blob/master/STEER/AOD/AliAODZDC.h#L51
     - They are outdated because, as mentioned here, they return timing
     - information from the first slot in those arrays (fZNATDCm[0], fZNCTDCm[0]):
     - https://github.com/alisw/AliRoot/blob/master/STEER/AOD/AliAODZDC.h#L145
     - The first hit often corresponds to previous bunch crossings (e.g. EMD),
     - while interesting hit around 0 may be stored in the next slots.
     -
     -
   */
  Bool_t isZNAfired = kFALSE;
  Bool_t isZNCfired = kFALSE;
  Bool_t isZNAfiredStrict = kFALSE;
  Bool_t isZNCfiredStrict = kFALSE;
  Int_t  counterZNA = 0;
  Int_t  counterZNC = 0;
  /* - Note that in C++ the && and || operators "short-circuit". That means that
     - they only evaluate a parameter if required. If the first parameter to &&
     - is false, or the first to || is true, the rest will not be evaluated.
     - That means that writing:
     - if ( (isZNAfired == 0) && (...) )
     - should mean effectively
     - if ( isZNAfired != 0 ) continue;
     - hence it should be *at least* one hit!!!
     -
   */
  for(Int_t iZDC = 0; iZDC < 4 ; iZDC++) {
    if ( (isZNAfired == 0) && (fZNATDC[iZDC] > -2.) && (fZNATDC[iZDC] < 2.) ) {
      isZNAfired = kTRUE;
      /* - After mail with Chiara Oppedisano, it seems like the best way
         - to proceed is to firstly call the IsZNAfired() and then filling...
         -
         - If this doesn't appear in later pulls it is because this
         - doesn't seem to suit my case...
         -
       */
      // if( dataZDC->IsZNAfired() ) {
      //   if ( (possibleJPsi.Mag() > 2.85) && (possibleJPsi.Mag() < 3.35) ){
      //     fZNATimeAgainstEntriesH->Fill(fZNATDC[iZDC]);
      //   }
      // }
      // fCounterZNAH->Fill(counterZNA);
    }
    if ( (isZNCfired == 0) && (fZNCTDC[iZDC] > -2.) && (fZNCTDC[iZDC] < 2.) ) {
      isZNCfired = kTRUE;
      // if( dataZDC->IsZNCfired() ) {
      //   if ( (possibleJPsi.Mag() > 2.85) && (possibleJPsi.Mag() < 3.35) ){
      //     fZNCTimeAgainstEntriesH->Fill(fZNCTDC[iZDC]);
      //   }
      // }
      // fCounterZNCH->Fill(counterZNC);
    }
    counterZNA++;
    counterZNC++;
  }

  if ( isZNCfired != 0 ) {
    fZNCEnergyAgainstEntriesH        ->Fill(fZNCEnergy);
    fZNCEnergyAgainstEntriesExtendedH->Fill(fZNCEnergy);
    // if ( calibrated == 0 ) fZNCEnergyUncalibratedH->Fill(fZNCEnergy);
    // if ( calibrated == 1 ) {
    //   fZNCEnergyCalibratedH          ->Fill( fZNCEnergy );
    //   fZNCEnergyCalibratedHigherGainH->Fill( dataZDC->GetZNCTowerEnergyLR()[0] );
    // }
    fZNCEnergyAfterTimingVsADAMultiH->Fill(fZNCEnergy, ADAmultiplicitiesTotal);
    fZNCEnergyAfterTimingVsADCMultiH->Fill(fZNCEnergy, ADCmultiplicitiesTotal);
    fZNCEnergyAfterTimingVsADMultiH ->Fill(fZNCEnergy, ADmultiplicitiesTotal );
  }
  fZNCEnergyBeforeTimingSelectionH        ->Fill(fZNCEnergy);
  fZNCEnergyBeforeTimingSelectionExtendedH->Fill(fZNCEnergy);
  fZNCEnergyBeforeTimingVsADAMultiH->Fill(fZNCEnergy, ADAmultiplicitiesTotal);
  fZNCEnergyBeforeTimingVsADCMultiH->Fill(fZNCEnergy, ADCmultiplicitiesTotal);
  fZNCEnergyBeforeTimingVsADMultiH ->Fill(fZNCEnergy, ADmultiplicitiesTotal );

  if ( dataZDC->IsZNCfired() && ( isZNCfired != 0 ) ) {
    fZNCEnergyAgainstEntriesExtendedHv2->Fill(fZNCEnergy);
  }
  if ( dataZDC->IsZNAfired() && ( isZNAfired != 0 ) ) {
    fZNAEnergyAgainstEntriesExtendedHv2->Fill(fZNAEnergy);
  }
  if ( isZNAfired != 0 ) {
    fZNAEnergyAgainstEntriesH        ->Fill(fZNAEnergy);
    fZNAEnergyAgainstEntriesExtendedH->Fill(fZNAEnergy);
    // if ( calibrated == 0 ) fZNAEnergyUncalibratedH->Fill(fZNAEnergy);
    // if ( calibrated == 1 ) {
    //   fZNAEnergyCalibratedH          ->Fill( fZNAEnergy );
    //   fZNAEnergyCalibratedHigherGainH->Fill( dataZDC->GetZNATowerEnergyLR()[0] );
    // }
    fZNAEnergyAfterTimingVsADAMultiH->Fill(fZNAEnergy, ADAmultiplicitiesTotal);
    fZNAEnergyAfterTimingVsADCMultiH->Fill(fZNAEnergy, ADCmultiplicitiesTotal);
    fZNAEnergyAfterTimingVsADMultiH ->Fill(fZNAEnergy, ADmultiplicitiesTotal );
  }
  fZNAEnergyBeforeTimingSelectionH        ->Fill(fZNAEnergy);
  fZNAEnergyBeforeTimingSelectionExtendedH->Fill(fZNAEnergy);
  fZNAEnergyBeforeTimingVsADAMultiH->Fill(fZNAEnergy, ADAmultiplicitiesTotal);
  fZNAEnergyBeforeTimingVsADCMultiH->Fill(fZNAEnergy, ADCmultiplicitiesTotal);
  fZNAEnergyBeforeTimingVsADMultiH ->Fill(fZNAEnergy, ADmultiplicitiesTotal );









  if( isZNCfired == 0 ) {
    if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -2.60 ) {
        // fInvariantMassDistributionZeroZNCH->Fill(possibleJPsi.Mag());
        // if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
        //   fDimuonPtDistributionZeroZNCH   ->Fill(ptOfTheDimuonPair);
        // }
        if( possibleJPsi.Rapidity() <= -3.10 ) {
          fInvariantMassDistributionRapidityBinsZeroZNCH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCbinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else {
          fInvariantMassDistributionRapidityBinsZeroZNCH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCbinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        }
    }












    if (        possibleJPsi.Rapidity() > -3.7 && possibleJPsi.Rapidity() <= -2.7 ) {
        if (   ptOfTheDimuonPair < 1.00 ) {
          if ( possibleJPsi.Rapidity() < -3.2 ){
            fInvariantMassDistributionZeroZNC37to37H[0]->Fill(possibleJPsi.Mag());
          } else{
            fInvariantMassDistributionZeroZNC37to37H[1]->Fill(possibleJPsi.Mag());
          }
        }
        if ( possibleJPsi.Rapidity() < -3.2 ){
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCbins27to37H[0]->Fill(ptOfTheDimuonPair);
          }
        } else {
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCbins27to37H[1]->Fill(ptOfTheDimuonPair);
          }
        }


    }









    if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -2.50 ) {
        if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionZeroZNCH->Fill(possibleJPsi.Mag());
        if ( ptOfTheDimuonPair < 1.00 && fVZEROCfiredcells < 5 ) fInvariantMassDistributionZeroZNCVZEROhitsLessThanFiveH->Fill(possibleJPsi.Mag());
        if ( ptOfTheDimuonPair < 1.00 && fVZEROCfiredcells > 4 ) fInvariantMassDistributionZeroZNCVZEROhitsMoreThanFiveH->Fill(possibleJPsi.Mag());


        // GammaGamma Study
        if ( (possibleJPsi.Mag() > 2.2) && (possibleJPsi.Mag() < 2.7) ) {
          fDimuonPtDistributionGammaGammaZNCH->Fill(ptOfTheDimuonPair);
        }


        // rejected events study
        if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
          if ( (fV0ADecision != 0) || (fADADecision != 0) || (fADCDecision != 0)  || !(fV0CDecision == 0  || fV0CDecision == 1) ){
            fDimuonPtDistributionRejectedZNCflagH->Fill(ptOfTheDimuonPair);
          }
        }

        if ( (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 2.8) ) {
          fPtSidebandZeroZNCH->Fill(ptOfTheDimuonPair);
          if            (possibleJPsi.Rapidity() <= -3.5) {
            fPtSidebandZeroZNCRapidityH[0]->Fill(ptOfTheDimuonPair);
            if (        (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 1.3) ) {
              fPtSidebandZeroZNCRapidityAndMassH[0]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.3) && (possibleJPsi.Mag() < 1.8) ) {
              fPtSidebandZeroZNCRapidityAndMassH[1]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.8) && (possibleJPsi.Mag() < 2.3) ) {
              fPtSidebandZeroZNCRapidityAndMassH[2]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 2.3) && (possibleJPsi.Mag() < 2.8) ) {
              fPtSidebandZeroZNCRapidityAndMassH[3]->Fill(ptOfTheDimuonPair);
            }
          } else if (possibleJPsi.Rapidity() <= -3.0) {
            fPtSidebandZeroZNCRapidityH[1]->Fill(ptOfTheDimuonPair);
            if (        (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 1.3) ) {
              fPtSidebandZeroZNCRapidityAndMassH[4]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.3) && (possibleJPsi.Mag() < 1.8) ) {
              fPtSidebandZeroZNCRapidityAndMassH[5]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.8) && (possibleJPsi.Mag() < 2.3) ) {
              fPtSidebandZeroZNCRapidityAndMassH[6]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 2.3) && (possibleJPsi.Mag() < 2.8) ) {
              fPtSidebandZeroZNCRapidityAndMassH[7]->Fill(ptOfTheDimuonPair);
            }
          } else if (possibleJPsi.Rapidity() <= -2.5) {
            fPtSidebandZeroZNCRapidityH[2]->Fill(ptOfTheDimuonPair);
            if (        (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 1.3) ) {
              fPtSidebandZeroZNCRapidityAndMassH[8]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.3) && (possibleJPsi.Mag() < 1.8) ) {
              fPtSidebandZeroZNCRapidityAndMassH[9]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.8) && (possibleJPsi.Mag() < 2.3) ) {
              fPtSidebandZeroZNCRapidityAndMassH[10]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 2.3) && (possibleJPsi.Mag() < 2.8) ) {
              fPtSidebandZeroZNCRapidityAndMassH[11]->Fill(ptOfTheDimuonPair);
            }
          }
        }
        if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
          fDimuonPtDistributionZeroZNCH   ->Fill(ptOfTheDimuonPair);
          if ( fVZEROCfiredcells < 5 ) {
            fDimuonPtDistributionZeroZNCVZEROhitsLessThanFiveH->Fill( ptOfTheDimuonPair );
          } else {
            fDimuonPtDistributionZeroZNCVZEROhitsMoreThanFiveH->Fill( ptOfTheDimuonPair );
          }
        }
        if(        possibleJPsi.Rapidity() <= -3.625 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNCH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfourbinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.625 && possibleJPsi.Rapidity() <= -3.250 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNCH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfourbinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.250 && possibleJPsi.Rapidity() <= -2.875 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNCH[2]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfourbinsH[2]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -2.875 && possibleJPsi.Rapidity() <= -2.500 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNCH[3]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfourbinsH[3]           ->Fill(ptOfTheDimuonPair);
          }
        }




        if(        possibleJPsi.Rapidity() <= -3.5 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityThreeBinsZeroZNCH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCthreebinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.5 && possibleJPsi.Rapidity() <= -3.0 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityThreeBinsZeroZNCH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCthreebinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.0 && possibleJPsi.Rapidity() <= -2.5 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityThreeBinsZeroZNCH[2]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCthreebinsH[2]           ->Fill(ptOfTheDimuonPair);
          }
        }





        if(        possibleJPsi.Rapidity() <= -3.7 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNCH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfivebinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.7 && possibleJPsi.Rapidity() <= -3.4 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNCH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfivebinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.4 && possibleJPsi.Rapidity() <= -3.1 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNCH[2]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfivebinsH[2]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.1 && possibleJPsi.Rapidity() <= -2.8 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNCH[3]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfivebinsH[3]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -2.8 && possibleJPsi.Rapidity() <= -2.5 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNCH[4]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNCfivebinsH[4]           ->Fill(ptOfTheDimuonPair);
          }
        }


    }

  }

  if( isZNAfired == 0 ) {
    if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -2.60 ) {
        // fInvariantMassDistributionZeroZNAH->Fill(possibleJPsi.Mag());
        // if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
        //   fDimuonPtDistributionZeroZNAH   ->Fill(ptOfTheDimuonPair);
        // }
        if( possibleJPsi.Rapidity() <= -3.10 ) {
          fInvariantMassDistributionRapidityBinsZeroZNAH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAbinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else {
          fInvariantMassDistributionRapidityBinsZeroZNAH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAbinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        }
    }












    if (        possibleJPsi.Rapidity() > -3.7 && possibleJPsi.Rapidity() <= -2.7 ) {
        if (   ptOfTheDimuonPair < 1.00 ) {
          if ( possibleJPsi.Rapidity() < -3.2 ){
            fInvariantMassDistributionZeroZNA37to37H[0]->Fill(possibleJPsi.Mag());
          } else{
            fInvariantMassDistributionZeroZNA37to37H[1]->Fill(possibleJPsi.Mag());
          }
        }
        if ( possibleJPsi.Rapidity() < -3.2 ){
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAbins27to37H[0]->Fill(ptOfTheDimuonPair);
          }
        } else {
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAbins27to37H[1]->Fill(ptOfTheDimuonPair);
          }
        }


    }









    if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -2.50 ) {
        if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionZeroZNAH->Fill(possibleJPsi.Mag());
        if ( ptOfTheDimuonPair < 1.00 && fVZEROCfiredcells < 5 ) fInvariantMassDistributionZeroZNAVZEROhitsLessThanFiveH->Fill(possibleJPsi.Mag());
        if ( ptOfTheDimuonPair < 1.00 && fVZEROCfiredcells > 4 ) fInvariantMassDistributionZeroZNAVZEROhitsMoreThanFiveH->Fill(possibleJPsi.Mag());
        if ( fVZEROCfiredcells < 5 ) {
          fDimuonPtDistributionZeroZNAVZEROhitsLessThanFiveH->Fill( ptOfTheDimuonPair );
        } else {
          fDimuonPtDistributionZeroZNAVZEROhitsMoreThanFiveH->Fill( ptOfTheDimuonPair );
        }


                // rejected events study
                if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
                  if ( (fV0ADecision != 0) || (fADADecision != 0) || (fADCDecision != 0)  || !(fV0CDecision == 0  || fV0CDecision == 1) ){
                    fDimuonPtDistributionRejectedZNAflagH->Fill(ptOfTheDimuonPair);
                  }
                }

        // GammaGamma Study
        if ( (possibleJPsi.Mag() > 2.2) && (possibleJPsi.Mag() < 2.7) ) {
          fDimuonPtDistributionGammaGammaZNAH->Fill(ptOfTheDimuonPair);
        }


        if ( (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 2.8) ) {
          fPtSidebandZeroZNAH->Fill(ptOfTheDimuonPair);
          if            (possibleJPsi.Rapidity() <= -3.5) {
            fPtSidebandZeroZNARapidityH[0]->Fill(ptOfTheDimuonPair);
            if (        (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 1.3) ) {
              fPtSidebandZeroZNARapidityAndMassH[0]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.3) && (possibleJPsi.Mag() < 1.8) ) {
              fPtSidebandZeroZNARapidityAndMassH[1]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.8) && (possibleJPsi.Mag() < 2.3) ) {
              fPtSidebandZeroZNARapidityAndMassH[2]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 2.3) && (possibleJPsi.Mag() < 2.8) ) {
              fPtSidebandZeroZNARapidityAndMassH[3]->Fill(ptOfTheDimuonPair);
            }
          } else if (possibleJPsi.Rapidity() <= -3.0) {
            fPtSidebandZeroZNARapidityH[1]->Fill(ptOfTheDimuonPair);
            if (        (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 1.3) ) {
              fPtSidebandZeroZNARapidityAndMassH[4]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.3) && (possibleJPsi.Mag() < 1.8) ) {
              fPtSidebandZeroZNARapidityAndMassH[5]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.8) && (possibleJPsi.Mag() < 2.3) ) {
              fPtSidebandZeroZNARapidityAndMassH[6]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 2.3) && (possibleJPsi.Mag() < 2.8) ) {
              fPtSidebandZeroZNARapidityAndMassH[7]->Fill(ptOfTheDimuonPair);
            }
          } else if (possibleJPsi.Rapidity() <= -2.5) {
            fPtSidebandZeroZNARapidityH[2]->Fill(ptOfTheDimuonPair);
            if (        (possibleJPsi.Mag() > 0.8) && (possibleJPsi.Mag() < 1.3) ) {
              fPtSidebandZeroZNARapidityAndMassH[8]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.3) && (possibleJPsi.Mag() < 1.8) ) {
              fPtSidebandZeroZNARapidityAndMassH[9]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 1.8) && (possibleJPsi.Mag() < 2.3) ) {
              fPtSidebandZeroZNARapidityAndMassH[10]->Fill(ptOfTheDimuonPair);
            } else if ( (possibleJPsi.Mag() > 2.3) && (possibleJPsi.Mag() < 2.8) ) {
              fPtSidebandZeroZNARapidityAndMassH[11]->Fill(ptOfTheDimuonPair);
            }
          }
        }
        if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
          fDimuonPtDistributionZeroZNAH   ->Fill(ptOfTheDimuonPair);
        }
        if(        possibleJPsi.Rapidity() <= -3.625 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNAH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfourbinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.625 && possibleJPsi.Rapidity() <= -3.250 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNAH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfourbinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.250 && possibleJPsi.Rapidity() <= -2.875 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNAH[2]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfourbinsH[2]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -2.875 && possibleJPsi.Rapidity() <= -2.500 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFourBinsZeroZNAH[3]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfourbinsH[3]           ->Fill(ptOfTheDimuonPair);
          }
        }





        if(        possibleJPsi.Rapidity() <= -3.5 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityThreeBinsZeroZNAH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAthreebinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.5 && possibleJPsi.Rapidity() <= -3.0 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityThreeBinsZeroZNAH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAthreebinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.0 && possibleJPsi.Rapidity() <= -2.5 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityThreeBinsZeroZNAH[2]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAthreebinsH[2]           ->Fill(ptOfTheDimuonPair);
          }
        }






        if(        possibleJPsi.Rapidity() <= -3.7 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNAH[0]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfivebinsH[0]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.7 && possibleJPsi.Rapidity() <= -3.4 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNAH[1]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfivebinsH[1]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.4 && possibleJPsi.Rapidity() <= -3.1 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNAH[2]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfivebinsH[2]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -3.1 && possibleJPsi.Rapidity() <= -2.8 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNAH[3]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfivebinsH[3]           ->Fill(ptOfTheDimuonPair);
          }
        } else if( possibleJPsi.Rapidity() > -2.8 && possibleJPsi.Rapidity() <= -2.5 ) {
          if ( ptOfTheDimuonPair < 1.00 ) fInvariantMassDistributionRapidityFiveBinsZeroZNAH[4]->Fill(possibleJPsi.Mag());
          if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
            fDimuonPtDistributionZeroZNAfivebinsH[4]           ->Fill(ptOfTheDimuonPair);
          }
        }


    }



  }

  //_______________________________
  /* -
   * - Requiring that one neutron peak.
   */
  if( isZNCfired != 0 ) {
    fCounterH->Fill(60);
    if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -2.50 ) {
        fInvariantMassDistributionOneNeutronZNCH->Fill(possibleJPsi.Mag());
        if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
          fDimuonPtDistributionOneNeutronZNCH   ->Fill(ptOfTheDimuonPair);
        }
    }
  }

  if( isZNAfired != 0 ) {
    fCounterH->Fill(61);
    if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -2.50 ) {
        fInvariantMassDistributionOneNeutronZNAH->Fill(possibleJPsi.Mag());
        if ( (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
          fDimuonPtDistributionOneNeutronZNAH   ->Fill(ptOfTheDimuonPair);
        }
    }
  }
  //_______________________________



  if( fZNCEnergy > -500.0 && fZNCEnergy < 500.0 ) {
    if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -2.60 ) {
        fInvariantMassDistributionZeroZNCenergyH->Fill(possibleJPsi.Mag());
        if( possibleJPsi.Rapidity() <= -3.10 ) {
          fInvariantMassDistributionRapidityBinsZeroZNCenergyH[0]->Fill(possibleJPsi.Mag());
        } else {
          fInvariantMassDistributionRapidityBinsZeroZNCenergyH[1]->Fill(possibleJPsi.Mag());
        }
    }
  }

  if( fZNAEnergy > -15.0 && fZNAEnergy < 15.0 ) {
    if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -2.60 ) {
        fInvariantMassDistributionZeroZNAenergyH->Fill(possibleJPsi.Mag());
        if( possibleJPsi.Rapidity() <= -3.10 ) {
          fInvariantMassDistributionRapidityBinsZeroZNAenergyH[0]->Fill(possibleJPsi.Mag());
        } else {
          fInvariantMassDistributionRapidityBinsZeroZNAenergyH[1]->Fill(possibleJPsi.Mag());
        }
    }
  }


  if( isZNCfired == 0 ) {
        if( isZNAfired == 0 ) {
            if ( ptOfTheDimuonPair < 1.00 ) {
                fInvariantMassDistribution0N0NH->Fill(possibleJPsi.Mag());
                /**
                 * - Pt-integrated analysis
                 * - in 2 rapidity bins.
                 * -
                 */
                if (        possibleJPsi.Rapidity() > -4.00 && possibleJPsi.Rapidity() <= -3.25 ) {
                  fInvariantMassDistributionRapidityBins0N0NH[0]->Fill(possibleJPsi.Mag());
                } else if ( possibleJPsi.Rapidity() > -3.25 && possibleJPsi.Rapidity() <= -2.50 ) {
                  fInvariantMassDistributionRapidityBins0N0NH[1]->Fill(possibleJPsi.Mag());
                }
                /**
                 * - Pt-integrated analysis
                 * - in 3 rapidity bins.
                 * -
                 */
                if (        possibleJPsi.Rapidity() > -4.0  && possibleJPsi.Rapidity() <= -3.50 ) {
                  fInvariantMassDistributionMoreRapidityBins0N0NH[0]->Fill(possibleJPsi.Mag());
                } else if ( possibleJPsi.Rapidity() > -3.50 && possibleJPsi.Rapidity() <= -3.00 ) {
                  fInvariantMassDistributionMoreRapidityBins0N0NH[1]->Fill(possibleJPsi.Mag());
                } else if ( possibleJPsi.Rapidity() > -3.00 && possibleJPsi.Rapidity() <= -2.50 ) {
                  fInvariantMassDistributionMoreRapidityBins0N0NH[2]->Fill(possibleJPsi.Mag());
                }
                /**
                 * - Pt-integrated analysis
                 * - in 2 rapidity bins.
                 * -
                 */
                if (        possibleJPsi.Rapidity() > -3.60 && possibleJPsi.Rapidity() <= -3.10 ) {
                  fInvariantMassDistributionSmall0N0NH               ->Fill(possibleJPsi.Mag());
                  fInvariantMassDistributionRapidityBinsSmall0N0NH[0]->Fill(possibleJPsi.Mag());
                  // fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
                  // fDimuonPtDistributionRestrictedRapidity0N0N36to31H ->Fill(ptOfTheDimuonPair);
                } else if ( possibleJPsi.Rapidity() > -3.10 && possibleJPsi.Rapidity() <= -2.60 ) {
                  fInvariantMassDistributionSmall0N0NH               ->Fill(possibleJPsi.Mag());
                  fInvariantMassDistributionRapidityBinsSmall0N0NH[1]->Fill(possibleJPsi.Mag());
                  // fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
                  // fDimuonPtDistributionRestrictedRapidity0N0N31to26H ->Fill(ptOfTheDimuonPair);
                }

            }

            if (        (possibleJPsi.Rapidity() > -3.60) && (possibleJPsi.Rapidity() <= -3.10) && (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
              fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
              fDimuonPtDistributionRestrictedRapidity0N0N36to31H ->Fill(ptOfTheDimuonPair);
              /* -
               * - Variable pt-binning.
               * -
               */
              if (        ptOfTheDimuonPair < 0.275 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair);
                fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3->Fill(ptOfTheDimuonPair);
              } else if ( ptOfTheDimuonPair < 0.950 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.33333333333);
                fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3->Fill(ptOfTheDimuonPair, 0.33333333333);
              } else if ( ptOfTheDimuonPair < 1.400 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.16666666666);
                fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3->Fill(ptOfTheDimuonPair, 0.16666666666);
              } else if ( ptOfTheDimuonPair < 2.000 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.125);
                fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3->Fill(ptOfTheDimuonPair, 0.125);
              } else if ( ptOfTheDimuonPair < 4.000 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.050);
                fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3->Fill(ptOfTheDimuonPair, 0.050);
              } else if ( ptOfTheDimuonPair < 5.000 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.025);
                fDimuonPtDistributionRestrictedRapidity0N0N36to31Hv3->Fill(ptOfTheDimuonPair, 0.025);
              }
            } else if ( (possibleJPsi.Rapidity() > -3.10) && (possibleJPsi.Rapidity() <= -2.60) && (possibleJPsi.Mag() > 2.8) && (possibleJPsi.Mag() < 3.3) ) {
              fDimuonPtDistributionRestrictedRapidity0N0NH       ->Fill(ptOfTheDimuonPair);
              fDimuonPtDistributionRestrictedRapidity0N0N31to26H ->Fill(ptOfTheDimuonPair);
              /* -
               * - Variable pt-binning.
               * -
               */
              if (        ptOfTheDimuonPair < 0.275 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair);
                fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3->Fill(ptOfTheDimuonPair);
              } else if ( ptOfTheDimuonPair < 0.950 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.33333333333);
                fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3->Fill(ptOfTheDimuonPair, 0.33333333333);
              } else if ( ptOfTheDimuonPair < 1.400 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.16666666666);
                fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3->Fill(ptOfTheDimuonPair, 0.16666666666);
              } else if ( ptOfTheDimuonPair < 2.000 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.125);
                fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3->Fill(ptOfTheDimuonPair, 0.125);
              } else if ( ptOfTheDimuonPair < 4.000 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.050);
                fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3->Fill(ptOfTheDimuonPair, 0.050);
              } else if ( ptOfTheDimuonPair < 5.000 ) {
                fDimuonPtDistributionRestrictedRapidity0N0NHv3      ->Fill(ptOfTheDimuonPair, 0.025);
                fDimuonPtDistributionRestrictedRapidity0N0N31to26Hv3->Fill(ptOfTheDimuonPair, 0.025);
              }
            }

        }
  }



  /* -
     - Now we are ordering the muons. The first muon will always be positive.
     - This is useful for the histograms...
   */
  TLorentzVector muonsCopy[2];
  TLorentzVector muonsCopy2[2];
  TLorentzVector possibleJPsiCopy;
  if( chargeOfMuons[0] > 0 ){
    muonsCopy[0]     = muons[0];
    muonsCopy[1]     = muons[1];
  } else if( chargeOfMuons[0] < 0 ){
    muonsCopy[0]     = muons[1];
    muonsCopy[1]     = muons[0];
  }
  muonsCopy2[0] = muonsCopy[0];
  muonsCopy2[1] = muonsCopy[1];
  possibleJPsiCopy = possibleJPsi;
  /* - If we are in the J/Psi peak, hence 2.8 < M < 3.3 GeV/c, AND if we are
     - in the coherent regime, so if the Pt < 0.25 GeV/c, we fill the plots.
     -
     - In the following note that the rapidity is well computed, so we are
     - dealing with negative values... -4.0 < Y < -2.5 !!!
     -
   */
  Double_t possibleJPsiCopyMag =possibleJPsiCopy.Mag();





  // post the data
  PostData(1, fOutputList);
}
//_____________________________________________________________________________
Int_t AliAnalysisTaskUPCforwardpPb::MuonTagCellVZEROC(Double_t ItsEta, Double_t ItsPhi)
{
  // coverage in eta of v0c
  // -3.7,-3.2,-2.7,-2.2,-1.7 for ring 0, 1, 2, 3 and 4, respectively

  Int_t i_eta = -1;
  Int_t idx   = -1;
  if      ( ItsEta>-3.7 && ItsEta<-3.2) i_eta = 0;
  else if ( ItsEta>-3.2 && ItsEta<-2.7) i_eta = 1;
  else if ( ItsEta>-2.7 && ItsEta<-2.2) i_eta = 2;
  else if ( ItsEta>-2.2 && ItsEta<-1.7) i_eta = 3;

  if (i_eta> -1) {
    Int_t i_phi = (Int_t) ((4.0*ItsPhi/TMath::Pi()));
    idx = i_eta*8+i_phi;
  }

  return idx;
}
//_____________________________________________________________________________
void AliAnalysisTaskUPCforwardpPb::Terminate(Option_t *)
{
    cout << endl;
    // terminate
    // called at the END of the analysis (when all events are processed)
}
//_____________________________________________________________________________
