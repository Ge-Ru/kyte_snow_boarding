#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <time.h>

#define FILE_NAME "storico_partecipanti.txt"

using namespace std;

struct s_par
{
    string matricola, cognome;
    int x1[30], y1[30], x2[30], y2[30];
    float distanza=0;
};

void gara(s_par *ptr_vet_par);
int conta_record();
void carica_vet_iniziale(s_par *ptr_vet_par);
void riempi_con_vet(s_par *ptr_vet_par, int k);
void genera_coordinate(s_par *ptr_vet_par, int n_par);
void calcola_distanza(s_par *ptr_vet_par, int n_par);

void podio(s_par *ptr_vet_par);

void menu()
{
    s_par vet_par[2000];
    s_par *ptr_vet_par=vet_par;

    int scelta;
    do{
        cout<<endl<<"-=====- MENU -=====-"<<endl
        <<"1 - Avvia gara"<<endl
        <<"2 - Definisci podio"<<endl
        <<"3 - Uscita"
        <<endl<<">>";
        cin>>scelta;

        switch(scelta)
        {
            case 1:
                gara(ptr_vet_par);
                break;
            case 2:
                podio(ptr_vet_par);
                break;
            case 3:
                cout<<"\nPROGRAMMA TERMINATO";
        }
    }while(scelta!=3);
}

int main()
{
    srand(time(NULL));
    menu();
    return 0;
}

void gara(s_par *ptr_vet_par)
{
    int n_par=conta_record();
    carica_vet_iniziale(ptr_vet_par);
    genera_coordinate(ptr_vet_par, n_par);
    calcola_distanza(ptr_vet_par, n_par);
    riempi_con_vet(ptr_vet_par,n_par);
}

int conta_record()
{
    int i=0;
    string appoggio;

    fstream fin;
    fin.open(FILE_NAME,ios::in);

    while(getline(fin,appoggio))
        (i++);

    fin.close();
    return i;
}

void carica_vet_iniziale(s_par *ptr_vet_par)
{
    ifstream fin(FILE_NAME);

    string appoggio;

    int j=0;

    while(!fin.eof())
    {
        getline(fin,(ptr_vet_par+j)->matricola,',');
        getline(fin,(ptr_vet_par+j)->cognome);

        j++;
    }

    fin.close();
}

void genera_coordinate(s_par *ptr_vet_par, int n_par)
{
    for(int j=0; j<n_par; j++)
        for(int i=0; i<30; i++)
        {
            (ptr_vet_par+j)->x1[i]=rand()%101;
            (ptr_vet_par+j)->y1[i]=rand()%101;
            (ptr_vet_par+j)->x2[i]=rand()%101;
            (ptr_vet_par+j)->y2[i]=rand()%101;
        }
}

void calcola_distanza(s_par *ptr_vet_par, int n_par)
{
    for(int j=0; j<n_par; j++)
        for(int i=0; i<30; i++)
            (ptr_vet_par+j)->distanza+=sqrt(pow((ptr_vet_par+j)->x1[i]-(ptr_vet_par+j)->x2[i],2)+
                                            pow((ptr_vet_par+j)->y1[i]-(ptr_vet_par+j)->y2[i],2));
}

void riempi_con_vet(s_par *ptr_vet_par, int n_par)
{
    ofstream fout(FILE_NAME);

    for(int j=0;j<n_par;j++)
    {
        fout<<(ptr_vet_par+j)->matricola
        <<','<<(ptr_vet_par+j)->cognome
        <<',';
        for(int i=0; i<30; i++)
        {
            fout<<" ("<<(ptr_vet_par+j)->x1[i]
            <<'-'<<(ptr_vet_par+j)->y1[i]
            <<"; "<<(ptr_vet_par+j)->x2[i]
            <<'-'<<(ptr_vet_par+j)->y2[i]<<"),";
        }
        if(j<n_par-1)
            fout<<endl;
    }

    fout.close();
}

void podio(s_par *ptr_vet_par)
{

}
