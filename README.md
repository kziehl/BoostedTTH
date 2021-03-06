BoostedTTH
=======
CMSSW tools for analyzing TTH events with boosted objects

[![Build Status](https://mharrend.web.cern.ch/buildStatus/icon?job=cms-ttH/BoostedTTH/CMSSW_8_0_26_patch1)](https://mharrend.web.cern.ch/job/cms-ttH/job/BoostedTTH/job/CMSSW_8_0_26_patch1/)

## Installation
Follow These Steps:

    # setup environment
    export SCRAM_ARCH="slc6_amd64_gcc530"
    export CMSSW_VERSION="CMSSW_8_0_26_patch1"
    scram project $CMSSW_VERSION
    cd $CMSSW_VERSION/src
    export CMSSW_SRC="$( pwd )"
    cmsenv
    
    # updated MET tools
    # this topic is branched from the official cms-met:METRecipe_8020 but fixes the badGlobalMuonTagger
    # so that it works like any other MET filter module
    git cms-merge-topic riga:badGlobalMuonTagger_fix

    # EGMSmearer and data
    git cms-merge-topic shervin86:Moriond2017_JEC_energyScales
    cd EgammaAnalysis/ElectronTools/data
    git clone --depth 1 https://github.com/ECALELFS/ScalesSmearings.git
    cd ../../..

    # ttHFGenFilter
    # (only required when you use the ttHF filtered ttJets dataset)
    #git cms-merge-topic riga:ttHFGenFilter_tagging
 
    # bjetness code
    git clone --depth 1 https://github.com/IHEP-CMS/BJetnessTTHbb.git
    cd BJetnessTTHbb/BJetness
    mkdir data
    cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JEC/ data/
    cp -r /afs/cern.ch/work/f/fromeo/public/BJetnessTTHbb/JER/ data/
    cd -
    
    # install common classifier
    mkdir TTH
    cd TTH
    git clone --depth 1 https://gitlab.cern.ch/ttH/CommonClassifier.git
    source CommonClassifier/setup/install_mem.sh
    # use recent version of LHAPDF header
    sed -i '6i#include "LHAPDF/LHAPDF.h"' MEIntegratorStandalone/interface/Integrand.h
    sed -i '32i /*' MEIntegratorStandalone/interface/Integrand.h
    sed -i '44i */' MEIntegratorStandalone/interface/Integrand.h
    
    # install miniaod and boostedtth
    cd $CMSSW_BASE/src
    git clone  -b 'Spring17_v2' --single-branch --depth 1 https://github.com/cms-ttH/MiniAOD.git
    git clone --depth 1 -b CMSSW_8_0_26_patch1 https://github.com/cms-ttH/BoostedTTH.git
    
    # Download the JER correction files
    cd $CMSSW_BASE/src/BoostedTTH/BoostedAnalyzer/data
    mkdir jerfiles
    cd jerfiles
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_PtResolution_AK4PFchs.txt"
    wget "https://raw.githubusercontent.com/cms-jet/JRDatabase/master/textFiles/Spring16_25nsV10_MC/Spring16_25nsV10_MC_SF_AK4PFchs.txt"
    cd $CMSSW_BASE/src
    
    # hack to deactivate random JER smearing
    sed -i '248,259d' PhysicsTools/PatUtils/interface/SmearedJetProducerT.h
    
    #compile
    scram b -j10
    
## Overview
BoostedObjects contains the classes needed for subjet-analysis. They associate fat jets with the corresponding filtered objects.

BoostedProduces contains the tools used to run the HEPTopTagger and SubjetFilterJet algorithm on MiniAOD and add the output as the above collections.

BoostedAnalyzer can be used to analyze MiniAOD files. The plugin itself takes care of objectselections and stores the objects in InputCollections. Different event selection can be used in this step, too. The inputcollections can be analyzed with a TreeWriter that can load different Processors. Every processor writes a certain class of output variables in a flat TTree.
