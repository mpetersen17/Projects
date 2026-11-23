package Project1;

public abstract class LibraryMaterial {
	protected String id, title;
	protected boolean available; 
	
	public LibraryMaterial(String id, String title) {
		this.available = true;
		this.id = id;
		this.title = title;
	}
	
	public String getId() {
		return id;
	}
	
	public String getTitle() {
		return title;
	}
	
	public boolean getAvailable() {
		return available; 
	}
	
	public void setAvailable(boolean available) {
		this.available = available;
	}
	
	public abstract int getMaxDayShared (); 

}



