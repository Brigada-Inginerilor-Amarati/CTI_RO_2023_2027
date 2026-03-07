
package problem3;

public class Main {
    public static void main(String[] args) {
        Picture png = new PngPicture();
        Picture svg = new SvgPicture();
        
        PictureVisitor crop = new CropOperation();
        PictureVisitor resize = new ResizeOperation();
        
        System.out.println("--- Crop Operations ---");
        png.accept(crop);
        svg.accept(crop);
        
        System.out.println("\n--- Resize Operations ---");
        png.accept(resize);
        svg.accept(resize);
    }
}
