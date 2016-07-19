AC_INIT(klee-examples-config, version-0.1)

AC_PROG_CC([clang])

AC_ARG_WITH([klee],
	[AS_HELP_STRING([--with-klee],
		[KLEE installation directory])],
	[],
	[with_klee=/usr/local/lib/tracerx])

AC_ARG_WITH([whole-program-llvm],
	AS_HELP_STRING([--with-whole-program-llvm], [The source directory of whole-program-llvm]))

echo $with_whole-program-llvm
if test x == x$with_whole-program-llvm
then
	with_whole-program-llvm=/usr/local/lib/whole-program-llvm
fi

AC_OUTPUT(Makefile.common)
