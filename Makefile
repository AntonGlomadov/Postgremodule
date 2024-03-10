# contrib/superextension/Makefile

MODULE_big = superextension
OBJS = superextension.o

EXTENSION = superextension
DATA = superextension--1.0.sql

PG_CONFIG = /usr/local/pgsql/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

