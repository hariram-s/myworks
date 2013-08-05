<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
$previous = curPageName();
if (authorize('search_bill')) {
  $search_bill = new Savant3();
  $search_bill->title = 'Search bill';
  $search_bill->main_links = get_menu('main_menu');
  $search_bill->links = get_menu('billing');
  $search_bill->inputs = searchbill_form();  
  $search_bill->display('templates/content.tpl.php');
  if(isset ($_POST['searchbill'])) {
    if (!empty($_POST['billno'])) {
      if (search_bill_submit($_POST['billno'])) {
        $header = array ('Code', 'Name' , 'Quantity', 'Selling price', 'total'); 
        $list = view_bill($_POST['billno']);
        echo show_bill($header,$list); 
      }
      else {
        echo "Entered bill doesnt exists";
      }
    }
    else {
      echo "please fill all the required fields";
    }
  }
}
else {
  redirect ("login.php?destination=$previous");
}  
?>

