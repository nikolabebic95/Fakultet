package kisa;

import java.text.DecimalFormat;

/**
 * На мерљив бусен може да падне кап кише. Запремина бусена је укупна
 * запремина капи које су пале на њега. Вода са бусена може да испари.
 * Може да се направи копија бусена. Текстуални приказ бусена садржи
 * количину воде на бусену.
 */
public class Busen implements Merljiva, Cloneable {
    private double zapremina_ = 0;

    public Busen padni(Kap kap) {
        zapremina_ += kap.zapremina();
        return this;
    }

    public Busen ispari() {
        zapremina_ = 0;
        return this;
    }

    @Override
    public Busen clone() {
        try {
            return (Busen) super.clone();
        } catch (CloneNotSupportedException e) {
            return null; // Nece se nikad desiti ali mora nesto da se stavi da ne bi imalo throws
        }
    }

    @Override
    public double zapremina() {
        return zapremina_;
    }

    @Override
    public String toString() {
        DecimalFormat df = new DecimalFormat("#000.00");
        return df.format(zapremina_);
    }
}
