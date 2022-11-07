#! /usr/bin/env bash

# Wait for clients to connect and connect them to the correct lobby.
# Client can resquest to create a new lobby or join an existing one.

# Wait for clients to connect link them to the correct lobby (pipe).
while true; do
  # Wait for a client to connect.
  read -r client <&3

  # Read the client's request.
  read -r request <&3

  # If the client wants to create a new lobby.
  if [[ "$request" == "create" ]]; then
    # Create a new pipe.
    mkfifo "$client"

    # Connect the client to the pipe.
    ln -s "$client" "$client"

    # Connect the pipe to the client.
    ln -s "$client" "$client"

    # Send the client the name of the pipe.
    echo "$client" >&3

    # Launch the game in a new process.
    ./bin/game "$client" &

  # If the client wants to join an existing lobby.
  elif [[ "$request" == "join" ]]; then
    # Read the name of the lobby.
    read -r lobby <&3

    # Connect the client to the pipe.
    ln -s "$lobby" "$client"

    # Connect the pipe to the client.
    ln -s "$client" "$lobby"

    # Connect the client to the pipe.
    #echo "$client" >&3
    
    # Send the client the name of the pipe.
    echo "$lobby" >&3
  fi
done
