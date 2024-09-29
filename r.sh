#/bin/bash

# Collatz Conjecture: A program which calculates the 
#                     collatz conjecture for a given number
# Copyright (C) <2024>  <Kshitij Pingle>

# This file is part of the software program "Collatz Conjecture".

# "Collatz Conjecture" is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# "Collatz Conjecture" is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>. 

# Author information
#   Author name : Kshitij Pingle
#   Author email: kpingle@csu.fullerton.edu
#   Author section: 351-13
#   Author CWID : 885626978 

#Delete some un-needed files
rm *.o
rm *.out

#Compile output_array.c
gcc -o collatz collatz.c
