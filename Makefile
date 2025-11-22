game: game.cpp IO.cpp snake.cpp food.cpp
	g++ game.cpp IO.cpp snake.cpp food.cpp -o game

clean:
	rm -f *.o game

