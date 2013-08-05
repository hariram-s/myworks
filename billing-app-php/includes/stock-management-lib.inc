<?php
/**
 * user interface functions used in stock management system
 */

require_once 'Savant3.php';
require_once 'config/menu.conf.inc';

/**
 * Functions for displaying additem_form.
 */
function add_item_form() {
  $form['id'] = 'add_item_form';
  $form['state'] = 0;
  $form['form']['item_code'] = array(
    'label' => 'Enter item-code',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['item_name'] = array(
    'label' => 'Enter item-name',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['price'] = array(
    'label' => 'Enter selling price',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['additem'] = array(
    'type' =>'submit',
    'value' => 'Add',
    'default' =>'Add',
    'required' =>1
  );
	return  $form;
}

/**
 * Functions for adding the items.
 */
function add_item_form_validate(&$form) {
  if (!item_code_exists($_POST['item_code'])) {
    return true;
    
  }
  else {
    $msg = "Entered item already exists";
    set_form_error($form,null,$msg);
    return false;
    
  } 
} 

function add_item_form_submit($form) {
  $item_code =$form['form']['item_code']['value'];
  $item_name =$form['form']['item_name']['value'];
  $price =$form['form']['price']['value'];
  $result = add_item($_POST['item_code'],
      $_POST['item_name'],
      $_POST['price']
  );
  if ($result) {
    redirect('list-items.php');
  }
  else {
    return false;
  }
}
/**
 * Functions for submiting the list item form.
 *
 * @param array $header
 * @param array $rows.
 */
function list_item_form($header,$rows) {
	$list_item_form ="";
	$list_item_form .= '<form id="process-entry" method="POST" action="process-items.php">';
	$list_item_form .= '<table>';
	$list_item_form .= '  <thead>';
	$list_item_form .= '    <tr>';
	foreach ($header as $head) { 
    $list_item_form .=  '     <th>'.  $head .'</th>';
  } 
	$list_item_form .= '    </tr>';
	$list_item_form .= '  <thead>';
	foreach ($rows as $row) { 
    $list_item_form .= '    <tr>';
    foreach ($row as $value) { 
      $list_item_form .=  '     <td>' . $value .'</td>';
    } 
	  $list_item_form .= '    </tr>';
	}
	$list_item_form .= '</table>';
	if (authorize('process_items')) {
    $list_item_form .= '</div>';
    $list_item_form .= '<input type="submit" name="submit" value="Disable"/>';
    $list_item_form .= '<input type="submit" name="submit" value="Reset"/>';
    $list_item_form .= '</div>';
  }
  $list_item_form .= "</form>";
	return $list_item_form;
}

/**
 * Functions for submiting the list item form.
 *
 * @param array $header
 * @param array $rows.
 */
function disabled_items_form($header,$rows) {
	$disabled_items_form ="";
	$disabled_items_form .= '<form id="process-entry" method="POST" action="process-items.php">';
	$disabled_items_form .= '<table>';
	$disabled_items_form .= '  <thead>';
	$disabled_items_form .= '    <tr>';
	foreach ($header as $head) { 
    $disabled_items_form .=  '     <th>'.  $head .'</th>';
  } 
	$disabled_items_form .= '    </tr>';
	$disabled_items_form .= '  <thead>';
	foreach ($rows as $row) { 
    $disabled_items_form .= '    <tr>';
    foreach ($row as $value) { 
      $disabled_items_form .=  '     <td>' . $value .'</td>';
    } 
	  $disabled_items_form .= '    </tr>';
	}
	$disabled_items_form .= '</table>';
	if (authorize('process_items')) {
    $disabled_items_form .= '</div>';
    $disabled_items_form .= '<input type="submit" name="submit" value="Enable"/>';
    $disabled_items_form .= '</div>';
  }
  $disabled_items_form .= "</form>";
	return $disabled_items_form;
}

/**
 * Functions for displaying addstock_form.
 * 
 * @param string date
 */
function add_stock_form() {
  $date = date('d/m/Y');
  $form['id'] = 'add_stock_form';
  $form['state'] = 0;
  $form['form']['date'] = array(
    'label' => 'Enter the date',
    'type' =>'text',
    'default' => $date,
    'required' =>1
  );
  $form['form']['item-code'] = array(
    'label' => 'Enter item-code',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['stock'] = array(
    'label' => 'Enter the stock',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['addstock'] = array(
    'type' =>'submit',
    'value' => 'Add',
    'default' =>'Add',
    'required' =>1
  );
	return  $form;
}
  
/**
 * Functions for adding the items.
 */
function add_stock_form_validate(&$form) {
  $itemcode = $form['form']['item-code']['value'];
  if (item_code_exists($itemcode)) {
    return true;
    
  }
  else {
    $msg = "Entered item doesnt exists";
    set_form_error($form,null,$msg);
    return false;
    
  } 
} 

/**
 * Functions for adding the stock.
 */
function add_stock_form_submit(&$form) {
  $itemcode = $form['form']['item-code']['value'];
  $stock = $form['form']['stock']['value'];
  if(add_stock($itemcode,$stock)) {
    redirect('list-items.php');           
  }
  else {
    return false;
  } 
}

/**
 * Functions for displaying edit item form.
 */
function edit_item_form($code,$name,$price,$stock) {
  $edit_item_form ="";
	$edit_item_form .= "  <form method='POST' action='edit-item.php?q=$code' >";
	$edit_item_form .= '  <div class="edit-item input">';
	$edit_item_form .= '    <h3> Item code: \'' . $code . '\' </h3>';
	$edit_item_form .= "  </div>";
	$edit_item_form .= '  <div class="edit-item input">';
	$edit_item_form .= "    <label>Enter the item-name:</label>";
	$edit_item_form .= '    <input name="item_name" value =\'' . $name . '\' type="text" />';
	$edit_item_form .= "  </div>";
	$edit_item_form .= '  <div class="edit-item input">';
	$edit_item_form .= "    <label>Enter the selling price:</label>";
	$edit_item_form .= '    <input name="price" value =\'' . $price . '\' type="text" />';
	$edit_item_form .= "  </div>";
	$edit_item_form .= "  <div>";
	$edit_item_form .= "    <input name='edititem' type='submit' value='Edit' />";
	$edit_item_form .= "  </div>";
  $edit_item_form .= "</form>";
	return  $edit_item_form;
}

/**
 * Functions for submiting the edit item form.
 */
function edit_item_submit($code) {
  if(isset($_POST['edititem'])) {
    if (!empty($_POST['item_name']) 
      && !empty($_POST['price']) 
      && !empty($_POST['stock'])
    ) {
      edit_item($code,
        $_POST['item_name'],
        $_POST['price'],
        $_POST['stock']
      );
      return 'list-item';
    }
    else {
      return 'error';
    }
  }
}

/**
 * To check whether the item_code exist in the database
 *
 * @parameter string $item_code
 */
function item_code_exists($item_code) {
  $db = db_get_connection();
  $stmt = $db->prepare('SELECT id FROM items where code=:code and status = 1 and current_stock >= 0');
  $stmt->execute(array(':code'=>$item_code));
  $row = $stmt->fetch(PDO::FETCH_ASSOC);
  return $stmt->rowCount() > 0;
}

/**
 * 
 * This function is used to insert values to the database
 *
 * @parameter string $item_code
 * @parameter string $name
 * @parameter string $price
 * @parameter string $stock
 */
function add_item($item_code,$item_name,$price) {
  $db = db_get_connection();
  $stmt = $db->prepare("INSERT INTO "
    . " items(code,name,selling_price,current_stock) "
    . " VALUES(:code,:name,:selling_price,:current_stock)"
  );  
  $stmt->execute(array(':code' => $item_code, 
    ':name' => $item_name, 
    ':selling_price' => $price, 
    ':current_stock' => 0
  )); 
  return $stmt->rowCount() > 0;
}

/**
 * To list the enabled items 
 * 
 */
function list_items() {
  $output = array();
  $db = db_get_connection();
  $stmt = $db->query('SELECT code,name,selling_price,current_stock '
    . ' FROM items'
    . ' WHERE status = 1'
  );
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $output[] = array('code' => $row['code'],
      'name' => $row['name'] ,
	    'selling_price' => $row['selling_price'] ,
	    'current_stock' => $row['current_stock']
	  );                    
  }
  return $output;
}

/**
 * To list the disabled items 
 * 
 */
function disabled_items_list() {
  $output = array();
  $db = db_get_connection();
  $stmt = $db->query('SELECT code,name,selling_price,current_stock '
    . ' FROM items'
    . ' WHERE status = 0'
  );
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $output[] = array('code' => $row['code'],
      'name' => $row['name'] ,
	    'selling_price' => $row['selling_price'] ,
	    'current_stock' => $row['current_stock']
	  );                    
  }
  return $output;
}

/**
 * The function is used to update an item that has already been stored in the database
 * 
 * @parameter string $item_code
 * @parameter $values
 */
function edit_item($item_code,$name,$price,$stock) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE items "
    . " SET name =:name, "
    . "selling_price=:selling_price, "
    . "WHERE code=:code"
  );
  $stmt->execute(array (
    ':code'=> $item_code,
    ':name'=> $name,
    ':selling_price'=> $price
   ));
  return $stmt->rowCount() > 0;
}

/**
 * To get the role of the user
 *
 * @param $code string
 */
function get_items($code) {
  $db = db_get_connection();
  $stmt = $db->prepare("SELECT name,selling_price,current_stock "
    . " FROM items WHERE code=:code"
  );
  $stmt->execute(array(':code'=>$code));
  $row = $stmt->fetch(PDO::FETCH_ASSOC);
  return $row;  
}

/**
 * The function is used to add stock of a particular item
 * 
 * @parameter string $item_code
 * @parameter $quantity
 */
function add_stock($item_code,$quantity) {
  $db = db_get_connection();
  $date = time();
  // To insert the item into stock_details form.
  $stmt = $db->prepare("INSERT into " 
    . " stock_details(date,item_code,quantity) " 
    . "VALUES(:date,:item_code,:quantity)"
  );
  $stmt->execute(array (':date'=> $date,
    ':item_code'=> $item_code,
    ':quantity'=> $quantity
  ));
  // To get the existing stock for adding the current stock. 
  $stmt1 = $db->prepare('SELECT current_stock '
    . ' FROM items ' 
    . ' WHERE code=:code'
  );
  $stmt1->execute(array(':code'=>$item_code));
  $row1 = $stmt1->fetch(PDO::FETCH_ASSOC);  
  $current_stock = $row1['current_stock'] + $quantity; // To add the quantity
  // Update the existing current stock with the newly added stock. 
  $stmt2 = $db->prepare("UPDATE items " 
    . " SET current_stock=:current_stock " 
    . " WHERE code=:code "
  );
  $stmt2->execute(array (':code'=> $item_code,                       
  ':current_stock'=> $current_stock
  ));               
  return $stmt2->rowCount() > 0;
}
 
/**
 * The function is used to disable an item
 * 
 * @parameter string $item_code
 */
function disable_items($codes) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE items SET status = :status WHERE code = :code");
  foreach ($codes as $code) {
    $stmt->execute(array(':status' => 0,':code' => $code));
  }
  return $stmt->rowCount() > 0; 
}

/**
 * The function is used to enable an item
 * 
 * @parameter string $item_code
 */
function enable_items($codes) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE items SET status = :status WHERE code = :code");
  foreach ($codes as $code) {
    $stmt->execute(array(':status' => 1, ':code' => $code));
  }
  return $stmt->rowCount() > 0; 
}

/**
 * The function is used to reset stock of an iten
 * 
 * @parameter string $item_code
 */
function reset_stocks($codes) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE items SET current_stock = 0 WHERE code = :code");
  foreach ($codes as $code) {
    $stmt->execute(array(':code'=>$code));
  }
  return $stmt->rowCount() > 0; 
}
?>
