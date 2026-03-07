
package problem3;

public interface PictureVisitor {
    void visit(PngPicture png);
    void visit(SvgPicture svg);
    void visit(JpgPicture jpg);
}
