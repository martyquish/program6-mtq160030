# Author: Martin Quish
# Email: mtq160030@utdallas.edu
# Class: 3377.502


# --- Configure project settings ---

# Mainly used when exporting/backing up
PROJNAME = program6

# Name of executable for 'make all' to build
EXEC = prog6

# All object files necessary to build the above executable
OBJS = driver.o

# Specify any intermediary files which should not be automatically cleaned during implicit chaining.
.PRECIOUS =

# Specify any files which 'make clean' should remove. Object files are removed implicitly with clean
JUNK = *~ *.tab.* scan.c parse.c a.out

# Specify a location for 'make backup' to backup your files.	
BACKUPPATH = ~/backups

# Specify a log file to store any automatically suppressed errors (i.e. rm not finding a certain junk file)
LOG = make.log


# --- Configure C/C++ ---

#C++ compiler usedsettings:
CXX = g++

#C compiler used
CC = gcc

#C compiler flags
CCFLAGS = 	 

#C++ compiler flags
CXXFLAGS =

#C preprocessor flags
CPPFLAGS = -Wall

#C/C++ Linker Flags
LDFLAGS =

#C/C++ External Library Paths
LDLIBS =

# --- Configure Lex/Flex ---

# Program to interpret .l and .lex files:
LEX = /bin/flex

# Lex flags
LFLAGS =


# --- Configure YACC/Bison  ---

# Program to interpret .y filesttings:
YACC = /bin/bison

# Yacc flags
YFLAGS = -dy

all: $(EXEC)

clean:
	rm $(JUNK) $(OBJS) 2> $(LOG) || true

backup:
	@echo "Cleaning Project..."
# Clean unnecessary files from project
	@make clean
	@echo "Generating Timestamp..."
 # Create a date/time-stamped backup name
	@$(eval BACKUPNAME := $(PROJNAME)$(shell date +'-%b-%d-%Y-%H.%M.%S.tar.gz'))
	@echo "Tarring Project..."
# Generate tarball with all remaining project files.
	@tar -cvzf $(BACKUPNAME) *
# Move the tarball to the given backup path
	@mv $(BACKUPNAME) $(BACKUPPATH)
	@echo "Done!"
$(EXEC):$(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) $(OBJS)

