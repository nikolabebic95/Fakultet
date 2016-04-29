package njive;

/**
 * Шума је парцела која има задате површину коју заузима стабло, принос по зрелом стаблу и
 * период сазревања од засада до сече изражен у целом броју година. Ознака врсте је S. Принос
 * се остварује тек за период који почиње засадом и траје барем један период сазревања. Сматра
 * се да се после сазревања шума сече и одмах сади нова, тако да се у сваком завршеном
 * периоду сазревања оствари пуни принос. Текстуални облик је парцела:(површСт,
 * приносСт,период).
 */
public class Suma extends Parcela {
    private double povrsinaStabla_;
    private double prinosPoStablu_;
    private int period_;

    public Suma(double povrsina, double povrsinaStabla, double prinosPoStablu, int period) {
        super(povrsina);
        povrsinaStabla_ = povrsinaStabla;
        prinosPoStablu_ = prinosPoStablu;
        period_ = period;
    }

    @Override
    public char vrsta() {
        return 'S';
    }

    @Override
    public double prinos(int godine) {
        return povrsinaStabla_ * prinosPoStablu_ * (godine / period_);
    }

    @Override
    public String toString() {
        return super.toString() + ":(" + povrsinaStabla_ + "," + prinosPoStablu_ + "," + period_ + ")";
    }
}
