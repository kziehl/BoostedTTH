#include "BoostedTTH/BoostedAnalyzer/interface/RegressionVarProcessor.hpp"

using namespace std;

RegressionVarProcessor::RegressionVarProcessor(edm::ConsumesCollector && iC, std::vector<edm::InputTag> regJetCollections){

    //TODO: This only works if the collections are the systematic shifted Collections --> Think about something
    //when using multiple collections
    for(auto &tag : regJetCollections){
        regressedJetsTokens.push_back(iC.consumes< std::vector<pat::Jet> >(tag));
    }
    genJetswNuToken = iC.consumes< std::vector<reco::GenJet> >(edm::InputTag("ak4GenJetsCustomwNu","",""));
}
RegressionVarProcessor::~RegressionVarProcessor(){}


void RegressionVarProcessor::Init(const InputCollections& input,VariableContainer& vars){

    //Matched GenJet variabels
    //vars.InitVars( "Jet_MatchedGenJetwNuPt","N_Jets" );
    //vars.InitVars( "LooseJet_MatchedGenJetwNuPt","N_LooseJets" );

    //Vertex variables
    vars.InitVars( "Jet_vtxMass","N_Jets" );
    vars.InitVars( "Jet_vtx3DVal","N_Jets" );
    vars.InitVars( "Jet_vtxNtracks","N_Jets" );
    vars.InitVars( "Jet_vtx3DSig","N_Jets" );
    vars.InitVars( "Jet_vtxPt","N_Jets" );

    //Fraction variables
    vars.InitVars( "Jet_nHEFrac","N_Jets" );
    vars.InitVars( "Jet_cHEFrac","N_Jets" );
    vars.InitVars( "Jet_totHEFrac","N_Jets" );
    vars.InitVars( "Jet_nEmEFrac","N_Jets" );

    vars.InitVar( "N_RegJets", "I");

    vars.InitVars( "RegJet_E", "N_RegJets");
    vars.InitVars( "RegJet_M", "N_RegJets");
    vars.InitVars( "RegJet_Mt", "N_RegJets");
    vars.InitVars( "RegJet_Pt", "N_RegJets");
    vars.InitVars( "RegJet_rawPt", "N_RegJets");
    vars.InitVars( "RegJet_Eta", "N_RegJets");
    vars.InitVars( "RegJet_Phi", "N_RegJets");
    vars.InitVars( "RegJet_CSV", "N_RegJets");
    vars.InitVars( "RegJet_Flav", "N_RegJets");
    vars.InitVars( "RegJet_PartonFlav", "N_RegJets");
    vars.InitVars( "RegJet_Charge", "N_RegJets");
    vars.InitVars( "RegJet_PileUpID", "N_RegJets");

    vars.InitVars( "RegJet_helperJES", "N_RegJets");
    vars.InitVars( "RegJet_helperJESUp", "N_RegJets");
    vars.InitVars( "RegJet_helperJESDown", "N_RegJets");
    //Regression specific variables for regressedJets
    //Regression target
    vars.InitVars( "RegJet_MatchedGenJetwNuPt", "N_RegJets");

    //Vertex variables
    vars.InitVars( "RegJet_vtxMass", "N_RegJets");
    vars.InitVars( "RegJet_vtx3DVal", "N_RegJets");
    vars.InitVars( "RegJet_vtxNtracks", "N_RegJets");
    vars.InitVars( "RegJet_vtx3DSig", "N_RegJets");
    vars.InitVars( "RegJet_vtxPt", "N_RegJets");

    //Fraction variables
    vars.InitVars( "RegJet_nHEFrac", "N_RegJets");
    vars.InitVars( "RegJet_cHEFrac", "N_RegJets");
    vars.InitVars( "RegJet_nEmEFrac", "N_RegJets");
    vars.InitVars( "RegJet_totHEFrac", "N_RegJets");


    vars.InitVars( "RegJet_chargedMult", "N_RegJets");
    vars.InitVars( "RegJet_leadTrackPt", "N_RegJets");

    //Corrections
    vars.InitVars( "RegJet_corr", "N_RegJets");


    //Letpon variables
    vars.InitVars( "RegJet_leptonPtRel", "N_RegJets");
    vars.InitVars( "RegJet_leptonPt", "N_RegJets");
    vars.InitVars( "RegJet_leptonEta", "N_RegJets");
    vars.InitVars( "RegJet_leptonDeltaR", "N_RegJets");
    vars.InitVars( "RegJet_NmatchedsoftLeptons", "N_RegJets");
    vars.InitVars( "RegJet_NmatchedsoftElectrons", "N_RegJets");
    vars.InitVars( "RegJet_NmatchedsoftMuons", "N_RegJets");

    //Regression Results
    vars.InitVars( "RegJet_regcorr", "N_RegJets");
    vars.InitVars( "RegJet_preregPt", "N_RegJets");
    vars.InitVars( "RegJet_preregMt", "N_RegJets");


    vars.InitVar( "Evt_Reg_blr_ETH" );
    vars.InitVar( "Evt_Reg_blr_ETH_transformed" );
    vars.InitVar( "Evt_Reg_M_Total" );
    vars.InitVar( "Evt_Reg_H0" );
    vars.InitVar( "Evt_Reg_H1" );
    vars.InitVar( "Evt_Reg_H2" );
    vars.InitVar( "Evt_Reg_H3" );
    vars.InitVar( "Evt_Reg_H4" );

  
      
    vars.InitVar( "Evt_Reg_M_MinDeltaRJets" );
    vars.InitVar( "Evt_Reg_M_MinDeltaRTaggedJets" );
    vars.InitVar( "Evt_Reg_M_MinDeltaRUntaggedJets" );
    vars.InitVar( "Evt_Reg_M_MinDeltaRLeptonTaggedJet" );
    vars.InitVar( "Evt_Reg_M_MinDeltaRLeptonJet" );
    
    vars.InitVar( "Evt_Reg_Dr_MinDeltaRJets" );
    vars.InitVar( "Evt_Reg_Dr_MinDeltaRTaggedJets" );
    vars.InitVar( "Evt_Reg_Dr_MinDeltaRUntaggedJets" );
    vars.InitVar( "Evt_Reg_Dr_MinDeltaRLeptonTaggedJet" );
    vars.InitVar( "Evt_Reg_Dr_MinDeltaRLeptonJet" );
    
    vars.InitVar( "Evt_Reg_Pt_MinDeltaRJets" );
    vars.InitVar( "Evt_Reg_Pt_MinDeltaRTaggedJets" );
    vars.InitVar( "Evt_Reg_Pt_MinDeltaRUntaggedJets" );


}


void RegressionVarProcessor::Process(const InputCollections& input, VariableContainer& vars) {

    //Get Regressed Jets for current systematics
    edm::Handle < std::vector< pat::Jet > > h_regressedJets;
    input.iEvent.getByToken( regressedJetsTokens[input.isys], h_regressedJets );
    std::vector<pat::Jet> const &regressedJets = *h_regressedJets;
    /*
    edm::Handle< std::vector< reco::GenJet > > h_genjetswNu;
    std::vector< reco::GenJet > genJetswNu;
    if(input.sampleType != SampleType::data){
      input.iEvent.getByToken( genJetswNuToken, h_genjetswNu );
      std::vector< reco::GenJet > const &genjetswNu = *h_genjetswNu;
      for( size_t i = 0 ; i < genjetswNu.size() ; i++ ){
        if( genjetswNu[i].pt() > 15 && fabs( genjetswNu[i].eta()) < 2.4 ){
  	        genJetswNu.push_back(genjetswNu[i]);
        }
      }
    }

    GenJetMatcher matcher;
    map<const pat::Jet* , reco::GenJet* > matches;
    matcher.init( 0.4 );

    matches = matcher.match( input.selectedJetsLoose, genJetswNu);
    size_t iloosejet = 0;
    for(auto& LooseJet: input.selectedJetsLoose ){
        int iJet = iloosejet;
        if ( matches.find(&LooseJet) != matches.end() ){
            vars.FillVars( "LooseJet_MatchedGenJetwNuPt",iJet,matches[&LooseJet]->pt() );
        }
        else {
            vars.FillVars( "LooseJet_MatchedGenJetwNuPt",iJet, -1.0 );
        }
        iloosejet++;
    }
*/
    /*
    matcher.resetMaps();
    matches = matcher.match( input.selectedJets, genJetswNu );
    */
    size_t ijet = 0;
    for(auto& Jet: input.selectedJets ){
        int iJet = ijet;
        /*
        if ( matches.find(&Jet) != matches.end() ){
            vars.FillVars( "Jet_MatchedGenJetwNuPt",iJet,matches[&Jet]->pt() );
        }
        else {
            vars.FillVars( "Jet_MatchedGenJetwNuPt",iJet, -1.0 );
        }
*/
        vars.FillVars( "Jet_vtxMass",iJet,Jet.userFloat("vtxMass") );
        vars.FillVars( "Jet_vtx3DVal",iJet,Jet.userFloat("vtx3DVal") );
        vars.FillVars( "Jet_vtxNtracks",iJet,Jet.userFloat("vtxNtracks") );
        vars.FillVars( "Jet_vtx3DSig",iJet,Jet.userFloat("vtx3DSig") );
        vars.FillVars( "Jet_vtxPt",iJet,sqrt( Jet.userFloat("vtxPx")*Jet.userFloat("vtxPx") +
                                              Jet.userFloat("vtxPy")*Jet.userFloat("vtxPy") ) );


        //Fraction variables
        /** This Code can be used, when Jetcorrections are not applied "on the fly" anymore **/
        /*
        vars.FillVars( "Jet_nHEFrac",iJet, itJet.neutralHadronEnergyFraction() );
        vars.FillVars( "Jet_cHEFrac",iJet, itJet.chargedHadronEnergyFraction() );



        if (  ( itJet.neutralHadronEnergyFraction() + itJet.neutralEmEnergyFraction() ) >= 1  ){
        vars.FillVars( "Jet_totHEFrac",iJet, 1);
        }
        else {
        vars.FillVars( "Jet_totHEFrac",iJet, itJet.neutralHadronEnergyFraction() + itJet.chargedHadronEnergyFraction() );
        }
        vars.FillVars( "Jet_nEmEFrac",iJet, itJet.neutralEmEnergyFraction() );
        */

        /** This code has to be used as long as correction are applied "on the fly" **/
        vars.FillVars( "Jet_nHEFrac", iJet,  Jet.userFloat("idJetnhadEfrac"));
        vars.FillVars( "Jet_cHEFrac", iJet, Jet.userFloat("idJetchhadEfrac"));
        vars.FillVars( "Jet_nEmEFrac", iJet, Jet.userFloat("idJetnemEfrac"));


        double idtotHEFrac = ( Jet.userFloat("idJetnhadEfrac") + Jet.userFloat("idJetchhadEfrac") ) ;
        if ( idtotHEFrac >= 1  ){
        vars.FillVars( "Jet_totHEFrac",iJet, 1);
        }
        else {
        vars.FillVars( "Jet_totHEFrac",iJet, idtotHEFrac );
        }
        ijet++;
    }
    /*
    matcher.resetMaps();
    matches = matcher.match( regressedJets, genJetswNu );*/


    vars.FillVar( "N_RegJets", regressedJets.size() );
    size_t iregjet = 0;
    for (auto& Jet: regressedJets ){
        int iJet = iregjet;

        const char* btagger="pfCombinedInclusiveSecondaryVertexV2BJetTags";
        //Basic Vars for regressed Jets
        vars.FillVars( "RegJet_E",iJet,Jet.energy() );
        vars.FillVars( "RegJet_M",iJet,Jet.mass() );
        vars.FillVars( "RegJet_Mt",iJet,Jet.mt() );
        vars.FillVars( "RegJet_Pt",iJet,Jet.pt() );
        vars.FillVars( "RegJet_rawPt",iJet,Jet.userFloat("rawJetPt") );
        vars.FillVars( "RegJet_Eta",iJet,Jet.eta() );
        vars.FillVars( "RegJet_Phi",iJet,Jet.phi() );
        vars.FillVars( "RegJet_CSV",iJet,MiniAODHelper::GetJetCSV(Jet,btagger) );
        vars.FillVars( "RegJet_Flav",iJet,Jet.hadronFlavour() );
        vars.FillVars( "RegJet_PartonFlav",iJet,Jet.partonFlavour() );
        vars.FillVars( "RegJet_Charge",iJet,Jet.jetCharge() );
        vars.FillVars( "RegJet_PileUpID",iJet,Jet.userFloat("pileupJetId:fullDiscriminant") );

        vars.FillVars( "RegJet_helperJES", iJet, Jet.userFloat("HelperJES") );
        if (Jet.hasUserFloat("HelperJESUp")) { vars.FillVars( "RegJet_helperJESUp", iJet, Jet.userFloat("HelperJESUp") ); }
        if (Jet.hasUserFloat("HelperJESDown")) { vars.FillVars( "RegJet_helperJESDown", iJet, Jet.userFloat("HelperJESDown") ); }


        /*
        //Regression specific variables for regressedJets
        //Regression target
        if ( matches.find(&Jet) != matches.end() ){
            vars.FillVars( "RegJet_MatchedGenJetwNuPt",iJet,matches[&Jet]->pt() );
        }
        else {
            vars.FillVars( "RegJet_MatchedGenJetwNuPt",iJet, -1.0 );
        }
*/
        if ( Jet.hasUserFloat("matchedGenJetwNuPt") ){
            vars.FillVars( "RegJet_MatchedGenJetwNuPt",iJet,Jet.userFloat("matchedGenJetwNuPt") );
        }
        else {
            vars.FillVars( "RegJet_MatchedGenJetwNuPt",iJet, -1.0 );
        }

        //Vertex variables
        vars.FillVars( "RegJet_vtxMass",iJet,Jet.userFloat("vtxMass") );
        vars.FillVars( "RegJet_vtx3DVal",iJet,Jet.userFloat("vtx3DVal") );
        vars.FillVars( "RegJet_vtxNtracks",iJet,Jet.userFloat("vtxNtracks") );
        vars.FillVars( "RegJet_vtx3DSig",iJet,Jet.userFloat("vtx3DSig") );
        vars.FillVars( "RegJet_vtxPt",iJet,sqrt( Jet.userFloat("vtxPx")*Jet.userFloat("vtxPx") +
                                              Jet.userFloat("vtxPy")*Jet.userFloat("vtxPy") ) );


        //Fraction variables
        /** This Code can be used, when Jetcorrections are not applied "on the fly" anymore **/
        /*
        vars.FillVars( "RegJet_nHEFrac",iJet, Jet.neutralHadronEnergyFraction() );
        vars.FillVars( "RegJet_cHEFrac",iJet, Jet.chargedHadronEnergyFraction() );



        if (  ( Jet.neutralHadronEnergyFraction() + Jet.neutralEmEnergyFraction() ) >= 1  ){
        vars.FillVars( "RegJet_totHEFrac",iJet, 1);
        }
        else {
        vars.FillVars( "RegJet_totHEFrac",iJet, Jet.neutralHadronEnergyFraction() + Jet.chargedHadronEnergyFraction() );
        }
        vars.FillVars( "RegJet_nEmEFrac",iJet, Jet.neutralEmEnergyFraction() );
        */

        /** This code has to be used as long as correction are applied "on the fly" **/
        vars.FillVars( "RegJet_nHEFrac", iJet,  Jet.userFloat("idJetnhadEfrac"));
        vars.FillVars( "RegJet_cHEFrac", iJet, Jet.userFloat("idJetchhadEfrac"));
        vars.FillVars( "RegJet_nEmEFrac", iJet, Jet.userFloat("idJetnemEfrac"));


        double idtotHEFrac = ( Jet.userFloat("idJetnhadEfrac") + Jet.userFloat("idJetchhadEfrac") ) ;
        if ( idtotHEFrac >= 1  ){
        vars.FillVars( "RegJet_totHEFrac",iJet, 1);
        }
        else {
        vars.FillVars( "RegJet_totHEFrac",iJet, idtotHEFrac );
        }


        vars.FillVars( "RegJet_chargedMult",iJet, Jet.chargedMultiplicity() );
        vars.FillVars( "RegJet_leadTrackPt",iJet,Jet.userFloat("Jet_leadTrackPt") );


        //Corrections
        /** This Code can be used, when Jetcorrections are not applied "on the fly" anymore **/
        //vars.FillVars( "RegJet_corr",  iJet, 1.0 / (Jet.jecFactor("Uncorrected") / Jet.jecFactor("L3Absolute")) );

        /** This code has to be used as long as correction are applied "on the fly" **/
        vars.FillVars( "RegJet_corr" , iJet, Jet.userFloat("L3Correction"));


        //Letpon variables
        vars.FillVars( "RegJet_leptonPtRel",iJet,Jet.userFloat("Jet_leptonPtRel") );
        vars.FillVars( "RegJet_leptonPt",iJet,Jet.userFloat("Jet_leptonPt") );
        vars.FillVars( "RegJet_leptonEta",iJet,Jet.userFloat("Jet_leptonEta") );
        vars.FillVars( "RegJet_leptonDeltaR",iJet,Jet.userFloat("Jet_leptonDeltaR") );
        vars.FillVars( "RegJet_NmatchedsoftLeptons", iJet, Jet.userFloat("Jet_NmatchsoftLeptons")  );
        vars.FillVars( "RegJet_NmatchedsoftElectrons", iJet, Jet.userFloat("Jet_NmatchsoftElectrons")  );
        vars.FillVars( "RegJet_NmatchedsoftMuons", iJet, Jet.userFloat("Jet_NmatchsoftMuons")  );

        //Regression Results
        if(Jet.hasUserFloat("bregCorrection")){
            vars.FillVars( "RegJet_regcorr", iJet, Jet.userFloat("bregCorrection") );
            vars.FillVars( "RegJet_preregPt", iJet, Jet.pt() / Jet.userFloat("bregCorrection") );
            vars.FillVars( "RegJet_preregMt", iJet, Jet.mt() / Jet.userFloat("bregCorrection") );
        }
        else {
            vars.FillVars( "RegJet_regcorr", iJet, -1.0 );
            vars.FillVars( "RegJet_preregPt", iJet, Jet.pt() );
            vars.FillVars( "RegJet_preregPt", iJet, Jet.mt() );
        }
        iregjet++;
    }


    //Additional Evt variables for 80X BDTs not jet in CommonClassifier
    vector<TLorentzVector> jettvecs;
    vector<double> jetcsvs;
    for(uint i=0; i<regressedJets.size(); i++){
      jettvecs.push_back(BoostedUtils::GetTLorentzVector(regressedJets[i].p4()));
      jetcsvs.push_back(MiniAODHelper::GetJetCSV(regressedJets[i]));
    }
  
    std::vector<unsigned int> out_best_perm;
    double out_P_4b=-1;
    double out_P_2b=-1;
    double eth_blr=-1;
    if(regressedJets.size()>3)
      eth_blr=mem.GetBTagLikelihoodRatio(jettvecs,
					 jetcsvs,
					 out_best_perm,
					 out_P_4b,
					 out_P_2b);

    vars.FillVar("Evt_Reg_blr_ETH",eth_blr);
    vars.FillVar("Evt_Reg_blr_ETH_transformed",log(eth_blr/(1-eth_blr)));


    std::vector<math::XYZTLorentzVector> looseLeptonVecs = BoostedUtils::GetLepVecs(input.selectedElectronsLoose,input.selectedMuonsLoose);
    std::vector<math::XYZTLorentzVector> jetvecs = BoostedUtils::GetJetVecs(regressedJets);
    math::XYZTLorentzVector metvec = input.correctedMET.p4();
    
    
    math::XYZTLorentzVector p4all;
    for(std::vector<math::XYZTLorentzVector>::iterator itJetVec = jetvecs.begin() ; itJetVec != jetvecs.end(); ++itJetVec){
      p4all += *itJetVec;
    }
    for(std::vector<math::XYZTLorentzVector>::iterator itLep = looseLeptonVecs.begin() ; itLep != looseLeptonVecs.end(); ++itLep){
      p4all += *itLep;
    }
    p4all += metvec;
    vars.FillVar("Evt_Reg_M_Total",p4all.M());

    vector<TLorentzVector> jetvecsTL=BoostedUtils::GetTLorentzVectors(jetvecs);
    // Event Shape Variables
    // Fox Wolfram Moments
    float h0,h1,h2,h3,h4;
    h0=-9;
    h1=-9;
    h2=-9;
    h3=-9;
    h4=-9;
    bdtvar.getFox(jetvecsTL, h0,h1,h2,h3,h4);
    vars.FillVar( "Evt_Reg_H0", h0 );
    vars.FillVar( "Evt_Reg_H1", h1 );
    vars.FillVar( "Evt_Reg_H2", h2 );
    vars.FillVar( "Evt_Reg_H3", h3 );
    vars.FillVar( "Evt_Reg_H4", h4 );


   
    std::vector<pat::Jet> regressedTaggedJets;
    std::vector<pat::Jet> regressedTaggedJetsT;
    std::vector<pat::Jet> regressedTaggedJetsL;
    std::vector<pat::Jet> regressedUntaggedJets;
    for(std::vector<pat::Jet>::const_iterator itJet = regressedJets.begin(); itJet != regressedJets.end(); ++itJet){
	if(BoostedUtils::PassesCSV(*itJet, 'M')){
	    regressedTaggedJets.push_back(*itJet);
	}
	else{
	    regressedUntaggedJets.push_back(*itJet);
	}
	if(BoostedUtils::PassesCSV(*itJet, 'L')){
	    regressedTaggedJetsL.push_back(*itJet);
	}
	if(BoostedUtils::PassesCSV(*itJet, 'T')){
	    regressedTaggedJetsT.push_back(*itJet);
	}
    }
    
    math::XYZTLorentzVector primLepVec = math::XYZTLorentzVector();
    if(input.selectedElectrons.size()>0 || input.selectedMuons.size()>0){
	primLepVec = BoostedUtils::GetPrimLepVec(input.selectedElectrons,input.selectedMuons);
    }

    if(regressedJets.size()>1){
	int idClosestJet1 = -1;
	int idClosestJet2 = -1;
	float minDrJets = BoostedUtils::GetClosestJetIDs(idClosestJet1,idClosestJet2,regressedJets);
	math::XYZTLorentzVector closestJetVec1 = regressedJets[idClosestJet1].p4();
	math::XYZTLorentzVector closestJetVec2 = regressedJets[idClosestJet2].p4();
	vars.FillVar("Evt_Reg_M_MinDeltaRJets",(closestJetVec1+closestJetVec2).M());
	vars.FillVar("Evt_Reg_Dr_MinDeltaRJets",minDrJets);
	vars.FillVar("Evt_Reg_Pt_MinDeltaRJets",(closestJetVec1+closestJetVec2).Pt());
    }
    // Tagged Jets
    if(regressedTaggedJets.size()>1){
	int idClosestTaggedJet1 = -1;
	int idClosestTaggedJet2 = -1;
	float minDrTaggedJets = BoostedUtils::GetClosestJetIDs(idClosestTaggedJet1,idClosestTaggedJet2,regressedTaggedJets);
	math::XYZTLorentzVector closestTaggedJetVec1 = regressedTaggedJets[idClosestTaggedJet1].p4();
	math::XYZTLorentzVector closestTaggedJetVec2 = regressedTaggedJets[idClosestTaggedJet2].p4();
	vars.FillVar("Evt_Reg_M_MinDeltaRTaggedJets",(closestTaggedJetVec1+closestTaggedJetVec2).M());
	vars.FillVar("Evt_Reg_Dr_MinDeltaRTaggedJets",minDrTaggedJets);
	vars.FillVar("Evt_Reg_Pt_MinDeltaRTaggedJets",(closestTaggedJetVec1+closestTaggedJetVec2).Pt());
    }
    // Untagged Jets
    if(regressedUntaggedJets.size()>1){
	int idClosestUntaggedJet1 = -1;
	int idClosestUntaggedJet2 = -1;
	float minDrUntaggedJets = BoostedUtils::GetClosestJetIDs(idClosestUntaggedJet1,idClosestUntaggedJet2,regressedUntaggedJets);
	math::XYZTLorentzVector closestUntaggedJetVec1 = regressedUntaggedJets[idClosestUntaggedJet1].p4();
	math::XYZTLorentzVector closestUntaggedJetVec2 = regressedUntaggedJets[idClosestUntaggedJet2].p4();
	vars.FillVar("Evt_Reg_M_MinDeltaRUntaggedJets",(closestUntaggedJetVec1+closestUntaggedJetVec2).M());
	vars.FillVar("Evt_Reg_Dr_MinDeltaRUntaggedJets",minDrUntaggedJets);
	vars.FillVar("Evt_Reg_Pt_MinDeltaRUntaggedJets",(closestUntaggedJetVec1+closestUntaggedJetVec2).Pt());
    }
    // Jet and Lepton
    if(regressedJets.size()>1&&(input.selectedElectrons.size()>0||input.selectedMuons.size()>0)){
	int idClosestJet = -1;
	float minDrLepJet = BoostedUtils::GetClosestLepJetID(idClosestJet,primLepVec,regressedJets);
	math::XYZTLorentzVector closestJetVec = regressedJets[idClosestJet].p4();
	vars.FillVar("Evt_Reg_M_MinDeltaRLeptonJet",(primLepVec+closestJetVec).M());
	vars.FillVar("Evt_Reg_Dr_MinDeltaRLeptonJet",minDrLepJet);
    }
    
    // Tagged Jet and Lepton
    if(regressedTaggedJets.size()>1&&(input.selectedElectrons.size()>0||input.selectedMuons.size()>0)){
	int idClosestTaggedJet = -1;
	float minDrLepTaggedJet = BoostedUtils::GetClosestLepJetID(idClosestTaggedJet,primLepVec,regressedTaggedJets);
	math::XYZTLorentzVector closestTaggedJetVec = regressedTaggedJets[idClosestTaggedJet].p4();
	vars.FillVar("Evt_Reg_M_MinDeltaRLeptonTaggedJet",(primLepVec+closestTaggedJetVec).M());
	vars.FillVar("Evt_Reg_Dr_MinDeltaRLeptonTaggedJet",minDrLepTaggedJet);
    }
    
     
}