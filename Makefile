########################################################################
####################### Makefile Template ##############################
########################################################################

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = 

# Makefile settings - Can be customized.
TESTAPP1 = TestArrays
TESTAPP2 = TestObjects
TESTAPP3 = TestNestedRegion
TESTAPP5 = TestMultipleArrays
TESTAPP4 = TestMultipleObjects
EXT = .cpp
SRCDIR = src
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
# DEP = $(OBJ:$(OBJDIR)/%.o=%.d)

# UNIX-based OS variables & settings
RM = rm
DELOBJ = $(OBJ)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: $(TESTAPP1) $(TESTAPP2) $(TESTAPP3) $(TESTAPP4) $(TESTAPP5)

# Builds the apps
$(TESTAPP1): obj/RMM.o obj/TestArrays.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TESTAPP2): obj/RMM.o obj/TestObjects.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TESTAPP3): obj/RMM.o obj/TestNestedRegions.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TESTAPP4): obj/RMM.o obj/TestMultipleObjects.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TESTAPP5): obj/RMM.o obj/TestMultipleArrays.o
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Creates the dependecy rules
# %.d: $(SRCDIR)/%$(EXT)
#	@$(CPP) $(CFLAGS) $< -MM -MT $(@:%.d=$(OBJDIR)/%.o) >$@

# Includes all .h files
# -include $(DEP)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CC) $(CXXFLAGS) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project
.PHONY: clean
clean:
	$(RM) $(DELOBJ) $(APPNAME)
#	$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
# .PHONY: cleandep
# cleandep:
# 	$(RM) $(DEP)

# Cleans only all files with the extension .d
# .PHONY: cleandepw
# cleandepw:
#	$(DEL) $(DEP)
