import java.util.Objects;

public class Car {
    private String brand;
    private String color;
    private int year;
    private boolean faceLifted;
    private Person owner;

    public Car(String brand, String color, int year, boolean faceLifted) {
        this.brand = brand;
        this.color = color;
        this.year = year;
        this.faceLifted = faceLifted;
    }

    public Car(String brand, String color, int year, boolean faceLifted, Person owner) {
        this.brand = brand;
        this.color = color;
        this.year = year;
        this.faceLifted = faceLifted;
        this.owner = owner;
    }

    public String getBrand() {
        return brand;
    }

    public void setBrand(String brand) {
        this.brand = brand;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public int getYear() {
        return year;
    }

    public void setYear(int year) {
        this.year = year;
    }

    public boolean isFaceLifted() {
        return faceLifted;
    }

    public void setFaceLifted(boolean faceLifted) {
        this.faceLifted = faceLifted;
    }

    public Person getOwner() {
        return owner;
    }

    public void setOwner(Person owner) {
        this.owner = owner;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Car car = (Car) o;
        return year == car.year &&
                faceLifted == car.faceLifted &&
                Objects.equals(brand, car.brand) &&
                Objects.equals(color, car.color) &&
                Objects.equals(owner, car.owner);
    }

    @Override
    public int hashCode() {
        return Objects.hash(brand, color, year, faceLifted, owner);
    }

    @Override
    public String toString() {
        return "Car{" +
                "brand='" + brand + '\'' +
                ", color='" + color + '\'' +
                ", year=" + year +
                ", faceLifted=" + faceLifted +
                ", owner=" + owner +
                '}';
    }
}
