package Project1;

public class main {
	public static void main(String[] args) {
		GestorLibrary library = new GestorLibrary();
		
		Book book1 = new Book("LQ1", "Eregon");
		Magazine magazine1 = new Magazine ("ZQ0", "Economics");
		
		library.addMaterial(book1);
		library.addMaterial(magazine1);
		
		try {	
			library.borrowMaterial("LQ1");
			library.borrowMaterial("LQ1");
		} catch (MaterialNoAvailableException e) {
			System.out.println("Capture on the catch: " + e.getMessage());
		}
	}

}
