name(){
	basename `realpath .`
}
b(){
	flags=-O2\ -fsanitize=address
	[ a"$1" = a-d ] && flags=-g
	g++ -std=c++11 -lm -Wall -Wno-sign-compare -Wshadow $flags "$(name)".cpp -o "$(name)"
}
e(){
	b "$@"
	for i in "$(name)".in*; do echo $i:; `[ a"$1" = a-d ] && echo valgrind` ./"$(name)" < $i; done
}
n(){
	mkdir "$1"
	cd "$1"
	cp -rn ../template.cpp "$1".cpp
}
