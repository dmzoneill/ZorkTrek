#!/bin/bash
# main menu 

find . -iname "*~" -exec rm {} \;

compile=`cat ./data/lastcompile`
debug=`cat ./data/lastcompiledebug`

while [ answer != "0" ] 
do
clear
echo ""
echo -e "\e[00;31mZorktrek build menu\e[00m"
echo ""
echo -e "\e[00;34mSelect option\e[00m"
echo -e ""
echo -e "\e[00;34m1\e[00m)  compile release (${compile})"
echo -e "\e[00;34m2\e[00m)  compile debug (${debug})"
echo -e " "
echo -e "\e[00;34m3\e[00m)  execute release"
echo -e "\e[00;34m4\e[00m)  execute debug"
echo -e " "
echo -e "\e[00;31m0\e[00m)  \e[00;31mexit\e[00m"
echo -e ""
resize -s 40 110 >/dev/null
read -p "> " answer
    case $answer in
       0) 
	  echo -e "\e[00;34mgood luck\e[00m"
          echo ""
	  clear
          break	 
       ;;
       1) 
	  start_time=$(date +%s)
          echo -e "\e[00;34mcompiling release ....\e[00m"
          g++ -O2 -Wall -w `sdl-config --cflags --libs` -lpthread -lGL -lGLU -lSDL_image -lSDL_ttf -lSDL_mixer -I ./header ./source/*.cpp -o ./bin/zorkTrek          
          finish_time=$(date +%s)
          echo "compilation took : $((finish_time - start_time)) secs."
          echo "done"          
          du -sh ./bin/*
          date > ./data/lastcompile
          sleep 5	
       ;;
       2) 
          start_time=$(date +%s)
          echo -e "\e[00;34mcompiling debug ....\e[00m"
          date > ./data/lastcompiledebug
          g++ -O2 -Wall -w -g `sdl-config --cflags --libs` -lpthread -lGL -lGLU -lSDL_image -lSDL_ttf -lSDL_mixer -I ./header ./source/*.cpp -o ./debug/zorkTrek          
          finish_time=$(date +%s)
          echo "compilation took : $((finish_time - start_time)) secs."
          echo "done"
          du -sh ./debug/*
          sleep 5	
       ;;
       3) 
          start_time=$(date +%s)
          echo -e "\e[00;34mexecuting release ....\e[00m"
          ./bin/zorkTrek	
          echo "done"
          finish_time=$(date +%s)
          echo "Game was played for : $((finish_time - start_time)) secs."
          sleep 5	
       ;;
       4) 
          start_time=$(date +%s)
          echo -e "\e[00;34mexecuting debug with valgrind ....\e[00m"
          valgrind --tool=memcheck --leak-check=full --show-reachable=yes -v --track-origins=yes ./debug/zorkTrek	
          echo "done"
          finish_time=$(date +%s)
          echo "Game was played for : $((finish_time - start_time)) secs."
          sleep 5	
       ;;
       *) 
          break ;;
   esac 
done
exit 0
