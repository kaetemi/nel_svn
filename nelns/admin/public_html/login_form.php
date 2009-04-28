<?php

	function LoginForm()
	{
		global $command, $admlogin, $admpassword;

		htmlProlog($_SERVER['PHP_SELF'], "Administration", false);
		
		?>

		<form method="post" action="<?php echo basename($_SERVER['PHP_SELF']); ?>" name=loginform>
		<table frame=void rules=none WIDTH="300">
		<tr>
		<td align="left"> login: </td>
		<td align="left"> <input type="text" name="admlogin" maxlength=16 size=16> </td>
		<tr>
		<td align="left"> password: </td>
		<td align="left"> <input type="password" name="admpassword" maxlength=16 size=16> </td>
		<tr>
		<td align="left">&nbsp; </td>
		<td align="left">&nbsp; </td>
		<tr>
		<td align="left"> &nbsp; </td>
		<td align="left"> <input type=submit value="login" name="cmdlogin"> </td>
		<td align="left"> <input type=hidden name="command" value="login"> </td>
		</table>
		</form>
		<script type="text/javascript">
		<!--
		if (document.loginform)
		{
			document.loginform.login.focus();
		}
		// -->
		</script>
		
		<?php
		
		$admlogin = '';
		$admpassword = '';

		htmlEpilog();
	}  

?>
