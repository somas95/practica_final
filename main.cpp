/****************************************************/
/* Nombre: Manuel Genovés                           */
/* Programa:Práctica final                          */
/* Intención:                                       */
/* Fecha:                                           */
/****************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <climits>
using namespace std;

#define TAM 200     //número máximo de partículas

struct particula
{
    string nombre;
    string simbolo;
    double masa;
    string carga;
    string spin;
    string familia;
    string grupo;
    string generacion;
    string pais;
    int any;
};

struct pais
{
    string pais;
    int particulas;
};

struct preferencias
{
    string fichero;
};

/* PROTOTIPOS DE FUNCIONES */
//TODO: listar, buscar...preferencias

void abrir ( ifstream &f , string nombre );
void leer ( particula v[TAM], ifstream &f , int &tam );
void ordenar ( particula v[TAM], int tam );
void crear ( particula v[TAM] , int &tam );
void mostrar ( particula v[TAM] , int tam , bool lista, int pos );
void buscar ( particula v[TAM] , int tam , bool result[TAM], particula b );
void modificar ( particula v[TAM] , int &tam );
void borrar ( particula v[TAM] , int &tam );
void buscar_por ( particula v[TAM], int tam, bool result[TAM], particula b );
void estadisticas ( particula v[TAM] , int tam );
bool salir ( bool cambios );
void guardar ( particula v[TAM], int tam , string nombre );
void opciones ( preferencias &def );
void grafica ( pais p[200], int tam );

/* PROGRAMA PRINCIPAL */

int main()
{
    int op , n = 0;                     //op->opcion    n -> numero de fichas
    ifstream f ;                        //fichero (abrir)
    particula v[TAM];                   //vector con la información de todo
    particula b;                        //la informacion a buscar
    bool resultado[TAM];                //resultado de búsquedas
    bool cambios=false;                 //bandera:controla si se ha cambiado algo
    preferencias def;

    //Abrimos y leemos las preferencias

    opciones ( def );

    // Abrimos el fichero
    abrir ( f , def.fichero.c_str() );

    // Lo leemos y lo guardamos en un vector
    if ( !f==false )
        leer ( v , f , n );

    // Lo ordenamos
    if ( !f==false )
        ordenar ( v, n );

    // Y lo cerramos (ya no es necesario)
    f.close();

    // Menú principal
    

    
    do
    {

        cout << endl;
        cout << "*********************************" << endl;
        cout << "              MENÚ              |" << endl;
        cout << "--------------------------------|" << endl;
        cout << "0- Salir" << "\t\t\t|" << endl;
        cout << "1- Crear nueva ficha" << "\t\t|" << endl;
        cout << "2- Ver fichas" << "\t\t\t|" << endl;
        cout << "3- Modificar ficha" << "\t\t|" << endl;
        cout << "4- Borrar ficha" << "\t\t\t|" << endl;
        cout << "5- Buscar..." << "\t\t\t|" << endl;
        cout << "6- Ver estadísticas" << "\t\t|" << endl;
        cout << "7- Opciones"<<"\t\t\t|"<<endl;
        cout << "--------------------------------" << endl;
        cout << endl;

        cout << "Opción: ";
        cin >> op;
        cout << endl;

        switch ( op )
        {
        case 1:             //Crear nueva ficha
            crear ( v, n );
            ordenar ( v, n );
            cambios=true;
            break;
        case 2:             //Ver fichas
            mostrar ( v, n , false , -1 );
            break;
        case 3:             //Modificar ficha
            modificar ( v , n );
            cambios=true;
            break;
        case 4:             //Borrar ficha
            borrar ( v,n );
            cambios=true;
            break;
        case 5:             //Buscar...
            buscar_por ( v , n , resultado , b );
            break;
        case 6:             //Estadísiticas
            estadisticas ( v , n );
            break;
        case 7:

            break;
        case 0:             //Salir

            if ( salir ( cambios ) ==true )
            {
                guardar ( v, n , def.fichero );
                cout << "Guardando...\nGuardado";
            }
            break;
        default:
            cout << "Opción inexistente" << endl  ;
            break;
        }

    }
    while ( op != 0 );

    return 0;
}


/*********************FUNCIONES************************/


// Abre el archivo del cual recibimos el nombre. Si no existe, lo crea vacío

void abrir ( ifstream& f, string nombre )
{
    ofstream g;

    f.open ( nombre.c_str() );
    if ( !f )
    {
        //TODO
    }

}

// Guarda en un vector la información del archivo

void leer ( particula v[TAM], ifstream &f , int &tam )
{
    int i;      //contador

    for ( i = 0; ! f.eof() ; i++ )
    {
        getline ( f , v[i].nombre );
        getline ( f , v[i].simbolo );
        f >> v[i].masa >> v[i].carga >> v[i].spin;
        f.ignore();
        f >> v[i].grupo >> v[i].familia >> v[i].generacion;
        f.ignore();
        getline ( f , v[i].pais );
        f >> v[i].any;
        f.ignore();
        tam++;
    }


}

// Ordena el vector en orden de masa. Método de burbuja

void ordenar ( particula v[TAM], int tam )
{
    int i, j;
    particula aux;

    //comprobamos que haya más de un elemento

    if ( tam>1 )
    {

        for ( i = 0 ; i < tam ; i++ )
        {
            for ( j = 0 ; j < tam - i ; j++ )
            {
                if ( v[j].masa > v[j + 1].masa )
                {
                    aux = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = aux;
                }
            }
        }
    }
}

// Insertar ficha

void crear ( particula v[TAM] , int &tam )
{

    string basura;

    cout << "Nombre: ";
    cin.ignore();
    getline ( cin, v[tam].nombre );
    cout << "Símbolo: ";
    cin >> v[tam].simbolo;
    cout << "Masa: ";

    while ( ! ( cin >> v[tam].masa ) )
    {
        cin.clear();
        cin >> basura;          // desechamos los datos erróneos.
        cout << "Introduce un valor numérico, por favor: ";
    }

    cout << "Carga: ";
    cin >> v[tam].carga;
    cout << "Spin: ";
    cin >> v[tam].spin;
    cout << "Grupo: ";
    cin >> v[tam].grupo;
    cout << "Familia: ";
    cin >> v[tam].familia;
    cout << "Generación: ";
    cin >> v[tam].generacion;
    cout << "Lugar descubrimiento: ";
    cin.ignore();
    getline ( cin, v[tam].pais );
    cout << "Fecha descubrimiento: ";

    while ( ! ( cin>>v[tam].any ) )
    {
        cin.clear();
        cin >> basura;          // desechamos los datos erróneos.
        cout << "Introduce un valor numérico, por favor: ";
    }

    cout << endl << "Ficha añadida con éxito" << endl;

    if ( tam==0 )
        tam++;

    ordenar ( v , tam );
}

/**
 * @brief Muestra una, o todas las fichas
 *
 * @param v vector de información
 * @param tam número de fichas
 * @param lista true -> ennumera las fichas
 * @param pos ficha a mostrar. Si pos==1 , las muestra todas
 * @return void
 */

void mostrar ( particula v[TAM] , int tam, bool lista , int pos )
{
    int i , min , max;      //contador

    if ( pos == -1 )
    {
        min = 0;
        max = tam ;
    }
    else
    {
        min = pos;
        max = pos+1;
    }

    for ( i = min ; i < max ; i++ )
    {

        if ( lista == true )
        {
            cout << "[" << i + 1 << "]" << v[i].nombre << endl;
        }
        else
        {
            cout << v[i].nombre << endl;
        }
        cout << "---------------------------" << endl;
        cout << "Símbolo:\t" << v[i].simbolo << endl;
        cout << "Masa:\t\t" << v[i].masa << endl;
        cout << "Carga:\t\t" << v[i].carga << endl;
        cout << "Spin:\t\t" << v[i].spin << endl;
        cout << "Grupo:\t\t" << v[i].grupo << endl;
        cout << "Familia:\t" << v[i].familia << endl;
        cout << "Generación:\t" << v[i].generacion << endl;
        cout << "Descubrimiento:\t" << v[i].any << ", " << v[i].pais << endl;
        cout << endl;
    }
}

// Modifica una ficha seleccionada

void modificar ( particula v[200], int& tam )
{
    int op;
    bool error = false;   //control de errores al elegir opción
    string aux;

    cout << "¿Qué ficha deseas modificar? (seleccionar por número)" << endl;

    mostrar ( v , tam , true , -1 );

    do
    {
        if ( error == true )
        {
            cout << "Lo siento. Parece que esa opción no existe.";
            cout << "Has de elegir una ficha entre 1 y " << tam << endl;
        }


        cout << "Ficha: ";
        cin >> op;

        if ( op < 1 || op > tam )
        {
            error = true;
        }
        else
        {
            error = false;
        }
    }
    while ( op < 1 || op > tam );

    //devolvemos el valor numérico de opción al correspondiente en el vector
    op--;

    cout << endl << "Has elegido modificar la ficha :" << endl;
    mostrar ( v , tam , false , op );

    cout << "Introduce los nuevos valores. Dale a enter directamente si no quieres cambiar nada" << endl;

    cout << "Nombre: ";
    cin.ignore();
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].nombre = aux;
    }

    cout << "Símbolo: ";

    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].simbolo = aux;
    }

    cout << "Masa: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].masa = atoi ( aux.c_str() );
    }

    cout << "Carga: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].carga = aux;
    }

    cout << "Spin: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].spin = aux;
    }

    cout << "Grupo: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].grupo = aux;
    }

    cout << "Familia: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].familia = aux;
    }

    cout << "Generación: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].generacion = aux;
    }

    cout << "Lugar de descubrimiento: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].pais = aux;
    }

    cout << "Fecha de descubrimiento: ";
    getline ( cin , aux );

    if ( aux.length() > 0 )
    {
        v[op].any = atoi ( aux.c_str() );
    }


}

// Borra un elemento a placer

void borrar ( particula v[TAM] , int &tam )
{
    int op , i;
    bool error = false;   //control de errores al elegir opción
    char respuesta;

    cout << "¿Qué ficha deseas borrar? (seleccionar por número)" << endl;

    mostrar ( v , tam , true , -1 );

    do
    {
        if ( error == true )
        {
            cout << "Lo siento. Parece que esa opción no existe.";
            cout << "Has de elegir una ficha entre 1 y " << tam << endl;
        }


        cout << "Ficha: ";
        cin >> op;

        if ( op < 1 || op > tam )
        {
            error = true;
        }
        else
        {
            error = false;
        }
    }
    while ( op < 1 || op > tam );

    //devolvemos el valor numérico de opción al correspondiente en el vector
    op--;

    //comprobación de seguridad
    mostrar ( v , tam , false , op );
    cout << endl << "¿Deseas borrar esta la ficha? (S/N): ";

    cin >> respuesta;

    if ( respuesta=='S' || respuesta=='s' )
    {
        for ( i=op ; i<tam ; i++ )
        {
            v[i]=v[i+1];
        }
        tam--;

        cout << "Borrando..." << endl;
        cout << "Ficha borrada satisfactoriamente" << endl;
    }
    else
    {
        cout << "Cancelando..." << endl;
    }
}

/*
 * Buscar según características
 * Hace de intermediario entre "main" y "buscar"
 */

void buscar_por ( particula v[TAM] , int tam , bool result[TAM] , particula b )
{
    char op;
    int i , flag=0;             //i -> contador ; flag -> comprueba si el vector de resultados está vacío


    cout << "a) Buscar por nombre" << endl;
    cout << "b) Buscar partículas con masa inferior a... " << endl;
    cout << "c) Buscar partículas por masa y espín" << endl;
    cout << "d) Buscar por generación" << endl;
    cout << "e) Buscar partículas por familia y generación" << endl;
    cout << endl << "Elige opción: ";

    cin >> op;
    cout << endl;

    switch ( op )
    {
    case 'a':
        cout << "Nombre: ";
        cin >> b.nombre;
        break;
    case 'b':
        cout << "Masa: ";
        do
        {
            cin >> b.masa;
            if ( b.masa<0 )
                cout << "Introduce una masa positiva, por favor ;)" << endl;
        }
        while ( b.masa<0 );
        break;
    case 'c':
        cout <<"Masa: ";
        cin >> b.masa;
        cout << "Espín: ";
        cin >> b.spin;
        break;
    case 'd':
        cout << "Generación: ";
        cin >> b.generacion;
        break;
    case 'e':
        cout << "Familia: ";
        cin >> b.familia;
        cout << "Generación: ";
        cin >> b.generacion;
        break;
    default:
        cout << "Opción no encontrada" << endl;
        break;
    }

    buscar ( v , tam , result , b );

    // Mostramos resultados

    //(parche) Si el usuario ha escogido la opción b...

    if ( op=='b' )
    {
        for ( i=0 ; result[i]==false ; i++ )
        {
            mostrar ( v , tam , false ,i );
        }
    }

    for ( i=0 ; i<tam+1 ; i++ )
    {
        if ( result[i]==true )
        {
            mostrar ( v , tam , false , i );

            flag++;
        }
    }

    if ( flag==0 )
        cout << "No se han encontrado resultados" << endl;
}

/*
 * Buscar, es una funcion MUY general.
 * Recibe el vector de info y su tamaño.
 * Devuelve un vector del mismo tamaño que el de info, booleano. (true->elemento encontrado)
 * Para ello recibe otra variable de tipo particula, con la info a buscar por cada campo
 * Si un campo no contiene nada para buscar, el resultado no se altera
 * Eso permite una gran flexibilidad
 * Se exige coincidencia total sólo en 'masa' , 'carga' , 'spin' , 'generación' y 'año'
 */

void buscar ( particula v[TAM] , int tam , bool result[TAM] , particula b )
{
    int i, pos;

    for ( i=0 ; i < tam+1 ; i++ )
    {
        result[i]=true;

        pos=v[i].nombre.find ( b.nombre );
        if ( pos == -1 && b.nombre!="" )
            result[i]=false;

        pos=v[i].simbolo.find ( b.simbolo );
        if ( pos == -1 && b.simbolo!="" )
            result[i]=true;

        if ( v[i].masa!=b.masa && b.masa!=0 )
            result[i]=false;

        if ( v[i].carga!=b.carga && b.carga!="" )
            result[i]=false;

        if ( v[i].spin!=b.spin && b.spin!="" )
            result[i]=false;

        pos=v[i].familia.find ( b.familia );
        if ( pos == -1 && b.familia!="" )
            result[i]=false;

        pos=v[i].grupo.find ( b.grupo );
        if ( pos == -1 && b.grupo!="" )
            result[i]=false;

        if ( v[i].generacion!=b.generacion && b.generacion!="" )
            result[i]=false;

        pos=v[i].pais.find ( b.pais );
        if ( pos == -1 && b.pais!="" )
            result[i]=false;

        if ( v[i].any!=b.any && b.any!=0 )
            result[i]=false;
    }
}

// Estadísticas

void estadisticas ( particula v[TAM] , int tam ) //FIXME
{
    char op;
    int min, max;       //período de años
    int i,j , k,aux;    //contadores (aux actúa de bandera)
    int n_paises=1;
    pais p[TAM];
 
    min=INT_MIN;
    max=INT_MAX;
    
    system ("clear");

    cout << "a) Partículas descubiertas en un período de años" << endl;
    cout << "b) %  de partículas descubiertas por país " << endl;
    cout << endl << "Opción: ";

    cin >> op;

    switch ( op )
    {
    case 'a':           //intervalo años
        do
        {
            cout << "Año inicial: ";
            cin >> min;
            cout << "Año final: ";
            cin >> max;
            cout << endl;
        }
        while ( min>=max );
        for ( i=0 ; i<tam+1 ; i++ )
        {
            if ( v[i].any >= min && v[i].any <= max )
                mostrar ( v,tam,false,i );
        }
        break;
    case 'b':           //estadísticas por países

        // calculamos el número de paises y el nº de aportaciones por cada uno
        p[0].pais=v[0].pais;
        p[0].particulas=1;

        for ( i=1 ; i<tam+1; i++ )
        {
            aux=0;
            for ( j=0 ; j<=n_paises+1 ; j++ )
            {
                if ( v[i].pais==p[j].pais )
                {
                    p[j].particulas++;
                    aux++;
                }
            }

            if ( aux==0 )
            {
                n_paises++;
                p[n_paises].pais=v[i].pais;
                p[n_paises].particulas=1;
            }
        }

        cout << endl;
        for ( i=0 ; i<=n_paises ; i++ )
        {
            //Si el pais es desconocido, lo indicamos

            if ( p[i].pais=="" || p[i].pais=="?" )
                p[i].pais="Desconocido";

            cout << p[i].pais << ":\t\t " << p[i].particulas*100/ ( tam+1 ) << "%" << endl;
        }

        /****************GRÁFICAS*******************/
        /*      TODO:verticales                    */

        cout << endl << "Gráfica:" << endl;
        for ( i=0 ; i<=n_paises ; i++ )
        {
            if ( p[i].pais=="" || p[i].pais=="?" )
                p[i].pais="Desconocido";

            cout << p[i].pais << ":\t\t[" ;
            for ( k=0 ; k< ( p[i].particulas*100/ ( 2* ( tam+1 ) ) ) ; k++ )
            {
                cout <<"*";
            }
            for ( k= ( p[i].particulas*100/ ( 2* ( tam+1 ) ) ) ; k<50 ; k++ )
            {
                cout <<"-";
            }
            cout << "]" << endl;
        }

        grafica ( p, n_paises );

        break;
    default:
        cout << "Opción no encontrada" << endl;
        break;
    }
}

// Decide si hay que guardar o no

bool salir ( bool cambios )
{
    char op;
    bool salir;

    if ( cambios==false )
    {
        salir=false;
    }
    else
    {
        cout << "¿Guardar los cambios (S/N)?: ";
        cin >> op;

        if ( op=='S' || op=='s' )
            salir=true;
        else
            salir=false;
    }

    return salir;
}

void guardar ( particula v[200], int tam, string nombre )
{
    ofstream g;
    int i;

    g.open ( nombre.c_str() );

    for ( i=0 ; i<tam ; i++ )
    {
        g << v[i].nombre << endl;
        g << v[i].simbolo << endl;
        g << v[i].masa << "\t" << v[i].carga << "\t" << v[i].spin << endl;
        g << v[i].grupo << "\t" << v[i].familia << "\t" << v[i].generacion << endl;
        g << v[i].pais << endl;
        g << v[i].any << endl;
    }

    // el último endl sobra
    i=tam++;
    g << v[i].nombre << endl;
    g << v[i].simbolo << endl;
    g << v[i].masa << "\t" << v[i].carga << "\t" << v[i].spin << endl;
    g << v[i].grupo << "\t" << v[i].familia << "\t" << v[i].generacion << endl;
    g << v[i].pais << endl;
    g << v[i].any;
}

void grafica ( pais p[TAM] , int tam ) //TODO
{
    int i, j , k,x ,y;

    y=25;
    x=25/ ( tam );

    cout << endl<<endl;
    for ( i=0; i< ( 4*x+2 ); i++ )
        cout << "-";
    cout << endl;

    for ( j=y; j >0 ; j-- )
    {
        cout << "|";
        for ( k=0; k< ( x ) /2 ; k++ )
        {
            cout << " ";
        }

        for ( i=0 ; i<tam+1 ; i++ )
        {

            if ( ( p[i].particulas*25/tam ) >=j )
            {
                cout << " ";
                for ( k=0; k<x-2 ; k++ )
                {
                    cout << "+";
                }
                cout << " ";
            }
            else
            {
                for ( k=0; k<x ; k++ )
                {
                    cout << " ";
                }
            }

        }
        for ( k=0; k< ( x ) /2 ; k++ )
        {
            cout << " ";
        }
        cout << "|";

        cout << endl;
    }
    
    
    for ( i=0 ; i<tam+1 ; i++ )
        {
            for (j=0;j<(x-2)/tam;j++)
            {
                cout <<" ";
            }
            cout << p[i].pais;
        }
    
}

void opciones ( preferencias &def )
{
    ifstream f;
    ofstream g;

    f.open ( "preferencias.txt" );
    if ( !f )
    {
        g.open ( "preferencias.txt" );
        g << "particulas.txt" << endl;

        g.close();
    }

    f >> def.fichero;

    f.close();
}
// kate: indent-mode cstyle; indent-width 4; replace-tabs on; 
