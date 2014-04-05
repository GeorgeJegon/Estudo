var BasuEncription = (function(){
	function encrypt(m1,m2,p,q){
		p = p || 7;
		q = q || 5;
		var binaryM1 = getBinaryMessage(m1),
			binaryM2 = getBinaryMessage(m2),
			binaryMD = null,
			N = p * q,
			r = getRandomArrayController(),
			r1 = null,
			r2 = null,
			c = null
			maxLenght = Math.max(binaryM1.length,binaryM2.length);

			binaryM1 = leftPadding(maxLenght,"0",binaryM1);
			binaryM2 = leftPadding(maxLenght,"0",binaryM2);

			binaryMD = binaryMessageXOR(binaryM1,binaryM2);

			maxLenght = Math.max(r.length,binaryMD.length);
			r = leftPadding(maxLenght,"0",r);
			binaryMD = leftPadding(maxLenght,"0",binaryMD);

			r1 = binaryMessageOR(r,binaryMD);
			r2 = binaryMessageAND(r1,binaryStringNegation(binaryMD));

			maxLenght = Math.max(binaryM1.length,r1.length);
			binaryM1 = leftPadding(maxLenght,"0",binaryM1);
			r1 = leftPadding(maxLenght,"0",r1);

			c = binaryMessageXOR(binaryM1,r1);

			return {
				c: c,
				A: getRandomMatrix(N,r1),
				privateKey: N
			};

	}//END FUNCTION

	function decrypt(n,c,A){
		return binaryMessageTranslate(binaryMessageXOR(c,getRandomArrayControllerByMatrix(n,A)));
	}//END FUNCTION

	function decryptFake(n,c,A,m2){
		var r1 = getRandomArrayControllerByMatrix(n,A),
				m1 = binaryMessageXOR(c,r1);
		return binaryMessageTranslate(binaryMessageXOR(binaryMessageAND(binaryStringNegation(binaryMessageXOR(m1,leftPadding(m1.length,"0",getBinaryMessage(m2)))),r1),c));
		/*
		return binaryMessageTranslate(
			binaryMessageXOR(
				binaryMessageAND(
					binaryStringNegation(
						binaryMessageXOR(
							m1,leftPadding(
								m1.length,"0",getBinaryMessage(m2)
							)
						)
					),r1
				),c
			)
		);
		*/
	}//END FUNCTION

	function getRandomArrayController(){
		var l = 10, r = [];
		for(var i=0,j=(getRandomNumber(l)+l);i<j;i++){
			r.push(getRandomNumber(2));
		}//END FOR
		return r.join('');
	}//END FUNCTION

	function getRandomArrayControllerByMatrix(privateKey,baseMatrix){
		var r = [];
		loop1:
		for(var i=0,j=baseMatrix.length;i<j;i++){
			r.push(1);
			loop2:
			for(var x=0,y=baseMatrix[i].length;x<y;x++){
				if(!isQuadraticResidue(baseMatrix[i][x],privateKey)){
					r[i] = 0;
					break loop2;
				}//END IF
			}//END FOR
		}//END FOR
		return r.join('');
	}//END FUNCTION

	function getRandomMatrix(privateKey,r){
		var order = r.length, 
				a = createMatrixMN(order,4);
		for(var i=0;i<order;i++){
			if(r[i]==1){
				a[i] = createQuadraticResiduesRow(privateKey,4);
			}else{
				a[i] = createJacobiSymbolRow(privateKey,4);
			}//END IF
		}//END FOR
		return a;
	}//END FUNCTION

	function getBinaryMessage(m){
		var chars = string2ArrayChar(m),
			binaryArray = [];
		for(var i=0,j=chars.length;i<j;i++){
			binaryArray.push(charToBinary(chars[i]));
		}//END FOR
		return binaryArray.join('');
	}//END FUNCTION

	function createQuadraticResiduesRow(n,l){
		var r = [], a = 2;
		for(var i=0;i<l;i++){
			r.push(Math.pow(getRandomNumber(n-a)+a,2)%n);
		}//END FOR
		return r;
	}//END FUNCTION

	function createJacobiSymbolRow(n,l){
		var r = [],
			oddNumbersBase = getOddNumbersArrays(n),
			baseLen = oddNumbersBase.length;
		for(var i=0;i<l;i++){
			do{
				var v = oddNumbersBase[getRandomNumber(baseLen-1)],
					mdc = getMDC(v,n);
			}while(mdc!=1 || isQuadraticResidue(v,n));
			r.push(v);
		}//END FOR
		return r;
	}//END FUNCTION

	/*Helpers*/
	function isQuadraticResidue(x,n){
		for(var i=1,j=Math.round(n/2);i<j;i++){
			if((Math.pow(i,2)%n)==x){
				return true;
			}//END IF
		}//END FOR
		return false;
	}//END FUNCTION

	function isOdd(n){
		return !isEven(n);
	}//END FUNCTION

	function isEven(n){
		return !(n%2);
	}//END FUNCTION

	function isPrime(n){
		var r = Math.round(Math.sqrt(n));
		for(var i=2,j=1;i<=r;i+=j){
			if(!(n%i)){
				return false;
			}//END IF
			j = (isEven(i))?1:2;
		}//END FOR
		return true;
	}//END FUNCTION

	function getPrimeFactors(n){
		var pf = [1];
		if(!isPrime(n)){
			var r = Math.round(Math.sqrt(n));
			for(var i=2,j=1;i<=r;i+=j){
				if(isPrime(i) && !(n%i)){
					while(!(n%i)){
						pf.push(i);
						n /= i;
					}//END WHILE
				}//END IF
				j = (isEven(i))?1:2;
			}//END FOR
			if(isPrime(n) && n>1){
				pf.push(n);
			}//END IF
		}else{
			pf.push(n);
		}//END IF
		return pf;
	}//END FUNCTION

	function getMDC(a,b){
		var primesA = getPrimeFactors(a),
			primesB = getPrimeFactors(b);
			dc = getArrayIntersects(primesA,primesB);
			r = 1;
			for(var i=0,j=dc.length;i<j;i++){
				r *= dc[i];
			}//END FOR
			return r;
	}//END FUNCTION

	function getArrayIntersects(a,b){
		var intersectArray = [];
		while(a.length>0 && b.length>0){
			if(a[0] > b[0]){
				b.shift();
			}else if(a[0] < b[0]){
				a.shift();
			}else{	
				intersectArray.push(a.shift());
				b.shift();
			}//END IF
		}//END WHILE
		return intersectArray;
	}//END FUNCTION

	function getRandomNumber(n){
		n = n || 1;
		return Math.floor(Math.random()*n);
	}//END FUNCTION

	function getOddNumbersArrays(l){
		var r = [];
		for(var i=1;i<=l;i+=2){
			r.push(i);
		}//END FOR
		return r;
	}//END FUNCTION

	function createMatrixMN(m,n){
		n = n || m;
		var a = new Array(m);
		for(var i=0,j=a.length;i<j;i++){
			a[i] = new Array(n);
		}//END FOR
		return a;
	}//END FUNCTION

	function binaryStringNegation(str){
		var binaryNegative = [];
		for(var i=0,j=str.length;i<j;i++){
			binaryNegative.push(str[i] ^ 1);
		}//END FOR
		return binaryNegative.join('');
	}//END FUNCTION

	function binaryMessageTranslate(msg){
		var translateMsg = [],
			start = 0,
			end = 0;
		for(var i=0,j=(msg.length/8);i<j;i++){
			start = i*8;
			end = (i+1)*8;
			translateMsg.push(String.fromCharCode(bin2dec(msg.substring(start,end))));
		}//END FOR
		return translateMsg.join('');
	}//END FUNCTION

	function binaryMessageOperate(m1,m2,callback){
		var binaryResult = [],
			start = 0,
			end = 0;
		for(var i=0,j=(m1.length/8);i<j;i++){
			start = i*8;
			end = (i+1)*8;
			binaryResult.push(
				dec2bin(
					callback(bin2dec(m1.substring(start,end)),bin2dec(m2.substring(start,end)))
				)
			);
		}//END FOR
		return binaryResult.join('');
	}//END FUNCTION

	function binaryMessageXOR(a,b){
		return binaryMessageOperate(a,b,function(x,y){
			return x ^ y;
		});
	}//END FUNCTION

	function binaryMessageOR(a,b){
		return binaryMessageOperate(a,b,function(x,y){
			return x | y;
		});
	}//END FUNCTION

	function binaryMessageAND(a,b){
		return binaryMessageOperate(a,b,function(x,y){
			return x & y;
		});
	}//END FUNCTION

	function leftPadding(l,c,str){
		var len = str.length,
			paddingChars = [];
		if(len<l){
			for(var i=0,j=(l-len);i<j;i++){
				paddingChars.push(c);
			}//END FOR
		}//END IF
		paddingChars.push(str);
		return paddingChars.join('');
	}//END FUNCTION

	function setBinaryNotation(v){
		return leftPadding(8,"0",v);
	}//END FUNCTION

	function charToBinary(c){
		var charCode = c.charCodeAt(0);
		return dec2bin(charCode);
	}//END FUNCTION

	function string2ArrayChar(str){
		return str.split('');
	}//END FUNCTION

	function dec2bin(n){
		return setBinaryNotation(baseConvert.fromDec(n,2));
	}//END FUNCTION

	function bin2dec(n){
		return baseConvert.toDec(n,2);
	}//END FUNCTION

	return {
		encrypt: encrypt,
		decrypt: decrypt,
		decryptFake: decryptFake
	};
}());