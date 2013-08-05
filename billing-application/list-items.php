<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/stock-management-lib.inc';
require_once 'config/menu.conf.inc';
$previous = curPageName();
if (authorize('list_items')) {
  $header = array ('Mark', 'Item Code' , 'Item name', 'Selling price', 'Current Stock', 'Actions');
  $list_items = new Savant3();
  $list_items->title = 'List item';
  $list_items->main_links = get_menu('main_menu');
  $list_items->links = get_menu('stocks');
  $list = list_items();
  foreach ($list as $index => $item)  {
    if (authorize('edit_item')) {
      $link = "<a href='edit-item.php?q={$item['code']}'>Edit</a>";
      $list[$index][] = $link;
    }
    $check_box = "<input name=\"codes[{$item['code']}]\" type='checkbox' value='1'/>";
    array_unshift($list[$index],$check_box);
  }
  $rows = $list;
  $list_items->inputs = list_item_form($header,$rows); 
  $list_items->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}
?>

