#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <iostream>

class Funciones{

public:

	long sumaIterativa(int n){
	int suma = 0;
	for(int i = 0; i <= n; i++){
		suma = suma + i;
	}
	return suma;
	}

	long sumaDirecta(int n){

		if (n == 1){
			return 1;
		}
		else{

			int mitad = n/2;
			int resul = (n* mitad)+ mitad ;

			return resul; 
			}
		}
		

	long sumaRecursiva(int n){
		if (n == 1 ){
			return 1;
		}
		else if(n == 0) {
			return 0;
		}
		else{
			return sumaRecursiva(n-1)+n;
		}
		
	}

};

#endif

