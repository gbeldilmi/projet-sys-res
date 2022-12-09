#! /usr/bin/env bash

#------------------------------------------------------------------------------#
# Connect to a server to play the game                                         #
#------------------------------------------------------------------------------#


# How to use this script.
if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <server>"
  exit 1
fi

# Variables.
server="$1"
begin_port=7767
number_port=10
running=true

# Try to connect to the server, if it fails, ask to try the next port.
p=$begin_port
while $running
do
  echo "Connecting to $server @$p"
  netcat $server $p
  if [[ $? -eq 0 ]]
  then
    echo "Connection closed @$p"
    running=false
  else
    echo "Last status returned : $?"
    p=$(($p + 1))
    if [[ $p -gt $(($begin_port + $number_port - 1)) ]]
    then
      running=false
    else
      read -p "Test on next port ? [Y/n] " answer
      if [[ "$answer" == "n" ]]
      then
        running=false
      fi
    fi
  fi
done
