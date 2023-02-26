/*!
    \file main.cpp
    \author Gennaro Russo
    \brief Lo scopo di questo programma e` far gareggiare un numero indefinito di partecipanti a una gara di kyte snowboarding. Vince chi percorre piu` chilometri, chi si portera` a casa la sfida?
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <time.h>

//! \def FILE_NAME e` il file principale che mi servira` in tutto il programma
#define FILE_NAME "files/file_di_gara.txt"

using namespace std;

//! \struct s_par e` la struttura del partecipante
struct s_par
{
    string matricola; //! \var  matricola e` una variabile string che indica la matricola del partecipante
    string cognome; //! \var  cognome e` una variabile string che indica il cognome del partecipante
    int x[30]; //! \var  il vettore di int x indica le coordinate X dei punti percorsi durante la gara
    int y[30]; //! \var  il vettore di int y indica le coordinate Y dei punti percorsi durante la gara
    int minuti; //! \var  minuti e` una variabile int che indica quanti minuti dura la gara del partecipante
    float distanza; //! \var  idstanza e` una variabile float che indica la lunghezza (in km) del procorso fatto durante la gara
};

void pulisci_file();
void visualizza_par(s_par *ptr_vet_par);
void visualizza_ris(s_par *ptr_vet_par);
void gara(s_par *ptr_vet_par);
int conta_record();
void carica_vet_iniziale(s_par *ptr_vet_par);
void riempi_con_vet(s_par *ptr_vet_par, int n_par);
void genera_coordinate(s_par *ptr_vet_par, int n_par);
void calcola_distanza(s_par *ptr_vet_par, int n_par);
void podio(s_par *ptr_vet_par);
void stampa_podio(s_par *p_v_p_ord);

/*!
    \fn menu() e` una funzione void
    \brief questa funzione serve a creare il menu per navigare da una funzione all'altra del programma
*/
void menu()
{
    s_par vet_par[2000]; //! \var vet_par e` un vettore di tipo s_par che mi serve per muovermi tra un partecipante e l'altro
    s_par *ptr_vet_par=vet_par; //! \var ptr_vet_par e` un puntatore che punta a vet_par

    pulisci_file();

    carica_vet_iniziale(ptr_vet_par);

    int scelta; //! \var scelta e` una varabile int che mi serve per selezionare la voce nel menu
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

/*!
    \fn main() e` una funzione int
    \brief questa funzione e` quella principale
*/
int main()
{
    srand(time(NULL));
    menu();
    return 0;
}

/*!
    \fn pulisci_file() e` una funzione void
    \brief questa funzione serve per pulire file_di_gara, con coordinate, e renderlo come lista_partecipanti, quindi privo di coordinate
*/
void pulisci_file()
{
    char var; //! \var var e` una variabiale char e serve come appoggio per il trasferimento di informazioni tra un file ed un altro
    ofstream fout(FILE_NAME);
        ifstream fin("files/lista_partecipanti.txt");
        while(fin.get(var))
        {
            fout<<var;
        }
        fin.close();
    fout.close();
}

/*!
    \fn conta_record() e` una funzione int
    \brief questa funzione serve a contare il numero di righe (quindi di partecipanti) all'interno del file
*/
int conta_record()
{
    int i=0; //! \var i e` una variabile int contatore per le righe
    string appoggio; //! \var appoggio e` una variabile string di appoggio per far funzioinare il getline

    fstream fin;
    fin.open(FILE_NAME,ios::in);

    while(getline(fin,appoggio))
        (i++);

    fin.close();
    return i; //! \return ritorno il numero di righe con i
}

/*!
    \fn visualizza_par() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \brief questa funzione serve a stampare in maniera seriale ogni partecipante con matricola e cognome
*/
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

/*!
    \fn visualizza_ris() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \brief questa funzione serve a stampare in maniera seriale ogni partecipante con matricola, cognome, distanza percorsa e minuti di gara
*/
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

/*!
    \fn gara() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \brief questa funzione serve a gestire al meglio la seconda voce del menu, quindi per far avvenire l'intero svolgimento della gara
*/
void gara(s_par *ptr_vet_par)
{
    pulisci_file();
    int n_par=conta_record(); //! \var n_par e` una variabile int alla quale viene assegnato il valore di conta_record()
    genera_coordinate(ptr_vet_par, n_par);
    calcola_distanza(ptr_vet_par, n_par);
    riempi_con_vet(ptr_vet_par,n_par);

    cout<<"\n\t------------------"
        <<"\n\t| GARA TERMINATA |"
        <<"\n\t------------------\n";
}

/*!
    \fn carica_vet_iniziale() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \brief questa funzione serve a caricare il vettore di tipo s_par con matricola e cognome prelevati dal file
*/
void carica_vet_iniziale(s_par *ptr_vet_par)
{
    ifstream fin(FILE_NAME);

    int j=0; //! \var j e` una variabile int che serve per puntare le celle all'interno del puntatore di vettore

    while(!fin.eof())
    {
        getline(fin,(ptr_vet_par+j)->matricola,','); //! \brief qui si riempie il campo matricola con quella prelevata dal file
        getline(fin,(ptr_vet_par+j)->cognome); //! \brief qui si riempie il campo cognome con quello prelevato dal file

        j++;
    }

    fin.close();
}

/*!
    \fn genera_coordinate() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \param viene passato come parametro il numero di partecipanti
    \brief questa funzione serve a generare casualmente le coordinate dalle quali sono passati i partecipanti alla gara
*/
void genera_coordinate(s_par *ptr_vet_par, int n_par)
{
    for(int j=0; j<n_par; j++) //! \brief ciclo for che scorre su tutti i partecipanti
    {
        (ptr_vet_par+j)->minuti=rand()%7+24; //! \brief qui si riempie il campo minuti con un numero casuale da 24 a 30
        //! \brief qui si riempie la prima cella dei vettori x e y con 0 per far partire il partecipante dall'inizio del percorso
        (ptr_vet_par+j)->x[0]=0;
        (ptr_vet_par+j)->y[0]=0;
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++) //! \brief ciclo for che serve a generare le coordinate dal primo minuto fino all'uiltimo relativo di ogni partecipante
        {
            (ptr_vet_par+j)->x[i]=rand()%101; //! \brief qui si riempie il campo x con un numero casuale da 0 a 100
            (ptr_vet_par+j)->y[i]=rand()%101; //! \brief qui si riempie il campo y con un numero casuale da 0 a 100
        }
    }
}

/*!
    \fn calcola_distanza() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \param viene passato come parametro il numero di partecipanti
    \brief questa funzione serve a calcolare la distanza percorsa dai partecipanti, tenendo conto ovviamnete delle coordinate
*/
void calcola_distanza(s_par *ptr_vet_par, int n_par)
{
    for(int j=0; j<n_par; j++) //! \brief ciclo for che scorre su tutti i partecipanti
    {
        (ptr_vet_par+j)->distanza=0; //! \brief qui si riempie il campo distanza con lo 0 per resettare la distanza ogni volta che si riavvia la gara
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++) //! \brief ciclo for che scorre su tutte le coordinate dei vari partecipanti
        {
            //! \brief qui viene eseguito il calcolo della distanza con una formula predefinita
            (ptr_vet_par+j)->distanza+=sqrt(pow((ptr_vet_par+j)->x[i]-(ptr_vet_par+j)->x[i-1],2)+
                                            pow((ptr_vet_par+j)->y[i]-(ptr_vet_par+j)->y[i-1],2));
        }
        (ptr_vet_par+j)->distanza/=100; //! \brief qui viene divisa la distanza per 100 per renderla piu` realistica in quanto mediamente in mezz'ora un vero partecipante percorre circa 18 km
    }
}

/*!
    \fn riempi_con_vet() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \param viene passato come parametro il numero di partecipanti
    \brief questa funzione serve a riempire file_di_gara con anche le coordinate di ogni partecipanti, oltre matricola e cognome
*/
void riempi_con_vet(s_par *ptr_vet_par, int n_par)
{
    ofstream fout(FILE_NAME);

    for(int j=0;j<n_par;j++) //! \brief ciclo for che scorre su tutti i partecipanti
    {
        fout<<(ptr_vet_par+j)->matricola
        <<','<<(ptr_vet_par+j)->cognome; //! \brief qui vengono scritte nel file matricola e cognome separati da una vrigola
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++) //! \brief ciclo for che scorre su tutte le coordinate dei vari partecipanti
        {
            fout<<", ("<<(ptr_vet_par+j)->x[i-1]
            <<'-'<<(ptr_vet_par+j)->y[i-1]
            <<"; "<<(ptr_vet_par+j)->x[i]
            <<'-'<<(ptr_vet_par+j)->y[i]<<")"; //! \brief qui vengono scritte nel file tutte le coordinate dei vari punti.
            //! \brief le coordinate sono separate fra di loro con un trattino, i punti con un punto e virgola e i segmenti con le parentesi
        }
        if(j<n_par-1)
            fout<<endl; //! \brief qui va a capo ogni volte che finisce di scrivere le informazioni di un partecipante, tranne se e` l'ultimo
    }

    fout.close();
}

/*!
    \fn podio() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \param viene passato come parametro il numero di partecipanti
    \brief questa funzione serve a gestire al meglio la quarta voce del menu, quindi per la realizzazione del podio
*/
void podio(s_par *ptr_vet_par)
{
    int n_par=conta_record(); //! \var n_par e` una variabile int alla quale viene assegnato il valore di conta_record()
    s_par t; //! \var t e` una variabile di tipo s_par temporanea che serve solamente a spostare e ordinare i partecipanti
    s_par *p_v_p_ord=ptr_vet_par; //! \var p_v_p_ord e` un puntatore di tipo s_par che clona l'altro puntatore ptr_vet_par e serve per sistemare in ordine di distanza percorsa i vari partecipanti

    for(int i=0;i<n_par-1;i++) //! \brief ciclo for che scorre su tutti i partecipanti tranne l'ultimo
        for(int k=i+1;k<n_par;k++) //! \brief ciclo for che scorre sui partecipanti successivi a quello selezionato dal ciclo precedente
            if((p_v_p_ord+i)->distanza<(p_v_p_ord+k)->distanza) //! \brief qui si verifica se la distanza del primo partecipante e` minore di quella del secondo preso in analisi
            {
                //! \brief qui avviene lo scambio di posizione tra il partecipante che ha la distanza maggiore dell'altro
                t=*(p_v_p_ord+k);
                *(p_v_p_ord+k)=*(p_v_p_ord+i);
                *(p_v_p_ord+i)=t;
            }

    stampa_podio(p_v_p_ord);
}

/*!
    \fn stampa_podio() e` una funzione void
    \param viene passato come parametro il puntatore al vettore di tipo s_par
    \brief questa funzione serve a stampare i primi tre classificati con matricola, cognome e distanza
*/
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
