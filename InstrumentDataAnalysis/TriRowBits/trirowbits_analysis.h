#include <stdio.h>

TH1F *h1;

void conditions_histogram(TCut cut, int tower, char *data){
/** Conditions Histogram function:
    The purpose is to produce a histogram of the number of times each condition
    is satisfied given a TCut ("McEnergy>10" for example) for a given tower.
    There are two possible sources of data "digi" and "tem"
    */
char *title=(char*)malloc(30*sizeof(char));
sprintf(title, "Tower %d", tower);

if(h1) h1->Delete();

int type = strcmp(data, "digi");
TH1F *h1 = new TH1F("h1", title, 16, -0.5, 15.5);

for(int i=0; i<16; i++){
   svac->Draw("EvtEnergySumOpt>>htemp", condition(tower, i, type)&&cut);
   TH1F *htemp = (TH1F*)gDirectory->Get("htemp");
   h1->SetBinContent(i+1, htemp->GetEntries());
   }
h1->SetBarWidth(0.8*h1->GetBinWidth(1));
h1->SetFillColor(46);
h1->SetBarOffset(0.1);
if(type) title=strcat(title, " - TemWord");
  else strcat(title, " - DigiWord");
h1->SetTitle(title);
h1->DrawCopy("bar2");

}


TCut condition (int tower, int combination, int type){
/** condition function:
    The purpose is to return a TCut for a given combination and tower.
    type=0 for digi data
    type!=0 for tem data
    */
if(combination>15||combination<0||tower<0||tower>15){
   cout<<"condition doesnt make sense"<<endl;
   return NULL;
   }

char *s=(char*)malloc(30*sizeof(char));

if(type) sprintf(s, "(BitWord[%d]&2**%d)>0", tower, combination);
  else sprintf(s, "(TrgTriRowBits[%d]&2**%d)>0", tower, combination);
return s;

}

void bitword_friend(TChain *chain, char *name){
/** Bitword Friend function:
    The purpose is to produce a root file with a friend tree to svac tuple that contains
    the tem bitwords calculated from TkrReq
    */

char *filename = (char*)malloc(100*sizeof(char));

filename=strcpy(filename, svac_path);
name=strtok(name, ".root");
filename=strcat(filename, name);
filename=strcat(filename, "BitWordFriend.root");


int req[16][18][2][2], bitword[16];
int layer_bits[3];
int run, id;


TFile fr(filename);

if(!fr.IsOpen()){

    cout<<"Friend File does not exist, creating now..."<<endl;

    chain->SetBranchAddress("TkrReq", req);

    TFile fr(filename, "recreate");
    TTree *friend = new TTree("BitFriend", "Bitword Friend");

    friend->Branch("BitWord", bitword, "BitWord[16]/I");

    int nentries = chain->GetEntries();

    for(int i=0; i<nentries; i++){
       chain->GetEntry(i);
       for(int tower = 0; tower<16; tower++){
          bitword[tower]=0;
          for(int combination=0; combination<16; combination++){
	     for(int row=0; row<3; row++){
	       //int layer = 17 - (combination + row);     //layers in req are enumerated starting at the top,  @#*%%!
	       int layer = combination + row;
	       int xlayer = req[tower][layer][0][0] | req[tower][layer][0][1];
	       int ylayer = req[tower][layer][1][0] | req[tower][layer][1][1];
	       layer_bits[row] = xlayer & ylayer;
	       }
	     if(layer_bits[0]&&layer_bits[1]&&layer_bits[2])
	       bitword[tower] |= (int)pow(2, combination);
	   }
	}
	friend->Fill();
     }

     fr.cd();
     friend->Write();
     fr.Close();
     exit(1);
     }
     else fr.Close();

chain->AddFriend("BitFriend", filename);

}



void readchainfile(TChain *chain){
/** readchainfile function:
    The purpose is to read into a chain all the svac tuple root files specified in the
    file filelist.txt
    */

char *line, *filename, *listfile;
line=(char*)malloc(60*sizeof(char));
filename = (char*)malloc(100*sizeof(char));
listfile= (char*)malloc(100*sizeof(char));

listfile=strcpy(listfile, "filelist.txt");

FILE *list;

list=fopen(listfile, "r");
if(!list) {
    cout<<listfile<<" was not found"<<endl;
    return;
    }

while(!feof(list)){
    fgets(line, 60, list);
    if(strcmp(line, "")==0) break;   //In case there is an empty line at the end of filelist.txt
    line=strtok(line, "\n");
    filename=strcpy(filename, svac_path);
    filename=strcat(filename, line);
    if(chain->Add(filename))  cout<<line<<" was read..."<<endl;
    }

bitword_friend(svac, line);
}




void check_consistency(int tower){

/** check_consistency function:

   The purpose is to go over the svac tuple and check the bitwords from the digis
   and the tem and look for inconsistent events. The results are kept in the root
   file analysis.root.
   The most significant variable in tree analysis is Inconsistent which can take one
   of 3 possible values  0   if   digiword  is equal to  temword
                         1   if   digiword  >  temword
			-1   if   digiword  <  temword
   Finally two plots are produced. The first one is a scatter plot of digiword vs temword
   The second plot is a 3D surface of the same data, useful to get a feeling of the density
   of events as a function of bitwords.
   */

n_inconsistent_events=0;
n_fakehits=0;
int digiword, temword, inconsistent;
int svac_run, svac_id, tem_bitword[16], digi_bitword[16];
int nentries, tkrnumtracks, gltword;

nentries=svac->GetEntries();

TFile file("Analysis.root", "recreate");
TTree *analysis = new TTree("Analysis", "Analysis");

analysis->Branch("Run", &svac_run, "Run/I");
analysis->Branch("Event_ID", &svac_id, "Event_ID/I");
analysis->Branch("DigiWord", &digiword, "DigiWord/I");
analysis->Branch("TemWord", &temword, "TemWord/I");
analysis->Branch("Inconsistent", &inconsistent, "Inconsistent/I");
analysis->Branch("TkrNumTracks", &tkrnumtracks, "TkrNumTracks/I");
analysis->Branch("GltWord", &gltword, "GltWord");


svac->SetBranchStatus("*", 0);
svac->SetBranchStatus("Run", 1);
svac->SetBranchStatus("Event_ID", 1);
svac->SetBranchStatus("BitWord", 1);
svac->SetBranchStatus("TkrNumTracks", 1);
svac->SetBranchStatus("GltWord", 1);
svac->SetBranchStatus("TrgTriRowBits", 1);
svac->SetBranchAddress("Run", &svac_run);
svac->SetBranchAddress("Event_ID", &svac_id);
svac->SetBranchAddress("BitWord", tem_bitword);
svac->SetBranchAddress("TkrNumTracks", &tkrnumtracks);
svac->SetBranchAddress("GltWord", &gltword);
svac->SetBranchAddress("TrgTriRowBits", digi_bitword);

char *title;
title=(char*)malloc(30*sizeof(char));
sprintf(title, "Tower %d", tower);


for(int i=0; i<nentries; i++){
   if(i%2000==0) cout<<i<<" out of "<<nentries<<" have been processed...   "<<n_inconsistent_events<<" inconsistent so far"<<endl;
   int svac_entry = svac->LoadTree(i);
   svac->GetEntry(i);
   temword=tem_bitword[tower];
   digiword=digi_bitword[tower];
   if(temword==digiword) inconsistent=0;
     else{
        n_inconsistent_events++;
	if(digiword>temword) inconsistent=1;
	  else inconsistent=-1;
	  }
   plot->Fill(TMath::Log2(digiword), TMath::Log2(temword));
   analysis->Fill();
   }

file.cd();
analysis->Write();
svac->SetBranchStatus("*", 1);

dplot = new TCanvas("d", title);
dplot->SetLogz(1);
(plot->GetXaxis())->SetTitleSize(0.035);
(plot->GetYaxis())->SetTitleSize(0.035);
plot->SetXTitle("Log2(Digis Bitword)");
plot->SetYTitle("Log2(TEM Bitword) *");
plot->Draw("surf23z");
dplot->Print("logconsistency.gif");

cplot = new TCanvas(title, title);

plot->SetMarkerStyle(2);
(plot->GetXaxis())->SetTitleSize(0.045);
(plot->GetYaxis())->SetTitleSize(0.045);
plot->SetXTitle("Log2(Digis Bitword)");
plot->SetYTitle("Log2(TEM Bitword) *");
plot->DrawCopy();
cplot->Print("consistency.gif");


cout<<"Number of Inconsistent events: "<<n_inconsistent_events<<" out of "<<nentries<<endl;
}

void word_to_array(int word, int *array){
//! Purpose = to convert a bitword in an array of 0s and 1s
for(int i=0; i<16; i++)
   if((word&2**i)>0) array[i]=1;
     else array[i]=0;
}


int array_to_word(int *array){
//! Purpose = to convert an array of 0s and 1s into a bitword
int word=0;
for(int i=0; i<16; i++)
   if(array[i]==1)
      word |= (int)pow(2, i);

return word;
}


void inconsistency(int digiword, int temword, int run, int id){

/** inconsistency function:
    The purpose is to produce a plot to check the difference of the digi and temword in
    terms of the active/inactive combinations. Hard to explain with words, just make
    a plot and it will become clear.
    */

char *title = (char*)malloc(50*sizeof(char));
sprintf(title, "Run=%d  Event_ID=%d ||| Digi=%d  Svac=%d", run, id, digiword, temword);

//if(hdigi) hdigi->Delete();
//if(hsvac) hsvac->Delete();

TH1F *hdigi = new TH1F("hdigi", title, 16, -0.5, 15.5);
TH1F *hsvac = new TH1F("hsvac", title, 16, -0.5, 15.5);
TCanvas *c1 = new TCanvas("c1", "Inconsistency Plot");
c1->DrawFrame(-1., 0., 16., 1.7, title);

int svac_array[16], digi_array[16];

word_to_array(digiword, digi_array);
word_to_array(temword, svac_array);

for(int i=0; i<16; i++){
   if(digi_array[i]==1) hdigi->Fill(i);
   if(svac_array[i]==1) hsvac->Fill(i);
   }

hdigi->SetBarWidth(0.40);
hdigi->SetBarOffset(0.15);
hdigi->SetFillColor(49);
hdigi->DrawCopy("bar2, same");
hsvac->SetBarWidth(0.35);
hsvac->SetBarOffset(0.55);
hsvac->SetFillColor(50);
hsvac->DrawCopy("bar2,same");

TLegend *legend = new TLegend(0.70,0.72,0.85,0.82);
legend->AddEntry(hdigi,"Digi","f");
legend->AddEntry(hsvac,"TEM","f");
legend->Draw();
}
