#! /usr/bin/env bash


#------------------------------------------------------------------------------#
# Welcomme the player to the lobby and let him choose an action                #
#------------------------------------------------------------------------------#


# Variables.
run_dir="/tmp"
game_dir="$run_dir/game"
program="./game/bin/game"
pio="./gio/bin/gio"

# Set everything up.
init () {
  # Check if the program exists.
  if [ ! -f "$program" ]
  then
    echo "Error: $program not found"
    exit 1
  fi
  # Prepare the directories.
  mkdir -p $run_dir $game_dir $pipe_dir
}
init

# Welcome the player.
welcome () {
  echo " "
  echo " ___       __   _______   ___       ________  ________  _____ ______  "\
      " _______      "
  echo "|\\  \\     |\\  \\|\\  ___ \\ |\\  \\     |\\   ____\\|\\   __  \\|\\"\
      "   _ \\  _   \\|\\  ___ \\     "
  echo "\\ \\  \\    \\ \\  \\ \\   __/|\\ \\  \\    \\ \\  \\___|\\ \\  \\|\\"\
      "  \\ \\  \\\\\\__\\ \\  \\ \\   __/|    "
  echo " \\ \\  \\  __\\ \\  \\ \\  \\_|/_\\ \\  \\    \\ \\  \\    \\ \\  \\"\
      "\\\\  \\ \\  \\\\|__| \\  \\ \\  \\_|/__  "
  echo "  \\ \\  \\|\\__\\_\\  \\ \\  \\_|\\ \\ \\  \\____\\ \\  \\____\\ \\  "\
      "\\\\\\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\ "
  echo "   \\ \\____________\\ \\_______\\ \\_______\\ \\_______\\ \\_______\\"\
      " \\__\\    \\ \\__\\ \\_______\\"
  echo "    \\|____________|\\|_______|\\|_______|\\|_______|\\|_______|\\|__|"\
      "     \\|__|\\|_______|"
}
welcome

# Let the player choose an action.
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

# Convert a string to an integer properly.
int () {
  printf '%d' $(expr ${1:-} : '[^0-9]*\([0-9]*\)' 2>/dev/null)||:;
}

# Create a new game.
action_create () {
  # Ask for the game name
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
  # Ask for the number of players
  while true
  do 
    echo "Enter the number of human players: "
    read num_humans
    num_humans=$(int $num_humans)
    echo "Enter the number of bot players: "
    read num_bots
    num_bots=$(int $num_bots)
    num_players=$(expr $num_humans + $num_bots)
    if [ $num_humans -lt 1 ]
    then
      echo "Number of human players must be at least 1. Please try again."
    elif [ $num_bots -lt 0 ]
    then
      echo "Number of bots must be at least 0. Please try again."
    elif [ $num_players -gt 10 ]
    then
      echo "Total number of players must be at most 10. Please try again."
    elif [ $num_players -lt 2 ]
    then
      echo "Total number of players must be at least 2. Please try again."
    else
      break
    fi
  done
  # Create the game.
  echo "Creating game $game_name..."
  mkdir "$game_dir/$game_name"
  for i in $(seq 1 $(($num_humans - 1)))
  do
    touch "$game_dir/$game_name/$i.open"
    mkfifo "$game_dir/$game_name/$i.in"
    mkfifo "$game_dir/$game_name/$i.out"
  done
  # Start the game.
  echo "Connecting to game $game_name..."
  $program $game_dir/$game_name $num_humans $num_bots
}

# Choose a game and join it.
action_join () {
  # How to read and write to a FIFO
  write_fifo () {
    in="$1"
    while true
    do
      read line
      echo "$line" >> "$in"
    done
  }
  read_fifo () {
    out="$1"
    while true
    do
      read line < "$out"
      echo $line
    done
  }
  # Ask the player to choose a game to join.
  while true
  do
    echo "Available games: "
    ls $game_dir
    
    echo "Enter the name of the game you want to join: "
    read game_name
    if [ -z "$game_name" ]
    then
      echo "Game name cannot be empty. Please try again."
    elif [ ! -e "$game_dir/$game_name" ]
    then
      echo "Game name does not exist. Please try again."
    else
      break
    fi
  done
  # Join the selected game.
  echo "Joining game $game_name..."
  for i in {1..9}
  do
    if [ -f "$game_dir/$game_name/$i.open" ]
    then
      rm "$game_dir/$game_name/$i.open"
      write_fifo "$game_dir/$game_name/$i.in" &
      read_fifo "$game_dir/$game_name/$i.out"
      return
    fi
  done
  echo "Game $game_name is full. Please try again."
}

# Main loop : select an action and execute it
main () {
  while true
  do
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
      0)
        echo "Goodbye!"
        exit 0
        ;;
    esac
  done
}
main
