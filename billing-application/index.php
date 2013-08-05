<?php 
require_once 'bootstrap.php';
require_once 'includes/user-management-lib.inc';
require_once 'includes/common.inc';
authorize('index');
$register = new Savant3();
$register->title = 'Home'; 
$register->main_links = get_menu('main_menu');
$register->display('templates/content.tpl.php');

