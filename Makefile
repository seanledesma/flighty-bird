# Compiler and Directories
COMPILER = clang
EMCC = emcc
CFILES = src/*.c
SOURCE_LIBS = -Ilib/

# macOS-specific options
OSX_OPT = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
OUTPUT = bin/build_osx

# Web-specific options
WEB_OUTPUT = web/game.html
WEB_SOURCE_LIBS = -I. -Ilib/ -Lweb/
WEB_FLAGS = -Os -Wall -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB

# Build Target for macOS
build_osx: 
	$(COMPILER) $(CFILES) $(SOURCE_LIBS) $(OSX_OPT) -o $(OUTPUT)

# Build Target for Web
build_web: 
	$(EMCC) -o $(WEB_OUTPUT) $(CFILES) $(WEB_FLAGS) web/libraylib.a $(WEB_SOURCE_LIBS)

# Run Target
run: build_osx
	./$(OUTPUT)

# Clean Target
clean:
	rm -f $(OUTPUT) $(WEB_OUTPUT)
