/*!
    \file main.cpp
    \author Gennaro Russo
    \date 21/02/2023
    \date 27/02/2023
    \brief Lo scopo di questo programma è far gareggiare un numero indefinito di partecipanti a una gara di kyte snowboarding. Vince chi percorre più chilometri, chi si porterà a casa la sfida?
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <time.h>

//! \def FILE_NAME
#define FILE_NAME "files/file_di_gara.txt"

using namespace std;

//! \struct s_par
//! \brief s_par e` la struttura del partecipante
struct s_par
{
    //! \var matricola
    //! \brief matricola e` una variabile string che indica la matricola del partecipante
    string matricola;
    //! \var cognome
    //! \brief cognome e` una variabile string che indica il cognome del partecipante
    string cognome;
    //! \var x
    //! \brief il vettore di int x indica le coordinate Y dei punti percorsi durante la gara
    int x[30];
    //! \var y
    //! \brief il vettore di int y indica le coordinate Y dei punti percorsi durante la gara
    int y[30];
    //! \var minuti
    //! \brief minuti e` una variabile int che indica quanti minuti dura la gara del partecipante
    int minuti;
    //! \var distanza
    //! \brief distanza e` una variabile float che indica la lunghezza (in km) del procorso fatto durante la gara
    float distanza;
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
    \fn menu()
    \brief questa funzione serve a creare il menu per navigare da una funzione all'altra del programma
*/
void menu()
{
    //! \var vet_par
    //! \brief vet_par e` un vettore di tipo s_par che mi serve per muovermi tra un partecipante e l'altro
    s_par vet_par[2000];
    //! \var ptr_vet_par
    //! \var ptr_vet_par e` un puntatore che punta a vet_par
    s_par *ptr_vet_par=vet_par;

    pulisci_file();

    carica_vet_iniziale(ptr_vet_par);

    //! \var scelta
    //! \brief scelta e` una varabile int che mi serve per selezionare la voce nel menu
    int scelta;
    do{
        cout<<endl<<"--=============================--"<<endl
                  <<"||  GARA DI KYTE SNOWBOARDING  ||"<<endl
                  <<"--=============================--"<<endl
                  <<"|| 1 - Visualizza partecipanti ||"<<endl
                  <<"|| 2 - Avvia gara              ||"<<endl
                  <<"|| 3 - Visualizza risultati    ||"<<endl
                  <<"|| 4 - Definisci podio         ||"<<endl
                  <<"|| 5 - Uscita                  ||"<<endl
                  <<"--=============================--"
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
    \fn main()
    \brief questa funzione e` quella principale
*/
int main()
{
    srand(time(NULL));
    menu();
    return 0;
}

/*!
    \fn pulisci_file()
    \brief questa funzione serve per pulire file_di_gara, con coordinate, e renderlo come lista_partecipanti, quindi privo di coordinate
*/
void pulisci_file()
{
    //! \var var
    //! \brief var e` una variabiale char e serve come appoggio per il trasferimento di informazioni tra un file ed un altro
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

/*!
    \fn conta_record()
    \brief questa funzione serve a contare il numero di righe (quindi di partecipanti) all'interno del file
*/
int conta_record()
{
    //! \var i
    //! \brief i e` una variabile int contatore per le righe
    int i=0;
    //! \var appoggio
    //! \brief appoggio e` una variabile string di appoggio per far funzioinare il getline
    string appoggio;

    fstream fin;
    fin.open(FILE_NAME,ios::in);

    while(getline(fin,appoggio))
        (i++);

    fin.close();
    //! \return i
    //! \brief ritorno il numero di righe con i
    return i;
}

/*!
    \fn visualizza_par(s_par *ptr_vet_par)
    \param ptr_vet_par
    \brief questa funzione serve a stampare in maniera seriale ogni partecipante con matricola e cognome
*/
void visualizza_par(s_par *ptr_vet_par)
{
    cout<<"\n\t--------------------------------------------------------------"
        <<"\n\t| I PARTECIPANTI DI QUESTA GARA DI KYTE SNOW BOARDING SONO : |"
        <<"\n\t--------------------------------------------------------------"
        <<"\n\t| "<<setw(18)<<"MATRICOLA"<<setw(11)<<"|"<<setw(19)<<"COGNOME"<<setw(12)<<"|"
        <<"\n\t--------------------------------------------------------------";
    for(int j=0;j<conta_record();j++)
    {
        cout<<"\n\t| "<<setw(15)<<(ptr_vet_par+j)->matricola<<setw(14)<<"|"<<setw(19)<<(ptr_vet_par+j)->cognome<<setw(12)<<"|";
    }
    cout<<"\n\t--------------------------------------------------------------"<<endl;
}

/*!
    \fn visualizza_ris(s_par *ptr_vet_par)
    \param ptr_vet_par
    \brief questa funzione serve a stampare in maniera seriale ogni partecipante con matricola, cognome, distanza percorsa e minuti di gara
*/
void visualizza_ris(s_par *ptr_vet_par)
{
    cout<<"\n\t-----------------------------------------------------------"
        <<"\n\t| I RISULTATI DI QUESTA GARA DI KYTE SNOW BOARDING SONO : |"
        <<"\n\t-----------------------------------------------------------"
        <<"\n\t|  MATRICOLA  |"<<setw(12)<<"COGNOME"<<setw(6)<<"|"<<"   DISTANZA   |  MINUTI  |"
        <<"\n\t-----------------------------------------------------------";
    for(int j=0;j<conta_record();j++)
    {
        cout<<"\n\t| "<<setw(7)<<(ptr_vet_par+j)->matricola<<setw(6)<<"|"<<setw(12)<<(ptr_vet_par+j)->cognome<<setw(6)<<"|"<<setw(9)<<(ptr_vet_par+j)->distanza<<" km  |"<<setw(4)<<(ptr_vet_par+j)->minuti<<" min  |";
    }
    cout<<"\n\t-----------------------------------------------------------"<<endl;
}

/*!
    \fn gara(s_par *ptr_vet_par)
    \param ptr_vet_par
    \brief questa funzione serve a gestire al meglio la seconda voce del menu, quindi per far avvenire l'intero svolgimento della gara
*/
void gara(s_par *ptr_vet_par)
{
    pulisci_file();
    //! \var n_par
    //! \brief n_par e` una variabile int alla quale viene assegnato il valore di conta_record()
    int n_par=conta_record();
    genera_coordinate(ptr_vet_par, n_par);
    calcola_distanza(ptr_vet_par, n_par);
    riempi_con_vet(ptr_vet_par,n_par);

    cout<<"\n\t------------------"
        <<"\n\t| GARA TERMINATA |"
        <<"\n\t------------------\n";
}

/*!
    \fn carica_vet_iniziale(s_par *ptr_vet_par)
    \param ptr_vet_par
    \brief questa funzione serve a caricare il vettore di tipo s_par con matricola e cognome prelevati dal file
*/
void carica_vet_iniziale(s_par *ptr_vet_par)
{
    ifstream fin(FILE_NAME);

    //! \var j
    //! \brief j e` una variabile int che serve per puntare le celle all'interno del puntatore di vettore
    int j=0;

    while(!fin.eof())
    {
        //! \brief qui si riempie il campo matricola con quella prelevata dal file
        getline(fin,(ptr_vet_par+j)->matricola,',');
        //! \brief qui si riempie il campo cognome con quello prelevato dal file
        getline(fin,(ptr_vet_par+j)->cognome);

        j++;
    }

    fin.close();
}

/*!
    \fn genera_coordinate(s_par *ptr_vet_par, int n_par)
    \param ptr_vet_par
    \param n_par
    \brief questa funzione serve a generare casualmente le coordinate dalle quali sono passati i partecipanti alla gara
*/
void genera_coordinate(s_par *ptr_vet_par, int n_par)
{
    //! \brief ciclo for che scorre su tutti i partecipanti
    for(int j=0; j<n_par; j++)
    {
        //! \brief qui si riempie il campo minuti con un numero casuale da 24 a 30
        (ptr_vet_par+j)->minuti=rand()%7+24;
        //! \brief qui si riempie la prima cella dei vettori x e y con 0 per far partire il partecipante dall'inizio del percorso
        (ptr_vet_par+j)->x[0]=0;
        (ptr_vet_par+j)->y[0]=0;
        //! \brief ciclo for che serve a generare le coordinate dal primo minuto fino all'uiltimo relativo di ogni partecipante
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++)
        {
            //! \brief qui si riempie il campo x con un numero casuale da 0 a 100
            (ptr_vet_par+j)->x[i]=rand()%101;
            //! \brief qui si riempie il campo y con un numero casuale da 0 a 100
            (ptr_vet_par+j)->y[i]=rand()%101;
        }
    }
}

/*!
    \fn calcola_distanza(s_par *ptr_vet_par, int n_par)
    \param ptr_vet_par
    \param n_par
    \brief questa funzione serve a calcolare la distanza percorsa dai partecipanti, tenendo conto ovviamnete delle coordinate
*/
void calcola_distanza(s_par *ptr_vet_par, int n_par)
{
    //! \brief ciclo for che scorre su tutti i partecipanti
    for(int j=0; j<n_par; j++)
    {
        //! \brief qui si riempie il campo distanza con lo 0 per resettare la distanza ogni volta che si riavvia la gara
        (ptr_vet_par+j)->distanza=0;
        //! \brief ciclo for che scorre su tutte le coordinate dei vari partecipanti
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++)
        {
            //! \brief qui viene eseguito il calcolo della distanza con una formula predefinita
            (ptr_vet_par+j)->distanza+=sqrt(pow((ptr_vet_par+j)->x[i]-(ptr_vet_par+j)->x[i-1],2)+
                                            pow((ptr_vet_par+j)->y[i]-(ptr_vet_par+j)->y[i-1],2));
        }
        //! \brief qui viene divisa la distanza per 100 per renderla piu` realistica in quanto mediamente in mezz'ora un vero partecipante percorre circa 18 km
        (ptr_vet_par+j)->distanza/=100;
    }
}

/*!
    \fn riempi_con_vet(s_par *ptr_vet_par, int n_par)
    \param ptr_vet_par
    \param n_par
    \brief questa funzione serve a riempire file_di_gara con anche le coordinate di ogni partecipanti, oltre matricola e cognome
*/
void riempi_con_vet(s_par *ptr_vet_par, int n_par)
{
    ofstream fout(FILE_NAME);

    //! \brief ciclo for che scorre su tutti i partecipanti
    for(int j=0;j<n_par;j++)
    {
        //! \brief qui vengono scritte nel file matricola e cognome separati da una vrigola
        fout<<(ptr_vet_par+j)->matricola
        <<','<<(ptr_vet_par+j)->cognome;
        //! \brief ciclo for che scorre su tutte le coordinate dei vari partecipanti
        for(int i=1; i<(ptr_vet_par+j)->minuti; i++)
        {
            //! \brief qui vengono scritte nel file tutte le coordinate dei vari punti.
            fout<<", ("<<(ptr_vet_par+j)->x[i-1]
            <<'-'<<(ptr_vet_par+j)->y[i-1]
            <<"; "<<(ptr_vet_par+j)->x[i]
            <<'-'<<(ptr_vet_par+j)->y[i]<<")";
            //! \brief le coordinate sono separate fra di loro con un trattino, i punti con un punto e virgola e i segmenti con le parentesi
        }
        //! \brief qui va a capo ogni volte che finisce di scrivere le informazioni di un partecipante, tranne se e` l'ultimo
        if(j<n_par-1)
            fout<<endl;
    }

    fout.close();
}

/*!
    \fn podio(s_par *ptr_vet_par)
    \param ptr_vet_par
    \param n_par
    \brief questa funzione serve a gestire al meglio la quarta voce del menu, quindi per la realizzazione del podio
*/
void podio(s_par *ptr_vet_par)
{
    //! \var n_par
    //! \brief n_par e` una variabile int alla quale viene assegnato il valore di conta_record()
    int n_par=conta_record();
    //! \var t
    //! \brief t e` una variabile di tipo s_par temporanea che serve solamente a spostare e ordinare i partecipanti
    s_par t;
    //! \var p_v_p_ord
    //! \brief p_v_p_ord e` un puntatore di tipo s_par che clona l'altro puntatore ptr_vet_par e serve per sistemare in ordine di distanza percorsa i vari partecipanti
    s_par *p_v_p_ord=ptr_vet_par;

    //! \brief ciclo for che scorre su tutti i partecipanti tranne l'ultimo
    for(int i=0;i<n_par-1;i++)
        //! \brief ciclo for che scorre sui partecipanti successivi a quello selezionato dal ciclo precedente
        for(int k=i+1;k<n_par;k++)
            //! \brief qui si verifica se la distanza del primo partecipante e` minore di quella del secondo preso in analisi
            if((p_v_p_ord+i)->distanza<(p_v_p_ord+k)->distanza)
            {
                //! \brief qui avviene lo scambio di posizione tra il partecipante che ha la distanza maggiore dell'altro
                t=*(p_v_p_ord+k);
                *(p_v_p_ord+k)=*(p_v_p_ord+i);
                *(p_v_p_ord+i)=t;
            }

    stampa_podio(p_v_p_ord);
}

/*!
    \fn stampa_podio(s_par *p_v_p_ord)
    \param p_v_p_ord
    \brief questa funzione serve a stampare i primi tre classificati con matricola, cognome e distanza
*/
void stampa_podio(s_par *p_v_p_ord)
{
    cout<<"\n\t"<<setw(26)<<(p_v_p_ord+0)->cognome
        <<"\n\t"<<setw(23)<<(p_v_p_ord+0)->matricola
        <<"\n\t"<<setw(24)<<(p_v_p_ord+0)->distanza<<"km"
        <<"\n\t"<<setw(12)<<(p_v_p_ord+1)->cognome<<"  ---------------"
        <<"\n\t"<<setw(9)<<(p_v_p_ord+1)->matricola<<"     |             |"
        <<"\n\t"<<setw(10)<<(p_v_p_ord+1)->distanza<<"km  |      1      |"
        <<"\n\t--------------|             |"<<setw(11)<<(p_v_p_ord+2)->cognome
        <<"\n\t|             |             |"<<setw(8)<<(p_v_p_ord+2)->matricola
        <<"\n\t|      2      |             |"<<setw(9)<<(p_v_p_ord+2)->distanza<<"km"
        <<"\n\t|             |             |--------------"
        <<"\n\t|             |             |      3      |"
        <<"\n\t-------------------------------------------"
        <<endl;
}
