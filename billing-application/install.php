<?php
require_once 'includes/common.inc';
session_start();
/**
 * Create a string for enter_database_form 
 */
function enter_database_form() {
  $form = '';
  $form .= '<form id="database_details" method="POST" action="install.php">';
  $form .= '<div class="text-input">';
  $form .= '<label for="database">Enter the database Name:</label>';
  $form .= '<input id="database" name="database"  type="text" />';
  $form .= '</div>';
  $form .= '<div class="text-input">';
  $form .= '<label for="username">Enter the database username:</label>'; 
  $form .= '<input id="username" name="username"  type="text" />';
  $form .= '</div>';
  $form .= '<div class="text-input">';
  $form .= '<label for="password">Enter the database password:</label>'; 
  $form .= '<input id="password" name="password"  type="password" />';
  $form .= '</div>';
  $form .= '<div>';
  $form .= '<input type="submit" name="database_submit" value="Submit"/>';
  $form .= '</div>';
  $form .= '</form>';
  return $form;
}

/**
 * Function for database submit.
 *
 * @param string $dbname.
 * @param string $username.
 * @param string $password. 
 */
function enter_database_submit($dbname, $username, $password) {
  $result = initialize_storage($dbname, $username, $password);
  if ($result == true)  {
    $_SESSION['database'] = $dbname;
    $_SESSION['username'] = $username;
    $_SESSION['password'] = $password;
    return true;
  }
  else {
    return 'Entered database doesnt exists. Please check that';
  }
}

/**
 * Function for creating congiuration file.
 *
 * @param string $dbname.
 * @param string $username.
 * @param string $password.
 */
function create_config_file($dbname, $username, $password) {
  try {
    $file = @fopen('config/config.php', 'w+');
    if ($file !== FALSE) {
      fwrite($file, '<?php' . "\n");
      fwrite($file, '$db_name=\'' . $dbname . '\';' . "\n");
      fwrite($file, '$db_username=\'' . $username . '\';' . "\n");
      fwrite($file, '$db_password=\'' . $password . '\';' . "\n");
      fwrite($file, '?>' . "\n");
      fclose($file);
      return true;
    }
  } catch (Exception $e) {
      return false;
  }
}

/**
 * Function for creating admin entry form 
 */
function admin_entry_form() {
  $form = '';
  $form .= '<form id="first_user_details" method="POST" action="install.php">';
  $form .= '<div class="text-input">';
  $form .= '<label for="username">Username:</label>'; 
  $form .= '<input id="username" name="username"  type="text" />';
  $form .= '</div>';
  $form .= '<div class="text-input">';
  $form .= '<label for="password">Password:</label>'; 
  $form .= '<input id="password" name="password"  type="password" />';
  $form .= '</div>';
  $form .= '<div class="text-input">';
  $form .= '<label for="confirm_password">Confirm password:</label>'; 
  $form .= '<input id="confirm_password" name="confirm_password"  type="password" />';
  $form .= '</div>';
  $form .= '<div>';
  $form .= '<input type="submit" name="user_submit" value="Submit"/>';
  $form .= '</div>';
  $form .= '</form>';
  return $form;
}

/**
 * Function for admin entry submit
 */
function admin_entry_submit($username, $password) {
  if (create_first_user($username, $password)) {
    $_SESSION['user']['name'] = $username;
    $_SESSION['user']['password'] = $password;
    return true;
  }
  return false;
}

/**
 * Function for creating tables inside the database 
 */
function create_tables() {
  try {
    $db = db_get_connection(
      $_SESSION['database'],
      $_SESSION['username'],
      $_SESSION['password']
    );
    
    // Query for creating users table
    $stmt = $db->prepare("CREATE TABLE users ( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "name VARCHAR(50) NOT NULL UNIQUE, "
      . "password VARCHAR(100), "
      . "role_id INT, "
      . "status INT DEFAULT 1 "
      . ")"
      );
    $stmt->execute();
    
    // Query for creating roles table
    $stmt = $db->prepare("CREATE TABLE roles( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "role_name VARCHAR(50) NOT NULL UNIQUE "
      . ")"
      );
    $stmt->execute();
    
    // Query for creating items table
    $stmt = $db->prepare("CREATE TABLE items( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "code VARCHAR(50) NOT NULL UNIQUE, "
      . "name VARCHAR(50), "
      . "selling_price INT, "
      . "current_stock INT, "
      . "status INT DEFAULT 1 "
      . ")"
    );
    $stmt->execute();
    
    // Query for creating stock_details table
    $stmt = $db->prepare("CREATE TABLE stock_details( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "date INT NOT NULL, "
      . "item_code VARCHAR(50), "
      . "quantity INT "
      . ")"
      );
    $stmt->execute();
    
    // Query for creating bills table
    $stmt = $db->prepare("CREATE TABLE bills( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, " 
      . "date INT, customer_id INT, " 
      . "user_id INT, "
      . "status INT DEFAULT 1 "
      . ")"
      );
    $stmt->execute();
    
    // Query for creating bill_items table
    $stmt = $db->prepare("CREATE TABLE bill_items( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "bill_id INT, code VARCHAR(50), "
      . "name VARCHAR(50), "
      . "quantity INT, "
      . "selling_price INT "
      . ")"
    );
    $stmt->execute();
    
    // Query for creating customers table
    $stmt = $db->prepare("CREATE TABLE customers( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "name VARCHAR(50) NOT NULL,  "
      . "status INT DEFAULT 1, "
      . "date INT "
      . ")"
      );
    $stmt->execute();
    
    // Query for creating sessions table
    $stmt = $db->prepare("CREATE TABLE session( "
      . "id INT UNSIGNED NOT NULL AUTO_INCREMENT KEY, "
      . "user_id INT NOT NULL,  "
      . "session_id VARCHAR(50) NOT NULL "
      . ")"
      );
    $stmt->execute();
    
    return true;
  } catch (PDOException $ex) {
      return "An Error occured! " . $ex->getMessage();
  } 
}

/**
 * Function for creating first user in a query 
 */
function create_first_user($username, $password) {
  $db = db_get_connection(
    $_SESSION['database'],
    $_SESSION['username'],
    $_SESSION['password']
  );
  $stmt = $db->prepare("INSERT INTO users(name, password, role_id) VALUES(:username, :password, :role_id)");
  $stmt->execute(array(':username' => $username,
    ':password' => sha1($password), 
    ':role_id' => 1 )
  );
  $row_count = $stmt->rowCount();
  if ($row_count > 0) {
    return true;
  }
  return false;
}

/**
 * Function for creating first customer in a query 
 */
function create_first_customer() {
  $db = db_get_connection($_SESSION['database'], 
    $_SESSION['username'], 
    $_SESSION['password']
  );
  $date = time();
  $stmt = $db->prepare("INSERT INTO customers(name, date) VALUES(:name, :date)");
  $stmt->execute(array(':name' => 'General Customer', ':date' => $date ));
  $row_count = $stmt->rowCount();
  if ($row_count > 0) {
    return true;
  }
  return false;
}

/**
 * Function for creating roles in a query 
 */
function create_roles() {
	$db = db_get_connection($_SESSION['database'], 
	  $_SESSION['username'], 
	  $_SESSION['password']
	);
 	$db->query("INSERT INTO roles(role_name) VALUES('admin')");
  $db->query("INSERT INTO roles(role_name) VALUES('user')");	
}

/**
 * Function for configuration submit part 
 */
function create_config_submit() {
  return create_config_file($_SESSION['database'], 
    $_SESSION['username'], 
    $_SESSION['password']
  );
}

if (!isset($_SESSION['case'])) {
  $_SESSION['case'] = 1;
}
  $path = getcwd();
if (file_exists($path . '/config/config.php')) {
   $_SESSION['case'] = 4;
 }
$msg = '';
$content = '';
switch ($_SESSION['case']) {
  case 1 :
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
      $result = enter_database_submit($_POST['database'], 
        $_POST['username'], 
        $_POST['password']
      );
      if($result == 1) {
        create_tables();
        $_SESSION['case'] = 2;
        redirect('install.php');  
      }
      else {
        $msg = 'Please enter valid database name, username and password';
      } 
    }
    $content = enter_database_form();
    break;
  case 2 :
    if ($_SERVER['REQUEST_METHOD'] == 'POST') {
      $result = admin_entry_submit($_POST['username'], 
        $_POST['password']
      );
      if($result == 1) {
        create_first_customer();
        create_roles();
        $_SESSION['case'] = 3;
        redirect('install.php');
      }
      else {
        $msg = 'Please enter valid admin, username and password';
      }
    }
    $content = admin_entry_form();
    break;
  case 3 :  
    $msg .= "Your installation completed succesfully.  ";
    $msg .= " Your user name is ". $_SESSION['user']['name'] ;
    $msg .= " Your password is ".$_SESSION['user']['password'] ;
    create_config_submit();
    $content = '';
    break; 
  case 4:
    $msg = 'Sorry. This application is already installed in your web server.';
    $content = ' ';
    session_destroy();
    break;
}
?><!DOCTYPE HTML>
<html>
  <head>
    <title>Installation</title>
    <meta http-equiv="content-type" content="text/html; charset=utf-8" />
  </head>
  <body> 
    <h1>Installation</h1>
    <?php 
      echo $msg;
      echo $content;
    ?>
  </body>
</html>

