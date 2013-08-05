<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/user-management-lib.inc';
$previous = curPageName();
if (authorize('change_password')) {
  $change_password = new Savant3();
  $change_password->title = 'change password';
  $change_password->main_links = get_menu('main_menu');
  $change_password->links = get_menu('main_menu'); 
  $change_password->inputs = change_password_form();  
  $change_password->display('templates/content.tpl.php');
  if (change_password_submit() == 'change-password') {
    $result = change_password($_POST['password']);
    if ($result == true) {
      redirect('index.php');
    }
  }
  elseif (change_password_submit() == 'error') {
    echo "your password mismatches";
  }
}
else {
  redirect ("login.php?destination=$previous");
}

