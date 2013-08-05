<form method='POST' action='#'>
<?php 
  if(isset($this->error)) :
    echo $this->error;
  endif; ?>
<input type="hidden" name="id" value="<?php echo $this->field['id']; ?>">
<?php foreach ($this->fields as $key => $field) :
  switch($field['type']) {
    case 'text': ?>
      <div>
        <label> <?php echo $field['label']; ?></label> 
        <input type='text' name="<?php echo $key; ?>" <?php if(!empty($field['value'])) {?>value="<?php echo $field['value']; ?>"<?php }; ?>>
        <?php if(isset($field['msg'])):
        echo $field['msg'];
        endif; ?>
      </div>  
      <?php break; ?>
<?php case 'password': ?>
      <div>
        <label> <?php echo $field['label']; ?></label> 
        <input type='password' name="<?php echo $key; ?>" value="<?php echo $field['value'];?>">
        <?php if(isset($field['msg'])):
        echo $field['msg'];
        endif; ?>
      </div>  
      <?php break;?>
<?php case 'checkbox': ?>
      <div>
        <label> <?php echo $field['label']; ?></label> 
        <input type='checkbox' name="<?php echo $key; ?>"<?php if(!empty($field['value'])) {?>value="<?php echo $field['value']; ?>"<?php }; ?> <?php if($field['value']){?>checked="<?php echo $field['value']; ?>"<?php }; ?>">
        <?php if(isset($field['msg'])):
        echo $field['msg'];
        endif; ?>
      </div>  
      <?php break;?>      
<?php case 'radio': ?>
      <div>
      <?php foreach($field['options'] as $key1 => $option) :?> 
        <input type='radio' name="<?php echo $key; ?>" value = "<?php echo $key1; ?>" checked='checked'>
        <label> <?php echo $option; ?></label>
      <?php endforeach ; ?>  
      <?php if(isset($field['msg'])):
        echo $field['msg'];
        endif; ?> 
      </div>  
      <?php break;?>
<?php case 'submit': ?>
      <div> 
        <input type='submit' name="<?php echo $key; ?>" value="<?php echo $field['value'];?>">
      </div>  
      <?php break;
      
 }?> 
         
<?php endforeach ; ?>  
</form>
                               
