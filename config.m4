dnl $Id$
dnl config.m4 for extension segmentation

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(segmentation, for segmentation support,
Make sure that the comment is aligned:
[  --with-segmentation             Include segmentation support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(segmentation, whether to enable segmentation support,
dnl Make sure that the comment is aligned:
dnl [  --enable-segmentation           Enable segmentation support])

if test "$PHP_SEGMENTATION" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-segmentation -> check with-path
   SEARCH_PATH="/usr/local /usr"     # you might want to change this
   SEARCH_FOR="include/segmentation/seg.h"  # you most likely want to change this
   if test -r $PHP_SEGMENTATION/$SEARCH_FOR; then # path given as parameter
     SEGMENTATION_DIR=$PHP_SEGMENTATION
   else # search default path list
     AC_MSG_CHECKING([for segmentation files in default path])
     for i in $SEARCH_PATH ; do
       if test -r $i/$SEARCH_FOR; then
         SEGMENTATION_DIR=$i
         AC_MSG_RESULT(found in $i)
       fi
     done
   fi
  
   if test -z "$SEGMENTATION_DIR"; then
     AC_MSG_RESULT([not found])
     AC_MSG_ERROR([Please reinstall the segmentation distribution])
   fi

  dnl # --with-segmentation -> add include path
   PHP_ADD_INCLUDE($SEGMENTATION_DIR/include/segmentation)

  dnl # --with-segmentation -> check for lib and symbol presence
   LIBNAME=segmentation # you may want to change this
   LIBSYMBOL=segmentation # you most likely want to change this 
   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, /usr/local/lib, SEGMENTATION_SHARED_LIBADD)

  PHP_SUBST(SEGMENTATION_SHARED_LIBADD)

  PHP_NEW_EXTENSION(segmentation, segmentation.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
