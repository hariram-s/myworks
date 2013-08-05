<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/stock-management-lib.inc';
require_once 'Savant3.php';
require_once 'includes/form.inc';

$previous = curPageName();
if (authorize('add_item')) {
  $form_id = 'add_item_form';
  $add_item = new Savant3();
  $add_item->title = 'Add item';
  $add_item->main_links = get_menu('main_menu');
  $add_item->links = get_menu('stocks');
  $add_item->inputs = render_form($form_id); 
  $add_item->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}

