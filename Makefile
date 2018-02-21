.POSIX:

OUTS=mastermind-make mastermind-break
all: $(OUTS)
clean:
	rm -f $(OUTS) $(OBJS) $(MAKE_OBJS) $(BREAK_OBJS)

OBJS=mastermind.o
mastermind.o: mastermind.h

MAKE_OBJS=$(OBJS) make.o
make.o: mastermind.h io.h
mastermind-make: $(MAKE_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(MAKE_OBJS)

BREAK_VALUE=min
BREAK_OBJS=$(OBJS) break.o break-$(BREAK_VALUE).o
break.o: mastermind.h io.h break.h
break-min.o: mastermind.h break.h
break-avg.o: mastermind.h break.h
mastermind-break: $(BREAK_OBJS)
	$(CC) $(LDFLAGS) -o $@ $(BREAK_OBJS)
