AM_CFLAGS = $(MORE_CFLAGS)
AM_CPPFLAGS = $(MORE_CPPFLAGS)
AM_LDFLAGS = $(MORE_LDFLAGS)

bin_PROGRAMS = tp_algo
dist_man_MANS = tp_algo.8

# tp_algo_dir   = ../data
# tp_algo__DATA = test_data.txt
tp_algo_SOURCES  = log.c log.h main.h main.c \
                   stack.h stack.c \
                   sequence.h sequence.c
tp_algo_CFLAGS   = $(AM_CFLAGS) @JANSSON_CFLAGS@
tp_algo_LDFLAGS  = $(AM_LDFLAGS) @JANSSON_LIBS@
