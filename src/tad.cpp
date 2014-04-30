/* Prueba:
    - ALTURA, NODOS, NODOSHOJA   
*/

#include <iostream>
#include "tabbcom.h"
#include "tcomplejo.h"
#include "tvectorcom.h"
using namespace std;

int
main(void)
{

  
  TABBCom a;
 
  TComplejo c100(100, 1);
  TComplejo c50(50, 1);
  TComplejo c20(20, 1);
  TComplejo c110(110, 1);
 
  cout << a.Borrar(c100) << endl;
  cout <<"Altura: "<<a.Altura()<<endl;
  cout <<"Nodos: "<<a.Nodos()<<endl;
  cout <<"NodosHoja: "<<a.NodosHoja()<<endl;
  cout <<"Raiz: "<<a.Raiz()<<endl;

  cout << a.Insertar(c100) << endl;
  cout << a.Buscar(c100) << endl;
  cout << a.Buscar(c50) << endl;
  cout << a.Insertar(c100) << endl;
  cout <<"Altura: "<<a.Altura()<<endl;
  cout <<"Nodos: "<<a.Nodos()<<endl;
  cout <<"NodosHoja: "<<a.NodosHoja()<<endl;
  cout <<"Raiz: "<<a.Raiz()<<endl;

  a.Insertar(c50);
  cout <<"Altura: "<<a.Altura()<<endl;
  cout <<"Nodos: "<<a.Nodos()<<endl;
  cout <<"NodosHoja: "<<a.NodosHoja()<<endl;
  cout <<"Raiz: "<<a.Raiz()<<endl;

  a.Insertar(c20);
  cout <<"Altura: "<<a.Altura()<<endl;
  cout <<"Nodos: "<<a.Nodos()<<endl;
  cout <<"NodosHoja: "<<a.NodosHoja()<<endl;
  cout <<"Raiz: "<<a.Raiz()<<endl;

  a.Insertar(c110);
  cout <<"Altura: "<<a.Altura()<<endl;
  cout <<"Nodos: "<<a.Nodos()<<endl;
  cout <<"NodosHoja: "<<a.NodosHoja()<<endl;
  cout <<"Raiz: "<<a.Raiz()<<endl;

  cout << a.Borrar(c20) << endl;
  cout << a.Borrar(c20) << endl;
  cout <<"Altura: "<<a.Altura()<<endl;
  cout <<"Nodos: "<<a.Nodos()<<endl;
  cout <<"NodosHoja: "<<a.NodosHoja()<<endl;
  cout <<"Raiz: "<<a.Raiz()<<endl;

  TABBCom ordenes;
  TComplejo a1(1,0);
  TComplejo a2(2,0);
  TComplejo a3(3,0);
  TComplejo a4(4,0);
  TComplejo a5(5,0);
  TComplejo a6(6,0);
  TComplejo a7(7,0);

  cout << ordenes.Insertar(a4) << endl;
  cout << ordenes.Insertar(a2) << endl;
  cout << ordenes.Insertar(a6) << endl;
  cout << ordenes.Insertar(a1) << endl;
  cout << ordenes.Insertar(a3) << endl;
  cout << ordenes.Insertar(a5) << endl;
  cout << ordenes.Insertar(a7) << endl;

  cout << ordenes.Inorden() << endl;
  cout << ordenes.Preorden() << endl;
  cout << ordenes.Postorden() << endl;
  cout << ordenes.Niveles() << endl;
  cout << "pene" << endl;
  cout << ordenes << endl;

  return 1; 

}
