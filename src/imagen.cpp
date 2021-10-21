#include "imagen.h"
#include <sstream>
#include "imagenES.h"
#include <assert.h>
#include <iostream>

//PRACTICA 2 TDA IMAGEN - ING. INFORMATICA 2A-1
//SERGIO HIDALGO ROMERO NIEVA
using namespace std;

    Imagen::Imagen(){
        img = nullptr;
        filas = 0;
        cols = 0;
    }

    Imagen::Imagen(int nfilas, int ncols){

        filas = nfilas;
        cols = ncols;
        reservar();
    }
    
    Imagen::Imagen(const Imagen &copy){

        filas = copy.filas;
        cols = copy.cols;

        img = new byte*[filas];
        for(int i=0; i<filas; i++){

            *(img + i) = new byte[cols];

            for(int j=0; j<cols; j++){
                *(*(img+i) + j) = *(*(copy.img + i) + j);
            }
        }
    }

    Imagen::Imagen(const char *nombre){
        this->decode(LeerImagenPGM(nombre, filas, cols));   
    }

    Imagen::~Imagen(){
        for(int i=0;i<filas;i++){
            delete[] *(img + i);
        }
        img = nullptr;
        filas = 0;
        cols = 0;
    }

    void Imagen::liberar(){
        if(img != 0){
            for(int i=0; i < filas; i++){
                delete[] *(img + i);
            }
            delete[] img;
            img = nullptr;
        }
    }
    
    void Imagen::reservar(){
        img = new byte*[filas]; 
        
        for(int i = 0; i < filas; i++){
            *(img + i) = new byte[cols];
        }
    }

    int Imagen::num_filas() const{
        return filas;
    }


    int Imagen::num_columnas() const{
        return cols;
    }


    void Imagen::asigna_pixel(int fila, int col, byte valor){
        if((fila>=0 && fila < filas) && (col>=0 && col < cols) && (valor>=0 && valor<=255)){
            *(*(img + fila) + col) = valor;
        }
    }


    byte Imagen::valor_pixel(int fila, int col) const{
        if((fila>=0 && fila < filas) && (col>=0 && col < cols)){
            return *(*(img+fila)+col);
        }
    }


    void Imagen::operator=(const Imagen &copia){
        for(int i=0; i<filas; i++){
            delete[] *(img + i);
        }

        for(int i=0; i<filas; i++){
            for(int j=0; j<cols; j++){
                asigna_pixel(i, j, *(*(copia.img+i)+j) );
            }
        }
    }


    void Imagen::decode(const byte *ptr){
        liberar();
        reservar();
        for(int i=0; i<filas*cols; i++){
            asigna_pixel(i/cols, i%cols, *(ptr + i)); 
        }
    }


    byte* Imagen::encode(){
        byte* bytes = new byte[this->num_filas()*this->num_columnas()];
        int k = 0;
        for(int i=0; i<this->num_filas(); i++){
            for(int j=0; j<this->num_columnas(); j++){
                *(bytes + k) = this->valor_pixel(i,j);
                k++;
            }
        }
        return bytes;
    }

    void Imagen::guardar(const char *nombreImagen){
        EscribirImagenPGM(nombreImagen, encode(), filas, cols);
    }

    void Imagen::umbralizar(const char *imagenEntrada, const char *imagenSalida, int limInf, int max){
        Imagen *aux = new Imagen(imagenEntrada);
        for(int i = 0; i < aux->filas; i++){
            for(int j = 0; j<aux->cols; j++){
                if( (aux->valor_pixel(i, j) <= limInf) || (aux->valor_pixel(i, j) >= max) ){
                    aux->asigna_pixel(i, j, 255);
                }
            }
        }
        aux->guardar(imagenSalida);
    }

    void Imagen::zoom(const char *imagenEntrada, const char *imagenSalida, int x_1, int y_1, int x_2, int y_2){
        
        
        Imagen *origen = new Imagen(imagenEntrada);

        //Si el rectángulo se sale de la imagen, lo ajusta para que tenga las dimensiones de la imagen
        if(x_2 > origen->filas-1){
            x_2 = origen->filas-1;
        }
        
        if(y_2 > origen->cols-1){
            y_2 = origen->cols-1;
        }

        Imagen *fin = new Imagen((y_2-y_1)*2 - 1, (x_2-x_1)*2 - 1);
                

        //Ver si la expresion es valida
        if(x_1 < 0 || x_1 > origen->filas || y_1 < 0 || y_1 > origen->cols || x_2<0 || x_2 > origen->filas || y_2<0 || y_2 > origen->cols || x_1 > x_2 || y_1 > y_2 || (x_2-x_1 != y_2-y_1) ){
            cout << "EXPRESION MAL HECHA EN EL ZOOM, AUN ASÍ FUNCIONA Y POR ESO HE DEJADO QUE SIGA PERO SI QUIERE QUE NO FUNCIONE QUITE LOS COMENTARIOS DE ABAJO" << endl;
            //assert(false);
        }

        //Copiar rectangulo de imagen original sobre la final de forma "salteada"
        for(int i=0; i<fin->filas; i+=2){
            for(int j=0; j<fin->cols; j+=2){
                fin->asigna_pixel(i, j, origen->valor_pixel( (y_1+i/2), (x_1+j/2)));
            }
        }

        //Rellenar los huecos de las columnas con las medias de sus horizontales
        for(int i=0; i<fin->filas; i+=2){
            for(int j=1; j<fin->cols; j+=2){
                fin->asigna_pixel(i, j, (fin->valor_pixel(i, j-1)+fin->valor_pixel(i, j+1) ) /2 +0.5 );
            }
        }

        //Rellenar los huecos de las filas con las medias de sus verticales
        for(int i=1; i<fin->filas; i+=2){
            for(int j=0; j<fin->cols; j++){
                fin->asigna_pixel(i, j, (fin->valor_pixel(i-1, j)+fin->valor_pixel(i+1, j) ) /2 +0.5 );
            }
        }

        fin->guardar(imagenSalida);
    }
    
    void Imagen::contraste(const char *imagenEntrada, const char *imagenSalida, int min, int max){

        //Buscamos cuales son los valores maximos y minimos de la Imagen
        byte minImg = 255;
        byte maxImg = 0;
        byte current;
        Imagen *origen = new Imagen(imagenEntrada);
        Imagen *destino = new Imagen(imagenEntrada);

        for(int i=0; i<origen->filas; i++){
            for(int j=0; j<origen->cols; j++){
                current = origen->valor_pixel(i, j);
                if( current < minImg){
                    minImg = current;
                }
                else if(current > maxImg){
                    maxImg = current;
                }
            }
        }

        //Aplicamos la transformacion lineal
        const double contraccion = (max - min)*1.0/(maxImg - minImg);
        for(int i=0; i<origen->filas; i++){
            for(int j=0; j<origen->cols; j++){
                destino->asigna_pixel(i, j, (contraccion * (origen->valor_pixel(i, j)) ) + min + 0.5);
            }
        }

        destino->guardar(imagenSalida);

    }

    void Imagen::morphing(const char *imagenEntrada, const char *imagenObjetivo, const char *animacion, int numPasos){
        Imagen *origen  = new Imagen(imagenEntrada);
        Imagen *fotograma = new Imagen(imagenEntrada);
        Imagen *objetivo = new Imagen(imagenObjetivo);

        byte pixelOrigen = 0;
        byte pixelObjetivo = 0;
        byte pixelPaso = 0;

        string s;

        float paso = (1.0/(numPasos-1));
        float alfa = 0.0f;
        //Hacemos numIter modificaciones de la imagen
        for(int k=0; k<numPasos; k++){
            alfa = 1 - paso*k;
            //Recorremos toda la imagen
            for(int i=0; i<fotograma->filas; i++){
                for(int j=0; j<fotograma->cols; j++){                   
                    //Modificamos el valor de cada pixel
                    pixelOrigen = origen->valor_pixel(i, j);
                    pixelObjetivo = objetivo->valor_pixel(i, j);

                    pixelPaso = alfa*pixelOrigen + (1-alfa)*pixelObjetivo + 0.5;

                    fotograma->asigna_pixel(i, j, pixelPaso);
                }
            }
            //Guardamos cada modificacion de cada imagen
            s = animacion;
            s += to_string(k);
            fotograma->guardar(s.c_str());
        }
    }


    



