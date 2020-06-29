PROGRAM = thetraveler

SRC = .\src\game.c
DIST = .\dist
INC = .\include

all: $(SRC)
	cl /Fe$(DIST)\$(PROGRAM).exe $(SRC) \
	/I$(INC) \
	/link /LIBPATH:lib\win64
