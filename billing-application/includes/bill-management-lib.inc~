<?php
require_once 'Savant3.php';
/**
 * user interface functions used in bill management system
 */

/**
 * Functions for displaying addbill_form.
 */
function add_bill_form() {
  $date = date('d/m/Y');
  $form['id'] = 'add_bill_form';
  $form['state'] = 0;
  $form['form']['date'] = array(
    'label' => 'Enter the date:',
    'type' =>'text',
    'default' =>$date,
    'required' =>1
  );
  $form['form']['cus_id'] = array(
    'label' => 'Enter the customer-id:',
    'type' =>'text',
    'default' =>1,
    'required' =>1
  );
  $form['form']['code'] = array(
    'label' => 'Enter the item-code:',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  ); 
  $form['form']['quantity'] = array(
    'label' => 'Enter the quantity:',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['addbill'] = array(
    'value' => 'Add bill',
    'type' =>'submit',
    'default' =>'Add bill',
    'required' =>1
  );   
	return $form;
}

function add_bill_form_validate(&$form) {
  $item_code = $form['form']['code']['value'];
  if((!empty($item_code)) && (!item_code_exists($item_code))) {
    $msg = "Item code doesnt exists";
    set_form_error($form,'code',$msg);
    return false;
  }
  else {
    return true;
  } 
}

/**
 * Functions for submitting the billno for searching.
 */
function add_bill_form_submit(&$form) {
  $date = $form['form']['date']['value'];
  $cus_id = $form['form']['cus_id']['value'];
  $item_code = $form['form']['code']['value'];
  $quantity = $form['form']['quantity']['value'];
  $add_bill = add_bill($date,$cus_id,$item_code,$quantity);
  if ($add_bill) {
    redirect ('add-bill.php');   
  }
  else {
    return 0;
  }
}

/**
 * Functions for submitting the values entered.
 */
function add_bill($date,$cus_id,$code,$qty) {
  $db = db_get_connection();
 	$stmt1 = $db->prepare("SELECT code,name,selling_price,current_stock FROM items where code= :code");
  $stmt1->execute(array(':code' => $code)); 
  while($row = $stmt1->fetch(PDO::FETCH_ASSOC)) {
    if($row['current_stock'] >= $qty) {
      $total = $qty * $row['selling_price'];
      $output = array ('date' => $date,
        'cus_id' => $cus_id,
        'itemcode' => $row['code'],
        'name' => $row['name'],
        'quantity' => $qty,
        'current_stock' => $row['current_stock'],
        'selling_price' => $row['selling_price'],
        'total' => $total 
      );
      $_SESSION['bill'][] = $output;
      return true;     
    }
    else {
      return false;
    }                   
  }
} 

function generate_bill_form($gen_bills) {
  $date = date('Y-m-d');
  $form['id'] = 'generate_bill_form';
  $form['template'] = 'templates/table.tpl.php';
  $grand_total = 0;
  $row_count = 1;
	foreach ($gen_bills as $bill) {
    $form['form']['itemcode'.$row_count] = array(
      'name' => 'itemcode'.$row_count,
      'label' => 'Itemcode',
      'type' =>'text',
		  'default' => $bill['itemcode'],
      'required' =>1
    );
    $form['form']['name'.$row_count] = array(
      'name' => 'name'.$row_count,
      'label' => 'Item Name',
      'type' =>'',
		  'default' => $bill['name'],
      'required' =>''
    );
    $form['form']['quantity'.$row_count] = array(
      'name' => 'quantity'.$row_count,
      'label' => 'Quantity',
      'type' =>'text',
		  'default' => $bill['quantity'],
      'required' =>1
    );
    $form['form']['selling_price'.$row_count] = array(
      'name' => 'selling_price'.$row_count,
      'label' => 'Selling Price',
      'type' =>'',
		  'default' => $bill['selling_price'],
      'required' =>''
    );
    $form['form']['total'.$row_count] = array(
      'name' => 'total'.$row_count,
      'label' => 'Total',
      'type' =>'',
		  'default' => $bill['total'],
      'required' =>''
    );
    $grand_total = $grand_total + $bill['total'];
    $row_count ++;
  }
  $form['form']['grand_total'] = array(
    'label' => '',
    'type' =>'total',
	  'default' => $grand_total,
    'required' =>''
  );
  $form['form']['submit'] = array(
    'label' => '',
    'type' =>'submit',
    'default' => 'Generate bill',
    'required' =>''
  );
  $form['rowcount'] = $row_count;
  return $form; 
}

/**
 * Functions for generating the bill.
 */
function generate_bill_form_submit(&$form) {
  if (!isset($_SESSION['billno'])) {
    $_SESSION['billno'] = 1;
  }
  $result = generate_bill();
  if ($result) {
    redirect('view-bill.php');
    return 1;
  }
  else {
    return 0;
  }
}

/**
 * Functions for generating the bill.
 * 
 * @parameter $code
 * @parameter $quantity
 */
function generate_bill() {
  $db = db_get_connection();
  $date = $_SESSION['bill'][0]['date'];
  $cust_id = $_SESSION['bill'][0]['cus_id'];
  $date_str = strtotime($date);
  $userid = $_SESSION['userid'];
  // Inserting the value into bills.
  $stmt1 = $db->prepare("INSERT INTO bills(date,customer_id,user_id) "
    . " VALUES(:date,:cust_id,:user_id)"
  );
  $stmt1->execute(array(':date' => $date_str,
    ':cust_id' => $cust_id,
    ':user_id' => $userid
  ));
  $_SESSION['bill_id'] = $db->lastInsertId();
  
  // Inserting the values into bill items.
  $items = $_SESSION['bill'];
  $stmt2 = $db->prepare("INSERT INTO bill_items(bill_id,code,name,quantity,selling_price)"
  . " VALUES(:bill_id,:code,:name,:quantity,:selling_price)");
  foreach($items as $item) { 
    $stmt2->execute(array(':bill_id' => $_SESSION['bill_id'],
    ':code' => $item['itemcode'],
    ':name' => $item['name'],
    ':quantity' => $item['quantity'],
    ':selling_price' => $item['selling_price']
    ));
  
  // Updating the current stock of the items.   
  $quantity = $item['current_stock'] - $item['quantity'];
  $stmt3 = $db->prepare("UPDATE items SET current_stock = :quantity WHERE code = :code");
  $stmt3->execute(array(':quantity' => $quantity, ':code' => $item['itemcode'])) ;  
  }
  return $stmt2->rowCount() > 0;
} 

/**
 * Functions for displaying searchbill_form.
 */
function searchbill_form() {
  $search_bill_form ="";
	$search_bill_form .= '<form method="POST" action="search-bill.php" >';
	$search_bill_form .= '<div class= "bill search">';
	$search_bill_form .= '<label for="billno">Enter the bill no:</label>';
	$search_bill_form .= '<input name="billno" type="text" />';
	$search_bill_form .= '</div>';
	$search_bill_form .= '<div>';
	$search_bill_form .= '<input name="searchbill" type="submit" value="searchbill" />';
	$search_bill_form .= '</div>';
  $search_bill_form .= '</form>';
	return  $search_bill_form;
}

/**
 * Functions for submitting the billno for searching.
 */
function search_bill_submit($billno) {
  return bill_exists($billno);
}  

/**
 * Functions for showing the search bill.
 */
function show_bill($header,$rows) {
  $show_bill_table ="";
	$show_bill_table .= '<table>';
	$show_bill_table .= '  <thead>';
	$show_bill_table .= '    <tr>';
	foreach ($header as $head) { 
    $show_bill_table .=  '     <th>'.  $head .'</th>';
  } 
	$show_bill_table .= '    </tr>';
	$show_bill_table .= '  <thead>';
	$grand_total = 0;
	foreach ($rows as $row) {
	  $customer_id = $row['customer_id'];
	  $user_id = $row['user_id'];
    $show_bill_table .= '    <tr>'; 
    $show_bill_table .=  '     <td> ' . $row['code'] .'</td>'; 
    $show_bill_table .=  '     <td>' . $row['name'].'</td>'; 
    $show_bill_table .=  '     <td>' . $row['quantity'] . '</td>'; 
    $show_bill_table .=  '     <td>' . $row['selling_price'].'</td>'; 
    $show_bill_table .=  '     <td>' . $row['total'].'</td>';
	  $show_bill_table .= '    </tr>';
	  $grand_total = $grand_total + $row['total'];
	}
	$show_bill_table .= '  <tfoot>';
	$show_bill_table .= '    </tr>'; 
  $show_bill_table .=  '     <td>'."The grand total is ".$grand_total.'</td>'; 
	$show_bill_table .= '    </tr>';
	$show_bill_table .= '  <tfoot>';
	$show_bill_table .= '</table>';
	$show_bill_table .= '<div class="gen-bill input">';
	$show_bill_table .= '  <p>Customer id:\'' . $customer_id . '\' </p> ';
	$show_bill_table .= '  <p>User id:\'' . $user_id . '\' </p> ';
	$show_bill_table .= '</div>';
	return $show_bill_table;
}

/**
 * Functions for showing the search bill.
 */
function print_bill($header,$rows) {
  $print_bill_table ="";
	$print_bill_table .= '<table>';
	$print_bill_table .= '  <thead>';
	$print_bill_table .= '    <tr>';
	foreach ($header as $head) { 
    $print_bill_table .=  '     <th>'.  $head .'</th>';
  } 
	$print_bill_table .= '    </tr>';
	$print_bill_table .= '  <thead>';
	$grand_total = 0;
	foreach ($rows as $row) {
    $print_bill_table .= '    <tr>'; 
    $print_bill_table .=  '     <td> ' . $row['itemcode'] .'</td>'; 
    $print_bill_table .=  '     <td>' . $row['name'].'</td>'; 
    $print_bill_table .=  '     <td>' . $row['quantity'] . '</td>'; 
    $print_bill_table .=  '     <td>' . $row['selling_price'].'</td>'; 
    $print_bill_table .=  '     <td>' . $row['total'].'</td>';
	  $print_bill_table .= '    </tr>';
	$grand_total = $grand_total + $row['total'];
	}
	$print_bill_table .= '  <tfoot>';
	$print_bill_table .= '    </tr>'; 
  $print_bill_table .=  '     <td>'."The grand total is ".$grand_total.'</td>'; 
	$print_bill_table .= '    </tr>';
	$print_bill_table .= '  <tfoot>';
	$print_bill_table .= '</table>';
	return $print_bill_table;
}

/**
 * Function for check whether the bill exists or not
 * 
 * @param string $id.
 */
function bill_exists($id) {
  $db = db_get_connection();
  $stmt = $db->prepare("SELECT bills.id "
  . "FROM bills "
  . "JOIN bill_items  "
  . "WHERE bills.id = bill_items.bill_id "
  . " AND status = :status "
  . "AND bills.id = :id");
  $stmt->execute(array(':status'=> 1,':id'=>$id));
  $row = $stmt->fetchAll(PDO::FETCH_ASSOC);
  $row_count = $stmt->rowCount();
  if($row_count > 0) {
    return true;
  }
  return false;
}

/**
 * Functions searching a particular bill.
 */ 
function view_bill($id) {
  $db = db_get_connection();
  $stmt = $db->prepare("SELECT bill_items.name, bill_items.code, "
  . "bill_items.quantity, bill_items.selling_price, "
  . "bills.user_id, bills.customer_id " 
  . "FROM bill_items "
  . "JOIN bills "
  . "ON bill_items.bill_id = bills.id "
  . "AND bill_items.bill_id = $id "
  ); 
  $stmt->execute(array(':id'=>$id));
  $bill = array();
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $total = $row['quantity'] * $row['selling_price'];
    $bill[] = array ( 'code' => $row['code'],
      'name' => $row['name'],
      'quantity' => $row['quantity'],
      'selling_price' => $row['selling_price'],
      'customer_id' => $row['customer_id'],      
      'user_id' => $row['user_id'],
      'total' => $total 
    );                      
  }
  return $bill; 
}

/**
 * Functions for displaying addcustomer_form.
 */
function add_customer_form() {
  $date = date('d/m/Y');
  $form['id'] = 'add-customer';
  $form['state'] = 0;
  $form['form']['date'] = array(
    'label' => 'Enter the date',
    'type' =>'text',
    'default' => $date,
    'required' =>1
  );
  $form['form']['name'] = array(
    'label' => 'Enter the customer name:',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['addcustomer'] = array(
    'type' =>'submit',
    'value' => 'Add',
    'default' =>'Add',
    'required' =>1
  );
	return  $form;
}

function add_customer_form_validate(&$form) {
  $cust_name = $form['form']['name']['value'];
  if (!customer_exists($cust_name)) {
    return true;
    
  }
  else {
    $msg = "Entered customer already exists";
    set_form_error($form,null,$msg);
    return false;
    
  } 
}

/**
 * Functions for submitting the billno for searching.
 */
function add_customer_form_submit(&$form) {
  $cust_name = $form['form']['name']['value'];
  $date = $form['form']['date']['value'];
  if ($id = add_customer($cust_name,$date)) {
    redirect ('list-customers.php');
    return "Customer added successfully and id is $id";    
  }
  else {
    return false;
  }
}

function customer_exists($customer_name) {
  $db = db_get_connection() ;
	$result = $db->prepare( "SELECT id FROM customers WHERE status=:status AND name=:name" );
  $result->execute( array(':status' => 1,':name' => $customer_name) );
  if($result->rowCount() > 0) {
	  return true;
	}    
	return false;
}


/**
 * Functions for submiting the list customer form.
 */
function list_customer_form($header,$rows) {
	$list_customer_form ="";
	$list_customer_form .= '<form method="POST" action="process-customers.php">';
	$list_customer_form .= '<table>';
	$list_customer_form .= '  <thead>';
	$list_customer_form .= '    <tr>';
	foreach ($header as $head) { 
    $list_customer_form .=  '     <th>'.  $head .'</th>';
  } 
	$list_customer_form .= '    </tr>';
	$list_customer_form .= '  <thead>';
	foreach ($rows as $row) { 
    $list_customer_form .= '    <tr>';
    foreach ($row as $value) { 
      $list_customer_form .=  '     <td>' . $value .'</td>';
    } 
	  $list_customer_form .= '    </tr>';
	}
	$list_customer_form .= '</table>';
  $list_customer_form .= '<div>';
  $list_customer_form .= '<input type="submit" name="submit" value="Disable"/>';
  $list_customer_form .= '</div>';
  $list_customer_form  .= '</form>';
	return $list_customer_form;
}

/**
 * Functions for submiting the list customer form.
 */
function disabled_customers_form($header,$rows) {
	$disabled_customers_form ="";
	$disabled_customers_form .= '<form method="POST" action="process-customers.php">';
	$disabled_customers_form .= '<table>';
	$disabled_customers_form .= '  <thead>';
	$disabled_customers_form .= '    <tr>';
	foreach ($header as $head) { 
    $disabled_customers_form .=  '     <th>'.  $head .'</th>';
  } 
	$disabled_customers_form .= '    </tr>';
	$disabled_customers_form .= '  <thead>';
	foreach ($rows as $row) { 
    $disabled_customers_form .= '    <tr>';
    foreach ($row as $value) { 
      $disabled_customers_form .=  '     <td>' . $value .'</td>';
    } 
	  $disabled_customers_form .= '    </tr>';
	}
	$disabled_customers_form .= '</table>';
  $disabled_customers_form .= '</div>';
  $disabled_customers_form .= '<input type="submit" name="submit" value="Enable"/>';
  $disabled_customers_form .= '</div>';
	return $disabled_customers_form;
}
 
/**
 * Used for listing the details of all enabled customers
 */
function list_customers() {
  $db = db_get_connection();
  $stmt = $db->query("SELECT id,name,date FROM customers WHERE status = 1");
  $output = array();
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $date = date('Y-m-d',$row['date']);
    $output[] = array('id' => $row['id'],
      'name' => $row['name'],
      'date' => $date
		);
  }   
  return $output; 
}

/**
 * Used for listing the disabled customers
 */
function disabled_customers_list() {
  $db = db_get_connection();
  $stmt = $db->query("SELECT id,name,date,status FROM customers WHERE status = 0");
  $output = array();
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $date = date('Y-m-d',$row['date']);
    $output[] = array('id' => $row['id'],
      'name' => $row['name'],
      'date' => $date
		);
  }   
  return $output; 
}

/**
 * Used for adding new customers to the table
 *
 *@param string $name
 *@param string $date
*/                                                                                                                                  
function add_customer($name,$date) {
  $db = db_get_connection();
  $d = strtotime ($date);
  $stmt = $db->prepare("INSERT INTO customers (name,date) VALUES (:name,:date)");
  $stmt->execute(array(':name' => $name, ':date' => $d));  
  $insertId = $db->lastInsertId();
  return $insertId;   
}

/**
 * Used for disabling customers
 */
function disable_customer($ids) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE customers SET status = 0 WHERE id = :id");
  foreach ($ids as $id) {
    $stmt->execute(array(':id'=>$id)); 
  }
  return $stmt->rowCount() > 0;
}

/**
 * Used for disabling customers
 */
function enable_customer($ids) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE customers SET status = 1 WHERE id = :id");
  foreach ($ids as $id) {
    $stmt->execute(array(':id'=>$id)); 
  }
  return $stmt->rowCount() > 0;
}

/**
 * Functions for displaying cancel bill form.
 */
function cancel_bill_form() {
  $cancel_bill_form ="";
	$cancel_bill_form .= '<form method="POST" action="cancel-bill.php" >';
	$cancel_bill_form .= '<div class= "bill search">';
	$cancel_bill_form .= '<label for="billno">Enter the bill no:</label>';
	$cancel_bill_form .= '<input name="billno" type="text" />';
	$cancel_bill_form .= '</div>';
	$cancel_bill_form .= '<div>';
	$cancel_bill_form .= '<input name="cancelbill" type="submit" value="Cancelbill" />';
	$cancel_bill_form .= '</div>';
  $cancel_bill_form .= '</form>';
	return  $cancel_bill_form;
}

/**
 * Functions for cancel bill submit
 */
function cancel_bill_submit($billno) {
  if (bill_exists($billno)) {
    return cancel_bill($billno);
  }
}

/**
 * Used for cancelling a specific bill
 */
function cancel_bill($id) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE bills SET status = 0 WHERE id = :id");
  $stmt->execute(array(':id'=>$id));
  return $stmt->rowCount() > 0;
}

