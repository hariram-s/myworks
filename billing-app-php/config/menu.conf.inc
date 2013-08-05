<?php
include 'permission.conf.inc';
if(!isset($_SESSION['role'])) {
  $_SESSION['role'] = '';
}
//Main menu
$menu['main_menu'] = array(
  array('title' => 'Home', 
    'href' => 'index.php', 
    'permission' => $permission['login']
  ),
  array('title' => 'Billing', 
    'href' => 'add-bill.php', 
    'permission' => $permission['add_bill']
  ),
  array('title' => 'Users', 
    'href' => 'list-users.php', 
    'permission' => $permission['list_users']
  ),
  array('title' => 'Stocks', 
    'href' => 'list-items.php', 
    'permission' => array ('admin' , 'user')
  ),
  array('title' => 'Reports', 
    'href' => 'report.php', 
    'permission' => $permission['report']
  ),
  array('title' => 'Change Password', 
    'href' => 'change-password.php', 
    'permission' => $permission['change_password']
  ),
  array('title' => 'Log out '.$_SESSION['role'], 
    'href' => 'logout.php', 
    'permission' => $permission['logout']
  ));
  
// Menu for billing management  
$menu['billing'] = array(
  array('title' => 'Create Bill', 
  'href' => 'add-bill.php', 
  'permission' => $permission['add_bill']
  ),
  array('title' => 'Search', 
    'href' => 'search-bill.php', 
    'permission' => $permission['search_bill']
  ),
  array('title' => 'Cancel', 
    'href' => 'cancel-bill.php', 
    'permission' => $permission['cancel_bill']
  ),
  array('title' => 'List Customers', 
    'href' => 'list-customers.php', 
    'permission' => $permission['list_customer']
  ),
  array('title' => 'Add Customer', 
    'href' => 'add-customer.php', 
    'permission' => $permission['add_customer']
  ),
  array('title' => 'Disabled Customers List', 
    'href' => 'disabled-customers-list.php', 
    'permission' => $permission['disabled_customers']
  ));
  
// Menu for user management  
$menu['users'] = array(
  array('title' => 'Add User', 
    'href' => 'add-user.php', 
    'permission' => $permission['add_user']
  ),
  array('title' => 'List Users', 
    'href' => 'list-users.php', 
    'permission' => $permission['list_users']
  ),
  array('title' => 'Disabled Users List', 
    'href' => 'disabled-users-list.php', 
    'permission' => $permission['disabled_users']
  ));
  
// Menu for Stock management 
$menu['stocks'] = array(
  array('title' => 'Add Item', 
    'href' => 'add-item.php', 
    'permission' => $permission['add_item']
  ),
  array('title' => 'List Items', 
    'href' => 'list-items.php', 
    'permission' => $permission['list_items']
  ),
  array('title' => 'Add Stock', 
    'href' => 'add-stock.php', 
    'permission' => $permission['add_stock']
  ),
  array('title' => 'Disabled Items List', 
    'href' => 'disabled-items-list.php', 
    'permission' => $permission['disabled_items']
  ));
?>

