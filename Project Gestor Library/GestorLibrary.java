package Project1;
import java.util.HashMap;
import java.util.Map;

public class GestorLibrary {
	private Map<String, LibraryMaterial> inventory;
	
	public GestorLibrary() {
		this.inventory = new HashMap<>();
	}
	
	public void addMaterial (LibraryMaterial material) {
		inventory.put(material.getId(), material);
	}
	
	public void borrowMaterial(String id) throws MaterialNoAvailableException {
		LibraryMaterial material = inventory.get(id);
		
		if(material == null) {
			System.out.println("Error: It wasnt possible to find any material with the ID: " + id);
			return;
		}
		
		if(!material.getAvailable()) {
			throw new MaterialNoAvailableException("Material '" + material.getTitle() + "' is not available right now. ");
		}
		
		material.setAvailable(false);
		int days = material.getMaxDayShared();
		
		System.out.println("Successful loan, you are retired: " + material.getTitle() + " You have " + days + " days of loan: ");
		
	}

}
