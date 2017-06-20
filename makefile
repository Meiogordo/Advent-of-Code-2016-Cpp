CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-g -std=c++11 -I.
LDFLAGS=-g
LDLIBS=

#Depend file stuff
DEPFILE=.depend
DEPTEXT='\#MAKE .DEPEND FILE'

# DAY is the day to compile, passed in with "make DAY=Day1" for example

ifndef DAY
DAY=Day1
endif

#Defining sources and objects
SRCS=$(DAY)/$(DAY).cpp Utils/Utilities.cpp
OBJS=$(subst .cpp,.o,$(SRCS))


## Tests in attempting to get all .o files to be inside the build directory - unsuccessful, obviously
#RAWSRCS=$(DAY).cpp Utilities.cpp
#RAWOBJS=$(subst .cpp,.o,$(RAWSRCS))
#dir=build
#OBJS_O=$(foreach robj, $(RAWOBJS), $(dir)/$(RAWOBJS))


all: $(DAY)

$(DAY): $(OBJS)
	$(CXX) $(LDFLAGS) -o bin/$(DAY) $(OBJS) $(LDLIBS)

depend: $(DEPFILE)

$(DEPFILE): $(SRCS)
	$(RM) $(DEPFILE)
	echo $(DEPTEXT) > $(DEPFILE)
	$(CXX) $(CPPFLAGS) -MM $^>>$(DEPFILE);

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ $(DEPFILE)

include $(DEPFILE)
