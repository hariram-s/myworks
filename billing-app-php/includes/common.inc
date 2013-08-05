<?php 
/**
 * Common functions for Billing application
 *
 * The functions which we used in all  files are said to common functions
 */

require_once 'config/permission.conf.inc';
require_once 'config/menu.conf.inc';

/**
 * Redirection function.
 *
 * @param string $location. 
 */ 
function redirect ($location) {
  $host = $_SERVER['HTTP_HOST'];
  $uri = rtrim (dirname($_SERVER['PHP_SELF']),'/');
  header("Location: http://$host$uri/$location");
  exit();
}

/**
 * Connect to the database
 */
function initialize_storage($dbname, $username, $password) {
  try {
    $db = new PDO('mysql:host=localhost;dbname='.$dbname, $username, $password);
    return true;
  } catch(Exception $ex) {
      return false;
  }
}

/**
 * Function to gets the connection object
 * 
 * @return object $db
 */
function db_get_connection($dbname='', $username='', $password='') {
  static $db;
  $path = getcwd();
  if (file_exists($path . '/config/config.php')) {
    include 'config/config.php';
  }
  if (empty($dbname)) {
    $dbname = $db_name;
    $username = $db_username;
    $password = $db_password;
  }
  try {
    if (!isset($db)) {
      $db = new PDO('mysql:host=localhost;dbname='.$dbname, $username, $password);
      $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    }
  } catch (PDOException $ex) {
      return "An Error occured! " . $ex->getMessage();
  }
  return $db;
}

/**
 * Function to check whether the user logged in or not.
 *
 */
function is_logged_in() {
  if(isset($_SESSION['userid']) && $_SESSION['userid'] > 0) {
    return true;
  }
  elseif($user = set_user()) {
	  set_role($user['id']);
    return true;
  }
  return false;   
}

/**
 * to set the user
 */
function set_user() {
  if(isset($_COOKIE['session'])) {
    $user['sid'] = $_COOKIE['session'];
    $db = db_get_connection() ;
    $stmt = $db->prepare("SELECT user_id "
    . " FROM session "
    . " WHERE(session_id = :sess_id)"
    );
    $stmt->execute(array(':sess_id' => $user['sid'] ));
    $row = $stmt->fetch(PDO::FETCH_ASSOC);
    $row_count = $stmt->rowCount();
    if ($row_count > 0) {
      $user['id'] = $row['user_id'];
      return $user;
    }
  }
  return false;
}

function set_role ($userid) {
  $db = db_get_connection() ;
  $stmt1 = $db->prepare( "SELECT role_id FROM users WHERE id=:user_id");
  $stmt1->execute( array(':user_id'=>$userid));
  $row1 = $stmt1->fetch(PDO::FETCH_ASSOC);
  if ($stmt1->rowCount() > 0) {
    $stmt2 = $db->prepare("SELECT role_name FROM roles WHERE id=:role_id ");
    $stmt2->execute( array(':role_id'=>$row1['role_id']) );
    $role = $stmt2->fetch(PDO::FETCH_ASSOC);
    $_SESSION['role'] = $role['role_name'];
    return true;
  }
  return false;
}
/**
 * Check authentication for both user and admin.
 * @param string action
 */
function authorize($action) {
	include 'config/permission.conf.inc';
	if (isset($_SESSION['role']) && is_logged_in()) {
		if (isset($permission[$action]) && in_array($_SESSION['role'], $permission[$action])) {
			return true;
		}
	}
	else {
	  return false;
	}
}

/**
 * display menu for both user and admin.
 * 
 * @param string menuname
 * return array of menu
 */
function get_menu($menuname) {
	include 'config/menu.conf.inc';
	$login = is_logged_in();
  if (!$login) {
    $output_menu[] = array('title'=>'Login', 'href' => 'login.php');
  }
  else {
    if (isset($menu[$menuname])) {
      foreach($menu[$menuname] as $key => $value) {
        if(in_array($_SESSION['role'],  $value['permission'])) {
        $output_menu[] = $value;
        }	 
      }
   	}
 	}
 	return $output_menu;
}

/**
 * display the current page
 */
function curPageName() {
  return substr($_SERVER["SCRIPT_NAME"],strrpos($_SERVER["SCRIPT_NAME"],"/")+1);
}

