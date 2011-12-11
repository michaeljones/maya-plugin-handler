
INCLUDES := -I/usr/autodesk/maya2010-x64/include

DEFINES := -DLINUX -D_BOOL -DREQUIRE_IOSTREAM

CFLAGS := -fPIC -Wall -Werror -Wextra

LIBS   := -L/usr/autodesk/maya2010-x64/lib -lOpenMaya -lOpenMayaUI -lFoundation -lGL -lGLU
LFLAGS := -Wl,-Bsymbolic

all:
	mkdir -p obj
	g++ -c examples.cc $(CFLAGS) $(INCLUDES) $(DEFINES) -o obj/examples.o
	
	g++ -c example-plugin.cc $(CFLAGS) $(INCLUDES) $(DEFINES) -o obj/example-plugin.o
	g++ obj/example-plugin.o obj/examples.o $(LFLAGS) $(LIBS) -shared -o example-plugin.so
	
	g++ -c opinionated-example-plugin.cc $(CFLAGS) $(INCLUDES) $(DEFINES) -o obj/opinionated-example-plugin.o
	g++ obj/opinionated-example-plugin.o obj/examples.o $(LFLAGS) $(LIBS) -shared -o opinionated-example-plugin.so

clean:
	rm -fr obj
	rm -f example-plugin.so
	rm -f opinionated-example-plugin.so

