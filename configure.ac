AC_INIT(klee-examples-config, version-0.1)

AC_PROG_CC([clang])

AC_ARG_WITH(klee,
	[AS_HELP_STRING([--with-klee],
		[KLEE installation directory (defaults to /usr/local/lib/tracerx)])],
	[],
	[with_klee=/usr/local/lib/tracerx])

AC_SUBST(KLEE, ["$with_klee"])

AC_SUBST(KLEE_REPLAY_TIMEOUT, ["60"])

AC_ARG_WITH(wllvm,
	AS_HELP_STRING([--with-wllvm], [The source directory of whole-program-llvm (defaults to /usr/local/lib/whole-program-llvm)]),
	[],
	[with_wllvm=/usr/local/lib/whole-program-llvm])

AC_SUBST(WLLVM, ["$with_wllvm"])

AC_ARG_WITH(z3,
	AS_HELP_STRING([--with-z3], [The directory of Z3 (defaults to /usr/local/lib/z3)]),
	[],
	[with_z3=/usr/local/lib/z3])

if test "$with_z3" != no
then
	a=0
	AC_CHECK_HEADERS(["$with_z3/include/z3.h"], [], [a=1])
	if test "$a" == "0"
	then
		if test x == x$extra_ld_path
		then
			extra_ld_path="$with_z3/lib"
		else
			extra_ld_path="$with_z3/lib:$extra_ld_path"
		fi
	fi
fi

AC_ARG_WITH(stp,
	AS_HELP_STRING([--with-stp], [The directory of STP (defaults to /usr/local)]),
	[],
	[with_stp=/usr/local])

if test "$with_stp" != no
then
	a=0
	AC_CHECK_HEADERS(["$with_stp/include/stp/c_interface.h"], [], [a=1])
	if test "$a" == "0"
	then
		if test x == x$extra_ld_path
		then
			extra_ld_path=$with_stp/lib
		else
			extra_ld_path="$with_stp/lib:$extra_ld_path"
		fi
	fi
fi

AC_ARG_WITH(clpr,
	AS_HELP_STRING([--with-clpr], [The directory of CLPR (defaults to /usr/local)]),
	[],
	[with_clpr=/usr/local])

if test "$with_stp" != no
then
	a=0
	AC_CHECK_HEADERS(["$with_clpr/include/clpr_api.h"], [], [a=1])
	if test "$a" == "0"
	then
		if test x == x$extra_ld_path
		then
			extra_ld_path="$with_clpr/lib"
		else
			extra_ld_path="$with_clpr/lib:$extra_ld_path"
		fi
	fi
fi

AC_SUBST(EXTRA_LD_LIBRARY_PATH, ["$extra_ld_path"])

AC_ARG_WITH(texinfo,
	[AS_HELP_STRING([--with-texinfo],
		[GNU texinfo 4.13 installation directory, i.e., the info utility should be under the bin subdirectory of the specified directory. Coreutils 6.10 requires GNU texinfo no later than 4.13.])])

if test "$with_texinfo" != no
then
	AC_MSG_CHECKING([whether texinfo exists])
	if test -x $with_texinfo/bin/info
	then
		AC_MSG_RESULT([yes])
		if test x == x$extra_path
		then
			extra_path="$with_texinfo/bin"
		else
			extra_path="$with_texinfo/bin:$extra_path"
		fi
	else
		AC_MSG_RESULT([no])
	fi
else
	AC_MSG_NOTICE([To look for texinfo in PATH])
fi


AC_ARG_WITH(llbmc,
	[AS_HELP_STRING([--with-llbmc],
		[LLBMC installation directory, i.e., the llbmc executable should be under the bin subdirectory of the specified directory (defaults to /usr/local).])],
		   [],
		   [with_llbmc=/usr/local])

if test "$with_llbmc" != no
then
	AC_MSG_CHECKING([whether LLBMC exists])
	if test -x $with_llbmc/bin/llbmc
	then
		AC_MSG_RESULT([yes])
		if test x == x$extra_path
		then
			extra_path="$with_llbmc/bin"
		else
			extra_path="$with_llbmc/bin:$extra_path"
		fi
	else
		AC_MSG_RESULT([no])
	fi
else
	AC_MSG_NOTICE([To look for llbmc in PATH])
fi

AC_SUBST(EXTRA_PATH, ["$extra_path"])

AC_OUTPUT(Makefile.common)
AC_OUTPUT(environ.sh)
