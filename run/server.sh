#! /usr/bin/env bash


program="./run/lobby.sh"
start_port=8777
number_port=20

running=true


close () { # Choose your way to die
  # running=false
  killall bash
}
trap close SIGINT


run () {
  while $running
  do
    echo "Opening connection @$1"
    netcat -l -p $1 -c -e $program
    echo "Connection closed @$1"
  done
}


for p in $(seq $start_port 1 $(($start_port + $number_port)))
do
  run $p &
done


while true
do
  sleep 1
done