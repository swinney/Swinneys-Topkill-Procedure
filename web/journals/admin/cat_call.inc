<?
#$Id$

###################################
# rollcall.inc - who is out there?
# this is the most major shit script
# in all of swinney.org.  UNTIL TODAY
# i just figured out how to generate the
# entire thing in one select statement.
# worship me.  suck my dick.  it does not matter
# i do this all for the bitches.  word up 
# in two thousand.  -OMS 
# Thu Jul 12, 2001 10:13 AM
#
# mmmm...the bitches. - J. 020010921

?>

<!-- BEGIN PHP Dynamically Required File: rollcall.inc -->


<table cellpadding="0" cellspacing="0" border="0" width="100%">
<tr>
<td align="center">

<img src="img/no.gif" alt="" width="1" height="10" border="0"><br>

<table cellpadding="0" cellspacing="0" border="0">
<tr>
<td width="150" valign="top" align="right" nowrap>
<p>
<a href="roll_call_all.phtml"><img src="<? echo URLBASE ?>/journals/img/rollcall.gif" alt="Roll Call" width="65" height="13" border="0"></a><br>

<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>

recent writers:<br>

<!-- WHAT IS GOING ON IN THE WORLD...  WHO?  -->
<?
$query="SELECT category FROM articles_info WHERE article_id=$article_id";
$res=mysql_query($query);
$that_cat=mysql_result($res,0,0);
$res = mysql_query("SELECT * FROM categories ORDER BY name ASC");

# for the next loop, index
$i=0;

while ($d=mysql_fetch_object($res)) {
  $this_cat=$d->level1;
  $meh = $that_cat & $this_cat;
  if ($this_cat==$meh) {
    echo "$d->name<input type='checkbox' name='cat[$i]' value='$this_cat' checked><br>\n";
  } else {
    echo "$d->name<input type='checkbox' name='cat[$i]' value='$this_cat'><br>\n";
  }
    $i++;
} # child loop

?>
<img src="<? echo URLBASE ?>/journals/img/no.gif" alt="" width="1" height="7" border="0"><br>
</p></td>

<!-- END PHP Dynamically Required File: rollcall.inc -->












