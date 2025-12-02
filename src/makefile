#  A.Zimmermann, Allzweck-Makefile
#  Vorteile:
#  * Nur geänderte C- und H-Dateien werden kompiliert.
#  * C- und O-Dateien werden getrennt gespeichert.
#
#  For MS DOS, for MS Windows, too :-)
#
#-------------------------------------

# Program name
ZIEL = letsgo.exe

# Source codes should be in current directory.
#SRC = start.c methoden.c lib.c
#HDR = adt.h
SRC = $(shell dir /b *.c)
HDR = $(shell dir /b *.h)

# Directory for obj-files.
OBJ_DIR = obj

#------------------------------

# Pattern for obj-files.
OBJ_PAT = $(OBJ_DIR)/%.o
# List of obj-files.
OBJ_DAT = $(SRC:%.c=$(OBJ_PAT))
# Pattern for obj-files as out in gcc.
OBJ_OUT = $(<:%.c=$(OBJ_PAT))

# Linker
$(ZIEL) : $(OBJ_DAT)
	@echo Linking ...
	gcc -o $@ $(OBJ_DAT)

# Compiler
$(OBJ_PAT) : %.c $(HDR)
	@echo Compiling ...
	gcc -c -o $(OBJ_OUT) $<

run:
	cls
	$(ZIEL)

clean:
	@echo Deleting obj-files ...
	del $(OBJ_DIR)\*.o

# Link obj-files only
link:
	@echo Linking obj-files only ...
	gcc -o $(ZIEL) $(OBJ_DAT)

#  =============  EOF  =============
