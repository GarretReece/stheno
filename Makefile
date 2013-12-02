CC = g++
SOURCES = vector2f.cpp vector2s.cpp vector3f.cpp vector3s.cpp quaternion.cpp matrix4d.cpp render_object.cpp ship.cpp main.cpp
CPPFLAGS += -Wall $(INCLUDES)
LDFLAGS = -framework OpenGL -framework GLUT
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
	rm -rf $(OBJECTS) $(TARGET)

stupidSnake: glStupidSnakeGlut.cpp
	$(CC) -ggdb -o $@ $< $(LDFLAGS)
