#ifndef SYNCHRONIZER_HPP
#define SYNCHRONIZER_HPP

#include <vector>
#include <assert.h>
#include <map>
#include <stdio.h>
#include <boost/format.hpp>

#include "BoostedTTH/BoostedAnalyzer/interface/InputCollections.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/Cutflow.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BoostedUtils.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/FilterSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/LeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMassSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonMETSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/JetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/DiLeptonJetTagSelection.hpp"
#include "BoostedTTH/BoostedAnalyzer/interface/BDT_v3.hpp"
#include "MiniAOD/MiniAODHelper/interface/MiniAODHelper.h"
#include "MiniAOD/MiniAODHelper/interface/TopTagger.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

class Synchronizer{

public:
    Synchronizer(const edm::ParameterSet& iConfig,edm::ConsumesCollector && iC);
    ~Synchronizer ();
    void DumpSyncExe(const std::vector<InputCollections>& inputs, bool dumpExtended, std::vector<int> dumpAlwaysEvents);
    void Init(std::string filename, const std::vector<std::string>& jetSystematics,const edm::ParameterSet& iConfig,MiniAODHelper* helper_,bool dumpExtended);
    void DumpSyncExeHeader(std::ostream &out, bool dumpExtended=false);


private:
    void DumpSyncExe(const InputCollections& input,std::ostream &out,Cutflow& cutflowSL,Cutflow& cutflowDL, bool dumpExtended,  std::vector<int> dumpAlwaysEvents);
    vector<ofstream*> cutflowFilesDL;
    vector<ofstream*> cutflowFilesSL;
    vector<ofstream*> dumpFiles;
    vector<Selection*> selectionsSL;
    vector<Selection*> selectionsDL;
    std::vector<Cutflow> cutflowsDL;
    std::vector<Cutflow> cutflowsSL;
    std::vector<std::string> systematics;

    MiniAODHelper* helper;

    bool initializedCutflowsWithSelections;
    std::string dataset;

    edm::EDGetTokenT< std::vector<pat::Electron> > rawElToken;
    edm::EDGetTokenT< std::vector<pat::Muon> > rawMuToken;

    bool isData;

};


#endif
