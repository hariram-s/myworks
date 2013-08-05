<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/user-management-lib.inc';
require_once 'includes/form.inc';

$previous = curPageName();
if (authorize('add_user')) {
  $form_id = 'add_user_form';
  $add_user = new Savant3();
  $add_user->title = 'Add user';
  $add_user->main_links = get_menu('main_menu');
  $add_user->links = get_menu('users');
  $add_user->inputs = render_form($form_id); 
  $add_user->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}

