/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_SEGMENTATION_H
#define PHP_SEGMENTATION_H

#include "segmentation/seg.h"

extern zend_module_entry segmentation_module_entry;
#define phpext_segmentation_ptr &segmentation_module_entry

#define PHP_SEGMENTATION_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_SEGMENTATION_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_SEGMENTATION_API __attribute__ ((visibility("default")))
#else
#	define PHP_SEGMENTATION_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/*
  	Declare any global variables you may need between the BEGIN
	and END macros here:
*/
ZEND_BEGIN_MODULE_GLOBALS(segmentation)
	char *word_file;
ZEND_END_MODULE_GLOBALS(segmentation)


/* Always refer to the globals in your function as SEGMENTATION_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define SEGMENTATION_G(v) ZEND_TSRMG(segmentation_globals_id, zend_segmentation_globals *, v)
#ifdef COMPILE_DL_SEGMENTATION
ZEND_TSRMLS_CACHE_EXTERN();
#endif
#else
#define SEGMENTATION_G(v) (segmentation_globals.v)
#endif

#endif	/* PHP_SEGMENTATION_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
