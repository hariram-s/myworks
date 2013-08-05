<?php 
require_once 'bootstrap.php';
require_once 'includes/common.inc';
require_once 'includes/user-management-lib.inc';
$previous = curPageName();
if (authorize('disable_user')) {
  $names = array();
  if(isset($_POST['names'])) { 
    foreach( $_POST['names'] as $index => $name) {
      $names[] = "$index";
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
					<p> <a href="confirmation.php?q=<?php echo $names ?>&user_confirm=y" >Yes</a> </p> 
					<p> <a href="confirmation.php?q=<?php echo $names ?>&user_confirm=n" >No</a> </p>
				</div>
				<?php  } ?>
				<?php if($_POST['submit']=='Enable') { ?>
				<div>
					<p> <a href="confirmation.php?q=<?php echo $names ?>&user_confirm=yes" >Yes</a> </p> 
					<p> <a href="confirmation.php?q=<?php echo $names ?>&user_confirm=no" >No</a> </p>
				</div>
				<?php } ?>
		</div>
		<?php include 'footer.php'; ?>
	</body>
</html>   		
