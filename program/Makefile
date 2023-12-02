CPP   := g++ -std=c++17
FLAGS := -O1 -Werror

calculator: driver.cpp        \
			lexer/lexer.cpp   \
			parser/parser.cpp \
			user_interface/user_interface.cpp
	$(CPP) $(FLAGS) $^ -o $@

clean:
	rm calculator