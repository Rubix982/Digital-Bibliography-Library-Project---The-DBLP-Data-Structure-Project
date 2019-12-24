CPRDIR=../packages/cpr_x64-linux/cpr/
CURLDIR=../packages/curl_x64-linux/include/curl/*.h
CFLAGS=-I$(CPRDIR) -I$(CURLDIR) -I./container/*.h -lcurl -I/usr/include/python2.7 -lpython2.7 -std=c++17 -Wno-register
CC=g++

_LOCALDEP=./algorithms/*.h ./api/*.h ./dataStructures/*.h ./container/*.h 
_DEPS = $(CURLDIR) $(CPRDIR)../include/cpr/*.h $(_LOCALDEP)
DEPS= $(_DEPS)

_LOCALOBJ=./dataStructures/*.cpp ./api/*.cpp ./algorithms/*.cpp ./container/*.cpp
_OBJ=main.cpp $(CPRDIR)*.cpp $(_LOCALOBJ)
OBJ=$(_OBJ)

%.o: %.c $(DEPS)
	@ $(CC) $(CFLAGS) -c $< -o $@ 

Project: $(OBJ)
	@ $(CC) -o $@ $^ $(CFLAGS) 