MAKE = gmake
CC = clang++-devel

INCDIR =
LIBDIR =
BINDIR = ..
OBJDIR = .obj
DBDIR = /usr/metin2/server/share/bin

GCC_VERSION = $(shell $(CC) --version 2>&1 | grep "(GCC)" | cut -d' ' -f3  | cut -d'.' -f1)
BSD_VERSION = $(shell uname -v 2>&1 | cut -d' ' -f2 | cut -d'.' -f1)
SVN_VERSION = 40142
$(shell if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi)

# TARGET = $(BINDIR)/db_r$(SVN_VERSION)
TARGET = $(BINDIR)/db

CFLAGS = -g -Wall -w -O2 -pipe -fno-rtti -std=c++2b -fno-exceptions -pthread -D_THREAD_SAFE
CFLAGS += -mtune=i686

# MySQL
LIBS += /usr/local/lib/mysql/libmysqlclient.a /usr/lib/libz.a

# OpenSSL
LIBS += /usr/lib/libssl.a /usr/lib/libcrypto.a

# Miscellaneous external libraries
INCDIR += -I../../../extern/include
LIBDIR += -L../../../extern/lib

INCDIR += -I/usr/local/include
INCDIR += -I/usr/include

LIBDIR += -L../../libthecore/lib -L../../libsql -L../../libpoly -L../../libgame/lib
LIBS += -lthecore -lsql -lpoly -lgame -lm

SRCS =	Config.cpp NetBase.cpp Peer.cpp PeerBase.cpp Main.cpp Lock.cpp DBManager.cpp \
		Cache.cpp LoginData.cpp ClientManager.cpp ClientManagerPlayer.cpp ClientManagerLogin.cpp \
		ClientManagerBoot.cpp ClientManagerParty.cpp ClientManagerGuild.cpp GuildManager.cpp HB.cpp \
		PrivManager.cpp MoneyLog.cpp ItemAwardManager.cpp ClientManagerEventFlag.cpp Marriage.cpp \
		Monarch.cpp BlockCountry.cpp ItemIDRangeManager.cpp ClientManagerHorseName.cpp version.cpp \
		AuctionManager.cpp ProtoReader.cpp CsvReader.cpp 

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

default: $(TARGET)

$(TARGET): $(OBJS)
	@echo linking $(TARGET)....
	@$(CC) $(CFLAGS) $(LIBDIR) $(OBJS) $(LIBS) -o $(TARGET)
	@touch version.cpp
	@echo "Moving $(TARGET) to $(DBDIR)"
	@mv $(TARGET) $(DBDIR)
	@echo "All done! Your db file moved to your server directory."

$(OBJDIR)/%.o: %.cpp
	@echo compile $<
	@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(OBJDIR)/version.o: version.cpp
	@$(CC) $(CFLAGS) -D__P4_VERSION__=\"$(SVN_VERSION)\" -c $< -o $@
	@echo compile $<

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@rm -f $(OBJS) $(BINDIR)/db_r*

dep:
	@touch Depend
	makedepend -fDepend $(INCDIR) -I/usr/include/c++/3.3 -I/usr/include/c++/4.2 -p$(OBJDIR)/ $(SRCS) 2> /dev/null

sinclude Depend
