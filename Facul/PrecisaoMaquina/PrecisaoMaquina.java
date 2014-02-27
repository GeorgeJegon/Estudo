public class PresicaoMaquina {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println(precisaoMaquina());
	}//END FUNCTION
	
	
	public static float precisaoMaquina(){
		return precisaoMaquina(1);
	}//END FUNCTION
	
	public static float precisaoMaquina(int r){
	    float a = 1, s = (a + r);
	    while(s>r){
	    	a /= 2;
	    	s = r + a;
	    }//END WHILE
		return 2*a;
	}//END FUNCTION
	
	public static float precisaoMaquina(int[] r){
	   return 0.0f;
	}//END FUNCTION
	
}//END CLASS
