#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <time.h>

#define FILE_NAME "files/file_di_gara.txt"

using namespace std;

struct s_par
{
    string matricola, cognome;
    int x[30], y[30], minuti;
    float distanza;
};

void pulisci_file();
void visualizza_par(s_par *ptr_vet_par);
void visualizza_ris(s_par *ptr_vet_par);
void gara(s_par *ptr_vet_par);
int conta_record();
void carica_vet_iniziale(s_par *ptr_vet_par);
void riempi_con_vet(s_par *ptr_vet_par, int k);
void genera_coordinate(s_par *ptr_vet_par, int n_par);
void calcola_distanza(s_par *ptr_vet_par, int n_par);
void podio(s_par *ptr_vet_par);
void stampa_podio(s_par *p_v_p_ord);

void menu()
{
    s_par vet_par[2000];
    s_par *ptr_vet_par=vet_par;

    pulisci_file();

    carica_vet_iniziale(ptr_vet_par);

    int scelta;
    do{
        cout<<endl<<"-=====- MENU -=====-"<<endl
        <<"1 - Visualizza partecipanti"<<endl
        <<"2 - Avvia gara"<<endl
        <<"3 - Visualizza risultati"<<endl
        <<"4 - Definisci podio"<<endl
        <<"5 - Uscita"
        <<endl<<">>";
        cin>>scelta;

        switch(scelta)
        {
            case 1:
                visualizza_par(ptr_vet_par);
                break;
            case 2:
                gara(ptr_vet_par);
                break;
            case 3:
                visualizza_ris(ptr_vet_par);
                break;
            case 4:
                podio(ptr_vet_par);
                break;
            case 5:
                cout<<"\nPROGRAMMA TERMINATO";
        }
    }while(scelta!=5);
}

int main()
{
    srand(time(NULL));
    menu();
    return 0;
}

void pulisci_file()
{
    char var;
    ofstream fout(FILE_NAME);
        ifstream fin("files/lista_partecipanti.txt");
        while(fin.get(var))
        {
            fout<<var;
        }
        fin.close();
    fout.close();
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

void visualizza_par(s_par *ptr_vet_par)
{
    cout<<"\n\tI PARTECIPANTI DI QUESTA GARA DI KYTE SNOW BOARDING SONO : "
        <<"\n\t---------------------------------------------------------";
    for(int j=0;j<conta_record();j++)
    {
        cout<<"\n\t"<<setw(3)<<(ptr_vet_par+j)->matricola<<setw(20)<<(ptr_vet_par+j)->cognome;
    }
    cout<<endl;
}

void visualizza_ris(s_par *ptr_vet_par)
{
    cout<<"\n\tI RISULTATI DI QUESTA GARA DI KYTE SNOW BOARDING SONO : "
        <<"\n\t---------------------------------------------------------";
    for(int j=0;j<conta_record();j++)
    {
        cout<<"\n\t"<<setw(3)<<(ptr_vet_par+j)->matricola<<setw(17)<<(ptr_vet_par+j)->cognome<<setw(17)<<(ptr_vet_par+j)->distanza<<" km"<<setw(13)<<(ptr_vet_par+j)->minuti<<" min";
    }
    cout<<endl;
}

void gara(s_par *ptr_vet_par)
{
    pulisci_file();
    int n_par=conta_record();
    genera_coordinate(ptr_vet_par, n_par);
    calcola_distanza(ptr_vet_par, n_par);
    riempi_con_vet(ptr_vet_par,n_par);

    cout<<"\n\t------------------"
        <<"\n\t| GARA TERMINATA |"
        <<"\n\t------------------\n";
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
    {
        (ptr_vet_par+j)->minuti=rand()%7+24;
        (ptr_vet_par+j)->x[0]=0;
        (ptr_vet_par+j)->y[0]=0;
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++)
        {
            (ptr_vet_par+j)->x[i]=rand()%101;
            (ptr_vet_par+j)->y[i]=rand()%101;
        }
    }
}

void calcola_distanza(s_par *ptr_vet_par, int n_par)
{
    int xa,ya;

    for(int j=0; j<n_par; j++)
    {
        (ptr_vet_par+j)->distanza=0;
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++)
        {
            (ptr_vet_par+j)->distanza+=sqrt(pow((ptr_vet_par+j)->x[i]-(ptr_vet_par+j)->x[i-1],2)+
                                            pow((ptr_vet_par+j)->y[i]-(ptr_vet_par+j)->y[i-1],2));
        }
    }
}

void riempi_con_vet(s_par *ptr_vet_par, int n_par)
{
    ofstream fout(FILE_NAME);

    for(int j=0;j<n_par;j++)
    {
        fout<<(ptr_vet_par+j)->matricola
        <<','<<(ptr_vet_par+j)->cognome
        <<',';
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++)
        {
            fout<<" ("<<(ptr_vet_par+j)->x[i-1]
            <<'-'<<(ptr_vet_par+j)->y[i-1]
            <<"; "<<(ptr_vet_par+j)->x[i]
            <<'-'<<(ptr_vet_par+j)->y[i]<<"),";
        }
        if(j<n_par-1)
            fout<<endl;
    }

    fout.close();
}

void podio(s_par *ptr_vet_par)
{
    int n_par=conta_record();
    s_par t,  *p_v_p_ord=ptr_vet_par;

    for(int i=0;i<n_par-1;i++)
        for(int k=i+1;k<n_par;k++)
            if((p_v_p_ord+i)->distanza<(p_v_p_ord+k)->distanza)
            {
                t=*(p_v_p_ord+k);
                *(p_v_p_ord+k)=*(p_v_p_ord+i);
                *(p_v_p_ord+i)=t;
            }

    stampa_podio(p_v_p_ord);
}

void stampa_podio(s_par *p_v_p_ord)
{
    cout<<"\n\tIl PRIMO POSTO va a"<<(p_v_p_ord+0)->cognome
        <<" con il numero "<<(p_v_p_ord+0)->matricola
        <<" che ha percorso "<<(p_v_p_ord+0)->distanza<<"km!"<<endl;

    cout<<"\n\tIl SECONDO POSTO va a"<<(p_v_p_ord+1)->cognome
        <<" con il numero "<<(p_v_p_ord+1)->matricola
        <<" che ha percorso "<<(p_v_p_ord+1)->distanza<<"km!"<<endl;

    cout<<"\n\tIl TERZO POSTO va a"<<(p_v_p_ord+2)->cognome
        <<" con il numero "<<(p_v_p_ord+2)->matricola
        <<" che ha percorso "<<(p_v_p_ord+2)->distanza<<"km!"<<endl;
}
