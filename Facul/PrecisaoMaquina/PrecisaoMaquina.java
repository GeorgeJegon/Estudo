public class PrecisaoMaquina {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int ArrayRefs[] = {1,10,17,100,184,1000,1575,10000,17893};
		precisaoMaquinaArray(ArrayRefs);
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
	
	public static double precisaoMaquinaDouble(){
		return precisaoMaquinaDouble(1);
	}//END FUNCTION
	
	public static double precisaoMaquinaDouble(int r){
	    double a = 1, s = (a + r);
	    while(s>r){
	    	a /= 2;
	    	s = r + a;
	    }//END WHILE
		return 2*a;
	}//END FUNCTION
	
	public static void precisaoMaquinaArray(int[] r){
		for(int x: r){
			System.out.println("Valor de referência: "+x);
			System.out.println("Precisão Simples da Máquina: "+precisaoMaquina(x));
			System.out.println("Precisão Dupla da Máquina: "+precisaoMaquinaDouble(x));
			System.out.println("---------------------------------------------");
		}//END FOR
	}//END FUNCTION
	
}//END CLASS
