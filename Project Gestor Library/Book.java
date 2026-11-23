package Project1;

public class Book extends LibraryMaterial {
	public Book(String id, String title) {
		super(id, title);
	}
	@Override
	public int getMaxDayShared() {
		return 14;
	}
}
