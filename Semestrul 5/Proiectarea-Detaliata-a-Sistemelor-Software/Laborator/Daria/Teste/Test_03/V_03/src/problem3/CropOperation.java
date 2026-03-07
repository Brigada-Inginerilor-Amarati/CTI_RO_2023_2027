
package problem3;

public class CropOperation implements PictureVisitor {
    @Override
    public void visit(PngPicture png) {
        System.out.println("Cropping PNG...");
    }

    @Override
    public void visit(SvgPicture svg) {
        System.out.println("Cropping SVG (Calculated vectors)...");
    }

    @Override
    public void visit(JpgPicture jpg) {
        System.out.println("Cropping JPG...");
    }
}
