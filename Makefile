##########################################################################################
#											 #
#			 Makefile for makedemo						 #
#								 			 #
# 				Made by: Bárkányi Adorján				 #
##########################################################################################

####################################################################
#								   #
#				Variables			   #
#								   #
####################################################################

##########################
#  Files and directiries #
##########################
dir_list:= bin bin/Debug bin/obj

c_files:=$(wildcard src/*.c)

out_file:=bin/Debug/a.out
folder_o:= bin/obj/

o_files:=$(patsubst %.c,%.o,$(addprefix $(folder_o),$(subst src/, , $(c_files))))

##########################
#  Translator and flags  #
##########################
CC:= gcc
CFLAGS:= -Wall -g -pedantic --std=c99


##########################
#  	Test variables 	 #
##########################
test_folder:= ../bin/Debug/test
test_c_file:= ../test/main.c

##########################
#   Packing variables 	 #
##########################
per:=/
empty:=
space:=$(empty) $(empty)
p_name:= $(lastword $(subst $(per), $(space), $(shell pwd)))
p_name_t:=$(p_name).tar.gz


##########################
#    Other variables	 #
##########################
RM:=rm -rf

#Export all variables
export


####################################################################
#								   #
#				Make				   #
#			  (files and dirs)		 	   #
####################################################################

##########################
#    	Main command	 #
##########################
#This command runs at first
$(out_file): $(dir_list) $(o_files)
	$(CC) -o $(out_file) $(o_files) $(CFLAGS)
	$(out_file)


##########################
#    Create directories	 #
##########################
$(dir_list):
	mkdir $(dir_list)


##########################
#    Make object files	 #
##########################
#make object files
bin/obj/%.o: src/%.c
	$(CC) -I include -c $< -o $@ $(CFLAGS)


####################################################################
#								   #
#			 	MANAGE				   #
#								   #
####################################################################

##########################
#	   Run		 #
##########################

run:$(out_file)
	$(out_file)

Debug:$(out_file)
	$(out_file)

##########################
#	 Clean		 #
##########################
cleanall:testclean docclean clean
	$(info status: All of the function files had been deleted successfully.)

clean:
	$(RM) bin

##########################
#	 Debug		 #
##########################
debug_off:
	sed -i -e 's/#define DEBUG/#undef DEBUG/g' include/globals.h

debug_on:
	sed -i -e 's/#undef DEBUG/#define DEBUG/g' include/globals.h

##########################
#	  Doc		 #
##########################
dochtml:doc
	$(MAKE) -C doc

docclean:
	$(MAKE) -C doc clean

docopen:
	$(MAKE) -C doc docopen


##########################
#	  Test		 #
##########################
test:
	$(MAKE) -C test

testclean:
	$(MAKE) -C test clean


##########################
# Pack the whole project #
##########################

packing: $(p_name)
	cp -ar $(filter-out $(p_name),$(wildcard *)) $(p_name)
	tar -zcvf $(p_name_t) $(p_name)
	$(RM) $(p_name)

$(p_name):
	mkdir $(p_name)

##################################
# Install and Pack the Installer #
##################################

install:
	mkdir include
	mkdir src

packinginstall: idirs
	cp Makefile installpack/Makefile
	cp doc/Makefile	installpack/doc/Makefile
	cp doc/Doxyfile installpack/doc/Doxyfile
	cp test/Makefile installpack/test/Makefile
	cp .gitignore installpack/.gitignore
	tar -zcvf installpack.tar.gz installpack
	$(RM) installpack

idirs: installpack
	mkdir installpack/test
	mkdir installpack/doc
	mkdir installpack/src
	mkdir installpack/include

installpack:
	mkdir installpack


####################################################################
#								   #
#			Phony and Unset variables		   #
#								   #
####################################################################

.PHONY: run test testclean doc* clean debug* install packinginstall idirs

#Unset files and directories variables
undefine dir_list c_files out_file folder_o o_files

#Unset Translator and flags variables
undefine CC CFLAGS STD

#Unset test variables
undefine test_folder test_c_file

#Unset pack variables
undefine per empty space p_name p_name_t
