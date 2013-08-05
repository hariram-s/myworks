<?php 
/** 
 * Common things used in all appliction are included in bootstrap file.
 */
 
session_start();
define('LIB_DIR', getcwd() . '/lib');
set_include_path(get_include_path(). PATH_SEPARATOR . LIB_DIR);

