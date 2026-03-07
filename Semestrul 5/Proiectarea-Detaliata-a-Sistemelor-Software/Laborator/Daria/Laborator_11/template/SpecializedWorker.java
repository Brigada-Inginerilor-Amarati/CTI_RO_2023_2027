package Laborator.Daria.Laborator_11.template;

public class SpecializedWorker extends Worker {
    private int y;

    public SpecializedWorker(int _x, int _y) {
        super(_x);
        y = _y;
    }

    
    @Override
    protected void modifyX() {
        x += y;
    }

    @Override
    protected int calculateZ() {
        return x * x + y * y;
    }
}
