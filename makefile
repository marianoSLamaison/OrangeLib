FLAGS := -Wall
D_FLAGS := -g -Wall
SRC := src
#para no tener que andar buscando funciones de shell
#recuerda modificar esto cada que añadas una nueva carpeta
VPATH = src/sllist
#lista todos los files del sistema (los que pueda encontrar gracais a VPATH)
C_FILES := $(wildcard $(VPATH)/*.c)
#remplaza el directorio raiz i la terminacion de los archivos apra meterlos en el directorio objetos
#para mantener todo mas limpio y no tener que asegurarme que todos los sub files tengan nombre unicos
O_FILES := $(patsubst src/%.c, objs/%.o, ${C_FILES})




#Debug build 

debug : 
	echo ${C_FILES}
	echo ${O_FILES}


#Release build
