#ifndef _IMAGEN_H_
#define _IMAGEN_H_

typedef unsigned char byte;

class Imagen{

    private:

        byte **img = nullptr;
        int filas;
        int cols;

    public:

        /**
         * @brief Crea una imagen de 0 filas, 0 columnas, en un lugar no valido
         */
        Imagen();

        /**
         * @brief Crea una imagen de nfilas filas y ncols columnas
         * @param nfilas Numero de filas de la nueva imagen (Resolucion vertical)
         * @param ncols Numero de columnas de la nueva imagen (Resolucion horizontal)
         */
        Imagen(int nfilas, int ncols);

        /**
         * @brief Constructor copia, crea una imagen a parti de otra con su misma resolucion e imagen
         * @param copy El objeto Imagen a partir del cual crear el nuevo objeto
         */
        Imagen(const Imagen &copy);

        /**
         * Carga una imagen del directorio activo
         * @param nombre El nombre de la imagen a cargar
         */
        Imagen(const char *nombre);

        /**
         * @brief Destructor de la clase Imagen
         */
        ~Imagen();

        /**
         * @brief Libera el espacio asignado a la matriz bidimensional de la Imagen
         */
        void liberar();

        /**
         * @brief Reservar memoria para la imagen basado en las filas y las columnas del objeto Imagen
         */
        void reservar();

        /**
         * @brief Consulta el numero de filas de la imagen
         * @return El numero de filas de la imagen
         */
        int num_filas() const;

        /**
         * @brief Consulta el numero de columnas de la imagen
         * @return El numero de columnas de la imagen
         */
        int num_columnas() const;

        /**
         * @brief Modifica el valor de un pixel de la imagen
         * @param fila Fila en la que se encuentra el pixel a modificar
         * @param col Columna en la que se encuentra el pixel a modificar
         * @valor valor Valor que se le va a asignar al pixel
         */
        void asigna_pixel(int fila, int col, byte valor);

        /**
         * @brief Consulta el valor de un pixel de la imagen
         * @param fila Fila en la que se encuentra el pixel a devolver
         * @param col Columna en la que se encuentra el pixel a devolver
         * @return Un byte representando el valor del pixel de la fila y columna
         */
        byte valor_pixel(int fila, int col) const;

        /**
         * @brief Sobrecarga de operador = para la clase Imagen
         */
        void operator=(const Imagen &copia);
        
        /**
         * @brief Decodifica el vector de datos de una imagen de un fichero PGM 
         * y la mete en la matriz bidimensional de la imagen sobre la que se usa el metodo
         * @param ptr el puntero que apunta al vector unidimensional de datos que devuelve la funcion leer_imagen
         */ 
        void decode(const byte *ptr);
        
        /**
         * @brief Codifica el valor de la imagen bidmensional en un unico vector unidimensional que se puede guardar en un archivo PGM
         * @return puntero a vector de pixeles codificado de la imagen
         */                
        byte* encode();
        
        /**
         * @brief Guardar Imagen en fichero
         * @param nombreImagen nombre del fichero en el que guardar la imagen
         */
        void guardar(const char *nombreImagen);

        /**
         * @brief Umbraliza una imagen al rango determinado, mantiene unicamente los pixeles
         * que están en el rango indicado, dejando los demás en blanco.
         * @param imagenEntrada La imagen a umbralizar
         * @param imagenSalida Fichero donde se guardará la imagen umbralizada
         * @param limInf Limite inferior del umbral
         * @param limSup Limite superior del umbral
         */
        void umbralizar(const char *imagenEntrada, const char *imagenSalida, int limInf, int limSup);

        /**
         * @brief Guarda una imagen a la que se le ha hecho zoom a una zona rectangular específica
         * @param imagenEntrada Imagen a la que se le quiere hacer zoom
         * @param imagenSalida Imagen con zoom y en que ficehro se quiere guardar
         * @param x1/2,y1/2 Los puntos que definen el rectángulo al que se le quiere hacer zoom siendo x1,y1 
         * el punto superior izquierdo y x2,y2 el punto inferior derecho.
         */
        void zoom(const char *imagenEntrada, const char *imagenSalida, int x_1, int y_1, int x_2, int y_2);

        /**
         * @brief Modifica el contraste de una imagen
         * @param imagenEntrada Imagen a la que se le quiere hacer zoom
         * @param imagenSalida Imagen con zoom y en que ficehro se quiere guardar
         * @param limInf Nivel de gris mas bajo
         * @param limSup Nivel de gris mas alto
         */
        void contraste(const char *imagenEntrada, const char *imagenSalida, int limInf, int limSup);

        /**
         * @brief Crea un conjunto de imagenes de nombre animacion[i], siendo i el indice del fotograma de la transicion
         * que se transforman en la imagen objetivo
         * @param imagenEntrada Imagen con la que empieza la animacion
         * @param imagenObjetivo Imagen con la que termina la animacion
         * @param animacion Sufijo de las imagenes de la animacion
         * @param numIteraciones Numero de fotogramas que tendrá la transición
         * @pre Hay que tener en cuenta qeu si el tamaño de las imagenes a las que hacer la transicion es distinto
         * se puede dar comportamiento inesperado, no dará error pero nos podemos quedar con mitad de la imagen o con una parte en negro etc.
         */
        void morphing(const char *imagenEntrada, const char *imagenObjetivo, const char *animacion, int numIteraciones);


        
};

#endif