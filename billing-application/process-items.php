<?php 
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/stock-management-lib.inc';
$previous = curPageName();
if (authorize('process_items')) {
  $codes = array();
  if(isset($_POST['codes'])) { 
    foreach( $_POST['codes'] as $index => $code) {
      $codes[] = "$index";
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
				<p> Are you sure you want to do this operation for item codes <?php foreach ($codes as $code) : echo $code." & " ; endforeach; ?> ? </p> </div>
				<?php if($_POST['submit']=='Enable') { ?>
				<div>
					<p> <a href="confirmation.php?q=<?php echo $codes ?>&stock_confirm=yes" >YES</a> </p>
					<p> <a href="confirmation.php?q=<?php echo $codes ?>&stock_confirm=no" >NO</a> </p>
				</div>
				<?php  } ?>
				<?php if($_POST['submit']=='Disable') { ?>
				<div>
					<p> <a href="confirmation.php?q=<?php echo $codes ?>&stock_confirm=y" >YES</a> </p> 
					<p> <a href="confirmation.php?q=<?php echo $codes ?>&stock_confirm=n" >NO</a> </p>
				</div>
				<?php } ?>
				<?php if($_POST['submit']=='Reset') { ?>
				<div>
					<p> <a href="confirmation.php?q=<?php echo $codes ?>&stock_confirm=yup" >YES</a> </p> 
					<p> <a href="confirmation.php?q=<?php echo $codes ?>&stock_confirm=nope" >NO</a> </p>
				</div>
				<?php  } ?>
		</div>
		<?php include 'footer.php'; ?>
	</body>
</html>
