# Sistema ambulatorio de bajo coste para el diagnóstico automático de epilepsia#

En este repositorio se encuentra el código y documentación generados durante el Proyecto Fin de Carrera. Se ha desarrollado un algoritmo para la detección automática de epilepsia siguiendo un modelo Bag-Of-Words (BoW). Además, para el Proyecto se ha contado un equipo EEG  con el que se ha podido obtener un sistema ambulatorio de bajo coste, que junto al algoritmo desarrollado pretende ofrecer una solución a los problemas derivados de la accesibilidad a las alternativas de diagnóstico.

# Estructura#

* **doc** Memoria del proyecto. Contiene todas las tablas, imágenes, listados, etc que aparecen en la misma.:
* **main**  Desarrollo principal del PFC
* **steps** Diferentes etapas de las que se compone el PFC. Se desarrollan  por separado y se van intengrando en el directorio main/ 

# Objetivo#

Este Proyecto Fin de Carrera se marca como objetivo buscar alternativas a los 
servicios de diagnóstico que complementen a los actuales o sirvan como base para futuros trabajos
que acaben proporcionando soluciones completamente eficaces y funcionales. 
Para ello, se busca desarrollar un sistema ambulatorio de bajo coste para el diagnóstico automático de la
epilepsia. En ningún caso se pretende sustituir al personal sanitario sino facilitar su trabajo y 
mejorar la calidad de la atención médica, favoreciendo la accesibilidad a este recurso básico 
para el diagnóstico de la epilepsia redundando en beneficio de toda la sociedad.

# Instalación#

## Memoria ##

Se puede descargar la memoria en formato pdf o bien se puede 
compilar desde los archivos fuente. Para ello es necesario 
instalar el paquete arco-pfc.
Más información:
https://bitbucket.org/arco_group/arco-pfc

## Training##

El código se puede compilar ejecutando en un terminal

$ make main-train

Es necesario instalar la librería mlpack. El proceso de instalación
se detalla en el directorio steps/clustering

Se trata de un programa que entrena el sistema usando dos 
datasets, que se indican en la clase principal main-train.cpp

## Testing##

El código se puede compilar ejecutando en un terminal

$ make main-predict

Predice las etiquetas (definidas en el entrenamiento) de una serie
de datasets.
# pfc
