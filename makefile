OUTPUT =		index
CXX =				emcc
CXXFLAGS =	
LFLAGS =		-O3 -o $(OUTPUT).html --shell-file shell_minimal.html -s EXPORTED_FUNCTIONS='["_main","_draw"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
OBJECTS =		juliaset.c
all:		$(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS)
clean:
	rm -f $(OUTPUT).*
