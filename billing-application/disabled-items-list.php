<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/stock-management-lib.inc';
require_once 'config/menu.conf.inc';
$previous = curPageName();
if (authorize('list_items')) {
  $header = array ('Mark', 'Item Code' , 'Item name', 'Selling price', 'Current Stock'); 
  $list = disabled_items_list();
  $disabled_items = new Savant3();
  $disabled_items->title = 'Disabled Items list';
  $disabled_items->main_links = get_menu('main_menu');
  $disabled_items->links = get_menu('stocks');
  foreach ($list as $index => $item)  {
    $check_box = "<input name=\"codes[{$item['code']}]\" type='checkbox' value='1'/>";
    array_unshift($list[$index],$check_box);
  } 
  $rows = $list;
  $disabled_items->inputs = disabled_items_form($header,$rows); 
  $disabled_items->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}

