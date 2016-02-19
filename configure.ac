
AC_INIT(libdxf, 0.0.1)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(libdxf.h)
AM_MAINTAINER_MODE

AC_CONFIG_MACRO_DIR([m4])
AC_ISC_POSIX
AC_PROG_CC
AM_PROG_CC_STDC
AM_PROG_CC_C_O
AC_HEADER_STDC

# See if we are supposed to build the Doxygen docs.

docs_yesno=yes
AC_MSG_CHECKING([if the Doxygen developer documentation should be built])
AC_ARG_ENABLE([doc],
[  --enable-doc            Build and install the Doxygen developer documentation [[default=yes]]],
[
if test "X$enable_doc" = "Xno" ; then
        DOC=""
        AC_MSG_RESULT([no])
        docs_yesno=no
else
        DOC=doc
        AC_MSG_RESULT([yes])
        docs_yesno=yes
fi
],
[
DOC=doc
AC_MSG_RESULT([yes])
docs_yesno=yes
])
AC_SUBST(DOC)
AM_CONDITIONAL(DOXYGEN, test x$docs_yesno = xyes)


AM_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB(m, atan2)

# i18n
GETTEXT_PACKAGE=$PACKAGE
AH_TEMPLATE([GETTEXT_PACKAGE], [Name of this program's gettext domain])
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [Gettext package.])
AC_SUBST(GETTEXT_PACKAGE)
# Add the languages which your application supports.
ALL_LINGUAS=""
AM_GLIB_GNU_GETTEXT

AC_OUTPUT([
Makefile
doc/Makefile
doc/doxygen/Makefile
doc/refguides/Makefile
doc/refguides/R10/Makefile
doc/refguides/R12/Makefile
doc/refguides/R13/Makefile
doc/refguides/R14/Makefile
doc/refguides/R2014/Makefile
po/Makefile.in
src/Makefile
tests/Makefile
])
