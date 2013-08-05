<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
$previous = curPageName();
if (authorize('list_customer')) {
  $header = array ('Mark','Card number','Name' , 'Date');
  $list = list_customers();
  $list_customers = new Savant3();
  $list_customers->title = 'List customer';
  $list_customers->main_links = get_menu('main_menu');
  $list_customers->links = get_menu('billing');
  $list_customers->header = $header; 
    foreach ($list as $index => $entry)  {
      $check_box = "<input name=\"ids[{$entry['id']}]\" type='checkbox' value='1'/>";
      array_unshift($list[$index],$check_box);
    }
  $rows = $list;
  $list_customers->inputs = list_customer_form($header,$rows);
  $list_customers->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}
?>

