<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/stock-management-lib.inc';
$previous = curPageName();
if (authorize('edit_item')) {
  $code = $_GET['q'];
  $value = get_items($code);
  $edit_item = new Savant3();
  $edit_item->title = 'Edit item';
  $edit_item->main_links = get_menu('main_menu');
  $edit_item->links = get_menu('stocks');
  $edit_item->inputs = edit_item_form($code,$value['name'],$value['selling_price'],$value['current_stock']);  
  $edit_item->display('templates/content.tpl.php');
  if (edit_item_submit($code) == 'list-item') {
    redirect('list-items.php');
  }
  elseif (edit_item_submit($code) == 'error') {
    echo "Please enter all the required fields";
  }
}
else {
  redirect ("login.php?destination=$previous");
}
?>

