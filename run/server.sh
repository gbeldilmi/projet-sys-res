#! /usr/bin/env bash


#------------------------------------------------------------------------------#
# Run a server to play the game with multiple clients                          #
#------------------------------------------------------------------------------#


# Variables.
program="./run/lobby.sh"
start_port=7767
number_port=10

# Build.
./run/build.sh

# The red button.
close () {
  killall bash
  killall game
}
trap close SIGINT

# The run loop.
run () {
  while true
  do
    echo "Opening connection @$1"
    netcat -l -p $1 -e $program
    echo "Connection closed @$1"
  done
}

# Run the server on each port.
for p in $(seq $start_port 1 $(($start_port + $number_port - 1)))
do
  run $p &
done

# Wait for the end of the world.
while true
do
  sleep 1
done
