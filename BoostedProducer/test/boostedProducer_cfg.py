import FWCore.ParameterSet.Config as cms
# input
process = cms.Process("p")
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('file:/pnfs/desy.de/cms/tier2/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/00000/0AB045B5-BB0C-E511-81FD-0025905A60B8.root')
)
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

# messages
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.suppressWarning = cms.untracked.vstring('ecalLaserCorrFilter','manystripclus53X','toomanystripclus53X')
process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(False) )
process.options.allowUnscheduled = cms.untracked.bool(True)

# select loose lepton collections
process.selectedMuons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedMuons"), cut = cms.string('''abs(eta)<2.5 && pt>10. &&
(pfIsolationR03().sumChargedHadronPt+
max(0.,pfIsolationR03().sumNeutralHadronEt+
pfIsolationR03().sumPhotonEt-
0.50*pfIsolationR03().sumPUPt))/pt < 0.20 &&
(isPFMuon && (isGlobalMuon || isTrackerMuon) )'''))
process.selectedElectrons = cms.EDFilter("CandPtrSelector", src = cms.InputTag("slimmedElectrons"), cut = cms.string('''abs(eta)<2.5 && pt>20. &&
gsfTrack.isAvailable() &&
gsfTrack.hitPattern().numberOfLostHits(\'MISSING_INNER_HITS\') < 2 &&
(pfIsolationVariables().sumChargedHadronPt+
max(0.,pfIsolationVariables().sumNeutralHadronEt+
pfIsolationVariables().sumPhotonEt-
0.5*pfIsolationVariables().sumPUPt))/pt < 0.15'''))

#do projections
process.pfCHS = cms.EDFilter("CandPtrSelector", src = cms.InputTag("packedPFCandidates"), cut = cms.string("fromPV"))
process.pfNoMuonCHS =  cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfCHS"), veto = cms.InputTag("selectedMuons"))
process.pfNoElectronsCHS = cms.EDProducer("CandPtrProjector", src = cms.InputTag("pfNoMuonCHS"), veto =  cms.InputTag("selectedElectrons"))

# make patJets
process.load("PhysicsTools.PatAlgos.producersLayer1.patCandidates_cff")
process.load("Configuration.EventContent.EventContent_cff")
process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_mc')

# make HTT Top Jets
process.load('BoostedTTH.BoostedProducer.HTTTopJetProducer_cfi')

# make Subjet Filterjet Jets
process.load('BoostedTTH.BoostedProducer.SFJetProducer_cfi')

# make PAT HTT Top Jets
from PhysicsTools.PatAlgos.tools.jetTools import addJetCollection

# HTT fatjet
addJetCollection(
    process,
    labelName = 'HTTFatJetsPF',
    postfix="",
    #jetSource = cms.InputTag('HTTTopJetProducer','fatjets'),
    jetSource = cms.InputTag('HTTFatJetProducer',''),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = None
)

# HTT topjet
addJetCollection(
    process,
    labelName = 'HTTTopJetsPF',
    postfix="",
    jetSource = cms.InputTag('HTTTopJetProducer',''),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = None
)

# 3 HTT subjets
addJetCollection(
    process,
    labelName = 'HTTSubjetsPF',
    postfix="",
    jetSource = cms.InputTag('HTTTopJetProducer','subjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    algo = 'CA',
    rParam = 1.5,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags' ]
)

# make PAT Subjet Filterjet Jets
# add fat CA1.2 pat jet
addJetCollection(
    process,
    labelName = 'SFFatJetsPF',
    postfix = "",
    jetSource = cms.InputTag('SFJetProducer','fatjets'),
    algo = 'CA',
    rParam = 1.2,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = None
)
# the two subjets that created the mass drop
addJetCollection(
    process,
    labelName = 'SFSubjetsPF',
    postfix = "",
    jetSource = cms.InputTag('SFJetProducer','subjets'),
    algo = 'CA',
    rParam = 1.2,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = None
)
# filterjets (reclustered from subjets)
addJetCollection(
    process,
    labelName = 'SFFilterjetsPF',
    postfix = "",
    jetSource = cms.InputTag('SFJetProducer','filterjets'),
    pfCandidates = cms.InputTag('packedPFCandidates'),
    pvSource = cms.InputTag('offlineSlimmedPrimaryVertices'),
    svSource = cms.InputTag('slimmedSecondaryVertices'),
    algo = 'CA',
    rParam = 0.3,
    getJetMCFlavour = False,
    genJetCollection = None,
    jetCorrections = None,
    btagDiscriminators = [ 'pfCombinedInclusiveSecondaryVertexV2BJetTags' ]
)


#adjust MC matching for all Boosted Jet collections
#HTT Top Jet collections
# fatjets
process.patJetsHTTFatJetsPF.addGenJetMatch=False
process.patJetPartonMatchHTTFatJetsPF.matched = "prunedGenParticles"
# topjets
process.patJetsHTTTopJetsPF.addGenJetMatch=False
process.patJetPartonMatchHTTTopJetsPF.matched = "prunedGenParticles"
# subjets
process.patJetsHTTSubjetsPF.addGenJetMatch=False
process.patJetPartonMatchHTTSubjetsPF.matched = "prunedGenParticles"

#Subjet Filterjet Jet collections
# fatjets
process.patJetsSFFatJetsPF.addGenJetMatch=False
process.patJetPartonMatchSFFatJetsPF.matched = "prunedGenParticles"
# subjets
process.patJetsSFSubjetsPF.addGenJetMatch=False
process.patJetPartonMatchSFSubjetsPF.matched = "prunedGenParticles"
# filterjets
process.patJetsSFFilterjetsPF.addGenJetMatch=False
process.patJetPartonMatchSFFilterjetsPF.matched = "prunedGenParticles"

# all
process.patJetPartons.particles = "prunedGenParticles"


# create Path for PAT Jets
process.patJetsHTTTopJetsPath = cms.Path(process.patJetsHTTFatJetsPF * process.patJetsHTTTopJetsPF * process.patJetsHTTSubjetsPF)
process.patJetsSFJetsPath = cms.Path(process.patJetsSFFatJetsPF * process.patJetsSFSubjetsPF * process.patJetsSFFilterjetsPF)

#from RecoJets.JetProducers.ak4PFJets_cfi import ak4PFJets
from RecoJets.JetProducers.ak4GenJets_cfi import ak4GenJets
#process.ak4PFJetsCHS = ak4PFJets.clone(src = 'pfNoElectronsCHS', doAreaFastjet = True)
process.ak4GenJets = ak4GenJets.clone(src = 'packedGenParticles')

# match HTT Top Jet subjets to fat jet
process.load('BoostedTTH.BoostedProducer.HTTTopJetMatcher_cfi')
# match Subjet Filterjet Jet subjets to fat jet
process.load('BoostedTTH.BoostedProducer.SFJetMatcher_cfi')

# gen hadron matching for tt+X categorization
process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.load("BoostedTTH.BoostedProducer.genHadronMatching_cfi")

process.OUT = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('BoostedTTH_MiniAOD.root'),
    outputCommands = cms.untracked.vstring(['drop *','keep *_*_*_PAT','keep *_*_*_RECO','keep *_*_*_HLT','keep *_*_*_SIM','keep *_*_*_LHE','keep *_*HTTTopJetMatcher*_*_*','keep *_*SFJetMatcher*_*_*','keep *_matchGen*Hadron_*_*', 'keep *_ak4GenJetsCustom_*_*', 'keep *_categorizeGenTtbar_*_*'])
)

process.endpath = cms.EndPath(process.OUT)

