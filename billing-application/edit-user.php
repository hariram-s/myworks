<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/user-management-lib.inc';
$previous = curPageName();
if (authorize('edit_user')) {
  $name = $_GET['q'];
  $role= get_role($name);
  $edit_user = new Savant3();
  $edit_user->title = 'Edit user';
  $edit_user->main_links = get_menu('main_menu');
  $edit_user->links = get_menu('users');
  $edit_user->inputs = edit_user_form($name,$role);  
  $edit_user->display('templates/content.tpl.php');
  if(isset($_POST['edituser'])) {
    if (!empty($_POST['role'])) {
      echo edit_user_submit($_POST['role'],$name); 
    }
    else {
      echo "Please specify any one role to the user";
    }       
  }
}
else {
  redirect ("login.php?destination=$previous");
}
?>

