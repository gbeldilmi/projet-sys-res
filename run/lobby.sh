#! /usr/bin/env bash


run_dir="/tmp/lobby"
game_dir="$run_dir/games"
pipe_dir="$run_dir/pipes"


program="./bin/game"
if [ ! -f "$program" ]; then
    echo "Error: $program not found"
    exit 1
fi
mkdir -p $run_dir $game_dir $pipe_dir


title () {
  echo " "
  echo " ___       __   _______   ___       ________  ________  _____ ______   _______      "
  echo "|\\  \\     |\\  \\|\\  ___ \\ |\\  \\     |\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\     "
  echo "\\ \\  \\    \\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    "
  echo " \\ \\  \\  __\\ \\  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\    \\ \\  \\\\\\  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  "
  echo "  \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\____\\ \\  \\\\\\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ "
  echo "   \\ \\____________\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\ \\__\\    \\ \\__\\ \\_______\\"
  echo "    \\|____________|\\|_______|\\|_______|\\|_______|\\|_______|\\|__|     \\|__|\\|_______|"
}
title


select_action () {
  echo " "
  echo "1. Create a new game"
  echo "2. Join an existing game"
  echo "0. Quit"
  while true
  do
    read -p "Choose an action: " action
    case $action in
      1|2|0)
        return $action
        ;;
      *)
        echo "Invalid action. Please try again."
        ;;
    esac
  done
}


action_create () {
  read -p "Enter a name for your game: " game_name
  
}


action_join () {
  # TODO
  echo "Join an existing game"
}


select_action
action=$?
echo " "
case $action in
  1)
    action_create
    ;;
  2)
    action_join
    ;;
esac


echo " "
echo "Goodbye!"
