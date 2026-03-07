
package problem3;

public class SvgPicture implements Picture {
    @Override
    public void accept(PictureVisitor visitor) {
        visitor.visit(this);
    }
}
