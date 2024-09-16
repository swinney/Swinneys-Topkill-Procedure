<?
// $Id$

require_once("./global.php");
include(INCDIR ."/top.inc");

if ($error_msg) {
  echo <<<EOT
<p>
<b><font color="red">$error_msg</font></b>
</p>

EOT;
  session_unregister("error_msg");
}

// have an incrementing number in the filename
if (! isset($index)) {
  $index = 0;
}

if ($index <= 0) {
  echo <<<EOT
<P>
If you have any images to upload for this article, select them here,
otherwise click <a href="index.php">continue</a>.
</P>

EOT;
} else if ($aindex < 5) {
  echo <<<EOT
<P>
You have uploaded <b>$index</b> images for this article<br>
If you have any <b>more</b> images to upload for this article,
select them here.
</P>
<P>
Otherwise click <B>exit</B>.
</P>

EOT;
}

if ($index < 5) {
  echo <<<EOT
<br>

<form action="process_image.php" method="POST" enctype="multipart/form-data">
<P>file: <input type="file" name="userfile"></P>
<input type="hidden" name="article_id" value="$article_id">
<input type="hidden" name="index" value="$index"><br>
<input type="submit" name="submit_image" value="submit">
<input type="submit" name="exit" value="exit">
</form>
</FONT>

EOT;
} else {
  echo <<<EOT
<p>
You may not upload any more images for this article.<br>
<a href="./index.php">Continue</a>
</p>

EOT;
}

include(INCDIR ."/footer.inc");
?>
