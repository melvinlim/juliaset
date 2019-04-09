OUTPUT =		index
CXX =				emcc
CXXFLAGS =	
LFLAGS =		-o $(OUTPUT).html --shell-file shell_minimal.html -s EXPORTED_FUNCTIONS='["_test","_draw"]' -s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'
OBJECTS =		juliaset.c
all:		$(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS)
clean:
	rm -f $(OUTPUT).*
