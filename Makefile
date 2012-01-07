
INCLUDES := -I/usr/autodesk/maya2010-x64/include -Isrc

DEFINES := -DLINUX -D_BOOL -DREQUIRE_IOSTREAM

CFLAGS := -fPIC -Wall -Werror -Wextra

LIBS   := -L/usr/autodesk/maya2010-x64/lib -lOpenMaya -lOpenMayaUI -lFoundation -lGL -lGLU
LFLAGS := -Wl,-Bsymbolic

all:
	mkdir -p obj plugin
	g++ -c tests/examples.cc $(CFLAGS) $(INCLUDES) $(DEFINES) -o obj/examples.o
	
	g++ -c tests/example-plugin.cc $(CFLAGS) $(INCLUDES) $(DEFINES) -o obj/example-plugin.o
	g++ obj/example-plugin.o obj/examples.o $(LFLAGS) $(LIBS) -shared -o plugin/example-plugin.so
	
	g++ -c tests/opinionated-example-plugin.cc $(CFLAGS) $(INCLUDES) $(DEFINES) -o obj/opinionated-example-plugin.o
	g++ obj/opinionated-example-plugin.o obj/examples.o $(LFLAGS) $(LIBS) -shared -o plugin/opinionated-example-plugin.so

clean:
	rm -fr obj plugin 

