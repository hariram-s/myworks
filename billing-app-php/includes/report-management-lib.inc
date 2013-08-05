<?php
/**
 * user interface functions used in report management system
 */

require_once 'Savant3.php';

/**
 * Functions for displaying report_form.
 */
function report_form($date) {
  $report_form ="";
	$report_form .= '<form method="POST" action="#" >';
  $report_form .= '<div>';
	$report_form .= '<input id="customer" name="report" type="radio" value="1" />';
  $report_form .= '<label for="customer">Customerwise Report</label>';
	$report_form .= '<input id="report" name="report" type="radio" value="2" />';
	$report_form .= '<label id="report">Itemwise Report</label>';
	$report_form .= '</div>';
	$report_form .= '<div class="date input">';
	$report_form .= '<label for="start">Enter the start-date:</label>';
	$report_form .= '    <input name="start" value=\'' . $date . '\'type="text" />';
	$report_form .= '</div>';
	$report_form .= '<div class="date input">';
	$report_form .= '<label for="end">Enter the end-date:</label>';
	$report_form .= '    <input name="end" value=\'' . $date . '\'type="text" />';
	$report_form .= '</div>';
	$report_form .= '<div>';
	$report_form .= '<input name="submit" type="submit" value="report" />';
	$report_form .= '</div>';
  $report_form .= '</form>';
	return  $report_form;
}

/**
 * Functions for displaying report_form.
 */
function report_submit($start,$end,$report) {
  switch ($report) {
    case 1 :
      $reports = new Savant3();
      $header = array('Customer-id','Customer-Name','Total-Amount');
      $reports->header = $header;
      $reports->rows = report_customer($start, $end); ; 
      $reports->display('templates/list.tpl.php');
      break;
    case 2 : 
      $reports = new Savant3();
      $header = array('Item-Code','Item-Name','Items-Sold','Total-Amount');
      $reports->header = $header; 
      $reports->rows = report_item($start, $end); 
      $reports->display('templates/list.tpl.php');
  }
}

/**
 * Functions for creating the report in the given range by item.
 */
function report_item($start, $end) {
  $db = db_get_connection(); 
  $stmt = $db->query("SELECT code, "
    . " name, "
    . " sum(quantity) "
    . " AS items_sold, "
    . " sum(quantity*selling_price) "
    . " AS Total  "
    . " FROM bill_items "
    . " JOIN bills " 
    . " ON bills.id=bill_items.bill_id "
    . " WHERE date >= $start "
    . " AND date <= $end "
    . " GROUP BY code; "
  );
  $items = array();
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $items[] = array ('item-code'=> $row['code'],
      'item-name'=> $row['name'],
      'item-quantity' => $row['items_sold'],
      'item-total' => $row['Total']
    );
  }
  return $items;
}
  
 
/**
 * Functions for creating the report in the given range by item.
 */
function report_customer($start, $end) {
  $customers = array();
  $db = db_get_connection();
  $stmt = $db->query("SELECT customers.id,customers.name, "
    . " SUM(bill_items.quantity * bill_items.selling_price) "
    . " AS gross,bill_items.selling_price "
    . " FROM customers " 
    . " JOIN bills "
    . " ON customers.id =bills.customer_id "
    . " JOIN bill_items "
    . " ON bills.id=bill_items.bill_id "
    . " WHERE bills.date >= $start "
    . " AND bills.date <= $end "
    . " GROUP BY name"
  );
  while ($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $customers[] = array ('customer-id' => $row['id'],
      'customer-name' => $row['name'],
      'customer-total' =>  $row['gross']
    );
  }  
  return $customers;  
}


?>

