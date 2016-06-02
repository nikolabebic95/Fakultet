package grafika;

/**
 * Тачка у равни садржи реалне координате x и y које се задају при стварању
 * (подразумевано (0,0)) и које могу да се дохвате.
 */
public class Tacka {
    private double x_;
    private double y_;

    public Tacka() {
        x_ = 0;
        y_ = 0;
    }

    public Tacka(double x) {
        x_ = x;
        y_ = 0;
    }

    public Tacka(double x, double y) {
        x_ = x;
        y_ = y;
    }

    public double x() {
        return x_;
    }

    public double y() {
        return y_;
    }

}
