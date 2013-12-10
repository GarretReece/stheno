CC = g++
SOURCES = vector2f.cpp vector2s.cpp vector3f.cpp vector3s.cpp quaternion.cpp matrix4d.cpp sprite.cpp render_object.cpp physics_object.cpp ship.cpp main.cpp
CPPFLAGS += -Wall $(INCLUDES)
VPATH = src include
INCLUDES= -Iinclude

OBJECTS = $(subst .cpp,.o,$(SOURCES))

TARGET = ships

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

stupidSnake: glStupidSnakeGlut.cpp
	$(CC) -ggdb -o $@ $< $(LDFLAGS)

quaternion_rotate: quaternion_rotate.cpp src/quaternion.cpp
	$(CC) -o $@ $(CPPFLAGS) quaternion_rotate.cpp src/quaternion.cpp src/matrix4d.cpp src/vector3f.cpp src/vector2f.cpp $(LDFLAGS)

#OS detection and handling code here
ifeq ($(OS),Windows_NT)
 RM := del
 LDFLAGS += -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
 INCLUDES += -I"C:\Program Files\Common Files\MinGW\freeglut\include"
 CPPFLAGS += -m32
else
 UNAME_S := $(shell uname -s)
 ifeq ($(UNAME_S),Darwin)
  LDFLAGS += -framework OpenGL -framework GLUT
 else ifeq ($(UNAME_S),Linux)
  LDFLAGS += -lopengl -lglut
 endif
endif
