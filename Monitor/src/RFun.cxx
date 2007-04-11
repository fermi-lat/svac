#include "RFun.h"
#include "configData/db/LatcDBImplOld.h"


int RFun::engine(int i,unsigned key){
  m_tcf->updateKey(key);
  return m_tcf->lut()->engineNumber(i);
}
int RFun::enginecounter(int i,unsigned key,int engine){
  m_tcf->updateKey(key);
  int eng= m_tcf->lut()->engineNumber(i);
  if (eng==engine)return 1;
  else return 0;
}
int RFun::iden(int i ){
  return i;
}

unsigned RFun::getconsecutiveplaneshit(const UShort_t invector[36])
{
  unsigned n_consecutiveplaneshit(0),maxhits(0);
  for (unsigned iplane = 0; iplane < 36; iplane++)
    {
      if(invector[iplane]>0)
	n_consecutiveplaneshit++;
      else
	{
	  if(maxhits<n_consecutiveplaneshit)
	    maxhits=n_consecutiveplaneshit;
	  n_consecutiveplaneshit=0;
	}
    }
  
  if(maxhits<n_consecutiveplaneshit)
    maxhits=n_consecutiveplaneshit;

  return  maxhits;
}

  
bool RFun::isempty(bool invector[16], unsigned towerid)
{
  if(towerid>15)
    {
      std::cout << "RF::isempty; ERROR"<< std::endl
		<< "towerid (="<< towerid<<") is out of allowed range [0-15]"<< std::endl;
      assert(0);
    }
  return invector[towerid];

}
void RFun::getemptytowers(bool invector[16], bool outvector[16])
{

  // initialization
  
  int boundarytwr[16][8];
  for(unsigned itwr = 0;itwr<16;itwr++)
    {
      // initialize empty tower vector to 1 (all are empty towers)
      outvector[itwr] = 1;
      // initialize boundarytwr vector to -1 (non-existent tower)
      for(unsigned j = 0;j<8;j++)
	boundarytwr[itwr][j] = -1;
    }
  
  // define boundary towers for each tower

  // twr0
  boundarytwr[0][0] = 1;
  boundarytwr[0][1] = 4;
  boundarytwr[0][2] = 5;
   // twr1
  boundarytwr[1][0] = 0;
  boundarytwr[1][1] = 4;
  boundarytwr[1][2] = 5;
  boundarytwr[1][3] = 6;
  boundarytwr[1][4] = 2;
   // twr2
  boundarytwr[2][0] = 1;
  boundarytwr[2][1] = 5;
  boundarytwr[2][2] = 6;
  boundarytwr[2][3] = 7;
  boundarytwr[2][4] = 3;
  
  // to be done for all towers !!!!



  
  // scan over all towers, setting the "empty tower condition" whenver 
  // the tower has a trigger and/or is boundary tower to a tower which had a trigger
  
  for(unsigned itwr = 0;itwr<16;itwr++)
    {
      if(invector[itwr])
	outvector[itwr] = 0;  // the tower had a trigger
      for(unsigned j = 0; j<8;j++)
	{
	  if(boundarytwr[itwr][j]>=0)
	    outvector[boundarytwr[itwr][j]] = 0;
	}
    }
}


std::vector<double> RFun::testfun(){
  std::vector<double> retvec;
  for (int i=0;i<16;i++)retvec.push_back((double)i);
  return retvec;
}


TrgConfigDB* RFun::m_tcf=new TrgConfigDB(new LatcDBImplOld);

