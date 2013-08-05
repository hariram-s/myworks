<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/user-management-lib.inc';
$previous = curPageName();
if (authorize('disabled_users')) {
  $header = array ('Mark', 'Username' , 'Role of the user'); 
  $list = disabled_users_list();
  $list_user = new Savant3();
  $list_user->title = 'Disabled users list';
  $list_user->main_links = get_menu('main_menu');
  $list_user->links = get_menu('users');
  foreach ($list as $index => $entry)  {
    $check_box = "<input name=\"names[{$entry['name']}]\" type='checkbox' value='1'/>";
    array_unshift($list[$index],$check_box);
  } 
  $rows = $list;
  $list_user->inputs = disabled_users_form($header,$rows); 
  $list_user->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}
?>

