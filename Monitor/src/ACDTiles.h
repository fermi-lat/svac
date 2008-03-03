int toptiles(int index1, int index2){
  int ttile=-1;

  //Top Tiles
  if (index1==0 && index2==0){ttile=0;}
  if (index1==1 && index2==0){ttile=1;}
  if (index1==2 && index2==0){ttile=2;}
  if (index1==3 && index2==0){ttile=3;}
  if (index1==4 && index2==0){ttile=4;}
  if (index1==0 && index2==1){ttile=10;}
  if (index1==1 && index2==1){ttile=11;}
  if (index1==2 && index2==1){ttile=12;}
  if (index1==3 && index2==1){ttile=13;}
  if (index1==4 && index2==1){ttile=14;}
  if (index1==0 && index2==2){ttile=20;}
  if (index1==1 && index2==2){ttile=21;}
  if (index1==2 && index2==2){ttile=22;}
  if (index1==3 && index2==2){ttile=23;}
  if (index1==4 && index2==2){ttile=24;}
  if (index1==0 && index2==3){ttile=30;}
  if (index1==1 && index2==3){ttile=31;}
  if (index1==2 && index2==3){ttile=32;}
  if (index1==3 && index2==3){ttile=33;}
  if (index1==4 && index2==3){ttile=34;}
  if (index1==0 && index2==4){ttile=40;}
  if (index1==1 && index2==4){ttile=41;}
  if (index1==2 && index2==4){ttile=42;}
  if (index1==3 && index2==4){ttile=43;}
  if (index1==4 && index2==4){ttile=44;}

  return ttile;
}



int side1tiles(int index1, int index2){
  int stile1=-1;

  //Side 1  Tiles
  if (index1==0 && index2==0){stile1=120;}
  if (index1==0 && index2==1){stile1=121;}
  if (index1==0 && index2==2){stile1=122;}
  if (index1==0 && index2==3){stile1=123;}
  if (index1==0 && index2==4){stile1=124;}
  if (index1==1 && index2==0){stile1=110;}
  if (index1==1 && index2==1){stile1=111;}
  if (index1==1 && index2==2){stile1=112;}
  if (index1==1 && index2==3){stile1=113;}
  if (index1==1 && index2==4){stile1=114;}
  if (index1==2 && index2==0){stile1=100;}
  if (index1==2 && index2==1){stile1=101;}
  if (index1==2 && index2==2){stile1=102;}
  if (index1==2 && index2==3){stile1=103;}
  if (index1==2 && index2==4){stile1=104;}

  return stile1;
}


int side2tiles(int index1, int index2){
  int stile2=-1;

  //Side 2  Tiles
  if (index1==0 && index2==0){stile2=220;}
  if (index1==0 && index2==1){stile2=221;}
  if (index1==0 && index2==2){stile2=222;}
  if (index1==0 && index2==3){stile2=223;}
  if (index1==0 && index2==4){stile2=224;}
  if (index1==1 && index2==0){stile2=210;}
  if (index1==1 && index2==1){stile2=211;}
  if (index1==1 && index2==2){stile2=212;}
  if (index1==1 && index2==3){stile2=213;}
  if (index1==1 && index2==4){stile2=214;}
  if (index1==2 && index2==0){stile2=200;}
  if (index1==2 && index2==1){stile2=201;}
  if (index1==2 && index2==2){stile2=202;}
  if (index1==2 && index2==3){stile2=203;}
  if (index1==2 && index2==4){stile2=204;}

  return stile2;
}


int side3tiles(int index1, int index2){
  int stile3=-1;

  //Side 3  Tiles
  if (index1==0 && index2==0){stile3=300;}
  if (index1==0 && index2==1){stile3=301;}
  if (index1==0 && index2==2){stile3=302;}
  if (index1==0 && index2==3){stile3=303;}
  if (index1==0 && index2==4){stile3=304;}
  if (index1==1 && index2==0){stile3=310;}
  if (index1==1 && index2==1){stile3=311;}
  if (index1==1 && index2==2){stile3=312;}
  if (index1==1 && index2==3){stile3=313;}
  if (index1==1 && index2==4){stile3=314;}
  if (index1==2 && index2==0){stile3=320;}
  if (index1==2 && index2==1){stile3=321;}
  if (index1==2 && index2==2){stile3=322;}
  if (index1==2 && index2==3){stile3=323;}
  if (index1==2 && index2==4){stile3=324;}

  return stile3;
}



int side4tiles(int index1, int index2){
  int stile4=-1;

  //Side 4  Tiles
  if (index1==0 && index2==0){stile4=400;}
  if (index1==0 && index2==1){stile4=401;}
  if (index1==0 && index2==2){stile4=402;}
  if (index1==0 && index2==3){stile4=403;}
  if (index1==0 && index2==4){stile4=404;}
  if (index1==1 && index2==0){stile4=410;}
  if (index1==1 && index2==1){stile4=411;}
  if (index1==1 && index2==2){stile4=412;}
  if (index1==1 && index2==3){stile4=413;}
  if (index1==1 && index2==4){stile4=414;}
  if (index1==2 && index2==0){stile4=420;}
  if (index1==2 && index2==1){stile4=421;}
  if (index1==2 && index2==2){stile4=422;}
  if (index1==2 && index2==3){stile4=423;}
  if (index1==2 && index2==4){stile4=424;}

  return stile4;
}




int singletiles(int index1){
  int singlet=-1;

  // Single Side  Tiles
  if (index1==0){singlet=130;}
  if (index1==1){singlet=230;}
  if (index1==2){singlet=330;}
  if (index1==3){singlet=430;}

  return singlet;
}


