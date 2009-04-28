<?php

	$publicAccess = true;
	include('authenticate.php');


	if (isset($chCookieState))
	{
		sqlquery("UPDATE user SET useCookie='$chCookieState' WHERE uid='$uid'");
		$useCookie = $chCookieState;
	}

	htmlProlog($_SERVER['PHP_SELF'], "Preferences");
	
	echo "<br><b>Preferences edit</b><br>\n";

	echo "<table><tr><td>\n";

	echo "<br><table><tr><td>Use login cookie</td><form method=post action='".$_SERVER['PHP_SELF']."'><td>\n";
	echo "<select name='chCookieState' onChange='submit()'>\n";
	echo "<option value='yes'".($useCookie == 'yes' ? " selected" : "").">Yes\n";
	echo "<option value='no'".($useCookie != 'yes' ? " selected" : "").">No\n";
	echo "</td></form></tr></table><br>\n";

	echo "</td></tr><tr><td><hr></td></tr><tr><td>\n";

	echo "<table><tr><td colspan=2>Change password</td></tr>\n";
	echo "<form method=post action='".$_SERVER['PHP_SELF']."'><input type=hidden name='command' value='chPassword'><input type=hidden name='admlogin' value='$admlogin'><input type=hidden name='admpassword' value='$admpassword'>\n";
	echo "<tr><td>Enter previous password</td><td><input type=password name='chOldPass' size=16 maxlength=16></td></tr>\n";
	echo "<tr><td>Enter new password</td><td><input type=password name='chNewPass' size=16 maxlength=16></td></tr>\n";
	echo "<tr><td>Reenter new password</td><td><input type=password name='chConfirmNewPass' size=16 maxlength=16></td></tr>\n";
	echo "<tr><td colspan=2 align=center><input type=submit type=password name='chPassword' value='Change password'></td></tr>\n";
	echo "</form></table><br>\n";

	echo "</td></tr></table>\n";
	
	htmlEpilog();
?>
