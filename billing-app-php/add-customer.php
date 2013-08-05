<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
require_once 'Savant3.php';
require_once 'includes/form.inc';

$previous = curPageName(); 
if (authorize('add_customer')) {
  $form_id = 'add_customer_form';
  $add_customer = new Savant3();
  $add_customer->title = 'Add customer';
  $add_customer->main_links = get_menu('main_menu');
  $add_customer->links = get_menu('billing');
  $add_customer->inputs = render_form($form_id);  
  $add_customer->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}
?>

