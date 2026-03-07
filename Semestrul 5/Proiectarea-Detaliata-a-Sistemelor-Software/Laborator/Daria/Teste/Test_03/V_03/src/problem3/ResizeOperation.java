
package problem3;

public class ResizeOperation implements PictureVisitor {
    @Override
    public void visit(PngPicture png) {
        System.out.println("Resizing PNG...");
    }

    @Override
    public void visit(SvgPicture svg) {
        System.out.println("Resizing SVG...");
    }

    @Override
    public void visit(JpgPicture jpg) {
        System.out.println("Resizing JPG...");
    }
}
