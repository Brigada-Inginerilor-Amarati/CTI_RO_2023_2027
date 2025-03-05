interface P {	
	public void r();
}
class S implements P {
	private P f;
	public S(P t) {
		this.f = t;
	}
	public void m(P a) {
		this.r();
		f.r();
	}
	public void r() {
		f.r();
	}
}
class Z implements P {
	public void q() {}
	public void r() {
		q();
	}
}
class Main {
	public static void main(String argv[]) {
		Z t = new Z();
		S s2 = new S(t);
		S s1 = new S(s2);
		/**/s1.m(s2);
	}
}