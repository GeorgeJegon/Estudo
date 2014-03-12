function precisaoMaquina(r){
	r = r || 1;
	var a = 1 , s = r + a;
	while(s>r){
		a /= 2;
		s = r + a;
	}//END WHILE
	return 2*a;
}//END FUNCTION

function precisaoMaquinaArray(a){
	if(isArray(a)){
		a.forEach(function(o){
			console.log(precisaoMaquina(o));
		});
	}//END IF

}//END FUNCTION

function isArray(a){
	return (a instanceof Array);
}//END FUNCTION

function fat(n){
	if(n<=0){
		return 1;
	}//END IF
	return n * fat(n-1);
}//END FUNCTION

function taylorEulerExp(v,n){
	if(n<=1){
		return 1;
	}//END IF
	return taylorEulerExp(v,n-1)+(Math.pow(v,n-1)/fat(n-1));
}//END FUNCTION

//precisaoMaquinaArray([10,17,100,184,1000,1575,10000,17893]);
taylorEulerExp(5,28);