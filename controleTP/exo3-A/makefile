#------------------------------------------------------------------------------
# Makefile generique pour c++
#------------------------------------------------------------------------------

# fichiers .hpp dans le dossier src
HPP_FILES := $(wildcard src/*.hpp)

# fichiers .cpp dans le dossier src
CPP_FILES := $(wildcard src/*.cpp)

#fichiers .o dans un dossier obj
OBJ_FILES := $(patsubst src/%.cpp, obj/%.o, $(CPP_FILES))

# commandes de compilation
CC_FLAGS = -O1 -Wall -std=c++11
# -O1 compromis entre rapidite et optimisation de code
# -Wall affichier tous les warnings
# -std=c++11 compiler les classes STL en mode C++11

# commandes d'edition de lien (décommenter pour une utilisation de la SFML)
LD_FLAGS =  -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

application: $(OBJ_FILES)
	g++ -o $@ $^ $(LD_FLAGS)

obj/%.o: $(CPP_FILES) $(HPP_FILES)
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -rf obj/*.o application

indent:
	astyle --style=allman --indent-switches src/*.cpp src/*.hpp
