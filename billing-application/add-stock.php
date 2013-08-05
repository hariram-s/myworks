<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/stock-management-lib.inc';
require_once 'Savant3.php';
require_once 'includes/form.inc';

$previous = curPageName();
if (authorize('add_stock')) {
  $form_id = 'add_stock_form';
  $add_stock = new Savant3();
  $add_stock->title = 'Add stock';
  $add_stock->main_links = get_menu('main_menu');
  $add_stock->links = get_menu('stocks');
  $add_stock->inputs = render_form($form_id);
  $add_stock->display('templates/content.tpl.php');
}
else {
  redirect ("login.php?destination=$previous");
}
?>

