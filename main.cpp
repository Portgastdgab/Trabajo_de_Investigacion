#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include<sstream>


using namespace std;
using namespace NTL;

int Euclides_clasico() {
ZZ module(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

ZZ empower(ZZ a, ZZ x){
    ZZ reply = a;
    for(ZZ i = ZZ(1); i < x; i++){
        reply = a*reply;
    }
    return reply;
}

ZZ RandomNumber(int bits) {
    //[2n−1,2n-1]
    ZZ begin = empower(ZZ(2), ZZ(bits-1));
    ZZ end = empower(ZZ(2), ZZ(bits)) - 1;
    return  RandomBnd(end - begin + 1) + begin;
}

ZZ min(ZZ a,ZZ b){
    return (a <b)? a:b;
}

string ZZtoStr(ZZ a){
    stringstream temp;
    temp<<a;
    return temp.str();
}
ZZ Euclides_clasico(ZZ D,ZZ d){
    // D=d*q+r
    if(D == 0 ) return d;
    while(d != 0){
        ZZ r = module(D,d);
        D = d;
        d = r;
        //cout<<"\n "<<D<<" = "<<d<<" - "<<r;
    }
    return D;
}

ZZ menorResto(ZZ a,ZZ b){
    return min(abs(a-b*(a/b)),abs(a-b*((a/b) + 1)));
}


ZZ Euclides_con_menor_resto(ZZ D,ZZ d){
    // D=d*q+ min(r1,r2)
    if(D == 0 ) return d;
    while(d != 0){
        ZZ r = menorResto(D,d);
        //cout<<"\n "<<D<<" = "<<d<<" - "<<r;
        D = d;
        d = r;
    }

    return D;
}



ZZ binario_del_mcd(ZZ a ,ZZ b) {
    ZZ k (1);
    // Regla 1 : a,b pares
    while(module(a,ZZ(2)) == 0  && module(b,ZZ(2))== 0 ){
        a/=2;
        b/=2;
        k*=2;
        //cout<<"\nmcd( "<<a<<" , "<<b<<" )";
    }
    while(a !=0){
        //Regla 2 : a,b alguno par
        if(module(a,ZZ(2))==0){
            a/=2;
        }
        else if(module(b,ZZ(2))==0){
            b/=2;
        }
        //Regla 3 a,b impares
        else{

            ZZ temp = abs(a-b)/2;
            b = min(a,b);
            a = temp;
        }
        //cout<<"\nmcd( "<<a<<" , "<<b<<" )";
    }
    return k*b;
}



ZZ Lehmer_del_mcd(ZZ U,ZZ V,ZZ p){

    ZZ H (empower(ZZ(10),p));

    while(  V >= H ){
        //Initialize
        ZZ k, u, v, A, B, C, D, q0, q1, T, t, w;
        k = ZZtoStr(U).size() - p;
        u = U / empower(ZZ(10), k);
        v = V / empower(ZZ(10), k);
        A = 1; B = 0; C = 0; D = 1;

        while (v+C != 0 &&  v+D != 0) {

            //Test quotient
            q0 = (u + A) / (v + C);
            q1 = (u + B) / (v + D);

            if (q0 != q1)
                break;

            //Emulate Euclid
            T = A - q0 * C;  A = C;  C = T;
            T = B - q0 * D;  B = D;  D = T;
            T = u - q0 * v;  u = v;  v = T;
        }

        //Multiprecision step
        if( B == 0){

            t = module(U,V);
            U = V;
            V = t;

        }else{

            t = A*U + B*V;
            w = C*U + D*V;
            U = t;
            V = w;
        }

        if(V == 0)
            return U;

        cout<<"\n"<<A<<" "<<B<<" "<<C<<" "<<D<<endl;
    }
    cout<<"\nuv: "<<U<<" "<<V<<"\n";

    // if v is small to be represented as a single-precision use gcd()
    return Euclides_con_menor_resto(U,V);
}





/*
int Otro_algoritmo_que_sugiera() {

}*/



int main() {

    /* initialize random seed: */


    //Euclides_clásico();

    int n_bits = 8;

    ZZ a = ZZ(27182818);
    ZZ b = ZZ(10000000);

    /*
    ZZ a = RandomNumber(64);
    ZZ b = RandomNumber(64);*/



    cout<<"\na: "<<a;
    cout<<"\nb: "<<b;
    cout<<"\nEuclides classic: "<<Euclides_clasico(a,b);
    cout<<"\nEuclides menorRes: "<<Euclides_con_menor_resto(a,b);
    cout<<"\nMCD binario: "<<binario_del_mcd(a,b);
    cout<<"\nMCD Lehmer: "<<Lehmer_del_mcd(a,b,ZZ(4));

    cout<<endl;

//    Euclides_con_menor_resto();
//    binario_del_mcd();
//    Lehmer_del_mcd();
//    Otro_algoritmo_que_sugiera();


}
