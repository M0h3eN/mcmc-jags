ACLOCAL_AMFLAGS = -I m4
SUBDIRS = m4 libltdl src etc win doc test
EXTRA_DIST = Doxyfile

.PHONY: win32-install win64-install installer docs

win32-install:
	make prefix=`pwd`/win/inst32
	make install prefix=`pwd`/win/inst32

win64-install:
	make prefix=`pwd`/win/inst64 
	make install prefix=`pwd`/win/inst64

installer:
	(for f in `find win/runtime32 -name '*.dll' -print`; do \
	   ${INSTALL} $$f win/inst32/bin/; done;)
	(for f in `find win/runtime32 -name '*.dll.a' -print`; do \
	   ${INSTALL} $$f win/inst32/lib/; done;)
	(for f in `find win/runtime64 -name '*.dll' -print`; do \
	   ${INSTALL} $$f win/inst64/bin/; done;)
	(for f in `find win/runtime64 -name '*.dll.a' -print`; do \
	   ${INSTALL} $$f win/inst64/lib/; done;)
	(cd win && $(MAKE) $@)

docs: FORCE
	-@(cd doc && $(MAKE) $@)

FORCE:

# Work around libltdl bug: make distclean leaves behind .deps/lt__strl.Plo
# causing make distcheck to fail.
distclean-local:
	rm -f libltdl/$(DEPDIR)/lt__strl.*
	rm -f libltdl/$(DEPDIR)/lt__dirent.*
