<<<<<<< HEAD

=======
#include <iostream>
#include<stdlib.h>
#include<time.h>
#include <cmath>

using namespace std;

int bits(int bits) {
    int begin = pow(2, bits)/2, end = pow(2, bits)-1;
    srand(time(NULL));
    return begin + rand() % (end - begin);
}

int module(int a, int n){
    int r = a-n*(a/n);
    r = r+(r<0)*n;
    return r;
}

void Euclides_clasico(int a, int b){
    int temp_a = a;
    int temp_b = b;
    while (module(temp_a, temp_b) != 0){
        int temp = temp_b;
        temp_b = module(temp_a, temp_b);
        temp_a = temp;
    }
    cout<<"mcd("<<a<<", "<<b<<") = "<<temp_b;
}
void Euclides_con_menor_resto(int a, int b){
    cout<<"mcd("<<a<<", "<<b<<") = ";

}
void binario_del_mcd(int a, int b){
    cout<<"mcd("<<a<<", "<<b<<") = ";
}
void Lehmer_del_mcd(int a, int b){
    cout<<"mcd("<<a<<", "<<b<<") = ";
}
void Otro_algoritmo_que_sugiera(int a, int b){
    cout<<"mcd("<<a<<", "<<b<<") = ";
}
int main() {
    int n_bits = 10;
    int a = bits(n_bits);
    int b = a*0.941852963;
    cout<<a<<"     "<<b<<endl;
    Euclides_clasico(a, b);
}
>>>>>>> 4d197e91f076b9924e8de6d20beaec6f1be85b57
