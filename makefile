OUTPUT =		index
CXX =				emcc
CXXFLAGS =	
LFLAGS =		-o $(OUTPUT).html --shell-file shell_minimal.html
OBJECTS =		juliaset.c
all:		$(OBJECTS)
	$(CXX) $(LFLAGS) $(OBJECTS)
clean:
	rm -f $(OUTPUT).*
