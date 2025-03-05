public class Main {
	public static void main(String argv[]) {
		Numar nr1 = new Numar(5);
		Numar nr2 = new Numar(6);
		Numar nr3 = new Numar(0);
		Suma  sum = new Suma(nr1,nr2);
		Inmultire prod = new Inmultire(sum,nr3);
	    prod.accept(new Parcurgere());
	}
}