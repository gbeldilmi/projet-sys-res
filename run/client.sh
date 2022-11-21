#! /usr/bin/env bash


if [[ $# -lt 1 ]]; then
  echo "Usage: $0 <server>"
  exit 1
fi


server="$1"
begin_port=8777
number_port=20

running=true


p=$begin_port
while $running
do
  echo "Connecting to $server @$p"
  netcat -c $server $p
  if [[ $? -eq 0 ]]
  then
    echo "Connection closed @$p"
    running=false
  else
    echo "Last status returned : $?"
    p=$(($p + 1))
    if [[ $p -gt $(($begin_port + $number_port)) ]]
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
