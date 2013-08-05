<?php
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/report-management-lib.inc';
$previous = curPageName();
if(authorize('report')) {
  $date =date("Y-m-d");
  $report_item = new Savant3();
  $report_item->title = 'Reports';
  $report_item->main_links = get_menu('main_menu');
  $report_item->inputs = report_form($date);  
  $report_item->display('templates/content.tpl.php');
  if(isset ($_POST['report'])) {
    if (!empty($_POST['start']) 
      && !empty($_POST['end'])
    ) {
      $starting = strtotime ($_POST['start']);
      $ending = strtotime ($_POST['end']);
      if ($starting <= $ending) {
        echo report_submit(($starting),($ending),$_POST['report']) ;
      }
      else {
        echo " Please enter a valid date";
      }
    }
    else {
      echo "please fill the required fields";
    }
  }
}
else {
  redirect ("login.php?destination=$previous");
}
?>
