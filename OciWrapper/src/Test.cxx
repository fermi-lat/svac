#include <iostream>
#include "OCIWrapper.h"

using namespace std;

int main() {

  OCIWrapper db("slac_tcp", "GLAST_CAL", "9square#");

  OCIStmt* stmtH = db.prepareStatement("select * from test");

  int x, y;

  db.defineIntByPos(stmtH, &x, 1);
  db.defineIntByPos(stmtH, &y, 2);

  db.executeStatement(stmtH, 0);

  while(db.fetchNextRow(stmtH)) {

    cout << "x = " << x << " y = " << y << endl;

  }
}
