<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
require_once 'includes/stock-management-lib.inc';
require_once 'Savant3.php';
require_once 'includes/form.inc';

$previous = curPageName(); 
if (authorize('add_bill')) {
  $bill = new Savant3();
  $bill->title = 'Add bill';
  $bill->main_links = get_menu('main_menu');
  $bill->links = get_menu('billing');
  $form_id = 'add_bill_form';
  $bill->forms = render_form($form_id);
  if (!isset($_SESSION['bill'])) {
    $bill->tables = '';
  }
  else {
    $gen_bill = $_SESSION['bill'];
    $form_id = 'generate_bill_form';
    $bill->tables = render_form($form_id, $gen_bill);
  }
  $bill-> display('templates/page.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}
?>

