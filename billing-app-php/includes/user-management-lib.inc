<?php
/**
 * user interface functions used in User management system
 */

require_once 'Savant3.php';

/**
 * Functions for displaying login_form.
 */
function login_form() {
  $form['id'] = 'login_form';
  $form['state'] = 0;
  $form['form']['user-name'] = array(
    'label' => 'User name',
    'type' =>'text',
    'default' =>'',
    'required' =>1
    );
    $form['form']['password'] = array(
    'label' => 'password',
    'type' =>'password',
    'default' =>'',
    'required' =>1
    );
    $form['form']['remember'] = array(
    'label' => 'Remember Me',
    'type' =>'checkbox',
    'required' => 0,
    'default' => 0
    );
    $form['form']['login'] = array(
    'type' => 'submit',
    'default' => 'Login',
    'value' => 'Login',
    'required' => 1
    );
    return $form;
}
function login_form_validate(&$form) {
  $username = $form['form']['user-name']['value'];
  $password = $form['form']['password']['value'];
  if(authenticate($username,$password)) {
    return true;
  }
  else {
    $msg = 'User name and password does not match';
    set_form_error($form,null,$msg);
    return false;  
  }  
}
/**
 * Functions for login submit.
 */
function login_form_submit($form) {
  $remember = $form['form']['remember']['value'];
  if($remember) {
    $session_id = session_id();
    setcookie (
    'session',
    $session_id,
    time() + 60*60
    );
    if(store_cookie($_SESSION['userid'],$session_id)) {
      redirect ('index.php');
      
    }
  }
  if(isset($_GET['destination'])) {
    redirect($_GET['destination']);
  }  
    redirect ('index.php');   
}   

/**
 * To store the cookie name.
 */
function store_cookie($userid,$sess_id) {
  $db = db_get_connection();
  $stmt = $db->prepare("INSERT INTO " 
    . " session(user_id,session_id)"
    . " VALUES(:user_id,:sess_id)"
  );
  $stmt->execute(array(':user_id' => $userid,
    ':sess_id' =>$sess_id
  ));
  return $stmt->rowCount() > 0 ;
}


/**
 * Functions for displaying Change password forn.
 */
function change_password_form() {
	$change_password_form ="";
	$change_password_form .= '<form id="Database-entry" method="POST" action="change-password.php">';
  $change_password_form .= '<div class="change-password input">';
  $change_password_form .= '<label for="password">Enter the password:</label>'; 
  $change_password_form .= '<input id="password" name="password" type="password"/>';
  $change_password_form .= '</div>';
  $change_password_form .= '<div class="change-password input">';
  $change_password_form .= '<label for="confirm-password">Confirm password:</label>'; 
  $change_password_form .= '<input id="confirm-password" name="confirmpass" type="password"/>';
  $change_password_form .= '</div>';
  $change_password_form .= '<div>';
  $change_password_form .= '<input type="submit" name="change" value="Change password"/>';
  $change_password_form .= '</div>';
	return $change_password_form;
}

/**
 * Functions for Change password submit.
 */
function change_password_submit() {
  if (isset($_POST['change'])== true) {
    if($_POST['password'] == $_POST['confirmpass']) {
      return 'change-password';
    }
    else {
      return 'error';
    }
  }
}

/**
 * Functions for displaying add user form.
 */
function add_user_form() {
  $form['id'] = 'add_user_form';
  $form['state'] = 0;
  $form['form']['username'] = array(
    'label' => 'Enter User name',
    'type' =>'text',
    'default' =>'',
    'required' =>1
  );
  $form['form']['role'] = array(
    'options' => array(1 => 'admin',2 => 'user'),
    'type' =>'radio',
    'default' =>'',
    'required' =>1
  ); 
  $form['form']['password'] = array(
    'label' => 'Enter the password:',
    'type' =>'password',
    'default' =>'',
    'required' =>1
  ); 
  $form['form']['confirmpass'] = array(
    'label' => 'Confirm password:',
    'type' =>'password',
    'default' =>'',
    'required' =>1
  );
  $form['form']['adduser'] = array(
    'value' => 'Add user',
    'type' =>'submit',
    'default' =>'Add user',
    'required' =>1
  );      
	return $form;
}

/**
 * Functions for submiting the add user form.
 */
function add_user_form_validate(&$form) {
  $name = $form['form']['username']['value'];
  if (user_exists($name) == false) {
    return true; 
  }
  else {
    $msg = "Entered user already exists";
    set_form_error($form,$name,$msg);
    return false;
  }  
}

function add_user_form_submit($form) {
  $name = $form['form']['username']['value'];
  $role = $form['form']['role']['value'];
  $pass = $form['form']['password']['value'];
  $confirmpass = $form['form']['confirmpass']['value'];
   $result = add_user($name,
      $role,
      $pass,
      $confirmpass
  );
  if ($result) {
    redirect('list-users.php');
  }
  else {
    return false;
  }  
}


/**
 * Functions for displaying edit user form.
 */
function edit_user_form($username) {
	$edit_user_form ="";
	$edit_user_form .= "<form id='user-entry' method='POST' action='edit-user.php?q=$username'>";
  $edit_user_form .= '<div class="edit-user input">';
  $edit_user_form .= '<label for="username"> User name: </label>'; 
  $edit_user_form .= " ' $username ' ";
  $edit_user_form .= '</div>';
  $edit_user_form .= '<div>';
	$edit_user_form .= '<input id="admin" name="role" type="radio" value="1" />';
  $edit_user_form .= '<label for="admin">Admin</label>';
	$edit_user_form .= '<input id="user" name="role" type="radio" value="2" />';
	$edit_user_form .= '<label for="user">User</label>';
	$edit_user_form .= '</div>';
  $edit_user_form .= '<input type="submit" name="edituser" value="Edit user"/>';
  $edit_user_form .= '</div>';
  $edit_user_form .= "</form>";
	return $edit_user_form;
}

/**
 * Functions for submiting the edit user form.
 */
function edit_user_submit($role,$username) {
  if (edit_user($role,$username)) {
    return "The entered user edited succesfully";
  }
}

/**
 * Functions for submiting the list user form.
 *
 * @param array $header
 * @param array $rows.
 */
function list_users_form($header,$rows) {
	$list_users_form ="";
	$list_users_form .= '<form id="user-entry" method="POST" action="process-users.php">';
	$list_users_form .= '<table>';
	$list_users_form .= '  <thead>';
	$list_users_form .= '    <tr>';
	foreach ($header as $head) { 
    $list_users_form .=  '     <th>'.  $head .'</th>';
  } 
	$list_users_form .= '    </tr>';
	$list_users_form .= '  <thead>';
	foreach ($rows as $row) { 
    $list_users_form .= '    <tr>';
    foreach ($row as $value) { 
      $list_users_form .=  '     <td>' . $value .'</td>';
    } 
	  $list_users_form .= '    </tr>';
	}
	$list_users_form .= '</table>';
  $list_users_form .= '</div>';
  $list_users_form .= '<input type="submit" name="submit" value="Disable"/>';
  $list_users_form .= '</div>';
	return $list_users_form;
}

/**
 * Functions for submiting the list user form.
 *
 * @param array $header
 * @param array $rows.
 */
function disabled_users_form($header,$rows) {
	$disabled_users_form ="";
	$disabled_users_form .= '<form id="user-entry" method="POST" action="process-users.php">';
	$disabled_users_form .= '<table>';
	$disabled_users_form .= '  <thead>';
	$disabled_users_form .= '    <tr>';
	foreach ($header as $head) { 
    $disabled_users_form .=  '     <th>'.  $head .'</th>';
  } 
	$disabled_users_form .= '    </tr>';
	$disabled_users_form .= '  <thead>';
	foreach ($rows as $row) { 
    $disabled_users_form .= '    <tr>';
    foreach ($row as $value) { 
      $disabled_users_form .=  '     <td>' . $value .'</td>';
    } 
	  $disabled_users_form .= '    </tr>';
	}
	$disabled_users_form .= '</table>';
  $disabled_users_form .= '</div>';
  $disabled_users_form .= '<input type="submit" name="submit" value="Enable"/>';
  $disabled_users_form .= '</div>';
	return $disabled_users_form;
}

/**
 *
 */
function confirm_form($names) {
  $confirm_form  = "";
	$confirm_form .= '<form id="confirmation" method="POST" action="#">';
	$confirm_form .= "Are you sure to do the operation with $names";
  $confirm_form .= '<div>';
	$confirm_form .= '<input id="admin" name="confirm" type="radio" value="yes" />';
  $confirm_form .= '<label for="admin">Yes</label>';
	$confirm_form .= '<input id="user" name="confirm" type="radio" value="no" />';
	$confirm_form .= '<label for="user">No</label>';
	$confirm_form .= '</div>';
  $confirm_form .= '<input type="submit" name="confirm" value="Confirm"/>';
	$confirm_form .= '</form>';
	return $confirm_form;
}

/**
 *
 */
function confirm_submit() {
  if(($_POST['confirm']) == 'yes') {
    return 'yes';
  }
  else {
    return 'no';
  }
}

/**
 * Function for check whether the user already exists or not
 * 
 * @param string $username.
 */
function user_exists ($username) {
  $db = db_get_connection();
  $stmt = $db->prepare("SELECT id FROM users WHERE name=:name");
  $stmt->execute(array(':name'=>$username));
  $row = $stmt->fetchAll(PDO::FETCH_ASSOC);
  $row_count = $stmt->rowCount();
  if($row_count == 0) {
    return false;
  }
  return true;
}

/**
 * function to authenticate.
 *
 * @param string $username
 * @param string $password
 */
function authenticate($username,$password) {
  $db = db_get_connection();
  $_SESSION['username'] = $username;
  $stmt = $db->prepare('SELECT id,role_id FROM users '
    . ' WHERE name=:name '
    . ' AND password=:password'
  );
  $stmt->execute(array(':name'=>$username,':password'=>SHA1($password)));
  $row = $stmt->fetch(PDO::FETCH_ASSOC);
  $row_count = $stmt->rowCount();
  if($row_count > 0) {
    $_SESSION['userid'] = $row['id'];
    $stmt1 = $db->prepare('SELECT role_name FROM roles WHERE id =:id' );
    $stmt1->execute(array(':id'=>$row['role_id']));
    $row1 = $stmt1->fetch(PDO::FETCH_ASSOC);
    $_SESSION['role'] = $row1['role_name'];
    return true;
  }
  $_SESSION['userid'] = 0;
  return false;
}

/**
 * Function for changing the password.
 *
 * @param string $password
 */
function change_password($password) {
  $db = db_get_connection();
  $stmt = $db->prepare("UPDATE users "
    . "SET password =:password "
    . "WHERE name =:name"
  );
  $stmt->execute(array(':password' =>SHA1($password),
    ':name'=> $_SESSION['username']
  ));
  return $stmt->rowCount()>0;
}

/**
 * Function for adding the user.
 *
 * @param string $username
 * @param string $role_id
 * @param string $password
 */
function add_user($username,$role_id,$password,$confirm_pass) {
 $db = db_get_connection();
 if ($password == $confirm_pass) {
   $stmt = $db->prepare("INSERT INTO " 
     . " users(name,role_id,password)"
     . " VALUES(:name,:role_id,:password)"
   );
   $stmt->execute(array(':name' => $username,
     ':role_id' => $role_id, 
     ':password' =>SHA1($password)
   ));
   if($stmt->rowCount() > 0) {
     return true;
   } 
 }
 else {
   $msg = "Password mismatches";
   set_form_error($form,null,$msg);
   return false;
 }
}

/**
 * Function for editing the user.
 *
 * @param string $role_id
 */
function edit_user($role,$username) {
 $db = db_get_connection();
 $stmt = $db->prepare("UPDATE users SET role_id=:role_id "
   . "WHERE name =:name " 
   . "AND status =:status "
 );
 $stmt->execute(array(':role_id' => $role, 
   ':name' => $username,
   ':status' => 1 
 ));
 return $stmt->rowCount()>0 ;
}

/**
 * Function for Listing the user.
 */
function list_users() {
  $db = db_get_connection();
  $stmt = $db->query("SELECT users.name,roles.role_name "
    . " FROM users "
    . " JOIN roles "
    . " ON status = 1 "
    . " AND users.role_id=roles.id "
  );
  $output = array();
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $output[] = array('name' => $row['name'] ,
	    'role' => $row['role_name']
	  );
  }
  return $output; 
}

/**
 * Function for Listing the user.
 */
function disabled_users_list() {
  $db = db_get_connection();
  $stmt = $db->query("SELECT users.name,roles.role_name "
    . " FROM users "
    . " JOIN roles "
    . " ON status = 0 "
    . " AND users.role_id=roles.id "
  );
  $output = array();
  while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
    $output[] = array('name' => $row['name'] ,
	    'role' => $row['role_name']
	  );
  }
  return $output; 
}

/**
 * Function for Disabling the user.
 */
function disable_users($names) {
 $db = db_get_connection();
 $stmt = $db->prepare("UPDATE users "
   . " SET status = :status "
   . " WHERE name =:name"
 );
 foreach ($names as $name) {
   $stmt->execute(array(':status' => 0, ':name' => $name));
 }
 return $stmt->rowCount()>0 ; 
}

/**
 * Function for Enabling the user.
 */
function enable_users($names) {
 $db = db_get_connection();
 $stmt = $db->prepare("UPDATE users "
   . " SET status = :status "
   . " WHERE name =:name"
 );
 foreach ($names as $name) {
   $stmt->execute(array(':status' => 1, ':name' => $name));
 }
 return $stmt->rowCount()>0 ; 
}

/**
 * To get the role of the user
 *
 */
function get_role($name) {
  $db = db_get_connection();
  $stmt = $db->prepare("SELECT name,role_id FROM users WHERE name=:name");
  $stmt->execute(array(':name'=>$name));
  $row = $stmt->fetch(PDO::FETCH_ASSOC);
  return $row['role_id'];   
}

/**
 * Function for logout
 *
 * It just set the session value into zero. 
 */
function logout() {
  if($user = set_user()) {
    delete_user($user); 
  }
  setcookie('session',NULL);
  session_destroy();
  //$_SESSION['userid'] = 0;
  unset ($_SESSION['bill']);
  return true;
}

/**
 * Function for delete the user.
 */
function delete_user($user) {
$db = db_get_connection() ;
  $stmt = $db->prepare("DELETE FROM session WHERE(session_id = :sess_id AND user_id = :user_id)"
  );
  $stmt->execute(array(
    ':sess_id' => $user['sid'],
    ':user_id' => $user['id']
  ));
  if ($stmt->rowCount() > 0) {
    return true;
  }
  return false;
}
