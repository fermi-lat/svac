#!/usr/local/bin/perl -w
# C 2007, Martin Kocian, SLAC

print "Interactive program to create a new monitoring input object\n\n";
print "Name of the object: ";
$name=<>;
chomp($name);
while (-e "MonInput_$name.h"){
    print "An object of that name exists already. Try a different name: ";
    $name=<>;
    chomp($name);
}
print "One-line description of object: ";
$description=<>;
chomp($description);
print "What type of variable is this?\n";
print "0 for Int_t\n";
print "1 for Bool_t\n";
print "2 for UInt_t\n";
print "3 for Double_t\n";
print "4 for ULong_t\n";
print "5 for UShort_t\n";
print "6 for Float_t\n";
print "7 for Char_t\n";
print "8 for Short_t\n";
print "9 for Long64_t\n";
print "10 for ULong64_t\n";
$type=<>;
chomp($type);
while ($type =~ /\D/ || $type<0 || $type>10){
    print "Invalid input. Try again...\n";
    print "0 for Int_t\n";
    print "1 for Bool_t\n";
    print "2 for UInt_t\n";
    print "3 for Double_t\n";
    print "4 for ULong_t\n";
    print "5 for UShort_t\n";
    print "6 for Float_t\n";
    print "7 for Char_t\n";
    print "8 for Short_t\n";
    print "9 for Long64_t\n";
    print "10 for ULong64_t\n";
    $type=<>;
    chomp($type);
}
if ($type==0){
    $ctype="Int_t";
    $ntype="I";
}elsif ($type==1){
    $ctype="Bool_t";
    $ntype="O";
}elsif ($type==2){
    $ctype="UInt_t";
    $ntype="i";
}elsif ($type==3){
    $ctype="Double_t";
    $ntype="D";
}elsif ($type==4){
    $ctype="ULong_t";
    $ntype="i";
}elsif ($type==5){
    $ctype="UShort_t";
    $ntype="s";
}elsif ($type==6){
    $ctype="Float_t";
    $ntype="F";
}elsif ($type==7){
    $ctype="Char_t";
    $ntype="B";
}elsif ($type==8){
    $ctype="Short_t";
    $ntype="S";
}elsif ($type==9){
    $ctype="Long64_t";
    $ntype="L";
}elsif ($type==10){
    $ctype="ULong64_t";
    $ntype="l";
}else{
    print "No such type.\n";
    exit(0);
}
print "What tree is the source of the data?\n";
print "0 for DigiEvent\n";
print "1 for ReconEvent\n";
print "2 for McEvent\n";
print "3 for MeritEvent\n";
print "4 for SvacEvent\n";
print "5 for CalEvent\n";
$source=<>;
chomp($source);
while ($source =~ /\D/ || $source<0 || $source>5){
    print "Invalid entry. Try again.\n";
    print "0 for DigiEvent\n";
    print "1 for ReconEvent\n";
    print "2 for McEvent\n";
    print "3 for MeritEvent\n";
    print "4 for SvacEvent\n";
    print "5 for CalEvent\n";
    $source=<>;
    chomp($source);
}
if ($source==0){
    $monsource="DigiEvent";
    $monsourcefile="#include \"digiRootData/DigiEvent.h\"";
    $subdir="digi";
}elsif($source==1){
    $monsource="ReconEvent";
    $monsourcefile="#include \"reconRootData/ReconEvent.h\"";
    $subdir="recon";
}elsif($source==2){
    $monsource="McEvent";
    $monsourcefile="#include \"mcRootData/McEvent.h\"";
    $subdir="mc";
}elsif($source==3){
    $monsource="MeritEvent";
    $monsourcefile="";
    $subdir="merit";
}elsif($source==4){
    $monsource="SvacEvent";
    $monsourcefile="";
    $subdir="svac";
}else{
    $monsource="CalEvent";
    $monsourcefile="";
    $subdir="cal";
}
	
print "What branch of the tree has to be activated?\n";
$inbranch=<>;
chomp($inbranch);
print "What is the function to access the quantity in the tree?\n";
print $monsource."->";
$access=<>;
chomp($access);
print "Create new object (y/n)?\n";
$ans=<>;
if (!($ans =~/[yY]/)){
    print "No object created. Exiting.\n";
    exit(0);
}
$user=$ENV{"USER"};
$date=gmtime;
open(HFILE,">${subdir}/MonInput_$name.h");
print HFILE "// 
// Class for input of quantity $name for monitoring 
// 
// Created by $user on $date 
// Object created automatically by script makeNewMonObject.pl
//
#ifndef MonInput_${name}_h
#define MonInput_${name}_h
#include \"../MonInputObject.h\"
#include \"Rtypes.h\"
#include \"TTree.h\"
#include \"TObject.h\"

// user defined part

#define VARTYPE $ctype 

// end user defined part

class MonInput_$name: public MonInputObject{
 public:
  MonInput_$name();
  ~MonInput_$name();
  int setOutputBranch(TTree*);
  void enableInputBranch(TTree&);
  void setValue(TObject* event) ;
  std::string getInputSource();
  std::string getDescription();
 private:
  VARTYPE m_val;
};

#undef VARTYPE
#endif
\n";
close(HFILE);

open(CFILE,">${subdir}/MonInput_$name.cxx");
print CFILE "// 
// Class for input of quantity $name for monitoring 
// 
// Created by $user on $date 
// Object created automatically by script makeNewMonObject.pl
//
#include \"MonInput_$name.h\"
#include <iostream>

// User defined part 

#define NAME $name
#define OUTBRANCH \"$name\"
#define LEAF \"$name/$ntype\"
#define INBRANCH \"$inbranch\"
#define ACCESSOR $access
#define MONSOURCE $monsource
#define INPUTSOURCE \"$monsource\"
#define DESCRIPTION \"$description\"
$monsourcefile

// End user defined part 

MonInput_${name}::MonInput_$name(){
  m_name=OUTBRANCH;
}
MonInput_${name}::~MonInput_$name(){
}


int MonInput_${name}::setOutputBranch(TTree* tree) {
 TBranch* bErr= tree->Branch(OUTBRANCH,&m_val,LEAF);
 return bErr != 0 ? 0 : 1;
}
void MonInput_${name}::enableInputBranch(TTree& tree){
  tree.SetBranchStatus(INBRANCH,1);
";
if($monsource eq "SvacEvent" || $monsource eq "MeritEvent" || $monsource eq "CalEvent"){
    print CFILE "  tree.SetBranchAddress(INBRANCH,&m_val);\n";
}
print CFILE "}
void MonInput_${name}::setValue(TObject* event) {\n";
if ($monsource eq "DigiEvent" || $monsource eq "ReconEvent" || $monsource eq "McEvent"){
print CFILE "  MONSOURCE* de=dynamic_cast<MONSOURCE*>(event);
  if (de==0){
    std::cerr<<\"Using object \"<<OUTBRANCH<<\" with wrong kind of data tree (like digi, reco, etc.)\"<<std::endl;
    assert(de);
  }
  m_val= de->ACCESSOR;\n";
}
print CFILE "}
std::string MonInput_${name}::getInputSource(){
  return INPUTSOURCE;
}
std::string MonInput_${name}::getDescription(){
  return DESCRIPTION;
}

#undef INPUTSOURCE
#undef NAME
#undef OUTBRANCH
#undef LEAF
#undef INBRANCH 
#undef ACCESSOR
#undef MONSOURCE
#undef DESCRIPTION
\n";
close(CFILE);

print "Update MonObjectFactory.cxx ?\n";
$ans=<>;
if ($ans =~/[yY]/){
    rename("MonObjFactory.cxx","MonObjFactory.cxx~");
    open (FIN,"MonObjFactory.cxx~");
    open (FOUT,">MonObjFactory.cxx");
    $line=<FIN>;
    while($line =~/\/\//){
	print FOUT $line;
	$line=<FIN>;
    }
    print FOUT "// Last updated with object $name by user $user on $date\n";
    print FOUT "#include \"${subdir}/MonInput_$name.h\"\n";
    print FOUT $line;
    $line=<FIN>;
    while(!($line =~/tag for makeNewMonObject/)){
	print FOUT $line;
	$line=<FIN>;
    }
    print FOUT "  if (s==\"$name\")\n";
    print FOUT "    return new MonInput_$name;\n";
    print FOUT $line;
    $line=<FIN>;
    while(!($line =~/tag used by makeNewMonObject/)){
	print FOUT $line;
	$line=<FIN>;
    }
    print FOUT "  names.push_back(\"$name\");\n";
    print FOUT $line;
    $line=<FIN>;
    while (!eof(FIN)){
	print FOUT $line;
	$line=<FIN>;
    }
    print FOUT $line;
    close(FIN);
    close(FOUT);
    print "You are now ready to compile. Good luck...\n";
}
