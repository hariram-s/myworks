<?php 
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
require_once 'includes/user-management-lib.inc';
require_once 'includes/stock-management-lib.inc';
if(isset($_GET['customer_confirm'])) {
	switch ($_GET['customer_confirm']) {
    case 'y':
		  disable_customer($ids);
		  //redirect('list-customers.php');
      break;
    case 'n':
		  //redirect('list-customers.php');
      break;
    case 'yes':
		  enable_customer($ids);
		  redirect('disabled-customers-list.php');
      break;
    case 'no':
		  redirect('disabled-customers-list.php');
      break;
  }
}
elseif(isset($_GET['user_confirm'])) {
	switch ($_GET['user_confirm']) {
    case 'y':
		  disable_users($names);
		  redirect('list-users.php');
      break;
    case 'n':
		  redirect('list-users.php');
      break;
    case 'yes':
		  disable_users($names);
		  redirect('disabled-users-list.php');
      break;
    case 'no':
		  redirect('disabled-users-list.php');
      break;
  }
}
elseif(isset($_GET['stock_confirm'])) {
	switch ($_GET['stock_confirm']) {
    case 'y':
		  disable_items($codes);
		  redirect('list-items.php');
      break;
    case 'n':
		  redirect('list-items.php');
      break;
    case 'yup':
		  reset_stocks($codes);
		  redirect('list-items.php');
      break;
    case 'nope':
		  redirect('list-items.php');
      break;
    case 'yes':
		  enable_items($codes);
		  redirect('disabled-items-list.php');
      break;
    case 'no':
		  redirect('disabled-items-list.php');
      break;
  }
}

