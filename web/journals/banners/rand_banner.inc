
<?

$banner = dice(1,20);

if ($banner%10 == 0 ) {

include "banners/amazon_oscon.inc";

} 

else if ($banner%8 == 0) {

include "banners/darwin.inc";

}  else {

include "banners/ghetto.inc";

}

?>