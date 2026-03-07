
package problem3;

public interface Picture {
    // Marker interface mostly, but needs to accept visitor to solve requirement "crucial that all Editing Operations can be performed"
    void accept(PictureVisitor visitor);
}
