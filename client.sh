#! /usr/bin/env bash

# Get all parameters.
while [[ $# -gt 0 ]]; do
  case "$1" in
    --server)
      server="$2"
      shift
      shift
      ;;
    --create)
      create=true
      shift
      ;;
    --join)
      join="$2"
      shift
      shift
      ;;
    *)
      echo "Unknown parameter: $1"
      exit 1
      ;;
  esac
done

# Tell how to use this script.
if [[ -z "$server" ]]; then
  echo "Usage: $0 --server <server> [--create | --join <lobby>]"
  exit 1
fi

# Print parameters.
echo "Server: $server"
echo "Create: $create"
echo "Join: $join"

# Connect to the server.
exec 3<>"$server"

# If the client wants to create a new lobby.
if [[ "$create" == true ]]; then
  # Send the request to the server.
  echo "create" >&3

  # Read the name of the lobby.
  read -r lobby <&3

  # Connect to the lobby.
  exec 4<>"$lobby"

  # Send the name of the client.
  echo "$name" >&4

  # Read the name of the other client.
  read -r other <&4

  # Print the name of the other client.
  echo "Other: $other"
fi

# If the client wants to join an existing lobby.
if [[ -n "$join" ]]; then
  # Send the request to the server.
  echo "join" >&3

  # Send the name of the lobby.
  echo "$join" >&3

  # Read the name of the lobby.
  read -r lobby <&3

  # Connect to the lobby.
  exec 4<>"$lobby"

  # Send the name of the client.
  echo "$name" >&4

  # Read the name of the other client.
  read -r other <&4

  # Print the name of the other client.
  echo "Other: $other"
fi

