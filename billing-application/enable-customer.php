<?php 
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/bill-management-lib.inc';
$previous = curPageName();
if (authorize('disable_customer')) {
  $ids = array();
  if(isset($_POST['ids'])) { 
    foreach( $_POST['ids'] as $index => $id) {
      $ids[] = "$index";
    }
  }
  if($_POST['submit']=='Disable') {
  	disable_customer($ids);
   }
  if($_POST['submit']=='Enable') {
    enable_customer($ids);
    redirect('list-customers.php');
  }
}
else {
  redirect ("login.php?destination=$previous");
}
?><!DOCTYPE html>
<html>
	<head>
		<meta http-equiv="content-type" content="text/html; charset=utf-8" />
		<title> Address book</title>
	</head>
	<body>

		<div id="content">
			<div>
				<p> Are you sure you want to disable this customer? </p> </div>
				
				<div>
					<p> <a href="confirm-disable.php?q=<?php echo $ids ?>&confirm=y" >YES</a> </p> 
					<p> <a href="confirm-disable.php?q=<?php echo $ids ?>&confirm=n" >NO!</a> </p>
				</div>
		</div>
		<?php include 'footer.php'; ?>
	</body>
</html>   		
