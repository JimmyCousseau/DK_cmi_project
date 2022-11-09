CXX = clang++
CXXFLAGS = -Wall -g -O2 -std=c++11
LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

TARGETS = main

all: $(TARGETS)

$(TARGETS): Element.o Rectangle.o Circle.o Math.o Game.o Maps.o Physics.o Player.o Text.o ScoreBoard.o Inputs.o Resources.o DonkeyKong.o FallingBarrel.o Hammer.o Weapon.o main.o
	$(CXX) $(LDFLAGS) Element.o Rectangle.o Circle.o Math.o Game.o Maps.o Physics.o Player.o Text.o ScoreBoard.o Inputs.o Resources.o DonkeyKong.o FallingBarrel.o Hammer.o Weapon.o main.o -o $(TARGETS)
Element.o: Element.cc Element.hpp Math.hpp
	$(CXX) $(CXXFLAGS) -c -o Element.o Element.cc
Rectangle.o: Rectangle.cc Rectangle.hpp Element.hpp
	$(CXX) $(CXXFLAGS) -c -o Rectangle.o Rectangle.cc
Circle.o: Circle.cc Circle.hpp Element.hpp
	$(CXX) $(CXXFLAGS) -c -o Circle.o Circle.cc
Math.o: Math.cc Math.hpp
	$(CXX) $(CXXFLAGS) -c -o Math.o Math.cc
Game.o: Game.cc Game.hpp Element.hpp Rectangle.hpp Circle.hpp Physics.hpp Player.hpp Text.hpp Inputs.hpp
	$(CXX) $(CXXFLAGS) -c -o Game.o Game.cc
Maps.o: Maps.cc Maps.hpp Rectangle.hpp Circle.hpp Text.hpp Resources.hpp Hammer.hpp Hammer.hpp Weapon.hpp
	$(CXX) $(CXXFLAGS) -c -o Maps.o Maps.cc
Physics.o: Physics.cc Physics.hpp Math.hpp Element.hpp
	$(CXX) $(CXXFLAGS) -c -o Physics.o Physics.cc
Player.o: Player.cc Player.hpp Weapon.hpp Resources.hpp Inputs.hpp
	$(CXX) $(CXXFLAGS) -c -o Player.o Player.cc
Text.o: Text.cc Text.hpp Element.hpp
	$(CXX) $(CXXFLAGS) -c -o Text.o Text.cc
ScoreBoard.o: ScoreBoard.cc ScoreBoard.hpp Rectangle.hpp Text.hpp
	$(CXX) $(CXXFLAGS) -c -o ScoreBoard.o ScoreBoard.cc
Inputs.o: Inputs.cc Inputs.hpp
	$(CXX) $(CXXFLAGS) -c -o Inputs.o Inputs.cc
Resources.o: Resources.cc Resources.hpp
	$(CXX) $(CXXFLAGS) -c -o Resources.o Resources.cc
DonkeyKong.o: DonkeyKong.cc DonkeyKong.hpp Rectangle.hpp FallingBarrel.hpp
	$(CXX) $(CXXFLAGS) -c -o DonkeyKong.o DonkeyKong.cc
FallingBarrel.o: FallingBarrel.cc FallingBarrel.hpp Circle.hpp
	$(CXX) $(CXXFLAGS) -c -o FallingBarrel.o FallingBarrel.cc
Weapon.o: Weapon.cc Weapon.hpp Rectangle.hpp Player.hpp
	$(CXX) $(CXXFLAGS) -c -o Weapon.o Weapon.cc
Hammer.o: Hammer.cc Hammer.hpp Weapon.hpp
	$(CXX) $(CXXFLAGS) -c -o Hammer.o Hammer.cc
main.o: main.cc Game.hpp Maps.hpp
	$(CXX) $(CXXFLAGS) -c -o main.o main.cc

clean:
	rm -f $(TARGETS) && rm -f *.o