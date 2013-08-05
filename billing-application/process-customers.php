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
				<p> Are you sure? </p> </div>
				<?php if($_POST['submit']=='Disable') { ?>
				<div>
					<p> <a href="confirmation.php?q=<?php foreach ($ids as $id ) : echo $id; endforeach; ?>&customer_confirm=y" >YES</a> </p> 
					<p> <a href="confirmation.php?q=<?php echo $ids ?>&customer_confirm=n" >NO</a> </p>
				</div>
				<?php  } ?>
				<?php if($_POST['submit']=='Enable') { ?>
				<div>
					<p> <a href="confirmation.php?q=<?php echo $ids ?>&customer_confirm=yes" >YES</a> </p> 
					<p> <a href="confirmation.php?q=<?php echo $ids ?>&customer_confirm=no" >NO</a> </p>
				</div>
				<?php  } ?>
		</div>
		<?php include 'footer.php'; ?>
	</body>
</html>   		
