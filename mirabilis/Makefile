CC = g++
SOURCES = entity.cpp map.cpp model.cpp player.cpp terminal_ui.cpp terminal_ui_game.cpp
CPPFLAGS += -Wall $(INCLUDES)
VPATH = src include
INCLUDES= -Iinclude

OBJECTS = $(subst .cpp,.o,$(SOURCES))

TARGET = terminal_mirabilis

$(TARGET): $(OBJECTS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

.PHONY:
debug: CPPFLAGS += -ggdb
debug: $(TARGET)

.PHONY:
release: CPPFLAGS += -O3
release: $(TARGET)

.PHONY:
clean:
	$(RM) $(OBJECTS) $(TARGET)

#terminal_mirabilis: mirabilis/*.h mirabilis/*.cpp
#	g++ -o terminal_mirabilis -ggdb mirabilis/*.cpp terminal_ui_game.cpp -lncurses
#
#clean:
#	rm terminal_mirabilis
#	rm -rf terminal_mirabilis.dSYM
#


#OS detection and handling code here
ifeq ($(OS),Windows_NT)
 RM := del
 LDFLAGS += -lpdcurses 
 INCLUDES +=
 CPPFLAGS += 
else
 UNAME_S := $(shell uname -s)
 ifeq ($(UNAME_S),Darwin)
  LDFLAGS += -lncurses
 else ifeq ($(UNAME_S),Linux)
  LDFLAGS += -lncurses
 endif
endif
