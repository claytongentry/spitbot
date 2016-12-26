CC := g++

SRCDIR 	 := src
BUILDDIR := build
TARGET 	 := bin/jeezy

SRCEXT 	:= cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS	:= -g -Wall -std=c++11 -O3
LIB     := -L lib
INC     := -I include

TEST_TARGET 	:= bin/testx
TEST_SRCDIR 	:= test
TEST_INC 	:= -I include -I src

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

test: $(TEST_SRCDIR)/*.$(SRCEXT)
	@echo "Building Tests..."
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_INC) $^

clean:
	@echo "Cleaning..."
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
