

<h1>Trying to figure out how to display the articles.</h1>

<?


$result_set = mysql( "lifestyle", "SELECT * FROM articles_info" );


// multiple rows 
while ( $individual_row = mysql_fetch_object( $result_set ) ) {

// one row
$individual_row = mysql_fetch_object( $result_set ); 

    echo "$individual_row->article_id<br>\n";
    echo "$individual_row->username<br>\n";
    echo "$individual_row->date<br>\n";
    echo "$individual_row->time<br>\n";
    echo "$individual_row->status<br>\n";
    echo "$individual_row->blurb<br>\n";
    echo "$individual_row->category<hr>\n";

}

?>

