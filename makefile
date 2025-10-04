##########Compiler stuff################
CC := gcc
FLAGS := -Wall
D_FLAGS := -g -Wall
SRC := src
OBJS := objs
###############Vars####################
#para no tener que andar buscando funciones de shell
#recuerda modificar esto cada que añadas una nueva carpeta
SRC_DIRS = src/collections src/extensions
OBJ_DIRS = $(patsubst ${SRC}/%, ${OBJS}/%, ${SRC_DIRS}) 
DEBUG := -debug
#lista todos los files del sistema (los que pueda encontrar gracais a DIRS) 
C_FILES := $(foreach dir, ${SRC_DIRS}, $(wildcard ${dir}/*.c))
O_FILES := $(patsubst ${SRC}/%.c, ${OBJS}/%.o, ${C_FILES})
O_DEBUG_FILES := $(patsubst ${SRC}/%.c, ${OBJS}/%${DEBUG}.o, ${C_FILES})
########################################

#Debug build 

debug : ${O_DEBUG_FILES}
	@echo Creando debug versions
#Parte encargada de la compilacion
${OBJS}/%${DEBUG}.o: ${SRC}/%.c ${SRC}/%.h
	@echo $^

#para garantizar que los directorios existan y tambien
#garantizar que solo se corra esta regla una vez
${O_DEBUG_FILES} : | ${OBJS} ${OBJ_DIRS} 
${OBJS} :
	@echo Creando directorio objetos
	@mkdir $@
${OBJ_DIRS}:
	@echo Creando directorio $@
	@mkdir $@


#Release build
