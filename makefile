OUTPUT =		juliaset
CXX =				emcc
CXXFLAGS =	
LFLAGS =		-O3 -o $(OUTPUT).html --shell-file shell_minimal.html -s EXPORTED_FUNCTIONS='["_main","_checkbox","_setDelay","_updateParameters"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["cwrap"]'
OBJECTS =		juliaset.c
all:		$(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS)
clean:
	rm -f $(OUTPUT).html $(OUTPUT).js $(OUTPUT).wasm
