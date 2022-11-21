#! /usr/bin/env bash


run_dir="/tmp/lobby"
game_dir="$run_dir/games"
pipe_dir="$run_dir/pipes"


init () {
  program="./game/bin/game"
  if [ ! -f "$program" ]; then
    echo "Error: $program not found"
    exit 1
  fi
  mkdir -p $run_dir $game_dir $pipe_dir
}
init


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
    echo "Choose an action: "
    read action
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
  while true
  do
    echo "Enter a name for your game: "
    read game_name
    if [ -z "$game_name" ]
    then
      echo "Game name cannot be empty. Please try again."
    elif [ -e "$game_dir/$game_name" ]
    then
      echo "Game name already exists. Please try again."
    else
      break
    fi
  done

  while true
  do 
    echo "Enter the number of players: "
    read num_players
    if [ $num_players -lt 2 ]
    then
      echo "Number of players must be at least 2. Please try again."
    else
      break
    fi
  done

  while true
  do
    echo "Enter the number of bots: "
    read num_bots
    if [ $num_bots -lt 0 ]
    then
      echo "Number of bots must be at least 0. Please try again."
    elif [ $num_bots -eq $num_players ]
    then
      echo "It must be at least one human player. Please try again."
    elif [ $num_bots -gt $num_players ]
    then
      echo "Number of bots cannot be greater than number of players. Please try again."
    else
      break
    fi
  done


  echo "Creating game $game_name with $($num_players - $num_bots) human players and $num_bots bots..."
}


action_join () {
  # TODO
  echo "Join an existing game"
}


main () {
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
}
main
