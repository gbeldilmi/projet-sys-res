#! /usr/bin/env bash


program="./bin/game"
pipe_dir="io"


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
    if [[ $action == "1" ]]
    then
      return 1
    elif [[ $action == "2" ]]
    then
      return 2
    elif [[ $action == "0" ]]
    then
      return 0
    else
      echo "Invalid action"
    fi
  done
}


action_create () {
  # TODO
  echo "Create a new game"
}


action_join () {
  # TODO
  echo "Join an existing game"
}


select_action
action=$?
if [ $action -eq 1 ]
then
  action_create
elif [ $action -eq 2 ]
then
  action_join
fi

echo " "
echo "Goodbye!"
