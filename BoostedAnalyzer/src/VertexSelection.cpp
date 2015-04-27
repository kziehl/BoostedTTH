#include "BoostedTTH/BoostedAnalyzer/interface/VertexSelection.hpp"

using namespace std;

VertexSelection::VertexSelection (){}
VertexSelection::~VertexSelection (){}

void VertexSelection::Init(const edm::ParameterSet& iConfig, Cutflow& cutflow){

  cutflow.AddStep("First PV is good PV");

  initialized=true;
}

bool VertexSelection::IsSelected(const InputCollections& input,Cutflow& cutflow){
  if(!initialized) cerr << "VertexSelection not initialized" << endl;
  
  if(!input.eventInfo.firstVertexIsGood) {
    return false;
  }
  else{
    cutflow.EventSurvivedStep("First PV is good PV");
    return true;    
  }

}