#include <iostream>

using namespace std;

#include "tcomplejo.h"

int
main(void)
{
  TComplejo a(1,2);
  TComplejo b(a);
  
  if( a.Mod() == b.Mod() )
    cout << "SI" << endl;
  else
    cout << "NO" << endl;

  b.Re(2);
  b.Im(3);

  if( a.Mod() == b.Mod() )
    cout << "SI" << endl;
  else
    cout << "NO" << endl;

  return 0;
}
