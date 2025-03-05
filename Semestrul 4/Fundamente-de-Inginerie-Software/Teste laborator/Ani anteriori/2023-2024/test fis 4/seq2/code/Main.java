public class Main {
	public static void main(String argv[]) {
		Numar nr1 = new Numar(5);
		Numar nr2 = new Numar(6);
		Numar nr3 = new Numar(0);
		Inmultire prod = new Inmultire(nr1,nr2);
		Suma sum = new Suma(prod,nr3);
		//*
	    	prod.accept(new Afisare());		
	}
}