<?php
	if (!isset($GLOBALS["NEL_TOOL_CONFIG_PHP"]))
	{
		$GLOBALS["dbhost"] = "localhost";
		$GLOBALS["dbname"] = "nel";
		$GLOBALS["dblogin"] = "";
		$GLOBALS["dbpassword"] = "";

		$GLOBALS["allowrootdebug"] = true;

		$GLOBALS["userlogpath"] = "/var/log/nelns";				// without final /

		$GLOBALS["rrdrootpath"] = "/var/log/nelns/rrds";				// without final /
		$GLOBALS["gifoutputpath"] = "graph";				// absolute path where to store gif files, without final /
		$GLOBALS["gifhttplocation"] = "graph";			// relative path to the http root, where to find gif files, without final /
		$GLOBALS["gifpersistence"] = 180;			// in number of seconds

		$GLOBALS["NEL_TOOL_CONFIG_PHP"] = true;

		$GLOBALS["ASHost"] = "localhost";
		$GLOBALS["ASPort"] = "49995";

		$GLOBALS["enablelock"] = true;

		$GLOBALS["allowDownload"] = true;
		$GLOBALS["allowUpload"] = true;
	}
?>
