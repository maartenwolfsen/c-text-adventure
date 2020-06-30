PROGRAM = thetraveler

SRC = .\src\game.c
INC = .\include

all: $(SRC)
	cl /Fe$(PROGRAM).exe $(SRC) \
	/I$(INC) \
	/link /LIBPATH:lib\win64
