
#include <cmath>
#include <ctime>
#include <cassert>

#include "TkrHits.h"
#include "facilities/Util.h"
#ifndef OLD_RECON
#include "commonRootData/idents/TkrId.h"
#endif
#include "commonRootData/idents/TowerId.h"

using std::string;
using std::cout;
using std::endl;

//#define PRINT_DEBUG 1


bool Cluster::addStrip( int strip ){

  if( strip == lastStrip+1 ){ // assume strip number is sorted.
    lastStrip = strip;
    return true;
  }
  else return false;

}

//
// layerId class implementation
//
inline layerId::layerId( int lyr, int vw, int twr ){ 
  setLayer( lyr, vw, twr ); }
inline layerId::layerId( int tr, std::string wh, int twr ){ 
  setTray( tr, wh, twr ); }
inline layerId::layerId( int unp ){ setUniPlane( unp ); }

inline void layerId::setLayer( int lyr, int vw, int twr ){
  layer = lyr; view = vw; tower = twr;
  layerToTray();
  trayToUniPlane();
}

inline void layerId::setUniPlane( int unp, int twr ){
  uniPlane = unp; tower = twr;
  uniPlaneToTray();
  trayToLayer();
}

inline void layerId::setTray( int tr, std::string wh, int twr ){
  tray = tr; which=wh; tower=twr;
  trayToUniPlane();
  trayToLayer();
}

inline void layerId::trayToUniPlane(){
  uniPlane = tray * 2;
  if( which == "bot" ) uniPlane--;
}

inline void layerId::trayToLayer(){
  view = (tray+1) % 2;
  layer = tray;
  if( which == "bot" ) layer--;
}

void layerId::layerToTray(){
  if(view==0){
    tray = 2 * ( layer/2 ) + 1;
    if(layer%2==0) which = "bot";
    else which = "top";
  }
  else{
    tray = 2 * ( (layer+1)/2 );
    if(layer%2==0) which = "top";
    else which = "bot";
  }
}


inline void layerId::uniPlaneToTray(){
  tray = (uniPlane+1) / 2;
  if( uniPlane%2 == 0 ) which ="top";
  else which = "bot";
}

//
// towerVar class implementation
//
//
// towerVar class implementation
//
towerVar::towerVar( int twr, bool badStrips ){
  towerId = twr;
  hwserial = "None";
  runid = "-1";
  bsVar.clear();

  for( int unp=0; unp!=g_nUniPlane; unp++){
    badStripVar bsv;
    for( int strip=0; strip!=g_nStrip; strip++){
      rHits[unp][strip] = 0;
      dHits[unp][strip] = 0;
      if( badStrips ){
	bsv.eHits[strip] = 0;
	bsv.tHits[strip] = 0;
	bsv.lHits[strip] = 0;
	for(int iWafer = 0; iWafer != g_nWafer; ++iWafer)
	  for( int tDiv = 0; tDiv != g_nTime; tDiv++)
	    bsv.nHits[strip][iWafer][tDiv] = 0;
      }
    }
    if( badStrips ) bsVar.push_back( bsv );
  }
#ifdef PRINT_DEBUG
  std::cout << "towerVar constructer " << twr << std::endl;
#endif
}


void towerVar::saveHists(){

  TH1F* hist, *rhist, *dhist, *ehist, *thist, *lhist;
  char name[] = "roccT00X17w3t4";
  char cvw[] = "XY";
  for( int unp=0; unp!=g_nUniPlane; unp++){
    layerId lid( unp );
    int layer = lid.layer;
    int view = lid.view;
    sprintf(name,"roccT%d%c%d", towerId, cvw[view], layer);
    rhist = new TH1F(name, name, g_nStrip, 0, g_nStrip);
    sprintf(name,"doccT%d%c%d", towerId, cvw[view], layer);
    dhist = new TH1F(name, name, g_nStrip, 0, g_nStrip);
    for( int strip=0; strip!=g_nStrip; strip++){
      rhist->Fill( strip+0.1, rHits[unp][strip] );
      dhist->Fill( strip+0.1, dHits[unp][strip] );
    }
    rhist->Write(0, TObject::kOverwrite);
    dhist->Write(0, TObject::kOverwrite);
  }

  for( UInt_t unp=0; unp!=bsVar.size(); unp++){
    layerId lid( unp );
    int layer = lid.layer;
    int view = lid.view;
    sprintf(name,"eoccT%d%c%d", towerId, cvw[view], layer);
    ehist = new TH1F(name, name, g_nStrip, 0, g_nStrip);
    sprintf(name,"toccT%d%c%d", towerId, cvw[view], layer);
    thist = new TH1F(name, name, g_nStrip, 0, g_nStrip);
    sprintf(name,"loccT%d%c%d", towerId, cvw[view], layer);
    lhist = new TH1F(name, name, g_nStrip, 0, g_nStrip);
    for( int strip=0; strip!=g_nStrip; strip++){
      ehist->Fill( strip+0.1, bsVar[unp].eHits[strip] );
      thist->Fill( strip+0.1, bsVar[unp].tHits[strip] );
      lhist->Fill( strip+0.1, bsVar[unp].lHits[strip] );
    }
    ehist->Write(0, TObject::kOverwrite);
    thist->Write(0, TObject::kOverwrite);
    lhist->Write(0, TObject::kOverwrite);
    for(int iWafer = 0; iWafer != g_nWafer; ++iWafer){
      sprintf(name,"occT%d%c%dw%d", towerId, cvw[view], layer, iWafer);
      hist = new TH1F(name, name, g_nStrip, 0, g_nStrip);
      for( int strip=0; strip!=g_nStrip; strip++)
	hist->Fill( strip+0.1, bsVar[unp].nHits[strip][iWafer][0] );
      hist->Write(0, TObject::kOverwrite);
    }
  }
}
//
// TkrHits implementation 
//
TkrHits::TkrHits(): 
  m_reconFile(0), m_reconTree(0), 
  m_reconEvent(0), m_digiFile(0), m_digiTree(0),
  m_digiEvent(0), m_rootFile(0)
{

  // get version number from CVS string
  std::string tag = "$Name$";
  int i = tag.find( " " );
  tag.assign( tag, i+1, tag.size() );
  i = tag.find( " " );
  tag.assign( tag, 0, i ) ;
  m_tag = tag;

  std::string version = "$Revision$";
  i = version.find( " " );
  version.assign( version, i+1, version.size() );
  i = version.find( " " );
  version.assign( version, 0, i ) ;
  m_version = version;
  std::cout << "Tag: " << m_tag << ", version: " << m_version << std::endl;

  for(int tower = 0; tower != g_nTower; ++tower)
    m_towerPtr[tower] = -1;

  m_badStrips = true;
  initHists();
}


void TkrHits::getTimeStamp(){

  // get time 
  time_t rawtime=0;
  time( &rawtime );
  // format time into a null-terminated string
  char nts[] = "050124-000000";
  size_t ntsmax=10;
  strftime( nts, ntsmax, "%y%m%d", gmtime( &rawtime ) );
  m_dateStamp = nts;
  strftime( nts, ntsmax, "%H%M%S", gmtime( &rawtime ) );
  m_timeStamp = nts;
}


void TkrHits::splitWords(  std::vector<std::string>& words, 
		    const std::string& line ) {

  std::string::size_type pos = 0;
  std::string word;

  for( ; ; ) {

    string::size_type i = line.find(' ', pos);
    if(i != string::npos) word = line.substr(pos, i-pos);
    else word = line.substr(pos); // end of line
    words.push_back( word );
    
    if(i == string::npos) break;
    pos = i + 1;
  }
}


void TkrHits::initHists(){
  m_nTrackDist = new TH1F("nTrack", "nTrack", 10, 0, 10);
  m_maxHitDist = new TH1F("maxHit", "maxHit", g_nUniPlane, 0, g_nUniPlane);
  m_trkRMS = new TH1F("trkRMS", "trkRMS", 100, 0, 0.002);
  m_numClsDist = new TH1F("numCls", "# of cluster per layer", 10, 0, 10 );
  m_dirzDist = new TH1F("dirZ", "dirZ", 100, -1, 1);
  m_armsDist = new TH1F("arms", "arms", 100, -5, 5);
  m_lrec = new TH1F("lrec", "lrec", g_nUniPlane, 0, g_nUniPlane);
  m_ldigi = new TH1F("ldigi", "ldigi", g_nUniPlane, 0, g_nUniPlane);
  m_lcls = new TH1F("lcls", "lcls", g_nUniPlane, 0, g_nUniPlane);

  if( m_badStrips ) initOccHists();
}


void TkrHits::initOccHists(){
  m_locc = new TH1F("locc", "locc", g_nUniPlane, 0, g_nUniPlane);
  m_leff = new TH1F("leff", "leff", g_nUniPlane, 0, g_nUniPlane);
  m_ltrk = new TH1F("ltrk", "ltrk", g_nUniPlane, 0, g_nUniPlane);
  m_dist = new TH1F("dist", "distance", 50, 0, 200);
  m_brmsDist[0] = new TH1F("brms0", "brms 0-2", 100, -5, 5);
  m_brmsDist[1] = new TH1F("brms1", "brms 3-5", 100, -5, 5);
  m_brmsDist[2] = new TH1F("brms2", "brms 6-8", 100, -5, 5);
  m_brmsDist[3] = new TH1F("brms3", "brms 9-11", 100, -5, 5);
  m_brmsDist[4] = new TH1F("brms4", "brms 12-14", 100, -5, 5);
  m_brmsDist[5] = new TH1F("brms5", "brms 15-17", 100, -5, 5);
  m_occDist = new TH1F("occDist", "occDist", 200, 0, 200);
  m_poissonDist = new TH1F("poissonDist", "poissonDist", 40, -20, 0);
  m_aPos[0] = new TH1F("apos0", "apos0", 100, -250, 250);
  m_aPos[1] = new TH1F("apos1", "apos1", 100, -250, 250);
  m_aPos[2] = new TH1F("apos2", "apos2", 100, -250, 250);
  m_aPos[3] = new TH1F("apos3", "apos3", 100, -250, 250);
  m_aPos[4] = new TH1F("apos4", "apos4", 100, -250, 250);
}


void TkrHits::saveAllHist()
{
  if(m_rootFile == 0) return;
  std::cout << "save histograms" << std::endl;

  m_nTrackDist->Write(0, TObject::kOverwrite);
  m_maxHitDist->Write(0, TObject::kOverwrite);
  m_trkRMS->Write(0, TObject::kOverwrite);
  m_numClsDist->Write(0, TObject::kOverwrite);
  m_dirzDist->Write(0, TObject::kOverwrite);
  m_armsDist->Write(0, TObject::kOverwrite);
  m_lrec->Write(0, TObject::kOverwrite);
  m_ldigi->Write(0, TObject::kOverwrite);
  m_lcls->Write(0, TObject::kOverwrite);

  if( m_badStrips ){
    saveOccHists();
    for( UInt_t tw = 0; tw != m_towerVar.size(); ++tw)
      m_towerVar[tw].saveHists();
  }
}

TkrHits::~TkrHits() 
{
//   if(m_rootFile == 0) return;
//   if(!m_rootFile->IsOpen()){
//     m_rootFile->Open(m_rootFile->GetName(),"UPDATE");
//     std::cout << "Reopening..." << m_rootFile->GetName() <<std::endl;
//   }

//   std::cout << "save histograms" << std::endl;

//   if(m_rootFile->cd("TkrCalib")==kFALSE) {
//     m_rootFile->mkdir("TkrCalib");
//     m_rootFile->cd("TkrCalib");
//   }

//   m_nTrackDist->Write(0, TObject::kOverwrite);
//   m_maxHitDist->Write(0, TObject::kOverwrite);
//   m_trkRMS->Write(0, TObject::kOverwrite);
//   m_numClsDist->Write(0, TObject::kOverwrite);
//   m_dirzDist->Write(0, TObject::kOverwrite);
//   m_armsDist->Write(0, TObject::kOverwrite);
//   m_lrec->Write(0, TObject::kOverwrite);
//   m_ldigi->Write(0, TObject::kOverwrite);
//   m_lcls->Write(0, TObject::kOverwrite);

//   if( m_badStrips ){
//     saveOccHists();
//     for( UInt_t tw = 0; tw != m_towerVar.size(); ++tw)
//       m_towerVar[tw].saveHists();
//   }

//   m_rootFile->Close();
}


void TkrHits::saveOccHists(){
  for( int i=0; i<g_nLayer/3; i++) 
    m_brmsDist[i]->Write(0, TObject::kOverwrite);
  m_locc->Write(0, TObject::kOverwrite);
  m_leff->Write(0, TObject::kOverwrite);
  m_ltrk->Write(0, TObject::kOverwrite);
  m_dist->Write(0, TObject::kOverwrite);
  m_occDist->Write(0, TObject::kOverwrite);
  m_poissonDist->Write(0, TObject::kOverwrite);
  m_aPos[0]->Write(0, TObject::kOverwrite);
  m_aPos[1]->Write(0, TObject::kOverwrite);
  m_aPos[2]->Write(0, TObject::kOverwrite);
  m_aPos[3]->Write(0, TObject::kOverwrite);
  m_aPos[4]->Write(0, TObject::kOverwrite);
}


bool TkrHits::setOutputFiles( const char* outputDir )
{
  m_outputDir = outputDir;

  std::string testId = "TE603";
  if( m_badStrips ) testId = "TE403";

  std::string filename;
  char fname[] = "/TE603_050121-000000.root";

  filename = m_outputDir;
  sprintf( fname, "/%s_%s-%s.log", testId.c_str(), 
	   m_dateStamp.c_str(), m_timeStamp.c_str() );
  filename += fname;
  m_log.open( filename.c_str() );
  if( m_log )
    std::cout << "Open log file: " << filename << std::endl;
  else{
    std::cout << filename << " cannot be opened." << std::endl;
    return false;
  }

  filename = m_outputDir;
  sprintf( fname, "/%s_%s-%s.root", testId.c_str(), 
	   m_dateStamp.c_str(), m_timeStamp.c_str() );
  filename += fname;
  m_rootFile = new TFile( filename.c_str(), "RECREATE" );
  if( m_rootFile ){
    std::cout << "Open output root file: " << filename << std::endl;
    m_log << "Output root file: " << filename << std::endl;
  }
  else{
    std::cout << filename << " can not be opened." << std::endl;
    return false;
  }
  return true;
}


void TkrHits::analyzeEvents( int iEvent )
{
    if(! passCut()) return;

    if( ! m_towerInfoDefined ) setTowerInfo();

    getReconClusters();
    getDigiClusters();
    selectGoodClusters();
    
    fillOccupancy( 0 );
}


void TkrHits::setTowerInfo(){

  if( m_towerVar.size() == g_nTower ){
    m_towerInfoDefined = true;
    return;
  }

  const TObjArray* tkrDigiCol = m_digiEvent->getTkrDigiCol();
  if (!tkrDigiCol) return;
  
  std::vector<int> strips;
  // Loop over all TkrDigis
  TIter tkrIter(tkrDigiCol);
  TkrDigi *tkrDigi = 0;
  while ( ( tkrDigi = (TkrDigi*)tkrIter.Next() ) ) {
    Int_t tower = tkrDigi->getTower().id();
    // register tower id pointer if this is the first encounter
    if( m_towerPtr[ tower ] < 0 ){
      m_towerPtr[ tower ] = m_towerVar.size();
      m_towerVar.push_back( towerVar( tower, m_badStrips ) );
    }
  }
}


layerId TkrHits::getLayerId( Cluster* cluster ){

  int tower = cluster->getTowerId();
  int unp = cluster->getUniPlane();

  layerId lid( unp );
  lid.setTower ( tower );
  return lid;
}


layerId TkrHits::getLayerId( const TkrCluster* cluster )
{
#ifdef OLD_RECON
  int planeId = cluster->getPlane();
  TkrCluster::view viewId = cluster->getView();
  int tower = cluster->getTower();
  int layer = g_nLayer - planeId - 1;
  int view = (viewId == TkrCluster::X) ? 0 : 1;
#else
  commonRootData::TkrId id = cluster->getTkrId();
  int tower = TowerId( id.getTowerX(), id.getTowerY() ).id();
  int view = id.getView();
  int layer = cluster->getLayer();
#endif
  layerId lid( layer, view, tower);
  return lid;
}


void TkrHits::getDigiClusters()
{
#ifdef PRINT_DEBUG
  std::cout << "getDigiClusters start" << std::endl;
#endif
  //
  // clear cluster information.
  for( UInt_t tw=0; tw!=m_towerVar.size(); tw++)
    for( int unp=0; unp!=g_nUniPlane; unp++)
      m_towerVar[tw].digiClusters[unp].clear();
  
  // The full collection of TkrDigis for this event
  const TObjArray* tkrDigiCol = m_digiEvent->getTkrDigiCol();
  if (!tkrDigiCol) return;
  
  std::vector<int> strips;
  // Loop over all TkrDigis
  TIter tkrIter(tkrDigiCol);
  TkrDigi *tkrDigi = 0;
  while ( ( tkrDigi = (TkrDigi*)tkrIter.Next() ) ) {
    // Identify the tower and layer
    Int_t tower = tkrDigi->getTower().id();
    Int_t tw = m_towerPtr[ tower ];
    Int_t totl = tkrDigi->getToT(0);
    Int_t toth = tkrDigi->getToT(1);
    Int_t lastRC0Strip = tkrDigi->getLastController0Strip();

    Int_t layer = tkrDigi->getBilayer();
  
    // Returns the orientation of the strips
    GlastAxis::axis viewId = tkrDigi->getView();
    int view = (viewId == GlastAxis::X) ? 0 : 1;

    layerId lid( layer, view );
    int uniPlane = lid.uniPlane;
    
    strips.clear();
    UInt_t numHits = tkrDigi->getNumHits();
    // Loop through collection of hit strips for this TkrDigi
    UInt_t ihit;
    for (ihit = 0; ihit < numHits; ihit++) {
      // Retrieve the strip number
      Int_t iStrip = tkrDigi->getStrip(ihit);
      strips.push_back( iStrip );
      m_towerVar[tw].dHits[uniPlane][iStrip]++;      
    }
    std::sort( strips.begin(), strips.end() ); // sort strip# for clustering.
    for( UInt_t i=0; i!=strips.size(); i++){
      bool newCls = false;
      if( m_towerVar[tw].digiClusters[uniPlane].empty() ) newCls = true;
      else if( !m_towerVar[tw].digiClusters[uniPlane].back().addStrip( strips[i] ) )
	newCls = true;
      
      if( newCls ){
	m_ldigi->Fill( uniPlane );
	if( strips[i] <= lastRC0Strip )
	  m_towerVar[tw].digiClusters[uniPlane].push_back( Cluster( strips[i], totl ) );
	else
	  m_towerVar[tw].digiClusters[uniPlane].push_back( Cluster( strips[i], toth ) );
      }
    }
  }
#ifdef PRINT_DEBUG
  std::cout << "getDigiClusters end" << std::endl;
#endif
}

void TkrHits::getReconClusters()
{
#ifdef PRINT_DEBUG
  std::cout << "getReconClusters start" << std::endl;
#endif
  
  // initialize recon cluster info
  for( unsigned int tw=0; tw<m_towerVar.size(); tw++){
    int twr = m_towerPtr[ m_towerVar[tw].towerId ];
    if( twr != int(tw) ) {
      std::cout << "Invalid tower id: " << twr << " != " << tw << std::endl;
      m_log << "Invalid tower id: " << twr << " != " << tw << std::endl;
      exit( EXIT_FAILURE );
    }
    for( int unp=0; unp<g_nUniPlane; unp++)
      m_towerVar[tw].reconClusters[unp] = 0;
  }
  m_trackTowerList.clear();
  
  TkrRecon* tkrRecon = m_reconEvent->getTkrRecon();
  assert(tkrRecon != 0);
  
  int lastTower = -1;
  int numRecCls = 0;
  
#ifdef OLD_RECON
  std::map<int, TkrCluster*> clsMap;
  TObjArray* siClusterCol = tkrRecon->getClusterCol();
  int noOfTkrClusters = siClusterCol->GetLast()+1;
  for(int i = 0; i != noOfTkrClusters; ++i) {
    TkrCluster* cluster = dynamic_cast<TkrCluster*>(siClusterCol->At(i));
    clsMap[cluster->getId()] = cluster;
  }
  
  TkrKalFitTrack* tkrTrack = m_track;
  int nHitPlane = tkrTrack->getNumHits();
  for(int iPlane = 0; iPlane != nHitPlane; ++iPlane) {
    const TkrHitPlane* plane = tkrTrack->getHitPlane(iPlane);
    std::map<int, TkrCluster*>::const_iterator itr = clsMap.find(plane->getIdHit());
    assert(itr != clsMap.end());
    TkrCluster* cluster = itr->second;
#else
  TkrTrack* tkrTrack = m_track;
  TIter trk1HitsItr(tkrTrack);
  TkrTrackHit* pTrk1Hit = 0;
  while( (pTrk1Hit = (TkrTrackHit*)trk1HitsItr.Next()) ) {    
    const TkrCluster* cluster = (pTrk1Hit->getClusterPtr());
    if(!cluster) continue;
#endif
    numRecCls++;
    layerId lid = getLayerId( cluster );
    //std::cout << lid.tower << " " << lid.uniPlane << " " << lid.layer << " " << lid.view << std::endl;
    int tw = m_towerPtr[ lid.tower ];
    m_towerVar[tw].reconClusters[lid.uniPlane] = cluster;
    if( lid.tower != lastTower ){
      lastTower = lid.tower;
      m_trackTowerList.push_back( lastTower );
      if( lid.view == 0 )
	m_towerVar[tw].center[1] = (cluster->getPosition()).Y();
      else
	m_towerVar[tw].center[0] = (cluster->getPosition()).X();
    }
    m_lrec->Fill( lid.uniPlane );
  }
#ifdef PRINT_DEBUG
  std::cout << "getReconClusters end" << std::endl;
#endif
}

void TkrHits::selectGoodClusters(){
  
#ifdef PRINT_DEBUG
  std::cout << "selectGoodClusters start" << std::endl;
#endif

  bool display = false;
  m_clusters.clear();
  //
  // register new raw clusters if it is close to the track position
  //
  Cluster* cluster;
  for( UInt_t tw=0; tw<m_trackTowerList.size(); tw++ ){
    int tower = m_trackTowerList[tw]; // order of towers for a track
    int twr = m_towerPtr[tower];
    for (int unp=g_nUniPlane-1; unp>=0; unp--){
      layerId lid( unp ); 
      int layer = lid.layer;
      int view = lid.view;
      float zpos = posZ[view][layer];
      //std::cout << layer << " " << view << " " 
      //	<< m_towerVar[twr].digiClusters[unp].size() << std::endl;

      int numCls = 0;
      for( UInt_t i=0; i!= m_towerVar[twr].digiClusters[unp].size(); i++){
	cluster = &( m_towerVar[twr].digiClusters[unp].at(i) );
	
	// calculate position
	float pos = ( cluster->getLastStrip() + cluster->getFirstStrip() )/2;
	int ladder = int( pos * 4 / g_nStrip );
	pos = pos - g_nStrip * 0.5 + 0.5;
	pos = pos * stripPitch + ladderGap * (ladder - 1.5 ) + m_towerVar[twr].center[view];
	//std::cout <<  cluster->getLastStrip() << " " 
	//<< cluster->getFirstStrip() << " " << pos << std::endl;
	if( view == 0 )
	  cluster->setXYZ( pos, m_towerVar[twr].center[1], zpos );
	else
	  cluster->setXYZ( m_towerVar[twr].center[0], pos, zpos );
	cluster->setId( tower, unp );
	if( m_towerVar[twr].reconClusters[unp] )
	  cluster->setCorrectedTot( 5.0 * m_towerVar[twr].reconClusters[unp]->getMips() );
	
	// check if this cluster is close to the track position
	layerId tlid;

	// find closest recon clusters
	float dzmin=10000, dzmin2=10000, dz;
	int numSkip=0, umin, umin2, tl, tunp;
	const TkrCluster* tcls;
	for( int dl=1; dl<g_nLayer; dl++){
	  for( int dir=-1; dir<2; dir+=2){
	    tl = layer + dl*dir;
	    if( tl < g_nLayer && tl >=0 ){
	      tlid.setLayer( tl, view );
	      tunp = tlid.uniPlane;
	      tcls = m_towerVar[twr].reconClusters[tunp];
	      if( tcls ){
		dz = fabs( zpos - tcls->getPosition().Z() );
		if( dz < dzmin ){
		  dzmin2 = dzmin;
		  umin2 = umin;
		  dzmin = dz;
		  umin = tunp;
		}
		else if( dz < dzmin2 ){
		  dzmin2 = dz;
		  umin2 = tunp;	
		}
		else numSkip++;
	      }
	    }
	    if( numSkip > 1 ) break;
	  }
	  if( numSkip > 1 ) break;
	}

	if( dzmin2>1000 || dzmin>1000 ) continue;

	TVector3 pos1 = m_towerVar[twr].reconClusters[umin]->getPosition();
	TVector3 pos2 = m_towerVar[twr].reconClusters[umin2]->getPosition();

	float delta;
	if( lid.view == 0 ){
	  pos = pos1.X() + ( pos2.X()-pos1.X() ) * ( zpos-pos1.Z() ) / ( pos2.Z() - pos1.Z() );
	  delta = cluster->getPosition().X() - pos;
	}
	else{
	  pos = pos1.Y() + ( pos2.Y()-pos1.Y() ) * ( zpos-pos1.Z() ) / ( pos2.Z() - pos1.Z() );
	  delta = cluster->getPosition().Y() - pos;
	}
	
	if( display ) std::cout << tower << " " << lid.layer << " " << lid.view << ", " << delta << " " << " " << pos << " " << zpos;
	m_armsDist->Fill( delta );
	if( fabs(delta) > 3.0 ){
	  if( display ) std::cout << " **************" << std::endl;
	  continue;
	}
	if( display ) std::cout << std::endl;
	
	//
	// good cluster, multiple cluster per layer allowed.
	//
	numCls++;
	m_clusters.push_back( cluster ); 
	for(int iStrip = cluster->getFirstStrip(); 
	    iStrip != int(cluster->getLastStrip()+1); ++iStrip){
	  m_towerVar[twr].rHits[unp][iStrip]++;
	  m_lcls->Fill( unp );
	}
      }
      m_numClsDist->Fill( numCls );
      //std::cout << tower << " " << uniPlane << std::endl;
    }
  }

#ifdef PRINT_DEBUG
  std::cout << "selectGoodClusters end" << std::endl;
#endif

}

bool TkrHits::closeToTrack( const TkrCluster* cluster, TkrCluster* clusters[g_nTower][g_nUniPlane] )
{
  layerId lid = getLayerId( cluster ), tlid;
  int tower = lid.tower;
  int layer = lid.layer;
  int view = lid.view;
  float zpos = cluster->getPosition().Z();

  bool display = false;
  //if( layer == 4 && view == 0 ) display = true;
  if( display ) std::cout << "X4 ";

  // find closest hits
  float dzmin=10000, dzmin2=10000, dz;
  int numSkip=0, umin, umin2, tl, tunp;
  TkrCluster* tcls;
  for( int dl=1; dl<g_nLayer; dl++){
    for( int dir=-1; dir<2; dir+=2){
      tl = layer + dl*dir;
      if( tl < g_nLayer && tl >=0 ){
	tlid.setLayer( tl, view );
	tunp = tlid.uniPlane;
	tcls = clusters[tower][tunp];
	if( tcls ){
	  dz = fabs( zpos - tcls->getPosition().Z() );
	  if( dz < dzmin ){
	    dzmin2 = dzmin;
	    umin2 = umin;
	    dzmin = dz;
	    umin = tunp;
	  }
	  else if( dz < dzmin2 ){
	    dzmin2 = dz;
	    umin2 = tunp;	
	  }
	  else numSkip++;
	}
      }
      if( numSkip > 1 ) break;
    }
    if( numSkip > 1 ) break;
  }

  if( display ) std::cout << numSkip << " " << lid.uniPlane << " " 
			  << umin << " " << dzmin << " " 
			  << umin2 << " " << dzmin2 << ", ";
  
  if( dzmin2>1000 || dzmin>1000 ){
    if( display ) std::cout << std::endl;
    return false;
  }

  TVector3 pos1 = clusters[tower][umin]->getPosition();
  TVector3 pos2 = clusters[tower][umin2]->getPosition();

  float delta, pos;
  if( lid.view == 0 ){
    pos = pos1.X() + ( pos2.X()-pos1.X() ) * ( zpos-pos1.Z() ) / ( pos2.Z() - pos1.Z() );
    delta = cluster->getPosition().X() - pos;
  }
  else{
    pos = pos1.Y() + ( pos2.Y()-pos1.Y() ) * ( zpos-pos1.Z() ) / ( pos2.Z() - pos1.Z() );
    delta = cluster->getPosition().Y() - pos;
  }
  
  if( display ) std::cout << tower << " " << lid.layer << " " << lid.view << ", " << delta << " " << " " << pos << " " << zpos;
  m_armsDist->Fill( delta );
  if( fabs(delta) > 3.0 ){
    if( display ) std::cout << " **************" << std::endl;
    return false;
  }
  if( display ) std::cout << std::endl;

  return true;

}


bool TkrHits::passCut() 
{
  TkrRecon* tkrRecon = m_reconEvent->getTkrRecon(); 
  assert(tkrRecon != 0);
  
  TObjArray* tracks = tkrRecon->getTrackCol();
  int numTracks = tracks->GetEntries();
  m_nTrackDist->Fill( numTracks );
  
  // select only 1 or 2 track event
  if( numTracks > 2) return false;
  
  // find a track with maximum number of hits.
  int maxHits = 0, nHits;
  for( int tk=0; tk!=numTracks; tk++){
    
#ifdef OLD_RECON
    TkrKalFitTrack* track = dynamic_cast<TkrKalFitTrack*>(tracks->At(tk));
#else
    TkrTrack* track = dynamic_cast<TkrTrack*>(tracks->At(tk));
#endif
    if(track) {
      nHits = track->getNumFitHits();
      if( nHits > maxHits ){
	maxHits = nHits;
	m_track = track;
	m_pos = track->getInitialPosition();
	m_dir = track->getInitialDirection();
      }
    }
  }
  m_maxHitDist->Fill( maxHits );
  if( maxHits < 6 ) return false;
  m_trkRMS->Fill( m_track->getScatter() );
  m_dirzDist->Fill( m_dir.Z() );
  float maxDirZ = m_maxDirZ;
  if( m_badStrips ) maxDirZ = -0.7;
  if( m_dir.Z() > maxDirZ ) return false;
  if( m_track->getScatter() > 2.0E-4 ) return false;
  
  return true;
}


void TkrHits::fillOccupancy( int tDiv ) 
{
#ifdef PRINT_DEBUG
  std::cout << "fillOccupancy start" << std::endl;
#endif
  
  //initialize container
  int nHits[g_nTower][g_nLayer][g_nView][g_nWafer+1];
  for( unsigned int tw=0; tw<m_towerVar.size(); tw++){
    int tower = m_towerVar[tw].towerId;
    for( int layer=0; layer<g_nLayer; layer++)
      for( int view=0; view<g_nView; view++)
	for( int i=0; i<g_nWafer+1; i++) nHits[tower][layer][view][i] = 0;
  }
  
  //
  // first loop to register hits and get tower offset
  //
  int hitLayers[g_nLayer];
  int hitPlanes[g_nLayer][g_nView];
  for( int layer=0; layer!=g_nLayer; layer++){
    hitLayers[layer]=0;
    for( int vw=0; vw!=g_nView; vw++) hitPlanes[layer][vw]=0;
  }
  
  for( unsigned int cls=0; cls<m_clusters.size(); cls++){
    Cluster* cluster = m_clusters[cls];
    layerId lid = getLayerId( cluster );
    int tower = lid.tower;
    int view = lid.view;
    int layer = lid.layer;
    
    for(int iStrip = cluster->getFirstStrip(); 
	iStrip != int(cluster->getLastStrip()+1); ++iStrip){
      nHits[tower][layer][view][iStrip/384]++;
      nHits[tower][layer][view][g_nWafer]++;
    }
    
    hitLayers[layer]++;
    hitPlanes[layer][view]++;
  }
  
  //
  // main loop to fill occupancy and track position
  //
  float pos, apos, tpos[g_nView], lpos, posz;
  float dist, dxz, dyz, dz, delta, deltax, deltay;
  float dirX=m_dir.X()/m_dir.Z(), dirY=m_dir.Y()/m_dir.Z(), 
    preX=m_pos.X(), preY=m_pos.Y(), preXZ=m_pos.Z(), preYZ=m_pos.Z();
  int aview, preLayer=g_nLayer;
  int lastTower=-1, nTowers, towers[2], strips[g_nView];

  int numCls = m_clusters.size();
  for( int cls=0; cls<numCls; cls++){
    Cluster* cluster = m_clusters[cls];
    layerId lid = getLayerId( cluster );
    int tower = lid.tower;
    int view = lid.view;
    int layer = lid.layer;
    int unp = lid.uniPlane;
    
    // fill track positions in all layer between previous and current layer
    // carefull for moving across towers.
    int elyr = layer;
    if( cls == numCls-1 ) elyr = 0;
    for( int lyr=preLayer-1; lyr>= elyr; lyr--){ 
      // layers where hits are expected.
      // hit in the same layer or hits in both layers below and above.
      if( hitLayers[lyr] != 0
	  || ( lyr!=0 && lyr!=g_nLayer-1 
	       && hitLayers[lyr+1]>0 && hitLayers[lyr-1]>0 ) ){
	posz =  posZ[view][lyr];
	dxz = posz - preXZ;
	tpos[0] = preX + dirX*dxz;
	dyz = posz - preYZ;
	tpos[1] = preY + dirY*dyz;
	
	// check if track moves across towers.
	if( tower != lastTower ){
	  if( lastTower < 0 ){ 
	    lastTower = tower;
	    towers[0] = tower;
	    nTowers = 1;
	  }
	  else{
	    towers[0] = lastTower;
	    towers[1] = tower;
	    nTowers = 2;
	    lastTower = -1;
	  }
	}
	for( int tw=0; tw<nTowers; tw++){ // check both tower
	  int twr = towers[tw];
	  int vtw = m_towerPtr[twr];
	  int numActive=0;
	  for( int vw=0; vw!=g_nView; vw++){
	    strips[vw]=-1;
	    lpos = tpos[vw] - m_towerVar[vtw].center[vw];
	    for( int iw=0; iw!=g_nWafer; ++iw){
	      float stp = ( lpos-ladderGap*(iw-1.5) ) / stripPitch 
		+ g_nStrip/2;
	      if( stp>=iw*g_nStrip/4 && stp < (iw+1)*g_nStrip/4 ){
		strips[vw] = int(stp);
	      }
	    }
	    if( strips[vw] > 0 ) numActive++;
	  }
	  // check if track go thorugh active region in all views
	  if( numActive == g_nView ){
	    for( int vw=0; vw!=g_nView; vw++){
	      layerId lid( lyr, vw );
	      m_towerVar[vtw].bsVar[lid.uniPlane].tHits[strips[vw]]++;
	      // layer with associated hits
	      if( hitPlanes[layer][vw]>0 )
		m_towerVar[vtw].bsVar[lid.uniPlane].eHits[strips[vw]]++;
	      m_ltrk->Fill( lid.uniPlane );
	    }
	  }
	} // tower loop
      } // valid layer
    } // layer loop
    preLayer = layer;

    TVector3 position = cluster->getPosition();
    posz = position.Z();
    if( fabs(posz-posZ[view][layer]) > 0.01 )
      std::cout << "Incosistent z position: " << layer << " " << view << ", " 
		<< posZ[view][layer] << " != " << posz << std::endl;
    dyz = posz - preYZ;
    dxz = posz - preXZ;
    deltax = preX + dirX*dxz - position.X();
    deltay = preY + dirY*dyz - position.Y();
    
    if( view == 0 ){
      dz = dxz;
      delta = deltax;
    }
    else{
      dz = dyz;
      delta = deltay;
    }
    
    float dx = dirX*dz;
    float dy = dirY*dz;
    dist =sqrt( dz*dz+dx*dx+dy*dy );
    m_dist->Fill( dist );
    if( dist < 30 ) dist = 30;
    delta *= (35.0/dist);
    m_brmsDist[layer/3]->Fill( delta );
    //if( layer==4 && view==0 ) m_brmsDist[layer/3]->Fill( delta );
    
    // select good clusters
    if( fabs(delta) > 3.0  ) continue;
    
    if( view == 0 ){
      aview = 1;
      pos = deltax;
      apos = deltay;
      if( dxz > 10.0 ) dirX = ( position.X() - preX ) / dxz;
      preX = position.X();
      preXZ = position.Z();
    }
    else{
      aview = 0;
      pos = deltay;
      apos = deltax;
      if( dyz > 10.0 ) dirY = ( position.Y() - preY ) / dyz;
      preY = position.Y();
      preYZ = position.Z();
    }
    
    //std::cout << layer << " " << view << ", " << pos << " " << apos
    //      << std::endl;
    
    int twr = m_towerPtr[tower];
    m_locc->Fill( lid.uniPlane );
    for(int iStrip = cluster->getFirstStrip(); 
	iStrip != int(cluster->getLastStrip()+1); ++iStrip){
      m_towerVar[twr].bsVar[unp].lHits[iStrip]++;
      if( nHits[tower][layer][aview][g_nWafer] > 0 ){
	for( int iw=0; iw<g_nWafer; iw++ )
	  if( nHits[tower][layer][aview][iw] > 0 ){
	    m_towerVar[twr].bsVar[unp].nHits[iStrip][iw][tDiv]++;
	    m_aPos[iw]->Fill( apos-89.5*(iw-1.5) );
	  }
      }
      else{
	for( int iw=0; iw<g_nWafer; iw++ )
	  if( fabs( apos-89.5*(iw-1.5) ) < 44.4 ){
	    m_towerVar[twr].bsVar[unp].nHits[iStrip][iw][tDiv]++;
	    m_aPos[iw]->Fill( apos-89.5*(iw-1.5) );
	  }
      }
    }
  }
  
#ifdef PRINT_DEBUG
  std::cout << "fillOccupancy end" << std::endl;
#endif
}
