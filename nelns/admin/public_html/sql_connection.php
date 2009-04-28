<?php
	include('../config.php');

	// connect to database
	function connectToDatabase($dbhost, $dbname, $dblogin, $dbpasswd)
	{
		if (!mysql_connect($dbhost, $dblogin, $dbpasswd))
			return "Unable to connect to MySQL server (host='$dbhost' login='$dblogin')";
		if (!mysql_select_db ($dbname))
			return "Unable to select MySQL database '$dbname'";
		return FALSE;
	}
	
	// default connection to database
	function defaultConnectToDatabase()
	{
		global	$dbhost, $dbname, $dblogin, $dbpassword;
		return connectToDatabase($dbhost, $dbname, $dblogin, $dbpassword);
	}

	function sqlquery($query)
	{
		// here log queries
		global	$sqlQueries;
		$res = mysql_query($query);
		$sqlQueries[] = $query.(($res)?"":" ***FAILED***: ".mysql_error());
		return $res;
	}

	function sqlfetch(&$result)
	{
		return mysql_fetch_array($result);
	}

	function sqlnumrows(&$result)
	{
		return mysql_num_rows($result);
	}

	function sqlchrows(&$result)
	{
		return mysql_affected_rows($result);
	}
	
	function displayQueries()
	{
		global	$sqlQueries;
		if (isset($sqlQueries))
		{
			echo "<br><br><hr><ul>";
			foreach ($sqlQueries as $query)
				echo "<li>$query</li>\n";
			echo "</ul>";
/*
			echo "<br><br><p align=right><textarea rows=15 cols=100 readOnly>";
			foreach ($sqlQueries as $query)
				echo "$query\n---\n";
			echo "</textarea>\n";
*/
		}
	}
	
	if ($queries)
	{
		echo "<textarea rows=15 cols=100 readOnly>";
		echo "$queries";
		echo "</textarea>\n";
		die();
	}

?>