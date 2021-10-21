#include "imagen.h"
//#include "imagenES.h"
#include <iostream>
#include <string>

using namespace std;

void sintaxis()
{
    cerr << "Sintaxis:" << endl;
    cerr << "   FUNCION A USAR:" << endl;
    cout << "       1 = Umbralizar\n";
    cout << "       2 = Zoom\n";
    cout << "       3 = Contraste\n";
    cout << "       4 = Morphing\n";
    cerr << "   IMAGEN SOBRE LA QUE REALIZAR LA FUNCION(con nombre de extension) " << endl;
    cerr << "   FICHERO DONDE GUARDAR LA IMAGEN MODIFICADA(con nombre de extension)" << endl;
    cerr << "   LIMITE INFERIOR Y SUPERIOR O COORDENADAS DE LOS PUNTOS QUE FORMAN EL RECTANGULO DEPENDIENDO DE LA FUNCION" << endl << endl;
    cerr << "   SUFIJO DE LOS ARCHIVOS QUE GUARDARAN LA ANIMACION" << endl;
    cerr << "EJEMPLO1:\n1 vacas.pgm vacasUmbralizadas.pgm 30 120" << endl;
    cerr << "EJEMPLO2:\n2 vacas.pgm vacasZoom.pg 20 10 100 120" << endl;
    cerr << "EJEMPLO3:\n4 niveles.pgm castillo.pgm 24 0 0 0 transicion" << endl;
}


int main(int argc, char *argv[]){

    /*LAS IMAGENES DEBEN ESTAR LOCALIZADAS EN EL DIRECTORIO ACTIVO
    POR LA TERMINAL, DE LO CONTRARIO NO SE PODRA ENCONTRAR LA IMAGEN*/
    
    /*ES RECOMENDABLE GUARDAR LA ANIMACION EN UNA CARPETA APARTE, 
    TENER ACTIVA UNA CARPETA DISTINTA Y DE AHÍ LLAMAR AL BIN/MAIN*/

    /*LAS IMAGENES DEBEN SER PGM*/
    
    sintaxis();

    // Lee Y muestra los parametros que has introducido
    cout << "\n\n\nTUS OPCIONES SON: "                      << "\n";
    int opcion = atoi(argv[1]);    
    cout << "\n\tFUNCION: " << opcion                       << "\n";
    char *nombreImagen1 = argv[2];    
    cout << "\n\tnombreImagenOrigen: " << nombreImagen1     << "\n";    
    char *nombreImagen2 = argv[3];
    cout << "\n\tnombreImagenDestino: " << nombreImagen2    << "\n";
    char *nombreImagen3 = argv[8];

    int x1, y1, x2, y2;
    if(argc > 4){
        x1 = atoi(argv[4]);
        cout << "\tx1= " << x1 << "\n";
        y1 = atoi(argv[5]);        
        cout << "\ty1= " << y1 << "\n";
        if(argc > 6){
            x2 = atoi(argv[6]);
            cout << "\tx2= " << x2 << "\n";
            y2 = atoi(argv[7]);             
            cout << "\ty2= " << y2 << "\n";
            if(argc > 8){
                char *nombreImagen3 = argv[8];
                cout << "\n\tnombreImagenAnimacion: " << nombreImagen3  << "\n";
            }
        }
    }
    cout << endl;

    //Crear un objeto de la clase Imagen vacío
    Imagen *a = new Imagen();

    switch(opcion){
        case 1:
            a->umbralizar(nombreImagen1, nombreImagen2, x1, y1);
        break;

        case 2:
            a->zoom(nombreImagen1, nombreImagen2, x1, y1, x2, y2);
        break;

        case 3:
            a->contraste(nombreImagen1, nombreImagen2, x1, y1);
        break;

        case 4:
            a->morphing(nombreImagen1, nombreImagen2, nombreImagen3, x1);
        break;

        default:
            sintaxis();

    }
    
    return 0;

}
