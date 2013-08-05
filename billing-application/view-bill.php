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
  $bill->title = 'Print bill';
  $bill->main_links = get_menu('main_menu');
  $bill->links = get_menu('billing');
  $header = array('Itemcode','Name','Quantity','Selling price','Total-Amount');
  $row = $_SESSION['bill'];
  $bill->bill_no = "Bill no :".$_SESSION['bill_id'];
  $bill->forms = print_bill($header,$row);
  unset ($_SESSION['bill']);
  $bill-> display('templates/page.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}

