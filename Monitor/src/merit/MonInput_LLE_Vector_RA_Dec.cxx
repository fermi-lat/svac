// 
// Class for input of quantity LLE_Vector_RA_Dec for monitoring 
// 
// Created by dpaneque on Mon Jun 13 17:28:23 2011 
// Object created automatically by script makeNewMonObject.pl
//
#include "MonInput_LLE_Vector_RA_Dec.h"
#include <iostream>
#include <math.h>

// User defined part 

#define NAME LLE_Vector_RA_Dec
#define OUTBRANCH "LLE_Vector_RA_Dec"
#define LEAF "LLE_Vector_RA_Dec[8][5]/I"
#define INBRANCH "FT1EventClass"
#define ACCESSOR NotApplicable
#define MONSOURCE MeritEvent
#define INPUTSOURCE "MeritEvent"
#define DESCRIPTION "Vector [8][5] reporting whether an event falls into one of the predefined circles with 45 deg radius centered at following  RA and Dec locations: RA=[0,45,90,135,180,225,270,315], Dec=[-90,-45,0,45,90]"

// End user defined part 

MonInput_LLE_Vector_RA_Dec::MonInput_LLE_Vector_RA_Dec(){
  m_name=OUTBRANCH;
  
  // Define vectors and variables
  m_radius = 45.0;
  m_PI = 3.14159265358979312;
  for (Int_t i=0;i<8;i++)
    m_RALocations[i]=Float_t(i)*m_radius;
  for (Int_t i=0;i<5;i++)
    m_DecLocations[i]=-90.0+Float_t(i)*m_radius;
}
MonInput_LLE_Vector_RA_Dec::~MonInput_LLE_Vector_RA_Dec(){
}


int MonInput_LLE_Vector_RA_Dec::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_LLE_Vector_RA_Dec::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
  tree.SetBranchStatus("FT1Ra",1);
  tree.SetBranchStatus("FT1Dec",1);
  tree.SetBranchAddress(INBRANCH,&m_ft1eventclass);
  tree.SetBranchAddress("FT1Ra",&m_RA);
  tree.SetBranchAddress("FT1Dec",&m_Dec);   
}
void MonInput_LLE_Vector_RA_Dec::setValue(TObject* event) {

  // Initialize vector:
  for (Int_t ra = 0; ra<8;ra++){
    for (Int_t dec = 0; dec<5;dec++){
      m_val[ra][dec] = 0;
    }
  }
  
  // Fill vector
  for (Int_t ra = 0; ra<8;ra++){ 
    for (Int_t dec = 0; dec<5;dec++){
      if (m_ft1eventclass & 1 << 14){// Bit 14 is the one that corresponds to LLE event
	if (getSeparation(m_RALocations[ra],m_DecLocations[dec],m_RA,m_Dec) < m_radius)
	  m_val[ra][dec] = 1;
      }
      // Print vector
      //std::cout << m_RALocations[ra] << " " << m_DecLocations[dec] << " " << m_val[ra][dec] << std::endl;
    }
  }

}
std::string MonInput_LLE_Vector_RA_Dec::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_LLE_Vector_RA_Dec::getDescription(){
  return DESCRIPTION;
}

Float_t MonInput_LLE_Vector_RA_Dec::getSeparation(Float_t RefRA,Float_t RefDec,Float_t RA,Float_t Dec){

  // Check input values

  if (RefRA <-360.0 || RefRA >360.0 || RefDec <-90.0 || RefDec >90.0 || RA <-360.0 || RA >360.0 || Dec <-90.0 || Dec >90.0)
    {
      //std::cout << "MonInput_LLE_Vector_RA_Dec::getSeparation: WARNING " << std::endl;
      //std::cout << "Input values are out of bounds" << std::endl;
      //std::cout << "RefRA, RefDec, RA, Dec" << RefRA << ", " << RefDec << ", " << ", " << RA << ", " << Dec << std::endl;
      //std::cout << "Returning 400" << std::endl;
      return 400.0;
    }

  //std::cout << "RefRA = " << RefRA << " RefDec = " << RefDec << std::endl;
  //std::cout << "RA = " << RA << " Dec = " << Dec << std::endl;

  double angsep = 180./m_PI * acos((cos((90.-RefDec)/180.*m_PI)*cos((90.-Dec)/180.*m_PI)+(sin((90.-RefDec)/180.*m_PI)*sin((90.-Dec)/180.*m_PI)*cos((RefRA-RA)/180.*m_PI))));

  //std::cout << "The angular separation is = " << angsep << std::endl;
  return angsep;

}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION

