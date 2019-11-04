#!/bin/bash

ROOTfile=$1

echo "OK0"
echo $ROOTfile
#aliroot -b -l -q fitZNC.cpp($ROOTfile)


#before I had always used aliroot -b -l -q , but it doesn't seem to work...
# aliroot -b -l <<EOF
# .L fitRootConverted/fitZNCkaedenRoofitPlot.cpp
# fitZNC("$ROOTfile");
# EOF
#
# echo "OK1"
#
# aliroot -b -l <<EOF
# .L fitRootConverted/fitZNAkaedenRoofitPlot.cpp
# fitZNA("$ROOTfile");
# EOF
#
# echo "OK2"

# aliroot -b -l <<EOF
# TFile* fileSyst = new TFile("pngResults/Systematics.root", "recreate");
# TH1F* Systematics = new TH1F("Systematics", "Systematics", 1000, -0.5, 999.5);
# TH1F* Errors = new TH1F("Errors", "Errors", 1000, -0.5, 999.5);
# Systematics->Fill(0);
# Errors->Fill(0);
# Systematics->Write(Systematics->GetName(), TObject::kOverwrite);
# Errors->Write(Errors->GetName(), TObject::kOverwrite);
# fileSyst->Close();
# EOF
#
# echo "REGENERATED Systematics.root"
#
# aliroot -b -l <<EOF
# TFile* fileSyst = new TFile("pngResults/SystematicsHalfBin.root", "recreate");
# TH1F* Systematics = new TH1F("Systematics", "Systematics", 1000, -0.5, 999.5);
# TH1F* Errors = new TH1F("Errors", "Errors", 1000, -0.5, 999.5);
# Systematics->Fill(0);
# Errors->Fill(0);
# Systematics->Write(Systematics->GetName(), TObject::kOverwrite);
# Errors->Write(Errors->GetName(), TObject::kOverwrite);
# fileSyst->Close();
# EOF
#
# echo "REGENERATED SystematicsHalfBin.root"
#
# aliroot -b -l <<EOF
# TFile* fileSyst = new TFile("pngResults/SystematicsHalfHalfBin.root", "recreate");
# TH1F* Systematics = new TH1F("Systematics", "Systematics", 1000, -0.5, 999.5);
# TH1F* Errors = new TH1F("Errors", "Errors", 1000, -0.5, 999.5);
# Systematics->Fill(0);
# Errors->Fill(0);
# Systematics->Write(Systematics->GetName(), TObject::kOverwrite);
# Errors->Write(Errors->GetName(), TObject::kOverwrite);
# fileSyst->Close();
# EOF
#
# echo "REGENERATED SystematicsHalfHalfBin.root"

aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBall.cpp
fitJPsiTemplate("$ROOTfile",0,0);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root

for value2 in {0..1}
do
aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBall.cpp
fitJPsiTemplate("$ROOTfile",1,$value2);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root
done

for value2 in {0..2}
do
aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBall.cpp
fitJPsiTemplate("$ROOTfile",2,$value2);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root
done




aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBall0N0N.cpp
fitJPsiTemplate("$ROOTfile",0,0);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root

for value2 in {0..1}
do
aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBall0N0N.cpp
fitJPsiTemplate("$ROOTfile",1,$value2);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root
done

for value2 in {0..2}
do
aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBall0N0N.cpp
fitJPsiTemplate("$ROOTfile",2,$value2);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root
done



aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBallSmall0N0N.cpp
fitJPsiTemplate("$ROOTfile",0,0);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root

for value2 in {0..1}
do
aliroot -b -l <<EOF
.L fitRootConverted/fitJPsiCrystalBallSmall0N0N.cpp
fitJPsiTemplate("$ROOTfile",1,$value2);
EOF
# rm pngResults/Systematics.root
# mv pngResults/Systematics2.root pngResults/Systematics.root
done


# for value in {1..10}
# do
# for value2 in {0..4}
# do
# aliroot -b -l <<EOF
# .L fitRootConverted/fitJPsiCrystalBallSystematicsHalfBin.cpp
# fitJPsiTemplate("$ROOTfile",$value,$value2);
# EOF
# rm pngResults/SystematicsHalfBin.root
# mv pngResults/SystematicsHalfBin2.root pngResults/SystematicsHalfBin.root
# done
# done
#
# for value in {1..10}
# do
# for value2 in {0..4}
# do
# aliroot -b -l <<EOF
# .L fitRootConverted/fitJPsiCrystalBallSystematicsHalfHalfBin.cpp
# fitJPsiTemplate("$ROOTfile",$value,$value2);
# EOF
# rm pngResults/SystematicsHalfHalfBin.root
# mv pngResults/SystematicsHalfHalfBin2.root pngResults/SystematicsHalfHalfBin.root
# done
# done
#
# for value in {0..4}
# do
# aliroot -b -l <<EOF
# .L fitRootConverted/fitPtDistr0.cpp
# fitPtDistr("$ROOTfile",$value);
# EOF
# done
#
# for value in {0..4}
# do
# aliroot -b -l <<EOF
# .L fitRootConverted/fitPtDistrShift.cpp
# fitPtDistr("$ROOTfile",$value);
# EOF
# done


# for value in {0..7}
# do
# aliroot -b -l <<EOF
# .L fitRootConverted/fitXNXNTemplate.cpp
# fitJPsiTemplate("$ROOTfile", $value);
# EOF
# done


if [ -d "pngResults/$(date +%F)" ]; then rm -rf pngResults/$(date +%F); fi
mkdir -p pngResults/$(date +%F)
mkdir -p pngResults/$(date +%F)/FitInvMass
mkdir -p pngResults/$(date +%F)/FitInvMass0N0N
mkdir -p pngResults/$(date +%F)/FitInvMass0N0Nsmall
# mkdir -p pngResults/$(date +%F)/FitInvMassHalfBin
# mkdir -p pngResults/$(date +%F)/FitInvMassHalfHalfBin

mv pngResults/InvMassSystematics_0_*              pngResults/$(date +%F)/FitInvMass
mv pngResults/InvMassSystematics_1_*              pngResults/$(date +%F)/FitInvMass
mv pngResults/InvMassSystematics_2_*              pngResults/$(date +%F)/FitInvMass
mv pngResults/InvMassSystematics0N0N_0_*          pngResults/$(date +%F)/FitInvMass0N0N
mv pngResults/InvMassSystematics0N0N_1_*          pngResults/$(date +%F)/FitInvMass0N0N
mv pngResults/InvMassSystematics0N0N_2_*          pngResults/$(date +%F)/FitInvMass0N0N
mv pngResults/InvMassSystematics0N0Nsmall_0_*     pngResults/$(date +%F)/FitInvMass0N0Nsmall
mv pngResults/InvMassSystematics0N0Nsmall_1_*     pngResults/$(date +%F)/FitInvMass0N0Nsmall
# mv pngResults/fitPtDistrALL*                      pngResults/$(date +%F)/FitInvMass
# mv pngResults/InvMassSystematicsHalfBin_1_*       pngResults/$(date +%F)/FitInvMassHalfBin
# mv pngResults/InvMassSystematicsHalfBin_2_*       pngResults/$(date +%F)/FitInvMassHalfBin
# mv pngResults/InvMassSystematicsHalfHalfBin_1_*   pngResults/$(date +%F)/FitInvMassHalfHalfBin
# mv pngResults/InvMassSystematicsHalfHalfBin_2_*   pngResults/$(date +%F)/FitInvMassHalfHalfBin
# mv pngResults/Systematics.root                    pngResults/$(date +%F)/XNXN
# mv pngResults/SystematicsHalfBin.root             pngResults/$(date +%F)/XNXNhalfBin
# mv pngResults/SystematicsHalfHalfBin.root         pngResults/$(date +%F)/XNXNhalfHalfBin
