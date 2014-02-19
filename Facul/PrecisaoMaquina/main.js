function precisaoMaquina(r){
	r = r || 1;
	var a = 1 , s = r + a;
	while(s>r){
		a /= 2;
		s = r + a;
	}//END WHILE
	return 2*a;
}//END FUNCTION

function fat(n){
	if(n<=0){
		return 1;
	}//END IF
	return n * fat(n-1);
}//END FUNCTION