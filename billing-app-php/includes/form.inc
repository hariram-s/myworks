<?php
/**
 * @file
 * Defines the form API functions.
 * 
 * Using functions defined in this file any simple PHP application can easily
 * automate creation, validation and submission of simple forms.
 */

/**
 * Function to build the form
 * 
 * @param array $form.
 * @param array $_POST
 */
function build_form($form,$post) {
  $form['state']  = 1;
  foreach($form['form'] as $name => $field) {
    if ($field['type'] == 'checkbox') {
      $form['form'][$name]['checked'] = isset($post[$name]) ? true : false;
    }
    elseif(isset($post[$name])) {
      $form['form'][$name]['value'] = $post[$name];
    }    
  }
  return $form;
}  

function form_validate(&$form) {
  $error = 0;
  foreach($form['form'] as $name => $field) {
    if (isset($field['required']) && $field['required'] == 1 && empty($field['value'])) {
      $error = 1;
      $error_msg = $name ." ". "cannot be left empty";
      set_form_error($form,$name,$error_msg);
    }
  }
  if ($error == 0){
    return true;
  } 
  else {
    return false;
  }       
}

/**
 *
 */
function render_form(&$form_id, $param = null) {
  if ($_SERVER['REQUEST_METHOD'] == 'GET') {
    $form = preprocess_form($form_id, $param);
  }
  elseif ($_SERVER['REQUEST_METHOD'] == 'POST') {
    if ($form_id == $_POST['id']) {
      $form = process_form($form_id, $param);
    }
    else {
      $form = preprocess_form($form_id, $param);
    }
  } 
  $print_form = new Savant3();
  $print_form->fields = $form['form'];
  $print_form->field = $form;
  if (isset($form['error'])) {
    $print_form->error = $form['error'];
  }
  if (isset($form['template'])) {
    return($print_form->fetch($form['template'])); 
  }
  return($print_form->fetch('templates/form.tpl.php'));
}

function set_form_error(&$form,$name,$error_msg) {
  foreach($form['form'] as $key => $fields) {
    if ($key == $name) {
      $form['form'][$name]['error'] = 1;
      $form['form'][$key]['msg'] = $error_msg;
    }
  }  
  if ($name == null) {
    $form['error'] = $error_msg;
  }   
}

function get_form($form_id, $param) {
  if (function_exists($form_id)) {
    if (!isset($param)) {
      $form = call_user_func($form_id);
    }
    else {
      $form = call_user_func($form_id, $param);
    }
    return $form;
  }
  return false;
}    

function preprocess_form($form_id, $param) {
  $form  = get_form($form_id, $param);
  foreach($form['form'] as $name => $field) {
    $form['form'][$name]['value'] = (isset($form['form'][$name]['default'])?$form['form'][$name]['default']:NULL);
  }
  return $form;
}

function process_form($form_id, $param) {
  $form  = get_form($form_id, $param);
  $form1 = build_form($form,$_POST);
  $default_validation = form_validate($form1);
  $custom_validation = true;
  if (function_exists($form_id. '_validate')) {
    $custom_validation = call_user_func($form_id. '_validate', &$form1);
  }
  if ($default_validation && $custom_validation) {
    if (function_exists($form_id.'_submit')) {
      $submit = call_user_func($form_id. '_submit', &$form1);
      if ($submit) {
        $form1 = preprocess_form($form_id, $param);
      }
    } 
  }  
  return $form1;  
}   

