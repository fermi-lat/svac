void getConfigKey (char *digiFileName, char* latcKeyFineName) {

  // Name of the input digi file:
  TFile *digiFile = new TFile(digiFileName);

  // Output file with LATC key:
  ofstream latcKeyFile;
  latcKeyFile.open(latcKeyFineName,std::ios::trunc);
  
  // Get the digi:
  DigiEvent *evt = 0;
  TTree *t = (TTree*)digiFile->Get("Digi");
  t->SetBranchAddress("DigiEvent", &evt);


  // See if file is non-empty:
  int nEvt = (int) t->GetEntries(); 

  if (nEvt > 0) {

    // Get the first event: It doesn't matter that it is a sweep event!
    t->GetEvent(0);

    // Get the LATC key:
    unsigned int latckey = evt->getMetaEvent().keys()->LATC_master();

    // Write out the LATC key value:
    //std::cout << "The LatC key is " << latckey << std::endl;
    latcKeyFile << latckey << std::endl;

    evt->Clear(); 
  } else {

    // Empty digi file i.e. no LATC key!
    int latckey = -1;
    latcKeyFile << latckey << std::endl;
  }

  // Close the output file:
  latcKeyFile.close();
}
