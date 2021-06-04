#include <iostream>
#include <NTL/ZZ.h>
#include <string>
#include<sstream>

using namespace std;
using namespace NTL;

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

string ZZtoStr(ZZ a){
    stringstream temp;
    temp<<a;
    return temp.str();
}

void Euclides_clasico(ZZ &a, ZZ &b){
    ZZ temp_a = a;
    ZZ temp_b = b;
    while (module(temp_a, temp_b) != 0){
        ZZ temp = temp_b;
        temp_b = module(temp_a, temp_b);
        temp_a = temp;
    }
    cout<<temp_b;
}

void Euclides_menor_resto(ZZ &a, ZZ &b){
    while (module(a,b) != 0){
        ZZ temp = abs(b);
        ZZ r =  abs(a - b * (a/b+(module(a,b)>=b/2)));
        b = r;
        a = temp;
    }
    cout<<b;
}

void binario(ZZ &u,ZZ &v){
    ZZ t, g, a, b;
    g=1;
    a=abs(u);
    b=abs(v);
    while(a%2==0 && b%2==0){
        a=a/2;
        b=b/2;
        g=2*g;
    }
    while(a!=0){
        if(a%2==0){
            a=a/2;
        }else if(b%2==0){
            b=b/2;
        }else{
            t=abs(a-b)/2;
            if(a>= b){
                a=t;
            }else{
                b=t;
            }
        }
    }
    cout<<g*b;
}
int Lehmer_del_mcd(ZZ &U,ZZ &V,ZZ p){

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
            cout<<U;
    }
    // if v is small to be represented as a single-precision use gcd()
    binario(U,V);
}

int main() {
    ZZ a = conv <ZZ> ("32317756071311007300714876688669951960444102669715484032130345427524655138867890893197201411522913463688717960921898019494119559150490921095088152386448283120630877367300996091750197750389652106796057638384067568276792218642619756161838094338476170470581645852036305042887575891541065808607552399123930385521914333389668342420684974786564569494856176035326322058077805659331026192708460314150258592864177116725943603718461857357598351152301645904403697613233287231227125684710820209725157101726931323469678542580656697935045997268352998638215525166389437335543602135433229604645318478604952148193555853611059596230655");
    ZZ b = conv <ZZ> ("27458503035655503650357438344334975980275351334857742016065172713762327569433945446598600705761456731844358980460949009747059779575245460547544076193224141560315438683650498045875098875194826053398028819192033784138396109321309878080919047169238085235290822926018152521443787945770532904303776199561965192760957166694834171210342487393282284747428088017663161029038902829665513096354230157075129296432088558362971801859230928678799175576150822952201848806616643615613562842355410104862578550863465661734839271290328348967522998634176499319107762583194718667771801067716614802322659239302476074096777926805529798115328");
    Lehmer_del_mcd(a, b, ZZ(120));
}
