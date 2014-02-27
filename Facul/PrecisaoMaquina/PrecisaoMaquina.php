<?php 
function precisaoMaquina($r=1){
	$a = 1;
	$s = ($r + $a);
	while($s>$r){
		$a /= 2;
		$s = $r + $a;
		//var_dump($a);
	}//END WHILE
	return 2*$a;
}//END FUNCTION

echo precisaoMaquina();
?>
