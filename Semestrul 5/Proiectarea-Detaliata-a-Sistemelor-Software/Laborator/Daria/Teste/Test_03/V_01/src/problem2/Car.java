
package problem2;

public class Car {
    private String type;
    private String brand;
    private String model;
    private double minPrice;
    private double maxPrice;
    private String profilePictureUrl;

    public Car(String type, String brand, String model, double minPrice, double maxPrice, String profilePictureUrl) {
        this.type = type;
        this.brand = brand;
        this.model = model;
        this.minPrice = minPrice;
        this.maxPrice = maxPrice;
        this.profilePictureUrl = profilePictureUrl;
    }

    public String getType() { return type; }
    public String getBrand() { return brand; }
    public String getModel() { return model; }
    public double getMinPrice() { return minPrice; }
    public double getMaxPrice() { return maxPrice; }
    public String getProfilePictureUrl() { return profilePictureUrl; }
}
