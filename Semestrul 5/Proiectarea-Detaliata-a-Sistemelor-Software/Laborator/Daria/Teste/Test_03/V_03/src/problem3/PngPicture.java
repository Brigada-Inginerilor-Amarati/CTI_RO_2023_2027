
package problem3;

public class PngPicture implements Picture {
    @Override
    public void accept(PictureVisitor visitor) {
        visitor.visit(this);
    }
}
