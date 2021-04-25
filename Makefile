##################################
#Makefile
#Charles Myers
#COSC 3750 Spring 2021
#Homework 9
#April 6, 2021
#
#This file will compile the  files for HW8
##################################
CC=gcc
CFLAGS=-ggdb -Wall
RM=/bin/rm -f
#tidy and clean are not files
.PHONY : tidy clean 
#wyshell will use the wyshell files and create an executable called wyshell
wyshell : wyshell.c 
	$(CC) $(CFLAGS) -o wyshell wyscanner.c wyshellfunctions.c wyshell.c
#tidy will remove any object files in the directory
tidy :
	$(RM) *.o
#clean will run tidy and remove the executable approxe
clean : tidy
	$(RM) wyshell
