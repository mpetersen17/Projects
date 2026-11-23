package Project1;

public class Magazine extends LibraryMaterial {
	public Magazine(String id, String title) {
		super(id, title);
	}
	@Override
	public int getMaxDayShared() {
		return 3;
	}
	
}
