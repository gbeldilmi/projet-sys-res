#! /usr/bin/env bash


#------------------------------------------------------------------------------#
# Run the game locally with a single player and bots                           #
#------------------------------------------------------------------------------#


# Build.
cd game && make re && cd ..

# Run.
./game/bin/game /tmp 1 3
