#! /usr/bin/env bash


#------------------------------------------------------------------------------#
# Run the game locally with a single player and bots                           #
#------------------------------------------------------------------------------#


# Build.
./run/build.sh

# Run.
./game/bin/game /tmp 1 3
