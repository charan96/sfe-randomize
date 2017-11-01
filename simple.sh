#!/bin/csh

# use current working directory for input and output
# default is to use the users home directory
#$ -cwd

# name this job
#$ -N sequential-method

# send stdout and stderror to this file
#$ -o submit-output.out
#$ -j y

# select queue - if needed 
#$ -q eecs,eecs2,share,share2,share3,share4

# see where the job is being run
hostname

# print date and time
date

# Sleep for 10 seconds
make all

# print date and time again
date
