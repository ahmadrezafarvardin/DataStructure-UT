CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

SOURCES = Song.cpp CircularDoubleLinkedList.cpp Playlist.cpp PlaybackState.cpp MusicPlayer.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = music_player

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean