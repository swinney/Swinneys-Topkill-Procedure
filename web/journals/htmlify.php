<?


$txt=<<<EOT
hi hi hi

bla bla

blalbalbllabalb

hi hi

dogs
EOT;

$html=preg_replace("/^\r$/","<BR><BR>",$txt);

echo "Becomes:\n";
echo $html;

?>