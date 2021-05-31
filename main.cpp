#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <cmath>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

ZZ module(ZZ a, ZZ n){
    ZZ r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

ZZ empower(ZZ a, int x){
    ZZ b = ZZ(x);
    ZZ reply = a;
    for(ZZ i = ZZ(1); i < b; i++){
        reply = a*reply;
    }
    return reply;
}

ZZ bits(int bits) {
    ZZ begin = empower(ZZ(2), bits)/ZZ(2), end = empower(ZZ(2), bits);
    srand(time(NULL));
    return begin + module(ZZ(rand()), (end - begin));
}

void Euclides_clasico(ZZ a, ZZ b){
    ZZ temp_a = a;
    ZZ temp_b = b;
    while (module(temp_a, temp_b) != 0){
        ZZ temp = temp_b;
        temp_b = module(temp_a, temp_b);
        temp_a = temp;
    }
    cout<<"mcd("<<a<<", "<<b<<") = "<<temp_b;
}
void Euclides_con_menor_resto(ZZ a, ZZ b){
    cout<<"mcd("<<a<<", "<<b<<") = ";

}
void binario_del_mcd(ZZ a, ZZ b){
    cout<<"mcd("<<a<<", "<<b<<") = ";
}
void Lehmer_del_mcd(ZZ a, ZZ b){
    cout<<"mcd("<<a<<", "<<b<<") = ";
}
void Otro_algoritmo_que_sugiera(ZZ a, ZZ b){
    cout<<"mcd("<<a<<", "<<b<<") = ";
}
int main() {
    int n_bits = 1024;
    ZZ a = bits(n_bits);
    ZZ b = bits(n_bits);
    while(b == a){
        b = bits(n_bits);
    }
    Euclides_clasico(a, b);
}
