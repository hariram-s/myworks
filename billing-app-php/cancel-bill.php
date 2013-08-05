<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
$previous = curPageName();
if (authorize('cancel_bill')) {
  $cancel_bill = new Savant3();
  $cancel_bill->title = 'Search bill';
  $cancel_bill->main_links = get_menu('main_menu');
  $cancel_bill->links = get_menu('billing');
  $cancel_bill->inputs = cancel_bill_form();  
  $cancel_bill->display('templates/content.tpl.php');
  if(isset ($_POST['cancelbill'])) {
    if (!empty($_POST['billno'])) {
      if (cancel_bill_submit($_POST['billno'])) {
       echo 'The bill no: \'' .$_POST['billno'] . '\' is cancelled succesfully ';
      }
      else{
        echo "The entered bill doesn't exists";
      }
    }
    else {
      echo "Please fill all the required fields";
    }
  }
}
else {
  redirect ("login.php?destination=$previous");
}
?>

