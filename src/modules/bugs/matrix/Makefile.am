noinst_LTLIBRARIES = libbugsmatrix.la

libbugsmatrix_la_CPPFLAGS = -I$(top_srcdir)/src/include

libbugsmatrix_la_SOURCES = matrix.cc blas.f90 lapack.f90

noinst_HEADERS = blas.h lapack.h matrix.h

MOSTLYCLEANFILES = jags_lapack.mod jags_blas.mod
