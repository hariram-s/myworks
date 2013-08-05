<form method='POST' action='#'>
<?php 
  if(isset($this->error)) :
    echo $this->error;
  endif; ?>
	<input type="hidden" name="id" value="<?php echo $this->field['id']; ?>">
  <table>
    <thead>
      <th>Item-code</th>
      <th>Item-name</th>
      <th>Quantity</th>
      <th>Selling Price</th>
      <th>Total</th>
    </thead>
    <tbody>
      <?php 
  for ($row_count = 1; $row_count < $this->field['rowcount'] ; $row_count++) { ?>
      <tr id="row-<?php echo $this->field['rowcount']; ?>">
        <td><input type="<?php echo $this->fields['itemcode'.$row_count]['type']; ?>" name= "<?php echo $this->fields['itemcode'.$row_count]['name']; ?>" <?php if(!empty($this->fields['itemcode'.$row_count]['value'])) {?>value= "<?php echo $this->fields['itemcode'.$row_count]['value']; ?>"<?php }; ?> ></td>
        <td><?php if(!empty($this->fields['name'.$row_count]['value'])) {?><?php echo $this->fields['name'.$row_count]['value']; ?><?php }; ?></td>
        <td><input type="<?php echo $this->fields['quantity'.$row_count]['type']; ?>" name= "<?php echo $this->fields['quantity'.$row_count]['name']; ?>" <?php if(!empty($this->fields['quantity'.$row_count]['value'])) {?>value= "<?php echo $this->fields['quantity'.$row_count]['value']; ?>"<?php }; ?> ></td>
        <td><?php if(!empty($this->fields['selling_price'.$row_count]['value'])) {?><?php echo $this->fields['selling_price'.$row_count]['value']; ?><?php }; ?> </td>
        <td><?php if(!empty($this->fields['total'.$row_count]['value'])) {?><?php echo $this->fields['total'.$row_count]['value']; ?><?php }; ?> </td>
      </tr>
  <?php 
  }
  ?>
    </tbody>
  </table>
  <div>
     <p> The Grand Total is <?php if(!empty($this->fields['grand_total']['value'])) {?><?php echo $this->fields['grand_total']['value']; ?><?php }; ?>/- </p>
  </div>
  <div> 
    <input type='submit' name="submit" value="<?php echo $this->fields['submit']['value']; ?>">
  </div>
</form>

