import FWCore.ParameterSet.Config as cms
from BoostedTTH.BoostedAnalyzer.Selection_cff import *

BoostedAnalyzer = cms.EDAnalyzer(
    'BoostedAnalyzer',
    LeptonSelectionData, # defined in Selection_cff
    DiLeptonSelectionData, # defined in Selection_cff
    JetTagSelection, # defined in Selection_cff
    METSelection, # defined in Selection_cff
    checkBasicDataTriggers, # defined in Selection_cff

    era = cms.string("2015_74x"), # has little effect so far, might become important for MiniAODhelper
    analysisType = cms.string("LJ"), # has little effect so far, might become important for MiniAODhelper
    sampleID = cms.int32(9125), # has little effect so far, might become important for MiniAODhelper

    eventWeight = cms.double(1.),
    isData = cms.bool(True),

    recorrectMET = cms.bool(True),

    makeSystematicsTrees = cms.bool(False),
    doJERsystematic = cms.bool(False),
    generatorName = cms.string("notSpecified"),

    useFatJets = cms.bool(True),
    useForwardJets = cms.bool(False),
    useGenHadronMatch = cms.bool(False),

    dumpSyncExe = cms.bool(False),
    dumpSyncExe2 = cms.bool(False),

    doBoostedMEM = cms.bool(False),

    minJetsForMEM = cms.int32(4),
    minTagsForMEM = cms.int32(3),

    selectionNames = cms.vstring("VertexSelection","LeptonSelection","JetTagSelection"),
    processorNames = cms.vstring("WeightProcessor","TriggerVarProcessor","AdditionalJetProcessor","SpinCorrelationProcessor","BasicVarProcessor"),

    outfileName = cms.string("BoostedTTH"),
)
