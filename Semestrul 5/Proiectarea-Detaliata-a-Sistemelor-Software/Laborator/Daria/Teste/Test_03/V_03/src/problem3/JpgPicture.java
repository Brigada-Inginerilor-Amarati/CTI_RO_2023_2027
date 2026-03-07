
package problem3;

public class JpgPicture implements Picture {
    @Override
    public void accept(PictureVisitor visitor) {
        visitor.visit(this);
    }
}
