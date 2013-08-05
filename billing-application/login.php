<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/user-management-lib.inc';
require_once 'includes/form.inc';

if (is_logged_in() == FALSE) {
  $form_id = 'login_form';
  $login = new Savant3();
  $login->title = 'Login';
  $login->inputs = render_form($form_id); 
  $login->display('templates/content.tpl.php');
}
else {
  redirect ("access-denied.php");
}
include 'footer.php';

