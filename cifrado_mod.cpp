#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<string.h>
using namespace std;
class afin{
	private:
	string alfabeto="abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ.,_-0123456789";
	int m=alfabeto.size(),inver;
	public:
	long long clave1,clave2;
	private:
	long long mod(long long a,long long b){
		int r=a-(a/b)*b;
		return (r>=0)*r+(r<0)*(r+b);
	}
	long long gcd(long long a,long long b){
		if(a<b){
			long long tmp=a;
			a=b;
			b=tmp;
		}
		else if(a==b){
			return a;
		}
		long long r;
		while(b>0){
			r=a-b*(a/b);
			a=b;
			b=r;
		}
		return a;
	}
	void cal_inversa(long long a,int b){
		long long r1=a,r2=m;
		long long s1=1,s2=0;
		long long t,q;
		while(r2>0){
			q=r1/r2;
			t=r1-q*r2;
			r1=r2;r2=t;
			t=s1-q*s2;
			s1=s2;s2=t;
		}
		inver=s1;
		clave2=b;
	}
	void Generar_claves(){
		srand(time(NULL));
		bool b=1;
		while(b){
			clave1=rand()%100000;
			clave2=rand()%100000;
			b=(gcd(clave1,m)!=1);
		}
	}
	public:
	afin(){
		Generar_claves();
	}
	afin(long long a,long long b){
		cal_inversa(a,b);
	}
	string Cifrar(string p){
		for(int i=0;i<p.size();i++){
			long long r=alfabeto.find(p[i]);
			r=mod((r*clave1)+clave2,m);
			p[i]=alfabeto[r];
		}
		return p;
	}
	string Descifrar(string p){
		for(int i=0;i<p.size();i++){
			long long r=alfabeto.find(p[i]);
			r=mod(mod(r-clave2,m)*inver,m);
			p[i]=alfabeto[r];
		}
		return p;
	}
};
int main(){
	char oracion[1000];
	cin.getline(oracion,1000);
	string p(oracion);
	long long clave1,clave2;
	afin a;
	cout<<a.clave1<<endl<<a.clave2<<endl;
	afin b(a.clave1,a.clave2);
	p=a.Cifrar(p);
	//cout<<p<<endl;
	//p=b.Descifrar(p);
	cout<<p<<endl;
	cout<<b.Descifrar(p)<<endl;
	return 0;
}
