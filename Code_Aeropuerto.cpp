#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
class cAvion{
private:
    int hv, fabric, hm , tipo,codigo;
    char modelo[12];
    char marca[12];
public:
    cAvion();
    int getcodigo();
    int mante();
    virtual void leer();
    virtual void mostrar();
    int gettipo();
    void settipo(int x);
};
int cAvion :: mante(){
    int m = 0;
    if (hv > hm){
        m = 1;
    }
    return m;
}
void cAvion :: leer(){
    cout << "Ingrese el codigo del avion: "; 
	cin >> codigo;
    cout << "Ingrese la marca del avion: "; 
	cin >> marca;
    cout << "Ingrese el modelo del avion: "; 
	cin >> modelo;
    cout << "Ingrese el a�o de fabricaion del avion: "; 
	cin >> fabric;
    cout << "Ingrese las horas de vuelo del avion: "; 
	cin >> hv;
    cout << "Ingrese las horas de vuelo sin mantenimiento del avion: "; 
	cin >> hm;
}
void cAvion :: mostrar(){
    cout << "El codigo del avion es: " << codigo << endl;
    cout << "La marca del avion es: " << marca << endl;
    cout << "El modelo del avion es: " << modelo << endl;
    cout << "El a�o de fabricacion del avion es: " << fabric << endl;
    cout << "Las horas de vuelo del avion son: " << hv << endl;
    cout << "Las horas de vuelo sin matenimiento del avion son: " << hm << endl;
}
int cAvion :: gettipo(){
    return tipo;
}
void cAvion :: settipo(int x){
    tipo = x;
}
cAvion :: cAvion(){
    codigo = 0;
    hv = 0;
    hm = 0;
    fabric = 0;
    strcpy(modelo, " ");
    strcpy(marca, " ");
}
int cAvion::getcodigo(){
	return (codigo);
}
class cTurista : public cAvion{
private:
    int vip, tur;
public:
    void leer();
    void mostrar();
    int totala();
    cTurista();
   
};
int cTurista::totala(){
	int x=vip+tur;
	return (x);
}
void cTurista :: leer(){
    cAvion :: leer();
    cout << "asientos VIP: "; cin>> vip;
    cout << "asientos TURISTAS: "; cin>> tur;
    cout << endl;
}
void cTurista :: mostrar(){
    cAvion :: mostrar();
    cout <<"El numero de asientos VIP del avion son: "<<vip<<endl;
    cout << "El numero de asientos para TURISTAS del avion son: "<<tur<<endl;
    cout << endl;
}
cTurista :: cTurista() : cAvion(){
    vip = 0;
    tur = 0;
    settipo(1);
}
class cComercial : public cAvion{
private:
    int carga, toneladas;
public:
    void leer();
    void mostrar();
    cComercial();
    int getCarga();
};
int cComercial::getCarga(){
	return (carga);
}
void cComercial :: leer(){
    cAvion :: leer();
    cout <<"Ingrese la capacidad de carga de avion: "; cin >> carga;
    cout<<"ingrese las toneladas de peso: "; cin>>toneladas;
    cout << endl;
    cout << endl;
}
void cComercial :: mostrar(){
    cAvion :: mostrar();
    cout << "La Capacidad de Carga del avion es: " <<carga<<endl;
    cout << endl;
}
cComercial :: cComercial() : cAvion(){
    carga = 0;
    toneladas=0;
    settipo(2);
}
class cAeropuerto {
private:
    char nombre[20];
    char ciudad[20];
    int nAD, nAM;
    cAvion* Ad[100];
    cAvion* Am[100];
public:
    void leer();
    void mostrar();
    void clasificar();
    void recorrerAD(int x);
    void menu(int i);
    cAeropuerto();
    ~cAeropuerto();
    void addAvion();
    void totalasientos();
    void eliminar();
    int buscarAv(int);
    void totaldecarga();
    void del(int);
};
void cAeropuerto::del(int a){
		delete (Ad[a]);
}
void cAeropuerto::totaldecarga(){
	int acum;
	for (int i=0; i<nAM ;i++){
		if (Am[i]->gettipo()==2){
			cComercial* m=(cComercial*)Am[i];
			acum+=m->getCarga();
		}	
	}
	cout<<"Total carga en los aviones de mantenimiento: "<<acum<<endl;
}
int cAeropuerto::buscarAv(int z){
	int pos=-1, i=0;
	while (pos==-1 && i<nAD){
		if (Ad[i]->getcodigo()==z){
			pos=i;
		}
		i++;
	}
	return (pos);
}
void cAeropuerto::totalasientos(){
	int acum=0;
	for (int i=0; i<nAD; i++){	
		if (Ad[i]->gettipo()==1){
			cTurista* p= (cTurista*)Ad[i]; 
			acum+=p->totala(); 
		}
	}
	cout<<"El total de asientos disponibles son: "<<acum<<endl;
}
void cAeropuerto::addAvion(){
	if (nAD <100){
		menu(nAD);
		nAD++;
	}
}
void cAeropuerto::eliminar(){
	int aux;
	cout<<"ingrese el codigo del avion accidentado: "; cin>>aux;  
	int y=buscarAv(aux);
	cout<<y<<endl;
	if (y=!-1){
		delete (Ad[y]);
		recorrerAD(y);
		nAD--;
	}
}
void cAeropuerto :: recorrerAD (int x){
    if((x>=0)&&(x<nAD )){
        for(int i=x; i<nAD -1;i++){
            Ad[i]= Ad[i+1];
        }
    }
}
void cAeropuerto :: clasificar(){
    for (int i=0;i<nAD ;i++){
        if (Ad[i] -> mante() == 1){
            Am[nAM] = Ad[i];
            Ad[i]=Ad[nAD-1];
            nAM++;
            nAD--;
            i--;
        }
    }
}
void cAeropuerto::leer(){
	cout<<"--Datos Aeropuerto---"<<endl;
	fflush(stdin);
	cout<<"Nombre: "; cin.getline(nombre,50);
	cout<<"Direccion: "; cin.getline(ciudad,50);
	cout<<"Numero de aviones en el aeropuerto"<<endl;
	cin>>nAD;
	system("cls");
	for (int i=0; i<nAD; i++){
		menu(i);
	}
}
void cAeropuerto::menu(int i){
	int y;
	cout<<"Digite 1: Avion Comercial"<<endl;
	cout<<"Digite 2: Avion Carga"<<endl;
	cin>>y;
		if (y==1){
			Ad[i]=new cTurista;
			Ad[i]->leer();
		}
		if (y==2){
			Ad[i]=new cComercial;
			Ad[i]->leer();
		}
}
void cAeropuerto :: mostrar(){
    cout << "El Nombre del Aeropuerto es: " << nombre << endl;
    cout << "La Ciudad donde esta el Aeropuerto es: " << ciudad << endl;
    cout << endl;
    cout << "------------Lista de Aviones Disponibles------------" << endl;
    for(int i=0;i<nAD;i++){
        Ad[i] -> mostrar();
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << "------------Lista de Aviones en Mantenimineto------------" << endl;
    for(int i=0;i<nAM;i++){
        Am[i] -> mostrar();
        cout << endl;
    }
}
cAeropuerto :: cAeropuerto(){
    nAD = 0;
    nAM = 0;
    strcpy(nombre," ");
    strcpy(ciudad," ");
}
cAeropuerto :: ~cAeropuerto(){
    for(int i=0;i<nAD;i++){
        delete(Ad[i]);
    }
    for(int i=0;i<nAM;i++){
        delete(Am[i]);
    }
}
int main(){
cAeropuerto oA;
oA.leer();
oA.clasificar();
oA.mostrar();
oA.eliminar();
oA.mostrar();
oA.addAvion();
oA.totalasientos();
oA.totaldecarga();
}