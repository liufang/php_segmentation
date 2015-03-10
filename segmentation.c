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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_segmentation.h"

/* If you declare any globals in php_segmentation.h uncomment this:*/
ZEND_DECLARE_MODULE_GLOBALS(segmentation)


/* True global resources - no need for thread safety here */
static int le_segmentation;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini */
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("segmentation.word_file", "/tmp/seg.txt", PHP_INI_ALL, OnUpdateString, word_file, zend_segmentation_globals, segmentation_globals)
PHP_INI_END()

/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_segmentation_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_segmentation_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "segmentation", arg);

	RETVAL_STRINGL(strg, len);
	efree(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

//进行文本分词
PHP_FUNCTION(segmentation)
{
	char *arg = NULL;
	size_t arg_len, len;
	char *strg;
	result* r;
	result_node* node;

	if(zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		php_error_docref(NULL, E_WARNING, "请传递需要分词的字符串");
	}

	//分词库调用
	r = seg(arg);
	array_init(return_value);
	if(r->count > 0) {
		node = r->node;
		do{
			add_next_index_string(return_value, node->word->str->str);
			//php_printf("%s ", node->word->str->str);
		} while((node = node->next) != NULL);
	}
}

/* {{{ php_segmentation_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_segmentation_init_globals(zend_segmentation_globals *segmentation_globals)
{
	segmentation_globals->global_value = 0;
	segmentation_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(segmentation)
{
	//初始化模块配置信息
	REGISTER_INI_ENTRIES();
	//模块启动的时候进行字典初始化
	init_index(INI_STR("segmentation.word_file"));
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(segmentation)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(segmentation)
{
#if defined(COMPILE_DL_SEGMENTATION) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(segmentation)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(segmentation)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "segmentation support", "enabled");
	php_info_print_table_header(2, "author", "fang.liu");
	php_info_print_table_header(2, "Extension Version", "1.0");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ segmentation_functions[]
 *
 * Every user visible function must have an entry in segmentation_functions[].
 */
const zend_function_entry segmentation_functions[] = {
	PHP_FE(confirm_segmentation_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(segmentation, NULL)
	PHP_FE_END	/* Must be the last line in segmentation_functions[] */
};
/* }}} */

/* {{{ segmentation_module_entry
 */
zend_module_entry segmentation_module_entry = {
	STANDARD_MODULE_HEADER,
	"segmentation",
	segmentation_functions,
	PHP_MINIT(segmentation),
	PHP_MSHUTDOWN(segmentation),
	PHP_RINIT(segmentation),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(segmentation),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(segmentation),
	PHP_SEGMENTATION_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_SEGMENTATION
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(segmentation)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
