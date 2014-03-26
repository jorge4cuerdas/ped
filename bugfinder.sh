#! /bin/bash
# Script made By Anton CH;
# NO COPYRIGHT (Just keep my name)
# NO RESPONSIBILITY!
# Please report all bugs & suggestions to "anton.1990@live.ru"

# Formato de salida:
# ...
# NOMBRE PRUEBA
# ...
# VALGRIND
# ...
# DIFF
# ...
# RESULTADO
# ...
#
#

# Este script hace todo el trabajo mecanico a la hora de probar los "tads". :-)
# Hay que colocarlo en la raiz de de la practica y darle permisos de ejecucion.
# Acepta 2 parametros, el nombre del directorio con los tads, y el nombre del
# ejecutable generado por "make". El segundo argumento es opcional.
# Si valgrind falla, el script para. :-(
# Si alguna de las salidas producidas por la practica no coinciden,
# el script muestra las diferencias y para. :-(
# OJO! Se da por supuesto que el programa no entra en bucles infinitos,
# los directorios y ficheros tienen los permisos r/w/x adecuados. :-)

# RECORDATORIO:
# Las lineas del diff que empiezan por "<" representan la salida del programa
# y las lineas que empiezan por ">" representan la salida correcta;

DEF_EXE="tad"  # Nombre del ejecutable generado por "make";
F_SALIDA="salida.sal"
BAKNAME="_tad.cpp"  # Nombre del bakup de "tad.cpp";
ERR_DIR="ERROR! $1 es un fichero o no existe!"
USAGE="Acepto 2 parametros: 1- Nombre del directorio (sin '/') con tads a testear(OBLIGATORIO). 2- Nombre del ejecutable que genera 'make' (OPCIONAL)."

if !(test -z $1) && (test -d $1)
then
	# Hacer bakup del tad.cpp original (si existe) para evitar sobreescritura;
	# OJO! Si ya hay un bakup, o fichero con nombre del bakup no se hara NADA;
	if (test -f ./src/tad.cpp) && !(test -f ./src/$BAKNAME)
	then
		mv ./src/tad.cpp ./src/$BAKNAME
	fi

	#Copiar tadxx.cpp al directorio src, compilar, ejecutar con valgrind, y comprobar salidas;
	for i in ./$1/tad*.cpp
	do
 		cp $i ./src/tad.cpp

		echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
		echo " Comprobando '$i' "
		echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"

		make -s clean
		make -s

		if (test $? -eq 2)
		then
			echo "*********************************************************************************"
			echo " !!! ERROR AL COMPILAR !!! "
			echo "*********************************************************************************"
			break
		fi

		if !(test -z $2) && !(test -d $2) && (test -x $2)
		then
			(valgrind  ./$2) > $F_SALIDA
		else
			(valgrind  ./tad) > $F_SALIDA
		fi

		if (test $? -eq 2)
		then
			echo "*********************************************************************************"
			echo " !!! REVISA LA PRUEBA '$i' !!! "
			echo " !!! VALGRIND FALLA !!! "
			echo "*********************************************************************************"
			break
		fi

		echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		diff -b $F_SALIDA $i.sal
		if (test $? -eq 0)
		then
			echo "*********************************************************************************"
			echo " LA PRUEBA '$i' SUPERADA CON EXITO! "
			echo "*********************************************************************************"
			echo ""
			echo ""
		elif (test $? -eq 1)
		then
			echo "*********************************************************************************"
			echo " !!! REVISA LA PRUEBA '$i' !!! "
			echo " !!! LAS SALIDAS NO COINCIDEN !!! "
			echo "*********************************************************************************"
			break
		fi
	done

	# Poner tad.cpp original en su sitio
	if (test -f ./src/$BAKNAME) && !(test -z /src/$BAKNAME)
	then
		mv ./src/$BAKNAME ./src/tad.cpp
	fi

	# Limpiar ...
	make -s clean
	rm -f $F_SALIDA
elif (test $# -gt 0) && (test $# -lt 3)
then
	echo $ERR_DIR
fi

if (test $# -eq 0)
then
 	echo $USAGE
fi
