var baseConvert = (function(){
	var arrayValues = [0,1,2,3,4,5,6,7,8,9,"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"];
	
	function fromDec(n,b){
		var baseArray = [], m = 0;
		if(b<=arrayValues.length){
			while(n>=b){
				m = (n%b);
				n = (n-m)/b;
				baseArray.push(arrayValues[m]);
			}//END WHILE
			baseArray.push(arrayValues[n]);
			return baseArray.reverse().join('');
		}//END IF
		return false;
	}//END FUNCTION
	
	function toDec(n,b){
		n = (!isNaN(n))?String(n):n;
		n = n.split('').reverse();
		var s = 0;
		for(var i=0,j=n.length;i<j;i++){
			var c = Number(n[i]);
			if(c>0){
				s += (c * Math.pow(b,i));
			}//END IF
		}//END FOR
		return s;
	}//END FUNCTION

	return {
		fromDec: fromDec,
		toDec: toDec
	};
}());