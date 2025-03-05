class Message {
	
	private String text;
	private Person exp,dest;
	
	public Message(Person exp, Person dest, String text) {
		this.exp = exp;
		this.text = text;
		this.dest = dest;
	} 
	
	public Person getDest() {
		return dest;
	}
	
	public String toString() {
		return exp + " said to " + dest + ":" + text;
	}
}

class Person {
	
	private String name;
	private Transmitter t;
	
	public void setTransmitter(Transmitter t) {
		this.t = t;
	} 

	public Person(String name) {
		this.name = name;
	} 
	
	public void send(String text, Person dest) {
		Message m = new Message(this,dest,text);
		t.store(m);
	}
	
	public void notifyMail(Transmitter t) {
		System.out.println(t.retreive(this));
	}
	
	public boolean equals(Object o) {
		if(o instanceof Person) {
			return name.equals(((Person)o).name);
		}
		return false;
	}
	
	public String toString() {
		return name;
	}
}

interface Transmitter {
	public void store(Message m);
	public Message retreive(Person p);
}

class EMailTransmitter implements Transmitter {
	
	private Message m;
	
	private void recordMessage(Message m) {
		this.m = m;
	}
	
	public void store(Message a) {
		recordMessage(a);
		m.getDest().notifyMail(this);
	}
	
	public Message retreive(Person p) {
		return m;
	}
	
}

class Test {
	public static void main(String argvp[]) {
		Person p1 = new Person("Mircea");
		p1.setTransmitter(new EMailTransmitter());
		Person p2 = new Person("Radu");
		/**/p1.send("Ce faci?",p2);
	}
}