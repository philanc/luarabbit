
# ----------------------------------------------------------------------
# adjust the following to the location of your Lua install
#
#   Lua binary and include files are to be found repectively in 
#   $(LUADIR)/bin and $(LUADIR)/include

LUADIR ?= ../lua

# ----------------------------------------------------------------------

CC= gcc
AR= ar
LUA ?= $(LUADIR)/bin/lua

INCFLAGS= -I$(LUADIR)/include
CFLAGS= -Os -fPIC $(INCFLAGS) 
LDFLAGS= -fPIC

LUARABBIT_O= luarabbit.o rabbit.o 

luarabbit.so:  src/*.c src/*.h
	$(CC) -c $(CFLAGS) src/*.c
	$(CC) -shared $(LDFLAGS) -o luarabbit.so $(LUARABBIT_O)

test:  luarabbit.so
	$(LUA) test/test_luarabbit.lua
	
clean:
	rm -f *.o *.a *.so

.PHONY: clean test

