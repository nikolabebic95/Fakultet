package kisa;

/**
 * Мерљива кап кише има случајну целобројну запремину од 3 до 10 mm3.
 */
public class Kap implements Merljiva {
    private static final double donja_ = 3;
    private static final double gornja_ = 10;
    private final double zapremina_ = Math.random() * (gornja_ - donja_) + donja_;

    @Override
    public double zapremina() {
        return zapremina_;
    }
}
